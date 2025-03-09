#include <iostream>
#include <fstream>

using namespace std;


void quick_sort(int* arr, int high, int low);


int main () {

    ifstream inputFile("input.txt");
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

    inputFile.close();

    ofstream fout("output_qs.txt");
    if (!fout) {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }

    // sort and fout

    quick_sort(arr, n-1, 0);
    for (int i = 0; i < n; i++) {
        fout << arr[i] << " ";
    }

    fout.close();

    return 0;
}


void quick_sort(int* arr, int high, int low) {
    
    if (low < high) {
        
        int pivot = arr[high];
        int i = low;
        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                swap(arr[i], arr[j]);
                i++;
            }
        }
        swap(arr[i], arr[high]);

        quick_sort(arr, i - 1, low);
        quick_sort(arr, high, i + 1);

    }
}