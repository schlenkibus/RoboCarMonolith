#include <iostream>
#include <tuple>
#include "MazeGraph.h"

MazeGraph::MazeGraph(std::vector<std::string> textualRepresenation) {
    //Test!
    parseNodeFromLine("0-6,55,2");

    auto it = textualRepresenation.begin();
    parseCount(*it);
    std::advance(it, 1);
    parseStart(*it);
    std::advance(it, 1);
    parseEnd(*it);

    //Remove already parsed lines
    textualRepresenation.erase(textualRepresenation.begin() + 3, textualRepresenation.end());

    m_nodes.reserve(textualRepresenation.size() * 2);
    for(const auto &entry: textualRepresenation) {
       parseNodeFromLine(entry);
    }

    //Remove Duplicate Nodes
    std::set<Node> s( m_nodes.begin(), m_nodes.end() );
    m_nodes.assign( s.begin(), s.end() );
}



int reverseDir(int dir) {
    switch(dir) {
        case 0:
            return 2;
        case 1:
            return 3;
        case 2:
            return 0;
        case 3:
            return 1;
        default:
            std::cerr << "__LINE__ NaN" << std::endl;
            exit(99);
    }
}

void MazeGraph::parseNodeFromLine(const std::string &line) {
    //Oppsie Dooo No Magic happening here
    auto dashDelim = line.find_first_of('-');
    auto firstComma = line.find(',');
    auto secondComma = line.find(',', firstComma);
    auto firstNodeNumber = std::stoi(line.substr(0, dashDelim));
    auto secondNodeNumber = std::stoi(line.substr(dashDelim + 1, firstComma - 2));
    auto edgeLength = std::stoi(line.substr(firstComma + 1, secondComma - 1));
    //SANITIZE ROATATION!!!!
    auto rotation = std::stoi(line.substr(line.find(std::to_string(edgeLength)) + edgeLength.length() + 1));

    m_nodes.emplace_back(Node{firstNodeNumber});
    m_nodes.emplace_back(Node{secondNodeNumber});
    m_edges.emplace_back(Edge(firstNodeNumber, secondNodeNumber, edgeLength, rotation));
    m_edges.emplace_back(Edge(secondNodeNumber, firstNodeNumber, edgeLength, reverseDir(rotation)));
}

void MazeGraph::parseCount(std::string &basic_string) {
    auto delim = basic_string.find_first_of('-') + 1;
    countNodes = std::stoi(basic_string.substr(delim + 1));
}

void MazeGraph::parseEnd(std::string &basic_string) {
    auto delim = basic_string.find_first_of('-') + 1;
    goalId = std::stoi(basic_string.substr(delim + 1));
}

void MazeGraph::parseStart(std::string &basic_string) {
    auto delim = basic_string.find_first_of('-') + 1;
    startId = std::stoi(basic_string.substr(delim + 1));
}

const std::string MazeGraph::toString(int currentId) const {
    std::string text;
    text += "count - ";
    text += std::to_string(countNodes);
    text += "\n";
    text += "start - ";
    text += std::to_string(currentId);
    text += "\n";
    text += "end - ";
    text += std::to_string(goalId);
    text += "\n";
    for(auto edge: m_edges) {
        text += std::to_string(std::get<0>(edge)) + std::string("-") + std::to_string(std::get<1>(edge));
        text += "," + std::to_string(std::get<2>(edge)) + std::string(",") + std::to_string(std::get<3>(edge)) + '\n';
    }
    return text;
}

void MazeGraph::removeEdge(int from, int to) {
    auto it = m_edges.begin();
    for(auto edge: m_edges) {
        if((std::get<0>(edge) == from && std::get<1>(edge) == to) ||
           (std::get<1>(edge) == from && std::get<0>(edge) == to))
            m_edges.erase(it);
        std::advance(it, 1);
    }
}

int MazeGraph::directionOfNodeFromPos(int nodeid, const RoboPosition &pos) const {
    auto currentPos = pos.currentNode;
    for(auto edge: m_edges) {
        if(std::get<0>(edge) == currentPos && std::get<1>(edge) == nodeid) {
            return std::get<3>(edge);
        }
    }
}

int MazeGraph::directionOfNodeFromNode(int nodeid, int targetNode) const {
    for(auto edge: m_edges) {
        if(std::get<0>(edge) == nodeid && std::get<1>(edge) == targetNode) {
            return std::get<3>(edge);
        }
    }
}
