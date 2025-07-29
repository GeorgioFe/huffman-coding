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
    unsigned char byte = input.read_byte();
    vector<int> frequencies(size, 0);

    while (input.good()) {
        frequencies[byte] += 1;
        byte = input.read_byte();
    }

    HCTree ht;
    ht.build(frequencies);

    /*for (int i = 0; i < size; i++) {
        output.write_int(frequencies[i]);
    }*/

    vector<unsigned char> byteVector;
    for (int i = 0; i < size; i++) {
        int val = frequencies[i];
        unsigned char bytes[3];

        bytes[0] = (val >> 16) & 0xFF;
        bytes[1] = (val >> 8) & 0xFF;
        bytes[2] = val & 0xFF;

        byteVector.push_back(bytes[0]);
        byteVector.push_back(bytes[1]);
        byteVector.push_back(bytes[2]);

    }

    for (int i = 0; i < byteVector.size(); i++) {
        output.write_byte(byteVector[i]);
    }

    input.reset();
    byte = input.read_byte();
    while (input.good()) {
        ht.encode(byte, output);
        byte = input.read_byte();
    }

    return 0;
}
