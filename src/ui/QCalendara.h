// -*- mode: c++; c-basic-offset: 2; c-indentation-style: ellemtel; -*-

#ifndef QCALENDARA_H
#define QCALENDARA_H

#include <QCalendarWidget>
#include <QWidget>
#include "QLinkBox.h"


/*!
  \brief class containing a calendar and a qlinkbox wich says if a
  task is linked to its master
*/
class QCalendara : public QCalendarWidget
{
  Q_OBJECT

public:
  /*!
    \brief Constructor of the calendara
  */
  QCalendara(QWidget *parent=0, QString* parentDate=NULL);
  /*!
    \brief says if the task is linked to a master task
  */
  bool isLinked();

  ~QCalendara();

private:
  QLinkBox* linkbox;

};

#endif
