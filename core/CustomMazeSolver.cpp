#include "MazeSolver.hpp"
#include "CustomMazeSolver.hpp"
#include "MazeSolution.hpp"
#include "Maze.hpp"
#include "Direction.hpp"
//#include <iostream>
//#include <stdbool.h>
#include <ics46/factory/DynamicFactory.hpp> 
ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, CustomMazeSolver, "Custom DFS Maze Solver(Required)");

void 
CustomMazeSolver::solveMaze(const Maze& maze, MazeSolution& mazeSolution){
    mazeSolution.restart();
    visited = new bool*[mazeSolution.getHeight()];
    for(int i=0;i<mazeSolution.getHeight();i++){
        visited[i] = new bool[mazeSolution.getWidth()];
        for(int j=0;j<mazeSolution.getWidth();j++){
            visited[i][j] = false;
        }
    }
    /*for(int i=0;i<mazeSolution.getHeight();i++){
        for(int j=0;j<mazeSolution.getWidth();j++){
            visited[i][j]=false;
        }
    }*/
    doSolve(maze,mazeSolution);
}

bool
CustomMazeSolver::doSolve(const Maze& maze, MazeSolution& mazeSolution){
    std::pair<int,int> curr = mazeSolution.getCurrentCell();
    int currX = curr.first;
    int currY = curr.second;
    bool solved = false;
    //should not be the case
    if(visited[currY][currX]){
        return solved;
    }
    visited[currY][currX] = true;
    if(mazeSolution.isComplete()){
        /*const std::vector<Direction>& directions = mazeSolution.getMovements();
        for(int i=0; i<directions.size(); ++i){
            printf("%d\n",directions[i]);
        }*/
        solved = true;
    }
    if(!solved && currY-1>=0 && !maze.wallExists(currX,currY,Direction::up)){
        mazeSolution.extend(Direction::up);
        solved = doSolve(maze,mazeSolution);
        if(!solved){
            mazeSolution.backUp();
        }
    }
    if(!solved && currY+1 < mazeSolution.getHeight() && !maze.wallExists(currX,currY,Direction::down)){
        mazeSolution.extend(Direction::down);
        solved = doSolve(maze,mazeSolution);
        if(!solved){
            mazeSolution.backUp();
        }
    }

    if(!solved && currX-1>=0 && !maze.wallExists(currX,currY,Direction::left)){
        mazeSolution.extend(Direction::left);
        solved = doSolve(maze,mazeSolution);
        if(!solved){
            mazeSolution.backUp();
        }
    }
    if(!solved && currX+1 <= mazeSolution.getWidth() && !maze.wallExists(currX,currY,Direction::right)){
        mazeSolution.extend(Direction::right);
        solved = doSolve(maze,mazeSolution);
        if(!solved){
            mazeSolution.backUp();
        } 
    }
    return solved;
}

