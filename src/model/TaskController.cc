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
}

void TaskController::removeTask(Task* t)
{
}

void TaskController::loadModel()
{
  tasks = loadTasklist("tasklist.xml");
}

void TaskController::saveModel()
{
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
