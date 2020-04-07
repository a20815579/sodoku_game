#ifndef SUDOKU_H
#define SUDOKU_H
#include <iostream>
#include <vector>
using namespace std;
class Sudoku
{
public:
    Sudoku();
	Sudoku(vector<vector<int> > origin_map);
    // generate
    void generate();

    // transform
    void swapNum(int x, int y);
    void swapRow(int x, int y);
    void swapCol(int x, int y);
    void rotate(int x);
    void flip(int x);

    // solve
    int solve();
    void printMap();
    
    void printdebug();
    
    bool isCorrect();
    
private:
    void build_candidate();
    void eraseSame(int x, int y, int num);
    void eraseSameRow(int x, vector<int> y, int num);
    void eraseSameCol(vector<int> x, int y, int num);
    bool fillRow(int x);
    bool fillCol(int y);
    bool fillSubGrid(int x, int y);
    bool fillBlock();
    bool isNineNumDiff(vector<int> be_checked);
    bool isValid();
    bool isMultiAns();
	    
	vector<vector<int> > map;
	vector<int> cand[9][9];  //candidate number
	int zero_cnt;
	//int is_no_ans = 0;
	//int try_map[9][9];
};

#endif // SUDOKU_H
