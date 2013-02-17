#include "QTaskContainer.h"

QTaskContainer::QTaskContainer(QWidget* parent) :QWidget(parent)
{


  tasks = std::list<QTask*>();
  layout = new QVBoxLayout(this);

}

void
QTaskContainer::addTask(Task* parent)
{
  QTask* qtask;
  if (parent != NULL)
    {
      qtask = new QTask(new Task("Titre",parent,parent->hasOrderedSubtasks(),NULL));
    }
  else
    {
      qtask = new QTask(new Task("Titre",NULL,false,NULL));
    }
  tasks.push_back(qtask);
  this->layout->addWidget(qtask);
  this->layout->setStretch(this->tasks.size()-1,0);
  this->layout->addStretch(1);
}
