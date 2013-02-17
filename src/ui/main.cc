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
  //creates a parent and its child and print them.
  Task* parent = new Task("parent", NULL, true);
  Task* son = parent->addSubtask("son", time(NULL));
  std::cout << "Hello, QtWorld !" << std::endl;

  std::cout << parent->toString() << std::endl;


  //deletes a subtask
  parent->deleteSubtask(son);
  std::cout << parent->toString() << std::endl;

  //checks a task

  parent->checkTask();
  std::cout << parent->toString() << std::endl;

  delete(parent);


  //my tests

  std::cout << "avant" << std::endl;
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
