#include "TaskController.h"
#include "modelutil.h"

QTaskContainer* TaskController::qTaskContainer = NULL;
std::list<Task*> TaskController::tasks = std::list<Task*>();

TaskController::TaskController()
{
}

void TaskController::setQTaskContainer(QTaskContainer *qtc)
{
  qTaskContainer = qtc;
}


void TaskController::addTask(Task* t)
{
  QTask* qt = new QTask(t);
  qTaskContainer->simpleAddTask(qt);
}

void TaskController::removeTask(Task* t)
{
//  qTaskContainer->removeTask(t);
}

void TaskController::loadModel()
{
  tasks = loadTasklist("tasklist.xml");
  for (std::list<Task*>::iterator it = tasks.begin(); it != tasks.end(); ++it)
  {
    addTask(*it);
  }
}

void TaskController::saveModel()
{
  qTaskContainer->updateModel();
  int i = 0;
  for (std::list<Task*>::iterator it = tasks.begin(); it != tasks.end(); it++)
  {
    std::cout << i << ": " << &(*it) << std::endl;
    i++;
  }
  saveTasklist("tasklist.xml", tasks);
}

void TaskController::loadTemplate(std::string xmlFileName, QTask* root)
{
}

void TaskController::saveTemplate(std::string xmlFileName, QTask* root)
{
  std::list<Task*> list = std::list<Task*>();
  list.push_back(root->task);
  saveTasklist(xmlFileName, list);
}


void TaskController::updateModel(std::list<Task*> theTasks)
{
  tasks = theTasks;
}
