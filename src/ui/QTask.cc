// -*- mode: c++; c-basic-offset: 2; c-indentation-style: ellemtel; -*-

#include "QTask.h"
#include <QtDebug>

#include "../model/TaskController.h"

QTask::QTask(Task* t, QTask* parent)
  : task(t)
{
  text = NULL;
  connect(this, SIGNAL(changedDone(bool)), this, SLOT(redraw()));
  connect(this, SIGNAL(changedCurrent(bool)), this, SLOT(redraw()));
  connect(this, SIGNAL(changedLate(bool)), this, SLOT(redraw()));
  setDone(false);
  setLate(false);

  pare = parent;
  dateIsLinked = task->hasLinkedDate();
  
  this->setAttribute(Qt::WA_DeleteOnClose);

  QVBoxLayout *lay = new QVBoxLayout();
  setLayout(lay);

  this->qTaskWidget = new QWidget();
  QHBoxLayout *qTaskLayout = new QHBoxLayout();

  QString textstr = QString::fromStdString(task->getName());
  time_t datet = task->getDate();
  QString datestr = ctime(&datet);
  QDate dateq = QDateTime::fromTime_t(task->getDate()).date();

  if (parent != NULL) {
    dateq = parent->cal->selectedDate();
  }

  // Check button
  check = new QCheckBox();
  check->setToolTip(trUtf8("Marquer comme fait"));
  check->setChecked(this->task->isChecked());
  connect(check, SIGNAL(toggled(bool)), this, SLOT(checkTask(bool)));
  setDone(this->task->isChecked());
  check->setEnabled(task->isCheckable());
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
  menu->addAction(addTaskAction);
  checkTaskAction = new QAction(trUtf8("Marquer comme fait"),menu);
  menu->addAction(checkTaskAction);

  menu->addSeparator();

  orderSubtasksAction = new QAction(trUtf8("Ordonner les tâches"),menu);
  menu->addAction(orderSubtasksAction);
  menu->addSeparator();
  templateMenu = menu->addMenu(trUtf8("Insérer un template"));

  std::list<std::string> templatelist = TaskController::loadTemplateList();

  for (std::list<std::string>::iterator it = templatelist.begin(); it != templatelist.end(); ++it)
  {
    templateMenu->addAction(QString(it->c_str()));
  }
  connect(templateMenu, SIGNAL(triggered(QAction*)), this, SLOT(manageTemplates(QAction*)));


  saveTemplateAction = new QAction(trUtf8("Sauver un template"),menu);
  menu->addAction(saveTemplateAction);
  menu->addSeparator();

  upTaskAction = new QAction(trUtf8("Monter la tâche"),menu);
  menu->addAction(upTaskAction);
  downTaskAction = new QAction(trUtf8("Descendre la tâche"),menu);
  menu->addAction(downTaskAction);
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
  connect(text,SIGNAL(textChanged(const QString&)),this, SLOT(textChanged(const QString&)));
  connect(this, SIGNAL(changedDone(bool)), text, SLOT(redraw()));
  connect(this, SIGNAL(changedLate(bool)), text, SLOT(redraw()));

  // Task date
  date = new QLabel("<a href='date'>" % dateq.toString()   % "</a>");
  setLate(dateq < QDate::currentDate());
  date->installEventFilter(this);
  date->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
  qTaskLayout->addWidget(date);

  //prepares the popup
  calmenu = new QWidget(this);
  cal = new QCalendara(calmenu, this->task->hasLinkedDate(), &datestr);
  calmenu->installEventFilter(this);

  calmenu->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
  calmenu->resize(cal->sizeHint());
  connect(cal, SIGNAL(clicked(QDate)), this, SLOT(setDateText(QDate)));
  connect(cal, SIGNAL(boxChecked(bool)),this, SLOT(dateLinked(bool)));

  // Separator
  QFrame *f2 = new QFrame();
  f2->setFrameStyle( QFrame::VLine | QFrame::Sunken );
  qTaskLayout->addWidget(f2);

  // Close button
  closeButton = new QToolButton();
  closeButton->setToolTip(trUtf8("Supprimer la tâche"));
  closeButton->setText("x");
  closeButton->setObjectName("closeButton");
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

  // recursive creation of QTasks, if any subtasks in this->task
  std::list<Task*> subtasks = this->task->getSubtasks();
  for (std::list<Task*>::iterator it = subtasks.begin();
       it != subtasks.end(); ++it)
  {
    new QTask((*it), this);
  }
}

void
QTask::saveTemplate(int code){
  if (code == QMessageBox::Ok)
  {
    std::cout << "template saved ! " << std::endl;
    std::string fileName = "./templates/";
    fileName = fileName.append(this->task->getName());
    fileName = fileName.append(".xml");
    TaskController::saveTemplate(fileName,this);

    //updates the template menu
    TaskController::reloadTemplateMenu();
  }
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

  for (int i=0; i < this->subtaskContainer->layout()->count(); i++) {
    QTask * curr = (QTask*) this->subtaskContainer->layout()->itemAt(i)->widget();
    if (curr->task->hasLinkedDate())
    {
      curr->refreshDateText();
    }
  }
  
  task->setDate(QDateTime(aDate).QDateTime::toTime_t());
  setLate(aDate < QDate::currentDate());
}

void
QTask::refreshDateText()
{
  QDate aDate = QDateTime::fromTime_t(task->getDate()).date();
  date->setText("<a href='date'>" % aDate.toString() % "</a>");

  for (int i=0; i < this->subtaskContainer->layout()->count(); i++) {
    QTask * curr = (QTask*) this->subtaskContainer->layout()->itemAt(i)->widget();
    if (curr->task->hasLinkedDate())
    {
      curr->refreshDateText();
    }
  }

  setLate(aDate < QDate::currentDate());
}

void
QTask::dateLinked(bool isLinked)
{
  this->dateIsLinked = isLinked;
  this->task->setLinkedDate(isLinked);
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
QTask::checkTask(bool isChecked)
{
  
  task->checkTask(isChecked);
  this->check->setEnabled(task->isCheckable());
  
  if (pare != NULL)
  {
    for (int i=0; i < pare->subtaskContainer->layout()->count(); i++) {
      QTask * curr = (QTask*) pare->subtaskContainer->layout()->itemAt(i)->widget();
      curr->check->setEnabled(curr->task->isCheckable());
      curr->check->setChecked(curr->task->isChecked());
    }

    pare->check->setEnabled(pare->task->isCheckable());
  }
  else
  {
    for (int i=0; i < this->subtaskContainer->layout()->count(); i++) {
      QTask * curr = (QTask*) this->subtaskContainer->layout()->itemAt(i)->widget();
      curr->check->setEnabled(curr->task->isCheckable());
      curr->check->setChecked(curr->task->isChecked());
    }
  }

  setDone(task->isChecked());
}

void
QTask::manageTemplates(QAction* action)
{
  TaskController::loadTemplate(action->text().toStdString(),this);
}

void
QTask::menuActionManager(QAction* action)
{
  
  if (action == checkTaskAction) {
    this->checkTask(!this->check->isChecked());
    this->check->setChecked(this->task->isChecked());
  } else if (action == delTaskAction) {
    //carefull shaky part
    this->closeButton->click();
  } else if (action == expandTaskAction) {
    this->expand->toggle();
  } else if (action == addTaskAction) {
    this->task->checkTask(false);
    this->check->setChecked(false);
    this->check->setEnabled(false);
    this->addSubtask();
    if (!this->expand->isChecked()) {
      this->expand->toggle();
    }
  } else if (action == orderSubtasksAction) {
    orderSubtasks();
  }
  else if (action == upTaskAction){
    if (this->task->hasBigBrother()) {
      QBoxLayout* lay = (QBoxLayout*) pare->subtaskContainer->layout();
      exchangeWidgets(this->task->getIndex()-1,-1,lay);
      this->task->getUp();
      }
  }
  else if (action == downTaskAction){
    if (this->task->hasLittleBrother()){
      QBoxLayout* lay = (QBoxLayout*) pare->subtaskContainer->layout();
      exchangeWidgets(this->task->getIndex()-1,1,lay);
      this->task->getDown();
    }
  }
  else if (action == saveTemplateAction){
    QString message = trUtf8("Le template sera sauvé sous le nom ");
    message = message.append(QString(this->task->getName().c_str()));
    message = message.replace(QRegExp("/"),"_");
    message = message.append("\n");
    message = message.append(trUtf8("Si un template du même nom existe, il sera écrasé."));
    saveTemplateMB = new QMessageBox(QMessageBox::Question,trUtf8("Sauver un template"), message,QMessageBox::Abort | QMessageBox::Ok);
    
    connect(saveTemplateMB,SIGNAL(finished(int)),this, SLOT(saveTemplate(int)));

    saveTemplateMB->show();
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

void QTask::textChanged(const QString& s)
{
  task->setName(s.toStdString());
}

void QTask::exchangeWidgets(int from, int change, QBoxLayout* layout)
{
  QWidget* widget = layout->takeAt(from)->widget();
  layout->insertWidget(from+change,widget);
}

QTask::~QTask()
{
  for (int i=0; i < this->subtaskContainer->layout()->count(); i++) {
    QTask * curr = (QTask*) this->subtaskContainer->layout()->itemAt(i)->widget();
    delete curr;
  }
  delete task; task = NULL;
}

void
QTask::setTasksCheckable(QTask* parent)
{

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
}

void
QTask::redraw()
{
  style()->unpolish(this);
  style()->polish(this);
  setStyle(style());
  if (text) {
    text->setBackground(palette().color(QPalette::Background));
  }
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
