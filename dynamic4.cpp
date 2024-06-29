
//The code is a dynamic programming solution to the problem of finding the maximum amount of gold that can be collected from a 2D matrix.
// The matrix is given as input, with each cell containing either a number (representing the amount of gold in that cell) or a special 
//character 'X' (representing a blocked cell) or '!' (representing a rubber cell that negates the gold in the cell). 
//The goal is to find the maximum amount of gold that can be collected by starting from the top-left cell and moving to the bottom-right cell,
// while avoiding blocked cells and taking into account the rubber cells.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <stack>

using namespace std;

bool isNumber(const string& str) {//checking wether is a number or character(containing gold or not)
    for (int t = 0; t < str.size(); t++) {
        if (!isdigit(str[t]))
            return false;
    }
    return true;
}

int max(const int a, const int b) {
    return (a > b) ? a : b;
}

//the recursive relation for completing dp matrics:
//           dp[i][j]=max(value from above , value from left)
//         value from above=dp[i−1][j]+(gold value at cell (i,j))
//         value from left=dp[i][j−1]+(gold value at cell (i,j))


int dynamicProgrammingPath(vector<vector<string> >& matrix) {
    int n = matrix.size();

    vector<vector<int> > dp(n, vector<int>(n, INT_MIN)); //initializing the dp matrics with INT_MIN value

    vector<vector<pair<int, int> > > path(n, vector<pair<int, int> >(n, {-1, -1})); //storing the way we're going
    
    //initializing the first move
    dp[0][0] = (matrix[0][0] != "X" && matrix[0][0] != "!" && isNumber(matrix[0][0])) ? stoi(matrix[0][0]) : 0;


   //iterating in matrics to fill houses

    //checking the house above
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == "X") continue;

            if (i > 0 && matrix[i-1][j] != "X") {
                //initializing the value
                int value = (matrix[i][j] != "!" && isNumber(matrix[i][j])) ? stoi(matrix[i][j]) : 0;
                int newValue;
                
                if (matrix[i][j] == "!" && isNumber(matrix[i-1][j])) {
                    newValue = dp[i-1][j] - stoi(matrix[i-1][j]);   //if there was a rubber decrease the  value
                } else if (matrix[i-1][j] == "!" && isNumber(matrix[i][j])) {
                    newValue = dp[i-1][j] - value;   //if there is a rubber decrese the value
                } else {
                    newValue = dp[i-1][j] + value; //else kepp the value
                }

                if (newValue > dp[i][j]) {   //if the new value is greater than the previous value
                    dp[i][j] = newValue;    //update the value
                    path[i][j] = {i-1, j};  //store the path
                }
            }
            
            //checking the house left
            if (j > 0 && matrix[i][j-1] != "X") { //if the house is blockes stay INT_MIN so we don't pass through
                int value = (matrix[i][j] != "!" && isNumber(matrix[i][j])) ? stoi(matrix[i][j]) : 0;  //initializing the value
                int newValue;

                if (matrix[i][j] == "!" && isNumber(matrix[i][j-1])) {  //if there was a rubber decrease the  value
                    newValue = dp[i][j-1] - stoi(matrix[i][j-1]); 
                } else if (matrix[i][j-1] == "!" && isNumber(matrix[i][j])) { //if there is a rubber decrese the value
                    newValue = dp[i][j-1] - value; 
                } else {
                    newValue = dp[i][j-1] + value; //else kepp the value
                }
               
                if (newValue > dp[i][j]) {
                    dp[i][j] = newValue;
                    path[i][j] = {i, j-1};
                }
            }

            if (dp[i][j] < 0) //if the value is negative make it 0
             dp[i][j] = 0;
        }
    }

    if (dp[n-1][n-1] == 0) { //if the value is 0 then we found no way
        cout << "No valid path found or all gold was negated by robbers." << endl;
        return 0;
    } else {
        stack<pair<int, int> > pathStack;  //if the value is not 0 then we found a way
        int i = n-1, j = n-1;

        while (i != -1 && j != -1) {
            pathStack.push({i, j}); 
            pair<int, int> next = path[i][j];
            i = next.first;
            j = next.second;
        }

        cout << "Path taken: ";
        while (!pathStack.empty()) {   //printing the path
            pair<int, int> cell = pathStack.top();
            pathStack.pop();
            cout << "(" << cell.first << "," << cell.second << ") ";
        }
        cout << endl;

        return dp[n-1][n-1];
    }
}
int main() {
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
        {"2", "X", "!", "5" , "0"},
        {"1", "9", "!", "X" , "3"},
        {"1", "3", "1", "6" , "2"},
        {"2", "X", "5", "3" , "X"},
        {"8", "4", "2", "!" , "1"}
    };

    cout << "Gold collected by dynamic programming path: " << dynamicProgrammingPath(matrix) << endl;
    return 0;
}
