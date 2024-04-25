#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

template<typename T>
T parallelMin(const vector<T>& data) {
T result = data[0];
#pragma omp parallel for reduction(min: result)
for (size_t i = 1; i < data.size(); i++) {
result = min(result, data[i]);
}
return result;
}

template<typename T>
T parallelMax(const vector<T>& data) {
T result = data[0];
#pragma omp parallel for reduction(max: result)
for (size_t i = 1; i < data.size(); i++) {
result = max(result, data[i]);
}
return result;
}

template<typename T>
T parallelSum(const vector<T>& data) {
T result = 0;
#pragma omp parallel for reduction(+: result)
for (size_t i = 0; i < data.size(); i++) {
result += data[i];
}
return result;
}

template<typename T>
double parallelAverage(const vector<T>& data) {
T sum = parallelSum(data);
return static_cast<double>(sum) / data.size();
}

int main() {
vector<int> data;
for (int i = 0; i < 100; i++) {
data.push_back(rand() % 100);
}
cout << "Random Data: ";
for (auto i : data) {
cout << i << " ";
}

int minResult = parallelMin(data);
cout << "Min: " << minResult << endl;
int maxResult = parallelMax(data);
cout << "Max: " << maxResult << endl;
int sumResult = parallelSum(data);
cout << "Sum: " << sumResult << endl;
double averageResult = parallelAverage(data);
cout << "Average: " << averageResult << endl;
return 0;
}