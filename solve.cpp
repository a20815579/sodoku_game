#include<iostream>
#include<vector>
#include <algorithm>
#include "sudoku.h"
using namespace std;

int main()
{
    vector<vector<int> > map(9 ,vector<int>(9,0));
	for(int i = 0; i < 9; i++) {
		for(int j = 0; j < 9; j++) {
			cin >> map[i][j];
		}
	}
    Sudoku su(map);
	int result = su.solve();
	//su.printdebug();
	cout << result << endl;
	if(result == 1) {
		su.printMap();
	}
	
    return 0;
}
