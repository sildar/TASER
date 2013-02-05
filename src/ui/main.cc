// -*- c-basic-offset: 2; c-indentation-style: ellemtel; -*-
#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QWidget>
#include <QDebug>
#include "MyWidget.hpp"

int main(int argc, char** argv)
{
  QApplication *qapp = new QApplication(argc, argv);

  MyWidget *w = new MyWidget();
  QWidget *mw = new QWidget();
  QVBoxLayout *vbox = new QVBoxLayout();
  QPushButton *p1 = new QPushButton("p1");
  mw->setLayout(vbox);
  vbox->addWidget(w);
  vbox->addWidget(p1);
  mw->show();
  return qapp->exec();
}
