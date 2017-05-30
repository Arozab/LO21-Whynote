QT += widgets
QT += xml
QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11

HEADERS += \
    mainwindow.h \
    parametresparcelle.h
    

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    parametresparcelle.cpp
    

DISTFILES += \
    config.xml
