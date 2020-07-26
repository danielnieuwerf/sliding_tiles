#include <iostream>
#include <vector>
#include <algorithm>
#include "Board.h"

using namespace std;


int main()
{
    // Initialise board object
    auto board = Board();
    /*
    ALGORITHM
    1. Create two lists, L and Lseen. Initially, L contains only the initial state, and Lseen is empty.

    2. Compare L[0] with the ﬁnal state.
       If they are identical, stop with success.

    3. Apply to L[0] all available search operators, thus obtaining a set of new states.
       Discard those states that already exist in Lseen.
       As for the rest, sort them by the evaluation function and place them at the front of L.
       

    4. Transfer L[0] from L into the list Lseen.

    5. If L is empty stop and report failure. Otherwise, go to 2.
    */

    // ALGORITHM 1. Initialise L and Lseen
    vector<Board> L{}, Lseen{};
    L.push_back(board);     // add initial board to L and leave Lseen empty

    bool done = false;
    bool success = false;

    while (!done) {
        // ALGORITHM 2. Compare L[0] to final state
        if (L[0].distance_from_final_board() == 0) {
            done = true;
            success = true;
        }

        // ALGORITHM 3-5 if not done
        if (!done) {
            // ALGORITHM 3.
            Board current_board = L[0];
            pair<int,int> empty_tile_pos = current_board.index_of_empty_tile();
            // Make a swap in each direction on a copy board if it's not in Lseen and L add it to L

            // East
            if (empty_tile_pos.second != 2) {
                Board new_board = Board(current_board.get_tiles());    // a copy of current board
                pair<int,int> temp = empty_tile_pos;
                temp.second +=1;
                new_board.swap(empty_tile_pos, temp);
                // check if copy is in Lseen and L
                bool in_L = false, in_Lseen = false;
                for (Board b : L) {
                    if (b == new_board) {
                        in_L = true;
                        break;
                    }
                }
                for (Board b : Lseen) {
                    if (b == new_board) {
                        in_Lseen = true;
                        break;
                    }
                }
                // If new_board is not in L and Lseen add to L
                if (!in_Lseen && !in_L) {
                    L.push_back(new_board);
                }
            }
            // West
            if (empty_tile_pos.second != 0) {
                Board new_board = current_board;
                pair<int, int> temp = empty_tile_pos;
                temp.second --;
                new_board.swap(empty_tile_pos, temp);
                // check if copy is in Lseen and L
                bool in_L = false, in_Lseen = false;
                for (Board b : L) {
                    if (b == new_board) {
                        in_L = true;
                        break;
                    }
                }
                for (Board b : Lseen) {
                    if (b == new_board) {
                        in_Lseen = true;
                        break;
                    }
                }
                // If new_board is not in L and Lseen add to L
                if (!in_Lseen && !in_L) {
                    L.push_back(new_board);
                }
            }
            // North
            if (empty_tile_pos.first != 0) {
                Board new_board = current_board;
                pair<int, int> temp = empty_tile_pos;
                temp.first--;
                new_board.swap(empty_tile_pos, temp);
                // check if copy is in Lseen and L
                bool in_L = false, in_Lseen = false;
                for (Board b : L) {
                    if (b == new_board) {
                        in_L = true;
                        break;
                    }
                }
                for (Board b : Lseen) {
                    if (b == new_board) {
                        in_Lseen = true;
                        break;
                    }
                }
                // If new_board is not in L and Lseen add to L
                if (!in_Lseen && !in_L) {
                    L.push_back(new_board);
                }
            }
            // South
            if (empty_tile_pos.first != 2) {
                Board new_board = current_board;
                pair<int, int> temp = empty_tile_pos;
                temp.first++;
                new_board.swap(empty_tile_pos, temp);
                // check if copy is in Lseen and L
                bool in_L = false, in_Lseen = false;
                for (Board b : L) {
                    if (b == new_board) {
                        in_L = true;
                        break;
                    }
                }
                for (Board b : Lseen) {
                    if (b == new_board) {
                        in_Lseen = true;
                        break;
                    }
                }
                // If new_board is not in L and Lseen add to L
                if (!in_Lseen && !in_L) {
                    L.push_back(new_board);
                }
            }


           
            // ALGORITHM 4.
            if(find(Lseen.begin(),Lseen.end(),L[0])==Lseen.end()){  // If L[0] not in Lseen add to Lseen
                Lseen.push_back(L[0]);
            }
            L.erase(L.begin()); // delete first element from L

            unique(L.begin(), L.end(), [](Board& a, Board& b) -> bool {
                return a==b; });   // Remove copies from L

            // Sort L by distance to final board metric smallest first
            sort(L.begin(), L.end(), [](Board& a, Board& b) -> bool {
                return a.distance_from_final_board() < b.distance_from_final_board(); });
            
            // ALGORITHM 5.
            if (L.empty()) {
                // Failure
                done = true;
            }

            // PRINT BOARD test
            else {
                cout << "______________" << endl;
                for (auto b : L) {
                    b.print_board();
                    cout<<b.distance_from_final_board();
                    cout << endl;
                    break;
                }
                cout << "______________" << endl;

            }
        }
    }

    // Print final board
    if (success) {
        cout << endl;
        cout << "The final board is:" << endl;
        L[0].print_board();
    }
    else {
        cout << "Board can't be solved." << endl;
    }
}
