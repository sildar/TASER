// -*- mode: c++; c-basic-offset: 2; c-indentation-style: ellemtel; -*-

#ifndef QWINDOW_H
#define QWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QDir>
#include <QLocale>
#include <QTranslator>
#include <QLibraryInfo>
#include <iostream>

class QWindow : public QMainWindow{
  Q_OBJECT
  
public:
  QWindow(QWidget* parent=0);
  void setScrolledWidget(QWidget *widget);
  QWidget* scrolledWidget() const;

private :
  QScrollArea* container;
  QMenu* pref;

  QTranslator m_translator;   /**< contains the translations for this application */
  QTranslator m_translatorQt; /**< contains the translations for qt */
  QString m_currLang;     /**< contains the currently loaded language */
  QString m_langPath;     /**< Path of language files. This is always fixed to /languages. */
  
  void createLanguageMenu();
  void loadLanguage(const QString& rLanguage);

public slots:
  void slotLanguageChanged(QAction*);
};

#endif
