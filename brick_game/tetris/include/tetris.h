/**
 * @file
 *  @brief Tetris backend part header
 */
#ifndef TETRIS_H
#define TETRIS_H

#include <stdbool.h>

#include "../../../components/GameInfo.h"

typedef enum {
  FieldRows = 23,
  FieldCols = 12,
  LeftBorder = 1,
  RightBorder = 11
} Borders;

static int figures[14][5] = {

    {0, 1, 1, 1, 1},  // ####
    {0, 0, 0, 0, 0},  //

    {0, 0, 1, 0, 0},  //  #
    {0, 1, 1, 1, 0},  // ###

    {0, 1, 0, 0, 0},  // #
    {0, 1, 1, 1, 0},  // ###

    {0, 0, 0, 1, 0},  //   #
    {0, 1, 1, 1, 0},  // ###

    {0, 1, 1, 0, 0},  // ##
    {0, 1, 1, 0, 0},  // ##

    {0, 1, 1, 0, 0},  // ##
    {0, 0, 1, 1, 0},  //  ##

    {0, 0, 1, 1, 0},  //  ##
    {0, 1, 1, 0, 0}   // ##

};

typedef struct {
  GameState_t state;

  int clicks;
  int blocking;
  int key;
  int last_key;
  int move;

} TetrisGame;

void TetrisGameInit();

GameInfo_t updateCurrentState();

int getTetrisLastKey();

GameState_t getTetrisState();

void TetrisGameInfoInit();

void DeleteGameInfo();

void userInput(UserAction_t action, bool hold);

void actionProcessing(UserAction_t action, bool hold);

int StatusProcessing(UserAction_t action);

void ShiftingProcessing();

void ResettingOldFigure(int axis, int term);

int CheckingFreePosition();

void ReturnFigureBack(int axis, int term);

void TransferFigureToField();

void ClearField(int **field, int row1, int row2, int col1, int col2);

void AttachingStage();

void FigureDown();

void DropFigure();

void MoveHorizontal(char *side);

void Rotate();

void SetNextFigure(int next);

int GetNextFigure();

void SetCurrentFigure(int next);

int GetCurrentFigure();

void Restart();

void GameOverCheck();

void RemovingFilledLines();

void FieldDown(int row);

void SaveHighScore(const char *path);

int GetHighScore(const char *path);

void ProcessingRemovedLines(int removed_lines);

int defineTetrisTime(int level);

void setKey(int new_key);

int CreateMatrix(int rows, int columns, int ***matrix);

void RemoveMatrix(int **matrix, int rows);

int getFigureIndex(int x, int y);

#endif