#include <iostream>
#include "../model/task.h"

int main(int arc, char** argv)
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
  delete(son);

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
  
  

  return 0;
}
