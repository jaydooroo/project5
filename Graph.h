//
// Created by ejh61 on 12/6/2021.
//

#ifndef PROJECT4_GRAPH_H
#define PROJECT4_GRAPH_H
#include <map>
#include <set>
#include <vector>

class Graph {
private:
    std::map<int,std::set<int>> edges;

public:
    Graph(std::map<int, std::set<int>> graph) {
        edges = graph;
    }
    Graph() {}
    ~ Graph () {}
    void setGraph (int index, std::set<int> list) {   // index(int) 와 set<int> list 만 만들어서 입력
        std::pair<int, std::set<int>> tempPair(index, list);
        edges.insert(tempPair);
    }

    std::set<int> &getEdge (int index) {
        return edges[index];
    }

    std::map<int,std::set<int>> &getGraph () {
        return edges;
    }

    Graph reverseGraph();

};


#endif //PROJECT4_GRAPH_H
