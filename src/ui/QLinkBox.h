// -*- mode: c++; c-basic-offset: 2; c-indentation-style: ellemtel; -*-

#ifndef QLINKBOX_H
#define QLINKBOX_H

#include <QCheckBox>
#include <QWidget>
#include <QLabel>
#include <string>
#include <QHBoxLayout>

/*!
  \brief A widget consisting in a checkbox and its associated label
*/
class QLinkBox : public QWidget
{
  Q_OBJECT

public:
  /*
    \brief constructor, the label is specified by the first, mandatory
    parameter.
  */
  QLinkBox(QString label, QWidget* parent=0);
  /*
    \brief says if the checkbox is checked
  */
  bool isLinked();

  void setText(QString txt);

signals:
  void boxChecked(bool);

public slots:
  void manageCheckBox(bool);

private:
  QHBoxLayout* lay;
  QCheckBox *linkbox;
  QLabel *linkboxlab;

};

#endif
