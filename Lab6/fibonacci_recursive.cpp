#include <iostream>


using namespace std;


int f_rec(int n);


int main(int argc, char* argv[]) {
    int input = stoi(argv[1]);
    int f = 0;
    int i = 0;

    while (input > f) {
        f = f_rec(i);
        i++;
    }
    if (input == f) {
        cout << 1 << endl;
    }
    else {
        cout << 0 << endl;
        cout << f << endl;
    }


    return 0;
}



int f_rec(int n) {
    if (n < 2) {
        return n;
    }
    else {
        return (f_rec(n-1) + f_rec(n-2));
    }
    
}
