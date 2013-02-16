// -*- mode: c++; c-basic-offset: 2; c-indentation-style: ellemtel; -*-

#include "QCalendara.h"
#include <QGridLayout>

QCalendara::QCalendara(QWidget *parent):QCalendarWidget(parent)
{
  this->linkbox = new QLinkBox("Lier la tache a la tache principale");

  this->layout()->addWidget(linkbox);
}

bool
QCalendara::isLinked()
{
  return linkbox->isLinked();
}

QCalendara::~QCalendara()
{
  delete linkbox;
}
