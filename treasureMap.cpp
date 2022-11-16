#include "treasureMap.h"
#include "queue.h"
using namespace std;

// using gdb ./testMaze 
// run

treasureMap::treasureMap(const PNG & baseim, const PNG & mazeim, pair<int,int> s)
{    
    base = baseim;
    maze = mazeim;
    start = s;
}

void treasureMap::setGrey(PNG & im, pair<int,int> loc){

    RGBAPixel* location = im.getPixel(loc.first, loc.second);
    location->r = 2 * (location->r / 4);
    location->g = 2 * (location->g / 4); //effect grayer //these numbers because 
    location->b = 2 * (location->b / 4);

}

void treasureMap::setLOB(PNG & im, pair<int,int> loc, int d){
    //why are we using dereferencing - RGBA Pixel is a pointer

    RGBAPixel* location = im.getPixel(loc.first, loc.second);
    location->r = ((location->r >> 2) << 2) + ((d / 16) % 4);
    location->g = (location->g & 0xFC) + ((d / 4) % 4);
    location->b = (location->b & 0xFC) + (d % 4); 
    //use modulous and >> <<

}

PNG treasureMap::renderMap(){

    PNG map = base;

    vector<vector<bool>> visited(base.width(), vector<bool> (base.height(), false)); 
    vector<vector<int>> shortestlenghts(base.width(), vector<int> (base.height(), 0)); // (width height) 
    
    //double vectors initialized

    Queue<pair<int,int>> explored;

    visited[start.first][start.second] = true;
    shortestlenghts[start.first][start.second] = 0; //both set to 0 //next +1
    setLOB(map, start, 0); //d = 0 (encode distance)
    explored.enqueue(start);

    while (!explored.isEmpty()) {
        pair<int,int> curr = explored.dequeue(); //our queue methods only (dequeue also returns it)
        for (pair<int,int> p : neighbors(curr)) {
            if (good(visited, curr, p)) {
                visited[p.first][p.second] = true;
                shortestlenghts[p.first][p.second] = 1 + shortestlenghts[curr.first][curr.second];
                setLOB(map, p, shortestlenghts[p.first][p.second]); // essentially every point encoded
                explored.enqueue(p);
            }
        }
    }
    return map;
}

    //
    // This function also draws a red 7px x 7px square at the start                                                                                    
    // location. If the start location is near the edge of the image,
    // just draw the existing portion of the square. The start 
    // should be at the center of the square.

PNG treasureMap::renderMaze(){ 


    PNG mapMaze = base; //PNG(base)
    vector<vector<bool>> visited(base.width(), vector<bool> (base.height())); //default is false 
    Queue<pair<int,int>> explored;

    visited[start.first][start.second] = true;
    explored.enqueue(start);

    while (!explored.isEmpty()) {
        pair<int,int> curr = explored.dequeue(); 
        for (pair<int,int> p : neighbors(curr)) { //(only Maze grey) = good
            if (good(visited, curr, p)) {
                visited[p.first][p.second] = true;
                setGrey(mapMaze, p); 
                explored.enqueue(p);
            }
        }
    }


    // at start
    // if +3.5 available on 4 sides make a square (red colour)
    // else nothing (can leave empty)
    //- how to start = for loop

    // should have done with brain this one (but its fine you learned it)

    for (int col = -3; col <= 3; col++){
        for (int row = -3; row <= 3; row++){
            int x = start.first + col;
            int y = start.second + row;
            if (x >= 0 && x < (int)base.width() && y >= 0 && y < (int)base.height()){
                RGBAPixel* p = mapMaze.getPixel(x, y); //RGBA get Pixel *
                p->b = 0;
                p->g = 0;
                p->r = 255;
            } //column and row used smartly here (Square every pixel)
        }
    }
        
    return mapMaze;

}



bool treasureMap::good(vector<vector<bool>> & v, pair<int,int> curr, pair<int,int> next){

if (next.first >= 0 && next.first < (int) base.width()){ //warnings cast to (int), irrelevant
        if (next.second >= 0 && next.second < (int) base.height()){
            if (v[next.first][next.second] == false){ //2D vector or array -> location 
                if (*maze.getPixel(next.first, next.second) == (*maze.getPixel(curr.first, curr.second))) { //** whats the ->operator
                // pointer maze.getPixel (dereferencing) ->
                    return true;
                }
            }
        }
    }
//else {    
    return false; // keep it out (if inner false -> SEGILL)
//}

}



vector<pair<int,int>> treasureMap::neighbors(pair<int,int> curr) {

    vector<pair<int,int>> adjacent;

    adjacent.push_back(make_pair(curr.first - 1, curr.second)); // Left
    adjacent.push_back(make_pair(curr.first, curr.second + 1)); // Below
    adjacent.push_back(make_pair(curr.first + 1, curr.second)); // Right
    adjacent.push_back(make_pair(curr.first, curr.second - 1)); // Above
    
    return adjacent;

}

