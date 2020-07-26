#pragma once
#include <vector>
#include <iostream>
#include <string>
using namespace std;

class Board {
private:
	vector<vector<int>> tiles;
public:
	// Constructors
	Board() {
		vector<int> row(3, 1);
		row[0] = 1;
		row[1] = 2;
		row[2] = 3;
		tiles.push_back(row);
		row[0] = 7;
		row[1] = 8;
		row[2] = 4;
		tiles.push_back(row);
		row[0] = -1;
		row[1] = 6;
		row[2] = 5;
		tiles.push_back(row);
	}
	Board(vector<vector<int>> t) {
		tiles = t;
	}

	bool operator==(const Board& b) {
		return this->get_tiles() == b.tiles;
	}
	void operator=(const Board& b) {
		tiles = b.tiles;
	}
	// Utilities
	pair<int, int> index_of_empty_tile() {
		// returns pair row,index of empty tile (-1 tile)
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				if (tiles[i][j] == -1)
					return make_pair(i, j);
		// Shouldn't reach here
		return make_pair(-1, -1);
	}
	void swap(pair<int, int> x, pair<int, int> y) {
		// Swaps position x (row,col) with y (row,col)
		int temp = tiles[x.first][x.second];
		tiles[x.first][x.second] = tiles[y.first][y.second];
		tiles[y.first][y.second] = temp;
	}
	int distance_from_final_board() {
		int total{};
		// find row and column of each number i from 1 to 8 
		for (int i = 1; i < 9; ++i) {
			for (int row = 0; row < 3; ++row)
				for (int col = 0; col < 3; ++col) {
					if (tiles[row][col] == i) {
						// the final position of i is row2,col2
						int row2{}, col2{};
						if (i < 4) {
							row2 = 0;
							col2 = i - 1;
						}
						else if (i == 4) {
							row2 = 1;
							col2 = 2;
						}
						else if (i < 8) {
							row2 = 2;
							col2 = 7 - i;
						}
						else if (i == 8) {
							row2 = 1;
							col2 = 0;
						}

						// Add distance to total
						total += abs(row2 - row);
						total += abs(col2 - col);

					}
				}


		}

		return total;
	}
	void print_board() {
		// Print blank space where -1 and otherwise print the number
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				tiles[i][j] == -1 ?
					cout << "|" << " " << "| " :
					cout << "|" << tiles[i][j] << "| ";
			}
			cout << endl;
		}
	}
	bool is_final_board() {
		return tiles[0][0] == 1 && tiles[0][1] == 2 && tiles[0][2] == 3 &&
			tiles[1][2] == 4 && tiles[2][2] == 5 && tiles[2][1] == 6 &&
			tiles[2][0] == 7 && tiles[1][0] == 8 && tiles[1][1] == -1;

	}
	vector<vector<int>> get_tiles(){
		return tiles;
	}

};