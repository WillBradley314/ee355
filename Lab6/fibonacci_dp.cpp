#include <iostream>


using namespace std;


int f_dp(int n, int* arr);


int main(int argc, char* argv[]) {
    int input = stoi(argv[1]);
    int* arr = new int[input+1];
    int f = 0;
    int i = 0;
    
    

    while (input > f) {
        f = f_dp(i, arr);
        i++;
    }
    if (input == f) {
        cout << 1 << endl;
    }
    else {
        cout << 0 << endl;
        cout << f << endl;
    }


    delete[] arr;

    return 0;
}



int f_dp(int n, int* arr) {
    if (n < 2) {
        arr[n] = n;
    }
    else {
        arr[n] = (arr[n-1] + arr[n-2]);
    }
    return arr[n];
}

