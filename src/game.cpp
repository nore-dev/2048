#include "game.hpp"

void Game::reset()
{
    std::fill_n(&m_Grid[0][0], GRID_SIZE * GRID_SIZE, EMPTY);
    m_Score = 0;
    generateNewTile();
}

Color Game::getColor(Tile tile)
{
    if (tile == EMPTY)
        return COLOR_TILE_EMPTY;

    int index = log(tile) / log(DEFAULT_TILE_VALUE) - 1;

    if (index >= TileColors.size())
        return TileColors.at(TileColors.size() - 1);

    return TileColors.at(index);
}

void Game::drawGrid(int tileSize, int opacity)
{

    int margin = 15;

    Vec2 offset = {
        (GetScreenWidth() - tileSize * GRID_SIZE) / 2,
        160};

    DrawRectangle(offset.x - margin, offset.y - margin, tileSize * GRID_SIZE + margin, tileSize * GRID_SIZE + margin, Color{187, 173, 160, opacity});

    for (int y = 0; y < GRID_SIZE; y++)
        for (int x = 0; x < GRID_SIZE; x++)
        {
            Tile currentTile = m_Grid[y][x];
            Color color = getColor(currentTile);
            color.a = opacity;

            DrawRectangle(offset.x + x * tileSize, offset.y + y * tileSize, tileSize - margin, tileSize - margin, color);

            const char *text = std::to_string(m_Grid[y][x]).c_str();
            float fontSize = (currentTile > 64) ? ((currentTile > 512) ? 30 : 40) : 60;

            Vector2 textDim = MeasureTextEx(GetFontDefault(), text, fontSize, .0f);

            if (m_Grid[y][x] != EMPTY)
                DrawText(text, offset.x + (tileSize - margin - textDim.x) / 2 + x * tileSize, (tileSize - margin - textDim.y) / 2 + offset.y + y * tileSize, fontSize, currentTile > 4 ? WHITE : Color{130, 130, 130, opacity});
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

bool Game::canTileMove(uint8_t x, uint8_t y)
{
    for (int8_t yOffset = -1; yOffset <= 1; yOffset++)
        for (int8_t xOffset = -1; xOffset <= 1; xOffset++)
        {
            if (!isInBounds(x, xOffset) || !isInBounds(y, yOffset) || !(xOffset == 0 ^ yOffset == 0))
                continue;

            Tile currentTile = m_Grid[y + yOffset][x + xOffset];

            if (currentTile == EMPTY || currentTile == m_Grid[y][x])
                return true;
        }

    return false;
}

bool Game::isGameOver()
{
    for (uint8_t y = 0; y < GRID_SIZE; y++)
        for (uint8_t x = 0; x < GRID_SIZE; x++)
            if (canTileMove(x, y))
                return false;

    return true;
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
