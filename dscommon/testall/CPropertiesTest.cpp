#include "CPropertiesTest.h"
#include "CTestWindow.h"
#include "ui_CTestWindow.h"

#include <QDial>

CPropertiesTest::CPropertiesTest(QObject *parent)
  : QObject(parent), m_main(qobject_cast<CTestWindow*>(parent))
{ }

CPropertiesTest::~CPropertiesTest()
{ delete propertyEditor;
  delete variantManager;
}

void CPropertiesTest::init()
{ variantManager = new QtVariantPropertyManager(this);

  connect(variantManager, SIGNAL(valueChanged(QtProperty *, const QVariant &)),
          this, SLOT(vpValueChanged(QtProperty *, const QVariant &)));

  QtVariantEditorFactory* variantFactory = new QtVariantEditorFactory(m_main);

  propertyEditor = new QtTreePropertyBrowser(m_main->ui->wgtProperties);
  propertyEditor->setFactoryForManager(variantManager, variantFactory);
  m_main->ui->gloProps->addWidget(propertyEditor, 0, 0, -1, 1);

  connect(m_main->ui->dlPbTest, SIGNAL(valueChanged(int)), SLOT(dialValueChanged(int)));

  //As a single item to check for its properties, I must set properties once and
  //then check for their values change... the following must be done in another
  //method if you are going to check several objects.
  QMap<QtProperty *, QString>::ConstIterator itProp = propertyToId.constBegin();
  while (itProp != propertyToId.constEnd())
  { delete itProp.key();
    itProp++;
  }
  propertyToId.clear();
  idToProperty.clear();

  QtVariantProperty *property;
  QDial* i = m_main->ui->dlPbTest;

  property = variantManager->addProperty(QVariant::Bool, tr("Enabled"));
  if (property)
  { property->setValue(i->isEnabled());
    addProperty(property, QLatin1String("enabled"));
  }

  property = variantManager->addProperty(QVariant::String, tr("Tooltip"));
  if (property)
  { property->setValue(i->toolTip());
    addProperty(property, QLatin1String("tooltip"));
  }

  property = variantManager->addProperty(QVariant::Palette, tr("Palette"));
  if (property)
  { property->setValue(i->palette());
    addProperty(property, QLatin1String("palette"));
  }

  property = variantManager->addProperty(QVariant::Int, tr("Minimum"));
  if (property)
  { property->setValue(i->minimum());
    addProperty(property, QLatin1String("minimum"));
  }

  property = variantManager->addProperty(QVariant::Int, tr("Maximum"));
  if (property)
  { property->setValue(i->maximum());
    addProperty(property, QLatin1String("maximum"));
  }

  property = variantManager->addProperty(QVariant::Int, tr("Value"));
  if (property)
  { property->setValue(i->value());
    addProperty(property, QLatin1String("value"));
  }

  property = variantManager->addProperty(QVariant::Bool, tr("Wrapping"));
  if (property)
  { property->setValue(i->wrapping());
    addProperty(property, QLatin1String("wrapping"));
  }
}

void CPropertiesTest::addProperty(QtVariantProperty* property, const QString& id)
{ propertyToId[property] = id;
  idToProperty[id] = property;
  propertyEditor->addProperty(property);
}

void CPropertiesTest::vpValueChanged(QtProperty* property, const QVariant& value)
{ if (!propertyToId.contains(property)) return;

  QDial*  i   = m_main->ui->dlPbTest;
  QString id  = propertyToId[property];

  if (id == QLatin1String("enabled")) i->setEnabled(value.toBool());
  else if (id == QLatin1String("tooltip")) i->setToolTip(value.toString());
  else if (id == QLatin1String("palette")) i->setPalette(value.value<QPalette>());
  else if (id == QLatin1String("minimum")) i->setMinimum(value.toInt());
  else if (id == QLatin1String("maximum")) i->setMaximum(value.toInt());
  else if (id == QLatin1String("value")) i->setValue(value.toInt());
  else if (id == QLatin1String("wrapping")) i->setWrapping(value.toBool());
}

void CPropertiesTest::dialValueChanged(int newValue)
{ variantManager->setValue(idToProperty[QLatin1String("value")], newValue); }
