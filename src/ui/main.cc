// -*- mode: c++; c-basic-offset: 2; c-indentation-style: ellemtel; -*-

#include <iostream>
#include <QApplication>
#include <QScrollArea>
#include <QFile>
#include "../ui/QTask.h"
#include "../ui/QCalendara.h"
#include "QWindow.h"
#include "QTaskContainer.h"
#include <QTranslator>
#include <QLibraryInfo>
#include <QLocale>

int main(int argc, char** argv)
{
  QApplication app(argc, argv);
  
  QTranslator qtTranslator;
  qtTranslator.load("qt_" + QLocale::system().name(),
		    QLibraryInfo::location(QLibraryInfo::TranslationsPath));
  app.installTranslator(&qtTranslator);
  
  QTranslator myappTranslator;
  myappTranslator.load("taser_en"); //+ QLocale::system().name());
  app.installTranslator(&myappTranslator);
  
  // Read taser.qss
  QFile qss(":/taser.qss");
  qss.open(QFile::ReadOnly);
  app.setStyleSheet(qss.readAll());
  qss.close();
  
  QWindow* mainWindow = new QWindow();
  mainWindow->resize(640, 400);

  QTaskContainer* container = new QTaskContainer();

  mainWindow->setScrolledWidget(container);

  mainWindow->show();

  return app.exec();
}
