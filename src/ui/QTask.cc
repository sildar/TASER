// -*- mode: c++; c-basic-offset: 2; c-indentation-style: ellemtel; -*-

#include "QTask.h"
#include <QtDebug>
#include "../model/TaskController.h"

QTask::QTask(Task* t, QTask* parent)
  : task(t)
{
  setDone(false);
  // setCurrent(true);
  
  this->setAttribute(Qt::WA_DeleteOnClose);

  QVBoxLayout *lay = new QVBoxLayout();
  setLayout(lay);
  lay->setContentsMargins(0, 0, 0, 0);

  this->qTaskWidget = new QWidget();
  QHBoxLayout *qTaskLayout = new QHBoxLayout();
  qTaskLayout->setContentsMargins(0, 0, 0, 0);

  QString textstr = QString::fromStdString(task->getName());
  time_t datet = task->getDate();
  QString datestr = ctime(&datet);
  //QDate dateq = QDateTime::fromTime_t(datet).date();
  QDate dateq = QDate::currentDate();

  if (parent != NULL) {
    dateq = parent->cal->selectedDate();
  }

  // Check button
  check = new QCheckBox();
  check->setToolTip(trUtf8("Marquer comme fait"));
  connect(check, SIGNAL(clicked()), this, SLOT(checkTask()));
  connect(check, SIGNAL(clicked()), this, SLOT(enable()));
  qTaskLayout->addWidget(check);

  //0x2193 is a arrow down
  expand = new QToolButton();
  expand->setToolTip(trUtf8("Déplier la tâche"));
  expand->setText(QChar(0x2193));
  expand->setCheckable(true);
  qTaskLayout->addWidget(expand);
  connect(expand, SIGNAL(toggled(bool)), this, SLOT(changeText(bool)));
  connect(expand, SIGNAL(toggled(bool)), this, SLOT(enable()));

  // Parameter Button and its menu
  param = new QToolButton();
  param->setToolTip(trUtf8("Actions disponibles"));
  param->setIcon(QIcon("./resources/param_icon_black_32.png"));

  QMenu *menu = new QMenu();
  addTaskAction = new QAction(trUtf8("Ajouter une tâche"),menu);
  //addTaskAction->setShortcut(QKeySequence(trUtf8("CTRL+T")));
  menu->addAction(addTaskAction);
  checkTaskAction = new QAction(trUtf8("Marquer comme fait"),menu);
  menu->addAction(checkTaskAction);

  menu->addSeparator();

  orderSubtasksAction = new QAction(trUtf8("Ordonner les tâches"),menu);
  menu->addAction(orderSubtasksAction);
  menu->addSeparator();
  menu->addAction(trUtf8("Insérer un template"));
  menu->addAction(trUtf8("Sauver un template"));
  menu->addSeparator();
  menu->addAction(trUtf8("Monter la tâche"));
  menu->addAction(trUtf8("Descendre la tâche"));
  menu->addSeparator();
  expandTaskAction = new QAction(trUtf8("Déplier la tâche"),menu);
  menu->addAction(expandTaskAction);

  delTaskAction = new QAction(trUtf8("Supprimer la tâche"), menu);
  menu->addAction(delTaskAction);  

  param->setMenu(menu);
  param->setPopupMode(QToolButton::InstantPopup);
  qTaskLayout->addWidget(param);

  connect(menu, SIGNAL(triggered(QAction*)), this, SLOT(menuActionManager(QAction*)));
  connect(menu, SIGNAL(triggered(QAction*)), this, SLOT(enable()));
  
  // Separator
  QFrame *f = new QFrame();
  f->setFrameStyle( QFrame::VLine | QFrame::Sunken );
  qTaskLayout->addWidget(f);

  // Ordered or not
  order = new QLabel();
  order->setToolTip(trUtf8("Ordonner les tâches"));
  if (parent != NULL && parent->task->hasOrderedSubtasks())
  {
    order->setText(QString::number(t->getIndex()));
  }
  else
  {
    order->setText("-");
  }
  qTaskLayout->addWidget(order);

  // Task text
  text = new QLabelEdit(textstr);
  text->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  qTaskLayout->addWidget(text);
  connect(text,SIGNAL(textChanged(QString&)),this, SLOT(textChanged(QString&)));

  // Task date
  date = new QLabel("<a href='date'>" % dateq.toString()   % "</a>");
  date->installEventFilter(this);
  date->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
  qTaskLayout->addWidget(date);

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
  qTaskLayout->addWidget(f2);

  // Close button
  closeButton = new QToolButton();
  closeButton->setToolTip(trUtf8("Supprimer la tâche"));
  closeButton->setText("x");
  closeButton->setStyleSheet("color: red");
  connect(closeButton, SIGNAL(clicked()), this, SLOT(closeTask()));
  qTaskLayout->addWidget(closeButton);

  this->qTaskWidget->setLayout(qTaskLayout);

  installEventFilter(this);

  //Management of the subtasks
  this->subtaskContainer = new QWidget();
  QVBoxLayout* subtaskLayout = new QVBoxLayout();
  subtaskLayout->setContentsMargins(20, 0, 0, 0);
  this->subtaskContainer->setLayout(subtaskLayout);
  this->subtaskContainer->setVisible(false);
  if (parent != NULL)
  {
    parent->subtaskContainer->layout()->addWidget(this);
  }
  connect(this->expand, SIGNAL(toggled(bool)), this->subtaskContainer, SLOT(setVisible(bool)));

  lay->addWidget(this->qTaskWidget);
  lay->addWidget(this->subtaskContainer);
}

bool
QTask::eventFilter(QObject* object, QEvent* event)
{
  if(object == date) {
    if(event->type() == QEvent::MouseButtonPress) {
      calmenu->show();
      return false; // lets the event continue to the edit
    }
  } else if (object == this) {
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
  date->setText("<a href='date'>" % aDate.toString() % "</a>");
  task->setDate(QDateTime(aDate).QDateTime::toTime_t());
}

void
QTask::changeText(bool isPressed)
{
  if (isPressed)
  {
    expand->setText(QChar(0x2191));
  }
  else
  {
    expand->setText(QChar(0x2193));
  }
}

void
QTask::checkTask()
{
  std::cout << "task is null ? " << (task == NULL) << std::endl;
  task->checkTask();
  setDone(task->isChecked());
}

void
QTask::menuActionManager(QAction* action)
{
  if (action == checkTaskAction) {
    this->checkTask();
    this->check->setChecked(this->task->isChecked());
  } else if (action == delTaskAction) {
    //carefull shaky part
    this->closeButton->click();
  } else if (action == expandTaskAction) {
    this->expand->toggle();
  } else if (action == addTaskAction) {
    this->addSubtask();
    if (!this->expand->isChecked()) {
      this->expand->toggle();
    }
  } else if (action == orderSubtasksAction) {
    orderSubtasks();
  }
}

void QTask::orderSubtasks()
{
  this->task->setSubtasksOrdered(!this->task->hasOrderedSubtasks());
  if (this->task->hasOrderedSubtasks()) {
    orderSubtasksAction->setText(trUtf8("Enlever l'ordre"));
    for (int i=0; i < this->subtaskContainer->layout()->count(); i++) {
	  QTask * curr = (QTask*) this->subtaskContainer->layout()->itemAt(i)->widget();
	  curr->order->setText(QString::number(curr->task->getIndex())); 
	}
  } else {
    orderSubtasksAction->setText(trUtf8("Ordonner les tâches"));
    for (int i=0; i<this->subtaskContainer->layout()->count(); i++) {
	  QTask * curr = (QTask*) this->subtaskContainer->layout()->itemAt(i)->widget();
	  curr->order->setText("-"); 
	}
  }
}

void QTask::addSubtask()
{
  setStyle(style());
  Task* t = new Task(trUtf8("Titre").toStdString(), this->task,
                     this->task->hasOrderedSubtasks(),
                     this->task->getDate());
  QTask* task = new QTask(t, this);
}

void QTask::closeTask(){
  for (int i=0; i < this->subtaskContainer->layout()->count(); i++)
  {
    this->subtaskContainer->layout()->itemAt(i)->widget()->close();
  }
  this->close();
}

void QTask::textChanged(QString& s)
{
  task->setName(s.toStdString());
}

QTask::~QTask()
{
  TaskController::removeTask(task);
  delete task;
}

void
QTask::paintEvent(QPaintEvent *)
{
  QStyleOption opt;
  opt.init(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void
QTask::enable()
{
  emit enabled(this);
  redraw();
}

void
QTask::redraw()
{
  style()->unpolish(this);
  style()->polish(this);
  setStyle(style());
}

void QTask::changeEvent(QEvent* event)
{
  if (event->type() == QEvent::LanguageChange)
    {
      retranslate();
    }
  
  // remember to call base class implementation
  QWidget::changeEvent(event);
}


void QTask::retranslate(){
  addTaskAction->setText(trUtf8("Ajouter une tâche"));
  checkTaskAction->setText(trUtf8("Marquer comme fait"));
  delTaskAction->setText(trUtf8("Supprimer la tâche"));
  expandTaskAction->setText(trUtf8("Déplier la tâche"));

  if (this->task->hasOrderedSubtasks()) {
    orderSubtasksAction->setText(trUtf8("Enlever l'ordre"));
  }
  else {
      orderSubtasksAction->setText(trUtf8("Ordonner les tâches"));
    }
  
  
}
