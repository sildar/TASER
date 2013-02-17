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
#include <QDateTime>
#include <QPainter>
#include <QStyleOption>

class QTask : public QWidget
{
  Q_OBJECT

public:
  QTask(Task* t, QTask* parent = NULL);
  ~QTask();
  void paintEvent(QPaintEvent *qpe);

  /*!
    \brief eventFilter for specific actions
  */
  bool eventFilter(QObject* object, QEvent* event);
  /*!
    \brief
    adds a subtask to an existing Qtask
  */
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
  QAction* orderSubtasksAction;

  QLabel* order;

  QLabelEdit* text;

  QLabel* date;
  QCalendara* cal;
  QWidget* calmenu;


  QToolButton* closeButton;

  // subtask-related attributes
  QWidget* subtaskContainer;

public slots:
  /*!
    \brief updates the date label
  */
  void setDateText(QDate date);
  /*!
    \brief check or uncheck a QTask
  */
  void checkTask();
  /*!
    \brief changes the text of the expand button (arrow direction)
  */
  void changeText(bool isDown);

private slots:
  /*!
    \brief manages all the actions available in the param menu
  */
  void menuActionManager(QAction* action);
  /*!
    \brief closes a task and its subtasks
  */
  void closeTask();

  void orderSubtasks();

};

#endif
