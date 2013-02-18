#ifndef TASKLIST_H
#define TASKLIST_H

#include <list>
#include <QObject>
#include "../ui/QTaskContainer.h"
#include "../ui/QTask.h"
#include "task.h"

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
  static void loadTemplate(std::string xmlFileName, QTask* root);
  static void saveTemplate(std::string xmlFileName, QTask* root);

private:
  static QTaskContainer* qTaskContainer;
  static std::list<Task*> tasks;
};

#endif // TASKLIST_H
