CONFIG      += qt
QMAKE_CLEAN += taser
TARGET       = taser

SOURCES     += ./src/ui/main.cc
SOURCES     += ./src/model/task.cc
SOURCES     += ./src/model/tinyxml/tinystr.cpp
SOURCES     += ./src/model/tinyxml/tinyxml.cpp
SOURCES     += ./src/model/tinyxml/tinyxmlerror.cpp
SOURCES     += ./src/model/tinyxml/tinyxmlparser.cpp
SOURCES     += ./src/ui/QTask.cc
SOURCES     += ./src/ui/QCalendara.cc
SOURCES     += ./src/ui/QLinkBox.cc
SOURCES     += ./src/ui/QWindow.cc

HEADERS     += ./src/model/task.h
HEADERS     += ./src/model/tinyxml/tinystr.h
HEADERS     += ./src/model/tinyxml/tinyxml.h
HEADERS     += ./src/ui/QTask.h
HEADERS     += ./src/ui/QCalendara.h
HEADERS     += ./src/ui/QLinkBox.h
HEADERS     += ./src/ui/QWindow.h

RESOURCES    = taser.qrc
