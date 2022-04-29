#ifndef CPROPERTIESTEST_H
#define CPROPERTIESTEST_H

#include <QObject>

class CTestWindow;

#include <QtProperty>
#include <QtTreePropertyBrowser>
#include <QtVariantProperty>
#include <QtVariantPropertyManager>

class CPropertiesTest : public QObject
{
    Q_OBJECT

  public:
    explicit                          CPropertiesTest(QObject* parent = nullptr);
    ~                                 CPropertiesTest();

  public slots:
    void                              init();

  private:
    CTestWindow*                      m_main;
    QtVariantPropertyManager*         variantManager;
    QtTreePropertyBrowser*            propertyEditor;

    QMap<QtProperty*, QString>        propertyToId;
    QMap<QString, QtVariantProperty*> idToProperty;

    void                              addProperty(QtVariantProperty *property,
                                                  const QString &id);

  private slots:
    void                              vpValueChanged(QtProperty *property,
                                                     const QVariant &value);
    void                              dialValueChanged(int newValue);
};

#endif // CPROPERTIESTEST_H
