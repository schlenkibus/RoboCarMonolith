#pragma once

#include <algorithm>

class RoboPosition {
public:
    class Direction {
    public:
        void left() {
            rot -= 1;
            if(rot < 0)
                rot = 3;
        }
        void right() {
            rot += 1;
            if(rot > 3)
                rot = 0;
        }
        void turn() {
            left();
            left();
        }
        int rot = 0;
    };

    RoboPosition(int nodeNum, Direction d) : currentNode{nodeNum}, relativeRotationFromStart{d}, targetNode{-99} {
    }

    int currentNode;
    int targetNode;
    Direction relativeRotationFromStart;
};
