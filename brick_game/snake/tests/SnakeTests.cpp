#include "tests.h"

TEST_F(SnakeTests, Constructor) {
  // Act
  GameInfo_t gameInfo = model->updateCurrentState();
  int height = gameInfo.field[0][0];
  int width = gameInfo.field[1][0];

  gameInfo.field[0][0] = 0;
  gameInfo.field[1][0] = 0;

  // Assert
  EXPECT_EQ(height, static_cast<int>(s21::Field::height));
  EXPECT_EQ(width, static_cast<int>(s21::Field::width));

  EXPECT_TRUE(gameInfo.high_score == 0 || gameInfo.high_score == 196);
  EXPECT_EQ(gameInfo.score, 0);
  EXPECT_EQ(gameInfo.level, 1);
  EXPECT_EQ(gameInfo.pause, 0);
  EXPECT_EQ(gameInfo.speed, 576);

  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      if (((j == 0 || j == 11) || i == height - 1))
        EXPECT_EQ(gameInfo.field[i][j], '\0');
      else
        EXPECT_EQ(gameInfo.field[i][j], ' ');
    }
    EXPECT_EQ(model->getGameState(), GameState_t::Launch);
  }
}

TEST_F(SnakeTests, LaunchStage) {
  // Act
  model->setKey(Keys::PAUSE);
  UserAction_t action = UserAction_t::Pause;
  bool hold = false;
  model->userInput(action, hold);

  action = UserAction_t::Start;
  model->userInput(action, hold);

  action = Terminate;
  model->userInput(action, hold);

  // Assert
  EXPECT_EQ(model->getLastKey(), Keys::PAUSE);

  // Act
  action = Start;
  model->setKey(Keys::ENTER);
  model->userInput(action, hold);

  // Assert
  EXPECT_EQ(model->getGameState(), GameState_t::Moving);
}

TEST_F(SnakeTests, SpawnStage) {
  // Act
  model->setKey(Keys::ENTER);
  UserAction_t action = UserAction_t::Start;
  bool hold = false;

  model->userInput(action, hold);

  GameInfo_t gameInfo = model->updateCurrentState();
  int height = gameInfo.field[0][0];
  int width = gameInfo.field[1][0];

  bool appleFound = false;
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      if (gameInfo.field[i][j] == 43) {  // ASCII code for '+'
        appleFound = true;
        break;
      }
    }
    if (appleFound) break;
  }

  // Assert
  EXPECT_TRUE(appleFound);
  EXPECT_EQ(model->getGameState(), GameState_t::Moving);
}

//
// TEST_F(SnakeTests, MovingForward) {
//    // Act
//    model->setKey(Keys::ENTER);
//    UserAction_t action = UserAction_t::Start;
//    bool hold = false;
//
//    model->userInput(action, hold);
//
//    model->setKey(Keys::ArrowDown);
//    model->userInput(UserAction_t::Down, hold);
//    model->userInput(UserAction_t::Down, hold);
//    hold = true;
//
//    for (int i = 0; i < 6; i++) model->userInput(UserAction_t::Down, hold);
//
//    model->setKey(Keys::ArrowRight);
//    model->userInput(UserAction_t::Right, hold);
//
//    GameInfo_t gameInfo = model->updateCurrentState();
//
//    // Assert
//    EXPECT_EQ(model->getGameState(), GameState_t::Moving);
//
//    EXPECT_TRUE(gameInfo.field[10][5] >= '*');
//    EXPECT_TRUE(gameInfo.field[11][5] >= '*');
//    EXPECT_TRUE(gameInfo.field[12][5] >= '*');
//    EXPECT_TRUE(gameInfo.field[12][6] >= '*');
//
//    // Act
//    model->setKey(Keys::ArrowLeft);
//    model->userInput(UserAction_t::Left, false);
//
//    // Assert
//    EXPECT_TRUE(gameInfo.field[11][5] >= '*');
//    EXPECT_TRUE(gameInfo.field[12][5] >= '*');
//    EXPECT_TRUE(gameInfo.field[12][6] >= '*');
//    EXPECT_TRUE(gameInfo.field[12][7] >= '*');
//
//    // Act
//    model->setKey(Keys::ArrowUp);
//    model->userInput(UserAction_t::Up, false);
//
//    model->setKey(Keys::ArrowDown);
//    model->userInput(UserAction_t::Down, false);
//
//    // Assert
//    EXPECT_TRUE(gameInfo.field[12][6] >= '*');
//    EXPECT_TRUE(gameInfo.field[12][7] >= '*');
//    EXPECT_TRUE(gameInfo.field[11][7] >= '*');
//    EXPECT_TRUE(gameInfo.field[10][7] >= '*');
//
//    // Act
//    model->setKey(Keys::ArrowRight);
//    model->userInput(UserAction_t::Right, false);
//
//    model->setKey(Keys::ArrowDown);
//    model->userInput(UserAction_t::Down, false);
//
//    model->setKey(Keys::ArrowUp);
//    model->userInput(UserAction_t::Up, false);
//
//    // Assert
//    EXPECT_TRUE(gameInfo.field[10][7] >= '*');
//    EXPECT_TRUE(gameInfo.field[10][8] >= '*');
//    EXPECT_TRUE(gameInfo.field[11][8] >= '*');
//    EXPECT_TRUE(gameInfo.field[12][8] >= '*');
//
//    // Act
//    model->setKey(Keys::ArrowDown);
//
//    for (int i = 0; i < 4; i++) model->userInput(UserAction_t::Down, true);
//
//    model->setKey(Keys::ArrowLeft);
//    model->userInput(UserAction_t::Left, false);
//
//    model->setKey(Keys::ArrowRight);
//    model->userInput(UserAction_t::Right, false);
//
//    // Assert
//    EXPECT_TRUE(gameInfo.field[14][8] >= '*');
//    EXPECT_TRUE(gameInfo.field[15][8] >= '*');
//    EXPECT_TRUE(gameInfo.field[15][7] >= '*');
//    EXPECT_TRUE(gameInfo.field[15][6] >= '*');
//
//    // Act
//    model->setKey(Keys::ACTION);
//    model->userInput(UserAction_t::Action, false);
//
//    // Assert
//    EXPECT_TRUE(gameInfo.field[15][8] >= '*');
//    EXPECT_TRUE(gameInfo.field[15][7] >= '*');
//    EXPECT_TRUE(gameInfo.field[15][6] >= '*');
//    EXPECT_TRUE(gameInfo.field[15][5] >= '*');
//    }

TEST_F(SnakeTests, PauseWithTerminate) {
  // Act
  model->setKey(Keys::ENTER);
  UserAction_t action = UserAction_t::Start;
  bool hold = false;

  model->userInput(action, hold);

  model->setKey(Keys::ArrowDown);
  model->userInput(UserAction_t::Down, hold);
  model->userInput(UserAction_t::Down, hold);
  hold = true;

  model->setKey(Keys::PAUSE);
  model->userInput(UserAction_t::Pause, hold);

  GameInfo_t gameInfo_first = model->updateCurrentState();

  model->setKey(Keys::ArrowRight);
  model->userInput(UserAction_t::Right, hold);

  model->setKey(Keys::ArrowLeft);
  model->userInput(UserAction_t::Left, hold);

  model->setKey(Keys::ArrowDown);
  model->userInput(UserAction_t::Down, hold);

  GameInfo_t gameInfo_second = model->updateCurrentState();

  // Assert
  EXPECT_EQ(model->getGameState(), GameState_t::Moving);

  for (int i = 0; i < gameInfo_first.field[0][0]; ++i) {
    for (int j = 0; j < gameInfo_first.field[1][0]; ++j) {
      EXPECT_EQ(gameInfo_first.field[i][j], gameInfo_second.field[i][j]);
    }
  }

  // Act
  model->setKey(Keys::PAUSE);
  model->userInput(UserAction_t::Pause, false);

  model->setKey(-1);
  model->userInput(UserAction_t::Start, false);

  GameInfo_t gameInfo_third = model->updateCurrentState();

  // Assert
  EXPECT_EQ(model->getGameState(), GameState_t::Moving);
}

TEST_F(SnakeTests, AppleCollisionAndHighScore) {
  // Arrange
  model->setKey(Keys::ENTER);
  UserAction_t action = UserAction_t::Start;
  bool hold = false;

  model->userInput(action, hold);

  GameInfo_t gameInfo = model->updateCurrentState();
  EXPECT_EQ(model->getGameState(), GameState_t::Moving)
      << "Game should be in Moving state after start.";

  model->setKey(Keys::ArrowRight);
  action = UserAction_t::Right;
  model->userInput(action, hold);

  gameInfo = model->updateCurrentState();
  EXPECT_EQ(model->getGameState(), GameState_t::Moving)
      << "Game should still be Moving while eating apple.";
}

TEST_F(SnakeTests, GameOverStageWithWallCollision) {
  // Act
  model->setKey(Keys::ENTER);
  UserAction_t action = UserAction_t::Start;
  bool hold = false;

  model->userInput(action, hold);

  model->setKey(Keys::ArrowUp);
  model->userInput(UserAction_t::Up, hold);
  model->setKey(Keys::ArrowLeft);
  model->userInput(UserAction_t::Left, hold);

  for (int i = 0; i < 12; i++) model->userInput(UserAction_t::Left, true);

  GameInfo_t gameInfo = model->updateCurrentState();
  int height = gameInfo.field[0][0];
  int width = gameInfo.field[1][0];

  // Assert
  EXPECT_EQ(model->getGameState(), GameState_t::GameOver);

  for (int i = 0; i < height - 1; ++i) {
    for (int j = 1; j < width - 1; ++j) EXPECT_EQ(gameInfo.field[i][j], ' ');
  }
}

TEST_F(SnakeTests, InnerCollision) {
  // Arrange
  model->setKey(Keys::ENTER);
  UserAction_t action = UserAction_t::Start;
  bool hold = false;
  model->userInput(action, hold);

  fieldByPass(model, 1);

  // Act
  GameInfo_t gameInfo = model->updateCurrentState();

  model->setKey(Keys::ArrowRight);
  model->userInput(UserAction_t::Right, false);
  model->setKey(Keys::ArrowDown);
  model->userInput(UserAction_t::Down, false);
  model->setKey(Keys::ArrowLeft);
  model->userInput(UserAction_t::Left, false);

  // Assert
  EXPECT_EQ(model->getGameState(), GameState_t::GameOver);
}

// TEST_F(SnakeTests, WinStage) {
//     // Act
//     fieldByPass(model, 210);
//
//     GameInfo_t gameInfo = model->updateCurrentState();
//     int height = static_cast<int>(s21::Field::height);
//     int width = static_cast<int>(s21::Field::width);
//     int counter = 0;
//
//     for (int i = 0; i < height - 1; i++) {
//         for (int j = 1; j < width - 1; j++) {
//             if (gameInfo.field[i][j] >= '*') counter++;
//         }
//     }
//
//     // Assert
//     EXPECT_EQ(model->getGameState(), GameState_t::Win);
//     EXPECT_TRUE(counter >= 199);
// }

void printField(int **field) {
  int height = static_cast<int>(s21::Field::height);
  int width = static_cast<int>(s21::Field::width);

  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      if (field[i][j] > 33)
        std::cout << "* "
                  << " ";
      else
        std::cout << field[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

void moveHead(s21::Point &head, UserAction_t action) {
  switch (action) {
    case UserAction_t::Right:
      head.x += 1;
      break;
    case UserAction_t::Down:
      head.y += 1;
      break;
    case UserAction_t::Left:
      head.x -= 1;
      break;
    case UserAction_t::Up:
      head.y -= 1;
      break;
    default:
      break;
  }
}

void fieldByPass(s21::SnakeModel *model, int count) {
  model->setKey(Keys::ENTER);
  model->userInput(UserAction_t::Start, false);

  model->setKey(Keys::ArrowLeft);
  model->userInput(UserAction_t::Up, false);
  model->userInput(UserAction_t::Left, false);

  for (int i = 0; i < 3; i++) model->userInput(UserAction_t::Start, false);

  model->userInput(UserAction_t::Up, false);

  for (int i = 0; i < 5; i++) model->userInput(UserAction_t::Start, false);

  GameInfo_t gameInfo = model->updateCurrentState();
  int height = gameInfo.field[0][0];
  int width = gameInfo.field[1][0];

  for (int i = 0; i < count; i++) {
    UserAction_t action = UserAction_t::Right;

    s21::Point head{0, 1};

    for (int i = 0, n = 4; i < height - 1; i++) {
      if (i != 0 && (head.x == 10 || head.x == 2)) {
        model->setKey(Keys::ArrowDown);
        model->userInput(UserAction_t::Down, false);
        moveHead(head, UserAction_t::Down);
      }

      if (head.x == 1 || head.x == 2 || head.x == 10) {
        model->setKey(action == UserAction_t::Right ? Keys::ArrowRight
                                                    : Keys::ArrowLeft);
        model->userInput(action, false);
        moveHead(head, action);
      }

      for (int j = 0; j < width - n; j++) {
        if (model->getGameState() == GameState_t::Win) {
          height = 0;
          count = 0;
          break;
        }

        model->setKey(-1);
        model->userInput(Start, false);
        moveHead(head, action);
      }

      action = (action == UserAction_t::Right) ? UserAction_t::Left
                                               : UserAction_t::Right;
      n = 5;
    }

    model->userInput(UserAction_t::Start, false);
    model->userInput(UserAction_t::Up, false);

    for (int i = 0; i < 18 && height; i++)
      model->userInput(UserAction_t::Start, false);
  }
}
