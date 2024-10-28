#include "TetrisModel.h"

namespace s21 {
TetrisModel::TetrisModel() {
  ::TetrisGameInit();
  ::TetrisGameInfoInit();
}

TetrisModel::~TetrisModel() { ::DeleteGameInfo(); }

void TetrisModel::userInput(UserAction_t action, bool hold) {
  ::userInput(action, hold);
}

GameInfo_t TetrisModel::updateCurrentState() { return ::updateCurrentState(); }

void TetrisModel::setKey(int key) { ::setKey(key); }

int TetrisModel::getLastKey() { return ::getTetrisLastKey(); }

GameState_t TetrisModel::getGameState() { return ::getTetrisState(); }
}  // namespace s21