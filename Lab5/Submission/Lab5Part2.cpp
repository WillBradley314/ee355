#include <iostream>
#include <fstream>
#include <cstdlib> // for atoi
using namespace std;

// Function to extract and display command-line arguments using pointer-to-pointer
void extractCommandLineArgs(int argc, char** argv, ofstream &outputFile) {
    outputFile << "Extracted Command-Line Arguments:" << endl;
    for (int i = 0; i < argc; i++) {
        outputFile << "  - argv[" << i << "] = " << *argv << endl;
        argv++;
    }
}

// Function to swap two integers using pass-by-value (no effect)
void swapByValue(int a, int b) {
    int tempVar;
    tempVar = a;
    a = b;
    b = tempVar;
}

// Function to swap two integers using pass-by-reference (modifies values)
void swapByReference(int &a, int &b) {
    int tempVar = a;
    a = b;
    b = tempVar;
}

// Function to swap two integers using pass-by-pointer(modifies values)
void swapByPointer(int* a, int* b) {
    int tempVar = *a;
    *a = *b;
    *b = tempVar;
}

// Function to modify array: Double each value (using pass-by-pointer)
void doubleValues(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        *arr *= 2;
        arr++;
    }
}

// Function to compute sum and product using pass-by-reference
void computeSumAndProduct(int* arr, int size, int &sum, int &product) {
    sum = 0;
    product = 1;
    for (int i = 0; i < size; i++) {
        sum += *arr;
        product *= *arr;
        arr++;
    }
}

// Function to reverse an array using pointers (without array indexing)
void reverseArray(int* arr, int size) {
    for (int i = 0; i < size/2; i++) {
        swapByPointer(arr + i, arr + (size-i-1));
    }
}


// Main function
int main(int argc, char* argv[]) {


    // Convert command-line arguments to integers

    int* cmdLine = new int[argc-1];
    char **argvPtr = argv + 1; 
    int* cmdPtr = cmdLine; 

    for (int i = 0; i < argc-1; i++) {
        *cmdPtr = atoi(*argvPtr);
        cmdPtr++;
        argvPtr++;
    }
    cmdPtr = cmdLine;


    // Open output file
    
    ofstream fout("output_Q2.txt");


    // Print original array
    cmdPtr = cmdLine;
    fout << "Original Numbers: ";
    for (int i = 0; i < argc-1; i++) {
        fout << *cmdPtr << " ";
        cmdPtr++;
    }
    fout << endl << endl;
    cmdPtr = cmdLine;


    // Extract command-line arguments using pointer-to-pointer
    
    extractCommandLineArgs(argc, argv, fout);

    
    // Demonstrate pass-by-value (no effect)

    int a = *(cmdPtr + 1);
    int b = *(cmdPtr + 2);

    swapByValue(a, b);

    fout << endl << "Pass-by-Value Swap (No Effect):" << endl;
    fout << "  - Swap(" << *(cmdPtr + 1) << ", " << *(cmdPtr + 2) << ")"
    << " -> a = " << a << ", b = " << b << " (Unchanged)" << endl << endl;
    

    // Demonstrate pass-by-reference (modifies values)

    swapByReference(a, b);

    fout << "Pass-by-Reference Swap (Successful):" << endl;
    fout << "  - Swap(" << *(cmdPtr + 1) << ", " << *(cmdPtr + 2) << ")"
    << " -> a = " << a << ", b = " << b << endl << endl;
    

    // Modify array (double values using pointer)
    
    doubleValues(cmdLine, argc-1);
    
    cmdPtr = cmdLine;
    fout << "Pass-by-Pointer Modification:" << endl << "  - Doubled Values: ";
    for (int i = 0; i < (argc-1); i++) {
        fout << *cmdPtr << " ";
        cmdPtr++;
    }

    // Compute sum and product
    
    int sum, product;
    
    computeSumAndProduct(cmdLine, argc-1, sum, product);

    fout << endl << endl << "Sum of Numbers: " << sum << endl;
    fout << "Product of Numbers: " << product << endl;
    

    // Reverse array
    
    reverseArray(cmdLine, argc-1);
    
    cmdPtr = cmdLine;
    fout << endl << "Reversed Order: ";
    for (int i = 0; i < (argc-1); i++) {
        fout << *cmdPtr << " ";
        cmdPtr++;
    }


    fout.close();
    delete[] cmdLine;
    
    return 0;
}