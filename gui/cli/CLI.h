#ifndef CPP3_BRICKGAME_V2_0_1_CLI_H
#define CPP3_BRICKGAME_V2_0_1_CLI_H

#include <ncurses.h>
#include <wchar.h>

#include "../../components/GameInfo.h"

#define MVADDCH(y, x, c) mvaddch(2 + (y), 2 + (x), c)

void ncursesInit();

void InitColors();

void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);

void DrawingHighScore(int high_score);

void DrawingGameFieldBorders(const int **field);

int render(GameInfo_t *gameInfo, int code);

void DrawingWinBanner();

void DrawingGameOver();

void DeleteGameOver();

void DrawingStartBanner();

void DeleteStartBanner();

void DrawPause();

void DeletePause();

void DrawingNextFigureField();

void DrawingNextFigure(const int **next);

void DrawingScore(int score);

void DrawingLevel(int level);

void PrintColorStr(int x, int y, const char *string, int color);

void PrintColorWc(int x, int y, wchar_t symbol, int color);

void PrintGameField(const int **field);

int GetColor(int symbol);

#endif  // CPP3_BRICKGAME_V2_0_1_CLI_H
