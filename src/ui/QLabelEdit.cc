// -*- mode: c++; c-basic-offset: 2; c-indentation-style: ellemtel; -*-

#include "QLabelEdit.h"

QLabelEdit::QLabelEdit(QString &s)
  : text_(s)
{
  setText(text_);
  setReadOnly(true);
  connect(this, SIGNAL(editingFinished()),
          this, SLOT(enableReadOnly()));
  setAttribute(Qt::WA_Hover);
  setToolTip(trUtf8("Double Cliquer pour éditer"));
}

void
QLabelEdit::mouseDoubleClickEvent(QMouseEvent *event)
{
  setReadOnly(false);
  selectAll();
  setFocus();
}

void
QLabelEdit::enableReadOnly()
{
  setReadOnly(true);
}
