#include <iostream>
#include <vector>
#include <chrono>
#include <random>

using namespace std;
using namespace chrono;

// Function to perform linear search in a single-threaded manner
int LinearSearch(const vector<int>& A, int x, int N) {
    for (int i = 0; i < N; ++i) {
        if (A[i] == x) {
            return i; // Return index if element is found
        }
    }
    return -1; // Return -1 if element is not found
}

// Function to perform refined multipart linear search with N=2 segments
int RefinedMultipartLS_N2(const vector<int>& A, int x, int N) {
    int p1 = 0, as = p1;
    int p2 = N / 2, bs = p2, ae = p2 - 1;
    int be = N - 1;

    while (as <= ae && bs <= be) {
        if (A[as] == x) return as;
        if (A[ae] == x) return ae;
        if (A[bs] == x) return bs;
        if (A[be] == x) return be;
        
        as++; ae--;
        bs++; be--;
    }
    return -1; // Return -1 if element is not found
}

// Function to perform refined multipart linear search with N=3 segments
int RefinedMultipartLS_N3(const vector<int>& A, int x, int N) {
    int p1 = 0, as = p1;
    int p2 = N / 3, bs = p2, ae = p2 - 1;
    int p3 = p2 * 2, cs = p3, be = p3 - 1;
    int ce = N - 1;

    while (as <= ae && bs <= be && cs <= ce) {
        if (A[as] == x) return as;
        if (A[ae] == x) return ae;
        if (A[bs] == x) return bs;
        if (A[be] == x) return be;
        if (A[cs] == x) return cs;
        if (A[ce] == x) return ce;

        as++; ae--;
        bs++; be--;
        cs++; ce--;
    }
    return -1; // Return -1 if element is not found
}

int main() {
    random_device rd;
    default_random_engine gen(rd());
    uniform_int_distribution<int> dist(0, 49999);

    // Create an array with values from 0 to 9999
    vector<int> arr(50000);
    for (int i = 0; i < 50000; ++i) {
        arr[i] = i;
    }

    int target = dist(gen);//40486; //dist(gen); // Example target element
    int N = arr.size(); // Size of the array

    // Measure the time taken for the linear search
    auto startTime = high_resolution_clock::now();
    int index = LinearSearch(arr, target, N);
    auto endTime = high_resolution_clock::now();

    // Calculate the duration
    auto duration1 = duration<double, milli>(endTime - startTime);

    if (index != -1) {
        cout << "Element " << target << " found at index " << index << "." << endl;
    } else {
        cout << "Element not found." << endl;
    }

    cout << "Time taken: " << duration1.count() << " ms for Linear Search" << endl;

    // Measure the time taken for the Refined Multipart Linear Search (RMLS) n=2
    startTime = high_resolution_clock::now();
    index = RefinedMultipartLS_N2(arr, target, N);
    endTime = high_resolution_clock::now();

    // Calculate the duration
    auto duration2 = duration<double, milli>(endTime - startTime);

    if (index != -1) {
        cout << "Element " << target << " found at index " << index << "." << endl;
    } else {
        cout << "Element not found." << endl;
    }

    cout << "Time taken: " << duration2.count() << " ms for RMLS_N2" << endl;

    // Measure the time taken for the Refined Multipart Linear Search (RMLS) n=4
    startTime = high_resolution_clock::now();
    index = RefinedMultipartLS_N3(arr, target, N);
    endTime = high_resolution_clock::now();

    // Calculate the duration
    auto duration3 = duration<double, milli>(endTime - startTime);

    if (index != -1) {
        cout << "Element " << target << " found at index " << index << "." << endl;
    } else {
        cout << "Element not found." << endl;
    }

    cout << "Time taken: " << duration3.count() << " ms for RMLS_N3" << endl;

    return 0;
}
