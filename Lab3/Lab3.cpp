#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <time.h>


using namespace std;



class matrix {
    public:
        vector<vector<int>> value;
        int row;
        int max;
        int min;

        matrix mult(matrix, int);
        matrix stras(matrix, int);  
        matrix add(matrix, int);
        matrix sub(matrix, int);

        vector<vector<matrix>> splitMatrix(int);

        matrix(int size) {
            value.resize(size, vector<int>(size, 0));
        }


};


class matrices {
    public:
        int dim;
        int size;
        matrix value1 = matrix(0);
        matrix value2 = matrix(0);
        matrix result = matrix(0);


        matrices(string fileName) {
            ifstream matFile;
            matFile.open(fileName);
            if (!matFile.is_open()){
                cerr << "error opening file" << endl;
            }
            else {
                matFile >> dim;
                if ((dim & (dim-1)) != 0) {
                    size = 1;
                    while(size < dim) {
                        size *= 2;
                    }
                }

                value1.value.resize(size, vector<int>(size, 0));
                value2.value.resize(size, vector<int>(size, 0));
                result.value.resize(size, vector<int>(size, 0));
                

                for(int i = 0; i < dim; i++){
                    for(int j = 0; j < dim; j++){
                        matFile >> value1.value[i][j];
                        
                    }
                }
                for(int i = 0; i < dim; i++){
                    for(int j = 0; j < dim; j++){
                        matFile >> value2.value[i][j];
                        
                    }
                }

                for(int i = 0; i < size; i++){
                    for(int j = dim; j < size; j++){
                        matFile >> value2.value[i][j];
                        
                    }
                }

                matFile.close();
            }


        }

};






int main(){
    matrices m = matrices("input.txt");
    matrix m1 = m.value1;
    matrix m2 = m.value2;
    matrix result = matrix(m.size);
    time_t start, end, diff1, diff2;
    ofstream fout;

    start = clock();
    result = m1.mult(m2, m.size);
    end = clock();
    diff1 = end - start;
    
    fout.open("output_m1.txt");
    if(!fout.is_open()) {
        cerr << "Could not open q1 file." << endl;
    }
    else {
        for(int i = 0; i < m.dim; i++){
            for(int j = 0; j < m.dim; j++){
                fout << result.value[i][j] << " ";  
            }
            fout << endl;
        }
    }
    fout.close();


    start = clock();
    result = m1.stras(m2, m.size);
    end = clock();
    diff2 = end - start;

    fout.open("output_q3.txt");
    if(!fout.is_open()) {
        cerr << "Could not open q3 file." << endl;
    }
    else {
        fout << diff1 << ' ' << diff2;
    }
    fout.close();
    
    fout.open("output_m2.txt");
    if(!fout.is_open()) {
        cerr << "Could not open q2 file." << endl;
    }
    else {
        for(int i = 0; i < m.dim; i++){
            for(int j = 0; j < m.dim; j++){
                fout << result.value[i][j] << " ";  
            }
            fout << endl;
        }
    }
    fout.close();

    return 0;
}







vector<vector<matrix>> matrix::splitMatrix(int size) {
    vector<vector<matrix>> quarterMatrices;

    matrix m11 = matrix(size/2);
    matrix m12 = matrix(size/2);
    matrix m21 = matrix(size/2);
    matrix m22 = matrix(size/2);
                
    for (int i = 0; i < size/2; i++){
        for (int j = 0; j < size/2; j++) {
            m11.value[i][j] = value[i][j];

            m12.value[i][j] = value[i][j+size/2];

            m21.value[i][j] = value[i+size/2][j];

            m22.value[i][j] = value[i+size/2][j+size/2];
        }

    }
    
    quarterMatrices.resize(size, vector<matrix>(2, m11));
    quarterMatrices[0][0] = m11;
    quarterMatrices[0][1] = m12;
    quarterMatrices[1][0] = m21;
    quarterMatrices[1][1] = m22;


    return quarterMatrices;
}

matrix matrix::add(matrix otherMatrix, int size){
    matrix sumMatrix = matrix(size);
    
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            sumMatrix.value[i][j] = value[i][j] + otherMatrix.value[i][j];
        }
    }


    return sumMatrix;
}

matrix matrix::sub(matrix otherMatrix, int size){
    matrix difMatrix = matrix(size);
    
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            difMatrix.value[i][j] = value[i][j] - otherMatrix.value[i][j];
        }
    }


    return difMatrix;
}


matrix matrix::mult(matrix otherMatrix, int size){
    matrix prodMatrix = matrix(size);
    ofstream outFile;
    
    

     if (size == 2) {

        for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++) {
                prodMatrix.value[i][j] = 0;
                    for (int k = 0; k < size; k++) {
                        prodMatrix.value[i][j] += value[i][k] * otherMatrix.value[k][j];
                    }  
            }
        }           
        return prodMatrix;
    }
    else {
                
        vector<vector<matrix>> A = splitMatrix(size);
        vector<vector<matrix>> B = otherMatrix.splitMatrix(size);

        matrix C11 = A[0][0].mult(B[0][0], size/2).add(A[0][1].mult(B[1][0], size/2), size/2);
        matrix C12 = A[0][0].mult(B[0][1], size/2).add(A[0][1].mult(B[1][1], size/2), size/2);
        matrix C21 = A[1][0].mult(B[0][0], size/2).add(A[1][1].mult(B[1][0], size/2), size/2);
        matrix C22 = A[1][0].mult(B[0][1], size/2).add(A[1][1].mult(B[1][1], size/2), size/2);



        for (int i = 0; i < size/2; i++){
            for (int j = 0; j < size/2; j++) {
                prodMatrix.value[i][j] = C11.value[i][j];
                prodMatrix.value[i][j+size/2] = C12.value[i][j];
                prodMatrix.value[i+size/2][j] = C21.value[i][j];
                prodMatrix.value[i+size/2][j+size/2] = C22.value[i][j];
            }
        }

        return prodMatrix;
    }
}
    
    
matrix matrix::stras(matrix otherMatrix, int size) {
matrix prodMatrix = matrix(size);
    ofstream outFile;
    
    

     if (size == 2) {

        for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++) {
                prodMatrix.value[i][j] = 0;
                    for (int k = 0; k < size; k++) {
                        prodMatrix.value[i][j] += value[i][k] * otherMatrix.value[k][j];
                    }  
            }
        }           
        return prodMatrix;
    }
    else {
                
        vector<vector<matrix>> A = splitMatrix(size);
        vector<vector<matrix>> B = otherMatrix.splitMatrix(size);

        matrix M1 = (A[0][0].add(A[1][1], size/2)).stras((B[0][0].add(B[1][1], size/2)), size/2);
        matrix M2 = (A[1][0].add(A[1][1], size/2)).stras((B[0][0]), size/2);
        matrix M3 = (A[0][0]).stras((B[0][1].sub(B[1][1], size/2)), size/2);
        matrix M4 = (A[1][1]).stras((B[1][0].sub(B[0][0], size/2)), size/2);
        matrix M5 = (A[0][0].add(A[0][1], size/2)).stras((B[1][1]), size/2);
        matrix M6 = (A[1][0].sub(A[0][0], size/2)).stras((B[0][0].add(B[0][1], size/2)), size/2);
        matrix M7 = (A[0][1].sub(A[1][1], size/2)).stras((B[1][0].add(B[1][1], size/2)), size/2);


        matrix C11 = M1.add(M4, size/2).sub(M5, size/2).add(M7, size/2);
        matrix C12 = M3.add(M5, size/2);
        matrix C21 = M2.add(M4, size/2);
        matrix C22 = M1.sub(M2, size/2).add(M3, size/2).add(M6, size/2);


        for (int i = 0; i < size/2; i++){
            for (int j = 0; j < size/2; j++) {
                prodMatrix.value[i][j] = C11.value[i][j];
                prodMatrix.value[i][j+size/2] = C12.value[i][j];
                prodMatrix.value[i+size/2][j] = C21.value[i][j];
                prodMatrix.value[i+size/2][j+size/2] = C22.value[i][j];
            }
        }

        return prodMatrix;
    }



} 
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    





