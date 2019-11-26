/*
 * @Descripttion: Implement pathfinder to work on an unweighted graph and
 * weighted graph for PA4
 * @version: 1.0
 * @Author: Kaixin Lin
 */
#include <stack>
#include <string>
#include <unordered_map>
#include "Actor.hpp"
#include "ActorGraph.hpp"
#include "ActorNode.hpp"
#include "MovieNode.hpp"
#include "cxxopts.hpp"
using namespace std;
/* Main program that runs the pathfinder */
int main(int argc, char** argv) {
    cxxopts::Options options("./pathfinder", "pathfinder files");
    options.positional_help(
        "./source_file u/v ./path_to_input_file ./path_to_output_file");
    string sourceFileName, inFileName, outFileName;
    char flag;
    options.allow_unrecognised_options().add_options()(
        "source", "", cxxopts::value<string>(sourceFileName))(
        "flag", "", cxxopts::value<char>(flag))(
        "input", "", cxxopts::value<string>(inFileName))(
        "output", "", cxxopts::value<string>(outFileName))(
        "h,help", "Print help and exit");
    options.parse_positional({"source", "flag", "input", "output"});
    auto userOptions = options.parse(argc, argv);
    ActorGraph ag;
    Actor at;
    vector<pair<string, stack<pair<string, string>>>> res;
    // load file from input Actor data
    ag.readFile(inFileName);
    if (flag == 'u') {
        // unweighted graph
        // load file from dataset
        ag.loadFromFile(sourceFileName.c_str(), false, at);
        // vector<pair<string, stack<pair<string, string>>>> res;
        for (int i = 0; i < ag.input.size(); i++) {
            string src = ag.input[i].first;
            string dst = ag.input[i].second;
            at.unweightedPathfinder(src, dst);
            res.push_back(make_pair(src, at.result));
            at.clear();
        }
        // write result to the file
        ag.writeFile(res, outFileName);
    } else if (flag == 'w') {
        // weighted graph
        // load file from dataset
        ag.loadFromFile(sourceFileName.c_str(), true, at);

        for (int i = 0; i < ag.input.size(); i++) {
            string src = ag.input[i].first;
            string dst = ag.input[i].second;
            at.weightedPathfinder(src, dst);
            res.push_back(make_pair(src, at.result));
            at.clear();
        }
        // write result to the file
        ag.writeFile(res, outFileName);
    }

    return 0;
}