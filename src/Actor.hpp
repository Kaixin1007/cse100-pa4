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
#define OUTPUT_NUMBER 4
class Actor {
  public:
    unordered_map<string, ActorNode*> actor_map;
    unordered_map<string, MovieNode*> movie_map;
    stack<pair<string, string>> result;  // actor -- movie||year
    typedef priority_queue<ActorNode*, vector<ActorNode*>, ActorNodeComp>
        my_quene;

    Actor() {}
    ~Actor();
    void unweightedPathfinder(string& source, string& target);
    void weightedPathfinder(string& source, string& target);
    void levelBFS(string& source, unordered_map<string, ActorNode*>& firstlevel,
                  unordered_map<string, ActorNode*>& secondlevel);
    void linkpredictor(vector<string>& input, vector<vector<string>>& res1,
                       vector<vector<string>>& res2);

       void outputHelper(my_quene& quene_res, vector<vector<string>>& result);
    void updatePQ(ActorNode*& candiate, my_quene& quene_res);
    void clear();

    // void clearPriority(string source);
};

#endif