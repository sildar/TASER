// -*- mode: c++; c-basic-offset: 2; c-indentation-style: ellemtel; -*-

#include "QTask.h"

QTask::QTask(Task* t)
  : task(t)
{

  QHBoxLayout *lay = new QHBoxLayout();

  QString textstr = QString::fromStdString(task->getName());
  time_t datet = task->getDate();
  QString datestr = ctime(&datet);

  // Check button
  check = new QCheckBox();
  connect(check, SIGNAL(clicked()), this, SLOT(checkTask()));
  lay->addWidget(check);

  //0x2193 is a arrow down
  expand = new QToolButton();
  expand->setText(QChar(0x2193));
  lay->addWidget(expand);

  // Parameter Button
  param = new QToolButton();
  param->setIcon(QIcon("./resources/param_icon_black_32.png"));
  QMenu *menu = new QMenu();
  menu->addAction(trUtf8("Ajouter une tâche"));
  checkTaskAction = new QAction(trUtf8("Marquer comme fait"),menu);
  //menu->addAction();
  menu->addAction(checkTaskAction);
  menu->addSeparator();
  menu->addAction(trUtf8("Insérer un template"));
  menu->addAction(trUtf8("Sauver un template"));
  menu->addSeparator();
  menu->addAction(trUtf8("Monter la tâche"));
  menu->addAction(trUtf8("Descendre la tâche"));
  menu->addSeparator();
  menu->addAction(trUtf8("Déplier la tâche"));
  menu->addAction(trUtf8("Supprimer la tâche"));
  param->setMenu(menu);
  param->setPopupMode(QToolButton::InstantPopup);
  lay->addWidget(param);

  connect(menu, SIGNAL(triggered(QAction*)), this, SLOT(menuActionManager(QAction*)));

  
  // Separator
  QFrame *f = new QFrame();
  f->setFrameStyle( QFrame::VLine | QFrame::Sunken );
  lay->addWidget(f);

  // Ordered or not
  order = new QLabel();
  order->setText("-");
  lay->addWidget(order);

  // Task text
  text = new QLabelEdit(textstr);
  lay->addWidget(text);

  // Task date
  date = new QLineEdit(datestr);
  date->installEventFilter(this);
  lay->addWidget(date);

  //prepares the popup
  calmenu = new QWidget();
  cal = new QCalendara(calmenu, &datestr);
  calmenu->installEventFilter(this);

  calmenu->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
  calmenu->resize(cal->sizeHint());
  connect(cal, SIGNAL(clicked(QDate)), this, SLOT(setDateText(QDate)));

  // Separator
  QFrame *f2 = new QFrame();
  f2->setFrameStyle( QFrame::VLine | QFrame::Sunken );
  lay->addWidget(f2);

  // Close button
  close = new QToolButton();
  close->setText("x");
  close->setStyleSheet("color: red");
  connect(close, SIGNAL(clicked()), this, SLOT(close()));
  lay->addWidget(close);

  setLayout(lay);

  installEventFilter(this);

}

bool
QTask::eventFilter(QObject* object, QEvent* event)
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

void
QTask::setDateText(QDate aDate)
{
  date->setText(aDate.toString());
}

void
QTask::checkTask()
{
  task->checkTask();
}

void
QTask::menuActionManager(QAction* action)
{
  if (action == checkTaskAction)
    {
      this->checkTask();
      this->check->setChecked(this->task->isChecked());
    }
}

void
QTask::closeTask(){
  delete task;
  delete this;
}
