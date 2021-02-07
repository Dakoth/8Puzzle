#include <iostream>
#include <string>
#include <queue>
#include <vector> 

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
    int goalState[9] = {1, 2, 3, 4, 5, 6, 7, 8, 0};   //2D representation of the goalState 


};

//class generalSearch (Problem prob) {}




//main program
int main() {
    char user; 
    cout << "Hello and Welcome to Alfredo Gonzalez' 8-puzzle solver " << endl;
    cout << "Type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle." << endl;
    
    //FIXME
    while (user != '1' && user != '2') { 
        cin >> user; 
        if (user == '1' ) { 
            cout << "IMPLEMENT DEFAULT" << endl;
        }
        
        else if (user == '2') {
            cout << "IMPLEMENT OWN PUZZLE" << endl; 
        }
        else {
            cout << "pick a right answer bruh" << endl;
        }
        //user = '';
    }   

    //testing out queues 
    queue<int> testQ;
    testQ.push(5);  
    cout << "the front of the queue is: " << testQ.front() << endl;
    cout << endl;



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

    return 0; 
}