
//The GreedyPath function navigates through a 2D grid (mapMatrics)
// to collect the maximum possible gold while avoiding obstacles.
// It uses a greedy algorithm to decide the next move based on the
// highest gold value available in the adjacent cells (right and down).
// The function returns the total gold collected by the end of the path.


// The time complexity of the GreedyPath function is O(n^2)
// This is because the function iterates through each cell in the grid once to calculate the total gold collected.
// The space complexity of the function is O(1), 


#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Cell {
    int x, y;
    int GoldBag;
};

bool compareCell(const Cell& a, const Cell& b) {
    return a.GoldBag > b.GoldBag;
}

bool isNumber(const string& str) {
    for (int t = 0; t < str.size(); ++t){
        if (!isdigit(str[t])) {
            return false;
        }
    }
    return true;
}



int GreedyPath(vector<vector<string> >& mapMatrix, int size) {
    int i = 0, j = 0;
    int GoldBag = 0;
    bool PreviousHadRubber = false;

    if (mapMatrix[0][0] == "X") { // in case the starting house is blocked
        cout << "Moving impossible" << endl;
        return 0;
    }

    while (i < size - 1 || j < size - 1) { // while it didn't hit the wall
        if (isNumber(mapMatrix[i][j])) {
            if (PreviousHadRubber) {
                GoldBag -= stoi(mapMatrix[i][j]);
            } else {
                GoldBag += stoi(mapMatrix[i][j]);
            }
            PreviousHadRubber = false;
        } else if (mapMatrix[i][j] == "!") {
            if (PreviousHadRubber) {
                // If we encounter two consecutive rubber cells, don't subtract anything
                PreviousHadRubber = true;
            } else {
                PreviousHadRubber = true; // Mark that we've encountered a rubber cell
            }
        }

        vector<Cell> Candidates; // valid surrounding houses (right and down houses)

        // Checking the down cell
        if (i < size - 1 && mapMatrix[i + 1][j] != "X") {
            int GoldVal = 0;
            if (isNumber(mapMatrix[i + 1][j])) { // getting the gold value if available
                GoldVal = stoi(mapMatrix[i + 1][j]);
                if (PreviousHadRubber) { // if we have rubber, we lose the gold
                    GoldVal = -GoldVal;
                }
            }
            Cell NewCell;
            NewCell.x=i+1;
            NewCell.y=j;
            NewCell.GoldBag=GoldVal;
            Candidates.push_back(NewCell);
        }

        // Checking the right cell
        if (j < size - 1 && mapMatrix[i][j + 1] != "X") {
            int GoldVal = 0;
            if (isNumber(mapMatrix[i][j + 1])) { // getting the gold value if available
                GoldVal = stoi(mapMatrix[i][j + 1]);
                if (PreviousHadRubber) {
                    GoldVal = -GoldVal; // lose the gold if we have rubber
                }
            }
            Cell NewCell;
            NewCell.x=i;
            NewCell.y=j+1;
            NewCell.GoldBag=GoldVal;
            Candidates.push_back(NewCell);
        }

        // if no valid moves, break the loop
        if (Candidates.empty()) {
            break;
        }

        // sort candidates based on the max gold value
        sort(Candidates.begin(), Candidates.end(), compareCell);

        // choose the best option with the most gold value and move to it
        i = Candidates[0].x;
        j = Candidates[0].y;

        // if moving to a rubber cell, mark it and subtract the gold of the previous house if not a rubber
        if (mapMatrix[i][j] == "!" && !PreviousHadRubber) {
            if (isNumber(mapMatrix[i][j])) {
                GoldBag -= stoi(mapMatrix[i][j]);
            }
            PreviousHadRubber = true;
        } else {
            PreviousHadRubber = false;
        }
    }

    // add the value of the last house
    if (isNumber(mapMatrix[i][j])) {
        GoldBag += stoi(mapMatrix[i][j]);
    }

    return GoldBag;
}

    

int main(){
    /*
    int size;
    cout<<"Enter the size of the matrix: "<<endl;
    cin>>size;

    vector<vector<string> > matrix ;
    for(size_t i=0 ; i<size ; i++){
        vector<string> row;
        for(size_t j=0 ; j<size ; j++){
            string value;
            cout<<"Enter the value of the cell: "<<endl;
            cin>>value;
            row.push_back(value);
        }
        matrix.push_back(row);
    }
    */
    vector<vector<string> > matrix = {
        {"2", "X", "!", "5", "0"},
        {"1", "9", "!", "X", "3"},
        {"1", "3", "1", "6", "2"},
        {"2", "X", "5", "3", "X"},
        {"8", "4", "2", "!", "1"}
    };


    cout << "Gold collected by greedy path: " << GreedyPath(matrix , 5) << endl;

    return 0;
}