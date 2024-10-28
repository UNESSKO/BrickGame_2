// GameSelection.h
#ifndef GAMESELECTION_H
#define GAMESELECTION_H

#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "../../brick_game/controller/Controller.h"
#include "../../brick_game/snake/include/SnakeModel.h"
#include "../../brick_game/tetris/model/TetrisModel.h"
#include "../gui_templates/cli/ConsoleViewTemplate.h"
#include "../gui_templates/desktop/DesktopViewTemplate.h"
#include "../interfaces/IModel.h"
#include "../interfaces/IView.h"

namespace s21 {
enum class GameType { Snake, Tetris };
enum class GuiType { Desktop, CLI };

class GameSelection : public QWidget {
  Q_OBJECT
 public:
  explicit GameSelection(QWidget *parent = nullptr);

 private slots:
  void onStartButtonClicked();

 private:
  QComboBox *gameComboBox;
  QComboBox *guiComboBox;
  QPushButton *startButton;

  GameType getSelectedGameType();
  GuiType getSelectedGuiType();

  static IModel *createModel(GameType type);
  static IView *createView(GuiType type, Controller &controller);
};
}  // namespace s21

#endif  // GAMESELECTION_H
