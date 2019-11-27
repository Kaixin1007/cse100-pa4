#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
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
    ifstream in;
    vector<vector<string>> result, result1;
    ag.loadFromFile("../test/data/imdb_middle_sample.tsv", false, at);
    vector<string> input;
    input.push_back("Kevin Bacon");
    at.linkpredictor(input, result, result1);
    ASSERT_EQ(result1[0].front(), "DeForest Kelley");

    ag.writeFile(result, result1, "../test/data/out1.tsv",
                 "../test/data/out2.tsv");
    in.open("../test/data/out1.tsv", ios::binary);
    ASSERT_EQ(in.is_open(), true);
    in.close();
}