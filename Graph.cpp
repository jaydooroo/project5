//
// Created by ejh61 on 12/6/2021.
//

#include "Graph.h"

Graph Graph::reverseGraph() {
    std::map<int,std::set<int>> reverseGraph;

    for(unsigned int i = 0; i < edges.size(); i++) {
        std::set<int> adjacency;
        for(unsigned int j = 0; j < edges.size(); j++) {
           for(int elem: edges[j]){
               if(elem == (int)i){
                   adjacency.insert(j);
               }
           }
        }
        reverseGraph.insert(std::pair<int, std::set<int>> (i,adjacency));
    }
    return reverseGraph;
}

