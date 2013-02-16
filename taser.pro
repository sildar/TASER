CONFIG += qt
QMAKE_CLEAN += taser
TARGET = taser

SOURCES =                               \
    src/ui/main.cc                      \
    src/model/task.cc                   \
    src/model/tinyxml/tinystr.cpp       \
    src/model/tinyxml/tinyxml.cpp       \
    src/model/tinyxml/tinyxmlerror.cpp  \
    src/model/tinyxml/tinyxmlparser.cpp \
    src/ui/QTask.cc                     \
    src/ui/QCalendara.cc                \
    src/ui/QLinkBox.cc                  \
    src/ui/QWindow.cc

HEADERS =                               \
    src/model/task.h                    \
    src/model/tinyxml/tinystr.h         \
    src/model/tinyxml/tinyxml.h         \
    src/ui/QTask.h                      \
    src/ui/QCalendara.h                 \
    src/ui/QLinkBox.h                   \
    src/ui/QWindow.h

RESOURCES = taser.qrc
