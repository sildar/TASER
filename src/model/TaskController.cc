#include "TaskController.h"
#include "modelutil.h"

std::list<Task*> TaskController::tasks = std::list<Task*>();

TaskController::TaskController()
{
}


void TaskController::addTask(Task* t)
{
}

void TaskController::removeTask(Task* t)
{
}

void TaskController::loadModel()
{
  tasks = loadTasklist("tasklist.xml"); // O RLY?
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
}
