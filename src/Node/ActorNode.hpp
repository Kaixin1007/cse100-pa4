/*
 * @Descripttion:ActorNode to store Actor's information and the actor's movie
 * information
 * @version: 1.0
 * @Author: Kaixin Lin
 */
#ifndef ACTORNODE_HPP
#define ACTORNODE_HPP
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
/**
 * @name: ActorNode
 * @msg:  the class of Actor node for graph operation
 */
class ActorNode {
  public:
    string name;
    int dis;
    bool isDone;
    int priority;
    vector<Edge> edges;
    ActorNode* preActor;
    MovieNode* preMovie;
    stack<string, string> result;
    /* Constructor that initialize a MovieNode */
    ActorNode(string name) : name(name), dis(INT_MAX), priority(0) {}
    /* deconstruction for ActorNode */
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
struct ActorDisComp {
    bool operator()(ActorNode*& lhs, ActorNode*& rhs) const {
        if (lhs->dis == rhs->dis)
            return lhs->name > rhs->name;
        else
            return lhs->dis > rhs->dis;
    }
};
#endif  // ACTORNODE_HPP