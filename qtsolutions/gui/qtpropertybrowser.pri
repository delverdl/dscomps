INCLUDEPATH         +=  $$PWD
DEPENDPATH          +=  $$PWD

SOURCES             +=  $$PWD/qtpropertybrowser.cpp \
                        $$PWD/qtpropertymanager.cpp \
                        $$PWD/qteditorfactory.cpp \
                        $$PWD/qtvariantproperty.cpp \
                        $$PWD/qttreepropertybrowser.cpp \
                        $$PWD/qtbuttonpropertybrowser.cpp \
                        $$PWD/qtgroupboxpropertybrowser.cpp \
                        $$PWD/qtpropertybrowserutils.cpp

HDR_PUBLIC          +=  $$PWD/qtpropertybrowser.h \
                        $$PWD/qtpropertymanager.h \
                        $$PWD/qteditorfactory.h \
                        $$PWD/qtvariantproperty.h \
                        $$PWD/qttreepropertybrowser.h \
                        $$PWD/qtbuttonpropertybrowser.h \
                        $$PWD/qtgroupboxpropertybrowser.h

HEADERS             +=  $$HDR_PUBLIC \
                        $$PWD/qtpropertybrowserutils_p.h

HDR_INSTALL         +=  $$PWD/QtAbstractEditorFactoryBase $$PWD/QtAbstractPropertyBrowser \
                        $$PWD/QtAbstractPropertyManager $$PWD/QtBoolPropertyManager \
                        $$PWD/QtBrowserItem $$PWD/QtButtonPropertyBrowser \
                        $$PWD/QtCharEditorFactory $$PWD/QtCharPropertyManager \
                        $$PWD/QtCheckBoxFactory $$PWD/QtColorEditorFactory \
                        $$PWD/QtColorPropertyManager $$PWD/QtCursorEditorFactory \
                        $$PWD/QtCursorPropertyManager $$PWD/QtDateEditFactory \
                        $$PWD/QtDatePropertyManager $$PWD/QtDateTimeEditFactory \
                        $$PWD/QtDateTimePropertyManager $$PWD/QtDoublePropertyManager \
                        $$PWD/QtDoubleSpinBoxFactory $$PWD/QtEnumEditorFactory \
                        $$PWD/QtEnumPropertyManager $$PWD/QtFlagPropertyManager \
                        $$PWD/QtFontEditorFactory $$PWD/QtFontPropertyManager \
                        $$PWD/QtGroupBoxPropertyBrowser $$PWD/QtGroupPropertyManager \
                        $$PWD/QtIntPropertyManager $$PWD/QtKeySequenceEditorFactory \
                        $$PWD/QtKeySequencePropertyManager $$PWD/QtLineEditFactory \
                        $$PWD/QtLocalePropertyManager $$PWD/QtPointFPropertyManager \
                        $$PWD/QtPointPropertyManager $$PWD/QtProperty \
                        $$PWD/QtRectFPropertyManager $$PWD/QtRectPropertyManager \
                        $$PWD/QtScrollBarFactory $$PWD/QtSizeFPropertyManager \
                        $$PWD/QtSizePolicyPropertyManager $$PWD/QtSizePropertyManager \
                        $$PWD/QtSliderFactory $$PWD/QtSpinBoxFactory \
                        $$PWD/QtStringPropertyManager $$PWD/QtTimeEditFactory \
                        $$PWD/QtTimePropertyManager $$PWD/QtTreePropertyBrowser \
                        $$PWD/QtVariantEditorFactory $$PWD/QtVariantProperty \
                        $$PWD/QtVariantPropertyManager \
                        $$HDR_PUBLIC

RESOURCES           +=  $$PWD/qtpropertybrowser.qrc

win32:dll:DEFINES   +=  QT_QTPROPERTYBROWSER_EXPORT
