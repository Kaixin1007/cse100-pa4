#ifndef MOVIENODE_HPP
#define MOVIENODE_HPP
#include <algorithm>
#include <memory>
#include <queue>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include "ActorNode.hpp"
#include "Edge.hpp"
using namespace std;
class ActorNode;
class Edge;
class MovieNode {
  private:
  public:
    string name;
    int year;
    /* Constructor that initialize a MovieNode */
    MovieNode(string name, int year) : name(name), year(year) {}
    vector<ActorNode*> actors;
    // Edge edges;
    vector<Edge> edges;

    ~MovieNode() {}
};

#endif  // MOVIENODE_HPP