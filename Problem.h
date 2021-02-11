#ifndef PROBLEM.H
#define PROBLEM.H

#include <iostream>
#include <string>
#include <queue>
#include <vector> 
#include <sstream>  //For taking in input 

#include <algorithm> //For swapping values in puzzle

using namespace std;


//Struct Node {}};



class Problem {
    private:
        //Node* root = nullptr; //root pointer to root      TESTING OUT NOT HAVING A ROOT CLASS 

        //Problem* root = nullptr;  

        //Pointers to the possible operators 
        Problem* up = nullptr; 
        Problem* down = nullptr;
        Problem* left = nullptr; 
        Problem* right = nullptr;

        //vector<int> inputPuzzle;

    public:
        //Data 
        vector<int> goalState = {1, 2, 3, 4, 5, 6, 7, 8, 0};   //2D representation of the goalState 
        vector<int> inputPuzzle;
        
        
        //vector<Problem> children; 


        //Originally from NOde class
        int depth;      //depth of a node / ALSO G(N)  general cost, [generally increases as more nodes are added]
        int hn;         //heuristic cost, depends on the type of heuristic used 
        //end of original node class stuff 


        //Methods
        //Sets inputPuzzle
        void setPuzzle(vector<int> puz);          //originally by reference?
        void setHn(int hn_);                


        //Adds all possible operators to the ExpandedOperatorProbs to then be added to priority queue based off of their costs 
        void operators(Problem& p); 


        int mismatchedHueristic(); 


        //Actually moving them 
        //returns a vector with the moved element
        //Because of the constraints given in Operator class, this SHOULD not lead to any issues of swapping an element 
        vector<int> moveUp(); 
        vector<int> moveDown();
        vector<int> moveLeft();
        vector<int> moveRight();


        //returns index for blank character
        int getBlankIndex();


        //Test's if this problem is the goal state
        bool goalTest();


        //originally had this outside 
        void printResults ();


        //Constructors    // might need more constructors 
        Problem(vector<int> inputPuzzle); 
        Problem (vector<int> inPuzz, int d, int hn_);
        Problem() {};

        Problem(const Problem& oldProb);            //Copy constructor
        //~Problem(); //destructor 

};

#endif