#pragma once

#include <string>
#include "data/MazeGraph.h"

class MazeGrapherModule {
public:
    explicit MazeGrapherModule(const std::string& pathToImage);
    MazeGraph createGraphFromImage();
    std::vector<std::string> getText();
protected:
    std::string imagePath;
};
