#ifndef MAZE
#define MAZE
    #include "Maze.hpp"
#endif

Maze::Maze(){};

Maze::Maze(int cellWidth, int cellHeight, int numRows, int numCols) {
    this->rows = numRows;
    this->cols = numCols;
    this->cells = vector<vector<Cell>>(this->rows);
    for(int i = 0; i < this->rows; i++) {
         vector<Cell> row = vector<Cell>(numCols);

         for(int i = 0; i < this->cols; i++) {
             row[i] = Cell();
         }

         this->cells[i] = row;
    }

    this->entranceIndex = Vector2i(0, this->cells.size());
    this->exitIndex = Vector2i(this->cells[0].size() - 1, 0);

    this->cellWidth = cellWidth;
    this->cellHeight = cellHeight;
};

Cell Maze::getCell(Vector2i index) {
    return this->cells[index.x][index.y];
}


bool Maze::outOfBounds(int i, int j) {

    return (
        i < 0 ||
        j < 0 ||
        i >= this->cells.size() ||
        j >= this->cells[0].size()
    );
}

bool Maze::isInBounds(int i, int j) {

    return (
        i >= 0 &&
        j >= 0 &&
        i < this->cells.size() &&
        j < this->cells[0].size()
    );
}

bool Maze::isValidIndex(Vector2i index) {
    int i = index.x;
    int j = index.y;

    return this->isInBounds(i, j);
}

vector<Vector2i> Maze::generateNeighbours(Vector2i index) {
    vector<Vector2i> neighbourIndices = vector<Vector2i>(4);

    int ind = 0;

    for(int i = index.x - 1; i <= index.x + 1; i++) {
        for(int j = index.y - 1; j <= index.y + 1; j++) {
            int dx = index.x - i;
            int dy = index.y - j;

            if(abs(dx + dy) != 1) {
                continue;
            }

            if(this->outOfBounds(i, j)) {
                continue;
            }

            Vector2i neighbourIndex = Vector2i(i, j);
            neighbourIndices[ind] = neighbourIndex;

            ind++;
        }
    }

    return neighbourIndices;
}



void Maze::generateMaze(Vector2i index) {
    this->cells[index.x][index.y].visited = true;

    vector<Vector2i> neighbours = this->generateNeighbours(index);

    // cout << endl;

    for(int i = 0; i < neighbours.size(); i++) {
        if(this->getCell(neighbours[i]).visited) {
            neighbours.erase(neighbours.begin() + i);
            i--;
        }
    }

    if(!neighbours.size()) {
        return;
    }

    int neighbourIndex = rand() % neighbours.size();
    Vector2i nextIndex = neighbours[neighbourIndex];

    neighbours.erase(neighbours.begin() + neighbourIndex);

    // determine which walls need to be removed
    int dx = nextIndex.x - index.x;
    int dy = nextIndex.y - index.y;

    if(dx == 1) {
        this->cells[index.x][index.y].east = false;
        this->cells[nextIndex.x][nextIndex.y].west = false;
    }

    else if(dy == 1) {
        this->cells[index.x][index.y].south = false;
        this->cells[nextIndex.x][nextIndex.y].north = false;
    }


    else if(dx == -1) {
        this->cells[index.x][index.y].west = false;
        this->cells[nextIndex.x][nextIndex.y].east = false;
    }


    else if(dy == -1) {
        this->cells[index.x][index.y].north = false;
        this->cells[nextIndex.x][nextIndex.y].south = false;
    }

    generateMaze(nextIndex);

    for(int i = 0; i < neighbours.size(); i++) {
        if(this->getCell(neighbours[i]).visited) {
            neighbours.erase(neighbours.begin() + i);
            i--;
        }
    }

    if(!neighbours.size()) {
        return;
    }
    

    neighbourIndex = rand() % neighbours.size();

    nextIndex = neighbours[neighbourIndex];

    neighbours.erase(neighbours.begin() + neighbourIndex);

    dx = nextIndex.x - index.x;
    dy = nextIndex.y - index.y;

    if(dx == 1) {
        this->cells[index.x][index.y].east = false;
        this->cells[nextIndex.x][nextIndex.y].west = false;
    }

    else if(dy == 1) {
        this->cells[index.x][index.y].south = false;
        this->cells[nextIndex.x][nextIndex.y].north = false;
    }


    else if(dx == -1) {
        this->cells[index.x][index.y].west = false;
        this->cells[nextIndex.x][nextIndex.y].east = false;
    }


    else if(dy == -1) {
        this->cells[index.x][index.y].north = false;
        this->cells[nextIndex.x][nextIndex.y].south = false;
    }

    this->generateMaze(nextIndex);
}

// return the vertices of the cell wall in the form of a vector of vectors
vector<vector<Vector2f>> Maze::getCellWalls(Vector2i index) {
    Cell cell = this->getCell(index);

    vector<vector<Vector2f>> borders;

    vector<Vector2f> border = vector<Vector2f>(2);

    if(cell.north) {
        border[0] = Vector2f((index.x + 1) * this->cellWidth, (index.y + 1) * this->cellHeight);
        border[1] = Vector2f((index.x + 2) * this->cellWidth, (index.y + 1) * this->cellHeight);
        borders.push_back(border);
    }

    if(cell.east) {
        border[0] = Vector2f((index.x + 2) * this->cellWidth, (index.y + 1) * this->cellHeight);
        border[1] = Vector2f((index.x + 2) * this->cellWidth, (index.y + 2) * this->cellHeight);
        borders.push_back(border);
    }

    if(cell.south) {
        border[0] = Vector2f((index.x + 1) * this->cellWidth, (index.y + 2) * this->cellHeight);
        border[1] = Vector2f((index.x + 2) * this->cellWidth, (index.y + 2) * this->cellHeight);
        borders.push_back(border);
    }

    if(cell.west) {
        border[0] = Vector2f((index.x + 1) * this->cellWidth, (index.y + 1) * this->cellHeight);
        border[1] = Vector2f((index.x + 1) * this->cellWidth, (index.y + 2) * this->cellHeight);
        borders.push_back(border);
    }

    return borders;
}