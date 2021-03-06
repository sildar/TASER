#include "TaskController.h"
#include "modelutil.h"
#include "../ui/QTask.h"

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
  saveTasklist("tasklist.xml", tasks);
}

std::list<std::string> TaskController::loadTemplateList(){
  
  DIR *dir;
  struct dirent *ent;
  std::list<std::string> list;

  if ((dir = opendir ("./templates")) != NULL) {
    /* print all the files and directories within directory */
    while ((ent = readdir (dir)) != NULL) {
      std::string res = ent->d_name;
      res = res.substr(0, res.size()-4);
      if (res.length() > 2){
	list.push_back(res);
      }
    }
    closedir (dir);
  } else {
    /* could not open directory */
    perror ("");
    return list;
  }

  return list;
}

void TaskController::reloadTemplateMenu()
{
  qTaskContainer->reloadTemplateMenu();
}

void TaskController::loadTemplate(std::string xmlFileName, QTask* parent)
{
  std::string temp = "./templates/";
  std::string file = temp.append(xmlFileName.append(".xml"));
  std::list<Task*> theTasks = loadTasklist(file);

  for (std::list<Task*>::iterator it = theTasks.begin(); it != theTasks.end(); ++it)
  {
    parent->task->addSubtask(*it);
    QTask* subtask = new QTask(*it,parent);
  }
  saveModel();
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
