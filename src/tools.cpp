#include "headers.h"

vector<double> generateRandomTimeSeries(int size)
{
    vector<double> time_series(size);
    random_device rd;                            // Seed generator
    mt19937 gen(rd());                           // Mersenne Twister engine to generate random numbers
    uniform_real_distribution<> dis(0.0, 100.0); // Uniform distribution between 0 and 100

    for (int i = 0; i < size; ++i)
    {
        time_series[i] = dis(gen);
    }

    return time_series;
}
vector<double> generateWhiteNoise(int size, double mean, double stddev, unsigned seed)
{
    vector<double> series(size);
    mt19937 gen(seed); // Standard mersenne_twister_engine seeded with seed
    normal_distribution<> dis(mean, stddev);

    for (int i = 0; i < size; ++i)
    {
        series[i] = dis(gen);
    }
    return series;
}
string convertTimestampToDate(long long timestamp)
{
    time_t rawTime = timestamp / 1000; // Convert from milliseconds to seconds
    struct tm *dt;
    char buffer[30];
    dt = localtime(&rawTime);
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", dt);
    return string(buffer);
}
vector<double> calculatePriceDifferences(const map<string, double> &map1, const map<string, double> &map2)
{
    vector<double> result;

    for (const auto &entry : map1)
    {
        const string &date = entry.first;
        double price1 = entry.second;

        // Check if the key exists in the second map
        auto it = map2.find(date);
        if (it != map2.end())
        {
            double price2 = it->second;
            double difference = price1 - price2;
            result.push_back(difference);
        }
    }

    return result;
}