#include <vector>
#include <iostream>
#include <string.h>
#include <sstream>

using namespace std;

int nbOfColumns;
int nbOfRows;
bool hardcodeInput = false;

vector<string> lines;


vector<char> findPossibleSol(int i, int j, vector<vector<char>>& vec) {
    vector<bool> res(10);
    for(int k=0; k < nbOfColumns; k++) {
        if(vec[i][k] != '-') {
            res[vec[i][k] - '0'] = true;
        }
    }

    for(int k=0; k < nbOfColumns; k++) {
        if(vec[k][j] != '-') {
            res[vec[k][j] - '0'] = true;
        }
    }

    int quadx = i/3;
    int quady = j/3;

    for(int k=0; k<3; k++) {
        for(int z=0; z<3; z++) {
            int x = k + quadx*3;
            int y = z + quady*3;
            if(vec[x][y] != '-') {
                res[vec[x][y] - '0'] = true;
            }
        }
    }
    vector<char> ans;
    for(i=1; i<10; i++)
        if(!res[i])
            ans.push_back(i);
    return ans;
}

bool findSolution(vector<vector<char>>& vec) {
    int i, j;
    bool finished = false;
    for(i=0; i<nbOfRows && !finished; i++) {
        for(j=0; j<nbOfColumns && !finished; j++) {
            if(vec[i][j] == '-'){
                finished = true;
                break;
            }
        }
        if(finished)
            break;
    }
    if(i == nbOfRows || j == nbOfColumns) {
        return true;
    }
    
    vector<char> pos = findPossibleSol(i, j, vec);
    

    for(char c : pos) {
        vec[i][j] = c + '0';
        if(findSolution(vec)) {
            return true;
        }
        vec[i][j] = '-';
    }
    return false;

}


vector<vector<char>> takeInput() {

    lines.push_back("53--7----");
    lines.push_back("6--195---");
    lines.push_back("-98----6-");
    lines.push_back("8---6---3");
    lines.push_back("4--8-3--1");
    lines.push_back("7---2---6");
    lines.push_back("-6----28-");
    lines.push_back("---419--5");
    lines.push_back("----8--79");


    if(!hardcodeInput) {
        cout << "Input nb of Columns/Rows: ";
        cin >> nbOfColumns;
        nbOfRows = nbOfColumns;
        cout << "Enter one line at a time" << endl;
    }
    string line;
    vector<vector<char>> vec(nbOfRows);
    getline(cin, line);
    for(int j=0; j<nbOfRows; j++) {
        if(!hardcodeInput){
            getline(cin, line);
         }else{
            line = lines[j];
        }
        for(int i=0; i<line.length() && i<nbOfColumns ; i++) {
            if((line[i] < '0' || line[i] > '9') && line[i] != '-') {
                cout << "error with input";
                throw new exception();
            }
            vec[j].push_back(line[i]);
        }
    }
    return vec;
}


void print(vector<vector<char>> vec) {
    for(vector<char> v : vec) {
        for(char c : v) {
            cout << " " << c;
        }
        cout << endl;
    }
}

int main() {

    vector<vector<char>> vec = takeInput();

    if(findSolution(vec)) {
        cout << "found solution" << endl;
    } else {
        cout << "no solution";
    }

    print(vec);
    
}


