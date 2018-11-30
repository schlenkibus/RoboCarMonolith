#include "MazeGrapherModule.h"
#include "data/MazeGraph.h"

MazeGrapherModule::MazeGrapherModule(const std::string &pathToImage) : imagePath{pathToImage} {
}

MazeGraph MazeGrapherModule::createGraphFromImage() {
    return MazeGraph(getText());
}

std::vector<std::string> MazeGrapherModule::getText() {
    return std::vector<std::string>();
}

std::vector<std::string> MazeGrapherModule::mockGraph() {
    return {
            "count - 6",
            "start - 1",
            "end - 6",
            "1-5,1,0",
            "5-4,5,3",
            "5-3,1,1",
            "5-2,5,0",
            "2-6,1,0"
    };
}
