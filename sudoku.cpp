#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "sudoku.h"
using namespace std;

Sudoku::Sudoku() {
    map = vector<vector<int> > (9,vector<int>(9,0));
}

Sudoku::Sudoku(vector<vector<int> > origin_map) {
    map = origin_map;
}

void Sudoku::generate() {
    int origin_map[9][9] = {{8,0,0,0,0,6,2,0,0},
        {0,0,0,8,0,0,6,9,0},
        {7,0,0,1,9,0,0,0,8},
        {0,5,0,0,1,0,4,0,3},
        {1,0,0,0,0,0,0,0,6},
        {4,0,6,0,5,0,0,1,0},
        {5,0,0,0,2,1,0,0,7},
        {0,4,9,0,0,7,0,0,0},
        {0,0,1,9,0,0,0,0,4}
    };
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            map[i][j] = origin_map[i][j];
        }
    }
    srand(time(NULL));
    int swaprow_a = rand() % 3, swaprow_b = rand() % 3;
    swapRow(swaprow_a,swaprow_b);
    int swapcol_a = rand() % 3, swapcol_b = rand() % 3;
    swapNum(swapcol_a,swapcol_b);
    int rotate_n = rand() % 4, flip_n = rand() % 2;
    rotate(rotate_n);
    flip(flip_n);
}

void Sudoku::swapNum(int x, int y) {
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(map[i][j] == y) {
                map[i][j] = x;
            } else if(map[i][j] == x) {
                map[i][j] = y;
            }
        }
    }
}

void Sudoku::swapRow(int x, int y) {
    vector<int> temp(9);
    for(int i = 0; i < 3; i++) {
        temp = map[x*3+i];
        map[x*3+i] = map[y*3+i];
        map[y*3+i] = temp;
    }
}

void Sudoku::swapCol(int x, int y) {
    int temp = 9;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 9; j++) {
            temp = map[j][x*3+i];
            map[j][x*3+i] = map[j][y*3+i];
            map[j][y*3+i] = temp;
        }
    }
}

void Sudoku::rotate(int x) {
    vector<vector<int> > origin_map(9,vector<int>(9,0));
    for(int i = 0; i < x; i++) {
        origin_map = map;
        for(int j = 0; j < 9; j++) {
            for(int k = 0; k < 9; k++) {
                map[k][8-j] = origin_map[j][k];
            }
        }
    }
}

void Sudoku::flip(int x) {
    int temp;
    if(x == 1) {
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 4; j++) {
                temp = map[i][j];
                map[i][j] = map[i][8-j];
                map[i][8-j] = temp;
            }
        }
    } else {
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 4; j++) {
                temp = map[j][i];
                map[j][i] = map[8-j][i];
                map[8-j][i] = temp;
            }
        }
    }
}

void Sudoku::printMap() {
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(j == 8)
                cout << map[i][j] << endl;
            else
                cout << map[i][j] << " ";
        }
    }
}

void Sudoku::build_candidate() {
    const int nine_num[9] = {1,2,3,4,5,6,7,8,9};
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(map[i][j] == 0) {
                cand[i][j].insert(cand[i][j].begin(), nine_num, nine_num+9);
            }
        }
    }
}

void Sudoku::eraseSame(int x, int y, int num) {
    vector<int>::iterator it;
    for(int i = 0; i < 9; i++) {
        if(map[x][i] == 0) {
            it = find(cand[x][i].begin(), cand[x][i].end(), num);
            if(it != cand[x][i].end()) {
                cand[x][i].erase(it);
            }
        }
    }
    for(int i = 0; i < 9; i++) {
        if(map[i][y] == 0) {
            it = find(cand[i][y].begin(), cand[i][y].end(), num);
            if(it != cand[i][y].end()) {
                cand[i][y].erase(it);
            }
        }
    }
    int x_now, y_now;
    int x_base = x/3, y_base = y/3;
    for(int i = 0; i < 3; i++) {
        x_now = x_base*3 + i;
        for(int j = 0; j < 3; j++) {
            y_now = y_base*3 + j;
            if(map[x_now][y_now] == 0) {
                it = find(cand[x_now][y_now].begin(), cand[x_now][y_now].end(), num);
                if(it != cand[x_now][y_now].end()) {
                    cand[x_now][y_now].erase(it);
                }
            }
        }
    }
}

void Sudoku::eraseSameRow(int x, vector<int> y, int num) {
    vector<int>::iterator be_erase, self;
    for(int i = 0; i < 9; i++) {
        self = find(y.begin(), y.end(), i);
        if(self == y.end()) {
            be_erase = find(cand[x][i].begin(), cand[x][i].end(), num);
            if(be_erase != cand[x][i].end())
                cand[x][i].erase(be_erase);
        }
    }
}

void Sudoku::eraseSameCol(vector<int> x, int y, int num) {
    vector<int>::iterator be_erase, self;
    for(int i = 0; i < 9; i++) {
        self = find(x.begin(), x.end(), i);
        if(self == x.end()) {
            be_erase = find(cand[i][y].begin(), cand[i][y].end(), num);
            if(be_erase != cand[i][y].end())
                cand[i][y].erase(be_erase);
        }
    }
}

bool Sudoku::fillRow(int x) {
    vector<int>::iterator it;
    vector<int> can_fill;
    bool have_appear;
    int c;
    for(int j = 1; j < 10; j++) {
        have_appear = false;
        for(int k = 0; k < 9; k++) {
            if(j == map[x][k]) {
                have_appear = true;
                break;
            }
        }
        if(have_appear)
            continue;
        for(int k = 0; k < 9; k++) {
            if(map[x][k] == 0) {
                it = find(cand[x][k].begin(), cand[x][k].end(), j);
                if(it != cand[x][k].end()) {
                    can_fill.push_back(k);
                }
            }
        }
        if(can_fill.size() == 0) {
            return false;
        } else if(can_fill.size() == 1) {
            c = can_fill[0];
            map[x][c] = j;
            cand[x][c].clear();
            zero_cnt--;
            eraseSame(x, c, j);
        }
        can_fill.clear();
    }
    return true;
}

bool Sudoku::fillCol(int y) {
    vector<int>::iterator it;
    vector<int> can_fill;
    bool have_appear;
    int r;
    for(int j = 1; j < 10; j++) {
        have_appear = false;
        for(int k = 0; k < 9; k++) {
            if(j == map[k][y]) {
                have_appear = true;
                break;
            }
        }
        if(have_appear) {
            continue;
        }
        for(int k = 0; k < 9; k++) {
            if(map[k][y] == 0) {
                it = find(cand[k][y].begin(), cand[k][y].end(), j);
                if(it != cand[k][y].end()) {
                    can_fill.push_back(k);
                }
            }
        }
        if(can_fill.size() == 0) {
            return false;
        } else if(can_fill.size() == 1) {
            r = can_fill[0];
            map[r][y] = j;
            cand[r][y].clear();
            zero_cnt--;
            eraseSame(r, y, j);
        }
        can_fill.clear();
    }
    return true;
}

bool Sudoku::fillSubGrid(int x, int y) {
    vector<int>::iterator it;
    vector<int> can_fill[2];
    vector<int> known_index;
    int r, c;
    bool have_appear;
    for(int k = 1; k < 10; k++) {
        have_appear = false;
        for(int m = 0; m < 3; m++) {
            for(int n = 0; n < 3; n++) {
                if(k == map[x*3+m][y*3+n]) {
                    have_appear = true;
                    break;
                }
            }
            if(have_appear) {
                break;
            }
        }
        if(have_appear) {
            continue;
        }
        for(int m = 0; m < 3; m++) {
            for(int n = 0; n < 3; n++) {
                if(map[x*3+m][y*3+n] == 0) {
                    it = find(cand[x*3+m][y*3+n].begin(), cand[x*3+m][y*3+n].end(), k);
                    if(it != cand[x*3+m][y*3+n].end()) {
                        can_fill[0].push_back(m);
                        can_fill[1].push_back(n);
                    }
                }
            }
        }
        if(can_fill[0].size() == 0) {
            return false;
        } else if(can_fill[0].size() == 1) {
            r = can_fill[0][0];
            c = can_fill[1][0];
            map[x*3+r][y*3+c] = k;
            cand[x*3+r][y*3+c].clear();
            zero_cnt--;
            eraseSame(x*3+r, y*3+c, k);
        } else if(can_fill[0].size() == 2) {
            if(can_fill[0][0] == can_fill[0][1]) {
                known_index.push_back(y*3+can_fill[1][0]);
                known_index.push_back(y*3+can_fill[1][1]);
                eraseSameRow(x*3+can_fill[0][0], known_index, k);
            } else if(can_fill[1][0] == can_fill[1][1]) {
                known_index.push_back(x*3+can_fill[0][0]);
                known_index.push_back(x*3+can_fill[0][1]);
                eraseSameCol(known_index, y*3+can_fill[1][0], k);
            }
            known_index.clear();
        } else if(can_fill[0].size() == 3) {
            if(can_fill[0][0] == can_fill[0][1] && can_fill[0][1] == can_fill[0][2]) {
                known_index.push_back(y*3);
                known_index.push_back(y*3+1);
                known_index.push_back(y*3+2);
                eraseSameRow(x*3+can_fill[0][0], known_index, k);
            } else if(can_fill[1][0] == can_fill[1][1] && can_fill[1][1] == can_fill[1][2]) {
                known_index.push_back(x*3);
                known_index.push_back(x*3+1);
                known_index.push_back(x*3+2);
                eraseSameCol(known_index, y*3+can_fill[1][0], k);
            }
            known_index.clear();
        }
        can_fill[0].clear();
        can_fill[1].clear();
    }
    return true;
}

bool Sudoku::fillBlock() {
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(map[i][j] == 0 && cand[i][j].size() == 0) {
                return false;
            } else if(cand[i][j].size() == 1) {
                map[i][j] = cand[i][j][0];
                cand[i][j].clear();
                zero_cnt--;
                eraseSame(i, j, map[i][j]);
            }
        }
    }
    return true;
}

int Sudoku::try_recursive(vector<vector<int> > temp_map,
                          vector<int> temp_cand[9][9], int temp_zero_cnt) {
    int x, y, result;
    bool find_zero = false;
    vector<int> temp_this_cand;
    vector<int> temp2_cand[9][9];
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            temp2_cand[i][j] = temp_cand[i][j];
        }
    }
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(temp_map[i][j] == 0) {
                x = i;
                y = j;
                temp_this_cand = temp_cand[i][j];
                find_zero = true;
                break;
            }
        }
        if(find_zero)
            break;
    }
    if(!find_zero) {
        map = temp_map;
        return 1;
    }
    if(temp_this_cand.size() == 0) {
        return 0;
    }
    int num;
    for(int k = 0; k < temp_this_cand.size(); k++) {
        num = temp_this_cand[k];
        temp_map[x][y] = num;
        temp_cand[x][y].clear();
        temp_zero_cnt--;
        if(temp_zero_cnt == 0) {
            map = temp_map;
            return 1;
        }
        //erase start
        vector<int>::iterator it;
        for(int i = 0; i < 9; i++) {
            if(temp_map[x][i] == 0) {
                it = find(temp_cand[x][i].begin(), temp_cand[x][i].end(), num);
                if(it != temp_cand[x][i].end()) {
                    temp_cand[x][i].erase(it);
                }
            }
        }
        for(int i = 0; i < 9; i++) {
            if(temp_map[i][y] == 0) {
                it = find(temp_cand[i][y].begin(), temp_cand[i][y].end(), num);
                if(it != temp_cand[i][y].end()) {
                    temp_cand[i][y].erase(it);
                }
            }
        }
        int x_now, y_now;
        int x_base = x/3, y_base = y/3;
        for(int i = 0; i < 3; i++) {
            x_now = x_base*3 + i;
            for(int j = 0; j < 3; j++) {
                y_now = y_base*3 + j;
                if(temp_map[x_now][y_now] == 0) {
                    it = find(temp_cand[x_now][y_now].begin(), temp_cand[x_now][y_now].end(), num);
                    if(it != temp_cand[x_now][y_now].end()) {
                        temp_cand[x_now][y_now].erase(it);
                    }
                }
            }
        }
        //erase end
        result = try_recursive(temp_map, temp_cand, temp_zero_cnt);
        if(result == 1) {
            return 1;
        }
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 9; j++) {
                temp_cand[i][j] = temp2_cand[i][j];
            }
        }
        temp_zero_cnt++;
    }
    return 0;
}

bool Sudoku::isMultiAns() {
    zero_cnt = 0;
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(map[i][j] == 0) {
                zero_cnt++;
            }
        }
    }
    if(zero_cnt >= 65) {
        return true;
    } else {
        return false;
    }
}

int Sudoku::solve() {
    if(isMultiAns())
        return 2;

    build_candidate();

    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(map[i][j] != 0) {
                eraseSame(i, j, map[i][j]);
            }
        }
    }

    int old_zero_cnt = zero_cnt;
    while(zero_cnt) {
        for(int i = 0; i < 9; i++) {
            if(!fillRow(i))
                return 0;
        }
        for(int i = 0; i < 9; i++) {
            if(!fillCol(i))
                return 0;
        }
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(!fillSubGrid(i, j))
                    return 0;
            }
        }
        if(!fillBlock())
            return 0;
        if(zero_cnt == 0) {
            return 1;
        } else if(zero_cnt == old_zero_cnt) {
            return try_recursive(map, cand, zero_cnt);
        } else {
            old_zero_cnt = zero_cnt;
        }
    }
}
