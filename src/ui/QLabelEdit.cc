// -*- mode: c++; c-basic-offset: 2; c-indentation-style: ellemtel; -*-

#include "QLabelEdit.h"
#include <QtDebug>

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

void
QLabelEdit::redraw()
{
  style()->unpolish(this);
  style()->polish(this);
  setStyle(style());
}

void
QLabelEdit::setBackground(const QColor &bg)
{
  setStyleSheet("*:!hover { background-color: " % bg.name() % ";}" %
                "*:hover { background-color: #cdad00; }");
}
