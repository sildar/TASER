// -*- mode: c++; c-basic-offset: 2; c-indentation-style: ellemtel; -*-

#ifndef QTASKCONTAINER_H
#define QTASKCONTAINER_H

#include <QWidget>
#include <list>
#include "QTask.h"
#include <QVBoxLayout>
#include <QScrollArea>

class QTaskContainer : public QWidget
{
  Q_OBJECT

 public:
  QTaskContainer(QWidget* parent=0);
  void addTask(Task* parent=0);
  ~QTaskContainer(){}
  
 private:
  QVBoxLayout* layout;
  std::list<QTask*> tasks;
  
};



#endif
