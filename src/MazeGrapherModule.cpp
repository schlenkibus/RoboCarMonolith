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
