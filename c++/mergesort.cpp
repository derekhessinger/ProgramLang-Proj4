/**
 * Generic merge sort algorithm that can be used with any data type
 *
 * Derek Hessinger
 * Prof. Ying Li
 * CS 333
 * 10/21/24
 */

#include <iostream>
#include <vector>
using namespace std;

// Comparator for the integer sorting logic
template<typename T>
struct IntegerComparator {
    int operator()(const T& p, const T& q) const {
        // If both numbers are even, sort in descending order
        if (p % 2 == 0 && q % 2 == 0) {
            return q - p;  // Descending order for even numbers
        }
        // If both numbers are odd, sort in ascending order
        else if (p % 2 == 1 && q % 2 == 1) {
            return p - q;  // Ascending order for odd numbers
        }
        // If p is even and q is odd, p should come first
        else if (p % 2 == 0 && q % 2 == 1) {
            return -1;  // p comes before q (even before odd)
        }
        // If p is odd and q is even, q should come first
        else {
            return 1;  // q comes before p (even before odd)
        }
    }
};

// Helper function to merge two sorted subarrays
template<typename T, typename Comparator>
void merge(vector<T>& arr, const vector<T>& left_arr, const vector<T>& right_arr, Comparator comp) {
    int i = 0, j = 0, k = 0;
    int left_size = left_arr.size();
    int right_size = right_arr.size();

    while (i < left_size && j < right_size) {
        if (comp(left_arr[i], right_arr[j]) >= 0) {
            arr[k++] = right_arr[j++];
        } else {
            arr[k++] = left_arr[i++];
        }
    }

    while (i < left_size) {
        arr[k++] = left_arr[i++];
    }

    while (j < right_size) {
        arr[k++] = right_arr[j++];
    }
}

// Recursive merge sort function
template<typename T, typename Comparator>
void merge_sort(vector<T>& arr, Comparator comp) {
    if (arr.size() <= 1) {
        return;
    }

    int mid = arr.size() / 2;
    vector<T> left(arr.begin(), arr.begin() + mid);
    vector<T> right(arr.begin() + mid, arr.end());

    merge_sort(left, comp);
    merge_sort(right, comp);
    merge(arr, left, right, comp);
}

// Wrapper function that uses the integer comparator
template<typename T>
void merge_sort(vector<T>& arr) {
    merge_sort(arr, IntegerComparator<T>());
}

int main(int argc, char** argv) {
    // Example with integers using default comparator
    vector<int> arr1 = {10, 11, 1, 8, 9, 0, 13, 4, 2, 7, 6, 3, 5, 12};
    merge_sort(arr1);
    
    cout << "Sorted integers with custom even/odd comparator: ";
    for (const auto& num : arr1) {
        cout << num << " ";
    }
    cout << endl;

    // Example with doubles using a simple less-than comparator
    vector<double> arr2 = {3.14, 1.41, 2.71, 0.58, 1.73};
    merge_sort(arr2, [](const double& a, const double& b) { return a < b ? -1 : (a > b ? 1 : 0); });
    
    cout << "Sorted doubles with standard comparison: ";
    for (const auto& num : arr2) {
        cout << num << " ";
    }
    cout << endl;

    // Example with strings using standard string comparison
    vector<string> arr3 = {"banana", "apple", "cherry", "date"};
    merge_sort(arr3, [](const string& a, const string& b) { return a.compare(b); });
    
    cout << "Sorted strings alphabetically: ";
    for (const auto& str : arr3) {
        cout << str << " ";
    }
    cout << endl;

    return 0;
}