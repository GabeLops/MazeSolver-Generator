#include "Maze.hpp"
#include "MazeGenerator.hpp"
#include "CustomMazeGenerator.hpp"
#include "time.h"
#include <stdlib.h>
#include <ics46/factory/DynamicFactory.hpp> 
#include <random>
ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, CustomMazeGenerator, "Custom DFS Maze Generator(Required)");

bool CustomMazeGenerator::initialized=false;

CustomMazeGenerator::CustomMazeGenerator(){
    if(!initialized)
    {
        srand(time(NULL));
        //srand(1);

        //set it to true
        initialized = true;
    }

}
  
void 
CustomMazeGenerator::generateMaze(Maze& maze){
    maze.addAllWalls();
    visited = new bool*[maze.getHeight()];
    for(int i=0;i<maze.getHeight();i++){
        visited[i] = new bool[maze.getWidth()];
        for(int j=0;j<maze.getWidth();j++){
            visited[i][j] = false;
        }
    }
    doGenerate(maze,0,0);
}

void
CustomMazeGenerator::doGenerate(Maze& maze, int currY, int currX){
    visited[currY][currX] = true;
    for(int i=0;i<4;i++){
        if(shouldRecurse(maze,currY,currX)){
            Direction d = getRandomDirection(maze,currY,currX);
            //printf("Recurse: %d,%d,%d\n",currY,currX,d);
            recurse(maze,currY,currX,d);
        }else{
            //nothing to do
            //printf("Skipping: %d,%d,\n",currY,currX);
            break;
        }       
    }
}

void
CustomMazeGenerator::recurse(Maze& maze, int currY,int currX, Direction direction){
    maze.removeWall(currX,currY,direction);
    if(direction==Direction::up){
        doGenerate(maze,currY-1,currX);
    }else if(direction==Direction::down){
        doGenerate(maze,currY+1,currX);
    }else if(direction == Direction::left){
        doGenerate(maze,currY,currX-1);
    }else{
        doGenerate(maze,currY,currX+1);
    }
}

bool
CustomMazeGenerator::shouldRecurse(Maze& maze, int currY, int currX){
    if(currY-1>=0 && !visited[currY-1][currX]){
        return true;
    }
    if(currX-1>=0 && !visited[currY][currX-1]){
        return true;
    }
    if(currY+1<maze.getHeight() && !visited[currY+1][currX]){
        return true;
    }
    if(currX+1<maze.getWidth() && !visited[currY][currX+1]){
        return true;
    }
    return false;
}


Direction
CustomMazeGenerator::getRandomDirection(Maze& maze, int currY, int currX){
    while(true){    
        int randomDirectionIndex = rand()%4;
        if(randomDirectionIndex==0){
            if(currY-1>=0 && !visited[currY-1][currX]){
                return Direction::up;
            }
        }else if(randomDirectionIndex==1){
            if(currY+1<maze.getHeight() && !visited[currY+1][currX]){
                return Direction::down;
            }

        }else if(randomDirectionIndex==2){
            if(currX-1>=0 && !visited[currY][currX-1]){
                return Direction::left;
            }
        }else{
            if(currX+1<maze.getWidth()&& !visited[currY][currX+1]){
                return Direction::right;
            }
        }
        
    }
}