#ifndef CAPPLOGGER_H
#define CAPPLOGGER_H

#include <qglobal.h>

#include <QFile>

class CAppLogger
{
  public:
    /**
     *  @internal
    */
    explicit      CAppLogger();
    ~             CAppLogger();
    /**
     *  @endinternal
    */

    static void   activate();

  private:
    /**
     *  @internal
    */
    static QFile* fLog;
    static void   messageHandler(QtMsgType type, const QMessageLogContext &context,
                                 const QString &msg);
    /**
     *  @endinternal
    */

};

/**
 * @class CAppLogger
 * @brief Application logger helper class
 *
 * This is a simple usage class, it's only intended for changing the way applications
 * and libraries logs messages into the system; by installing a new messages handler for
 * Qt Debugging classes, say qDebug, qCDebug, qWarning, qCWarning, etcetera. The output
 * format is [yyyy-MM-dd hh:mm:ss] {Message type (3 chars)} {category}: {message}. The only
 * thing you need to do to use it is by only calling the static method CAppLogger::activate().
 * The @ref CAppLogger::activate "activate" function, it will allow to log messages onto
 * console and application's log file in directory defined by Qt's definition named
 * @c QStandardPaths::AppDataLocation; by using above format.
 *
 * The following example shows how to use QLoggingCategory class to print logs to console
 * and a log file, by using any of @b "qC*" definitions.
 *
 * @code
 * #include <QLoggingCategory>
 * #include <QTimer>
 *
 * #include <CAppLogger>
 *
 * //In some header you declare the following
 * Q_DECLARE_LOGGING_CATEGORY(appTest)
 * /////
 *
 * //In some source code you declare de following
 * Q_LOGGING_CATEGORY(appTest, "app.test")
 * /////
 *
 * int main(int argc, char *argv[])
 * { //Application's description
 *   QCoreApplication::setApplicationName("Test Application");
 *   QCoreApplication::setOrganizationName("My company");
 *
 *   //Logger activation
 *   CAppLogger::activate();
 *
 *   QCoreApplication a(argc, argv);
 *
 *   QTimer::singleShot(3500, [] ()
 *   { //This will run 3.5 s after application start
 *     qCDebug(appTest()) << "Finalizing application...";
 *     qApp->quit();
 *     qCCritical(appTest()) << "We are closing";
 *   });
 *
 *   return a.exec();
 * }
 * @endcode
 *
 * @note
 * To use this class you must include library's configuration prefix in Qt's project file
 * just like the following:
 * <tt>CONFIG += dsapplogger</tt>
 * @author  Delver Domingo
 * @date    1977-2023
 */

/**
 * @fn static void CAppLogger::activate()
 * @brief Activate CAppLogger's logging posibilities
 *
 * This static method will make active CAppLogger's posibilities; it will thus allow you
 * to log messages to console and a log file.
 *
 */

#endif // CAPPLOGGER_H
