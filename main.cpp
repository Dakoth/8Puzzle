#include <iostream>
#include <string>
#include <queue>
#include <vector> 
#include <sstream>  //For taking in input 

#include <algorithm> //For swapping values in puzzle

#include "Problem.h"

using namespace std;

int numOfNodes = 1; //global variable to count number of nodes
int maxNumInQueue = 0; //Max number of nodes in a queue. 
int sortingAgorithm;  //used to determine which heuristic to use


//queue<Problem> ExpandedOperatorProbs; //Used to queue the puzzles given when expanding operators


//PRIORITY QUEUE STUFF /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class minHeapComp {
    public: 
        int operator() (const Problem& p1, const Problem& p2 ) {
            return (p1.depth + p1.hn) > (p2.depth + p2.hn); //empty for now
        }
};

priority_queue< Problem, vector<Problem>, minHeapComp > PriorityQ;   //Generates a min heap 
priority_queue< Problem, vector<Problem>, minHeapComp > ExpandedOperatorProbs; //used for Operator class to store expanded problems 



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


//Problem definitions 

//Constructors    // might need more constructors 
Problem::Problem(vector<int> inputPuzzle) { //NOT SURE IF THIS IS CORRECT FOR WHAT I WANNA DO        
    this->inputPuzzle = inputPuzzle;
    this->depth = 0;
    this->hn = 0;
}
Problem::Problem (vector<int> inPuzz, int d, int hn_) { //
    this->inputPuzzle = inPuzz;
    this->depth = d;
    this->hn = hn_;
}

//Problem::Problem() {};


void Problem::setPuzzle(vector<int> puz) {this->inputPuzzle = puz;};         //originally by reference?


//Adds all possible operators to the ExpandedOperatorProbs to then be added to priority queue based off of their costs 
void Problem::operators(Problem& p){       //might need to have a Prob as an input 
    int blankIndex = getBlankIndex();

    p.depth++;   //increment the depth by 1 when you add  an operator //Not sure if it should be here or inside funct

    //cout << blankIndex << endl; //test
    cout << "OPERATORS CALLED " << endl;


    Problem t;       //makes a default problem, unsure If i need to make other ones 

    //moveUP is allowed 
    
    if (blankIndex > 2) {
        t = p; 
        //cout << "CAN MOVE UP, CALL APPROPRIATE MOVE FUNC" << endl;


        t.setPuzzle(t.moveUp()); //Not sure if this function works like this??????

        numOfNodes++; //increment if this operator is valid
        //this->depth++;   //increment the depth by 1 when you add  an operator 
        //MIGHT NEED SOMETHING TO HANDLE IF USING A HUERSITC OR NOT 
        
        ExpandedOperatorProbs.push(t);
    }


    // moveDown allowed
    if (blankIndex < 6) {
        t = p;
        //cout << "CAN MOVE down, CALL APPROPRIATE MOVE FUNC" << endl;

        //t.moveDown();
        numOfNodes++; //increment if this operator is valid
        //this->depth++;   //increment the depth by 1 when you add  an operator 

        t.setPuzzle(t.moveDown());
        ExpandedOperatorProbs.push(t);
        
    }


    //move left 
    if ( (blankIndex % 3) > 0 ) {
        t = p;
        //cout << "CAN MOVE left, CALL APPROPRIATE MOVE FUNC" << endl;

        //t.moveLeft();
        numOfNodes++; //increment if this operator is valid
        //this->depth++;   //increment the depth by 1 when you add  an operator 

        t.setPuzzle(t.moveLeft());
        ExpandedOperatorProbs.push(t);
    }

    
    //move Right
    if ( (blankIndex % 3) < 2)  {
        t = p;
        cout << "CAN MOVE RIGHT, CALL APPROPRIATE MOVE FUNC" << endl;


        //t.moveRight();
        numOfNodes++; //increment if this operator is valid
        //this->depth++;   //increment the depth by 1 when you add  an operator 
        t.setPuzzle(t.moveRight());
        ExpandedOperatorProbs.push(t);
    }
    return;
}


//Actually moving them 
//returns a vector with the moved element
//Because of the constraints given in Operator class, this SHOULD not lead to any issues of swapping an element 
vector<int> Problem::moveUp() {  //orignally all had a parameter Problem
    vector<int> tempP1 = this->inputPuzzle;
    //vector<int> tempP2 = this->inputPuzzle;
    int zeroIndex = getBlankIndex();

    //iter_swap(tempP1.at(zeroIndex), tempP1.at(zeroIndex - 3) ); //swaps the elements 
    iter_swap(tempP1.begin() +zeroIndex - 1, tempP1.begin() +zeroIndex - 1 - 3); //swaps the elements 

    return tempP1;  //I think tempP1 is the one I'm supposed to return...
}

vector<int> Problem::moveDown() {
    vector<int> tempP1 = this->inputPuzzle;
    //vector<int> tempP2 = this->inputPuzzle;
    int zeroIndex = getBlankIndex();

    //iter_swap(tempP1.at(zeroIndex), tempP1.at(zeroIndex + 3) ); //swaps the elements 
    iter_swap(tempP1.begin() +zeroIndex - 1, tempP1.begin() +zeroIndex - 1 + 3); //swaps the elements 

    return tempP1;
}

vector<int> Problem::moveLeft() {
    vector<int> tempP1 = this->inputPuzzle;
    int zeroIndex = getBlankIndex();

    //iter_swap(tempP1.at(zeroIndex), tempP1.at(zeroIndex - 1) ); //swaps the elements 
    iter_swap(tempP1.begin() +zeroIndex - 1, tempP1.begin() +zeroIndex - 1 - 1); //swaps the elements 
    return tempP1;
}

vector<int> Problem::moveRight() {
    vector<int> tempP1 = this->inputPuzzle;
    int zeroIndex = getBlankIndex();

    //iter_swap(tempP1.at(zeroIndex), tempP1.at(zeroIndex + 1) ); //swaps the elements 
    iter_swap(tempP1.begin() +zeroIndex - 1, tempP1.begin() +zeroIndex - 1 + 1); //swaps the elements 
    return tempP1;
}



//returns index for blank character
int Problem::getBlankIndex() { //(Problem& prob) {           //originally prob...
    int index = 0;  

    for (int i = 0; i < inputPuzzle.size(); i++) {
        if (inputPuzzle.at(i) == 0) { 
            //cout << "recognized that " << i << " is the BlankIndex" << endl; //test
            index = i;
        }
    }
    return index; 
}


//Test's if this problem is the goal state
bool Problem::goalTest() {  //orignally Problem& prob)
    //cout << "goalTest called" << endl;

    for (int i = 0; i < inputPuzzle.size(); i++) {
        if (inputPuzzle.at(i) != goalState.at(i)) {        //If any element does not equal the goal state, then false
            return false;
        }
    }
    return true;    //Means that this puzzle is the goal state, return true
}


//originally had this outside 
void Problem::printResults () {
    cout << endl;
    cout << "The best state to expand with a g(n) = " << this->depth << " and h(n) = " << this->hn << " is..." << endl;
    cout << inputPuzzle.at(0) << " " << inputPuzzle.at(1) << " " << inputPuzzle.at(2) << endl;
    cout << inputPuzzle.at(3) << " " << inputPuzzle.at(4) << " " << inputPuzzle.at(5) << endl;
    cout << inputPuzzle.at(6) << " " << inputPuzzle.at(7) << " " << inputPuzzle.at(8) << endl;
    return;
}






//Queue stuff

//queue<Problem> ExpandedOperatorProbs;   //used for Operator class to store expanded problems 





////////////////////////////////////////////////////////////////////////////////////////////////
//General search 

//Fix later
//Returns if the soln was found or not 
void generalSearch (Problem& p) { 
    //cout << "yuh" << endl;      // endl;

    PriorityQ.push(p);


    //TESTING out 2 elemeents in the queue
    //vector<int> p2 = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    //vector<int> p3 = {1, 2, 3, 4, 0, 8, 7, 6, 5};
    //Problem prob2(p2, 0, 1);
    //PriorityQ.push(prob2);

    // END OF TEST


    maxNumInQueue = PriorityQ.size();    //set inital max 
    
    Problem temp;   //creates a temp problem, used to represent the top of the queue n stuff 

    Problem tempForInput;           //Creates a temporary problem that is then set to equal temp, used to pass in values to Operator


    //cout << "PRIORITYQ SIZE IS: " << PriorityQ.size() << endl;

    //While the queue is not empty 
    while (PriorityQ.size() >= 0 )  {         //orignally !PriorityQ.empty()
        //cout << "in while loop" << endl;

        temp = PriorityQ.top();     //makes temp the top element of the priority queue
        
        tempForInput = temp;       //Used for when we pass into Operator()
        
        if (PriorityQ.empty()) {
            cout << "FAILURE" << endl;
            return;       //if the queue becomes empty, report failure
        }

        temp.printResults();   //Not sure if I should put this here 
        
        //If the goal is reached, then return success
        if (temp.goalTest()) {
            cout << "Goal!!!" << endl;
            cout << "To solve this problem the search algorithm expanded a total of " << numOfNodes << " nodes." << endl;
            cout << "The maximum number of nodes in the queue at any one time was " << maxNumInQueue << "." << endl;
            cout << "The depth of the goal node was " << temp.depth << endl;
            return;
        }


        PriorityQ.pop();  //Need to pop the queue after checking 

        //Next, expand operators into the queue
        //NEED TO FIGURE OUT HOW TO DO THIS PART, Probably in some kind of forloop using the operator vector
        //PriorityQ.push(temp.operators());
        //PriorityQ.top().operators();
        temp.operators(tempForInput);
        //numOfNodes++;       //increment num of nodes

        //cout << "The size of Operators Queue is: " << ExpandedOperatorProbs.size() << endl;     //TEST


        //Next, add the expanded operators (if any) to the Priority Queue until the expanded operator queue is empty
        //for (int i = 0; i < ExpandedOperatorProbs.size(); i++) {
        //Should skip if empty
        while (!ExpandedOperatorProbs.empty()) {
            PriorityQ.push(ExpandedOperatorProbs.top());          //orignally was .front() cause EOP was a regular queue
            ExpandedOperatorProbs.pop();
        }
       


        //Update max num of nodes in queue if need be
        if (maxNumInQueue < PriorityQ.size() ) {
            maxNumInQueue = PriorityQ.size();
        }

    }

    cout << "exited loop" << endl;
    //assume it returns 
    return;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//main program
int main() {
    char user = '\0';
    bool isSolvable;



    string userPuzzle = "";  
    string userPuzzleConcat = "";
    //int problem[9] = {}; //Initalize an empty problem 

    vector<int> initalProblem;
    vector<int> defaultProb = {1, 2, 3, 4, 8, 0, 7, 6, 5};


    cout << "Hello and Welcome to Alfredo Gonzalez' 8-puzzle solver " << endl;
    cout << "Type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle." << endl;
    
    //Puzzle choices WORKS!!
    while (user != '1' && user != '2') { 
        cin >> user; 
        cin.ignore(); 

        if (user == '1' ) { //default puzzle 
            initalProblem = defaultProb;
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
            
            //
            while(ss >>n ){
                initalProblem.push_back(n);
            }
            ss.clear();
        }
        else {
            cout << "Plese pick a valid input " << endl;
        }
    }   

    //TESTING FUNCTIONS
    /*
    Problem prob(initalProblem, 0, 0);   //initalizes a problem 

   // prob.setPuzzle(initalProblem); //sets the inital problem puzzle to be the input
    cout << "TEST PRINT OF PROBLEM" << endl;
    //prob.printResults();
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
    */ 
    //PriorityQ.push()



    //Second part 
    //user = '\0';
    sortingAgorithm = 0;
    cout << "Enter your choice of algorithm" << endl;
    cout << "1. Uniform Cost Search" << endl;
    cout << "2. A* with the Misplaced Tile heuristic" << endl;
    cout << "3. A* with the Manhattan Distance heuristic" << endl;
 
    while (sortingAgorithm != 1 && sortingAgorithm != 2 && sortingAgorithm != 3) { 
        cin >> sortingAgorithm; 
        cin.ignore(); 

        if (sortingAgorithm == 1 ) { //h(n) = 0
            Problem prob(initalProblem, 0, 0);
            cout << "UNIFORM COST SEARCH" << endl;
            generalSearch(prob);           //TESTING
            
        }
        else if (sortingAgorithm == 2) {
             cout << "MISPLACED TILE" << endl;
        }
        else if (sortingAgorithm == 3) {
            cout << "MANHATTAN DISTANCE" << endl;
        }
        else {
            cout << "Please pick a valid input" << endl;
        }
    }    

    cout << "reached end of program" << endl;


    //tests if the array was added 
    /*
    for(int i = 0; i < problem.size(); i++){ 
         cout << problem.at(i) << " ";
    }
    */

   
    //Testing out 2d arrays, maybe could use this for mismatched heuristic 
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