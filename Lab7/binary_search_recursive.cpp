#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;


bool recursive_binary_search(int* arr, int high, int low, int n, ofstream &fout);

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

    bool found = recursive_binary_search(arr, n, 0, target, fout);
    if (!found) {
        fout << "Not Found" << endl;
    }
    fout.close();


    return 0;
}


bool recursive_binary_search(int* arr, int high, int low, int target, ofstream &fout) {
    int mid;
    bool found = false;
    if (high > low+1) {
        mid = (high+low)/2;
        if (target > arr[mid]) {
            found = recursive_binary_search(arr, high, mid, target, fout);
        }
        else if (target < arr[mid]) {
            found = recursive_binary_search(arr, mid, low, target, fout);
        }
        else {
            fout << mid << endl;
            found = true;
        }   
    }
    return found;
}
