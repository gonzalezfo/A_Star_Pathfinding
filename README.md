# Console A* Pathfinder



*** Summary ***
-------------------------------------------------------------------------------
The program takes a .txt input of the maze, loads it and tries to find the best
path using the A* algorithm. The grid is formed by cell structs with different
params such as if has been visited or not, distance to goal, position in the
grid, a vector of the four neighbours that surround each cell and a pointer to
the parent.

The algorithm starts from the starting point (A) and analyzes all the neighbours
taking into account their distance to the goal (B). It keeps updating the parent
pointer when it finds an appropiated path so we can run it backwards once we
reach the end cell. Once it visites a cell, won't go back to it. The cells are
represented by (.) and walls by (X).

*** Testing ***
-------------------------------------------------------------------------------
The code has been tested with different .txt.
Some of them respecting all the necessary details, others skipping the start or
end point to check the error handling. Also I have tried maps without solution

*** Build Program ***
-------------------------------------------------------------------------------
1. If the project is already compiled (there are .exes in the bin folder) go to step 5
2. Click on compile_vsXXXX.bat depending on your version of Visual Studio installed.
3. The VS project will be built in a build folder.
4. Compile it
5. Execute it from the bin folder (the one with _d is the debug compiled version)
6. Put the number of the map you want (make sure that it exists)
7. If you create new files keep the format of the existing files
9. Output will appear in the console
10. May the force be with you

*** Credits ***
--------------------------------------------------------------------------------
Program based in OneLoneCoder solution: https://github.com/OneLoneCoder/videos/blob/master/OneLoneCoder_PathFinding_AStar.cpp
