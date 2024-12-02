// include/schmoo.hpp
#pragma once
#include <random>
#include <cmath>
#include <utility>

class SchmooGame {
private:
    int shots;
    int turn;
    int x, y;
    std::mt19937 rng;
    int requiredShots;
    bool isGameOver;
    
    void generatePosition();
    double calculateDistance(double x1, double y1);

public:
    SchmooGame();
    bool makeShot(double elevation, double angle, double& hitX, double& hitY);
    std::pair<int,int> getPosition() const { return {x, y}; }
    int getShotCount() const { return shots; }
    bool isOver() const { return isGameOver; }
    void reset();
};