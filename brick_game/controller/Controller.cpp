#include "Controller.h"

namespace s21 {
Controller::Controller(IModel *model) : model(model) {}

Controller::~Controller() { delete model; }

GameInfo_t Controller::updateCurrentState() {
  return model->updateCurrentState();
}

void Controller::getInput(UserAction_t *action, bool *hold, int new_key) {
  int key = processingInput(action, hold, model->getLastKey(), new_key);
  model->setKey(key);
}

int Controller::processingInput(UserAction_t *action, bool *hold, int last_key,
                                int new_key) {
  if (new_key == ArrowUp || new_key == Qt::Key_Up)
    *action = Up;
  else if (new_key == ArrowLeft || new_key == Qt::Key_Left)
    *action = Left;
  else if (new_key == ArrowRight || new_key == Qt::Key_Right)
    *action = Right;
  else if (new_key == ArrowDown || new_key == Qt::Key_Down)
    *action = Down;
  else if (new_key == QUIT || new_key == Qt::Key_Q) {
    *action = Terminate;
    new_key = QUIT;
  } else if (new_key == PAUSE || new_key == Qt::Key_P) {
    *action = Pause;
    new_key = PAUSE;
  } else if (new_key == ACTION)
    *action = Action;
  else {
    *action = Start;
    if (new_key == Qt::Key_Enter || new_key == Qt::Key_Return) new_key = ENTER;
  }

  if (new_key != -1) {
    if (new_key == last_key) *hold = true;
  } else
    *hold = false;

  return new_key;
}

void Controller::userInput(UserAction_t action, bool hold) {
  model->userInput(action, hold);
}

int Controller::getGameStateCode() {
  GameState_t state = model->getGameState();

  switch (state) {
    case Launch:
      return 1;
    case GameOver:
      return 2;
    case Win:
      return 3;
  }

  return 0;
}
}  // namespace s21