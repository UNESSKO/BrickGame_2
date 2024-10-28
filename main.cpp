//
// Created by KWAZAR_ on 17.08.2024.
//

#ifdef __cplusplus

#include "components/game_selection/GameSelection.h"
#include "gui/desktop/DesktopView.h"

extern "C" {
#endif

#ifdef __cplusplus
}
#endif

using namespace s21;

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  s21::GameSelection gameSelection;
  gameSelection.resize(300, 300);
  gameSelection.show();

  return app.exec();
}
