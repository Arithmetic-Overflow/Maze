#ifndef ASTARGRAPH
#define ASTARGRAPH
    #include "AStarGraph.hpp"
#endif


AStarGraph::AStarGraph(Maze maze, Vector2i startIndex, Vector2i targetIndex) {
    this->maze = maze;
    this->start = startIndex;
    this->target = targetIndex;

    this->generateNode(this->start, NULL);

    cout << "this runs too?" << endl;
};

vector<Vector2i> AStarGraph::generateConnections(Vector2i cellIndex) {
    Cell cell = this->maze.getCell(cellIndex);
    vector<Vector2i> connections;

    int i = cellIndex.x;
    int j = cellIndex.y;
    
    if(!cell.north) {
        connections.push_back(Vector2i(i, j-1));
    }

    if(!cell.east) {
        connections.push_back(Vector2i(i+1, j));
    }

    if(!cell.south) {
        connections.push_back(Vector2i(i, j+1));
    }

    if(!cell.west) {
        connections.push_back(Vector2i(i-1, j));
    }

    return connections;
}

void AStarGraph::generateNode(Vector2i cellIndex, AStarNode *pathedFrom) {
    Cell cell = this->maze.getCell(cellIndex);

    vector<Vector2i> connections = this->generateConnections(cellIndex);

    int i;
    for(i = 0; i < this->nodes.size(); i++) {
        if(this->nodes[i].p == pathedFrom->p) {
            break;
        }
    }

    AStarNode cellNode(cellIndex, connections, &(this->nodes[i]));
    this->nodes.push_back(cellNode);
}

bool AStarGraph::notInNodes(Vector2i nodeIndex) {
    for(AStarNode n : this->nodes) {
        if(n.p == nodeIndex) {
            return false;
        }
    }

    return true;
}

void AStarGraph::expandNode(AStarNode node) {
    for(Vector2i newNodeIndex : node.connections) {
        if(this->notInNodes(newNodeIndex)) {
            this->generateNode(newNodeIndex, &node);
        }
    }

    int i;

    for(i = 0; i < this->nodes.size(); i++) {
        if(this->nodes[i].p == node.p) {
            break;
        }
    }

    this->nodes[i].expanded = true;
}

void AStarGraph::search(string filename) {
    AStarNode expandingNode = this->nodes[0];
    while(expandingNode.p != this->target) {
        this->expandNode(expandingNode);

        int minfCost = 999999999;
        for(AStarNode node : this->nodes) {
            if(node.expanded) {
                continue;
            }

            node.calculatefCost(this->start, this->target);

            if(minfCost > node.fCost) {
                minfCost = node.fCost;
                expandingNode = node;
            }
        }
    }

    int i;
    for(i = 0; i < this->nodes.size(); i++) {
        if(expandingNode.p == (this->nodes[i]).p) {
            break;
        }
    }

    AStarNode *node = &(this->nodes[i]);

    ofstream output;
    output.open(filename);

    while(node->pathedFrom != NULL) {
        output << node->p.x << " " << node->p.y << endl;
        node = node->pathedFrom;
    }

    output.close();
}