#include <iostream>
#include <string>
#include <queue>
#include <vector> 
#include <sstream>

using namespace std;

int numOfNodes = 0; //global variable to count number of nodes
int maxNumInQueue = 0; //Max number of nodes in a queue. 


///////////////////////////////////////////////////
//NODE CLASSES

/* Orignal Node class
class Node {
    public: 
        int depth; //depth of a node 
        int gn; 
        int hn;   
    
        //Node* child;
        //Node* ; 
        
        //Methods
        
        void set_gn(int gn_) { this->gn = gn_;};
        int get_gn() { return this->gn; };

        void set_hn(int hn_) { this->hn = hn_;};
        int get_hn() { return this-> hn; };

        void set_depth(int depth_) {this->depth = depth_;};
        int get_depth() { return this-> depth; };
        
        //vector<Node*>child; 
        //COnstructors
        Node() { this->depth = 0; this->gn = 0; this->hn = 0; }; //default constructor
        Node(int depth, int gn, int hn) {this->depth = depth; this->gn = gn; this->hn = hn; } //other constructor
};
*/

class Problem {
    private:
        //Node* root = nullptr; //root pointer to root      TESTING OUT NOT HAVING A ROOT CLASS 


        //vector<int> inputPuzzle;

    public:
        //Data 
        vector<int> goalState = {1, 2, 3, 4, 5, 6, 7, 8, 0};   //2D representation of the goalState 
        vector<int> inputPuzzle;

        int depth;      //depth of a node / ALSO G(N)  
        //int gn;         //general cost, generally increases as more nodes are added
        int hn;         //heuristic cost, depends on the type of heuristic used 

        //Methods
        void setPuzzle(vector<int> puz) {this->inputPuzzle = puz;}; 


        //Adds all possible operators to the priority queue based off of their costs 
        void operators(Problem& prob){

            return;
        }


        //Actually moving them 
        void moveUp(Problem& prob) {
                return;
        }

        void moveDown(Problem& prob) {
                return;
        }

        void moveLeft(Problem& prob) {
                return;
        }

        void moveRight(Problem& prob) {
                return;
        }



        //returns index for blank character
        int getBlankIndex(Problem& prob) {
            int index;
            for (int i = 0; i < prob.inputPuzzle.size(); i++) {
                if (prob.inputPuzzle.at(i) == 0) {
                    index = prob.inputPuzzle.at(i);
                }
            }
            return index; 
        }


        //Test's if this problem is the goal state
        bool goalTest() {  //orignally Problem& prob)
            //bool test; //Assume true

            for (int i = 0; i < inputPuzzle.size(); i++) {
                if (inputPuzzle.at(i) != goalState.at(i)) {        //If any element does not equal the goal state, then false
                    return false;
                }
            }
            return true;    //Means that this puzzle is the goal state, return true
        }


        //originally had this outside 
        void printResults () {
            cout << endl;
            cout << inputPuzzle.at(0) << " " << inputPuzzle.at(1) << " " << inputPuzzle.at(2) << endl;
            cout << inputPuzzle.at(3) << " " << inputPuzzle.at(4) << " " << inputPuzzle.at(5) << endl;
            cout << inputPuzzle.at(6) << " " << inputPuzzle.at(7) << " " << inputPuzzle.at(8) << endl;
            return;
        }


        //Constructors    // might need more constructors 
        Problem(vector<int> inputPuzzle) { //NOT SURE IF THIS IS CORRECT FOR WHAT I WANNA DO        
            this->inputPuzzle = inputPuzzle;
            
        }
        Problem (vector<int> inPuzz, int d, int hn_) { //
            this->inputPuzzle = inPuzz;
            this->depth = d;
            this->hn = hn_;
        }

        Problem() {};

};


//PRIORITY QUEUE STUFF /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class minHeapComp {
    public: 
        int operator() (const Problem& p1, const Problem& p2 ) {
            return (p1.depth + p1.hn) > (p2.depth + p2.hn); //empty for now
        }
};

priority_queue< Problem, vector<Problem>, minHeapComp > PriorityQ;   //Generates a min heap 


////////////////////////////////////////////////////////////////////////////////////////////////

//Fix later
void generalSearch (Problem& p) {


return; 


}



/* Helper function (PUT THIS INSIDE THE PROBLEM CLASS)
        void printResults (Problem& p) {
            cout << endl;
            cout << p.inputPuzzle.at(0) << " " << p.inputPuzzle.at(1) << " " << p.inputPuzzle.at(2) << endl;
            cout << p.inputPuzzle.at(3) << " " << p.inputPuzzle.at(4) << " " << p.inputPuzzle.at(5) << endl;
            cout << p.inputPuzzle.at(6) << " " << p.inputPuzzle.at(7) << " " << p.inputPuzzle.at(8) << endl;
            return;
        }
*/


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//main program
int main() {
    char user = '\0';
    string userPuzzle = "";  
    string userPuzzleConcat = "";
    //int problem[9] = {}; //Initalize an empty problem 

    vector<int> problem;
    vector<int> defaultProb = {1, 2, 3, 4, 8, 0, 7, 6, 5};


    //testing out problem object
    Problem prob;   //initalizes a problem 
    //prob.setPuzzle(defaultProb);



    cout << "Hello and Welcome to Alfredo Gonzalez' 8-puzzle solver " << endl;
    cout << "Type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle." << endl;
    
    //Puzzle choices
    while (user != '1' && user != '2') { 
        cin >> user; 
        cin.ignore(); 

        if (user == '1' ) { //default puzzle 
            problem = defaultProb;
            //prob.setPuzzle(problem); //sets the inital problem puzzle to be the input
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

    //TESTING FUNCTIONS
    prob.setPuzzle(problem); //sets the inital problem puzzle to be the input
    cout << "TEST PRINT OF PROBLEM" << endl;
    prob.printResults();
    cout << endl;

    cout << "The result of checking if this is the goal state is: " << prob.goalTest() << endl;


    //Testing out the priority queue of problems 
    vector<int> p2 = {1, 2, 3, 4, 0, 8, 7, 6, 5};
    vector<int> p3 = {1, 2, 3, 4, 0, 8, 7, 6, 5};
    Problem prob2(p2, 0, 2);
    Problem prob3(p3, 1, 4);

    PriorityQ.push(prob);
    PriorityQ.push(prob2);
    PriorityQ.push(prob3);
    

    Problem temp = PriorityQ.top();
    temp.printResults();
    PriorityQ.pop();
    cout << endl;
    
    temp = PriorityQ.top();
    temp.printResults();
    PriorityQ.pop();

    cout << endl;
    temp = PriorityQ.top();
    temp.printResults();
    PriorityQ.pop();



    cout << "END OF TESTING" << endl;
    //PriorityQ.push()









    //Second part 
    user = '\0';
    cout << "Enter your choice of algorithm" << endl;
    cout << "1. Uniform Cost Search" << endl;
    cout << "2. A* with the Misplaced Tile heuristic" << endl;
    cout << "3. A* with the Manhattan Distance heuristic" << endl;
 
    while (user != '1' && user != '2' && user != '3') { 
        cin >> user; 
        cin.ignore(); 

        if (user == '1' ) { //h(n) = 0
            cout << "UNIFORM COST SEARCH" << endl;
        }
        else if (user == '2') {
             cout << "MISPLACED TILE" << endl;
        }
        else if (user == '3') {
            cout << "MANHATTAN DISTANCE" << endl;
        }
        else {
            cout << "Please pick a valid input" << endl;
        }

    }    



    //tests if the array was added 
    /*
    for(int i = 0; i < problem.size(); i++){ 
         cout << problem.at(i) << " ";
    }
    */
    //testing out queues 
    /*
    queue<int> testQ;
    testQ.push(5);  
    cout << "the front of the queue is: " << testQ.front() << endl;
    cout << endl;
    */

   
    //Testing out 2d arrays, maybe could use this for mismatched heuristic 
/*
    char goalState[3][3] = {{'1', '2', '3'},
                            {'4', '5', '6'},
                            {'7', '8', '0'}};


    char testPuzzle[3][3] = {{'2', '3', '4'},
                            {'1', '5', '6'},
                            {'7', '0', '8'}};    

    char testPuzzle[3][3] = {{'1', '2', '3'},
                            {'4', '5', '6'},
                            {'7', '0', '8'}}; 

*/
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