#include "DisjointSet.hpp"
#include "Actor.hpp"
#include "ActorNode.hpp"
#include "Edge.hpp"
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
void DisjointSet::Union(ActorNode*& node1, ActorNode*& node2, Actor& actor) {
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
            actor.actor_set.find(sentinel_b)->second = sentinel_a;
            actor.actor_rank.find(sentinel_a)->second += 1;
        }
    }
}
void DisjointSet::pathCompression(vector<ActorNode*>& path,
                                  ActorNode*& sentinel, Actor& actor) {
    for (ActorNode* node : path) {
        actor.actor_set.find(node)->second = sentinel;
    }
}
int DisjointSet::MST(Actor& actor, vector<Edge>& edge) {
    int index = 0, totalWeight = 0;
    while (index < actor.actor_map.size() && (!actor.edge.empty())) {
        Edge next_edge = actor.edge.top();
        actor.edge.pop();
        ActorNode* x = find(next_edge.actor1, actor);
        ActorNode* y = find(next_edge.actor2, actor);
        if (x != y) {
            edge.push_back(next_edge);
            Union(x, y, actor);
            index++;
            totalWeight += next_edge.weight;
        }
    }
    return totalWeight;
}