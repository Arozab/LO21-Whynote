QT += widgets
QT += xml
QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11

HEADERS += \
    Notes.h \
    noteediteur.h \
    fenprincipale.h

SOURCES += \
    main.cpp \
    Notes.cpp \
    noteediteur.cpp \
    fenprincipale.cpp
