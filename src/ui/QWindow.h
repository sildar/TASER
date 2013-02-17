// -*- mode: c++; c-basic-offset: 2; c-indentation-style: ellemtel; -*-

#ifndef QWINDOW_H
#define QWINDOW_H

#include <QMainWindow>
#include <QScrollArea>

class QWindow : public QMainWindow{
  Q_OBJECT
  
public:
  QWindow(QWidget* parent=0);
  void setScrolledWidget(QWidget *widget);
  QWidget* scrolledWidget() const;

private :
  QScrollArea* container;
};

#endif
