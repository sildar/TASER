// -*- mode: c++; c-basic-offset: 2; c-indentation-style: ellemtel; -*-

#ifndef _QLABELEDIT_H_
#define _QLABELEDIT_H_

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>

class QLabelEdit : public QWidget
{
  Q_OBJECT

public:
  QLabelEdit(QString &s);

private slots:
  void toggle();

private:
  QString text;
  QLabel *ro;
  QLineEdit *rw;
  QWidget *current;
};

#endif /* _QLABELEDIT_H_ */
