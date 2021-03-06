// -*- mode: c++; c-basic-offset: 2; c-indentation-style: ellemtel; -*-

#include "QCalendara.h"
#include <QGridLayout>
#include <iostream>
#include <QTextCharFormat>
#include <QLocale>

QCalendara::QCalendara(QWidget *parent, bool checked, QString *parentDate)
  : QCalendarWidget(parent)
{

  this->setLocale(QLocale());
  if (parentDate != NULL)
  {
    QTextCharFormat format = this->dateTextFormat(QDate::fromString(*parentDate));
    format.setBackground(QBrush(Qt::green,Qt::SolidPattern));
    format.setFontItalic(true);
    this->setDateTextFormat(QDate::fromString(*parentDate), format);
  }
  this->linkbox = new QLinkBox(trUtf8("Lier la tache à la tâche principale"), checked);

  this->layout()->addWidget(linkbox);
  connect(linkbox,SIGNAL(boxChecked(bool)),this,SLOT(manageCheckBox(bool)));
}

void
QCalendara::manageCheckBox(bool isChecked){
  emit boxChecked(isChecked);
}

bool
QCalendara::isLinked()
{
  return linkbox->isLinked();
}


void QCalendara::changeEvent(QEvent* event)
{
  if (event->type() == QEvent::LanguageChange)
    {
      this->setLocale(QLocale());
      linkbox->setText(trUtf8("Lier la tache à la tâche principale"));
    }
  
  // remember to call base class implementation
  QWidget::changeEvent(event);
}
