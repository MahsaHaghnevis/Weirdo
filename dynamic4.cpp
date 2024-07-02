//The algorithm uses dynamic programming to build a 2D matrix to store the maximum amount of gold that can be collected at each cell.
// The algorithm iterates through the matrix, calculating the maximum amount of gold that can be collected at each cell based on the values of the cells above and to the left. The algorithm considers the special cases of rubber cells and blocked cells adjusting the calculations accordingly.
// The algorithm also stores the path taken to reach the maximum amount of gold in a separate 2D matrix.
// After completing the calculations, the algorithm traces back the path taken to reach the maximum amount of gold and prints the path.
//The algorithm has a time complexity of O(n^2) and a space complexity of O(n^2), where n is the size of the input matrix.

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

// The recursive relation for completing dp matrics:
//         dp[i][j]=max(value from above , value from left)
//         value from above=dp[i−1][j]+(gold value at cell (i,j))
//         value from left=dp[i][j−1]+(gold value at cell (i,j))


int dynamicProgrammingPath(vector<vector<string> >& matrix) {
    int n = matrix.size();

    vector<vector<int> > dp(n, vector<int>(n, INT_MIN)); //initializing the dp matrics with INT_MIN value

    vector<vector<pair<int, int> > > path(n, vector<pair<int, int> >(n, {-1, -1})); //storing the way we're going
    
    //initializing the first move
    dp[0][0] = (matrix[0][0] != "X" && matrix[0][0] != "!" && isNumber(matrix[0][0])) ? stoi(matrix[0][0]) : 0;


   //iterating in matrics to fill houses

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == "X") continue;

            if (i > 0 && matrix[i-1][j] != "X") {
                //initializing the value
                int value = (matrix[i][j] != "!" && isNumber(matrix[i][j])) ? stoi(matrix[i][j]) : 0;
                int newValue;
                
                if (matrix[i-1][j] == "!" && isNumber(matrix[i][j])) {
                    newValue = dp[i-1][j] - value;   //if there is a rubber decrese the value
                } else if (matrix[i][j] == "!" )
                    newValue = dp[i-1][j];
                else {
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

                if (matrix[i][j-1] == "!" && isNumber(matrix[i][j])) { //if there is a rubber decrese the value
                    newValue = dp[i][j-1] - value; 
                } else if (matrix[i][j] == "!"){
                    newValue = dp[i][j-1];
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

    // vector<vector<string> > matrix = {
    //     {"2", "X", "!", "5" , "0"},
    //     {"1", "9", "!", "X" , "3"},
    //     {"1", "3", "1", "6" , "2"},
    //     {"2", "X", "5", "3" , "X"},
    //     {"8", "4", "2", "!" , "1"}
    // };

    // second test case
    vector<vector<string> > matrix = {
        {"2", "X", "!", "5", "0"},
        {"1", "9", "!", "X", "3"},
        {"1", "3", "1", "6", "2"},
        {"2", "X", "5", "!", "X"},
        {"8", "4", "2", "!", "1"}
    };

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
    // vector<vector<string> > matrix = {
    //     {"!", "X", "!", "!", "!"},
    //     {"!", "!", "!", "X", "!"},
    //     {"!", "!", "!", "!", "!"},
    //     {"!", "X", "!", "!", "X"},
    //     {"!", "!", "!", "!", "!"}};

    cout << "Gold collected by dynamic programming path: " << dynamicProgrammingPath(matrix) << endl;
    return 0;
}
