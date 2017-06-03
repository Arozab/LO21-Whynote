QT += widgets
QT += xml
QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11

HEADERS += \
    Xml_Dom.h


SOURCES += \
    main.cpp \
    Xml_Dom.cpp \
    xml_doc.xml
