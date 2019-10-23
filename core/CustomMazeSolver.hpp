#include <stdbool.h>
class CustomMazeSolver : public MazeSolver{
    public:
        void solveMaze(const Maze& maze, MazeSolution& mazeSolution);
    private:
        bool doSolve(const Maze& maze, MazeSolution& mazeSolution);
        bool** visited;
};
