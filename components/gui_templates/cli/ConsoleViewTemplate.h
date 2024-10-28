#ifndef CPP3_BRICKGAME_V2_0_1_CONSOLEVIEWTEMPLATE_H
#define CPP3_BRICKGAME_V2_0_1_CONSOLEVIEWTEMPLATE_H

#ifdef __cplusplus

#include <locale>

#include "../../../brick_game/controller/Controller.h"
#include "../../interfaces/IView.h"

extern "C" {
#endif

#include "../../../gui/cli/CLI.h"

#ifdef __cplusplus
}
#endif

namespace s21 {
class ConsoleViewTemplate : public IView {
 public:
  explicit ConsoleViewTemplate(Controller &controller);
  int startEventLoop() override;
  static int render(GameInfo_t &gameInfo, int code);

 private:
  Controller &controller_;
};
}  // namespace s21

#endif  // CPP3_BRICKGAME_V2_0_1_CONSOLEVIEWTEMPLATE_H
