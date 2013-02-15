// -*- c-basic-offset: 2; c-indentation-style: ellemtel; -*-

#ifndef QLINKBOX_H
#define QLINKBOX_H

#include <QCheckBox>
#include <QWidget>
#include <QLabel>
#include <string>
#include <QHBoxLayout>

class QLinkBox : public QWidget
{
  Q_OBJECT

 public:
  QLinkBox(std::string label, QWidget* parent=0);
  bool isLinked();
  
 private:
  QHBoxLayout* lay;
  QCheckBox *linkbox;
  QLabel *linkboxlab;
  
};

#endif
