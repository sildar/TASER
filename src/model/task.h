// -*- mode: c++; c-basic-offset: 2; c-indentation-style: ellemtel; -*-

#ifndef TASK_H
#define TASK_H

#include <list>
#include <string>
#include <ctime>
#include <iostream>
#include "tinyxml/tinyxml.h"

/*!
  A task class representing a task that can have subtasks, be checked
  or not and which is described by its name and an optional date.
*/
class Task
{

public:

  /*!
    \brief creates a Task and adds it to the subtask list of its
    parent (if it has a parent).
  */
  Task(std::string name, Task* parent, bool ordered, time_t date = NULL);

  /*!
    \brief Tells if the task has a parent (then, it is a subtask of
    some bigger task) or not (then it's a major task)
  */
  bool hasParent() const;

  /*!
    \brief Returns true if the subtasks of this task are ordered,
    false if they aren't or if there's no subtask.
  */
  bool hasOrderedSubtasks() const;

  /*!
    \brief adds a subtask to its parent subtask list
  */
  void addSubtask(Task* t);

  /*!
    \brief adds a subtask to the current task
    returns the new task created
  */
  Task* addSubtask(std::string name, time_t date);

  /*!
    \brief classic toString method, using an indentation for every
    level of subtask
  */
  std::string toString();

  /*
    \brief deletes a subtask from its parent.
  */
  void deleteSubtask(Task* t);

  /*!
    \brief checks a task when it's been completed. If it's part of an
    ordered task list, it is impossible to check it before the
    previous ones.
  */
  void checkTask();

  /*!
    \brief returns true if a task is checked (completed) and false
    otherwise
  */
  bool isChecked() const;

  /*!
    \brief returns true if a task can be checked (no subtask
    unchecked) and false otherwise
  */
  bool isCheckable() const;

  /*!
    \brief deletes a task and all its subtasks
  */
  ~Task();

  /*!
    \brief getter for the name
  */
  std::string getName() const;

  /*!
    \brief getter for the date
  */
  std::time_t getDate() const;

  /*!
    \brief getter for the index
  */
  int getIndex() const;


private:

  std::string name;
  std::time_t date;
  int index;
  Task* parent;
  std::list<Task*> subtasks;
  bool orderedSubtasks;
  bool checked;

  /*!
    \brief Creates a task from an XML element. This constructor is used for
    creating a task list from an XML tree, loaded from a file.
  */
  Task(TiXmlElement* root, Task* parent = NULL);

  /*!
    \brief Retrieves the XML subtree of this current task (the root is the
    current task, and its children represent the subtasks). This method is
    used for generating an XML tree recursively for storing in a file.
  */
  TiXmlElement* xmlSubtree();

  friend void saveModel(std::string xmlFile, std::list<Task*> tasks);
  friend std::list<Task*> loadModel(std::string xmlFile);
};

#endif // TASK_H
