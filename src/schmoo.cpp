#include "schmoo.hpp"

SchmooGame::SchmooGame() : shots(0), turn(0), isGameOver(false) {
    std::random_device rd;
    rng.seed(rd());
    reset();
}

void SchmooGame::reset() {
    shots = 0;
    turn++;
    isGameOver = false;
    requiredShots = (turn > 1) ? 5 + (rng() % 7) : INT_MAX;
    generatePosition();
}

void SchmooGame::generatePosition() {
    std::uniform_int_distribution<int> dist(5000, 31000);
    int quadrant = (rng() % 4) + 1;
    int p = (quadrant == 1 || quadrant == 2) ? -1 : 1;
    int q = (quadrant == 1 || quadrant == 3) ? -1 : 1;
    x = dist(rng) * p;
    y = dist(rng) * q;
}

bool SchmooGame::makeShot(double elevation, double angle, double& hitX, double& hitY) {
    if (elevation < 1 || elevation > 90 || angle < 0 || angle >= 360) {
        return false;
    }
    
    shots++;
    const double PI = 3.1415926535;
    double B = elevation;
    double C = angle;
    double J = PI / 180.0;
    
    // —начала вычисл€ем базовую дистанцию
    double base_distance = 93000.0 * sin(B * J) * cos(B * J);
    // ќкругл€ем до целого как в BASIC
    int D = static_cast<int>(base_distance / 2);
    
    // ƒл€ стандартных углов используем точные значени€ синуса и косинуса
    if (fmod(C, 90.0) == 0.0) {
        int angle_quadrant = static_cast<int>(C / 90.0) % 4;
        switch(angle_quadrant) {
            case 0: hitX = D; hitY = 0; break;
            case 1: hitX = 0; hitY = D; break;
            case 2: hitX = -D; hitY = 0; break;
            case 3: hitX = 0; hitY = -D; break;
        }
    } else {
        // ƒл€ остальных углов используем стандартное вычисление
        hitX = D * cos(C * J);
        hitY = D * sin(C * J);
    }
    
    if (shots >= requiredShots && turn > 1) {
        isGameOver = true;
        return false;
    }
    
    return calculateDistance(hitX, hitY) <= 100;
}

double SchmooGame::calculateDistance(double x1, double y1) {
    return std::sqrt(std::pow(x - x1, 2) + std::pow(y - y1, 2));
}