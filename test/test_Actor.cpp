#include <gtest/gtest.h>
#include <string>
#include <unordered_map>
#include <vector>
#include "Actor.hpp"
#include "ActorGraph.hpp"
#include "ActorNode.hpp"
#include "MovieNode.hpp"
using namespace std;
using namespace testing;
TEST(ACTORtest, ACTORGRAPH_TEST) {
    // Actor at;
    // ActorGraph ag;
    // ASSERT_EQ(ag.loadFromFile("imdb_small_sample.tsv", false, at), true);
    // ASSERT_EQ(ag.readFile("../data/test1.tsv"), true);
}
TEST(ACTORtest, SIMPLE_TEST) {
    Actor at;
    ActorGraph ag;

    //
    ActorNode* temp = new ActorNode("1");
    ActorNode* temp1 = new ActorNode("2");
    MovieNode* movie = new MovieNode("test", 2000);
    Edge e = Edge(temp, temp1, movie, 1);
    temp->edges.push_back(e);
    temp1->edges.push_back(e);
    at.actor_map.insert(make_pair("1", temp));
    at.actor_map.insert(make_pair("2", temp1));
    at.movie_map.insert(make_pair("test#@2000", movie));
    string temp2 = "1", temp3 = "2";
    at.unweightedPathfinder(temp2, temp3);
    ASSERT_EQ(at.result.top().first, "2");
    at.clear();
    ASSERT_EQ(at.result.size(), 0);
    // at.unweightedPathfinder(src, dst);
    // ASSERT_EQ(at.result.top().first, "Chris Evans");
    // MovieNode* m = new MovieNode("sdf", 1996);
}