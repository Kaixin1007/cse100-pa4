#ifndef ACTORNODE_HPP
#define ACTORNODE_HPP
#include <algorithm>
#include <climits>
#include <memory>
#include <stack>
#include <string>
#include <utility>
#include <vector>
#include "ActorNode.hpp"
#include "Edge.hpp"
#include "MovieNode.hpp"
using namespace std;
class MovieNode;
class Edge;
class ActorNode {
  public:
    string name;
    int dis;
    bool isDone;
    int priority;
    /* Constructor that initialize a MovieNode */
    ActorNode(string name) : name(name), dis(INT_MAX), priority(0) {}
    vector<Edge> edges;
    ActorNode* preActor;
    MovieNode* preMovie;
    stack<string, string> result;
    ~ActorNode() {}
};
struct ActorNodeComp {
    bool operator()(ActorNode*& lhs, ActorNode*& rhs) const {
        if (lhs->priority == rhs->priority)
            return lhs->name < rhs->name;
        else
            return lhs->priority > rhs->priority;
    }
};
#endif  // ACTORNODE_HPP