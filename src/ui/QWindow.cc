// -*- mode: c++; c-basic-offset: 2; c-indentation-style: ellemtel; -*-

#include "QWindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QVBoxLayout>

QWindow::QWindow(QWidget* parent):QMainWindow(parent)
{
  QAction *quit = new QAction(trUtf8("Quitter"), this);

  QMenu *file;
  file = menuBar()->addMenu(trUtf8("Fichier"));
  file->addAction(quit);

  QMenu *pref;
  pref = menuBar()->addMenu(trUtf8("Edition"));
  
  QMenu *help;
  help = menuBar()->addMenu(trUtf8("Aide"));

  connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));

  this->container = new QScrollArea(this);
  this->container->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  this->container->setWidgetResizable(true);
  QVBoxLayout* scrollLayout = new QVBoxLayout(this->container);
  this->setCentralWidget(this->container);
}

void QWindow::setScrolledWidget(QWidget *widget)
{
  this->container->setWidget(widget);
}

QWidget* QWindow::scrolledWidget() const
{
  return this->container->widget();
}
