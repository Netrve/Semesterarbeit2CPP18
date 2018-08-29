#include "window.h"
#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Window w;
  QSize size = qApp->screens()[0]->size();
  w.setFixedSize(QSize(860, 600));
  w.setGeometry(size.width() / 2 - 430, size.height() / 2 - 300, 860, 600);
  w.show();

  return a.exec();
}
