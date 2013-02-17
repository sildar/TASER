// -*- mode: c++; c-basic-offset: 2; c-indentation-style: ellemtel; -*-

#include "QLinkBox.h"

QLinkBox::QLinkBox(QString label,QWidget *parent)
  : QWidget(parent)
{
  this->linkboxlab = new QLabel(label);
  this->linkbox = new QCheckBox();
  this->linkbox->setChecked(true);
  this->lay = new QHBoxLayout();

  lay->addWidget(linkbox);
  lay->addWidget(linkboxlab);

  this->setLayout(lay);
}

bool
QLinkBox::isLinked()
{
  return this->linkbox->isChecked();
}
