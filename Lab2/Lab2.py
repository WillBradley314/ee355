import numpy as np
import pickle

class Matrix:
    def __init__(self):
        self.value = np.zeros((10,10))
        self.row = 0
        self.max = 0
        self.min = 0


    def matPop(self, fileName):
        file = open(fileName, "r")
        data = file.read()
        list = data.split()
        for i in range(10):
            for j in range(10):
                self.value[i,j] = int(list[j+i*10])  
        file.close()
              

    def linSearch(self):
        self.row = 11
        self.max = 0
        self.min = self.value[0,0]

        for i in range(10):
            for j in range(10):
                if ((self.value[i,j] == self.value[0,0]) and (self.row == 11) and i and j):
                    self.row = i
                if(self.value[i,j] > self.max):
                    self.max = self.value[i,j]
                if(self.value[i,j] < self.min):
                    self.min = self.value[i,j]


    def matAdd(self, otherMatrix):
        sumMatrix = Matrix()

        for i in range(10):
            for j in range(10):
                sumMatrix.value[i,j] = self.value[i,j] + otherMatrix.value[i,j]

        return sumMatrix.value
        

    def matMult(self, differentMatrix):
        prodMatrix = Matrix()
        for i in range(10):
            for j in range(10):
                for k in range(10):
                    prodMatrix.value[i,j] += self.value[i,k] * differentMatrix.value[k,j]

        return prodMatrix.value



def main():

    m1 = "matrix_1.txt"
    m2 = "matrix_2.txt"
    outFile = "output_py.pickle"

    matrix1 = Matrix()
    matrix2 = Matrix()

    matrix1.matPop(m1)
    matrix2.matPop(m2)

    matrix1.linSearch()
    matrix1.linSearch()

    sum = matrix1.matAdd(matrix2)

    prod12 = matrix1.matMult(matrix2)
    prod21 = matrix2.matMult(matrix1)

    data = {'row_m1': matrix1.row,
            'min_m1': matrix1.min,
            'max_m1': matrix1.max,
            'sum': sum,
            'prod_1x2': prod12,
            'prod_2x1': prod21,
    }

    with open(outFile, 'wb') as f:
        pickle.dump(data, f)



if __name__ == "__main__":
    main()