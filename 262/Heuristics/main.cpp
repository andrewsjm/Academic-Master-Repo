#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <cmath>
#include <algorithm>
#include <fstream>
using namespace std;

// Represents a 2D point in the grid.
struct Point {
  int x, y;

  Point() : x(0), y(0) {}
  Point(int _x, int _y) : x(_x), y(_y) {}

  bool operator==(const Point& other) const {
    return x == other.x && y == other.y;
  }

  bool operator!=(const Point& other) const {
    return !(*this == other);
  }

  //hash function for unordered_set
  struct Hash {
    size_t operator()(const Point& p) const {
      return p.x * 31 + p.y;
    }
  };
};


//node in A* search with position, cost, heuristic, and total cost
struct Node {
  Point pos;
  Node* parent;
  double cost;
  double heuristic;
  double totalCost;

  Node(Point p, Node* _parent, double _cost, double _heuristic)
    : pos(p), parent(_parent), cost(_cost), heuristic(_heuristic),
    totalCost(_cost + _heuristic) {}
  bool operator>(const Node& other) const {
    return totalCost > other.totalCost;
  }
};


//calculate manhattan distance
double manhattanHeuristic(const Point& a, const Point& b) {
  return abs(a.x - b.x) + abs(a.y - b.y);
}


//calculate Euclidean distance 
double euclideanHeuristic(const Point& a, const Point& b) {
  return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

//rebuild path from goal to start using parent pointers.
vector<Point> reconstructPath(Node current) {
  vector<Point> path;
  while (current.parent != nullptr) {
    path.push_back(current.pos);
    current = *(current.parent);
  }
  path.push_back(current.pos);
  reverse(path.begin(), path.end());
  return path;

}

// A* Search function to find the shortest path in a grid.
bool aStarSearch(vector<vector<char>>& grid, const Point& start, const Point& end, const string& heuristicType) {
  priority_queue<Node, vector<Node>, greater<Node>> agenda;     //Priority queue to maintain nodes to be explored, sorted by their heuristic cost
  unordered_set<Point, Point::Hash> visited;                    // Set to keep track of visited nodes.

  vector<vector<double>> costs(grid.size(), vector<double>(grid[0].size(), numeric_limits<double>::max()));     // Matrix to store cost

  Node startNode(start, nullptr, 0, (heuristicType == "manhattan" ? // Initialize starting node with respective heuristic.
        manhattanHeuristic(start, end) :
        euclideanHeuristic(start, end)));
  agenda.push(startNode);


  vector<Point> directions;                                     //intialize vector directions so that it can change based on hueristic
  if(heuristicType == "manhattan"){
    directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};            //possible moves: west, east, north, south
  }
  else if(heuristicType == "euclidean"){
    directions = {{0,1}, {1,0}, {0,-1}, {-1,0}, {1,1}, {-1,1}, {1,-1}};   //possible moves: W, NW, SW, E, NE, SE, N, S
  }

  while (!agenda.empty()) {                                     //loop until the pq is empty
    Node current = agenda.top();                                //sets node to the top of the pq

    agenda.pop();                                               //removes from pq 

    //skip if the current node is already visited.
    if (visited.find(current.pos) != visited.end()) {
      continue;                                                 //no need to re-visit a node we already decided was not a good path
    }

    visited.insert(current.pos);                                //puts current node into the visited list 

    //if current node is the goal, reconstruct the path.
    if (current.pos == end) {
      vector<Point> path = reconstructPath(current);
      for (const Point& p : path) {
        grid[p.x][p.y] = '@';
      }
      cout << "Path found with cost " << current.cost << "." << endl;
      return true;
    }
    //explore neighboring nodes
    for (const Point& dir : directions) {
      Point nextPos(current.pos.x + dir.x, current.pos.y + dir.y);
      // Check grid boundaries and if the node has been visited.
      if (nextPos.x < 0 || nextPos.x >= grid.size() ||
          nextPos.y < 0 || nextPos.y >= grid[0].size() ||
          visited.find(nextPos) != visited.end()) {
        continue;
      }
      char cell = grid[nextPos.x][nextPos.y];
      //skip if obstacle
      if (cell == '#') {
        continue;
      }
      double newCost = 0;//initialize newCost
                         //Calculate cost to move to the next cell. ':' indicates a costlier move.
      if(heuristicType == "manhattan"){
        newCost = current.cost + (cell == ':' ? 2 : 1);
        if (newCost >= costs[nextPos.x][nextPos.y]) {
          continue;
        }
        costs[nextPos.x][nextPos.y] = newCost;
      }

      else if(heuristicType == "euclidean"){
        double moveCost = (cell == ':' ? 2 : 1);  // Base cost based on the cell type.
        if (dir.x != 0 && dir.y != 0) {  // Diagonal move
          moveCost *= sqrt(2);
        }
        newCost = current.cost + moveCost;
        if (newCost >= costs[nextPos.x][nextPos.y]) {
          continue;
        }
        costs[nextPos.x][nextPos.y] = newCost;
      }

      //calculate heuristic for the new node.
      double heuristic = heuristicType == "manhattan" ?
        manhattanHeuristic(nextPos, end) :
        euclideanHeuristic(nextPos, end);

      //create a new node and add it to the agenda.
      Node* newNode = new Node(nextPos, new Node(current.pos, current.parent, current.cost, current.heuristic), newCost, heuristic);
      agenda.push(*newNode);

      //mark the cell as being considered.
      if (grid[nextPos.x][nextPos.y] == '.') {
        grid[nextPos.x][nextPos.y] = '-';
      }
    }

    //mark the current cell as explored
    grid[current.pos.x][current.pos.y] = '+';

  }
  //no valid path found.
  cout << "No path." << endl;
  return false;
}

//function to display grid on console.
void displayGrid(const vector<vector<char>>& grid) {
  for (const auto& row : grid) {
    for (char cell : row) {                             //cycles through eah item in the row
      cout << cell;      //print out each item
      cout << " ";
    }
    cout << endl;                                       //cylcle to next row
  }
}

//function to display grid on console.


int main(int argc, char* argv[]) {
  //check for proper command-line arguments.
  if (argc < 3) {
    cout << "Please provide an input file and heuristic type ('manhattan' or 'euclidean')." << endl;
    return 1;
  }

  //read heuristic type and file path.
  string heuristicType = argv[2];                       //user input heuristic type to inform the program of which to use
  
  if (heuristicType == "Manhattan"){
    heuristicType = "manhattan";                        //in case of user inputting a capitol M in manhattan
  }
  
  if (heuristicType == "Euclidean"){
    heuristicType = "euclidean";                        //in case of user inputting a capitol E in euclidean
  }

  string f = argv[1];                                   //user input filename
  ifstream file(f);                                     //open the file given to the program in the first argument
  if (!file.is_open()) {                                //error case if input file is not opened
    cout << "Failed to open the input file." << endl;
    return 1;
  }

  // Read grid dimensions.
  int width, height;                                    //initialize the dimensions
  file >> width >> height;                              //get dimensions from file
  vector<vector<char>> grid(height, vector<char>(width)); //create 2D vector to contain grid for search
  Point start, end;                                     //intialize these as they will be used for population

  //Populate grid and identify start and end points.
  for (int i = 0; i < height; ++i) {                    //cycle through each columm
    for (int j = 0; j < width; ++j) {                   //cycle through each item in the row
      file >> grid[i][j];                               //use the file to populate grid
      if (grid[i][j] == 'o') {                          //defines o as start
        start = {i, j};
      } else if (grid[i][j] == '*') {                   //defines * as end
        end = {i, j};
      }
    }
  }
 
  //Execute A* search.
  cout<< "Selected file: " << f << endl;
  cout<< "Selected heuristic type: " << heuristicType << endl;
  cout<< "Grid from "<< f << " before search: " << endl;
  displayGrid(grid);                                    //display grid before search
  vector<vector<char>> grid2 = grid;

  aStarSearch(grid2, start, end, heuristicType);                //search
  cout<< f << "'s grid after the search" << endl;
  displayGrid(grid2);                                   //display grid after operation/search
  return 0;

}
