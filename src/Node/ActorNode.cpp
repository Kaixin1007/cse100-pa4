#include "ActorNode.hpp"
#include <vector>
#include "MovieNode.hpp"

// ActorNode::~ActorNode() {
//     for (auto e : movies) {
//         for (auto i : e.second) delete (i);
//     }
//     delete (prev.second);

//     // vector<MovieNode*>().swap(movies);
//     // for (auto e : movies) {
//     //     delete (e);
//     //     // pair<string, vector<ActorNode*>> temp = movies.back();
//     //     // while (!temp.second.empty()) {
//     //     //     delete (temp.second.back());
//     //     // }
//     // }
// }
// MovieNode::~MovieNode() {
//     // vector<ActorNode*>().swap(actors);
//     while (!actors.empty()) delete (actors.back());
//     // if (prev) delete (prev);
// }