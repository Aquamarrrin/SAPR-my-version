
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
HEADERS += \
    preprocwindow.h \
    mainwindow.h \
    construction.h \
    rod.h \
    load.h \
    proccalculations.h \
    postprocwindow.h \
    graphicwindow.h

SOURCES += \
    preprocwindow.cpp \
    mainwindow.cpp \
    main.cpp \
    construction.cpp \
    rod.cpp \
    load.cpp \
    proccalculations.cpp \
    postprocwindow.cpp \
    graphicwindow.cpp

FORMS +=

RESOURCES += \
    myres.qrc
