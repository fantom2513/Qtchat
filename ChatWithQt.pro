QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adddatabaseform.cpp \
    loginform.cpp \
    main.cpp \
    mainwindow.cpp \
    BadLogin.cpp \
    BadPassword.cpp \
    Chat.cpp \
    DataBase.cpp \
    Logger.cpp \
    Message.cpp \
    User.cpp \
    registrationform.cpp \
    startscreen.cpp

HEADERS += \
    adddatabaseform.h \
    loginform.h \
    mainwindow.h \
    BadLogin.h \
    BadPassword.h \
    Chat.h \
    DataBase.h \
    Logger.h \
    Message.h \
    User.h \
    registrationform.h \
    startscreen.h

FORMS += \
    adddatabaseform.ui \
    loginform.ui \
    mainwindow.ui \
    registrationform.ui \
    startscreen.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH +=$$PWD/'../../../Program Files/MySQL/MySQL Server 8.0/include'
QMAKE_LIBDIR +=$$PWD/'../../../Program Files/MySQL/MySQL Server 8.0/lib'
LIBS += -llibmysql
