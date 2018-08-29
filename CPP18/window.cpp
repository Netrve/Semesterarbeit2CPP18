#include "window.h"

Window::Window(QWidget *parent) : QWidget(parent) {
  QGridLayout *gridLayout = new QGridLayout;
  createHorizontalGroupBox(gridLayout);
  myAvatar = new avatar;
  myAvatar->setFixedHeight(500);
  gridLayout->addWidget(myAvatar, 1, 0);
  setLayout(gridLayout);
  myAvatar->setFocus();
}

void Window::createHorizontalGroupBox(QGridLayout *gridLayout) {
  horizontalGroupBox = new QGroupBox(tr("Menu"));
  horizontalGroupBox->setFixedHeight(60);
  QHBoxLayout *layout = new QHBoxLayout;

  buttons[0] = new QPushButton(tr("Start"));
  connect(buttons[0], SIGNAL(released()), this, SLOT(startStop()));
  buttons[1] = new QPushButton(tr("Save"));
  connect(buttons[1], SIGNAL(released()), this, SLOT(saveFile()));
  buttons[2] = new QPushButton(tr("Load"));
  connect(buttons[2], SIGNAL(released()), this, SLOT(loadFile()));

  for (int i = 0; i < NumButtons; ++i) {
    layout->addWidget(buttons[i]);
  }
  horizontalGroupBox->setLayout(layout);
  gridLayout->addWidget(horizontalGroupBox, 0, 0);
}

void Window::saveFile(void) {
  QFileDialog dialog(this);
  QString fileName;
  QFile file;

  dialog.setFileMode(QFileDialog::AnyFile);
  fileName = dialog.getSaveFileName(this, tr("Save File"), ".",
                                    tr("Savegame (*.nsav)"));

  if (fileName.isNull() == false) {
    file.setFileName(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
      QMessageBox::warning(this, tr("Write Error"),
                           tr("The file can't be written to: ") + fileName,
                           QMessageBox::Ok);
    }

    myAvatar->serialize(file);
    file.close();
    return;
  }
}

void Window::loadFile(void) {
  QFileDialog dialog(this);
  QString fileName;
  QFile file;

  dialog.setFileMode(QFileDialog::AnyFile);
  fileName = dialog.getOpenFileName(this, tr("Open File"), ".",
                                    tr("Savegame (*.nsav)"));

  if (fileName.isNull() == false) {
    file.setFileName(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
      QMessageBox::warning(this, tr("Read Error"),
                           tr("The file can't be read: ") + fileName,
                           QMessageBox::Ok);
    }

    myAvatar->deserialize(file);
    file.close();
    return;
  }
}

void Window::startStop(void) {
  if (!gameState) {
    buttons[0]->setText("Stop");
    gameState = true;
    myAvatar->gameSwitch(gameState);
  } else {
    buttons[0]->setText("Start");
    gameState = false;
    myAvatar->gameSwitch(gameState);
  }
}
