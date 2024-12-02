// include/console_interface.hpp
#pragma once
#include "schmoo.hpp"
#include <iostream>
#include <iomanip>

class ConsoleInterface {
private:
    SchmooGame game;
    
public:
    void run() {
        std::cout << "\n=== SCHMOO GAME ===\n\n";
        std::cout << "Try to hit the Schmoo with mud balls!\n\n";
        
        while (true) {
            auto [x, y] = game.getPosition();
            std::cout << "\nSchmoo position: (" << x << "," << y << ")\n";
            
            double elevation, angle;
            std::cout << "Enter elevation (1-90): ";
            std::cin >> elevation;
            std::cout << "Enter angle (0-360): ";
            std::cin >> angle;
            
            double hitX, hitY;
            bool hit = game.makeShot(elevation, angle, hitX, hitY);
            
            if (hit) {
                std::cout << "\nHit! Shots taken: " << game.getShotCount() << "\n";
                std::cout << "\nPlay again? (y/n): ";
                char choice;
                std::cin >> choice;
                if (choice != 'y' && choice != 'Y') break;
                game.reset();
            } else if (game.isOver()) {
                std::cout << "\nGame Over! The Schmoo has won!\n";
                break;
            } else {
                std::cout << "Miss! Your mud hit at (" 
                         << std::fixed << std::setprecision(1) 
                         << hitX << "," << hitY << ")\n";
            }
        }
    }
};