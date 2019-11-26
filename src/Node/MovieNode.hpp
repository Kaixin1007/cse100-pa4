/*
 * @Descripttion:MovieNode to store movie's information and actor who plays in
 * this movie
 * @version: 1.0
 * @Author: Kaixin Lin
 */
#ifndef MOVIENODE_HPP
#define MOVIENODE_HPP
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

/**
 * @name: MovieNode
 * @msg:  the class of Movie node for graph operation
 */
class MovieNode {
  public:
    string name;
    int year;
    vector<ActorNode*> actors;
    vector<Edge> edges;
    /* Constructor that initialize a MovieNode */
    MovieNode(string name, int year) : name(name), year(year) {}
    /* deconstruction for MovieNode */
    ~MovieNode() {}
};

#endif  // MOVIENODE_HPP