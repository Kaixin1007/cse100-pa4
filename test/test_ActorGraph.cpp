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

TEST(AT_TEST, simple_TEST) {
    Actor at;
    ActorGraph ag;
    ASSERT_EQ(ag.loadFromFile("../test/data/imdb_small_sample.tsv", false, at),
              true);
    ASSERT_EQ(ag.readFile("../test/data/test1.tsv"), true);

    ASSERT_EQ(ag.readActorFile("../test/data/test_actors.tsv"), true);
}