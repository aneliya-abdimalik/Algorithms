#include "the2.h"

// DO NOT CHANGE ABOVE THIS LINE!
// you may implement helper functions below

int getKey(const std::string& s, int pos, int group_size) {
    int key = 0;
    for (int i = 0; i < group_size; ++i) {
        int char_pos = pos - group_size + 1 + i;
        int char_value = 0;
        if (char_pos >= 0 && char_pos < s.size()) {
            char_value = s[char_pos] - 'A' + 1; // Map 'A' to 1, ..., 'Z' to 26
        }
        key = key * 27 + char_value; // 27 to include 0 (missing character)
    }
    return key;
}

long CountingSort(std::string* arr, int size, int group_size, int pos, bool ascending) {
    long iterations = 0;

    // Compute keys and find maximum key value
    int* keys = new int[size];
    int max_key = 0;
    for (int i = 0; i < size; ++i) {
        keys[i] = getKey(arr[i], pos, group_size);
        if (keys[i] > max_key)
            max_key = keys[i];
    }

    // Initialize count array
    int k = max_key + 1;
    int* C = new int[k]{0};

    // Counting occurrences
    for (int j = 0; j < size; ++j) {
        C[keys[j]]++;
        iterations++;
    }

    // Build cumulative counts
    int* count_cum = new int[k];
    if (ascending) {
        count_cum[0] = C[0];
        for (int i = 1; i < k; ++i) {
            count_cum[i] = count_cum[i - 1] + C[i];
            iterations++;
        }
    } else {
        count_cum[k - 1] = C[k - 1];
        for (int i = k - 2; i >= 0; --i) {
            count_cum[i] = count_cum[i + 1] + C[i];
            iterations++;
        }
    }

    // Build the output array
    std::string* B = new std::string[size];
    if (ascending) {
        for (int j = size - 1; j >= 0; --j) {
            int key = keys[j];
            int index = count_cum[key] - 1;
            B[index] = arr[j];
            count_cum[key]--;
            iterations++;
        }
    } else {
        for (int j = 0; j < size; ++j) {
            int key = keys[j];
            int index = count_cum[key] - 1;
            B[index] = arr[j];
            count_cum[key]--;
            iterations++;
        }
    }

    // Copy back to arr
    for (int i = 0; i < size; ++i) {
        arr[i] = B[i];
        iterations++;
    }

    // Clean up
    delete[] keys;
    delete[] C;
    delete[] count_cum;
    delete[] B;

    return iterations;
}

long multi_digit_string_radix_sort(std::string* arr,
                                   const int size,
                                   const bool ascending,
                                   const int group_size) {
    long total_iterations = 0;

    // Compute maximum string length
    int max_length = 0;
    for (int i = 0; i < size; ++i) {
        if (arr[i].length() > max_length)
            max_length = arr[i].length();
    }

    // Compute number of passes
    int num_passes = (max_length + group_size - 1) / group_size;

    // Perform radix sort
    for (int pass = 0; pass < num_passes; ++pass) {
        int pos = max_length - 1 - pass * group_size;
        int current_group_size = group_size;
        if (pos - group_size + 1 < 0) {
            current_group_size = pos + 1;
        }
        total_iterations += CountingSort(arr, size, current_group_size, pos, ascending);
    }

    return total_iterations;
}
