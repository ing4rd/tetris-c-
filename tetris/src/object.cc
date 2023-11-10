#include "../head/object.h"
#include "../head/constants.h"

#include <string>

Block::Block(int shape) : m_shape(4, std::vector<int>(4, 0))
{
    m_x = SPAWN_X;
    m_y = SPAWN_Y;

    switch (shape)
    {
    case LINE:
        m_shape = {
            {0, 0, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 1, 0}};
        break;
    case SQUARE:
        m_shape = {
            {0, 0, 0, 0},
            {0, 2, 2, 0},
            {0, 2, 2, 0},
            {0, 0, 0, 0}};
        break;
    case T_PIECE:
        m_shape = {
            {0, 0, 0, 0},
            {0, 3, 0, 0},
            {3, 3, 3, 0},
            {0, 0, 0, 0}};
        break;
    case L_PIECE:
        m_shape = {
            {0, 0, 0, 0},
            {4, 0, 0, 0},
            {4, 4, 4, 0},
            {0, 0, 0, 0}};
        break;
    case J_PIECE:
        m_shape = {
            {0, 0, 0, 0},
            {0, 0, 0, 5},
            {0, 5, 5, 5},
            {0, 0, 0, 0}};
        break;
    case S_PIECE:
        m_shape = {
            {0, 0, 0, 0},
            {0, 0, 6, 6},
            {0, 6, 6, 0},
            {0, 0, 0, 0}};
        break;
    case Z_PIECE:
        m_shape = {
            {0, 0, 0, 0},
            {0, 7, 7, 0},
            {0, 0, 7, 7},
            {0, 0, 0, 0}};
        break;
    default:
        break;
    }
}

Matrix::Matrix()
{
    for (size_t i{}; i < BOARD_HEIGHT; i++)
        for (size_t j{}; j < BOARD_WIDTH; j++)
            m_board[j][i] = 0;
}

NextScreen::NextScreen(Resources &)
    : m_nextBlock{LINE}
{
}

void NextScreen::display(sf::RenderWindow &window)
{
    sf::RectangleShape cell{sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1)};
    for (size_t x{}; x < 4; x++)
    {
        for (size_t y{}; y < 4; y++)
        {
            auto currPixel{m_nextBlock.m_shape[x][y]};
            switch (currPixel)
            {
            case 0:
                cell.setFillColor(sf::Color::Black);
                break;
            case 1:
                cell.setFillColor(sf::Color(50, 100, 50));
                break;
            case 2:
                cell.setFillColor(sf::Color(50, 150, 50));
                break;
            case 3:
                cell.setFillColor(sf::Color(50, 150, 75));
                break;
            case 4:
                cell.setFillColor(sf::Color(50, 100, 75));
                break;
            case 5:
                cell.setFillColor(sf::Color(10, 140, 10));
                break;
            case 6:
                cell.setFillColor(sf::Color(50, 175, 50));
                break;
            case 7:
                cell.setFillColor(sf::Color(80, 130, 50));
                break;
            default:
                break;
            }
            cell.setPosition(350 + (CELL_SIZE * x), 150 + (CELL_SIZE * y));
            window.draw(cell);
        }
    }
}

ScoreScreen::ScoreScreen(Resources &res)
    : m_score{"000", res.m_font}
{
    // Score
    m_score.setPosition(350, 300);
    m_score.setFillColor(sf::Color(0, 90, 0));
    m_score.setScale(1.5, 1.5);
}

void ScoreScreen::display(sf::RenderWindow &window, int score)
{
    std::string str{std::to_string(score)};
    while (str.size() < 3)
        str = '0' + str;

    m_score.setString(str);

    window.draw(m_score);
}
