#include "decoder.h"
#include "queue.h"
#include "stack.h"
using namespace std;

decoder::decoder(const PNG & tm, pair<int,int> s)
   :start(s),mapImg(tm) {

/* YOUR CODE HERE */

vector<pair<int,int>> pathPts;
s = start;
tm = mapImg;
vector<pair<int,int>> encodePath;

    
}

PNG decoder::renderSolution(){

/* YOUR CODE HERE */

}

PNG decoder::renderMaze(){

/* YOUR CODE HERE */

}

void decoder::setGrey(PNG & im, pair<int,int> loc){

   RGBAPixel* location = im.getPixel(loc.first, loc.second);
    location->r = 2 * (location->r / 4);
    location->g = 2 * (location->g / 4); //effect grayer //these numbers because 
    location->b = 2 * (location->b / 4);

}

pair<int,int> decoder::findSpot(){

/* YOUR CODE HERE */

}

int decoder::pathLength(){

/* YOUR CODE HERE */

}

bool decoder::good(vector<vector<bool>> & v, vector<vector<int>> & d, pair<int,int> curr, pair<int,int> next){

/* YOUR CODE HERE */

}

vector<pair<int,int>> decoder::neighbors(pair<int,int> curr) {

   vector<pair<int,int>> adjacent;

    adjacent.push_back(make_pair(curr.first - 1, curr.second)); // Left
    adjacent.push_back(make_pair(curr.first, curr.second + 1)); // Below
    adjacent.push_back(make_pair(curr.first + 1, curr.second)); // Right
    adjacent.push_back(make_pair(curr.first, curr.second - 1)); // Above
    
    return adjacent;

}


bool decoder::compare(RGBAPixel p, int d){

/* YOUR CODE HERE */

}
