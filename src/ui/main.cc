// -*- c-basic-offset: 2; c-indentation-style: ellemtel; -*-
#include <iostream>
#include <QApplication>
#include "../model/task.h"
#include "../ui/HoverWidget.h"
#include "../../ui_example.h"

int main(int argc, char** argv)
{
  //creates a parent and its child and print them.
  Task* parent = new Task("parent", NULL, true);
  Task* son = new Task("son", parent, false);
  std::cout << "Hello, QtWorld !" << std::endl;

  std::cout << parent->toString() << std::endl;


  //deletes a subtask
  parent->deleteSubtask(son);
  std::cout << parent->toString() << std::endl;

  //checks a task

  parent->checkTask();
  std::cout << parent->toString() << std::endl;

  delete(parent);

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

  //my tests

  /*
  
  std::cout << "avant" << std::endl;
  QApplication app(argc, argv);

  QMainWindow *widget = new QMainWindow;
  Ui::MainWindow ui;
  ui.setupUi(widget);
  widget->show();

  /*
  QWidget window;
  window.resize(320, 240);
  window.show();

  HoverWidget *hw = new HoverWidget("task name", &window);
  hw->show();
  std::cout << "après" << std::endl;
  */
/*
  return app.exec();

  */
    return 0;
}
