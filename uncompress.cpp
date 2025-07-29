#include<iostream>
#include "HCTree.hpp"
#define UNICHAR 256;
using namespace std;

int main(int argc, char* argv[]) {
    FancyInputStream input(argv[1]);
    FancyOutputStream output(argv[2]);

    if (argc != 3) {
        error("Check arguments!\n");
    }
    else if (!(input.good())) {
        error("No input file with this name");
    }

    if (input.filesize() == 0) {
        return 0;
    }

    int size = UNICHAR;
    vector<int> frequencies(size, 0);
    vector<unsigned char> byteVector(768);

    for (int i = 0; i < 768; i++) {
        byteVector[i] = input.read_byte();
    }

    int j = 0;
    for (int i = 0; i < 768; i += 3) {
        int val = ((byteVector[i] & 0xFF) << 16) | ((byteVector[i+1] & 0xFF) << 8) | ((byteVector[i+2]) & 0xFF);
        frequencies[j] = val;
        j++;
    }

    /*for (int i = 0; i < size; i++) {
        frequencies[i] = input.read_int();
    }*/

    HCTree ht;
    ht.build(frequencies);
    unsigned char symbol;
    

    while (true) {
        symbol = ht.decode(input);
        if (!(input.good())) {
            break;
        }
        output.write_byte(symbol);
    }

    return 0;
}
