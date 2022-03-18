#include "game.hpp"

void Game::drawGrid(uint8_t tileSize)
{
    for (int x = 0; x < GRID_SIZE; x++)
    {
        for (int y = 0; y < GRID_SIZE; y++)
        {
            DrawRectangle(x * tileSize, 120 + y * tileSize, tileSize - 5, tileSize - 5, LIGHTGRAY);

            if (m_Grid[y][x] != EMPTY)
            {
                DrawText(std::to_string(m_Grid[y][x]).c_str(), x * tileSize, 120 + y * tileSize, 100, BLACK);
            }
        }
    }
}

Vec2 Game::getNextTile()
{
    std::vector<Vec2> available_tiles;

    for (uint8_t x = 0; x < GRID_SIZE; x++)
    {
        for (uint8_t y = 0; y < GRID_SIZE; y++)
        {
            available_tiles.push_back(Vec2{x, y});
        }
    }

    return available_tiles.at(GetRandomValue(0, available_tiles.size() - 1));
}
