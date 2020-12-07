#ifndef MAZEGENERATION
#define MAZEGENERATION
    #include "mazeGeneration.hpp"
#endif

#ifndef ASTARGRAPH
#define ASTARGRAPH
    #include "AStarGraph.hpp"
#endif

#define FPSCAP 60

int main(int argc, char *argv[]) {
    srand((unsigned int) time(NULL));

    string filename = "./Solution/sol.txt";

    int canvasWidth;
    int canvasHeight;

    VideoMode desktopDetails = VideoMode::getDesktopMode();
    canvasWidth = desktopDetails.width;
    canvasHeight = desktopDetails.height;

    RenderWindow canvas(VideoMode(canvasWidth, canvasHeight), "sfmltest", Style::Close | Style::Fullscreen);
    canvas.setFramerateLimit(FPSCAP);

    Event event;

    int w = 20;
    int h = 20;

    int numCols =  canvasWidth/w - 2;
    int numRows = canvasHeight/h - 2;

    Maze maze(w, h, numCols, numRows);
    maze.generateMaze(Vector2i(0,0));

    AStarGraph search(maze, Vector2i(0,0), Vector2i(numCols-1,numRows-1));

    while(canvas.isOpen()) {
        if(Keyboard::isKeyPressed(Keyboard::Escape)) {
            canvas.close();
        }

        canvas.clear();

        for(int i = 0; i < maze.cells.size(); i++) {
            for(int j = 0; j < maze.cells[i].size(); j++) {
                Vector2i index(i, j);

                vector<vector<Vector2f>> borders = maze.getCellWalls(index);

                for(int b = 0; b < borders.size(); b++) {
                    vector<Vector2f> border = borders[b];

                    Vertex borderVertices[2] {
                        Vertex(border[0]),
                        Vertex(border[1])
                    };

                    canvas.draw(borderVertices, 2, Lines);
                }
            }
        }

        {

            Color black(0,0,0);
            
            Vertex entrance[2] {
                Vertex(Vector2f((float) w*1, (float) w*1), black),
                Vertex(Vector2f((float) w*2, (float) w*1), black)
            };

            canvas.draw(entrance, 2, Lines);

            Vertex exit[2] {
                Vertex(Vector2f((float) (numCols+0)*w, (float) (numRows+1)*h), black),
                Vertex(Vector2f((float) (numCols+1)*w, (float) (numRows+1)*h), black)
            };

            canvas.draw(exit, 2, Lines);
        }

        canvas.display();
        break;
    }

    search.search(filename);

    ifstream inputPath;
    inputPath.open(filename);

    vector<Vector2i> path;

    int x, y;
    while(inputPath >> x >> y) {
        Vector2i nextNode = Vector2i(x, y);
        path.push_back(nextNode);
    }

    // add the start and end to the path

    path.push_back(Vector2i(0,0));
    path.push_back(Vector2i(0,-1));

    reverse(path.begin(), path.end());
    path.push_back(Vector2i(numCols-1, numRows));
    

    Color lineColour(100,255,255);

    for(int j = 0; j < path.size(); j++) {
        for(int i = 0; i < j; i++) {
            Vector2f start = Vector2f(path[i].x, path[i].y);
            Vector2f end = Vector2f(path[i+1].x, path[i+1].y);

            start += Vector2f(1.0f, 1.0f);
            end += Vector2f(1.0f, 1.0f);

            start *= (float) w;
            end *= (float) w;
            
            start += Vector2f((float) w/2, (float) h/2);
            end += Vector2f((float) w/2, (float) h/2);
            
            Vertex linePath[2] {
                Vertex(start, lineColour),
                Vertex(end, lineColour)
            };

            canvas.draw(linePath, 2, Lines);
        }

        canvas.display();
    }

    cin.get();

    return 0;
}


/*
Personal comment

Ubuntu WSL:
cd /mnt/c/users/aryag/onedrive/documents/github/mazeAndPathfinding
*/