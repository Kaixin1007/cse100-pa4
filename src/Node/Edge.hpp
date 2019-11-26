#ifndef EDGE_HPP
#define EDGE_HPP
#include <utility>
#include <vector>
#include "ActorNode.hpp"
#include "MovieNode.hpp"
class MovieNode;
class ActorNode;
class Edge {
  public:
    ActorNode* actor1;
    ActorNode* actor2;
    MovieNode* movie;
    int weight;
    Edge(ActorNode* actor1, ActorNode* actor2, MovieNode* movie, int weight)
        : actor1(actor1), actor2(actor2), movie(movie), weight(weight) {}
};
#endif