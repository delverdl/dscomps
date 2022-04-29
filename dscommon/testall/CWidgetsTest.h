#ifndef CWIDGETSTEST_H
#define CWIDGETSTEST_H

#include <QObject>

class CTestWindow;
class QwwButtonLineEdit;
class QwtThermo;

class CWidgetsTest : public QObject
{
    Q_OBJECT
  public:
    explicit            CWidgetsTest(QObject *parent = 0);
    ~                   CWidgetsTest();

  public slots:
    void                init();

  private:
    CTestWindow*        m_main;
    QwwButtonLineEdit*  m_le;
    QwtThermo*          m_trm;

  private slots:
    void                showToggled(bool on);
    void                leButtonClicked();
};

#endif // CWIDGETSTEST_H
