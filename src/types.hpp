#ifndef __TYPES_HPP__
#define __TYPES_HPP__

#include <stdint.h>
#include "raylib.h"
#include <vector>

enum Direction
{
    ROW,
    COLUMN
};

static const uint8_t EMPTY = 0;
static const uint8_t GRID_SIZE = 4;

static const uint16_t DEFAULT_TILE_VALUE = 2;

struct Vec2
{
    uint8_t x;
    uint8_t y;
};

typedef uint16_t Score;
typedef uint16_t Tile;
typedef Tile Grid[GRID_SIZE][GRID_SIZE];

static const Color COLOR_TILE_EMPTY = {205, 193, 180, 255};
static const std::vector<Color> TileColors = {
    {238, 228, 218, 255},
    {238, 225, 201, 255},
    {243, 178, 122, 255},
    {246, 150, 100, 255},
    {247, 124, 95, 255},
    {247, 95, 59, 255}};

#endif