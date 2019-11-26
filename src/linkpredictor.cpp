#include <stack>
#include <string>
#include <unordered_map>
#include "Actor.hpp"
#include "ActorGraph.hpp"
#include "ActorNode.hpp"
#include "MovieNode.hpp"
#include "cxxopts.hpp"
using namespace std;
int main(int argc, char** argv) {
    cxxopts::Options options("./linkpredictor", "linkpredictor files");
    options.positional_help(
        "./source_file ./path_to_input_file ./path_to_output_collaborated_file "
        "./path_to_output_uncollaborated_file");
    string sourceFileName, inFileName, outFileName1, outFileName2;
    options.allow_unrecognised_options().add_options()(
        "source", "", cxxopts::value<string>(sourceFileName))(
        "input", "", cxxopts::value<string>(inFileName))(
        "output_collaborated", "", cxxopts::value<string>(outFileName1))(
        "output_uncollaborated", "", cxxopts::value<string>(outFileName2))(
        "h,help", "Print help and exit");
    options.parse_positional(
        {"source", "input", "output_collaborated", "output_uncollaborated"});
    auto userOptions = options.parse(argc, argv);

    ActorGraph ag;
    Actor at;
    vector<vector<string>> result, result1;
    ag.loadFromFile(sourceFileName.c_str(), false, at);
    ag.readActorFile(inFileName);
    
    at.linkpredictor(ag.actor_input, result, result1);

    ag.writeFile(result, result1, outFileName1, outFileName2);

    return 0;
}