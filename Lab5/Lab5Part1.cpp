#include <iostream>
#include <fstream>

using namespace std;


void read_arr(int* array, int n, ifstream& fin);
void print_arr(int* array, int n, string title); 
void write_arr(int* array, int n, ofstream& fout);
void trans_arr(int* array, int n); 
int max_arr(int* array, int n);
int min_arr(int* array, int n);
void prefix_sum_arr(int* array, int n); 








int main () {

    int n, max, min;
    ifstream fin("input.txt");
    ofstream fout("output.txt");
 
    fin >> n;
    int* arr = new int[n];
    
    
    read_arr(arr, n, fin);
    print_arr(arr, n, "Original Array");
    
    fout << "Original Array: ";
    write_arr(arr, n, fout);
    fout << endl << endl;


    trans_arr(arr, n);

    fout << "Modified Array:" << endl;
    fout << "  - Doubled even numbers & Squared odd numbers: ";
    write_arr(arr, n, fout);
    fout << endl << endl;


    max = max_arr(arr, n);
    min = min_arr(arr, n);
    
    cout << "Max: " << max << endl;
    cout << "Min: " << min << endl;
    fout << "Max Value: " << max << endl;
    fout << "Min Value: " << min << endl << endl;


    prefix_sum_arr(arr, n);
    
    fout << "Prefix Sum Array: ";
    write_arr(arr, n, fout);    


    delete[] arr;
    fin.close();
    fout.close();

    return 0;
}

void read_arr(int* array, int n, ifstream& fin) {

    for (int i = 0; i < n; i++) {
        fin >> *array;
        array++;
    }
    array -= n;
}


void print_arr(int* array, int n, string title) {    
    cout << title << ": ";
    for (int i = 0; i < n; i++) {
        cout << *array << " ";
        array++;
    }
    cout << endl;
    array -= n;
}

void write_arr(int* array, int n, ofstream& fout) {
    
    for (int i = 0; i < n; i++) {
        fout << *array << " ";
        array++;
    }
    array -= n;
}

void trans_arr(int* array, int n) {
    for (int i = 0; i < n; i++) {
        if ((*array % 2) == 0) {
            *array *= 2;
        }
        else {
            *array *= *array;
        }
        array++;
    }
    array -= n;
}

int max_arr(int* array, int n) {
    int max = 0;
    for (int i = 0; i < n; i++) {
        if (max < *array) {
            max = *array;
        }
        array++;
    }
    array -= n;
    return max;
}

int min_arr(int* array, int n) {
    int min = *array;
    for (int i = 0; i < n; i++) {
        if (min > *array) {
            min = *array;
        }
        array++;
    }
    array -= n;
    return min;
}

void prefix_sum_arr(int* array, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += *array;
        *array = sum;
        array++;
    }
    array -= n;    
}
