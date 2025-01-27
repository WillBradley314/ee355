import numpy as np
import subprocess

arrs = np.loadtxt("data_table.csv", delimiter=",", dtype=str)
print(arrs)
#print(arrs.shape)

arrs = [i for i in arrs if len(i[0])>0]
#print(arrs)
#print(np.array(arrs).shape)

#=== array preparation ===
#1. Split arrs into two lists (arr1 and arr2), each of them store the numbers of one column in data_table.csv
#2. Convert arr1 and arr2 to strings (don't forget to include square brackets). E.g., arr1 = "[1.3, 2.4, 4.2, 5.0]"

# Please insert your code here
i = 1
arr1num = []
arr2num = []

for i in arrs:
    if (i[0] != 'a'):
        arr1num.append(i[0])
        arr2num.append(i[1])

arr1 = '['
for i in range(0, len(arr1num)):
    arr1 = arr1 + str(arr1num[i])
    if (i < len(arr1num)-1):
        arr1 = arr1 + ', '
arr1 = arr1 + ']'

arr2 = '['
for i in range(0, len(arr2num)):
    arr2 = arr2 + str(arr2num[i])
    if (i < len(arr2num)-1):
        arr2 = arr2 + ', '
arr2 = arr2 + ']'

#print(arr1)
#print(arr2)


#=== call C part === (Please don't modify code below this line)
subprocess.run(["gcc", "part3_calc_cov_and_var.c", "-o", "part3_calc_cov_and_var.out"])
direct_output = subprocess.run(["./part3_calc_cov_and_var.out", arr1, arr2], stdout=subprocess.PIPE)

outprint = str(direct_output.stdout)[2:-3]
print(outprint)
