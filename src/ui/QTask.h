// -*- mode: c++; c-basic-offset: 2; c-indentation-style: ellemtel; -*-

#ifndef QTASK_H
#define QTASK_H

#include <QWidget>
#include <QToolButton>
#include <QString>
#include <QLabel>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QFrame>
#include <QLineEdit>
#include "./../model/task.h"
#include "QCalendara.h"
#include <QEvent>
#include <QMenu>
#include <QWidgetAction>
#include "QLabelEdit.h"
#include <QAction>

class QTask : public QWidget
{
  Q_OBJECT

public:
  QTask(Task* t);

  bool eventFilter(QObject* object, QEvent* event);

private:
  QCheckBox* check;
  QToolButton* expand;
  QToolButton* param;

  //actions for the param menu
  QAction* addTaskAction;
  QAction* checkTaskAction;

  QLabel* order;

  QLabelEdit* text;

  QLineEdit* date;
  QCalendara* cal;
  QWidget* calmenu;


  QToolButton* close;


  Task* task;

public slots:
  void setDateText(QDate date);
  void closeTask();
  void checkTask();

private slots:
  void menuActionManager(QAction* action);

};

#endif
