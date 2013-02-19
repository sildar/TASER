#ifndef TASKLIST_H
#define TASKLIST_H

#include <list>
#include <QObject>
#include "../ui/QTaskContainer.h"
#include "task.h"
#include "dirent.h"

class TaskController : public QObject
{
  Q_OBJECT

public:
  TaskController();
  /*!
    \brief Sets the QTaskContainer the model will interact with.
  */
  static void setQTaskContainer(QTaskContainer* qtc);

public slots:
  static void addTask(Task* t);
  static void removeTask(Task* t);
  static void loadModel();
  static void saveModel();
  static void updateModel(std::list<Task*> theTasks);
  static void loadTemplate(std::string xmlFileName, QTask* root);
  static void saveTemplate(std::string xmlFileName, QTask* root);
  static std::list<std::string> loadTemplateList();

private:
  static QTaskContainer* qTaskContainer;
  static std::list<Task*> tasks;

  friend class Task;
};

#endif // TASKLIST_H
