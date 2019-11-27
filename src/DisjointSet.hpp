#ifndef DISJOINTSET_HPP
#define DISJOINTSET_HPP
#include <unordered_map>
#include "Actor.hpp"
#include "ActorNode.hpp"
#include "Edge.hpp"
using namespace std;
class DisjointSet {
  public:
    /* Unions two sets */
    void Union(ActorNode*& node1, ActorNode*& node2, Actor& actor);
    /* find the root node */
    ActorNode* find(ActorNode*& toFind, Actor& actor);
    void pathCompression(vector<ActorNode*>& path, ActorNode*& sentinel,
                         Actor& actor);
    int MST(Actor& actor, vector<Edge>& edge);
};
#endif  // DISJOINTSET_HPP