#include "QTaskContainer.h"

QTaskContainer::QTaskContainer(QWidget* parent) :QWidget(parent)
{

  addTaskButton = new QPushButton(trUtf8("Nouvelle Tâche"));


  tasks = std::list<QTask*>();
  tasksLayout = new QVBoxLayout();
  buttonLayout = new QHBoxLayout();
  buttonLayout->addWidget(addTaskButton);
  buttonLayout->addStretch(1);
  mainLayout = new QVBoxLayout(this);
  
  mainLayout->addLayout(buttonLayout);
  mainLayout->addLayout(tasksLayout);


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
  this->tasksLayout->addWidget(qtask);
  this->tasksLayout->setStretch(this->tasks.size()-1,0);
  this->tasksLayout->addStretch(1);
}
