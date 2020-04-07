#include<iostream>
#include<vector>
#include "sudoku.h"
using namespace std;

int main() {
    Sudoku su;
    su.generate();
    su.printMap();
    return 0;
}
