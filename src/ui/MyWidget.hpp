// -*- c-basic-offset: 2; c-indentation-style: ellemtel; -*-
#ifndef _MYWIDGET_H_
#define _MYWIDGET_H_

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class MyWidget : public QWidget
{
  Q_OBJECT
  
public:
  MyWidget();
  

private slots:
  void toggle();

private:
  QPushButton *b1, *b2, *current, *b3;
};

#endif /* _MYWIDGET_H_ */
