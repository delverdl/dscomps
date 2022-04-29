#include <QCoreApplication>
#include <QLoggingCategory>

#include "CSshTester.h"

int main(int argc, char *argv[])
{
  QLoggingCategory::setFilterRules("qtc.ssh=false");

  QCoreApplication  a(argc, argv);
  CSshTester        *tst;

  tst = new CSshTester(&a);
  tst->start();
  return a.exec();
}
