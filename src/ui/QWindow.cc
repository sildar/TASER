// -*- mode: c++; c-basic-offset: 2; c-indentation-style: ellemtel; -*-

#include "QWindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QApplication>

QWindow::QWindow(QWidget* parent):QMainWindow(parent)
{
  QAction *quit = new QAction("&Quit", this);

  QMenu *file;
  file = menuBar()->addMenu("&Fichier");
  file->addAction(quit);

  connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));
}