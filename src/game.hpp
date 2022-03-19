#ifndef __GAME_H__
#define __GAME_H__

#include "raylib.h"
#include <stdint.h>
#include <vector>
#include <string>
#include <memory>

enum Direction
{
    ROW,
    COLUMN
};

static const uint8_t EMPTY = 0;
static const uint8_t GRID_SIZE = 4;

struct Vec2
{
    uint8_t x;
    uint8_t y;
};

typedef uint16_t Score;
typedef uint16_t Tile;
typedef Tile Grid[GRID_SIZE][GRID_SIZE];

class Game
{
public:
    Game()
    {
        Vec2 nextTile = getNextTile();

        m_Grid[nextTile.y][nextTile.x] = 2;
    }

    void drawGrid(uint8_t tileSize);
    void slide(Direction direction, bool flip = false);

    bool isGameOver();

    Vec2 getNextTile();

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
};

#endif