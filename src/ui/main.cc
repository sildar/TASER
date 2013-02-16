// -*- mode: c++; c-basic-offset: 2; c-indentation-style: ellemtel; -*-

#include <iostream>
#include <QApplication>
#include <QScrollArea>
#include "../ui/QTask.h"
#include "../ui/QCalendara.h"
#include "QWindow.h"

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
  
  QWindow* qw = new QWindow();
  QWidget* container = new QWidget(qw);
  QVBoxLayout* lay = new QVBoxLayout();

  Task* t = new Task("Titre 1", NULL, true, time(NULL));
  QTask* qtask = new QTask(t);

  Task* t2 = new Task("Titre 2", NULL, true, time(NULL));
  QTask* qtask2 = new QTask(t2);

  Task* t3 = new Task("Titre 3", NULL, true, time(NULL));
  QTask* qtask3 = new QTask(t3);

  lay->addWidget(qtask);
  lay->addWidget(qtask2);
  lay->addWidget(qtask3);
  //lay->addStretch(); // is it necessary?

  container->setLayout(lay);

  qw->setCentralWidget(container);

  qw->show();

  return app.exec();

  return 0;
}
