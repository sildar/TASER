// -*- c-basic-offset: 2; c-indentation-style: ellemtel; -*-

#ifndef QCALENDARA_H
#define QCALENDARA_H

#include <QCalendarWidget>
#include <QWidget>
#include "QLinkBox.h"

class QCalendara : public QCalendarWidget
{
  Q_OBJECT

 public:
  QCalendara(QWidget *parent=0);
  bool isLinked();

 private:
  QLinkBox* linkbox;


};



#endif
