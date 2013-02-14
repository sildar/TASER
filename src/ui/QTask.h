// -*- c-basic-offset: 2; c-indentation-style: ellemtel; -*-

#ifndef QTASK_H
#define QTASK_H

#include <QWidget>
#include <QToolButton>
#include <QString>
#include <QLabel>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QFrame>
#include "./../model/task.h"

class QTask : public QWidget
{
  Q_OBJECT

 public :
  QTask(Task* t);


 private :
  QToolButton* extend;
  QToolButton* param;
  QToolButton* order;
  QToolButton* close;
  QLabel* text;
  QLabel* date;
  QCheckBox* check;
};


#endif
