// -*- c-basic-offset: 2; c-indentation-style: ellemtel; -*-

#include "QLinkBox.h"

QLinkBox::QLinkBox(std::string label,QWidget *parent):QWidget(parent)
{
  this->linkboxlab = new QLabel(QString(label.c_str()));
  this->linkbox = new QCheckBox();
  this->lay = new QHBoxLayout();

  lay->addWidget(linkbox);
  lay->addWidget(linkboxlab);

  this->setLayout(lay);
}

bool QLinkBox::isLinked()
{
  return this->linkbox->isChecked();
}


QLinkBox::~QLinkBox(){
  delete linkbox;
  delete linkboxlab;
  delete lay;
}
