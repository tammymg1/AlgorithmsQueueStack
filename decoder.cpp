#include "decoder.h"
#include "queue.h"
#include "stack.h"
using namespace std;


// TreasureMap
// renderMap -> encoded/embedded maze onto the image
// renderMaze -> greyed maze onto the image

// Decoder
// renderSolution -> red solution path onto the image //part of maze
// rederMaze -> greyed maze onto the image
// constructor -> pathPts solution path made ->

//*! read PA description again, *! what is decoder constructor doing

decoder::decoder(const PNG &tm, pair<int, int> s) : start(s), mapImg(tm){

    start = s;
    mapImg = tm;

    vector<vector<bool>> visited(mapImg.width(), vector<bool>(mapImg.height(), false));
    vector<vector<int>> shortestlenghts(mapImg.width(), vector<int>(mapImg.height(), 0));
    // vector<vector<int>> shortestlenghts(mapImg.width(), vector<int> (mapImg.height(), 0));
    vector<vector<pair<int, int>>> firstPath(mapImg.width(), vector<pair<int, int>>(mapImg.height(), make_pair(0, 0)));
    Queue<pair<int, int>> explored;
    pair<int, int> curr;
     
    visited[start.first][start.second] = true;
    shortestlenghts[start.first][start.second] = 0;
    firstPath[start.first][start.second] = start;
    pathPts.push_back(start);
    explored.enqueue(start); 

    while (!explored.isEmpty())
    {
        curr = explored.dequeue();
        for (pair<int, int> p : neighbors(curr))
        {
            if (good(visited, shortestlenghts, curr, p))
            {
                firstPath[p.first][p.second] = curr;
                pathPts.push_back(p);
                visited[p.first][p.second] = true;
                shortestlenghts[p.first][p.second] = shortestlenghts[curr.first][curr.second] + 1;
                explored.enqueue(p);
            }
        }
    }


    //finds index of treasure in pathPtrs //CHANGE UP LATER
      int value = 0;
      for (int i = 0; i < pathLength(); i++) {
         pair<int, int> compare = pathPts[value];
         pair<int, int> curr = pathPts[i];

         if (shortestlenghts[curr.first][curr.second] >= shortestlenghts[compare.first][compare.second]) {
            value = i;
         }
      }    


      Stack<pair<int, int>> path;
      pair<int, int> solution = pathPts[value];
      
      path.push(solution);
      while (path.peek() != start) {
         solution = firstPath[solution.first][solution.second];
         path.push(solution);
      }

      vector<pair<int, int>> newVector;
      while (!path.isEmpty()) {
         newVector.push_back(path.pop());
      }

      pathPts = newVector; 

} 

// Yu Guos method work

// maxDistance is ZouJJ method -> fails (*! but why)
//https://github.com/Zou-jj/CPSC221/blob/master/PA/pa2/pa2/decoder.cpp#L114

//https://github.com/DSbyte/CPSC-221-PAs/blob/master/Treasure%20Maps/decoder.cpp
//-1 implementation might see



PNG decoder::renderSolution()
{

    PNG solutionImage = mapImg;

    for (int index = 0; index < (int)pathLength(); index++)
    {
        RGBAPixel *pathpixel = solutionImage.getPixel(pathPts[index].first, pathPts[index].second); // removed .at[x]
        pathpixel->r = 255;
        pathpixel->g = 0;
        pathpixel->b = 0;
    }
    return solutionImage; //*! pathPts when added values? (solutions in it)

    // draw solution maze (for loop throw pathPTS) RED
}

PNG decoder::renderMaze()
{

    PNG mapMaze = mapImg;
    vector<vector<bool>> visited(mapImg.width(), vector<bool>(mapImg.height()));
    vector<vector<int>> shortestlenghts = vector<vector<int>>(mapImg.width(), vector<int>(mapImg.height(), 0));
    Queue<pair<int, int>> explored;

    visited[start.first][start.second] = true;
    explored.enqueue(start);

    while (!explored.isEmpty())
    {
        pair<int, int> curr = explored.dequeue();
        for (pair<int, int> p : neighbors(curr))
        {
            if (good(visited, shortestlenghts, curr, p))
            { // functions parameters edit accordingly
                visited[p.first][p.second] = true;
                setGrey(mapMaze, p);
                explored.enqueue(p);
                shortestlenghts[p.first][p.second] = shortestlenghts[curr.first][curr.second] + 1;
            }
        }
    }

    for (int col = -3; col <= 3; col++)
    {
        for (int row = -3; row <= 3; row++)
        {
            int x = start.first + col;
            int y = start.second + row;
            if (x >= 0 && x < (int)mapImg.width() && y >= 0 && y < (int)mapImg.height())
            {
                RGBAPixel *p = mapMaze.getPixel(x, y);
                p->b = 0;
                p->g = 0;
                p->r = 255;
            }
        }
    }

    return mapMaze;
}

void decoder::setGrey(PNG &im, pair<int, int> loc)
{

    RGBAPixel *location = im.getPixel(loc.first, loc.second);
    location->r = 2 * (location->r / 4);
    location->g = 2 * (location->g / 4); // effect grayer //these numbers because
    location->b = 2 * (location->b / 4);
}

/*
void decoder::setGrey(PNG & im, pair<int,int> loc){

   RGBAPixel *pixel = im.getPixel(loc.first, loc.second);
      pixel->r = 2*(pixel->r/4);
      pixel->g = 2*(pixel->g/4);
      pixel->b = 2*(pixel->b/4);


} */

pair<int,int> decoder::findSpot(){

   return pathPts.back();

}

int decoder::pathLength(){
   return pathPts.size();
}


bool decoder::good(vector<vector<bool>> &v, vector<vector<int>> &d, pair<int, int> curr, pair<int, int> next)
{

    if (next.first >= 0 && next.first < (int)mapImg.width())
    {
        if (next.second >= 0 && next.second < (int)mapImg.height())
        {
            if (v[next.first][next.second] == false)
            {
               return (compare(*mapImg.getPixel(next.first, next.second), d[curr.first][curr.second]));
                //{
                    // colour in Treasure map (endoded with proper distance)
                  //  return true;
                //}
            }
        }
    }
    return false;
}


vector<pair<int, int>> decoder::neighbors(pair<int, int> curr)
{

    vector<pair<int, int>> adjacent;

    adjacent.push_back(make_pair(curr.first - 1, curr.second)); // Left
    adjacent.push_back(make_pair(curr.first, curr.second + 1)); // Below
    adjacent.push_back(make_pair(curr.first + 1, curr.second)); // Right
    adjacent.push_back(make_pair(curr.first, curr.second - 1)); // Above

    return adjacent;
}


bool decoder::compare(RGBAPixel p, int d)
{
    //compare // d+1 and next RGBA Pixel have to be the same

    return (d + 1) % 64 == (p.r % 4) * 16 + (p.g % 4) * 4 + (p.b % 4); // d+1 and next RGBA Pixel have to be the same
}

