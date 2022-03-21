#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "raylib.h"

#include <stdint.h>
#include <vector>
#include <string>
#include <memory>
#include <cmath>
#include <algorithm>

#include "types.hpp"
class Game
{
public:
    Game() { generateNewTile(); }

    void reset();

    void drawGrid(int tileSize, int opacity);
    void slide(Direction direction, bool flip = false);

    bool isGameOver();

    Vec2 getNextTile();

    void generateNewTile();

    void swap(Tile *a, Tile *b)
    {
        Tile temp = *a;
        *a = *b;
        *b = temp;
    }

    inline Score getScore() const { return m_Score; }

private:
    Grid m_Grid = {0};
    Score m_Score = 0;

    void flipGrid();
    void rotateGrid();

    inline bool isInBounds(uint8_t a, uint8_t b) { return (a + b >= 0 && a + b < GRID_SIZE); }

    bool canTileMove(uint8_t x, uint8_t y);

    Color getColor(Tile tile);
};

#endif