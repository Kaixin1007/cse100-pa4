/*
 * @Descripttion: Actor file to finish Pathfinder, linkpredictor for PA4
 * @version: 1.0
 * @Author: Kaixin Lin
 */
#include "Actor.hpp"
#include <climits>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
/* deconstructor for Actor */
Actor::~Actor() {
    for (auto i = actor_map.begin(); i != actor_map.end(); ++i) {
        delete (i->second);
    }
    for (auto j = movie_map.begin(); j != movie_map.end(); ++j) {
        delete (j->second);
    }
}

/**
 * @name:   weightedPathfinder
 * @brief:  BFS for weighted graph to achieve pathfinder
 */
void Actor::weightedPathfinder(string& source, string& target) {
    if (actor_map.find(source) == actor_map.end() ||
        actor_map.find(target) == actor_map.end())
        return;
    // get source and target actor
    ActorNode* src = actor_map.find(source)->second;
    ActorNode* dst = actor_map.find(target)->second;

    priority_queue<ActorNode*, vector<ActorNode*>, ActorDisComp> toExplore;
    bool Found = false;
    src->dis = 0;
    toExplore.push(src);
    while (!toExplore.empty()) {
        ActorNode* cur = toExplore.top();
        toExplore.pop();
        if (cur->name == target) {
            Found = true;
            break;
        }
        if (!cur->isDone) {
            cur->isDone = true;
            for (Edge edge : cur->edges) {
                ActorNode* another =
                    (cur == edge.actor1) ? edge.actor2 : edge.actor1;
                unsigned int distance = cur->dis + edge.weight;
                if (distance < another->dis) {
                    another->dis = distance;
                    another->preActor = cur;
                    another->preMovie = edge.movie;
                    toExplore.push(another);
                }
            }
        }
    }
    if (Found == true) {
        ActorNode* prev = dst;
        while (prev != src) {
            result.push(make_pair(prev->name, prev->preMovie->name));
            prev = prev->preActor;
        }
    }
}

/**
 * @name:   unweightedPathfinder
 * @brief:  BFS for unweighted graph to achieve pathfinder
 */
void Actor::unweightedPathfinder(string& source, string& target) {
    if (actor_map.find(source) == actor_map.end() ||
        actor_map.find(target) == actor_map.end())
        return;
    // get source and target actor
    ActorNode* src = actor_map.find(source)->second;
    ActorNode* dst = actor_map.find(target)->second;
    queue<ActorNode*> toExplore;
    bool Found = false;

    toExplore.push(src);
    src->dis = 1;
    while (!toExplore.empty()) {
        ActorNode* cur = toExplore.front();
        toExplore.pop();
        if (cur->name == target) {
            Found = true;
            break;
        }

        for (Edge edge : cur->edges) {
            ActorNode* another =
                (cur == edge.actor1) ? edge.actor2 : edge.actor1;
            if (another->dis == INT_MAX) {
                another->dis = 1;
                another->preActor = cur;
                another->preMovie = edge.movie;
                toExplore.push(another);
            }
        }
    }
    if (Found == true) {
        ActorNode* prev = dst;
        while (prev != src) {
            result.push(make_pair(prev->name, prev->preMovie->name));
            prev = prev->preActor;
        }
    }
}

/**
 * @name:   clear
 * @brief:  clear all the variable's distance,isDone,priority and pre pointer
 */
void Actor::clear() {
    for (auto it : actor_map) {
        ActorNode* temp = it.second;
        if (temp->dis != INT_MAX) {
            temp->dis = INT_MAX;
            temp->preActor = nullptr;
            temp->preMovie = nullptr;
            temp->priority = 0;
            temp->isDone = false;
        }
    }
    while (!result.empty()) {
        result.pop();
    }
}

/**
 * @name:   levelBFS
 * @brief:  help function for linkprdictor that achieve first level BFS and
 * second level BFS
 */
void Actor::levelBFS(string& source,
                     unordered_map<string, ActorNode*>& firstlevel,
                     unordered_map<string, ActorNode*>& secondlevel) {
    queue<ActorNode*> toExplore;
    if (actor_map.find(source) == actor_map.end()) return;
    ActorNode* src = actor_map.find(source)->second;
    src->dis = 1;
    // 1st level BFS
    for (Edge edge : src->edges) {
        ActorNode* another = (src == edge.actor1) ? edge.actor2 : edge.actor1;
        firstlevel.insert(make_pair(another->name, another));
        toExplore.push(another);
        another->dis = 1;
    }
    // 2rd level BFS
    while (!toExplore.empty()) {
        ActorNode* cur = toExplore.front();
        toExplore.pop();
        for (Edge edge : cur->edges) {
            ActorNode* another =
                (cur == edge.actor1) ? edge.actor2 : edge.actor1;
            if (another->dis == INT_MAX)
                secondlevel.insert(make_pair(another->name, another));
        }
    }
}

/**
 * @name:   outputHelper
 * @brief:  get the top 4th actor in priority queue in linkpredictor
 */
void Actor::outputHelper(my_quene& quene_res, vector<vector<string>>& result) {
    vector<string> collaborated;
    int size = quene_res.size();
    stack<string> temp1;
    for (int i = size - 1; i >= 0; i--) {
        temp1.push(quene_res.top()->name);
        quene_res.pop();
    }
    while (!temp1.empty()) {
        collaborated.push_back(temp1.top());
        temp1.pop();
    }
    result.push_back(collaborated);
}

/**
 * @name:   updatePQ
 * @brief:  update priority Queue in linkpredictor
 */
void Actor::updatePQ(ActorNode*& candiate, my_quene& quene_res) {
    bool update = false;
    if (quene_res.size() < OUTPUT_NUMBER) {
        quene_res.push(candiate);
    } else {
        ActorNode* temp = quene_res.top();
        if (candiate->priority > temp->priority) {
            update = true;
        } else if (candiate->priority == temp->priority) {
            if (candiate->name < temp->name) update = true;
        }
        if (update) {
            quene_res.pop();
            quene_res.push(candiate);
        }
    }
}

/**
 * @name:   linkpredictor
 * @brief:  acheieve linkpredictor based on the input data and undirected graph
 */
void Actor::linkpredictor(vector<string>& input, vector<vector<string>>& res1,
                          vector<vector<string>>& res2) {
    string source;
    my_quene collaborated_res, uncollaborated_res;
    int commonCast = 0;
    queue<ActorNode*> toExplore;
    // for collaborated actor
    for (auto it : input) {
        source = it;
        // get first level and second level
        unordered_map<string, ActorNode*> firstlevel;
        unordered_map<string, ActorNode*> secondlevel;
        levelBFS(source, firstlevel, secondlevel);

        if (actor_map.find(source) == actor_map.end()) continue;

        ActorNode* src = actor_map.find(source)->second;

        for (auto it : firstlevel) {  // node == candiate
            ActorNode* candiate = it.second;

            for (Edge CandiateEdge : candiate->edges) {
                // cast point
                ActorNode* another = (candiate == CandiateEdge.actor1)
                                         ? CandiateEdge.actor2
                                         : CandiateEdge.actor1;

                // if it can build up triangluar
                if (firstlevel.find(another->name) != firstlevel.end()) {
                    ActorNode* castPoint =
                        firstlevel.find(another->name)->second;
                    for (Edge e : castPoint->edges) {
                        ActorNode* anothercastPoint =
                            (castPoint == e.actor1) ? e.actor2 : e.actor1;
                        if (anothercastPoint == src) {
                            commonCast++;
                        }
                    }
                    candiate->priority += commonCast;
                }
                commonCast = 0;
            }
            // update priority queue
            updatePQ(candiate, collaborated_res);
        }
        // get the top 4 actor
        outputHelper(collaborated_res, res1);
        // clear the variable in first level
        src->dis = INT_MAX;
        for (Edge edge : src->edges) {
            ActorNode* another =
                (src == edge.actor1) ? edge.actor2 : edge.actor1;
            another->priority = 0;
            toExplore.push(another);
            another->dis = INT_MAX;
        }
        // for uncollaborated actor
        for (auto it : secondlevel) {
            ActorNode* candiate = it.second;
            for (Edge CandiateEdge : candiate->edges) {
                // cast point
                ActorNode* another = (candiate == CandiateEdge.actor1)
                                         ? CandiateEdge.actor2
                                         : CandiateEdge.actor1;
                // in 1st level
                if (firstlevel.find(another->name) != firstlevel.end()) {
                    ActorNode* castPoint =
                        firstlevel.find(another->name)->second;
                    for (Edge e : castPoint->edges) {
                        ActorNode* anothercastPoint =
                            (castPoint == e.actor1) ? e.actor2 : e.actor1;

                        if (anothercastPoint == src) commonCast++;
                    }
                    candiate->priority += commonCast;
                }
                commonCast = 0;
            }
            updatePQ(candiate, uncollaborated_res);
        }
        outputHelper(uncollaborated_res, res2);

        while (!toExplore.empty()) {
            ActorNode* cur = toExplore.front();
            toExplore.pop();
            for (Edge edge : cur->edges) {
                ActorNode* another =
                    (cur == edge.actor1) ? edge.actor2 : edge.actor1;
                if (another->dis != INT_MAX) another->dis = INT_MAX;
                another->priority = 0;
            }
        }
    }
}
