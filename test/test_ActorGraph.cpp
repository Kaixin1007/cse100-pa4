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

TEST(AT_TEST, simple_TEST) {
    ifstream in;
    Actor at;
    ActorGraph ag;
    vector<pair<string, stack<pair<string, string>>>> res;
    stack<pair<string, string>> temp;
    temp.push(make_pair("abc", "def"));
    res.push_back(make_pair("test", temp));
    ag.writeFile(res, "../test/data/test.tsv");
    in.open("../test/data/test.tsv", ios::binary);
    ASSERT_EQ(in.is_open(), true);
    in.close();

    ASSERT_EQ(ag.loadFromFile("../test/data/imdb_small_sample.tsv", false, at),
              true);
    ASSERT_EQ(ag.readFile("../test/data/test1.tsv"), true);

    ASSERT_EQ(ag.readActorFile("../test/data/test_actors.tsv"), true);
}