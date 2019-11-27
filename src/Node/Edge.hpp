/*
 * @Descripttion:define edge to connect movie and actor in graph
 * @version: 1.0
 * @Author: Kaixin Lin
 */
#ifndef EDGE_HPP
#define EDGE_HPP
#include <utility>
#include <vector>
#include "ActorNode.hpp"
#include "MovieNode.hpp"
class MovieNode;
class ActorNode;
/**
 * @name: Edge
 * @msg:  the class of Edge for graph operation
 */
class Edge {
  public:
    // store two actor, movie and weight
    ActorNode* actor1;
    ActorNode* actor2;
    MovieNode* movie;
    int weight;  // in wnweighted graph, weight = 1,in weighted graph, weight = 1+2019-year

    /* Constructor that initialize a Edge */
    Edge(ActorNode* actor1, ActorNode* actor2, MovieNode* movie, int weight)
        : actor1(actor1), actor2(actor2), movie(movie), weight(weight) {}
};
/* Comparator of Edge for Edge.In priority queue,
 * Edge with less weight has higher priority
 */
struct EdgeComp {
    bool operator()(Edge& lhs, Edge& rhs) const {
        return lhs.weight > rhs.weight;
    }
};
#endif  // EDGE_HPP