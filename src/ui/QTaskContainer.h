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

class QTaskContainer : public QWidget
{
  Q_OBJECT

 public:
  QTaskContainer(QWidget* parent=0);
  void paintEvent(QPaintEvent *qpe);

public slots:
  /*!
    \brief adds a main QTask
  */
  void addTask(Task* parent=0);

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
