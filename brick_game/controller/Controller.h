#ifndef CPP3_BRICKGAME_V2_0_1_CONTROLLER_H
#define CPP3_BRICKGAME_V2_0_1_CONTROLLER_H

#ifdef __cplusplus

#include <Qt>

#include "../../components/interfaces/IModel.h"

extern "C" {
#endif

#include "../../components/GameInfo.h"

#ifdef __cplusplus
}
#endif

namespace s21 {
class Controller {
  IModel *model;

 public:
  explicit Controller(IModel *model);

  ~Controller();

  void userInput(UserAction_t action, bool hold);

  void getInput(UserAction_t *action, bool *hold, int new_key);

  static int processingInput(UserAction_t *action, bool *hold, int last_key,
                             int new_key);

  GameInfo_t updateCurrentState();

  int getGameStateCode();
};
}  // namespace s21

#endif  // CPP3_BRICKGAME_V2_0_1_CONTROLLER_H
