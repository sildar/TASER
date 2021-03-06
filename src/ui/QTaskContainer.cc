// -*- mode: c++; c-basic-offset: 2; c-indentation-style: ellemtel; -*-

#include "QTaskContainer.h"
#include "../model/TaskController.h"

QTaskContainer::QTaskContainer(QWidget* parent)
  : QWidget(parent)
{
  currentTask = NULL;
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

  connect(addTaskButton,SIGNAL(clicked()),this,SLOT(newTask()));
  TaskController::setQTaskContainer(this);
  TaskController::loadModel();

}

void
QTaskContainer::addTask(QTask* task)
{
  simpleAddTask(task);
}


void
QTaskContainer::reloadTemplateMenu(){

  std::list<std::string> templatelist = TaskController::loadTemplateList();
  
  for(std::list<QTask*>::iterator it = tasks.begin(); it != tasks.end(); ++it){

    if ((*it) != NULL && (*it)->templateMenu != NULL){

    (*it)->templateMenu->clear();
    
    for (std::list<std::string>::iterator it2 = templatelist.begin(); it2 != templatelist.end(); ++it2){
      (*it)->templateMenu->addAction(QString::fromUtf8(it2->c_str()));
    }
    
    for (int i = 0; i< (*it)->subtaskContainer->layout()->count(); i++){
      QTask* curr = (QTask*) (*it)->subtaskContainer->layout()->itemAt(i)->widget();
      
      curr->templateMenu->clear();
      
      for (std::list<std::string>::iterator it2 = templatelist.begin(); it2 != templatelist.end(); ++it2){
	curr->templateMenu->addAction(QString::fromUtf8(it2->c_str()));
      }
    }
    }
  }
}
  
void
QTaskContainer::simpleAddTask(QTask* task)
{
  for (unsigned int i = 0; i <= (this->tasks.size() + 1); i++) {
    this->tasksLayout->setStretch(i, 0);
  }

  connect(task, SIGNAL(enabled(QTask*)),
          this, SLOT(focusChanged(QTask*)));

  this->tasks.push_back(task);
  this->tasksLayout->addWidget(task);
  this->tasksLayout->addStretch(1);
}

void
QTaskContainer::newTask()
{
  QTask* qtask = new QTask(new Task("Titre", NULL, false, time(NULL)));
  addTask(qtask);
}

void
QTaskContainer::focusChanged(QTask *qtask)
{
  // if (currentTask != NULL) {
  //   currentTask->setCurrent(false);
  // }
  // currentTask = qtask;
  // currentTask->setCurrent(true);
}

void
QTaskContainer::paintEvent(QPaintEvent *)
{
  QStyleOption opt;
  opt.init(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}


void
QTaskContainer::removeTask(Task* t){

  for(std::list<QTask*>::iterator it = this->tasks.begin();
      it != this->tasks.end(); ++it)
  {
    if ((*it)->task == t)
    {
      tasks.erase(it);
      return;
    }
  }
}


void QTaskContainer::changeEvent(QEvent* event)
{
  if (event->type() == QEvent::LanguageChange)
  {
    this->addTaskButton->setText(trUtf8("Nouvelle Tâche"));
  }
  
  // remember to call base class implementation
  QWidget::changeEvent(event);
}
