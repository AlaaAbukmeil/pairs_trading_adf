#include "headers.h"

string getApiKey(const string &configFile)
{
    ifstream file(configFile);
    string line;
    while (getline(file, line))
    {
        if (line.find("API_KEY=") == 0)
        {
            return line.substr(8); // Length of "API_KEY="
        }
    }
    return "";
}

map<string, double> getData(const string &start, const string &end, const string &ticker, CURL *curl)
{
    string apiKey = getApiKey("./config/config.txt");
    if (apiKey.empty())
    {
        cerr << "API Key not found." << endl;
        return {};
    }

    string url = "https://api.polygon.io/v2/aggs/ticker/" + ticker + "/range/1/day/" + start + "/" + end + "?adjusted=true&sort=asc&apiKey=" + apiKey;
    Response data = httpGet(curl, url);

    json jsonData;
    try
    {
        jsonData = json::parse(data.body);
    }
    catch (json::parse_error &e)
    {
        cerr << "JSON parse error: " << e.what() << endl;
        return {};
    }

    // Print the JSON data
    // cout << jsonData.dump(4) << endl;

    // Extract and print relevant data
    map<string, double> result;
    if (jsonData.contains("results"))
    {
        for (const auto &item : jsonData["results"])
        {
            if (item.contains("t") && item.contains("c"))
            {                                                                     // Assuming "t" is the timestamp and "c" is the closing price
                string date = convertTimestampToDate(item["t"].get<long long>()); // Convert timestamp to string (or format as needed)
                double closingPrice = item["c"].get<double>();
                result[date] = closingPrice;
            }
        }
    }
    else
    {
        cerr << "No results found in the response." << endl;
    }

    return result;
};