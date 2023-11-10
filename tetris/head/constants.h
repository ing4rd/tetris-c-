#pragma once

// Sizes
const int CELL_SIZE(30), WIDTH{500}, HEIGHT{800}, BOARD_WIDTH{10}, BOARD_HEIGHT{25}, BOARD_VISEBLE_HEIGHT{5};
// Spawn
const int SPAWN_X{3}, SPAWN_Y{0};
// Totals
const int NUMBER_OF_DIFFERENT_BLOCKS{6}, NUMBER_OF_STATES{4};
// States
const int NOCHANGE{}, PLAYING{1}, GAMEOVER{2}, MENU{3};
// Blocks
const int LINE{}, SQUARE{1}, T_PIECE{2}, L_PIECE{3}, J_PIECE{4}, S_PIECE{5}, Z_PIECE{6};
// Directions
const int LEFT{}, RIGHT{1}, DOWN{2}, ROTATE{3};
