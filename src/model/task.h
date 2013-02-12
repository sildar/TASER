// -*- c-basic-offset: 2; c-indentation-style: ellemtel; -*-
#ifndef TASK_H
#define TASH_H

#include <list>
#include <string>
#include <ctime>
#include <iostream>
#include "tinyxml/tinyxml.h"


class Task
{

public:
  
  /*!
    \brief creates a Task and adds it to the subtask list of its
    parent (if it has a parent).
  */
  Task(std::string name, Task* parent, bool ordered);

  /*!
    \brief creates a Task and adds it to the subtask list of its
    parent (if it has a parent).
  */
  Task(std::string name, Task* parent, bool ordered, time_t date);

  Task(std::string xmlFileName, Task *parent = NULL);

  /*!
    \brief Tells if the task has a parent (then, it is a subtask of
    some bigger task) or not (then it's a major task)
  */
  bool hasParent();

  /*!
    \brief Returns true if the subtasks of this task are ordered,
    false if they aren't or if there's no subtask.
  */
  bool hasOrderedSubtasks();

  /*!
    \brief Adds a subtask to the subtasks list of this task.
    returns the new task created
  */
  void addSubtask(Task* t);


  /*!
    \brief adds a subtask to the current task
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
  bool isChecked();

  /*!
    \brief returns true if a task can be checked (no subtask
    unchecked)) and false otherwise
  */
  bool isCheckable();

  /*!
    \brief Stores the current task and all of its subtasks recursively
    in an XML file.
  */
  void storeAsXML(std::string filename);

  ~Task();

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

};

#endif // TASK_H
