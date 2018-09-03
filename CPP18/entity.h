#ifndef ENTITY_H
#define ENTITY_H

#include <QDebug>
#include <QWidget>
#include <QtGui>
#include <random>

class Entity : public QWidget {

public:
  Entity(QWidget *parent = 0);
  void genEntity();

private:
  int genNumber(int min, int max);

  int posX = 0;
  int posY = 0;
  int speed = 0;
  int deviation = 0;
  bool pickUp = false;

  // Generation Parameters
  int minSpeed = 20;
  int maxSpeed = 50;

  int maxPosX = 860;
  int maxPosY = 100;
};

#endif // ENTITY_H
