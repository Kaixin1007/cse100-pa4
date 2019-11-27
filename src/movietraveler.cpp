/*
 * @Descripttion:  it solve the movie traveler problem by finding a minimum
 * spanning tree using Kruskal's algorithm. Aslo, it implement union find data
 * structure with path compression and union by size/height to help you in
 * Kruskal's.
 * @version: 1.0
 * @Author: Kaixin Lin
 */
#include <stack>
#include <string>
#include <unordered_map>
#include "Actor.hpp"
#include "ActorGraph.hpp"
#include "ActorNode.hpp"
#include "DisjointSet.hpp"
#include "MovieNode.hpp"
#include "cxxopts.hpp"

/* Main program that runs the movietraveler */
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
    // load file from dataset
    ag.loadFromFile(sourceFileName.c_str(), true, at);
    // MST
    int total = ds.MST(at, e);
    // write result to the file
    ag.writeTravelerFile(outFileName, e, total);
    return 0;
}