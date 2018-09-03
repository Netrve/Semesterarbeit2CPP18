#include "avatar.h"

avatar::avatar(QWidget *parent) : QWidget(parent) {
  setStyleSheet("border: 1px solid black; background-color: #fffffa");
  setAutoFillBackground(true);
  std::thread(&avatar::gameTick, this).detach();
}

void avatar::gameTick() {
  for (;;) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    gameProcess();
  }
}

void avatar::gameProcess() {
  if (gameActive) {
    update();
  }
}

void avatar::paintEvent(QPaintEvent *) {
  QPainter painter;
  painter.begin(this);
  painter.setPen(QPen(Qt::black, 2));
  if (posX > 800) {
    posX = 800;
  } else if (posX < 0) {
    posX = 0;
  }
  painter.drawRect(posX, 440, 40, 40);
  painter.end();
}

void avatar::gameSwitch(bool state) { gameActive = state; }

void avatar::mousePressEvent(QMouseEvent *event) {
  if (event) {
    setFocus();
  }
}

void avatar::keyPressEvent(QKeyEvent *event) {
  if (gameActive) {
    if (event->key() == Qt::Key_Left) {
      posX -= 10;
    } else if (event->key() & Qt::Key_Right) {
      posX += 10;
    }

    update();
  }
}

void avatar::serialize(QFile &file) {
  QTextStream out(&file);
  out << "avatarFormat" << endl;
  out << "p " << posX << endl;
  out << "o " << points << endl;
  out << "l " << lives << endl;
}

void avatar::deserialize(QFile &file) {
  QTextStream in(&file);
  while (!in.atEnd()) {
    QString line = in.readLine();
    if (line.contains("p")) {
      line.remove("p ");
      posX = line.toInt();
    }
    if (line.contains("o")) {
      line.remove("o ");
      points = line.toInt();
    }
    if (line.contains("l")) {
      line.remove("l ");
      lives = line.toInt();
    }
  }
  file.close();

  update();
}
