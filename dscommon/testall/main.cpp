#include "CTestWindow.h"

#include <QApplication>
#include <QLoggingCategory>

int main(int argc, char *argv[])
{
  QLoggingCategory::setFilterRules("qtc.ssh=false");

  QApplication a(argc, argv);
  CTestWindow w;
  w.show();

  return a.exec();
}
