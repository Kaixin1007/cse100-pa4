/*
 * ActorGraph.cpp
 * Author: Kaixin Lin
 * Date:   2019.11.26
 *
 * This file is meant to exist as a container for starter code that you can use
 * to read the input file format defined in imdb_2019.tsv. Feel free to modify
 * any/all aspects as you wish.
 */

#include "ActorGraph.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
#include "Edge.hpp"
using namespace std;

/**
 * Constructor of the Actor graph
 */
ActorGraph::ActorGraph(void) {}

/** You can modify this method definition as you wish
 *
 * Load the graph from a tab-delimited file of actor->movie relationships.
 *
 * in_filename - input filename
 * use_weighted_edges - if true, compute edge weights as 1 + (2019 -
 * movie_year), otherwise all edge weights will be 1
 *
 * return true if file was loaded sucessfully, false otherwise
 */
bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges,
                              Actor& ac) {
    // Initialize the file stream
    ifstream infile(in_filename);
    // infile.open(in_filename, ios::binary);
    bool have_header = false;
    // cout << "0" << infile.eof() << endl;
    // keep reading lines until the end of file is reached
    while (infile) {
        string s;
        // get the next line
        if (!getline(infile, s)) break;

        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }

        istringstream ss(s);
        vector<string> record;

        while (ss) {
            string str;

            // get the next string before hitting a tab character and put it in
            // 'str'
            if (!getline(ss, str, '\t')) break;
            record.push_back(str);
        }

        if (record.size() != 3) {
            // we should have exactly 3 columns
            continue;
        }

        string actor(record[0]);
        string movie_title(record[1]);
        int year = stoi(record[2]);

        string str = movie_title + "#@" + record[2];
        // if the actor isn't in actor_map, update
        if (ac.actor_map.find(actor) == ac.actor_map.end()) {
            ActorNode* node = new ActorNode(actor);
            ac.actor_map.insert(make_pair(actor, node));
        }
        // if the movie isn't in movie_map, update
        if (ac.movie_map.find(str) == ac.movie_map.end()) {
            MovieNode* node = new MovieNode(str, year);
            ac.movie_map.insert(make_pair(str, node));
        }

        auto curActor = ac.actor_map.find(actor);
        auto curMovie = ac.movie_map.find(str);

        int weight = 1 + 2019 - year;
        // initialize the actor_set and actor_rank for MST
        ac.actor_set.insert(make_pair(curActor->second, nullptr));
        ac.actor_rank.insert(make_pair(curActor->second, 0));

        for (ActorNode* nodeInMovie : curMovie->second->actors) {
            // undirected graph, let the weight = 1
            if (!use_weighted_edges) {
                Edge e =
                    Edge(curActor->second, nodeInMovie, curMovie->second, 1);
                nodeInMovie->edges.push_back(e);
                curActor->second->edges.push_back(e);
            } else {
                // directed graph
                Edge e = Edge(curActor->second, nodeInMovie, curMovie->second,
                              weight);
                nodeInMovie->edges.push_back(e);
                curActor->second->edges.push_back(e);
                ac.edge.push(e);
            }
        }
        curMovie->second->actors.push_back(curActor->second);
    }
    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    return true;
}

/**
 * @name:   writeFile
 * @brief:  write result to the file in pathfinder according to the required
 * format
 */
void ActorGraph::writeFile(
    vector<pair<string, stack<pair<string, string>>>>& result,
    string filename) {
    ofstream out;
    out.open(filename, ios::binary);
    out << "(actor)--[movie#@year]-->(actor)--..." << endl;
    for (auto it : result) {
        if (!it.second.empty()) {
            string src = it.first;
            out << "(" << src << ")--";
        } else {
            out << endl;
            continue;
        }
        while (!(it.second.empty())) {
            pair<string, string> temp = it.second.top();
            it.second.pop();
            out << "[" << temp.second << "]-->"
                << "(" << temp.first << ")";
            if (!(it.second.empty())) out << "--";
        }
        out << endl;
    }

    out.close();
}
/**
 * @name:   writeFile
 * @brief:  write result to the file in linkpredictor according to the
 * required format
 */
void ActorGraph::writeFile(vector<vector<string>>& res1,
                           vector<vector<string>>& res2, string filename1,
                           string filename2) {
    ofstream out;
    out.open(filename1, ios::binary);
    out << "Actor1,Actor2,Actor3,Actor4" << endl;
    for (auto it : res1) {
        for (int i = 0; i < it.size(); ++i) {
            out << it[i];
            if (i != (it.size() - 1)) out << "\t";
        }
        out << endl;
    }
    out.close();
    out.open(filename2, ios::binary);
    out << "Actor1,Actor2,Actor3,Actor4" << endl;
    for (auto it : res2) {
        for (int i = 0; i < it.size(); ++i) {
            out << it[i];
            if (i != (it.size() - 1)) out << "\t";
        }
        out << endl;
    }
    out.close();
}
/**
 * @name:   writeTravelerFile
 * @brief:  write result to the file in movietraveler according to the
 * required format
 */
void ActorGraph::writeTravelerFile(string filename, vector<Edge>& edge,
                                   int totalWeight) {
    ofstream out;
    out.open(filename, ios::binary);
    out << "(actor)<--[movie#@year]-->(actor)" << endl;
    for (int i = 0; i < edge.size(); i++) {
        out << "(" << edge[i].actor1->name << ")<--[" << edge[i].movie->name
            << "]-->(" << edge[i].actor2->name << ")" << endl;
    }
    out << "#NODE CONNECTED: " << edge.size() + 1 << endl;
    out << "#EDGE CHOSEN: " << edge.size() << endl;
    out << "TOTAL EDGE WEIGHTS: " << totalWeight << endl;
    out.close();
}
/**
 * @name:   readFile
 * @brief:  read input file for pathfinder according to the required format
 * @return: Return true if file was loaded sucessfully
 */
bool ActorGraph::readFile(string filename) {
    ifstream infile(filename);
    bool have_header = false;
    while (infile) {
        string s;
        // get the next line
        if (!getline(infile, s)) break;

        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }
        istringstream ss(s);
        vector<string> record;
        while (ss) {
            string str;
            // get the next string before hitting a tab character and put it in
            // 'str'
            if (!getline(ss, str, '\t')) break;
            record.push_back(str);
        }

        if (record.size() != 2) {
            // we should have exactly 2 columns
            continue;
        }
        string actor1(record[0]);
        string actor2(record[1]);
        input.push_back(make_pair(actor1, actor2));
    }
    if (!infile.eof()) {
        cerr << "Failed to read " << filename << "!\n";
        return false;
    }
    infile.close();

    return true;
}
/**
 * @name:   readFile
 * @brief:  read input file for linkpredictor according to the required format
 * @return: Return true if file was loaded sucessfully
 */
bool ActorGraph::readActorFile(string filename) {
    ifstream infile(filename);
    bool have_header = false;
    while (infile) {
        string s;
        // get the next line
        if (!getline(infile, s)) break;

        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }

        istringstream ss(s);
        vector<string> record;
        while (ss) {
            string str;
            // get the next string before hitting a tab character and put it in
            // 'str'
            if (!getline(ss, str, '\t')) break;
            record.push_back(str);
        }

        if (record.size() != 1) {
            // we should have exactly 1 columns
            continue;
        }
        string actor1(record[0]);
        actor_input.push_back(actor1);
    }
    if (!infile.eof()) {
        cerr << "Failed to read " << filename << "!\n";
        return false;
    }
    infile.close();

    return true;
}