#include <QCoreApplication>
#include <QDebug>
#include <QLoggingCategory>
#include <QTimer>

#include <CAppLogger>

//In some header you declare the following
Q_DECLARE_LOGGING_CATEGORY(appTest)
/////

//In some source code you declare de following
Q_LOGGING_CATEGORY(appTest, "app.test")
/////

int main(int argc, char *argv[])
{ //Application's description
  QCoreApplication::setApplicationName("Test Application");
  QCoreApplication::setOrganizationName("My company");

  //Logger activation
  CAppLogger::activate();

  QCoreApplication a(argc, argv);

  QTimer::singleShot(3500, [] ()
  { //This will run 3.5 s after application start
    qCDebug(appTest()) << "Finalizing application...";
    qApp->quit();
    qCCritical(appTest()) << "We are closing";
  });

  return a.exec();
}
