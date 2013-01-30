// -*- c-basic-offset: 2; c-indentation-style: ellemtel; -*-
#ifndef TASK_H
#define TASH_H

#include <list>
#include <string>
#include <ctime>
#include <iostream>


class Task
{

public:
  
  Task(std::string name, Task* parent, bool ordered);

  Task(std::string name, Task* parent, bool ordered, time_t date);

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
  */
  void addSubtask(Task* t);

  /*!
    \brief classic toString method, using an indentation for every
    level of subtask
  */
  std::string toString();

  void deleteSubtask(Task* t);

  /*!
    \brief checks a task when it's been completed. If it's part of an
    ordered task list, it is impossible to check it before the
    previous ones.
  */
  void checkTask();

  bool isChecked();

  bool isCheckable();

private:

  std::string name;
  std::time_t date;
  Task* parent;
  std::list<Task*> subtasks;
  bool orderedSubtasks;
  bool checked;
  
  


};

#endif // TASK_H
