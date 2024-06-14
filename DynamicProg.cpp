#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

void PrintDP(vector <vector <int> >& dp , int size){
    for(int i=0 ; i<size ; i++){
        for(int j=0 ; j<dp[i].size() ; j++){
            if(dp[i][j] ==INT_MIN){
                cout<<"X";
            }
            else
            cout<<dp[i][j]<<" ";
        }
        cout<<endl;
    }
    cout << "------------------" << endl;
}

int DPPathResult(vector <vector <string> >& matrics , int size){
    vector<vector<int> > dp(size, vector<int>(size , INT_MIN));
    if(matrics[0][0] != "X" && matrics[0][0] != "!") 
    dp[0][0]=stoi(matrics[0][0]);
    else
    dp[0][0]=0;

    PrintDP(dp , size);

    for(int i=0 ; i<size ; i++){
        for(int j=0 ; j<size ; j++){
            if(matrics[i][j]=="X")
            continue;
            if (i > 0 && matrics[i-1][j] != "X"){
                if(matrics[i-1][j] != "!"){
                    dp[i][j] = max(dp[i][j], dp[i-1][j] -stoi(matrics[i][j]));
                }
                else
                dp[i][j] = max(dp[i][j], dp[i-1][j]);
            }
            if(j > 0 && matrics[i][j-1] != "X"){
                if(matrics[i][j-1] != "!"){
                    dp[i][j] = max(dp[i][j], dp[i][j-1] -stoi(matrics[i][j]));
                }
                else
                dp[i][j] = max(dp[i][j], dp[i][j-1]);
            }
             PrintDP(dp , size);
            
        }

    }

    return dp[size-1][size-1];

}
int main(){
     vector<vector<string> > matrix(5, vector<string>(5));
    
    matrix[0].push_back("2"); matrix[0].push_back("X"); matrix[0].push_back("!"); matrix[0].push_back("5"); matrix[0].push_back("0");
    matrix[1].push_back("1"); matrix[1].push_back("9"); matrix[1].push_back("!"); matrix[1].push_back("X"); matrix[1].push_back("3");
    matrix[2].push_back("1"); matrix[2].push_back("3"); matrix[2].push_back("1"); matrix[2].push_back("6"); matrix[2].push_back("2");
    matrix[3].push_back("2"); matrix[3].push_back("X"); matrix[3].push_back("5"); matrix[3].push_back("3"); matrix[3].push_back("X");
    matrix[4].push_back("8"); matrix[4].push_back("4"); matrix[4].push_back("2"); matrix[4].push_back("!"); matrix[4].push_back("1");

    cout << "Gold collected by dynamic programming path: " << DPPathResult(matrix , 5) << endl;
    return 0;
}