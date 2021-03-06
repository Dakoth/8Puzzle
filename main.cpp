#include <iostream>
#include <string>
#include <queue>
#include <vector> 

#include <sstream>  //For taking in input 
#include <algorithm> //For swapping values in puzzle

#include <chrono>   //For getting execution time 

#include "Problem.h"

using namespace std;

int numOfNodes = 1; //global variable to count number of nodes
int maxNumInQueue = 0; //Max number of nodes in a queue. 
int sortingAgorithm;  //used to determine which heuristic to use


//PRIORITY QUEUE STUFF /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class minHeapComp {
    public: 
        int operator() (const Problem& p1, const Problem& p2 ) {
            return (p1.depth + p1.hn) > (p2.depth + p2.hn); //empty for now
        }
};

priority_queue< Problem, vector<Problem>, minHeapComp > PriorityQ;   //Generates a min heap 

//priority_queue< Problem, vector<Problem>, minHeapComp > ExpandedOperatorProbs; //used for Operator class to store expanded problems 
 queue<Problem*>  ExpandedOperatorProbs;


///////////////////////////////////
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

//Copy constructor, might need
Problem::Problem(const Problem& oldProb) {
    this->inputPuzzle = oldProb.inputPuzzle;
    this->depth = oldProb.depth; 
    this->hn = oldProb.hn;
}

//Problem::Problem() {};

//Getter functions 
void Problem::setPuzzle(vector<int> puz) {this->inputPuzzle = puz;};         //originally by reference?
void Problem::setHn(int hn_) {this->hn = hn_;}



//Other Methods
//Adds all possible operators to the ExpandedOperatorProbs to then be added to priority queue based off of their costs 
//p = parent 
void Problem::operators(Problem& p){       //might need to have a Prob as an input 
    int blankIndex = getBlankIndex();

    p.depth++;   //increment the depth by 1 when you add  an operator 
    
    //moveUP is allowed 
    if (blankIndex > 2) {
        //numOfNodes++; //increment if this operator is valid
        
        p.up = new Problem(p.inputPuzzle, p.depth, p.hn);

        p.up->setPuzzle(p.up->moveUp());            //This statement is what's causing the crash

        //If the given operator is not the same as the parent puzzle, add it to the queue 
        if (p.up->inputPuzzle != p.inputPuzzle) {
            if (sortingAgorithm == 2) {                 //If mismatched heuristic is chosen, apply it 
            // cout << "MISMATCHED ENTERED" << endl;           //TEST
                p.up->setHn(p.up->mismatchedHueristic());
            }
            else if (sortingAgorithm == 3) {            //else do manhattan if a 3 
                p.up->setHn(p.up->manhattanDistance());
            }
        
            //ExpandedOperatorProbs.push( *(p.up) );
             ExpandedOperatorProbs.push( p.up );
        }   
    }


    // moveDown allowed
    if (blankIndex < 6) {
        //numOfNodes++; //increment if this operator is valid

        //Sets the child to be a new prob ... 
        p.down = new Problem(p.inputPuzzle, p.depth, p.hn);
        p.down->setPuzzle(p.down->moveDown());

        //If the given operator is not the same as the parent puzzle, add it to the queue 
        if (p.down->inputPuzzle != p.inputPuzzle) {
            if (sortingAgorithm == 2) {                 //If mismatched heuristic is chosen, apply it 
                p.down->setHn(p.down->mismatchedHueristic());
            }
            else if (sortingAgorithm == 3) {            //else do manhattan if a 3 
                p.down->setHn(p.down->manhattanDistance());
            }

        
    
            //ExpandedOperatorProbs.push( *(p.down) );
            ExpandedOperatorProbs.push( p.down );
        }
    }


    //move left 
    if ( (blankIndex % 3) > 0 ) {
        //numOfNodes++; //increment if this operator is valid
                                            //Sets the child to be a new prob ... 
        p.left = new Problem(p.inputPuzzle, p.depth, p.hn);         //Child pointer points to child node 
        p.left->setPuzzle(p.left->moveLeft());                  //set the puzzle of the child to the puzzle after doing Op 


        //If the given child puzzle is not the same as the parent puzzle, add it to the queue 
        if (p.left->inputPuzzle != p.inputPuzzle) {
            if (sortingAgorithm == 2) {                             //If mismatched heuristic is chosen, apply it 
                p.left->setHn(p.left->mismatchedHueristic());
            }
            else if (sortingAgorithm == 3) {                        //else do manhattan if a 3 
                //cout << "LEFT";
                p.left->setHn(p.left->manhattanDistance());
            }

            //ExpandedOperatorProbs.push(*(p.left));                  //enqueue this Problem* to a queue
            ExpandedOperatorProbs.push( p.left );
        }
    }

    
    //move Right
    if ( (blankIndex % 3) < 2)  {
        //cout << "CAN MOVE RIGHT, CALL APPROPRIATE MOVE FUNC" << endl;
        //numOfNodes++; //increment if this operator is valid

        //Sets the child to be a new prob ... 
        p.right = new Problem(p.inputPuzzle, p.depth, p.hn);        //Child pointer points to child node 
        p.right->setPuzzle(p.right->moveRight());                   //set the puzzle of the child to the puzzle after doing Op 


        //If the given child puzzle is not the same as the parent puzzle, add it to the queue 
        if (p.right->inputPuzzle != p.inputPuzzle) {
            if (sortingAgorithm == 2) {                                 //If mismatched heuristic is chosen, apply it 
                p.right->setHn(p.right->mismatchedHueristic());
            }
            else if (sortingAgorithm == 3) {                            //else do manhattan if a 3 
                p.right->setHn(p.right->manhattanDistance());
            }
        
            //ExpandedOperatorProbs.push(*(p.right));             //enqueue this Problem* to a queue
             ExpandedOperatorProbs.push( p.right );
        }
    }
    return;
}

//Actually moving them 
//returns a vector with the moved element
//Because of the constraints given in Operator class, this SHOULD not lead to any issues of swapping an element 
vector<int> Problem::moveUp() {  //orignally all had a parameter Problem
    vector<int> tempP1 = this->inputPuzzle;
    int zeroIndex = getBlankIndex();


    //(oringally did - 1 to everything)
    iter_swap(tempP1.begin() +zeroIndex, tempP1.begin() +zeroIndex- 3); //swaps the elements 

    return tempP1;  
}

vector<int> Problem::moveDown() {
    vector<int> tempP1 = this->inputPuzzle;
    int zeroIndex = getBlankIndex();
    iter_swap(tempP1.begin() +zeroIndex, tempP1.begin() +zeroIndex+ 3); //swaps the elements 

    return tempP1;
}

vector<int> Problem::moveLeft() {
    vector<int> tempP1 = this->inputPuzzle;
    int zeroIndex = getBlankIndex();
    iter_swap(tempP1.begin() +zeroIndex, tempP1.begin() +zeroIndex - 1); //swaps the elements 

    return tempP1;
}

vector<int> Problem::moveRight() {
    vector<int> tempP1 = this->inputPuzzle;
    int zeroIndex = getBlankIndex();
    iter_swap(tempP1.begin() +zeroIndex, tempP1.begin() +zeroIndex+ 1); //swaps the element
    return tempP1;
}



//returns index for blank character
int Problem::getBlankIndex() { 
    int index = 0;  

    for (int i = 0; i < inputPuzzle.size(); i++) {
        if (inputPuzzle.at(i) == 0) { 
            index = i;
        }
    }
    return index; 
}


//Test's if this problem is the goal state
bool Problem::goalTest() {  
    for (int i = 0; i < inputPuzzle.size(); i++) {
        if (inputPuzzle.at(i) != goalState.at(i)) {        //If any element does not equal the goal state, then false
            return false;
        }
    }
    return true;                //Means that this puzzle is the goal state, return true
}


//originally had this outside 
void Problem::printResults () {
    cout << endl;
    cout << "The best state to expand with a g(n) = " << this->depth << " and h(n) = " << this->hn << " is..." << endl;
    cout << this->inputPuzzle.at(0) << " " << this->inputPuzzle.at(1) << " " << this->inputPuzzle.at(2) << endl;
    cout << this->inputPuzzle.at(3) << " " << this->inputPuzzle.at(4) << " " << this->inputPuzzle.at(5) << endl;
    cout << this->inputPuzzle.at(6) << " " << this->inputPuzzle.at(7) << " " << this->inputPuzzle.at(8) << endl;
    return;
}


//Returns the number given by the mismatched heuristic 
int Problem::mismatchedHueristic() {
    int mismatches = 0; 

    for (int i = 0; i < this->inputPuzzle.size(); i++) {   

       if (this->inputPuzzle.at(i) == 0) {
            //if blank is selected, don't count it 
       }
       else if (this->inputPuzzle.at(i) != this->goalState.at(i)) {
           mismatches++;
       }
   }
    return mismatches;
}
 
int Problem::manhattanDistance() {
    int manCount = 0;   //manhatt distance count 

    //Notice that the Goal state just has each element in a strictly inceasing fashion (besides blank), we can take advantage of this 
    //in order to determine the manhattan distance between the input and the goal state;

    int goalRow;    //Both of these indicate the row and column of the corresponding element in the goal state. 
    int goalCol;

    int inputRow;   //Indicate the row and column of where an element is in the input Puzzle
    int inputCol;

    int indexOfIncorrectTile; //Uses helper function to get the index of a tile that is misplaced

    int difference = 0; //Difference between input and goal state  


    for (int i = 0; i < this->inputPuzzle.size(); i++) { 
            //Doesn't care if the blank char is in the right place 
            //originally inputPuzzle.at(i) 
        if ( (this->goalState.at(i) == 0) || (this->inputPuzzle.at(i) == this->goalState.at(i)) ) {
            //If blank is selected or both same element, do nothing
        }
        else {  //else not equal and not a blank state 
                    //originally i - 1
            goalRow = i / 3;      //Gets the row of this element in the goal state
            goalCol = i % 3;      //Gets the col of this element in the GOAL STATE

            indexOfIncorrectTile = getIndexOfInputElement(goalState.at(i));  //Gets the index of the desired element in input puzzle
            inputRow = indexOfIncorrectTile / 3;
            inputCol = indexOfIncorrectTile % 3; 

            difference = abs(goalRow - inputRow) + abs(goalCol - inputCol);  //This difference is the num of spaces an element is displaced

            manCount += difference; //Adds this difference to the Manhattan cost 
        }
    }
    
    return manCount;
} 

//Helper function for Manhattan 
//Takes in the desired element to look for 
int Problem::getIndexOfInputElement(int element){   
    int index; 

    for (int i = 0; i < this->inputPuzzle.size(); i++) { 
        if (inputPuzzle.at(i) == element) { 
            index = i;
        }
    }
    return index; 
}


////////////////////////////////////////////////////////////////////////////////////////////////
//General search  Returns if the soln was found or not 
//char PauseProgram;   //Use a cin to stop execution FOR TESTING PURPOSES

void generalSearch (Problem& p) { 

    PriorityQ.push(p);
    maxNumInQueue = PriorityQ.size();    //set inital max 
    
    Problem temp;                   //creates a temp problem, used to represent the top of the queue n stuff 
   
    //While the queue is not empty 
    while (PriorityQ.size() >= 0 )  {         //orignally !PriorityQ.empty()
        Problem tempForInput;        //Creates a temporary problem that is then set to equal temp, used to pass in values to Operator

        temp = PriorityQ.top();     //makes temp the top element of the priority queue
        tempForInput = temp;
        
        if (PriorityQ.empty()) {
            cout << "FAILURE" << endl;
            return;             //if the queue becomes empty, report failure
        }


        temp.printResults();   

        
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
        temp.operators(tempForInput);
        numOfNodes++;           //expand temp 
        //delete tempForInput;    //maybe delete it?

        //cout << "The size of Operators Queue is: " << ExpandedOperatorProbs.size() << endl;     //TEST


        //Next, add the expanded operators (if any) to the Priority Queue until the expanded operator queue is empty
        //Should skip if empty
        while(!ExpandedOperatorProbs.empty()) {
            //PriorityQ.push( ExpandedOperatorProbs.top() );     
            PriorityQ.push(  *(ExpandedOperatorProbs.front()) ); 
            ExpandedOperatorProbs.pop();
        }
       
        //Update max num of nodes in queue if need be
        if (maxNumInQueue < PriorityQ.size() ) {
            maxNumInQueue = PriorityQ.size();
        }

    /*
        cout << "Paused, give input: ";
        cin >> PauseProgram; //FOR TESTING
        cout << endl;
    */

    }
    return;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//main program
int main() {
    char user = '\0';

    string userPuzzle = "";  
    string userPuzzleConcat = "";

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
        }
        else if (user == '2') { //If not the default
            cout << "Enter your puzzle, use a zero to represent the blank" << endl;
            cout << "Enter the first row, use space or tabs between numbers: "; //<< endl; 

            getline(cin, userPuzzle);
            userPuzzleConcat += userPuzzle + " ";
            cout << endl;

            cout << "Enter the second row, use space or tabs between numbers: "; // << endl;
            getline(cin, userPuzzle);
            userPuzzleConcat += userPuzzle + " ";
            cout << endl;

            cout << "Enter the third row, use space or tabs between numbers: ";  //<< endl;
            getline(cin, userPuzzle);
            userPuzzleConcat += userPuzzle;
            cout << endl;


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


    //Timer stuff
    chrono::time_point<chrono::system_clock> start, end; 
    
    //Second part 
    sortingAgorithm = 0;
    cout << "Enter your choice of algorithm" << endl;
    cout << "1. Uniform Cost Search" << endl;
    cout << "2. A* with the Misplaced Tile heuristic" << endl;
    cout << "3. A* with the Manhattan Distance heuristic" << endl;
 
    while (sortingAgorithm != 1 && sortingAgorithm != 2 && sortingAgorithm != 3) { 
        cin >> sortingAgorithm; 
        cin.ignore(); 

        if (sortingAgorithm == 1 || sortingAgorithm == 2 || sortingAgorithm == 3) { //h(n) = 0
            Problem prob(initalProblem, 0, 0);

            cout << "Expanding state: " << endl;

            start = chrono::system_clock::now();
            generalSearch(prob);  
            end = chrono::system_clock::now();     
        }
        else {
            cout << "Please pick a valid input" << endl;
        }
    }    

    chrono::duration<double> elapsed_seconds = end - start;    
    //cout << "Elapsed time of algorithm is: " << elapsed_seconds.count() << " s" << endl; FOR TESTING
    return 0; 
}