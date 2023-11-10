#include "../head/state.h"
#include <iostream>
#include <queue>

// Globals----------------------------------

int SCORE{};
int FPS{5};

// Helper functions-------------------------

bool checkForCollision(std::array<std::array<int, BOARD_HEIGHT>, BOARD_WIDTH> &board, Block &block)
{
    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            int blockValue = block.m_shape[x][y];
            if (blockValue != 0)
            {
                // Check for collision with other block.
                int boardValue = board[block.m_x + x][block.m_y + y];
                if (boardValue != 0)
                {
                    return true;
                }
                // Checks for map boundries.
                if (block.m_x + x >= BOARD_WIDTH || block.m_y + y >= BOARD_HEIGHT || block.m_x + x < 0)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

Block rotate(Block const &currBlock)
{
    auto block{currBlock};

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            block.m_shape[j][3 - i] = currBlock.m_shape[i][j];
        }
    }

    return block;
}

void setBackground(sf::RenderWindow &window)
{
    sf::RectangleShape background{sf::Vector2f(WIDTH, HEIGHT)};
    background.setFillColor(sf::Color(0, 90, 0));
    window.draw(background);

    sf::RectangleShape border{sf::Vector2f(CELL_SIZE * BOARD_WIDTH + 1, CELL_SIZE * (BOARD_HEIGHT - BOARD_VISEBLE_HEIGHT))};
    border.setPosition(19, 149);
    border.setFillColor(sf::Color::Black);
    window.draw(border);

    border.setSize({(CELL_SIZE * 4) + 1, (CELL_SIZE * 4) + 1});
    border.setPosition(349, 149);
    window.draw(border);

    border.setSize({(CELL_SIZE * 4) + 1, (CELL_SIZE * 1.75) + 1});
    border.setPosition(349, 304);
    window.draw(border);
}

void setBoard(sf::RenderWindow &window, Matrix const &board)
{
    sf::RectangleShape cell{sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1)};
    for (size_t col{}; col < BOARD_WIDTH; col++)
    {
        for (size_t row{5}; row < BOARD_HEIGHT; row++)
        {
            auto currPixel{board.m_board[col][row]};
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
            cell.setPosition(CELL_SIZE * col + 20, CELL_SIZE * row);
            window.draw(cell);
        }
    }
}

// State functions-------------------------

void State::wait(sf::Clock &clock)
{
    const sf::Int32 targetFrameTime = 1000 / FPS;

    sf::Time elapsedTime = clock.getElapsedTime();
    sf::Int32 elapsedMilliseconds = elapsedTime.asMilliseconds();

    if (elapsedMilliseconds < targetFrameTime)
    {
        sf::sleep(sf::milliseconds(targetFrameTime - elapsedMilliseconds));
    }
}

// Playing functions-----------------------

void PlayingState::move(int action)
{
    auto &block{m_activeBlock.m_block};
    auto copy{m_matrix.m_board};

    // Create a variable to keep track of which cells belong to the active block
    bool clearActiveBlock = false;

    // Clear activeBlock from board.
    for (int x{}; x < 4; x++)
    {
        for (int y{}; y < 4; y++)
        {
            if (block.m_shape[x][y] != 0)
            {
                // Only clear the cells that belong to the active block
                if (block.m_x + x >= 0 && block.m_x + x < BOARD_WIDTH && block.m_y + y >= 0 && block.m_y + y < BOARD_HEIGHT)
                {
                    copy[block.m_x + x][block.m_y + y] = 0;
                    clearActiveBlock = true;
                }
            }
        }
    }

    // Check if allowed to move.
    auto tmp{block};
    switch (action)
    {
    case LEFT:
        tmp.m_x--;
        if (!checkForCollision(copy, tmp))
            block.m_x--;
        break;
    case RIGHT:
        tmp.m_x++;
        if (!checkForCollision(copy, tmp))
            block.m_x++;
        break;
    case ROTATE:
        tmp = rotate(block);
        if (!checkForCollision(copy, tmp))
            block = tmp;
        break;
    case DOWN:
        tmp.m_y++;
        if (checkForCollision(copy, tmp))
        {
            m_activeBlock.m_active = false;
            if (tmp.m_y < BOARD_VISEBLE_HEIGHT)
                m_changeState = GAMEOVER;
            return;
        }
        else
            block.m_y++;
        break;
    default:
        break;
    }

    // Update activeBlock on board only if we've cleared the active block
    if (clearActiveBlock)
    {
        for (int x{}; x < 4; x++)
        {
            for (int y{}; y < 4; y++)
            {
                if (block.m_shape[x][y] != 0)
                {
                    if (block.m_x + x >= 0 && block.m_x + x < BOARD_WIDTH && block.m_y + y >= 0 && block.m_y + y < BOARD_HEIGHT)
                    {
                        copy[block.m_x + x][block.m_y + y] = block.m_shape[x][y];
                    }
                }
            }
        }
    }

    // Update the game board with the modified copy
    m_matrix.m_board = copy;
}

void PlayingState::clearLine(int line)
{
    auto &board = m_matrix.m_board;

    // Clear the specified line
    for (size_t x = 0; x < BOARD_WIDTH; x++)
    {
        board[x][line] = 0;
    }

    // Shift the rows above it down
    for (size_t y = line; y > BOARD_VISEBLE_HEIGHT; y--)
    {
        for (size_t x = 0; x < BOARD_WIDTH; x++)
        {
            board[x][y] = board[x][y - 1];
        }
    }
}

void PlayingState::scanBoard()
{
    auto board{m_matrix.m_board};
    int counter{};
    for (size_t y{static_cast<size_t>(BOARD_HEIGHT - 1)}; y >= BOARD_VISEBLE_HEIGHT; y--)
    {
        bool clearedLine{true};
        for (size_t x{}; x < BOARD_WIDTH; x++)
        {
            if (board[x][y] == 0)
            {
                clearedLine = false;
                break;
            }
        }
        if (clearedLine)
        {
            clearLine(y);
            counter++;
        }
    }

    if (counter == 4)
    {
        // tetris();
    }
}

void PlayingState::input(Resources &)
{
    // Left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        move(LEFT);
    }
    // Right
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        move(RIGHT);
    }
    // Down
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        move(DOWN);
        move(DOWN);
    }
    // Rotate
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
    {
        move(ROTATE);
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
    {
        m_changeState = GAMEOVER;
    }
}

void PlayingState::logic(Resources &)
{
    // Add new block
    auto &activeBlock{m_activeBlock};
    static int counter{};
    if (!activeBlock.m_active)
    {
        ActiveBlock newBlock;
        std::swap(m_nextScreen.m_nextBlock, newBlock.m_block);
        m_activeBlock = newBlock;
    }
    // Move block down each game tick
    move(DOWN);
    // Handle line clearing
    scanBoard();
    // Increment score
    if (counter++ > 30)
    {
        SCORE++;
        counter = 0;
        if (SCORE % 10 == 0)
            FPS++;
    }
}

void PlayingState::update(Resources &, sf::RenderWindow &window)
{
    auto board{m_matrix};
    window.clear();

    setBackground(window);
    setBoard(window, m_matrix);

    window.draw(m_nextScreen);
    m_nextScreen.display(window);
    window.draw(m_scoreScreen);
    m_scoreScreen.display(window, SCORE);

    window.display();
}

// Gameover functions-----------------------

void GameoverState::input(Resources &)
{
    // Change state
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
    {
        m_changeState = MENU;
    }
}

void GameoverState::logic(Resources &)
{
    SCORE = 0;
    FPS = 5;
}

void GameoverState::update(Resources &resources, sf::RenderWindow &window)
{
    sf::Text str{"Press Space", resources.m_font};
    str.setPosition(70, 400);
    str.setScale(1.3, 1.3);
    window.draw(str);
    str.setString("GAMEOVER");
    str.setPosition(40, 200);
    str.setScale(2, 2);
    window.draw(str);

    window.display();
}

// Menu functions------------------------------

void MenuState::input(Resources &)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
    {
        m_changeState = PLAYING;
    }
}

void MenuState::logic(Resources &)
{
}

void MenuState::update(Resources &resources, sf::RenderWindow &window)
{
    window.clear();

    setBackground(window);
    setBoard(window, m_matrix);

    sf::Text str{"Press Enter", resources.m_font};
    str.setPosition(50, 400);
    str.setScale(1.5, 1.5);
    window.draw(str);
    str.setString("TETRIS");
    str.setPosition(40, 200);
    str.setScale(3, 3);
    window.draw(str);

    window.display();
}
