#ifndef MAZEGENERATION
#define MAZEGENERATION
    #include "mazeGeneration.hpp"
#endif

class AStarNode {
    public:
        // cost functions
        // f is the total cost
        // g is the manhattan distance from a node to the start
        // h is the manhattan distance from a node to the target
        int fCost, gCost, hCost;
        
        // position of a node
        Vector2i p;

        // indices of all connected nodes
        vector<Vector2i> connections;

        AStarNode *pathedFrom;

        bool expanded;

        AStarNode(Vector2i, vector<Vector2i>, AStarNode *);
        AStarNode();

        // manhattan distance from a point to the node
        int manhattanDistanceToNode(Vector2i);

        void calculatefCost(Vector2i, Vector2i);
        int calculategCost(Vector2i);
        int calculatehCost(Vector2i);
};