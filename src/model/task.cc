#include "task.h"

Task::Task(std::string name, Task* parent, bool ordered)
{
  
  this->name = name;

  this->orderedSubtasks = ordered;
  subtasks = std::list<Task*>();

  if (parent != NULL)
    {
      this->parent = parent;
      this->parent->addSubtask(this);
    }
}

bool Task::hasParent()
{
  return (this->parent != NULL);
}


bool Task::hasOrderedSubtasks()
{
  return (subtasks.size() > 0 && orderedSubtasks);
}


void Task::addSubtask(Task* t)
{
  subtasks.push_back(t);
}

std::string Task::toString()
{
  std::string res = "";
  res += this->name + "\n";

  for (std::list<Task*>::iterator it = this->subtasks.begin();
       it != this->subtasks.end();
       ++it)
    {
      res += "\t" + (*it)->toString();
    }

  return res;
}
