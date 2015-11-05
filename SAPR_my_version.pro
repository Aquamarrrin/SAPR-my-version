
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
HEADERS += \
    preprocwindow.h \
    mainwindow.h \
    construction.h \
    rod.h \
    load.h \
    proccalculations.h

SOURCES += \
    preprocwindow.cpp \
    mainwindow.cpp \
    main.cpp \
    construction.cpp \
    rod.cpp \
    load.cpp \
    proccalculations.cpp

FORMS +=

RESOURCES += \
    myres.qrc
