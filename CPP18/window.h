#ifndef WINDOW_H
#define WINDOW_H

#include "avatar.h"
#include <QCloseEvent>
#include <QFileDialog>
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
  bool gameState = false;
  enum { NumGridRows = 2, NumButtons = 3 };

  avatar *myAvatar;
  QPushButton *buttons[NumButtons];
  QGroupBox *horizontalGroupBox;

  void createHorizontalGroupBox(QGridLayout *gridLayout);
  void openDialog(void);

private slots:
  void saveFile(void);
  void loadFile(void);
  void startStop(void);
};

#endif // WINDOW_H
