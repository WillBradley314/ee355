#include <iostream>
#include <fstream>

using namespace std;


void merge_sort(int* arr, int high, int low);


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

    ofstream fout("output_ms.txt");
    if (!fout) {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }

    // sort and fout

    merge_sort(arr, n-1, 0);
    for (int i = 0; i < n; i++) {
        fout << arr[i] << " ";
    }

    fout.close();

    return 0;
}


void merge_sort(int* arr, int high, int low) {
    int mid;
    if (high > low) {
        mid = (high+low)/2;


        int L1 = mid - low + 1;
        int L2 = high - mid;
    
        int* arr1 = new int[L1];
        int* arr2 = new int[L2];


        cout << "Splitting:" << endl;
        for (int i = 0; i <= high; i++) {
            cout << arr[i] << " ";
        }
        cout << endl << "Into:" << endl;
        for (int i = 0; i < L1; i++) {
            cout << arr[i+low] << " ";
        }
        cout << endl;
        for (int i = 0; i < L2; i++) {
            cout << arr[i+mid+1] << " ";
        }
        cout << endl;

        merge_sort(arr, mid, low);
        merge_sort(arr, high, mid+1);

        for (int i = 0; i < L1; i++) {
            arr1[i] = arr[i + low];
        }
        for (int i = 0; i < L2; i++) {
            arr2[i] = arr[i + mid + 1];
        }

        int i = 0, j = 0;

        while (i < L1 || j < L2) {
            if (i < L1 && j < L2)
                if (arr1[i] < arr2[j]) {
                    arr[low] = arr1[i];
                    i++;
                }
                else {
                    arr[low] = arr2[j];
                    j++;
                }
            else {
                if (i < L1) {
                    arr[low] = arr1[i];
                    i++;
                }
                if (j < L2) {
                    arr[low] = arr2[j];
                    j++;
                }
            }
            low++;
        }
        cout << "Merging:" << endl;
        for (int i = 0; i < L1; i++) {
            cout << arr1[i] << " ";
        }
        cout << endl;
        for (int i = 0; i < L2; i++) {
            cout << arr2[i] << " ";
        }        
        cout << endl << "Into:" << endl;
        for (int i = 0; i <= high; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;

        delete[] arr1;
        delete[] arr2;
    }



}