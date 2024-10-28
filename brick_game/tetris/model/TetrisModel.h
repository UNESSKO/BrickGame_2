#ifndef CPP3_BRICKGAME_V2_0_1_TETRISMODEL_H
#define CPP3_BRICKGAME_V2_0_1_TETRISMODEL_H

#ifdef __cplusplus

#include "../../../components/interfaces/IModel.h"

extern "C" {
#endif

#include "../include/tetris.h"

#ifdef __cplusplus
}
#endif

namespace s21 {
class TetrisModel : public IModel {
 public:
  TetrisModel();

  ~TetrisModel() override;

  void userInput(UserAction_t action, bool hold) override;

  GameInfo_t updateCurrentState() override;

  void setKey(int key) override;

  int getLastKey() override;

  GameState_t getGameState() override;
};
}  // namespace s21

#endif  // CPP3_BRICKGAME_V2_0_1_TETRISMODEL_H
