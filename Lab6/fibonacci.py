import sys
import subprocess

n = sys.argv[1]

subprocess.run(["g++", "fibonacci_dp.cpp", "-o", "fibonacci_dp.out"])
direct_output = subprocess.run(["./fibonacci_dp.out", n], stdout=subprocess.PIPE)

string_Output = direct_output.stdout.decode('utf-8').strip().splitlines()
fStatus = int(string_Output[0])

if (fStatus):
    print("Congratulations! You have the Fibonacci {}".format(n))
else:
    f_next = int(string_Output[1])
    print("Sorry! {} is not a Fibonacci number but the next Fibonacci number to it is {}".format(n, f_next))