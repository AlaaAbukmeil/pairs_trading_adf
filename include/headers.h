#ifndef HEADER_H
#define HEADER_H

#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <Eigen/Dense>
#include <random>
#include <ctime>
#include <cmath>

using namespace std;
using namespace Eigen;
using namespace nlohmann;

const string baseUrl = "https://api.triadacapital.com/api/web/";

struct Response
{
    string body;
};

// Function prototypes
Response httpGet(CURL *curl, const string &url);
size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
string httpPost(CURL *curl, const string &url, const string &data);
int checkAuth();

vector<double> difference(const vector<double> &series, int lag);
double mean(const vector<double> &data);
VectorXd ols_regression(const VectorXd &y, const MatrixXd &X);
pair<VectorXd, MatrixXd> prepare_adf_data(const vector<double> &series, int max_lag);
double adf_test(const vector<double> &series, int max_lag);
vector<double> generateRandomTimeSeries(int size);
vector<double> generateWhiteNoise(int size, double mean, double stddev, unsigned seed);
string getApiKey(const string &configFile);
map<string, double> getData(const string &start, const string &end, const string &ticker, CURL *curl);
string convertTimestampToDate(long long timestamp);
vector<double> calculatePriceDifferences(const map<string, double> &map1, const map<string, double> &map2);
#endif