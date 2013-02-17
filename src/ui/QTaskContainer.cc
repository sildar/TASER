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
  mainLayout->addStretch(1);

  connect(addTaskButton,SIGNAL(clicked()),this,SLOT(addTask()));


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

  for (int i = 0; i <= this->tasks.size()+1; i++)
    {
      this->tasksLayout->setStretch(i,0);
    }

  tasks.push_back(qtask);
  this->tasksLayout->addWidget(qtask);  
  this->tasksLayout->addStretch(1);
}
