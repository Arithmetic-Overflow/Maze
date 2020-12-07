#ifndef ASTARNODE
#define ASTARNODE
    #include "AStarNode.hpp"
#endif

AStarNode::AStarNode(){};

AStarNode::AStarNode(Vector2i p, vector<Vector2i> connections, AStarNode *pathedFrom) {
    this->p = p;
    this->connections = connections;

    this->pathedFrom = pathedFrom;

    this->expanded = false;
};

int AStarNode::manhattanDistanceToNode(Vector2i point) {
    Vector2i displacement = point - this->p;
    int manhattanDist = abs(displacement.x) + abs(displacement.y);

    return manhattanDist;
}

void AStarNode::calculatefCost(Vector2i start, Vector2i target) {
    int fCost = this->calculategCost(start) + this->calculatehCost(target);

    this->fCost = fCost;
}

int AStarNode::calculategCost(Vector2i start) {
    int gCost = 0;
    AStarNode *nextNodeInPath = this;

    while(nextNodeInPath != NULL) {
        nextNodeInPath = nextNodeInPath->pathedFrom;
    }

    this->gCost = gCost;

    return gCost;
}

int AStarNode::calculatehCost(Vector2i target) {
    int hCost = this->manhattanDistanceToNode(target);
    this->hCost = hCost;

    return hCost; 
}