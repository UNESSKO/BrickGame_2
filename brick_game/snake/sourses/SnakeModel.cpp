#include "../include/SnakeModel.h"

namespace s21 {
SnakeModel::SnakeModel()
    : state_(GameState_t::Launch),
      field_(newMatrix(static_cast<int>(Field::height),
                       static_cast<int>(Field::width))),
      gameInfo_(gameInfoInit()),
      gameOver_(false),
      snake_(4),
      apple_({4, 7}),
      key_(0),
      last_key_(0) {
  int height = static_cast<int>(Field::height);
  int width = static_cast<int>(Field::width);

  for (int i = 0; i < height; ++i)
    for (int j = 0; j < width; ++j) {
      if (((j == 0 || j == 11) || i == height - 1))
        field_[i][j] = '\0';
      else
        field_[i][j] = ' ';
    }

  field_[0][0] = height;
  field_[1][0] = width;

  loadHighScore();
}

SnakeModel::~SnakeModel() {
  int height = static_cast<int>(Field::height);

  for (int i = 0; i < height; ++i) delete[] field_[i];
  delete[] field_;
}

GameInfo_t SnakeModel::gameInfoInit() {
  GameInfo_t gameInfo;
  gameInfo.field = field_;
  gameInfo.next = nullptr;

  gameInfo.score = 0;
  gameInfo.high_score = 0;
  gameInfo.level = 1;
  gameInfo.speed = setTime(gameInfo.level);
  gameInfo.pause = 0;

  return gameInfo;
}

void SnakeModel::startGame() {
  gameOver_ = false;

  loadHighScore();
  gameInfo_.score = 0;
  gameInfo_.level = 1;
}

void SnakeModel::resetGame() {
  gameOver_ = true;

  loadHighScore();
  gameInfo_.score = 0;
  gameInfo_.level = 1;
  gameInfo_.speed = setTime(gameInfo_.level);

  clearField();
  snake_.reset();
  apple_ = {4, 7};
}

void SnakeModel::loadHighScore() {
  std::ifstream save("snake_high_score.txt");

  if (save.is_open()) {
    save >> gameInfo_.high_score;
    save.close();
  } else {
    std::ofstream new_save("snake_high_score.txt");
    new_save << gameInfo_.high_score;
    new_save.close();
  }
}

void SnakeModel::saveHighScore() const {
  std::ofstream save("snake_high_score.txt");
  save << gameInfo_.high_score;
  save.close();
}

void SnakeModel::userInput(UserAction_t action, bool hold) {
  for (int i = 0, step = 1; i < step; ++i) {
    switch (state_) {
      case GameState_t::Launch:
        if (action == UserAction_t::Terminate) return;
        if (action == UserAction_t::Start && key_ == ENTER) {
          startGame();
          state_ = GameState_t::Spawn;
          step++;
        }
        break;
      case GameState_t::Spawn:
        deleteSnake();
        putSnake();
        spawnApple();
        putApple();
        state_ = GameState_t::Moving;
        break;
      case GameState_t::Moving:
        actionProcessing(action, hold);
        if (state_ == GameState_t::Eating) step++;
        break;
      case GameState_t::Eating:
        if (isAppleCollision()) {
          eat();
          state_ = GameState_t::Spawn;
          step++;
          if (snake_.size() >= 200) {
            saveHighScore();
            state_ = GameState_t::Win;
            break;
          }
          state_ = GameState_t::Spawn;
          break;
        }
        state_ = GameState_t::GameOver;
        step++;
        break;
      case Win:
        deleteSnake();
        putSnake();
        break;
      case GameOver:
        resetGame();
        state_ = GameState_t::Launch;
        break;
      default:
        break;
    }
  }
  gameInfo_.field = field_;
  last_key_ = key_;
}

void SnakeModel::actionProcessing(UserAction_t action, bool hold) {
  if (gameInfo_.pause && (action != Pause && action != Terminate)) return;

  switch (action) {
    case Left:
      snake_.setDirection(Left);
      break;
    case Right:
      snake_.setDirection(Right);
      break;
    case Up:
      snake_.setDirection(Up);
      break;
    case Down:
      snake_.setDirection(Down);
      break;
    case Pause:
      gameInfo_.pause = !gameInfo_.pause;
      break;
    case Terminate:
      break;
  }

  deleteSnake();
  snake_.move();

  if (!isCollision()) {
    putSnake();
  } else {
    state_ = GameState_t::Eating;
  }
}

void SnakeModel::clearField() {
  int height = static_cast<int>(Field::height);
  int width = static_cast<int>(Field::width);

  for (int i = 0; i < height - 1; ++i) {
    std::fill(field_[i] + 1, field_[i] + width - 1, ' ');
  }
}

bool SnakeModel::isAppleCollision() {
  return (snake_[0].x == apple_.x && snake_[0].y == apple_.y);
}

bool SnakeModel::isWallCollision() {
  int height = static_cast<int>(Field::height);
  int width = static_cast<int>(Field::width);

  return (snake_[0].x < 1 || snake_[0].x > width - 2) ||
         (snake_[0].y < 0 || snake_[0].y > height - 2);
}

bool SnakeModel::isInnerCollision() {
  for (int i = 1; i < snake_.size(); ++i) {
    if (snake_[0].x == snake_[i].x && snake_[0].y == snake_[i].y) return true;
  }
  return false;
}

bool SnakeModel::isCollision() {
  return isAppleCollision() || isWallCollision() || isInnerCollision();
}

void SnakeModel::putSnake() {
  for (int i = 1; i < snake_.size(); ++i) {
    field_[snake_[i].y][snake_[i].x] = '*' + 3;
  }

  field_[snake_[0].y][snake_[0].x] = '*' + 6;
}

void SnakeModel::deleteSnake() {
  for (int i = 0; i < snake_.size(); ++i) {
    field_[snake_[i].y][snake_[i].x] = ' ';
  }
}

void SnakeModel::putApple() { field_[apple_.y][apple_.x] = '*' + 1; }

void SnakeModel::deleteApple() { field_[apple_.y][apple_.x] = ' '; }

void SnakeModel::spawnApple() {
  int height = static_cast<int>(Field::height);
  int width = static_cast<int>(Field::width);

  Point freeSpace[210] = {0, 0};
  int freeSpaceCount = 0;

  for (int i = 0; i < height - 1; ++i) {
    for (int j = 1; j < width - 1; ++j) {
      if (field_[i][j] == ' ') {
        freeSpace[freeSpaceCount].x = j;
        freeSpace[freeSpaceCount].y = i;
        freeSpaceCount++;
      }
    }
  }

  int randomIndex = rand() % freeSpaceCount;
  apple_ = freeSpace[randomIndex];
}

void SnakeModel::eat() {
  deleteApple();
  snake_.addSegment();
  gameInfo_.score++;

  if (gameInfo_.score > gameInfo_.high_score) {
    gameInfo_.high_score = gameInfo_.score;
    saveHighScore();
  }

  if (gameInfo_.score % 5 == 0) {
    if (gameInfo_.level < 10) gameInfo_.level++;

    gameInfo_.speed = setTime(gameInfo_.level);
  }
}

int SnakeModel::setTime(int time) {
  int n = 0;

  if (time <= 5)
    n = 24;
  else if (time <= 9)
    n = 23;
  else if (time <= 10)
    n = 25;

  return 600 - time * n;
}

GameInfo_t SnakeModel::updateCurrentState() { return gameInfo_; }

void SnakeModel::setKey(int new_key) { key_ = new_key; }

int SnakeModel::getLastKey() { return last_key_; }

GameState_t SnakeModel::getGameState() {
  return gameOver_ ? GameState_t::GameOver : state_;
}

int **SnakeModel::newMatrix(int height, int width) {
  int **field = new int *[height];

  for (int i = 0; i < height; ++i) {
    field[i] = new int[width];
  }

  return field;
}
}  // namespace s21