// -*- mode: c++; c-basic-offset: 2; c-indentation-style: ellemtel; -*-

#include "QLabelEdit.h"

QLabelEdit::QLabelEdit(QString text)
{
  ro = new QPushButton(text);
  rw = new QLineEdit(text);
  QVBoxLayout *layout = new QVBoxLayout();
  layout->addWidget(ro);
  layout->addWidget(rw);

  connect(ro, SIGNAL(clicked()),
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
  } else {
    current = ro;
    ro->setText(rw->text());
  }
  current->show();
}
