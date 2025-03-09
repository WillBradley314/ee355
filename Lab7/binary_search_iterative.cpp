#include <iostream>
#include <algorithm>
#include <fstream>
#include <cmath>

using namespace std;


void iterative_binary_search(int* arr, int n, int target, ofstream &fout);

int main()
{
    std::ifstream inputFile("input.txt");
    if (!inputFile)
    {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }

    int n;
    inputFile >> n;

    int *arr = new int[n];
    for (int i = 0; i < n; ++i)
    {
        inputFile >> arr[i];
    }

    int target;
    inputFile >> target;

    inputFile.close();

    std::sort(arr, arr + n); // Ensure the array is sorted

    ofstream fout("output_bs.txt");
    if (!fout) {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }

    iterative_binary_search(arr, n, target, fout);
    
    fout.close();

    return 0;
}


void iterative_binary_search(int* arr, int n, int target, ofstream &fout) {
    int high = n;
    int low = 0;
    int mid;
    bool found = false;
    
    for (int i = 0; i < n; i++) {
        mid = (high + low) / 2;
        if (target > arr[mid]) {
            low = mid;
        }
        else if (target < arr[mid]) {
            high = mid;
        }
        else {
            found = true;
        }
    }

    if (found) {
        fout << mid << endl;
    }
    else {
        fout << "Not Found" << endl;
    }

}
