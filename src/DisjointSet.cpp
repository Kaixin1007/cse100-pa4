/*
 * @Descripttion: Achieve Disjoint Set DST for MST and movietravel in graph
 * @version: 1.0
 * @Author: Kaixin Lin
 */
#include "DisjointSet.hpp"
#include "Actor.hpp"
#include "ActorNode.hpp"
#include "Edge.hpp"
/* find the root node */
ActorNode* DisjointSet::find(ActorNode*& toFind, Actor& actor) {
    ActorNode* temp = toFind;
    vector<ActorNode*> path;
    auto it = actor.actor_set.find(temp);
    while (it != actor.actor_set.end() && it->second != nullptr) {
        path.push_back(temp);
        temp = it->second;
        it = actor.actor_set.find(temp);
    }
    pathCompression(path, temp, actor);
    return temp;
}
/* Unions two sets of ActorNode */
void DisjointSet::Union(ActorNode*& node1, ActorNode*& node2, Actor& actor) {
    // find the root for node1 and node2
    ActorNode* sentinel_a = find(node1, actor);
    ActorNode* sentinel_b = find(node2, actor);
    if (sentinel_a != sentinel_b) {
        if (actor.actor_rank.find(sentinel_a)->second >
            actor.actor_rank.find(sentinel_b)->second) {
            actor.actor_set.find(sentinel_b)->second = sentinel_a;
        } else if (actor.actor_rank.find(sentinel_a)->second <
                   actor.actor_rank.find(sentinel_b)->second) {
            actor.actor_set.find(sentinel_a)->second = sentinel_b;
        } else {
            // update rank
            actor.actor_set.find(sentinel_b)->second = sentinel_a;
            actor.actor_rank.find(sentinel_a)->second += 1;
        }
    }
}
/* Achieve path compression during find operation for disjoint set */
void DisjointSet::pathCompression(vector<ActorNode*>& path,
                                  ActorNode*& sentinel, Actor& actor) {
    for (ActorNode* node : path) {
        // points to the root
        actor.actor_set.find(node)->second = sentinel;
    }
}
/* Achieve MST in graph using disjoint Set, it return totalWeight in MST */
int DisjointSet::MST(Actor& actor, vector<Edge>& edge) {
    int index = 0, totalWeight = 0;
    while (index < actor.actor_map.size() && (!actor.edge.empty())) {
        // get the smallest edge for priority queue
        Edge next_edge = actor.edge.top();
        actor.edge.pop();
        ActorNode* x = find(next_edge.actor1, actor);
        ActorNode* y = find(next_edge.actor2, actor);
        // if x and y is different sets
        if (x != y) {
            // update edge
            edge.push_back(next_edge);
            // union two set
            Union(x, y, actor);
            // update index
            index++;
            totalWeight += next_edge.weight;
        }
    }
    return totalWeight;
}