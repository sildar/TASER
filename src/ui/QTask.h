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
  QTask(Task* t, QTask* parent = NULL);
  ~QTask();

  bool eventFilter(QObject* object, QEvent* event);
  void addSubtask(QTask* parent);

  Task* task;

private:
  QWidget* qTaskWidget;
  QCheckBox* check;
  QToolButton* expand;
  QToolButton* param;

  //actions for the param menu
  QAction* addTaskAction;
  QAction* checkTaskAction;
  QAction* delTaskAction;
  QAction* expandTaskAction;

  QLabel* order;

  QLabelEdit* text;

  QLabel* date;
  QCalendara* cal;
  QWidget* calmenu;


  QToolButton* close;



  // subtask-related attributes
  QWidget* subtaskContainer;

public slots:
  void setDateText(QDate date);
  void checkTask();
  void changeText(bool isDown);

private slots:
  void menuActionManager(QAction* action);

};

#endif
