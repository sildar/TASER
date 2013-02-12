// -*- c-basic-offset: 2; c-indentation-style: ellemtel; -*-
#include "task.h"
#include <iostream>
#include <sstream>

Task::Task(std::string name, Task* parent, bool ordered)
{
  
  this->checked = false;
  this->name = name;
  this->index = 0;

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
  this->index = 0;

  this->orderedSubtasks = ordered;
  subtasks = std::list<Task*>();

  if (parent != NULL)
    {
      this->parent = parent;
      this->parent->addSubtask(this);
    }
}

Task::Task(std::string xmlFileName, Task* parent)
{
  this->checked = false;
  this->orderedSubtasks = false;
  subtasks = std::list<Task*>();

  TiXmlDocument doc(xmlFileName.c_str());
  doc.LoadFile();
  TiXmlElement* root = doc.RootElement();

  int dateInt = 0;
  root->Attribute("date", &dateInt);
  this->date = dateInt;
  std::string yes = "yes";
  const char* orderedSubStr = root->Attribute("ordered-subtasks");
  const char* checkedStr = root->Attribute("checked");
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

  if (parent != NULL)
    {
      this->parent = parent;
      this->parent->addSubtask(this);
    }
}

Task::Task(TiXmlElement* root, Task* parent)
{
  this->checked = false;
  this->orderedSubtasks = false;
  subtasks = std::list<Task*>();

  int dateInt = 0;
  root->Attribute("date", &dateInt);
  this->date = dateInt;
  std::string yes = "yes";
  const char* orderedSubStr = root->Attribute("ordered-subtasks");
  const char* checkedStr = root->Attribute("checked");
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
  t->index = subtasks.size();
}

bool Task::isChecked()
{
  return this->checked;
}

std::string Task::toString()
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

void Task::deleteSubtask(Task* t)
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


void Task::storeAsXML(std::string filename)
{
  TiXmlDocument doc;
  TiXmlDeclaration* xmlDecl = new TiXmlDeclaration("1.0", "", "");
  TiXmlElement* root = xmlSubtree();

  doc.LinkEndChild(xmlDecl);
  doc.LinkEndChild(root);

  doc.SaveFile(filename.c_str());

  /* Note: the LinkEndChild method uses pointers instead of references, so
   * that when linked, the objects become owned (and deleted) by tinyXml.
   * This method is efficient and adds an extra copy, but should be used
   * with care as it uses a different memory model than the other insert
   * functions.
   */
}

TiXmlElement* Task::xmlSubtree()
{
  // make the root node
  TiXmlElement* root = new TiXmlElement("task");
  root->SetAttribute("date", this->date);
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


Task::~Task(){

  for (std::list<Task*>::iterator it = this->subtasks.begin(); it != this->subtasks.end(); ++it) {

    delete *it;

  }
}
