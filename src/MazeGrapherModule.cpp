#include <fstream>
#include <iostream>
#include "MazeGrapherModule.h"
#include "data/MazeGraph.h"
#include "util/ErrorCodes.h"

MazeGrapherModule::MazeGrapherModule(const std::string &pathToImage) : imagePath{pathToImage} {
}

MazeGraph MazeGrapherModule::createGraphFromImage() {
    return MazeGraph(getText());
}

std::vector<std::string> MazeGrapherModule::getText() {
    if(std::ifstream is(imagePath); is.is_open()) {
        std::vector<std::string> ret;
        std::string line;
        while(std::getline(is, line)) {
            if(line.find("count") != line.npos ||
                line.find("start") != line.npos ||
                line.find("end") != line.npos) {
                ret.emplace_back(line);
            } else {
                if(line.size() <= 0)
                    continue;
                auto lastComma = line.find_last_of(',');
                //Wenn Modul benutzt wird!
                auto lineWithoutRot = line.substr(0, lastComma + 1);
                auto rot = line.substr(lastComma + 1);
                signed int newRot = 0;
                switch(std::stoi(rot)) {
                    case 3:
                        newRot = 1;
                        break;
                    case 2:
                        newRot = 0;
                        break;
                    case 1:
                        newRot = 3;
                        break;
                    case 0:
                        newRot = 2;
                        break;
                    default:
                        exit(ErrorCodes::i(ErrorCodes::LogicError::IncorrectDirection));
                }
                ret.emplace_back(lineWithoutRot + std::to_string(newRot));
            }
        }
        return ret;
    } else {
        std::cerr << "Could not Open Image\n";
        exit(ErrorCodes::i(ErrorCodes::FileError::CantOpen));
    }
}

std::vector<std::string> MazeGrapherModule::mockGraph() {
    return {
        "count - 11",
        "start - 1",
        "end - 11",
        "1-2,2,0",
        "2-3,10,1",
        "2-5,4,3",
        "3-4,1,0",
        "4-9,2,0",
        "9-8,1,3",
        "5-6,6,0",
        "6-7,3,1",
        "6-10,3,0",
        "10-8,2,1",
        "8-11,2,0"
    };


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
