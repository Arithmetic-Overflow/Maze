GPP = g++
OBJ = mazeGeneration.o Maze.o Cell.o AStarNode.o AStarGraph.o
PROGRAMNAME = mazegen

main : $(OBJ)
	g++ $(OBJ) -o mazegen -lsfml-graphics -lsfml-window -lsfml-system

%.o : %.cpp
	g++ -c $<

exportDisplay:
	export DISPLAY=:0

clean:
	rm -fv *.o $(PROGRAMNAME)