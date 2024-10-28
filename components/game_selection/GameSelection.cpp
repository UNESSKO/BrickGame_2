#include "GameSelection.h"

#include <QApplication>
#include <QMessageBox>

namespace s21 {
GameSelection::GameSelection(QWidget *parent) : QWidget(parent) {
  gameComboBox = new QComboBox(this);
  gameComboBox->addItem("Snake");
  gameComboBox->addItem("Tetris");

  guiComboBox = new QComboBox(this);
  guiComboBox->addItem("Desktop");
  guiComboBox->addItem("CLI");

  startButton = new QPushButton("Start", this);

  auto *layout = new QVBoxLayout(this);
  layout->addWidget(gameComboBox);
  layout->addWidget(guiComboBox);
  layout->addWidget(startButton);

  connect(startButton, &QPushButton::clicked, this,
          &GameSelection::onStartButtonClicked);
}

GameType GameSelection::getSelectedGameType() {
  switch (gameComboBox->currentIndex()) {
    case 0:
      return GameType::Snake;
    case 1:
      return GameType::Tetris;
    default:
      return GameType::Snake;
  }
}

GuiType GameSelection::getSelectedGuiType() {
  switch (guiComboBox->currentIndex()) {
    case 0:
      return GuiType::Desktop;
    case 1:
      return GuiType::CLI;
    default:
      return GuiType::Desktop;
  }
}

IModel *GameSelection::createModel(GameType type) {
  if (type == GameType::Snake)
    return new SnakeModel();
  else if (type == GameType::Tetris)
    return new TetrisModel();
  return nullptr;
}

IView *GameSelection::createView(GuiType type, Controller &controller) {
  if (type == GuiType::Desktop)
    return new DesktopViewTemplate(controller);
  else if (type == GuiType::CLI)
    return new ConsoleViewTemplate(controller);
  return nullptr;
}

void GameSelection::onStartButtonClicked() {
  GameType gameType = getSelectedGameType();
  GuiType guiType = getSelectedGuiType();

  IModel *model = createModel(gameType);
  if (!model) {
    QMessageBox::critical(this, "Error", "Failed to create model.");
    return;
  }

  auto *controller = new Controller(model);

  IView *view = createView(guiType, *controller);
  if (!view) {
    QMessageBox::critical(this, "Error", "Failed to create view.");
    delete model;
    return;
  }

  this->close();
  view->startEventLoop();
  delete view;
}
}  // namespace s21