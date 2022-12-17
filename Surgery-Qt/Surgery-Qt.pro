QT       += core gui sql network webengine webenginewidgets

greaterThan(QT_MAJOR_VERSION, 6): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Authorization/Source/user.cpp \
    Authorization/Window/authorizationmainwindow.cpp \
    Db/databasemanager.cpp \
    Dialog/datechoosedialog.cpp \
    Dialog/diagnosischoosedialog.cpp \
    Dialog/operationadddialog.cpp \
    Dialog/operationdeletedialog.cpp \
    Dialog/sequelachoosedialog.cpp \
    Dialog/surgeonadddialog.cpp \
    ModelView/Model/genderlistmodel.cpp \
    ModelView/Model/handledoperationsmodel.cpp \
    ModelView/Model/operationtitleslistmodel.cpp \
    ModelView/Model/surgeonsmodel.cpp \
    ModelView/View/handledoperationstableview.cpp \
    ModelView/View/surgeonstableview.cpp \
    ModelView/View/surgeonscomboview.cpp \
    PaypalPayment/paypaldialog.cpp \
    Source/CustomWidgets/rangeslider.cpp \
    Source/diagnosis.cpp \
    Window/adminpanelwindow.cpp \
    main.cpp \
    Source/gender.cpp \
    Source/handledoperation.cpp \
    Source/operation.cpp \
    Source/sequela.cpp \
    Source/sequelatype.cpp \
    Source/surgeon.cpp \
    Window/operationswindow.cpp \
    Window/mainwindow.cpp \
    Window/statisticswindow.cpp \
    Window/surgeonswindow.cpp

HEADERS += \
    Authorization/Source/user.h \
    Authorization/Window/authorizationmainwindow.h \
    Db/databasemanager.h \
    Dialog/datechoosedialog.h \
    Dialog/diagnosischoosedialog.h \
    Dialog/operationadddialog.h \
    Dialog/operationdeletedialog.h \
    Dialog/sequelachoosedialog.h \
    Dialog/surgeonadddialog.h \
    ModelView/Model/genderlistmodel.h \
    ModelView/Model/handledoperationsmodel.h \
    ModelView/Model/operationtitleslistmodel.h \
    ModelView/Model/surgeonsmodel.h \
    ModelView/View/handledoperationstableview.h \
    ModelView/View/surgeonstableview.h \
    ModelView/View/surgeonscomboview.h \
    PaypalPayment/paypaldialog.h \
    Source/CustomWidgets/rangeslider.h \
    Source/diagnosis.h \
    Source/gender.h \
    Source/handledoperation.h \
    Source/operation.h \
    Source/sequela.h \
    Source/sequelatype.h \
    Source/surgeon.h \
    Window/adminpanelwindow.h \
    Window/operationswindow.h \
    Window/mainwindow.h \
    Window/statisticswindow.h \
    Window/surgeonswindow.h

FORMS += \
    Dialog/datechoosedialog.ui \
    Dialog/diagnosischoosedialog.ui \
    Dialog/operationadddialog.ui \
    Dialog/operationdeletedialog.ui \
    Dialog/sequelachoosedialog.ui \
    Dialog/surgeonadddialog.ui \
    PaypalPayment/paypaldialog.ui \
    Window/adminpanelwindow.ui \
    Window/operationswindow.ui \
    Window/mainwindow.ui \
    Window/statisticswindow.ui \
    Window/surgeonswindow.ui \
    Authorization/Window/authorizationmainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target