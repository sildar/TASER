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
          this, SLOT(enableRw()));
  connect(rw, SIGNAL(editingFinished()),
          this, SLOT(enableRo()));

  current = ro;
  rw->hide();

  setLayout(layout);
}

void
QLabelEdit::enableRw()
{
  if (current == ro) {
    current->hide();
    current = rw;
    current->show();
    rw->selectAll();
    rw->setFocus();
  }
}

void
QLabelEdit::enableRo()
{
  if (current == rw) {
    current->hide();
    current = ro;
    current->show();
    if (rw->text().isEmpty()) {
      text = "-";
    } else {
      text = rw->text();
    }
    emit(textChanged(text));
    ro->setText("<a href='title'>" % text % "</a>");
  }
}
