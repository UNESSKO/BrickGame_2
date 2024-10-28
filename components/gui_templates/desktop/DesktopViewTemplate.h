#ifndef CPP3_BRICKGAME_V2_0_1_DESKTOPVIEWTEMPLATE_H
#define CPP3_BRICKGAME_V2_0_1_DESKTOPVIEWTEMPLATE_H

#ifdef __cplusplus

#include <QtCore>
#include <QtGui>
#include <QtWidgets>

#include "../../../brick_game/controller/Controller.h"
#include "../../../gui/desktop/DesktopView.h"
#include "../../interfaces/IView.h"

extern "C" {
#endif

#ifdef __cplusplus
}
#endif

namespace s21 {
class DesktopViewTemplate : public IView {
 public:
  explicit DesktopViewTemplate(Controller &controller);

  int startEventLoop() override;

 private:
  Controller &controller_;
};
}  // namespace s21

#endif  // CPP3_BRICKGAME_V2_0_1_DESKTOPVIEWTEMPLATE_H
