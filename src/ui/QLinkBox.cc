// -*- mode: c++; c-basic-offset: 2; c-indentation-style: ellemtel; -*-

#include "QLinkBox.h"

QLinkBox::QLinkBox(QString label,QWidget *parent)
  : QWidget(parent)
{
  this->linkboxlab = new QLabel(label);
  this->linkbox = new QCheckBox();
  //this->linkbox->setChecked(true);
  this->lay = new QHBoxLayout();

  lay->addWidget(linkbox);
  lay->addWidget(linkboxlab);

  this->setLayout(lay);
  connect(linkbox,SIGNAL(toggled(bool)),this,SLOT(manageCheckBox(bool)));
}

void
QLinkBox::manageCheckBox(bool isChecked){
  emit boxChecked(isChecked);
}

bool
QLinkBox::isLinked()
{
  return this->linkbox->isChecked();
}

void
QLinkBox::setText(QString txt)
{
  linkboxlab->setText(txt);
}
