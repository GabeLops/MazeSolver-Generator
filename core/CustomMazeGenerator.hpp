
class CustomMazeGenerator : public MazeGenerator{
    public:
        CustomMazeGenerator();
        void generateMaze(Maze& maze);
    private:
        bool** visited;
        void doGenerate(Maze& maze, int currX, int currY);
        void recurse(Maze& maze, int currX,int currY, Direction direction);
		bool shouldRecurse(Maze& maze, int currX, int currY);
        Direction getRandomDirection(Maze& maze, int currX, int currY);

        static bool initialized;
};


