#include "playfield.h"

playfield::playfield(QWidget *parent) : QWidget(parent) {
  QPalette pal = palette();
  pal.setColor(QPalette::Background, QColor(200, 200, 200));
  setAutoFillBackground(true);
  setPalette(pal);
  setGeometry(0, 0, 860, 500);

  painter = new QPainter;
  std::thread(&playfield::gameTick, this).detach();
}

playfield::~playfield() { delete painter; }

void playfield::paintEvent(QPaintEvent *event) {
  if (event) {
    painter->begin(this);
    if (gameActive) {
      // Set Font
      QFont gameFont("Arial", 24, QFont::Bold, false);
      painter->setFont(gameFont);

      // Draw Elements
      drawPlayer(painter);
      drawScore(painter);
      drawLifes(painter);
    } else {
      // Set Font
      QFont gameFont("Arial", 24, QFont::Bold, false);
      painter->setFont(gameFont);

      // Draw Elements
      drawPlayer(painter);
      drawScore(painter);
      drawLifes(painter);
      drawPauseGameOver(painter);
    }
    painter->end();
  }
}

void playfield::drawPlayer(QPainter *painterIn) {
  painterIn->setBrush(Qt::BDiagPattern);
  painterIn->drawRect(playerX, 440, 40, 40);
}

void playfield::drawScore(QPainter *painterIn) {
  painterIn->setPen(QPen(Qt::black, 2));
  painterIn->drawText(QPointF(10, 34), QString::number(points / 10));
}

void playfield::drawLifes(QPainter *painterIn) {
  painterIn->setPen(QPen(Qt::darkGreen, 2));
  painterIn->drawText(QPointF(712, 34), "❤ ❤ ❤");

  painterIn->setPen(QPen(Qt::red, 2));
  switch (lifes) {
  case 2:
    painterIn->drawText(QPointF(712, 34), "❤");
    break;
  case 1:
    painterIn->drawText(QPointF(712, 34), "❤ ❤");
    break;
  case 0:
    painterIn->drawText(QPointF(712, 34), "❤ ❤ ❤");
    break;
  }
}

void playfield::drawPauseGameOver(QPainter *painterIn) {
  if (gameDeath) {
    painterIn->setPen(QPen(Qt::darkRed, 2));
    painterIn->drawText(QRectF(0, 0, 840, 440), Qt::AlignCenter, "GAME OVER");

    // Set Font
    QFont gameFont("Arial", 16, QFont::Bold, false);
    painterIn->setFont(gameFont);
    painterIn->drawText(QRectF(0, 0, 840, 500), Qt::AlignCenter,
                        "Click to Restart");
  } else {
    painterIn->setPen(QPen(Qt::black, 2));
    painterIn->drawText(QRectF(0, 0, 840, 500), Qt::AlignCenter, "PAUSED");
  }
}

void playfield::subtractLife() {
  if (lifes > 0) {
    lifes -= 1;
  }
  if (lifes <= 0) {
    gameOver();
  }
}

void playfield::gameOver() {
  if (gameActive) {
    gameActive = false;
    gameDeath = true;
  }
}

void playfield::restartGame() {
  if (!gameActive) {
    gameActive = true;
    gameDeath = false;
    points = 0;
    lifes = 3;
  }
}

bool playfield::gameSwitch() {
  if (gameActive) {
    gameActive = false;
  } else {
    gameActive = true;
  }
  update();
  return gameActive;
}

void playfield::gameTick() {
  for (;;) {
    std::this_thread::sleep_for(std::chrono::milliseconds(32));
    if (gameActive) {
      points += 5;
      if (points % 2000 == 0) {
        subtractLife();
      }
      update();
    }
  }
}

void playfield::mousePressEvent(QMouseEvent *event) {
  if (event) {
    if (gameActive) {
      setFocus();
    } else {
      restartGame();
    }
  }
}

void playfield::keyPressEvent(QKeyEvent *event) {
  if (gameActive) {
    if (event->key() == Qt::Key_Left) {
      playerX -= 10;
    } else if (event->key() & Qt::Key_Right) {
      playerX += 10;
    }
    update();
  }
}
