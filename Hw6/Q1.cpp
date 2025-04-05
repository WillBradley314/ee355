#include <iostream>

using namespace std;

int main() {
    int n;
    cout << "Enter array length: ";
    cin >> n;
    int* arr = new int[n];
    
    for (int i = 0; i < n; i++) {
        cout << "Enter element " << i << ": ";
        cin >> arr[i];
    }

    cout << "Array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    delete[] arr;



    return 0;
}