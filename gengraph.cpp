#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

int main() {
    std::ofstream graphfile("graphoutput.txt");
    int graphsize;
    int graphlowerbound;
    int graphupperbound;

    //std::cout << "size of graph?: ";
    //std::cin >> graphsize;
    graphsize = 10000;
    //std::cout << "lower bound of generated numbers (inclusive)?: ";
    //std::cin >> graphlowerbound;
    graphlowerbound = 0;
    //std::cout << "upper bound of generated numbers (inclusive)?: ";
    //std::cin >> graphupperbound;
    graphupperbound = 100000;

    // Initialize random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (int i = 0; i < graphsize; ++i) {
        std::string distlist;
        for (int i2 = 0; i2 < i; ++i2) {
            distlist += std::to_string(rand() % (graphupperbound - graphlowerbound + 1) + graphlowerbound) + " ";
        }
        distlist += "0\n";
        //std::cout << distlist;
        graphfile << distlist;
    }

    graphfile.close();
    return 0;
}
