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

class QTask : public QWidget
{
  Q_OBJECT

public:
  QTask(Task* t);
  ~QTask();

  bool eventFilter(QObject* object, QEvent* event);

private:
  QCheckBox* check;
  QToolButton* expand;
  QToolButton* param;

  QLabel* order;

  QLabel* text;

  QLineEdit* date;
  QCalendara* cal;
  QWidget* calmenu;

  Task* task;

  QToolButton* close;

public slots:
  void setDateText(QDate date);
  void closeTask();

};

#endif
