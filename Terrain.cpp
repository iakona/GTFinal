#include "Terrain.h"

Terrain::Terrain(Ogre::SceneManager* sceneMgr, std::string name) {
  Ogre::Entity* entity = sceneMgr->createEntity(name, "cube.mesh");
  Ogre::SceneNode* sceneNode = sceneMgr->getRootSceneNode()->createChildSceneNode(name);
  sceneNode->attachObject(entity);
  sceneNode->scale(.7, 0, 2.5);
  sceneNode->translate(0, 0, 70);
  entity->setMaterialName("Examples/Frost");
  entity->setCastShadows(false);

  setNode(sceneNode);
}

Terrain::Terrain(Ogre::SceneManager* sceneMgr, std::string name, Ogre::Real x, Ogre::Real y, Ogre::Real z, Ogre::Real scalex, Ogre::Real scaley, Ogre::Real scalez) {
  Ogre::Entity* entity = sceneMgr->createEntity(name, "cube.mesh");
  Ogre::SceneNode* sceneNode = sceneMgr->getRootSceneNode()->createChildSceneNode(name);
  sceneNode->attachObject(entity);
  sceneNode->scale(scalex, scaley, scalez);
  sceneNode->translate(x, y, z);
  entity->setMaterialName("Examples/Frost");

  setNode(sceneNode);
}

Terrain::~Terrain(void) {
}