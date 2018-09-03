#ifndef PLAYFIELD_H
#define PLAYFIELD_H

#include "entity.h"
#include <QPainter>
#include <QWidget>
#include <chrono>
#include <thread>

class playfield : public QWidget {
  Q_OBJECT

public:
  playfield(QWidget *parent = 0);
  ~playfield();
  bool gameSwitch();

private:
  QPainter *painter;
  bool gameActive = false;
  bool gameDeath = false;
  int points = 0;
  int lifes = 3;
  int playerX = 410;
  void subtractLife();
  void gameOver();
  void restartGame();
  void drawPlayer(QPainter *painterIn);
  void drawScore(QPainter *painterIn);
  void drawLifes(QPainter *painterIn);
  void drawPauseGameOver(QPainter *painterIn);

protected:
  void gameTick();
  void paintEvent(QPaintEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void keyPressEvent(QKeyEvent *event);
};

/*
  void serialize(QFile &file);
  void deserialize(QFile &file);
*/

#endif // PLAYFIELD_H
