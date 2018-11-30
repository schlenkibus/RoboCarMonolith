#pragma once

#include <string>
#include <vector>
#include <set>
#include "../RoboPosition.h"

class MazeGraph {
public:
    explicit MazeGraph(std::vector<std::string> textualRepresenation);
    struct Node {
        int id;
        friend bool operator< (const Node& lhs, const Node& rhs){
            return lhs.id < rhs.id;
        }
    };
    struct Edge {
        Edge(int f, int t, int l, int d) : from(f), to{t}, len{l}, dir{d} {
        }
        int from;
        int to;
        int len;
        int dir;
    };
    std::vector<Node> m_nodes;
    std::vector<Edge> m_edges;
    void removeEdge(int from, int to);
    int countNodes;
    int startId;
    int goalId;
    const std::string toString(int currentId) const;
    int directionOfNodeFromPos(int nodeid, const RoboPosition& pos) const;
    int directionOfNodeFromNode(int nodeid, int targetNode) const;

    //m_edges.emplace_back(Edge(firstNodeNumber, secondNodeNumber, edgeLength, rotation));
protected:
    void parseNodeFromLine(const std::string& line);
    void parseCount(std::string &basic_string);
    void parseEnd(std::string &basic_string);
    void parseStart(std::string &basic_string);
};