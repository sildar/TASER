#ifndef TASK_H
#define TASH_H

#include <list>
#include <string>
#include <ctime>


class Task
{

public:
  
  Task(std::string name, Task* parent, bool ordered);

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

  void addSubtask(Task* t);

  std::string toString();


private:

  std::string name;
  std::time_t date;
  Task* parent;
  std::list<Task*> subtasks;
  bool orderedSubtasks;
  
  


};

#endif // TASK_H
