
#include <string>
#include <vector>
#include <set>
#include "../RoboPosition.h"

class MazeGraph {
public:
    MazeGraph(std::vector<std::string> textualRepresenation);
    struct Node {
        int id;
    };
    std::vector<Node> m_nodes;
    std::vector<std::tuple<int, int, int, int>> m_edges;
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