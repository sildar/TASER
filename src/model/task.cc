// -*- c-basic-offset: 2; c-indentation-style: ellemtel; -*-
#include "task.h"
#include <iostream>

Task::Task(std::string name, Task* parent, bool ordered)
{
  
  this->checked = false;
  this->name = name;

  this->orderedSubtasks = ordered;
  subtasks = std::list<Task*>();


  this->parent = parent;
  if (parent != NULL)
    {
      this->parent->addSubtask(this);
    }
}

Task::Task(std::string name, Task* parent, bool ordered, time_t date)
{
  
  this->checked = false;
  this->name = name;
  this->date = date;

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

bool Task::isChecked()
{
  return this->checked;
}

std::string Task::toString()
{
  std::string res = "";
  res += this->name + " ";
  res += this->isChecked() ? "o" : "x";
  res+= "\n";

  for (std::list<Task*>::iterator it = this->subtasks.begin();
       it != this->subtasks.end();
       ++it)
    {
      res += "\t" + (*it)->toString();
    }

  return res;
}

void Task::deleteSubtask(Task* t)
{
  for(std::list<Task*>::iterator it = this->subtasks.begin();
      it != this->subtasks.end(); ++it)
    {
      if (*it == t)
	{
	  this->subtasks.erase(it);
	  return;
	}
    }
}

void Task::checkTask(){
  
  if (this->isCheckable())
    {
      this->checked = !(this->checked);
    }
}


bool Task::isCheckable()
{
  if (this->parent != NULL && this->parent->hasOrderedSubtasks())
    {
      for (std::list<Task*>::iterator it = this->parent->subtasks.begin(); it != this->parent->subtasks.end(); ++it)
	{
	  if ((*it) == (this))
	    {
	      return true;
	    }
	  else if (! (*it)->isChecked())
	    {
	      return false;
	    }
	}
    }
  return true;
}
