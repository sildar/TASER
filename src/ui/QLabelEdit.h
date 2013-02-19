// -*- mode: c++; c-basic-offset: 2; c-indentation-style: ellemtel; -*-

#ifndef _QLABELEDIT_H_
#define _QLABELEDIT_H_

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>

class QLabelEdit : public QLineEdit
{
  Q_OBJECT

public:
  QLabelEdit(QString &s);

protected:
  void mouseDoubleClickEvent(QMouseEvent *event);

private slots:
  void enableReadOnly();
  
private:
  QString text_;
};

#endif /* _QLABELEDIT_H_ */
