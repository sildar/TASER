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
#include <QBoxLayout>

class TaskController;

class QTask : public QWidget
{
  Q_OBJECT

  Q_PROPERTY(bool done READ done WRITE setDone NOTIFY changedDone)
  Q_PROPERTY(bool current READ current WRITE setCurrent NOTIFY changedCurrent)
  Q_PROPERTY(bool late READ late WRITE setLate NOTIFY changedLate)

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
  void addSubtask();

  void changeEvent(QEvent* event);
  void retranslate();

  Task* task;
  bool done() const { return done_; }
  void setDone(bool done) { done_ = done; emit changedDone(done); }
  bool late() const { return late_; }
  void setLate(bool late) { late_ = late; emit changedLate(late); }
  bool current() const { return current_; }
  void setCurrent(bool current) { current_ = current; emit changedCurrent(current); }

  QCheckBox* check;

signals:
  void changedDone(bool);
  void changedCurrent(bool);
  void changedLate(bool);

private:
  bool done_;
  bool late_;
  bool current_;
  bool dateIsLinked;
  QWidget* qTaskWidget;
  QToolButton* expand;
  QToolButton* param;
  QTask* pare;

  //actions for the param menu
  QAction* addTaskAction;
  QAction* checkTaskAction;
  QAction* delTaskAction;
  QAction* expandTaskAction;
  QAction* orderSubtasksAction;
  QAction* upTaskAction;
  QAction* downTaskAction;
  QMenu* templateMenu;

  QLabel* order;

  QLabelEdit* text;

  QLabel* date;
  QCalendara* cal;
  QWidget* calmenu;


  QToolButton* closeButton;

  // subtask-related attributes
  QWidget* subtaskContainer;

signals:
  void enabled(QTask *);

public slots:
  /*!
    \brief updates the date label
  */
  void setDateText(QDate date);

  void manageTemplates(QAction* action);

  void dateLinked(bool isLinked);

  /*!
    \brief check or uncheck a QTask
  */
  void checkTask(bool isChecked);

  void exchangeWidgets(int from, int change, QBoxLayout* layout);

  void setTasksCheckable(QTask* parent);

  /*!
    \brief changes the text of the expand button (arrow direction)
  */
  void changeText(bool isDown);

  void redraw();


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
  void enable();
  void textChanged(const QString& s);

private:
  /*!
    \brief updates the date label according to the task's date
  */
  void refreshDateText();
};

#endif
