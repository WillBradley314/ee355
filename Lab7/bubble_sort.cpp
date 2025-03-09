#include <iostream>
#include <fstream>

using namespace std;


void bubble_sort(int* arr, int n, ofstream &fout);


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

    ofstream fout("output_bubble.txt");
    if (!fout) {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }

    bubble_sort(arr, n, fout);

    fout.close();

    return 0;
}


void bubble_sort(int* arr, int n, ofstream &fout) {
    bool done = false;
    while (!done) {
        done = true;
        for (int i = 0; i < n-1; i++) {
            if(arr[i] > arr[i+1]) {
                swap(arr[i], arr[i+1]);
                done = false;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        fout << arr[i] << " ";
    }
}
