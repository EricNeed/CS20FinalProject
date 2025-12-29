#include "script_storge/radix_sort.h"

void countSort(std::vector<int>& vec, int exp) {
    int n = vec.size();
    std::vector<int> output(n);
    std::vector<int> count(10, 0);
    
    for (int i = 0; i < n; i++)
        count[(vec[i] / exp) % 10]++;
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];
    
    for (int i = n - 1; i >= 0; i--) {
        output[count[(vec[i] / exp) % 10] - 1] = vec[i];
        count[(vec[i] / exp) % 10]--;
    }
    
    for (int i = 0; i < n; i++)
        vec[i] = output[i];
}

void radixSort(std::vector<int>& vec) {
    if (vec.empty()) return;
    int max_val = *std::max_element(vec.begin(), vec.end());
    
    for (int exp = 1; max_val / exp > 0; exp *= 10)
        countSort(vec, exp);
}