QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    creditcalc.cpp \
    graph.cpp \
    main.cpp \
    mainwindow.cpp \
    ../../back/parse.c \
    ../../back/stack.c \
    ../../back/priority.c \
    ../../back/credit.c \
    ../../back/s21_SmartCalc.c \
    qcustomplot.cpp

HEADERS += \
    creditcalc.h \
    graph.h \
    mainwindow.h \
    ../../back/s21_SmartCalc.h \
    ../../back/credit.h \
    qcustomplot.h

FORMS += \
    creditcalc.ui \
    graph.ui \
    mainwindow.ui
    
DESTDIR = ~/Calc
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
