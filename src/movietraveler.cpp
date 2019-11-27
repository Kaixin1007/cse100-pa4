#include <stack>
#include <string>
#include <unordered_map>
#include "Actor.hpp"
#include "ActorGraph.hpp"
#include "ActorNode.hpp"
#include "DisjointSet.hpp"
#include "MovieNode.hpp"
#include "cxxopts.hpp"
int main(int argc, char** argv) {
    cxxopts::Options options("./movietraveler", "movietraveler files");
    options.positional_help("./source_file ./path_to_output_file");
    string sourceFileName, outFileName;
    options.allow_unrecognised_options().add_options()(
        "source", "", cxxopts::value<string>(sourceFileName))(
        "output", "", cxxopts::value<string>(outFileName))(
        "h,help", "Print help and exit");
    options.parse_positional({"source", "output"});
    auto userOptions = options.parse(argc, argv);
    ActorGraph ag;
    Actor at;
    DisjointSet ds;
    vector<Edge> e;
    ag.loadFromFile(sourceFileName.c_str(), true, at);
    int total = ds.MST(at, e);
    ag.writeTravelerFile(outFileName, e, total);
    return 0;
}