#include<iostream>
#include<vector>
#include "sudoku.h"
using namespace std;

int main() {
    vector<vector<int> > map(9,vector<int>(9,0));
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            cin >> map[i][j];
        }
    }
    Sudoku su(map);
    int operate_type, x, y;
    while(cin >> operate_type && operate_type != 0) {
        switch(operate_type) {
        case 1:
            cin >> x >> y;
            su.swapNum(x, y);
            break;
        case 2:
            cin >> x >> y;
            su.swapRow(x, y);
            break;
        case 3:
            cin >> x >> y;
            su.swapCol(x, y);
            break;
        case 4:
            cin >> x;
            su.rotate(x);
            break;
        case 5:
            cin >> x;
            su.flip(x);
        }
    }
    su.printMap();
    return 0;
}
