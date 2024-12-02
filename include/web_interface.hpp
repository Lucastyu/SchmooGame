// include/web_interface.hpp
#pragma once
#include "schmoo.hpp"
#include <SDL2/SDL.h>
#include <emscripten.h>
#include <emscripten/html5.h>

class WebInterface {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SchmooGame game;
    float inputElevation;
    float inputAngle;
    double lastHitX, lastHitY;
    bool lastShotMissed;

    void drawGrid() {
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        for(int i = 0; i < 800; i += 50) {
            SDL_RenderDrawLine(renderer, i, 0, i, 600);
            SDL_RenderDrawLine(renderer, 0, i, 800, i);
        }
    }

    void drawSchmoo() {
        auto [x, y] = game.getPosition();
        int screenX = 400 + (x / 200);
        int screenY = 300 - (y / 200);
        
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_Rect schmooRect = {screenX-5, screenY-5, 10, 10};
        SDL_RenderFillRect(renderer, &schmooRect);
    }

public:
    WebInterface() : window(nullptr), renderer(nullptr),
                    inputElevation(45.0f), inputAngle(0.0f),
                    lastShotMissed(false) {}

    ~WebInterface() {
        if (renderer) SDL_DestroyRenderer(renderer);
        if (window) SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void init() {
        SDL_Init(SDL_INIT_VIDEO);
        SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer);
        
        // Создание HTML элементов управления
        EM_ASM(
            var controls = document.createElement('div');
            controls.innerHTML = `
                <div style="position: absolute; top: 10px; left: 10px; background: rgba(255,255,255,0.8); padding: 10px;">
                    <p>Elevation: <span id="elevation">45</span>°</p>
                    <p>Angle: <span id="angle">0</span>°</p>
                    <p>Controls: ?? - Elevation, ?? - Angle, Space - Shoot</p>
                </div>
            `;
            document.body.appendChild(controls);
        );
    }

    void render() {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        
        drawGrid();
        drawSchmoo();
        
        if (lastShotMissed) {
            int hitScreenX = 400 + (lastHitX / 200);
            int hitScreenY = 300 - (lastHitY / 200);
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_Rect hitRect = {hitScreenX-3, hitScreenY-3, 6, 6};
            SDL_RenderFillRect(renderer, &hitRect);
        }
        
        SDL_RenderPresent(renderer);
    }

    void handleInput() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        inputElevation = std::min(90.0f, inputElevation + 1.0f);
                        break;
                    case SDLK_DOWN:
                        inputElevation = std::max(1.0f, inputElevation - 1.0f);
                        break;
                    case SDLK_LEFT:
                        inputAngle = std::fmod(inputAngle - 1.0f + 360.0f, 360.0f);
                        break;
                    case SDLK_RIGHT:
                        inputAngle = std::fmod(inputAngle + 1.0f, 360.0f);
                        break;
                    case SDLK_SPACE:
                        makeShot();
                        break;
                }
                updateControls();
            }
        }
    }

private:
    void updateControls() {
        EM_ASM({
            document.getElementById('elevation').textContent = $0.toFixed(1);
            document.getElementById('angle').textContent = $1.toFixed(1);
        }, inputElevation, inputAngle);
    }

    void makeShot() {
        double hitX, hitY;
        bool hit = game.makeShot(inputElevation, inputAngle, hitX, hitY);
        lastHitX = hitX;
        lastHitY = hitY;
        lastShotMissed = !hit;
        
        if (hit) {
            EM_ASM({
                alert('Hit! Shots taken: ' + $0);
            }, game.getShotCount());
            game.reset();
            lastShotMissed = false;
        } else if (game.isOver()) {
            EM_ASM({
                alert('Game Over! The Schmoo has won!');
            });
            game.reset();
            lastShotMissed = false;
        }
    }
};