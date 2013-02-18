// -*- mode: c++; c-basic-offset: 2; c-indentation-style: ellemtel; -*-

#include "QWindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QVBoxLayout>

QWindow::QWindow(QWidget* parent):QMainWindow(parent)
{

  //creating the menu
  QAction *quit = new QAction(trUtf8("Quitter"), this);

  QMenu *file;
  file = menuBar()->addMenu(trUtf8("Fichier"));
  file->addAction(quit);

  pref = menuBar()->addMenu(trUtf8("Edition"));
  //pref->addAction();
  
  QMenu *help;
  help = menuBar()->addMenu(trUtf8("Aide"));

  connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));

  this->container = new QScrollArea(this);
  this->container->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  this->container->setWidgetResizable(true);
  QVBoxLayout* scrollLayout = new QVBoxLayout(this->container);
  this->setCentralWidget(this->container);

  createLanguageMenu();
}

void QWindow::setScrolledWidget(QWidget *widget)
{
  this->container->setWidget(widget);
}

QWidget* QWindow::scrolledWidget() const
{
  return this->container->widget();
}



// Called every time, when a menu entry of the language menu is called
void QWindow::slotLanguageChanged(QAction* action)
{
  if(0 != action)
    {
      // load the language dependant on the action content
      loadLanguage(action->data().toString());
      setWindowIcon(action->icon());
    }
}

void switchTranslator(QTranslator& translator, const QString& filename)
{
  // remove the old translator
  qApp->removeTranslator(&translator);
  
  // load the new translator
  if(translator.load(filename))
    qApp->installTranslator(&translator);
}

void QWindow::loadLanguage(const QString& rLanguage)
{
  if(m_currLang != rLanguage)
    {
      m_currLang = rLanguage;
      QLocale locale = QLocale(m_currLang);
      QLocale::setDefault(locale);
      QString languageName = QLocale::languageToString(locale.language());
      switchTranslator(m_translator, QString("taser_%1.qm").arg(rLanguage));
      switchTranslator(m_translatorQt, QString("qt_%1.qm").arg(rLanguage));
    }
}



// we create the menu entries dynamically, dependant on the existing translations.
void QWindow::createLanguageMenu(void)
{
  QActionGroup* langGroup = new QActionGroup(pref);
  langGroup->setExclusive(true);
  
  connect(langGroup, SIGNAL(triggered(QAction *)), this, SLOT(slotLanguageChanged(QAction *)));
  
  // format systems language
  QString defaultLocale = QLocale::system().name();       // e.g. "de_DE"
  defaultLocale.truncate(defaultLocale.lastIndexOf('_')); // e.g. "de"
  
  m_langPath = QApplication::applicationDirPath();
  m_langPath.append("/languages");
  QDir dir(m_langPath);
  QStringList fileNames = dir.entryList(QStringList("taser_*.qm"));
  
  for (int i = 0; i < fileNames.size(); ++i)
    {
      // get locale extracted by filename
      QString locale;
      locale = fileNames[i];                  // "TranslationExample_de.qm"
      locale.truncate(locale.lastIndexOf('.'));   // "TranslationExample_de"
      locale.remove(0, locale.indexOf('_') + 1);   // "de"
      
      QString lang = QLocale::languageToString(QLocale(locale).language());
      QIcon ico(QString("%1/%2.png").arg(m_langPath).arg(locale));
      
      QAction *action = new QAction(ico, lang, this);
      action->setCheckable(true);
      action->setData(locale);
      
      this->pref->addAction(action);
      langGroup->addAction(action);
      
      // set default translators and language checked
      if (defaultLocale == locale)
	{
	  action->setChecked(true);
	}
    }
}
