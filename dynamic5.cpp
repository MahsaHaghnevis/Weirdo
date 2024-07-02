#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <stack>

using namespace std;

bool isNumber(const string& str) {
    for (int t = 0; t < str.size(); t++) {
        if (!isdigit(str[t]))
            return false;
    }
    return true;
}

int max(const int a, const int b) {
    return (a > b) ? a : b;
}

int dynamicProgrammingPath(vector<vector<string>>& matrix) {
    int n = matrix.size();

    vector<vector<int>> dp(n, vector<int>(n, INT_MIN));
    vector<vector<pair<int, int>>> path(n, vector<pair<int, int>>(n, {-1, -1}));

    dp[0][0] = (matrix[0][0] != "X" && isNumber(matrix[0][0])) ? stoi(matrix[0][0]) : 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == "X") continue;

            if (i > 0 && matrix[i-1][j] != "X") {
                int value = (isNumber(matrix[i][j])) ? stoi(matrix[i][j]) : 0;
                int newValue = dp[i-1][j];

                if (matrix[i-1][j] == "!") {
                    if (matrix[i][j] == "!") {
                        newValue = dp[i-1][j]; // two successive rubber cells, don't decrease gold
                    } else if (i < n - 1 && matrix[i+1][j] != "X") {
                        int nextValue = (isNumber(matrix[i+1][j])) ? stoi(matrix[i+1][j]) : 0;
                        newValue = max(dp[i-1][j] - value, dp[i-1][j] + nextValue);
                    } else {
                        newValue = dp[i-1][j] - value;
                    }
                } else {
                    newValue = dp[i-1][j] + value;
                }

                if (newValue > dp[i][j]) {
                    dp[i][j] = newValue;
                    path[i][j] = {i-1, j};
                }
            }

            if (j > 0 && matrix[i][j-1] != "X") {
                int value = (isNumber(matrix[i][j])) ? stoi(matrix[i][j]) : 0;
                int newValue = dp[i][j-1];

                if (matrix[i][j-1] == "!") {
                    if (matrix[i][j] == "!") {
                        newValue = dp[i][j-1]; // two successive rubber cells, don't decrease gold
                    } else if (j < n - 1 && matrix[i][j+1] != "X") {
                        int nextValue = (isNumber(matrix[i][j+1])) ? stoi(matrix[i][j+1]) : 0;
                        newValue = max(dp[i][j-1] - value, dp[i][j-1] + nextValue);
                    } else {
                        newValue = dp[i][j-1] - value;
                    }
                } else {
                    newValue = dp[i][j-1] + value;
                }

                if (newValue > dp[i][j]) {
                    dp[i][j] = newValue;
                    path[i][j] = {i, j-1};
                }
            }

            if (dp[i][j] < 0) dp[i][j] = 0;
        }
    }

    if (dp[n-1][n-1] == 0) {
        cout << "No valid path found or all gold was negated by rubbers." << endl;
        return 0;
    } else {
        stack<pair<int, int>> pathStack;
        int i = n-1, j = n-1;

        while (i != -1 && j != -1) {
            pathStack.push({i, j});
            pair<int, int> next = path[i][j];
            i = next.first;
            j = next.second;
        }

        cout << "Path taken: ";
        while (!pathStack.empty()) {
            pair<int, int> cell = pathStack.top();
            pathStack.pop();
            cout << "(" << cell.first << "," << cell.second << ") ";
        }
        cout << endl;

        return dp[n-1][n-1];
    }
}

int main() {
   // fifth test case
     vector<vector<string> > matrix = {
        {"2", "X", "!", "5", "0"},
        {"1", "9", "!", "X", "3"},
        {"1", "!", "!", "6", "2"},
        {"2", "X", "!", "5", "X"},
        {"8", "4", "2", "!", "!"}};

    cout << "Gold collected by dynamic programming path: " << dynamicProgrammingPath(matrix) << endl;
    return 0;
}


/*

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
*/
