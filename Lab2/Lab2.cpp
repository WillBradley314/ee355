#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class matrix {

    public:
        int value[10][10];
        int row;
        int max;
        int min;

        void popmat(string);
        void linSearch(string);
        void add(matrix, string);
        void mult(matrix, string);   


};




int main(){
    string m1 = "matrix_1.txt";
    string m2 = "matrix_2.txt";
    string Q11 = "output_Q1_1.txt";
    string Q12 = "output_Q1_2.txt";
    string Q2 = "output_Q2.txt";
    string Q3 = "output_Q3.txt";


    matrix matrix1;
    matrix matrix2;

    matrix1.popmat(m1);
    matrix2.popmat(m2);

    matrix1.linSearch(Q11);
    matrix2.linSearch(Q12);

    matrix1.add(matrix2, Q2);

    matrix1.mult(matrix2, Q3);

    return 0;
}


void matrix::popmat(string fileName) {
    //string fileName;
    string currLine;
    //cout << "Matrix File:" << endl;
    //cin >> fileName;
    ifstream matFile;
    matFile.open(fileName);
    if (!matFile.is_open()){
        cerr << "error opening file" << endl;
    }
    else {
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                matFile >> value[i][j];
                
            }
        }
        matFile.close();
    }

}


void matrix::linSearch(string lsOut){
    row = 11;
    max = 0;
    min = value[0][0];
    //string lsOut;
    ofstream outFile;

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if ((value[i][j] == value[0][0]) && (row == 11) && i && j){
                row = i;
            }
            if(value[i][j] > max) {
                max = value[i][j];
            }
            if(value[i][j] < min) {
                min = value[i][j];
            }
        }
    }
    
    //cout << "Enter Linear Search Output File Name: " << endl;
    //cin >> lsOut;
    outFile.open(lsOut);

    if (!outFile.is_open()){
        cerr << "error opening file" << endl;
    }
    else {
        if(row != 11){
            outFile << "Target value is shown in row " << row << endl << endl;
        }
        else {
            outFile << "Target value is not shown" << endl << endl;
        }
        outFile << "Maximum value is " << max << endl << endl;
        outFile << "Minimum value is " << min;
        outFile.close();
    }
}



 void matrix::add(matrix otherMatrix, string sumOut){
    matrix sumMatrix;
    //string sumOut;
    ofstream outFile;
    
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            sumMatrix.value[i][j] = value[i][j] + otherMatrix.value[i][j];
        }
    }

    //cout << "Enter Matrix Addition Output File Name: " << endl;
    //cin >> sumOut;
    outFile.open(sumOut);

    if (!outFile.is_open()){
        cerr << "error opening file" << endl;
    }
    else {
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                outFile << sumMatrix.value[i][j] << " ";
                if (j == 9){
                    outFile << endl;
                }        
            }
        }
        outFile.close();
    }
}


void matrix::mult(matrix otherMatrix, string prodOut){
    matrix prodMatrix;
    int sum;
    //string prodOut;
    ofstream outFile;
    
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            prodMatrix.value[i][j] = 0;
            for (int k = 0; k < 10; k++) {
                prodMatrix.value[i][j] += value[i][k] * otherMatrix.value[k][j];
            }  
        }
    }

    //cout << "Enter Matrix Multiplication Output File Name: " << endl;
    //cin >> prodOut;
    outFile.open(prodOut);

    if (!outFile.is_open()){
        cerr << "error opening file" << endl;
    }
    else {
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                outFile << prodMatrix.value[i][j] << " ";
                if (j == 9){
                    outFile << endl;
                }        
            }
        }
        outFile.close();
    }
}