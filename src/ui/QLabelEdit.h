// -*- mode: c++; c-basic-offset: 2; c-indentation-style: ellemtel; -*-

#ifndef _QLABELEDIT_H_
#define _QLABELEDIT_H_

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QStyle>

class QLabelEdit : public QLineEdit
{
  Q_OBJECT

public:
  QLabelEdit(QString &s);
  void setBackground(const QColor &bg);                      

public slots:
  void redraw();
  
protected:
  void mouseDoubleClickEvent(QMouseEvent *event);

private slots:
  void enableReadOnly();
  
private:
  QString text_;
  QColor bg_;
};

#endif /* _QLABELEDIT_H_ */
