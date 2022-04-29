#include <QCoreApplication>
#include <QLoggingCategory>

#include "CSftpTester.h"

int main(int argc, char *argv[])
{
  QLoggingCategory::setFilterRules("qtc.ssh=false");

  QCoreApplication  a(argc, argv);
  CSftpTester        *tst;

  tst = new CSftpTester(&a);
  tst->start();
  return a.exec();
}
