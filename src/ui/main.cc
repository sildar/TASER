#include <iostream>
#include "../model/task.h"

int main(int arc, char** argv)
{
  //creates a parent and its child and print them.
  Task* parent = new Task("parent", NULL, true);
  Task son("son", parent, false);
  std::cout << "Hello, QtWorld !" << std::endl;
  std::cout << son.hasParent() << std::endl;
  std::cout << parent->toString() << std::endl;

  return 0;
}
