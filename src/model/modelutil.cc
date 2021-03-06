#include "modelutil.h"

void
saveTasklist(std::string xmlFile, std::list<Task*> tasks){
  TiXmlDocument doc;
  TiXmlDeclaration* xmlDecl = new TiXmlDeclaration("1.0", "UTF-8", "");
  TiXmlElement* root = new TiXmlElement("tasklist");

  // save each task recursively
  if (tasks.size() > 0)
  {
    for (std::list<Task*>::iterator iter = tasks.begin();
         iter != tasks.end(); iter++)
    {
      root->LinkEndChild((*iter)->xmlSubtree());
    }
  }

  doc.LinkEndChild(xmlDecl);
  doc.LinkEndChild(root);

  doc.SaveFile(xmlFile.c_str());

  /* Note: the LinkEndChild method uses pointers instead of references, so
   * that when linked, the objects become owned (and deleted) by tinyXml.
   * This method is efficient and adds an extra copy, but should be used
   * with care as it uses a different memory model than the other insert
   * functions.
   */
}

std::list<Task*>
loadTasklist(std::string xmlFile){
  std::list<Task*> tasklist = std::list<Task*>();

  TiXmlDocument doc(xmlFile.c_str());
  if (doc.LoadFile())
  {
    TiXmlElement* root = doc.RootElement();

    if (root != NULL)
    {
      for(TiXmlElement* element = root->FirstChildElement("task");
          element; element = element->NextSiblingElement("task"))
      {
        tasklist.push_back(new Task(element));
      }
    }
  }

  return tasklist;
}
