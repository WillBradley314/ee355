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

        void popmat();
        void linSearch();
        matrix add(matrix);
        matrix mult(matrix);   


};




int main(){

    matrix matrix1;
    matrix matrix2;

    matrix1.popmat();
    matrix2.popmat();

    matrix1.linSearch();
    matrix2.linSearch();

    matrix1.add(matrix2);

    matrix1.mult(matrix2);

    return 0;
}


void matrix::popmat() {
    string fileName;
    string currLine;
    cout << "Matrix File:" << endl;
    cin >> fileName;
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

        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                cout << value[i][j] << " ";
                if (j == 9){
                    cout << endl;
                }        
            }
        }
        

    }

}


void matrix::linSearch(){
    row = 11;
    max = 0;
    min = value[0][0];
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if ((value[i][j] == value[0][0]) && (row == 11) && i && j){
                row = i+1;
            }
            if(value[i][j] > max) {
                max = value[i][j];
            }
            if(value[i][j] < min) {
                min = value[i][j];
            }
        }
    }
    if(row != 11){
        cout << "Target value is shown in row " << row << endl;
    }
    else {
        cout << "Target value is not shown" << endl;
    }
    cout << "Maximum value is " << max << endl;
    cout << "Minimum value is " << min << endl;
}



matrix matrix::add(matrix otherMatrix){
    matrix sumMatrix;
    
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            sumMatrix.value[i][j] = value[i][j] + otherMatrix.value[i][j];
        }
    }

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            cout << sumMatrix.value[i][j] << " ";
            if (j == 9){
                cout << endl;
            }        
        }
    }

    return sumMatrix;
}


matrix matrix::mult(matrix otherMatrix){

    matrix prodMatrix;
    int sum;
    
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            for (int k = 0; k < 10; k++) {
                prodMatrix.value[i][j] += value[i][k] * otherMatrix.value[k][j];
            }  
        }
    }

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            cout << prodMatrix.value[i][j] << " ";
            if (j == 9){
                cout << endl;
            }        
        }
    }

    return prodMatrix;

}