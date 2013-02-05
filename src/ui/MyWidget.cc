// -*- c-basic-offset: 2; c-indentation-style: ellemtel; -*-
#include "MyWidget.hpp"
#include <QDebug>

MyWidget::MyWidget()
{
  b1 = new QPushButton(tr("&b1"));
  b2 = new QPushButton(tr("&b2\nFoo"));
  b3 = new QPushButton(tr("&b3"));
  connect(b1, SIGNAL(clicked()), this, SLOT(toggle()));
  connect(b2, SIGNAL(clicked()), this, SLOT(toggle()));

  QVBoxLayout *layout = new QVBoxLayout();
  layout->addWidget(b1);
  layout->addWidget(b2);
  layout->addWidget(b3);
  current = b1;
  b2->hide();

  setLayout(layout);
  
}

void
MyWidget::toggle()
{
  current->hide();
  if (current == b1) {
    current = b2;
  } else {
    current = b1;
  }
  current->show();
}
