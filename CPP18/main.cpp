#include "window.h"
#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Window w;
  w.setFixedSize(QSize(860, 600));
  w.show();

  return a.exec();
}
