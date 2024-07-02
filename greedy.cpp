// The GreedyPath function navigates through a 2D grid (mapMatrics)
// to collect the maximum possible gold while avoiding obstacles.
// It uses a greedy algorithm to decide the next move based on the
// highest gold value available in the adjacent cells (right and down).

// The time complexity of the GreedyPath function is O(n^2)
// This is because the function iterates through each cell in the grid once to calculate the total gold collected.
// The space complexity of the function is O(n) where n is the size of the grid.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Cell struct to store the cell's position, gold value, and the direction of the move
struct Cell
{
    int x, y;
    int GoldBag;
    char cellPos;
};

// compare function to sort the cells based on the gold value
bool compareCell(const Cell &a, const Cell &b)
{
    return a.GoldBag > b.GoldBag;
}

// check if the next cell is a number or not
bool isNumber(const string &str)
{
    for (int t = 0; t < str.size(); ++t)
        if (!isdigit(str[t]))
            return false;
    return true;
}


void GreedyPath(vector<vector<string> > &mapMatrix, int size)
{
    int i = 0, j = 0; // to store the current position
    int GoldBag = 0; // to store the gold value
    bool PreviousHadRubber = false; // to check if the previous cell was rubber
    vector<char> path; // to store the path
    if (mapMatrix[0][0] == "X")
    { // in case the starting house is blocked
        cout << "Impossible to move." << endl;
        return;
    }

    while (i < size || j < size) // while it didn't hit the wall
    { 
        if (isNumber(mapMatrix[i][j]))
        {
            if (PreviousHadRubber)
                // If we have rubber with us, we lose the gold
                GoldBag -= stoi(mapMatrix[i][j]);
            else
                GoldBag += stoi(mapMatrix[i][j]);
            PreviousHadRubber = false;
        }
        else if (mapMatrix[i][j] == "!")
        {
            if (PreviousHadRubber)
                // If we encounter two consecutive rubber cells, don't subtract anything
                PreviousHadRubber = false;
            else
                PreviousHadRubber = true; // Mark that we've encountered a rubber cell
        }

        vector<Cell> Candidates; // valid surrounding houses (right and down houses)

        // Checking the down cell
        if (i < size - 1 && mapMatrix[i + 1][j] != "X")
        {
            int GoldVal = 0;
            if (isNumber(mapMatrix[i + 1][j]))
            { // getting the gold value if available
                GoldVal = stoi(mapMatrix[i + 1][j]);
                if (PreviousHadRubber) // if we have rubber in our current position, we will lose the gold
                    GoldVal = -GoldVal;
            }
            Cell NewCell;
            NewCell.x = i + 1;
            NewCell.y = j;
            NewCell.cellPos = 'd';
            NewCell.GoldBag = GoldVal;
            Candidates.push_back(NewCell);
        }

        // Checking the right cell
        if (j < size - 1 && mapMatrix[i][j + 1] != "X")
        {
            int GoldVal = 0;
            if (isNumber(mapMatrix[i][j + 1]))
            { // getting the gold value if available
                GoldVal = stoi(mapMatrix[i][j + 1]);
                if (PreviousHadRubber)
                    GoldVal = -GoldVal; // if we have rubber in our current position, we will lose the gold
            }
            Cell NewCell;
            NewCell.x = i;
            NewCell.y = j + 1;
            NewCell.cellPos = 'r';
            NewCell.GoldBag = GoldVal;
            Candidates.push_back(NewCell);
        }

        // if no valid moves, break the loop
        if (Candidates.empty())
            break;

        // sort candidates based on the max gold value
        sort(Candidates.begin(), Candidates.end(), compareCell);

        // choose the best option with the most gold value and move to it
        i = Candidates[0].x;
        j = Candidates[0].y;
        path.push_back(Candidates[0].cellPos);
        Candidates.clear();

    }
    if (i == size - 1 && j == size - 1)
        // if we reached the end
        cout << "Gold collected by greedy path: " << GoldBag << endl;
    else
    {
        // if we can't reach the end
        cout << "Impossible to move to the end" << endl
             << "Gold collected by greedy path: " << GoldBag << endl;
    }
    if (!path.empty())
    {
        cout << "Path: ";
        for (int t = 0; t < path.size(); ++t)
            cout << path[t] << ' ';
        cout << endl;
    }
}

int main()
{
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


    // first test case 
    // vector<vector<string> > matrix = {
    //     {"2", "X", "!", "5", "0"},
    //     {"1", "9", "!", "X", "3"},
    //     {"1", "3", "1", "6", "2"},
    //     {"2", "X", "5", "3", "X"},
    //     {"8", "4", "2", "!", "1"}
    // };

    // second test case
    // vector<vector<string> > matrix = {
    //     {"2", "X", "!", "5", "0"},
    //     {"1", "9", "!", "X", "3"},
    //     {"1", "3", "1", "6", "2"},
    //     {"2", "X", "5", "!", "X"},
    //     {"8", "4", "2", "!", "1"}
    // };

    // third test case
    // vector<vector<string> > matrix = {
    //     {"2", "X", "!", "5", "0"},
    //     {"1", "9", "!", "X", "3"},
    //     {"1", "3", "!", "6", "2"},
    //     {"2", "X", "!", "!", "X"},
    //     {"8", "4", "2", "!", "1"}
    // };

    // fourth test case
    // vector<vector<string> > matrix = {
    //     {"2", "X", "!", "5", "0"},
    //     {"1", "9", "!", "X", "3"},
    //     {"1", "3", "!", "6", "2"},
    //     {"2", "X", "!", "!", "X"},
    //     {"8", "4", "2", "!", "!"}};

    // fifth test case
    // vector<vector<string> > matrix = {
    //     {"2", "X", "!", "5", "0"},
    //     {"1", "9", "!", "X", "3"},
    //     {"1", "!", "!", "6", "2"},
    //     {"2", "X", "!", "5", "X"},
    //     {"8", "4", "2", "!", "!"}};

    // sixth test case, all cells are rubbers
    vector<vector<string> > matrix = {
        {"!", "X", "!", "!", "!"},
        {"!", "!", "!", "X", "!"},
        {"!", "!", "!", "!", "!"},
        {"!", "X", "!", "!", "X"},
        {"!", "!", "!", "!", "!"}};


    GreedyPath(matrix, 5);

    return 0;
}