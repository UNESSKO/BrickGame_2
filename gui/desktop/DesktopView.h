//
// Created by KWAZAR_ on 17.08.2024.
//

#ifndef CPP3_BRICKGAME_V2_0_1_DESKTOPVIEW_H
#define CPP3_BRICKGAME_V2_0_1_DESKTOPVIEW_H

#ifdef __cplusplus

#include <QtCore>
#include <QtGui>
#include <QtWidgets>

#include "../../brick_game/controller/Controller.h"

extern "C" {
#endif

#include "../../components/GameInfo.h"

#ifdef __cplusplus
}
#endif

namespace s21 {
class DesktopView : public QMainWindow {
  Q_OBJECT

 public:
  explicit DesktopView(Controller &controller);
  ~DesktopView() override;

 private:
  QWidget *wid_;
  Controller &controller_;
  QTimer *timer_;
  QHBoxLayout *gameLayout_;
  QVBoxLayout *infoTable_;
  QGraphicsScene *gameScene_;
  QGraphicsView *gameView_;
  QGraphicsScene *nextScene_;
  QGraphicsView *nextView_;
  QGraphicsRectItem **gameField_;
  QGraphicsRectItem **nextField_;
  QLabel *Score_;
  QLabel *Level_;
  QLabel *HighScore_;
  QGraphicsTextItem *textNext_;
  QGraphicsTextItem *startBanner_;
  QGraphicsTextItem *gameOverBanner_;
  QGraphicsTextItem *pauseBanner_;
  QGraphicsTextItem *winBanner_;
  int heightGameField_;

  void keyPressEvent(QKeyEvent *event) override;
  void pseudoKeyPressEvent();
  void mousePressEvent(QMouseEvent *event) override;
  void initLayout(int **gameField, bool next);
  void initLabels();
  static void quit();
  void render(const GameInfo_t &gameInfo, int code);
  void createGameField(int height, int width);
  void createNextField();
  void createInfoTable(bool next);
  void updateNextField(int **next);
  static void drawBanner(QGraphicsTextItem *banner);
  static void hideBanner(QGraphicsTextItem *banner);
  void updateGameField(int **field);
  static void updateLabelDetails(QLabel *label, const char *base, int value);
  static int isFigure(int symbol);
  static QColor getColor(int symbol);
  static void newMatrix(QGraphicsRectItem **&matrix, int height, int width);
  static void removeFieldMatrix(QGraphicsRectItem **matrix, int height);
  static void initFieldMatrix(QGraphicsRectItem **, QGraphicsScene *,
                              int height, int width, int step);
};
}  // namespace s21

#endif  // CPP3_BRICKGAME_V2_0_1_DESKTOPVIEW_H
