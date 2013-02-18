CONFIG += qt
CONFIG += debug
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
    src/ui/QWindow.cc                   \
    src/ui/QLabelEdit.cc                \
    src/ui/QTaskContainer.cc \
    src/model/modelutil.cc \
    src/model/TaskController.cc

HEADERS =                               \
    src/model/task.h                    \
    src/model/tinyxml/tinystr.h         \
    src/model/tinyxml/tinyxml.h         \
    src/ui/QTask.h                      \
    src/ui/QCalendara.h                 \
    src/ui/QLinkBox.h                   \
    src/ui/QWindow.h                    \
    src/ui/QLabelEdit.h                 \
    src/ui/QTaskContainer.h \
    src/model/modelutil.h \
    src/model/TaskController.h

RESOURCES = taser.qrc

TRANSLATIONS = languages/taser_en.ts \
                languages/taser_fr.ts

DEFINES *= QT_USE_QSTRINGBUILDER
