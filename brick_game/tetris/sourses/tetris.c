#include "../include/tetris.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

static GameInfo_t gameInfo;
static TetrisGame game;

void TetrisGameInit() {
  game.state = Launch;
  game.clicks = 0;
  game.blocking = 0;
  game.key = 0;
  game.last_key = -1;
  game.move = 0;
}

GameInfo_t updateCurrentState() { return gameInfo; }

int getTetrisLastKey() { return game.last_key; }

GameState_t getTetrisState() { return game.state; }

void TetrisGameInfoInit() {
  CreateMatrix(FieldRows, FieldCols, &gameInfo.field);

  for (int i = 0; i < FieldRows; i++)
    for (int j = 0; j < FieldCols; j++)
      if ((j == 0 || j == 11) || i == FieldRows - 1)
        gameInfo.field[i][j] = '\0';
      else
        gameInfo.field[i][j] = ' ';

  gameInfo.field[0][0] = FieldRows;
  gameInfo.field[1][0] = FieldCols;

  CreateMatrix(4, 6, &gameInfo.next);

  gameInfo.score = 0;

  gameInfo.high_score = GetHighScore("tetris_high_score");

  gameInfo.level = 1;

  gameInfo.speed = defineTetrisTime(gameInfo.level);

  gameInfo.pause = 0;

  SetNextFigure(rand() % 7);

  gameInfo.next[0][5] = rand() % 7;
}

void DeleteGameInfo() {
  if (gameInfo.field) RemoveMatrix(gameInfo.field, FieldRows);

  if (gameInfo.next) RemoveMatrix(gameInfo.next, 4);
}

void ClearField(int **field, int row1, int row2, int col1, int col2) {
  for (int i = row1; i <= row2; i++) {
    for (int j = col1; j <= col2; j++) {
      field[i][j] = ' ';
    }
  }
}

void ResettingOldFigure(int axis, int term) {
  for (int i = 0, x = 0, y = 0; i < 4; i++) {
    x = gameInfo.next[0][i];  // x
    y = gameInfo.next[1][i];  // y

    gameInfo.field[x][y] = ' ';

    gameInfo.next[axis][i] += term;
  }
}

int CheckingFreePosition() {
  int count = 0;

  for (int i = 0, x = 0, y = 0; i < 4; i++) {
    x = gameInfo.next[0][i];
    y = gameInfo.next[1][i];

    if (gameInfo.field[x][y] >= ' ' && gameInfo.field[x][y] < '*') count++;
  }

  return count;
}

void ReturnFigureBack(int axis, int term) {
  for (int i = 0; i < 4; i++) gameInfo.next[axis][i] -= term;
}

void FigureDown() {
  if (game.state != Shifting) return;

  bool figure_is_stopped = false;

  ResettingOldFigure(0, 1);

  int number_of_free_positions = CheckingFreePosition();

  if (number_of_free_positions != 4) {
    ReturnFigureBack(0, 1);
    figure_is_stopped = true;
  }

  if (figure_is_stopped) game.state = Eating;

  TransferFigureToField();
}

void DropFigure() {
  int number = GetNextFigure();

  gameInfo.next[1][5] = gameInfo.next[0][5];

  SetCurrentFigure(number);

  for (int i = 0, k = 0; (i < 2); i++)
    for (int j = 3, f_j = 0; (j < 7); j++, f_j++) {
      if (gameInfo.next[i + 2][f_j]) {
        gameInfo.next[0][k] = i;

        gameInfo.next[1][k] = j + 1;

        k++;
      }
    }

  number = (rand() % 7);

  SetNextFigure(number);

  gameInfo.next[0][5] = rand() % 7;

  TransferFigureToField();
}

void SetNextFigure(int next) {
  gameInfo.next[0][4] = next;

  for (int i = 0, i_ = 2; i < 2; ++i, ++i_)
    for (int j = 1; j < 5; ++j) {
      if (getFigureIndex(next * 2 + i, j))
        gameInfo.next[i_][j - 1] = 1;
      else
        gameInfo.next[i_][j - 1] = 0;
    }
}

int GetNextFigure() { return gameInfo.next[0][4]; }

void SetCurrentFigure(int current) { gameInfo.next[1][4] = current; }

int GetCurrentFigure() { return gameInfo.next[1][4]; }

void TransferFigureToField() {
  for (int i = 0, x = 0, y = 0; i < 4; i++) {
    x = gameInfo.next[0][i];
    y = gameInfo.next[1][i];

    gameInfo.field[x][y] = '*' + gameInfo.next[1][5];
  }
}

void MoveHorizontal(char *side) {
  int step = (!strcmp(side, "left")) ? -1 : 1;

  ResettingOldFigure(1, step);

  int number_of_free_positions = CheckingFreePosition();

  if (number_of_free_positions != 4) ReturnFigureBack(1, step);

  TransferFigureToField();
}

void Rotate() {
  if (GetCurrentFigure() == 4) return;

  int px = gameInfo.next[0][2];
  int py = gameInfo.next[1][2];

  ResettingOldFigure(0, 0);

  int collision = 0;

  for (int i = 0; i < 4; i++) {
    int x1 = gameInfo.next[0][i];
    int y1 = gameInfo.next[1][i];

    int x2 = px + py - y1;
    int y2 = x1 + py - px;

    if (x2 < 0 || x2 >= FieldRows || y2 < 0 || y2 >= RightBorder ||
        !(gameInfo.field[x2][y2] >= ' ' && gameInfo.field[x2][y2] < '*'))
      collision = 1;
  }

  if (!collision)
    for (int i = 0; i < 4; i++) {
      int x1 = gameInfo.next[0][i];
      int y1 = gameInfo.next[1][i];

      gameInfo.next[0][i] = px + py - y1;
      gameInfo.next[1][i] = py - (px - x1);
    }

  TransferFigureToField();
}

void GameOverCheck() {
  for (int i = 0; i < 2; i++)
    for (int j = LeftBorder; j < RightBorder; j++) {
      if (gameInfo.field[i][j] >= '*') {
        game.state = GameOver;
        return;
      }
    }
}

void RemovingFilledLines() {
  int removed_lines = 0, count = 0;

  for (int i = FieldRows - 2; i > 1; i--) {
    for (int j = LeftBorder; j < RightBorder; j++)
      if (gameInfo.field[i][j] >= '*') count++;

    if (count == 10) {
      FieldDown(i);
      removed_lines++;
      i++;
    }

    count = 0;
  }

  ProcessingRemovedLines(removed_lines);
}

void ProcessingRemovedLines(int removed_lines) {
  int score = 0;

  switch (removed_lines) {
    case 1:
      score = 100;
      break;
    case 2:
      score = 300;
      break;
    case 3:
      score = 700;
      break;
    case 4:
      score = 1500;
      break;
    default:
      break;
  }

  gameInfo.score += score;

  if (gameInfo.score > gameInfo.high_score)
    gameInfo.high_score = gameInfo.score;

  int level_increase = gameInfo.score / 600 + 1;

  if (level_increase > 10) level_increase = 1;

  gameInfo.level = level_increase;
  gameInfo.speed = defineTetrisTime(gameInfo.level);
}

void FieldDown(int row) {
  for (int i = row; i >= 1; i--)
    for (int j = LeftBorder, c_j = 0; j < RightBorder; j++, c_j++)
      gameInfo.field[i][j] = gameInfo.field[i - 1][j];

  for (int j = LeftBorder; j < RightBorder; j++) gameInfo.field[0][j] = ' ';
}

void SaveHighScore(const char *path) {
  FILE *filePointer = fopen(path, "w");

  if (filePointer == NULL) return;

  fprintf(filePointer, "HighScore = %d", gameInfo.high_score);

  fclose(filePointer);
}

int GetHighScore(const char *path) {
  FILE *filePointer = fopen(path, "r");

  if (filePointer == NULL) return 0;

  char line[256] = {0};

  int high_score = 0;

  while (fgets(line, 256, filePointer) != NULL) {
    if (strstr(line, "HighScore = ") != NULL) {
      int n = 0;
      n = sscanf(line, "HighScore = %d", &high_score);

      if (n < 1) high_score = 0;

      break;
    }
  }

  fclose(filePointer);

  return high_score;
}

void Restart() {
  ClearField(gameInfo.field, 0, FieldRows - 2, LeftBorder, RightBorder - 1);

  gameInfo.score = 0;
  gameInfo.level = 1;
  gameInfo.speed = defineTetrisTime(gameInfo.level);
  gameInfo.pause = 0;
}

void AttachingStage() {
  GameOverCheck();

  if (game.state == GameOver) {
    Restart();
    return;
  }

  RemovingFilledLines();

  game.state = Spawn;
}

int StatusProcessing(UserAction_t action) {
  if (game.key == ENTER && (game.state == Launch || game.state == GameOver)) {
    game.state = Spawn;
    game.blocking = 1;
  }

  if (action == Start && game.key != -1) game.blocking = 1;

  if (gameInfo.pause && game.key != PAUSE && game.key != QUIT) return 1;

  game.clicks = (game.clicks == 5) ? 1 : game.clicks + 1;

  return 0;
}

void userInput(UserAction_t action, bool hold) {
  game.last_key = game.key;

  if (StatusProcessing(action)) return;

  if (game.state == Moving || action == Terminate) {
    actionProcessing(action, hold);

    if (action == Up || action == Terminate) return;

    if (action != Pause) ShiftingProcessing();
  }

  if (game.state == Spawn) {
    DropFigure();
    game.state = Moving;
  }
}

void actionProcessing(UserAction_t action, bool hold) {
  switch (action) {
    case Up:
      break;
    case Action:
      Rotate();
      game.move = 1;
      break;
    case Right:
      MoveHorizontal("right");
      game.move = 1;
      break;
    case Left:
      MoveHorizontal("left");
      game.move = 1;
      break;
    case Down:
      if (hold) gameInfo.speed = defineTetrisTime(gameInfo.level + 1);
      break;
    case Pause:
      gameInfo.pause = !gameInfo.pause;
      break;
    case Terminate:
      SaveHighScore("tetris_high_score");
      return;
    default:
      break;
  }

  if (action == Down && !hold)
    gameInfo.speed = defineTetrisTime(gameInfo.level);
}

void ShiftingProcessing() {
  int click = game.clicks % 5;

  game.state = Shifting;

  if ((!game.move || click == 0) && !game.blocking) FigureDown();

  game.blocking = 0;
  game.move = 0;

  if (game.state == Eating)
    AttachingStage();
  else
    game.state = Moving;
}

int defineTetrisTime(int level) { return 600 - level * 25; }

void setKey(int new_key) { game.key = new_key; }

int CreateMatrix(int rows, int columns, int ***matrix) {
  int code = 1;

  if (rows > 0 && columns > 0) {
    *matrix = (int **)calloc(rows, sizeof(int *));

    for (int i = 0; i < rows; i++)
      (*matrix)[i] = (int *)calloc(columns, sizeof(int));

    code = 0;
  }

  return code;
}

void RemoveMatrix(int **matrix, int rows) {
  if (matrix) {
    for (int i = 0; i < rows; i++) free(matrix[i]);

    free(matrix);

    matrix = NULL;
  }
}

int getFigureIndex(int x, int y) { return figures[x][y]; }