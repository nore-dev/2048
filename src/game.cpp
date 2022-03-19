#include "game.hpp"

void Game::drawGrid(uint8_t tileSize)
{
    for (int x = 0; x < GRID_SIZE; x++)
        for (int y = 0; y < GRID_SIZE; y++)
        {
            DrawRectangle(x * tileSize, 120 + y * tileSize, tileSize - 20, tileSize - 20, LIGHTGRAY);

            if (m_Grid[y][x] != EMPTY)
                DrawText(std::to_string(m_Grid[y][x]).c_str(), x * tileSize, 120 + y * tileSize, 60, BLACK);
        }
}

Vec2 Game::getNextTile()
{
    std::vector<Vec2> available_tiles;

    for (uint8_t x = 0; x < GRID_SIZE; x++)
    {
        for (uint8_t y = 0; y < GRID_SIZE; y++)
        {
            if (m_Grid[y][x] == EMPTY)
                available_tiles.push_back(Vec2{x, y});
        }
    }

    return available_tiles.at(GetRandomValue(0, available_tiles.size() - 1));
}

void Game::generateNewTile()
{
    Vec2 nextTile = getNextTile();

    m_Grid[nextTile.y][nextTile.x] = DEFAULT_TILE_VALUE;

    if (GetRandomValue(0, 10) > 8)
        m_Grid[nextTile.y][nextTile.x] += DEFAULT_TILE_VALUE;
}

void Game::flipGrid()
{
    for (uint8_t y = 0; y < GRID_SIZE; y++)
        for (uint8_t x = 0; x < GRID_SIZE / 2; x++)
            std::swap(m_Grid[y][x], m_Grid[y][GRID_SIZE - x - 1]);
}

void Game::rotateGrid()
{
    Grid tempGrid = {0};

    for (uint8_t y = 0; y < GRID_SIZE; y++)
        for (uint8_t x = 0; x < GRID_SIZE; x++)
            tempGrid[x][y] = m_Grid[y][x];

    std::copy(&tempGrid[0][0], &tempGrid[0][0] + GRID_SIZE * GRID_SIZE, &m_Grid[0][0]);
}

void Game::slide(Direction direction, bool flip)
{
    if (direction == ROW)
        rotateGrid();

    if (flip)
        flipGrid();

    bool tileMoved = false;

    for (uint8_t y = 0; y < GRID_SIZE; y++)
    {
        uint8_t saved_index = 0;
        for (uint8_t x = 0; x < GRID_SIZE; x++)
        {
            Tile current_tile = m_Grid[y][x];
            if (current_tile == EMPTY || x - 1 < 0 || x - 1 > GRID_SIZE - 1)
                continue;

            m_Grid[y][x] = EMPTY;

            if (m_Grid[y][saved_index] == current_tile)
            {
                m_Grid[y][saved_index] += current_tile;
                m_Score += m_Grid[y][saved_index];
            }
            else if (m_Grid[y][saved_index] == EMPTY)
                m_Grid[y][saved_index] += current_tile;
            else
                m_Grid[y][saved_index + 1] = current_tile;

            if (!tileMoved && m_Grid[y][x] == EMPTY)
                tileMoved = true;

            if (m_Grid[y][saved_index] != EMPTY && m_Grid[y][saved_index] != current_tile)
                saved_index++;
        }
    }

    if (flip)
        flipGrid();

    if (direction == ROW)
    {
        rotateGrid();
        rotateGrid();
        rotateGrid();
    }

    if (tileMoved)
        generateNewTile();
}
