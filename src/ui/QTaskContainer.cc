// -*- mode: c++; c-basic-offset: 2; c-indentation-style: ellemtel; -*-

#include "QTaskContainer.h"

QTaskContainer::QTaskContainer(QWidget* parent)
  : QWidget(parent)
{
  addTaskButton = new QPushButton(trUtf8("Nouvelle Tâche"));

  tasks = std::list<QTask*>();
  tasksLayout = new QVBoxLayout();
  buttonLayout = new QHBoxLayout();
  buttonLayout->addWidget(addTaskButton);
  buttonLayout->addStretch(1);
  mainLayout = new QVBoxLayout(this);
  
  mainLayout->addLayout(buttonLayout);
  mainLayout->addLayout(tasksLayout);
  mainLayout->addStretch(1);

  connect(addTaskButton,SIGNAL(clicked()),this,SLOT(addTask()));


}

void
QTaskContainer::addTask(Task* parent)
{
  QTask* qtask;
  if (parent != NULL) {
    qtask = new QTask(new Task("Titre", parent,
                               parent->hasOrderedSubtasks(), NULL));
  } else {
    qtask = new QTask(new Task("Titre", NULL, false, NULL));
  }

  for (unsigned int i = 0; i <= (this->tasks.size() + 1); i++) {
    this->tasksLayout->setStretch(i, 0);
  }

  setStyle(style());
  tasks.push_back(qtask);
  this->tasksLayout->addWidget(qtask);  
  this->tasksLayout->addStretch(1);
}

void
QTaskContainer::paintEvent(QPaintEvent *)
{
  QStyleOption opt;
  opt.init(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
