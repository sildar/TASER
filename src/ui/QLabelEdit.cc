// -*- mode: c++; c-basic-offset: 2; c-indentation-style: ellemtel; -*-

#include "QLabelEdit.h"

QLabelEdit::QLabelEdit(QString &s)
  : text(s)
{
  ro = new QLabel("<a href='title'>" % text % "</a>");
  rw = new QLineEdit(text);
  QVBoxLayout *layout = new QVBoxLayout();
  layout->addWidget(ro);
  layout->addWidget(rw);

  connect(ro, SIGNAL(linkActivated(const QString&)),
          this, SLOT(toggle()));
  connect(rw, SIGNAL(returnPressed()),
          this, SLOT(toggle()));

  current = ro;
  rw->hide();

  setLayout(layout);
}

void
QLabelEdit::toggle()
{
  current->hide();
  if (current == ro) {
    current = rw;
    rw->selectAll();
    rw->setFocus();
  } else {
    current = ro;
    text = rw->text();
    ro->setText("<a href='title'>" % text % "</a>");
  }
  current->show();
}
