#include "the1.h"

// DO NOT CHANGE ABOVE THIS LINE!
// you may implement helper functions below

void partition(unsigned short *A, int size, int &left_pivot, int &right_pivot, long &swap) {
    int i = 1; // Start from 1 to prevent negative indices
    int j = 1;
    int k = size - 1;
    unsigned short pivot = A[0];

    while (j <= k) {
        if (A[j] == pivot) {
            j = j + 1;
        } else if (A[j] < pivot) {
            std::swap(A[i], A[j]);
            swap++;
            i = i + 1;
            j = j + 1;
        } else { // A[j] > pivot
            std::swap(A[j], A[k]);
            swap++;
            k = k - 1;
        }
    }
    // Swap pivot into its correct position
    std::swap(A[i - 1], A[0]);
    swap++;

    left_pivot = i - 1;
    right_pivot = j;
}

void quicksort3(unsigned short *A, int size, long &swap, unsigned int &rec_calls) {
    rec_calls++; // Increment at the start of every function call
    if (size <= 1) {
        return;
    }
    int left_pivot, right_pivot;
    partition(A, size, left_pivot, right_pivot, swap);

    // Recursive calls without conditionals
    quicksort3(A, left_pivot, swap, rec_calls);
    quicksort3(A + right_pivot, size - right_pivot, swap, rec_calls);
}

std::pair<unsigned short, unsigned int> select_k_with_quick_sort3(unsigned short *arr,
                                                                  unsigned int size,
                                                                  unsigned int index,
                                                                  long &swap) {
    unsigned int rec_calls = 0;
    quicksort3(arr, size, swap, rec_calls);
    return std::make_pair(arr[index], rec_calls);
}

unsigned short quickselect3(unsigned short *A, int size, unsigned int k, long &swap, unsigned int &rec_calls) {
    rec_calls++; // Increment at the start of every function call
    if (size == 1) {
        return A[0];
    }
    int left_pivot, right_pivot;
    partition(A, size, left_pivot, right_pivot, swap);

    if (k < left_pivot) {
        // The desired element is in the left partition
        return quickselect3(A, left_pivot, k, swap, rec_calls);
    } else if (k >= right_pivot) {
        // The desired element is in the right partition
        return quickselect3(A + right_pivot, size - right_pivot, k - right_pivot, swap, rec_calls);
    } else {
        // The desired element is the pivot
        return A[left_pivot];
    }
}

std::pair<unsigned short, unsigned int> quick_select3(unsigned short *arr,
                                                      unsigned int size,
                                                      unsigned int index,
                                                      long &swap) {
    unsigned int rec_calls = 0;
    unsigned short kth_element = quickselect3(arr, size, index, swap, rec_calls);
    return std::make_pair(kth_element, rec_calls);
}
