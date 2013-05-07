#include "Terrain.h"

Terrain::Terrain(Ogre::SceneManager* sceneMgr, std::string name,
  Ogre::Real x, Ogre::Real y, Ogre::Real z, Ogre::Radian angle,
  Ogre::Real l, Ogre::Real h, Ogre::Real w) {
  Ogre::Entity* entity = sceneMgr->createEntity(name, "cube.mesh");
  Ogre::SceneNode* sceneNode = sceneMgr->getRootSceneNode()->createChildSceneNode(name);
  sceneNode->attachObject(entity);
  sceneNode->scale((l/50),(h/50),(w/50));
  sceneNode->yaw(angle);
  sceneNode->translate(x, y, z);
  entity->setMaterialName("Examples/Frosty");

  setNode(sceneNode);
}

Terrain::~Terrain(void) {
}
