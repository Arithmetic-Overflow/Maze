#ifndef CELL
#define CELL
    #include "Cell.hpp"
#endif

#ifndef MAZEGENERATION
#define MAZEGENERATION
    #include "mazeGeneration.hpp"
#endif

class Maze {
    public:
        vector<vector<Cell>> cells;
        Vector2i entranceIndex;
        Vector2i exitIndex;

        int cellWidth, cellHeight;
        int rows, cols;

        Maze(int, int, int, int);
        Maze();

        Cell getCell(Vector2i);

        bool outOfBounds(int, int);
        bool isInBounds(int, int);
        bool isValidIndex(Vector2i);

        vector<Vector2i> generateNeighbours(Vector2i);

        void generateMaze(Vector2i);

        vector<vector<Vector2f>> getCellWalls(Vector2i);
};