/*
 * @Descripttion: Actor file to finish Pathfinder, linkpredictor for PA4
 * @version: 1.0
 * @Author: Kaixin Lin
 */
#ifndef Actor_HPP
#define Actor_HPP
#include <algorithm>
#include <queue>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include "ActorNode.hpp"
#include "Edge.hpp"
#include "MovieNode.hpp"
using namespace std;
#define OUTPUT_NUMBER 4  // print top 4th actor

/**
 * @name: Actor
 * @msg:  the class of Actor for graph operation
 */
class Actor {
  private:
    typedef priority_queue<ActorNode*, vector<ActorNode*>, ActorNodeComp>
        my_quene;

    /**
     * @name:   outputHelper
     * @brief:  get the top 4th actor in priority queue in linkpredictor
     */
    void outputHelper(my_quene& quene_res, vector<vector<string>>& result);

    /**
     * @name:   updatePQ
     * @brief:  update priority Queue in linkpredictor
     */
    void updatePQ(ActorNode*& candiate, my_quene& quene_res);
    
    /**
     * @name:   levelBFS
     * @brief:  help function for linkprdictor that achieve first level BFS and
     * second level BFS
     */
    void levelBFS(string& source, unordered_map<string, ActorNode*>& firstlevel,
                  unordered_map<string, ActorNode*>& secondlevel);

  public:
    // all the actor and movie
    unordered_map<string, ActorNode*> actor_map;
    unordered_map<string, MovieNode*> movie_map;

    stack<pair<string, string>> result;  // store result : actor -- movie
    unordered_map<ActorNode*, ActorNode*> actor_set;  // store actor_set for MST
    unordered_map<ActorNode*, int> actor_rank;  // store actor_rank for MST
    priority_queue<Edge, vector<Edge>, EdgeComp> edge;  // store all the edge

    /* Constructor that initialize a Actor */
    Actor() {}

    /* deconstructor for Actor */
    ~Actor();

    /**
     * @name:   unweightedPathfinder
     * @brief:  BFS for unweighted graph to achieve pathfinder
     */
    void unweightedPathfinder(string& source, string& target);

    /**
     * @name:   weightedPathfinder
     * @brief:  BFS for weighted graph to achieve pathfinder
     */
    void weightedPathfinder(string& source, string& target);

    /**
     * @name:   linkpredictor
     * @brief:  acheieve linkpredictor based on the input data and undirected
     * graph
     */
    void linkpredictor(vector<string>& input, vector<vector<string>>& res1,
                       vector<vector<string>>& res2);

    /**
     * @name:   clear
     * @brief:  clear all the variable's distance,isDone,priority and pre
     * pointer
     */
    void clear();
};

#endif