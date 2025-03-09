#include <iostream>
#include <fstream>

std::ofstream outFile("output_ToH.txt");
int moveCounter = 0; // Counter for the number of moves

void moveDisk(int n, char from_rod, char to_rod) {
    outFile << "Move disk " << n << " from rod " << from_rod << " to rod " << to_rod << std::endl;
    moveCounter++; // Increment the counter
}

void towerOfHanoi(int n, char from_rod, char to_rod, char aux_rod) {
    // Fill in the code here
    if (n > 1) {
        

        towerOfHanoi(n-1, from_rod, aux_rod, to_rod);
        moveDisk(n, from_rod, to_rod);
        towerOfHanoi(n-1, aux_rod, to_rod, from_rod);


    }
    else {
        moveDisk(1, from_rod, to_rod);
    }
        
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <number_of_disks>" << std::endl;
        return 1;
    }

    int n = std::stoi(argv[1]); // Number of disks
    towerOfHanoi(n, 'A', 'C', 'B'); // A, B and C are names of rods
    outFile << "Total number of moves: " << moveCounter << std::endl; // Output the total number of moves
    outFile.close();
    return 0;
}