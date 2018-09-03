#ifndef WINDOW_H
#define WINDOW_H

//#include "avatar.h"
//#include "entity.h"
#include "playfield.h"
// #include <QFileDialog>
#include <QGridLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QPushButton>
#include <QWidget>

class Window : public QWidget {
  Q_OBJECT

public:
  Window(QWidget *parent = 0);

private:
  int NumButtons = 3;
  playfield *myPlayfield;
  QPushButton *buttons[4];
  QGroupBox *horizontalGroupBox;
  void createHorizontalGroupBox(QGridLayout *gridLayout);

private slots:
  // void saveFile(void);
  // void loadFile(void);
  void startStop(void);
};

#endif // WINDOW_H
