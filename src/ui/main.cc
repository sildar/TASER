// -*- mode: c++; c-basic-offset: 2; c-indentation-style: ellemtel; -*-

#include <iostream>
#include <QApplication>
#include <QScrollArea>
#include <QFile>
#include "../ui/QTask.h"
#include "../ui/QCalendara.h"
#include "QWindow.h"
#include "QTaskContainer.h"

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


  /*

  //prints the tree, then the tree after trying to check something
  //impossible, then after checked both.
  Task* t1 = new Task("t1",NULL,true);
  Task* t11 = new Task("t1.1", t1, false);
  Task* t12 = new Task("t1.2", t1, false);


  std::cout << t1->toString() << std::endl;

  t12->checkTask();

  std::cout << t1->toString() << std::endl;

  t11->checkTask();
  t12->checkTask();

  std::cout << t1->toString() << std::endl;

  delete t1;

  */

  //my tests

  std::cout << "avant" << std::endl;
  QApplication app(argc, argv);

  // Read taser.qss
  QFile qss(":/taser.qss");
  qss.open(QFile::ReadOnly);
  app.setStyleSheet(qss.readAll());
  qss.close();
  
  QWindow* mainWindow = new QWindow();
  mainWindow->resize(640, 400);
  /*
  QScrollArea* scrollArea = new QScrollArea(mainWindow);
  scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  scrollArea->setWidgetResizable(true);
  QVBoxLayout* scrollLayout = new QVBoxLayout(scrollArea);
  */
  QTaskContainer* container = new QTaskContainer();
  //QVBoxLayout* lay = new QVBoxLayout(container);

  Task* t1 = new Task("Titre 1", NULL, true, time(NULL));
  QTask* qtask1 = new QTask(t1);

  Task* t2 = new Task("Titre 2", NULL, true, time(NULL));
  QTask* qtask2 = new QTask(t2);

  Task* t3 = new Task("Titre 3", NULL, true, time(NULL));
  QTask* qtask3 = new QTask(t3);

  Task* t4 = new Task("Titre 4", NULL, true, time(NULL));
  QTask* qtask4 = new QTask(t4, qtask1);

  Task* t5 = new Task("Titre 5", NULL, true, time(NULL));
  QTask* qtask5 = new QTask(t5, qtask2);

  /*
  lay->addWidget(qtask1);
  lay->addWidget(qtask2);
  lay->addWidget(qtask3);
  lay->addStretch(); // necessary
  */
  container->addTask(t1);
  container->addTask(t2);
  //scrollArea->setWidget(container);
  mainWindow->setCentralWidget(container);

  mainWindow->show();

  return app.exec();
}
