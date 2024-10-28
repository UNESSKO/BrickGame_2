//
// Created by KWAZAR_ on 07.09.2024.
//

#include "DesktopViewTemplate.h"

namespace s21 {
DesktopViewTemplate::DesktopViewTemplate(s21::Controller& controller)
    : controller_(controller) {}

int DesktopViewTemplate::startEventLoop() {
  std::setlocale(LC_NUMERIC, "C");
  srand(time(0));

  auto* view = new DesktopView(controller_);
  view->setWindowTitle("BrickGame");

  view->show();

  return 0;
}

}  // namespace s21