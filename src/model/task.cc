// -*- mode: c++; c-basic-offset: 2; c-indentation-style: ellemtel; -*-

#include "task.h"
#include <iostream>
#include <sstream>
#include "TaskController.h"

Task::Task(std::string name, Task* parent, bool ordered, time_t date)
{

  this->checked = false;
  this->name = name;
  this->index = 0;
  this->parent = parent;
  this->dateIsLinked = false;

  if (date != NULL){
    this->date = date;
  }

  this->orderedSubtasks = ordered;
  subtasks = std::list<Task*>();

  if (parent != NULL)
  {
    this->parent->addSubtask(this);
  }
  else
  {
    TaskController::tasks.push_back(this);
  }
  TaskController::saveModel();
}


void
Task::setDate(time_t aDate)
{
  time_t diff =  aDate - date;
  this->date = aDate;
  for(std::list<Task*>::iterator it = this->subtasks.begin();
      it != this->subtasks.end(); ++it)
  {
    if ((*it)->hasLinkedDate())
    {
      (*it)->setDate((*it)->getDate()+diff);
    }
  }

  TaskController::saveModel();
}

bool
Task::hasParent() const
{
  return (this->parent != NULL);
}


bool
Task::hasOrderedSubtasks() const
{
  return (!subtasks.empty() > 0 && orderedSubtasks);
}


void
Task::addSubtask(Task* t)
{
  subtasks.push_back(t);
  t->index = subtasks.size();
}

bool
Task::isChecked() const
{
  return this->checked;
}

std::string
Task::toString()
{
  std::string res = "";

  std::stringstream indexstr;
  indexstr << this->index;

  res += indexstr.str() + " : ";
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

void
Task::deleteSubtask(Task* t)
{
  for(std::list<Task*>::iterator it = this->subtasks.begin();
      it != this->subtasks.end(); ++it)
  {
    if (*it == t)
    {
      this->subtasks.erase(it);
      delete t;
      return;
    }
  }
}

bool
Task::hasBigBrother()
{
  if (this->parent == NULL)
  {
    return false;
  }
  else
  {
    //checks if the first subtask of its parent is itself
    return (*(this->parent->subtasks.begin()) != this);
  }
}

bool
Task::hasLittleBrother()
{
  if (this->parent == NULL)
  {
    return false;
  }
  else
  {
    bool sawMe = false;
    for (std::list<Task*>::iterator it = this->parent->subtasks.begin(); it != this->parent->subtasks.end(); ++it)
    {
      if (sawMe)
      {
        return true;
      }
      else if ((*it)==this)
      {
        sawMe = true;
      }
    }
  }
  return false;
}


void
Task::getUp()
{
  if (this->hasBigBrother())
  {
    std::list<Task*>::iterator pred = this->parent->subtasks.begin();

    for (std::list<Task*>::iterator it = this->parent->subtasks.begin(); it != this->parent->subtasks.end(); ++it)
    {
      if ((*it) == this)//insert before sibling and erase itself from preceding location
        {
          pred--;
          this->parent->subtasks.insert(pred,*it);
          this->parent->subtasks.erase(it);

          bool wasOrdered = this->parent->hasOrderedSubtasks();
          this->parent->setSubtasksOrdered(true);
          this->parent->setSubtasksOrdered(wasOrdered);
          return;
        }
      pred++;
    }
  }
  TaskController::saveModel();
}

void
Task::getDown()
{
  if (this->hasLittleBrother())
  {
    std::list<Task*>::iterator pred = this->parent->subtasks.begin();

    for (std::list<Task*>::iterator it = this->parent->subtasks.begin(); it != this->parent->subtasks.end(); ++it)
    {
      if ((*it) == this)//insert before sibling and erase itself from preceding location
        {
          Task* t = *it;
          it++;
          it++;
          this->parent->subtasks.insert(it,t);
          this->parent->subtasks.erase(pred);
          bool wasOrdered = this->parent->hasOrderedSubtasks();
          this->parent->setSubtasksOrdered(true);
          this->parent->setSubtasksOrdered(wasOrdered);
          return;
        }
      pred++;
    }
  }
  TaskController::saveModel();
}

void
Task::checkTask(bool isChecked){

  if (this->isCheckable())
  {
    this->checked = isChecked;
    //uncheck all little brothers
    if (!isChecked && parent != NULL && parent->hasOrderedSubtasks()){
      bool sawMe = false;
      for (std::list<Task*>::iterator it = this->parent->subtasks.begin(); it != this->parent->subtasks.end(); ++it){
        if (sawMe){
          (*it)->checked = false;
        }
        else if (*it == this){
          sawMe = true;
        }
      }
    }
    TaskController::saveModel();
  }
}

bool
Task::isCheckable() const
{
  if (this->parent != NULL && this->parent->hasOrderedSubtasks())
  {
    for (std::list<Task*>::iterator it = this->parent->subtasks.begin(); it != this->parent->subtasks.end(); ++it)
    {
      if ((*it) == (this))
      {
        it++;
        while (it != this->parent->subtasks.end())
        {
          if ((*it)->isChecked())
          {
            return false;
          }
          it++;
        }
        return !parent->isChecked();
      }
      else if (! (*it)->isChecked())
      {
        return false;
      }
    }
  }
  else {//if (this->parent == NULL){
    for (std::list<Task*>::const_iterator it = this->subtasks.begin(); it != this->subtasks.end(); ++it)
    {
      if (!(*it)->isChecked())
      {
        return false;
      }
    }
  }
  return (parent == NULL || !parent->isChecked());
}

Task::~Task()
{
  for (std::list<Task*>::iterator it = this->subtasks.begin(); it != this->subtasks.end(); ++it)
  {
    delete *it;
  }

  if (this->parent != NULL)
  {
    this->parent->subtasks.remove(this);
  }
  else
  {
    TaskController::tasks.remove(this);
  }
  TaskController::saveModel();
}

Task*
Task::addSubtask(std::string name, time_t date){

  Task* newTask = new Task(name,this, this->hasOrderedSubtasks(),date);
  return newTask;
}

std::string
Task::getName() const{
  return name;
}

void
Task::setName(std::string aName){
  this->name = aName;
  TaskController::saveModel();
}

std::time_t
Task::getDate() const{
  return date;
}

int
Task::getIndex() const{
  return index;
}

std::list<Task*>
Task::getSubtasks() const{
  return subtasks;
}

void
Task::setLinkedDate(bool isLinked)
{
  dateIsLinked = isLinked;
  TaskController::saveModel();
}

bool
Task::hasLinkedDate()
{
  return dateIsLinked;
}


void
Task::setSubtasksOrdered(bool order)
{
  this->orderedSubtasks = order;
  int i = 1;
  if (order)
  {
    for (std::list<Task*>::iterator it = this->subtasks.begin(); it != this->subtasks.end(); ++it)
    {
      (*it)->index = i;
      i++;
    }
  }
  TaskController::saveModel();
}


TiXmlElement*
Task::xmlSubtree()
{
  // make the root node
  TiXmlElement* root = new TiXmlElement("task");
  root->SetAttribute("date", this->date);
  if (this->dateIsLinked)
  {
    root->SetAttribute("date-linked", "yes");
  }
  if (this->hasOrderedSubtasks())
  {
    root->SetAttribute("ordered-subtasks", "yes");
  }
  if (this->checked)
  {
    root->SetAttribute("checked", "yes");
  }
  TiXmlElement* name = new TiXmlElement("name");
  TiXmlText* nameText = new TiXmlText(this->name.c_str());
  name->LinkEndChild(nameText);
  root->LinkEndChild(name);

  // make the children nodes recursively, if any
  if (this->subtasks.size() > 0)
  {
    for (std::list<Task*>::iterator iter = this->subtasks.begin();
         iter != this->subtasks.end(); iter++)
    {
      root->LinkEndChild((*iter)->xmlSubtree());
    }
  }

  return root;
}

Task::Task(TiXmlElement* root, Task* parent)
{
  this->checked = false;
  this->orderedSubtasks = false;
  this->dateIsLinked = false;
  subtasks = std::list<Task*>();

  int dateInt = 0;
  root->Attribute("date", &dateInt);
  this->date = dateInt;
  std::string yes = "yes";
  const char* dateLinkedStr = root->Attribute("date-linked");
  const char* orderedSubStr = root->Attribute("ordered-subtasks");
  const char* checkedStr = root->Attribute("checked");
  if (dateLinkedStr != NULL && yes.compare(dateLinkedStr) == 0)
  {
    this->dateIsLinked = true;
  }
  if (orderedSubStr != NULL && yes.compare(orderedSubStr) == 0)
  {
    this->orderedSubtasks = true;
  }
  if (checkedStr != NULL && yes.compare(checkedStr) == 0)
  {
    this->checked = true;
  }
  this->name = root->FirstChildElement("name")->GetText();

  for(TiXmlElement* child = root->FirstChildElement("task"); child; child = child->NextSiblingElement("task"))
  {
    new Task(child, this);
  }

  this->parent = parent;
  if (parent != NULL) {
    this->parent->addSubtask(this);
  }
}
