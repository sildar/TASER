// -*- mode: c++; c-basic-offset: 2; c-indentation-style: ellemtel; -*-

#include "QCalendara.h"
#include <QGridLayout>
#include <iostream>
#include <QTextCharFormat>

QCalendara::QCalendara(QWidget *parent, QString* parentDate):QCalendarWidget(parent){

  if (parentDate != NULL)
    {
      QTextCharFormat format = this->dateTextFormat(QDate::fromString(*parentDate));
      format.setBackground(QBrush(Qt::green,Qt::SolidPattern));
      format.setFontItalic(true);
      std::cout << parentDate->toStdString() << std::endl;
      this->setDateTextFormat(QDate::fromString(*parentDate), format);
    }
  this->linkbox = new QLinkBox("Lier la tache a la tache principale");

  this->layout()->addWidget(linkbox);
}

bool
QCalendara::isLinked()
{
  return linkbox->isLinked();
}
