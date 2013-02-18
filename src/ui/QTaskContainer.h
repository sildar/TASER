// -*- mode: c++; c-basic-offset: 2; c-indentation-style: ellemtel; -*-

#ifndef QTASKCONTAINER_H
#define QTASKCONTAINER_H

#include <QWidget>
#include <list>
#include "QTask.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QPainter>
#include <QStyleOption>


class TaskController;

class QTaskContainer : public QWidget
{
  Q_OBJECT

  friend class TaskController;

public:
  QTaskContainer(QWidget* parent=0);
  void paintEvent(QPaintEvent *qpe);
  
  void removeTask(Task* t);
  
  /*!
    \brief Adds a previously created root QTask to this widget.
  */
  void addTask(QTask* task);
  /*!
    \brief Adds a previously created root QTask to this widget.
    This method does not update the model (and is intended to be called from
    the TaskController).
  */
  void simpleAddTask(QTask* task);

public slots:

  /*!
    \brief Creates a new root QTask.
  */
  void newTask();


private slots:
  void focusChanged(QTask *);

private:
  QVBoxLayout* mainLayout;
  QHBoxLayout* buttonLayout;
  QVBoxLayout* tasksLayout;
  std::list<QTask*> tasks;
  QPushButton* addTaskButton;
  QTask *currentTask;

};



#endif
