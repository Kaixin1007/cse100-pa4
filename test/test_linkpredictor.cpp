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
TEST(LINKPREDICTOR_TEST, simple_TEST) {
    Actor at;
    ActorGraph ag;
    vector<vector<string>> result, result1;
    ag.loadFromFile("../test/data/imdb_small_sample.tsv", false, at);
    vector<string> input;
    input.push_back("Kevin Bacon");
    at.linkpredictor(input, result, result1);
    ASSERT_EQ(result1[0].front(), "Katherine Waterston");

    // vector<string> res = result1[0];
    // ASSERT_EQ(res, "James McAvoy");
    // input.push_back("Michael Fassbender");
    // at.linkpredictor(input, result, result1);
    // ASSERT_EQ(result[1][0], "James McAvoy");
}