/*
 * @Descripttion: Achieve Disjoint Set DST for MST and movietravel in graph
 * @version: 1.0
 * @Author: Kaixin Lin
 */
#ifndef DISJOINTSET_HPP
#define DISJOINTSET_HPP
#include <unordered_map>
#include "Actor.hpp"
#include "ActorNode.hpp"
#include "Edge.hpp"
using namespace std;
/**
 * @name: DisjointSet
 * @msg:  the class of Disjoint Set DST for MST
 */
class DisjointSet {
  private:
    /* Unions two sets of ActorNode */
    void Union(ActorNode*& node1, ActorNode*& node2, Actor& actor);
    /* find the root node */
    ActorNode* find(ActorNode*& toFind, Actor& actor);
    /* Achieve path compression during find operation for disjoint set */
    void pathCompression(vector<ActorNode*>& path, ActorNode*& sentinel,
                         Actor& actor);

  public:
    /* Achieve MST in graph using disjoint Set, it return totalWeight in MST */
    int MST(Actor& actor, vector<Edge>& edge);
};
#endif  // DISJOINTSET_HPP