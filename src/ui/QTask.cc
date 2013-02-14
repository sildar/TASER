// -*- c-basic-offset: 2; c-indentation-style: ellemtel; -*-
#include "QTask.h"

QTask::QTask(Task* t){

  QHBoxLayout* lay = new QHBoxLayout();
  
  QString textstr = QString::fromStdString(t->getName());
  time_t datet = t->getDate();
  QString datestr = ctime(&datet);

  this->text = new QLabel(textstr);
  this->date = new QLabel(datestr);
  this->check = new QCheckBox();
  this->extend = new QToolButton();
  extend->setText(QChar(0x2193));
  this->close = new QToolButton();
  close->setText("x");
  close->setStyleSheet("color: red");
  this->order = new QToolButton();
  order->setText("-");


  
  lay->addWidget(check);
  lay->addWidget(extend);

  //separator
  QFrame *f = new QFrame();
  f->setFrameStyle( QFrame::VLine | QFrame::Sunken );
  lay->addWidget(f);
  
  lay->addWidget(order);
  lay->addWidget(text);
  lay->addWidget(date);

  //separator
  QFrame *f2 = new QFrame();
  f2->setFrameStyle( QFrame::VLine | QFrame::Sunken );
  lay->addWidget(f2);

  lay->addWidget(close);

  this->setLayout(lay);

}
