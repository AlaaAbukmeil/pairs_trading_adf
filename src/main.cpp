#include "headers.h"

int main()
{
    CURL *curl = curl_easy_init();
    if (!curl)
    {
        cerr << "Failed to initialize CURL." << endl;
        return 1;
    }
    // int size = 1000;
    string ticker_1 = "AAPL";
    string ticker_2 = "SOF";

    string start = "2023-06-01";
    string end = "2024-01-01";

    map<string, double> series_one = getData(start, end, ticker_1, curl);
    map<string, double> series_two = getData(start, end, ticker_2, curl);

    vector<double> time_series = calculatePriceDifferences(series_one, series_two);

    // vector<double> time_series = generateRandomTimeSeries(size);

    // Perform the ADF test
    double t_stat = adf_test(time_series, 1);

    // Output the results
    cout << "ADF Statistic: " << t_stat << endl;

    // Critical values (example values, these should be looked up from statistical tables)
    vector<pair<string, double>> critical_values = {
        {"1%", -3.436912745214975},
        {"5%", -2.864437258861224},
        {"10%", -2.5683139618813964}};

    cout << "Critical Values:" << endl;
    for (const auto &cv : critical_values)
    {
        cout << "   " << cv.first << ": " << cv.second << endl;
    }

    // Decision
    for (const auto &cv : critical_values)
    {
        if (t_stat < cv.second)
        {
            cout << "The time series is stationary at the " << cv.first << " significance level." << endl;
            break;
        }
        else
        {
            cout << "The time series is not stationary at the " << cv.first << " significance level." << endl;
            // break;
        }
    }
    curl_easy_cleanup(curl);
    return 0;
}