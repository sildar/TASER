// -*- mode: c++; c-basic-offset: 2; c-indentation-style: ellemtel; -*-

#ifndef _QLABELEDIT_H_
#define _QLABELEDIT_H_

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>

class QLabelEdit : public QWidget
{
  Q_OBJECT

public:
  QLabelEdit(QString s);

private slots:
  void toggle();

private:
  QPushButton *ro;
  QLineEdit *rw;
  QWidget *current;
};

#endif /* _QLABELEDIT_H_ */
