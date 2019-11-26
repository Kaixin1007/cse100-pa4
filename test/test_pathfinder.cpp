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

TEST(PATHFINDER_TEST, simple_TEST) {
    Actor at;
    ActorGraph ag;
    ASSERT_EQ(ag.loadFromFile("../test/data/imdb_small_sample.tsv", true, at),
              true);
    string src = "Kevin Bacon";
    string dst = "James McAvoy";
    at.weightedPathfinder(src, dst);
    ASSERT_EQ(at.result.top().first, "James McAvoy");
}