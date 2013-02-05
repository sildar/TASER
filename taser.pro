CONFIG += qt console
QMAKE_CLEAN += taser
TARGET = taser
SOURCES += ./src/ui/main.cc
SOURCES += ./src/ui/MyWidget.cc
HEADERS += ./src/ui/MyWidget.hpp
SOURCES += ./src/model/task.cc
HEADERS += ./src/model/task.h
