#ifndef MAZE
#define MAZE
    #include "Maze.hpp"
#endif

#ifndef ASTARNODE
#define ASTARNODE
    #include "AStarNode.hpp"
#endif

// #ifndef MAZEGENERATION
// #define MAZEGENERATION
//     #include "mazeGeneration.hpp"
// #endif

class AStarGraph {
    public:
        Maze maze;
        vector<AStarNode> nodes;

        Vector2i start;
        Vector2i target;
    
        AStarGraph(Maze, Vector2i, Vector2i);
        AStarGraph();

        void generateNode(Vector2i, AStarNode *);
        vector<Vector2i> generateConnections(Vector2i);

        bool notInNodes(Vector2i);

        void expandNode(AStarNode);

        void search(string);
};