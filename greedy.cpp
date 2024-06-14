//The GreedyPath function navigates through a 2D grid (mapMatrics)
// to collect the maximum possible gold while avoiding obstacles.
// It uses a greedy algorithm to decide the next move based on the 
//highest gold value available in the adjacent cells (right and down).

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Cell{
   int x , y;
   int GoldBag;
};

bool compareCell(const Cell& a, const Cell& b){
    return a.GoldBag > b.GoldBag;
}

bool isNumber(const string& str){
    for(int i=0 ; i<str.length() ;i++){
        if(!isdigit(str[i]))
        return false;
        else
        return true;
    }
}

int GreedyPath(vector <vector <string> >& mapMatrics , int size){
    int i=0;
    int j=0;
    int GoldBag=0;
    bool PreviousHadRubber=false;
    while (i<size-1 || j<size-1 )//while it didn't hit the wall
    {
        if(isNumber(mapMatrics[i][j])){
            PreviousHadRubber=false;
            GoldBag+=stoi(mapMatrics[i][j]);
        }
        else if(mapMatrics[i][j]=="!"){
            PreviousHadRubber=true;  // and also check the house we are in has rubber
        }

        vector <Cell> Candidates ; //houses of sourrounding that gives feasible ans (right and down houses)
        if(i<size-1 && mapMatrics[i+1][j]!="X"){
            int GoldVal=0;
            if(isNumber(mapMatrics[i+1][j])){  //putting the right one if availabe
                GoldVal=stoi(mapMatrics[i+1][j]);
                if(PreviousHadRubber){
                    GoldVal=-GoldVal; // so in this case we lose the money but we handle it in sorting
                } 
            }
            Candidates.push_back({i+1,j,GoldVal});
        }
        else if(j<size-1 && mapMatrics[i][j+1]!="X"){
            int GoldVal=0;
            if(isNumber(mapMatrics[i][j+1])){  //putting the down one if availabe
                GoldVal=stoi(mapMatrics[i][j+1]);
                if(PreviousHadRubber){
                    GoldVal=-GoldVal; // so in this case we lose the money but we handle it in sorting
                } 
            }
            Candidates.push_back({i,j+1,GoldVal});
        }
        //but if we can't move break loop
        if(Candidates.empty()==true)
        break;

        //now we sort them based on the max gold value
        sort(Candidates.begin()  , Candidates.end() , compareCell);

        //here choose the best option with the most vgold value and move to it
        i=Candidates[0].x;
        j=Candidates[0].y;
        //now also handle losing the gold of this house
        if(mapMatrics[i][j]=="!"){
             GoldBag -= PreviousHadRubber ? 0 : (isNumber(mapMatrics[i][j]) ? stoi(mapMatrics[i][j]) : 0);
        }
    }
    //now add the value of new house
    if(isNumber(mapMatrics[i][j])){
        GoldBag+=stoi(mapMatrics[i][j]);
    }

    return GoldBag;
}


    

int main(){
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