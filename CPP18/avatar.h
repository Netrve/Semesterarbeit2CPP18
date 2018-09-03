#ifndef AVATAR_H
#define AVATAR_H

#include <QMessageBox>
#include <QWidget>
#include <QtGui>
#include <chrono>
#include <thread>

class avatar : public QWidget {
public:
  avatar(QWidget *parent = 0);
  void serialize(QFile &file);
  void deserialize(QFile &file);
  void gameSwitch(bool state);
  void gameTick();
  void gameProcess();

private:
  int posX = 410;
  int points = 0;
  int lives = 3;
  bool gameActive = false;

protected:
  void paintEvent(QPaintEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void keyPressEvent(QKeyEvent *event);
};

#endif // AVATAR_H
