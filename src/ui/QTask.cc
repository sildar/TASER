// -*- c-basic-offset: 2; c-indentation-style: ellemtel; -*-
#include "QTask.h"

QTask::QTask(Task* t){

  QHBoxLayout* lay = new QHBoxLayout();
  
  QString textstr = QString::fromStdString(t->getName());
  time_t datet = t->getDate();
  QString datestr = ctime(&datet);



  this->text = new QLabel(textstr);
  this->date = new QLineEdit(datestr);
  date->installEventFilter(this);
  
  //prepares the popup
  this->calmenu = new QWidget();
  this->cal = new QCalendara(calmenu);
  calmenu->installEventFilter(this);

  calmenu->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
  calmenu->resize(cal->sizeHint());


  this->check = new QCheckBox();
  //0x2193 is a arrow down
  this->extend = new QToolButton();
  extend->setText(QChar(0x2193));
  this->close = new QToolButton();
  close->setText("x");
  close->setStyleSheet("color: red");
  this->order = new QToolButton();
  order->setText("-");
  this->param = new QToolButton();
  param->setIcon(QIcon("./resources/param_icon_black_32.png"));
  //param->setIconSize(QSize(20,20));


  
  lay->addWidget(check);
  lay->addWidget(extend);
  lay->addWidget(param);

  //separator
  QFrame *f = new QFrame();
  f->setFrameStyle( QFrame::VLine | QFrame::Sunken );
  lay->addWidget(f);
  
  lay->addWidget(order);
  lay->addWidget(text);
  lay->addWidget(date);


  //separator
  QFrame *f2 = new QFrame();
  f2->setFrameStyle( QFrame::VLine | QFrame::Sunken );
  lay->addWidget(f2);

  lay->addWidget(close);

  this->setLayout(lay);

  this->installEventFilter(this);

  connect(cal, SIGNAL(clicked(QDate)), this, SLOT(setDateText(QDate)));

}

bool QTask::eventFilter(QObject* object, QEvent* event)
{
  if(object == date)
    {
      if(event->type() == QEvent::MouseButtonPress) {
	calmenu->show();
	return false; // lets the event continue to the edit
      }
    }
  else if (object == this)
    {
      if(event->type() == QEvent::WindowActivate) {
	calmenu->hide();
	return false; // lets the event continue to the edit
      }
    }
  return false;
}

void QTask::setDateText(QDate aDate){
  date->setText(aDate.toString());
}
