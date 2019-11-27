#include <gtest/gtest.h>
#include <string>
#include <unordered_map>
#include <vector>
#include "Actor.hpp"
#include "ActorGraph.hpp"
#include "ActorNode.hpp"
#include "DisjointSet.hpp"
#include "MovieNode.hpp"
using namespace std;
using namespace testing;

TEST(DISJOINTSET_TEST, SIMPLE_TEST) {
    Actor at;
    ActorGraph ag;
    ASSERT_EQ(ag.loadFromFile("../test/data/imdb_small_sample.tsv", true, at),
              true);
    DisjointSet ds;
    ActorNode* node1;
    ActorNode* node2;
    vector<Edge> e;
    int total = ds.MST(at, e);
    ASSERT_EQ(total, 20);
    ag.writeTravelerFile("../test/data/output.tsv", e, total);
    cout << endl;
}