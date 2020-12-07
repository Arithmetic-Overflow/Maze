#ifndef CELL
#define CELL
    #include "Cell.hpp"
#endif

Cell::Cell() {
    // cell's walls
    this->north = true;
    this->east  = true;
    this->south = true;
    this->west  = true;
    
    // whether a cell has been visited
    this->visited = false;
};