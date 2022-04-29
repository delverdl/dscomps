#include "CWidgetsTest.h"
#include "CTestWindow.h"
#include "ui_CTestWindow.h"

#include <QwwButtonLineEdit>
#include <qwt_thermo.h>
#include <qwt_scale_draw.h>
#include <qwt_color_map.h>

#include <QMessageBox>

CWidgetsTest::CWidgetsTest(QObject *parent)
  : QObject(parent), m_main(qobject_cast<CTestWindow*>(parent))
{ }

CWidgetsTest::~CWidgetsTest()
{  }

void CWidgetsTest::init()
{ m_le = new QwwButtonLineEdit(m_main->ui->wgtWidgets);
  m_le->setText("Test text...");
  m_le->setButtonPosition(QwwButtonLineEdit::RightInside);
  m_le->setIcon(QPixmap(":/help-about.png"));
  m_le->setVisible(false);
  connect(m_le, SIGNAL(buttonClicked()), SLOT(leButtonClicked()));

  m_trm = new QwtThermo(m_main->ui->wgtWidgets);
  m_trm->setValue(53.8);
  m_trm->setVisible(false);

  m_main->ui->gloWidgets->addWidget(m_le, 2, 0);
  m_main->ui->gloWidgets->addWidget(m_trm, 2, 1);

  connect(m_main->ui->pbWgtShow, SIGNAL(toggled(bool)), SLOT(showToggled(bool)));
}

void CWidgetsTest::showToggled(bool on)
{ m_le->setVisible(on);
  m_trm->setVisible(on);
  m_main->ui->pbWgtShow->setText(on ? QString("&Hide") : QString("S&how"));
}

void CWidgetsTest::leButtonClicked()
{ QMessageBox::information(m_main, "Info", m_le->text()); }
