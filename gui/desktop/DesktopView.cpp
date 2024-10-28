#include "DesktopView.h"

namespace s21 {
DesktopView::DesktopView(Controller &controller)
    : QMainWindow(nullptr),
      wid_(new QWidget()),
      controller_(controller),
      timer_(new QTimer()),
      gameLayout_(new QHBoxLayout()),
      infoTable_(new QVBoxLayout()),
      gameScene_(new QGraphicsScene()),
      gameView_(new QGraphicsView(gameScene_)),
      nextScene_(new QGraphicsScene()),
      nextView_(new QGraphicsView(nextScene_)),
      gameField_(nullptr),
      nextField_(nullptr),
      Score_(new QLabel()),
      Level_(new QLabel()),
      HighScore_(new QLabel()),
      textNext_(new QGraphicsTextItem()),
      startBanner_(new QGraphicsTextItem()),
      gameOverBanner_(new QGraphicsTextItem()),
      pauseBanner_(new QGraphicsTextItem()),
      winBanner_(new QGraphicsTextItem()),
      heightGameField_(0) {
  setStyleSheet("background-color: white;");

  setCentralWidget(wid_);
  wid_->setLayout(gameLayout_);

  setFocus();

  connect(timer_, &QTimer::timeout, this, &DesktopView::pseudoKeyPressEvent);

  GameInfo_t gameInfo = controller_.updateCurrentState();
  initLayout(gameInfo.field, gameInfo.next);

  gameView_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  gameView_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  pseudoKeyPressEvent();
}

void DesktopView::pseudoKeyPressEvent() {
  QKeyEvent event(QEvent::KeyPress, -1, Qt::NoModifier, QString());

  keyPressEvent(&event);
}

void DesktopView::keyPressEvent(QKeyEvent *event) {
  timer_->stop();

  UserAction_t action = Start;
  bool hold = false;

  controller_.getInput(&action, &hold, event->key());
  controller_.userInput(action, hold);

  if (action == UserAction_t::Terminate) quit();

  GameInfo_t gameInfo = controller_.updateCurrentState();

  render(gameInfo, controller_.getGameStateCode());

  timer_->setInterval(gameInfo.speed);
  timer_->start();
}

void DesktopView::initLayout(int **field, bool next) {
  int height = field[0][0] - 1;
  int width = field[1][0] - 2;

  createGameField(height, width);

  createInfoTable(next);

  gameLayout_->addWidget(gameView_);
  gameLayout_->addLayout(infoTable_);
}

void DesktopView::createGameField(int height, int width) {
  heightGameField_ = height;

  newMatrix(gameField_, height, width);
  initFieldMatrix(gameField_, gameScene_, height, width, 40);

  gameView_->setSceneRect(0, 0, width * 40, height * 40);
  gameView_->setFixedSize(width * 40 + 10, height * 40 + 10);

  gameScene_->setBackgroundBrush(QBrush(Qt::black));
  gameView_->setBackgroundBrush(QBrush(Qt::black));

  startBanner_->setPos(25, 350);
  startBanner_->setHtml(
      "<p style='color: #000000; font-weight: bold; "
      "font-size: 30px;'>Press Enter to start!</p>");
  startBanner_->setVisible(false);
  gameScene_->addItem(startBanner_);

  gameOverBanner_->setPos(90, 300);
  gameOverBanner_->setHtml(
      "<p style='color: #000000; font-weight: bold; font-size: "
      "35px;'>Game Over</p>");
  gameOverBanner_->setVisible(false);
  gameScene_->addItem(gameOverBanner_);

  pauseBanner_->setPos(110, 350);
  pauseBanner_->setHtml(
      "<p style='color: #000000; font-weight: bold; "
      "font-size: 55px;'>Pause</p>");
  pauseBanner_->setVisible(false);
  gameScene_->addItem(pauseBanner_);

  winBanner_->setPos(75, 300);
  winBanner_->setHtml(
      "<p style='color: #000000; font-weight: bold; font-size: "
      "55px;'>You Win!</p>");
  winBanner_->setVisible(false);
  gameScene_->addItem(winBanner_);

  gameView_->setBackgroundBrush(Qt::black);
  gameView_->setFixedSize(width * 40 + 10, height * 40 + 10);
}

void DesktopView::createNextField() {
  int height = 5, width = 6, size = 40;

  newMatrix(nextField_, height, width);
  initFieldMatrix(nextField_, nextScene_, height, width, size);

  textNext_->setPos(20, 10);
  textNext_->setHtml(
      "<p style='color: #000000; font-weight: bold; font-size: "
      "35px;'>Next</p>");

  nextScene_->addItem(textNext_);

  nextView_->setBackgroundBrush(Qt::black);
  nextView_->setFixedSize(width * size + 10, height * size + 10);
}

void DesktopView::createInfoTable(bool next) {
  infoTable_->setSpacing(40);

  if (next) {
    createNextField();
    infoTable_->addWidget(nextView_);
  }

  initLabels();

  infoTable_->addWidget(HighScore_);
  infoTable_->addWidget(Score_);
  infoTable_->addWidget(Level_);

  infoTable_->addStretch();

  infoTable_->setContentsMargins(20, 0, 0, 0);
}

void DesktopView::initLabels() {
  HighScore_->setText("HighScore  0");
  Score_->setText("Score  0");
  Level_->setText("Level 0");

  HighScore_->setStyleSheet(
      "color: #000000; font-weight: bold; font-size: 25px");
  Score_->setStyleSheet("color: #000000; font-weight: bold; font-size: 25px; ");
  Level_->setStyleSheet("color: #000000; font-weight: bold; font-size: 25px; ");

  HighScore_->setAlignment(Qt::AlignLeft);
  HighScore_->setContentsMargins(10, 30, 40, 30);

  Score_->setAlignment(Qt::AlignLeft);
  Score_->setContentsMargins(10, 30, 0, 30);

  Level_->setAlignment(Qt::AlignLeft);
  Level_->setContentsMargins(10, 30, 0, 30);
}

void DesktopView::drawBanner(QGraphicsTextItem *banner) {
  banner->setVisible(true);
}

void DesktopView::hideBanner(QGraphicsTextItem *banner) {
  banner->setVisible(false);
}

void DesktopView::initFieldMatrix(QGraphicsRectItem **matrix,
                                  QGraphicsScene *scene, int height, int width,
                                  int step) {
  int pos_x = 0, pos_y = 0;

  for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++) {
      matrix[i][j].setRect(pos_x, pos_y, step, step);

      scene->addItem(matrix[i] + j);

      matrix[i][j].setBrush(Qt::white);
      matrix[i][j].setPen(Qt::NoPen);

      pos_x += step;

      if (j == width - 1) {
        pos_x = 0;
        pos_y += step;
      }
    }
}

void DesktopView::quit() { QApplication::quit(); }

int DesktopView::isFigure(int symbol) {
  return symbol >= '*' ? symbol - '*' : 0;
}

QColor DesktopView::getColor(int symbol) {
  switch (symbol) {
    case 0:
      return QColor(2, 93, 255);  // blue
    case 1:
      return QColor(255, 3, 62);  // red
    case 2:
      return QColor(214, 0, 110);  // pink
    case 3:
      return QColor(0, 128, 0);  // Dark Green
    case 4:
      return QColor(27, 230, 176);  // azure
    case 5:
      return QColor(153, 17, 153);  // magenta
    case 6:
      return QColor(0, 255, 255);  // cyan
    case 7:
      return QColor(99, 93, 99);  // gray
  }

  return Qt::black;
}

void DesktopView::updateGameField(int **field) {
  int color = 0, symbol;
  int height = field[0][0] - 1;
  int width = field[1][0] - 1;

  for (int i = 0; i < height; i++) {
    for (int j = 1; j < width; j++) {
      symbol = field[i][j];

      color = isFigure(symbol);

      if (symbol >= '*') {
        gameField_[i][j - 1].setBrush(getColor(color));
        gameField_[i][j - 1].setPen(QPen());
      } else {
        gameField_[i][j - 1].setBrush(Qt::white);
        gameField_[i][j - 1].setPen(Qt::NoPen);
      }
    }
  }
}

void DesktopView::updateLabelDetails(QLabel *label, const char *base,
                                     int value) {
  label->setText(base + QString::number(value));
}

void DesktopView::updateNextField(int **field) {
  int color = field[0][5];

  for (int i = 0, shift = 2; i < 2; i++)
    for (int j = 0; j < 4; j++) {
      int sym = field[i + 2][j];

      if (!sym) {
        nextField_[i + shift][j + 1].setBrush(Qt::white);
        nextField_[i + shift][j + 1].setPen(Qt::NoPen);
      } else {
        nextField_[i + shift][j + 1].setBrush(getColor(color));
        nextField_[i + shift][j + 1].setPen(QPen());
      }
    }
}

void DesktopView::render(const GameInfo_t &gameInfo, int code) {
  hideBanner(startBanner_);
  hideBanner(gameOverBanner_);

  if (gameInfo.field) updateGameField(gameInfo.field);

  if (code == 1 || code == 2 || code == 3) {
    if (code == 3) {
      drawBanner(winBanner_);
      QTimer::singleShot(1500, this, &DesktopView::quit);
      return;
    }

    if (code == 2) drawBanner(gameOverBanner_);

    drawBanner(startBanner_);
  } else {
    hideBanner(startBanner_);
    hideBanner(gameOverBanner_);
  }

  if (gameInfo.pause)
    drawBanner(pauseBanner_);
  else
    hideBanner(pauseBanner_);

  if (gameInfo.next) updateNextField(gameInfo.next);

  updateLabelDetails(HighScore_, "HighScore  ", gameInfo.high_score);
  updateLabelDetails(Score_, "Score  ", gameInfo.score);
  updateLabelDetails(Level_, "Level  ", gameInfo.level);
}

void DesktopView::mousePressEvent(QMouseEvent *event) {
  Q_UNUSED(event);
  setFocus();
}

void DesktopView::newMatrix(QGraphicsRectItem **&matrix, int height,
                            int width) {
  matrix = new QGraphicsRectItem *[height];

  for (int i = 0; i < height; ++i) matrix[i] = new QGraphicsRectItem[width];
}

void DesktopView::removeFieldMatrix(QGraphicsRectItem **matrix, int height) {
  for (int i = 0; i < height; ++i) delete[] matrix[i];

  delete[] matrix;
}

DesktopView::~DesktopView() {
  delete HighScore_;
  delete Score_;
  delete Level_;

  delete textNext_;

  removeFieldMatrix(gameField_, heightGameField_);

  if (nextField_) removeFieldMatrix(nextField_, 5);

  delete nextView_;
  delete nextScene_;

  delete infoTable_;

  delete gameView_;
  delete gameScene_;

  delete gameLayout_;

  delete wid_;
}
}  // namespace s21
