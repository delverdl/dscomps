#ifndef CTESTWINDOW_H
#define CTESTWINDOW_H

#include <QWidget>

#include <CAbstractPrinter>

namespace Ui {
class CTestWindow;
}

class CCryptTest;
class CSshTest;
class CPropertiesTest;
class CWidgetsTest;

class CTestWindow : public QWidget
{
    Q_OBJECT
    friend            class CCryptTest;
    friend            class CSshTest;
    friend            class CPropertiesTest;
    friend            class CWidgetsTest;

  public:
    explicit          CTestWindow(QWidget* parent = nullptr);
    ~                 CTestWindow();

  private slots:
    void              on_pbClose_clicked();
    void              testPrintStart();
    void              testOpenPrinter();
    void              testDoPrint();
    void              testFinishPrint();

    void on_pbDecompress_clicked();

  protected:
    void              closeEvent(QCloseEvent* event);

  private:
    Ui::CTestWindow*  ui;

    CCryptTest*       m_cry;
    CSshTest*         m_ssh;
    CPropertiesTest*  m_props;
    CWidgetsTest*     m_wgt;
    CAbstractPrinter* m_printer;

    void              releaseResources();
    void              printerStatus(DeviceStatus ds);
    void              printDone(bool b);

};

#endif // CTESTWINDOW_H
