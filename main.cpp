#include <iostream>
#include <string>
#include <queue>
#include <vector> 

#include <sstream>

using namespace std;

int numOfNodes = 0; //global variable to count number of nodes
int maxNumInQueue = 0; //Max number of nodes in a queue. 

class Node {
    private: 
        int depth; //depth of a node 
        int gn; 
        int hn;   
    //Node* left;
    //Node* right; 
    public:
        int get_gn() { return this->gn; };
        int get_hn() { return this-> hn; };
    
    //vector<Node*>child; 
};


class Problem {
    vector<int> goalState = {1, 2, 3, 4, 5, 6, 7, 8, 0};   //2D representation of the goalState 


};

//class generalSearch (Problem prob) {}




//main program
int main() {
    char user = '\0';
    string userPuzzle = "";  
    string userPuzzleConcat = "";
    //int problem[9] = {}; //Initalize an empty problem 
    vector<int> problem;

    //int defaultProb[9] = {1, 2, 3, 4, 8, 0, 7, 6, 5};
    vector<int> defaultProb = {1, 2, 3, 4, 8, 0, 7, 6, 5};

    cout << "Hello and Welcome to Alfredo Gonzalez' 8-puzzle solver " << endl;
    cout << "Type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle." << endl;
    
    //Puzzle choices
    while (user != '1' && user != '2') { 
        cin >> user; 
        cin.ignore(); 

        if (user == '1' ) { //default puzzle 
            problem = defaultProb;
        }
        else if (user == '2') { //If not the default
            cout << "Enter your puzzle, use a zero to represent the blank" << endl;
            cout << "Enter the first row, use space or tabs between numbers" << endl; 

            getline(cin, userPuzzle);
            userPuzzleConcat += userPuzzle + " ";
            //cout << userPuzzleConcat << endl;// test

            cout << "Enter the second row, use space or tabs between numbers" << endl;
            getline(cin, userPuzzle);
            userPuzzleConcat += userPuzzle + " ";
            //cout << userPuzzleConcat << endl;// test

            cout << "Enter the third row, use space or tabs between numbers" << endl;
            getline(cin, userPuzzle);
            userPuzzleConcat += userPuzzle;

            //testing putting the streamstring in thingy 
            stringstream ss(userPuzzleConcat);
            int n;
            char ch;
            
            while(ss >>n ){
                problem.push_back(n);
            }
            ss.clear();
        }
        else {
            cout << "Plese pick a valid input " << endl;
        }
    }   

     //tests if the array was added 
    for(int i = 0; i < problem.size(); i++){ 
         cout << problem.at(i) << " ";
    }
    //testing out queues 
    /*
    queue<int> testQ;
    testQ.push(5);  
    cout << "the front of the queue is: " << testQ.front() << endl;
    cout << endl;
    */

   
    //Testing out 2d arrays, maybe could use this for mismatched heuristic 
    char goalState[3][3] = {{'1', '2', '3'},
                            {'4', '5', '6'},
                            {'7', '8', '0'}};

/*
    char testPuzzle[3][3] = {{'2', '3', '4'},
                            {'1', '5', '6'},
                            {'7', '0', '8'}};    
*/
    char testPuzzle[3][3] = {{'1', '2', '3'},
                            {'4', '5', '6'},
                            {'7', '0', '8'}}; 


    int mismatches = 0; 
    /*
    //can make the '3' just an n value
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {

            if (testPuzzle[i][j] == '0') {                              //|| (goalState[i][j] != '0')} 
                   //if the empty character is selected, don't count it 
            }
            else if (testPuzzle[i][j] != goalState[i][j] ) { //else If there is a mismatch, count it  
                mismatches++; 
            }  
        }
    }            
    cout << "The number of mismatches is: " << mismatches << endl;        
    */
    return 0; 
}