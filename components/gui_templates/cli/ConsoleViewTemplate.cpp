#include "ConsoleViewTemplate.h"

namespace s21 {
ConsoleViewTemplate::ConsoleViewTemplate(s21::Controller &controller)
    : controller_(controller) {}

int ConsoleViewTemplate::render(GameInfo_t &gameInfo, int code) {
  return ::render(&gameInfo, code);
}

int ConsoleViewTemplate::startEventLoop() {
  setlocale(LC_ALL, "");
  srand(time(0));

  ncursesInit();

  UserAction_t action = Start;

  bool hold = false;

  int code = 1;

  while (code) {
    int key = getch();

    controller_.getInput(&action, &hold, key);
    controller_.userInput(action, hold);

    if (action == Terminate) {
      endwin();
      break;
    }

    GameInfo_t gameInfo = controller_.updateCurrentState();

    code = render(gameInfo, controller_.getGameStateCode());

    timeout(gameInfo.speed);
  }

  return 0;
}
}  // namespace s21