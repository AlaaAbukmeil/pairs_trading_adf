#include "headers.h"

vector<double> difference(const vector<double> &series, int lag = 1)
{
    vector<double> diff;
    for (size_t i = lag; i < series.size(); ++i)
    {
        diff.push_back(series[i] - series[i - lag]);
    }
    return diff;
}

double mean(const vector<double> &data)
{
    double sum = 0.0;
    for (double val : data)
    {
        sum += val;
    }
    return sum / data.size();
}

VectorXd ols_regression(const VectorXd &y, const MatrixXd &X)
{
    return (X.transpose() * X).ldlt().solve(X.transpose() * y);
}
// Function to prepare data for ADF regression
pair<VectorXd, MatrixXd> prepare_adf_data(const vector<double> &series, int max_lag)
{
    vector<double> y_diff = difference(series);
    size_t n = y_diff.size();

    VectorXd y(n);
    for (size_t i = 0; i < n; ++i)
    {
        y(i) = y_diff[i];
    }

    MatrixXd X(n, 2 + max_lag);
    for (size_t i = 0; i < n; ++i)
    {
        X(i, 0) = 1.0;           // Intercept term
        X(i, 1) = series[i + 1]; // Lagged level term
    }

    for (int lag = 1; lag <= max_lag; ++lag)
    {
        vector<double> lagged_diff = difference(series, lag);
        for (size_t i = 0; i < n; ++i)
        {
            X(i, 1 + lag) = lagged_diff[i];
        }
    }

    return make_pair(y, X);
}

double adf_test(const vector<double> &series, int max_lag = 1)
{
    pair<VectorXd, MatrixXd> data = prepare_adf_data(series, max_lag);
    VectorXd y = data.first;
    MatrixXd X = data.second;

    VectorXd beta = ols_regression(y, X);
    double gamma_hat = beta(1);
    double se_gamma_hat = sqrt((y - X * beta).squaredNorm() / (X.rows() - X.cols()) / (X.col(1).array() - X.col(1).mean()).matrix().squaredNorm());

    return gamma_hat / se_gamma_hat;
}