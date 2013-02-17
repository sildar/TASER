#ifndef XML_H
#define XML_H

#include <string>
#include <list>
#include "task.h"

/*!
  \brief Stores a list of tasks and all their subtasks recursively in an
  XML file.
*/
void saveModel(std::string xmlFile, std::list<Task*> tasks);

/*!
  \brief Loads a list of tasks and all their subtasks from an XML file.
*/
std::list<Task*> loadModel(std::string xmlFile);

#endif // XML_H
