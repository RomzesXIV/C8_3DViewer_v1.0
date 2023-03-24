#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  setenv("LC_NUMERIC", "C", 1);
  QApplication a(argc, argv);
  QApplication::setOrganizationName("21_school_team");
  QApplication::setApplicationName("s21_3dViewer_1.0");
  MainWindow w;
  w.show();
  return a.exec();
}
