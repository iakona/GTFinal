#include "Wall.h"

// Wall is 25 x 10 x 5
Wall::Wall(Ogre::SceneManager* sceneMgr, std::string name,
  Ogre::Real x, Ogre::Real y, Ogre::Real z, Ogre::Radian angle) {
  Ogre::Entity* entity = sceneMgr->createEntity(name, "cube.mesh");
  Ogre::SceneNode* sceneNode = sceneMgr->getRootSceneNode()->createChildSceneNode(name);
  sceneNode->attachObject(entity);
  sceneNode->scale(.5,.2,.1);
  sceneNode->yaw(angle);
  sceneNode->translate(x, y, z);
  entity->setMaterialName("Examples/Rockwall");

  setNode(sceneNode);
}

Wall::Wall(Ogre::SceneManager* sceneMgr, std::string name,
  Ogre::Real x, Ogre::Real y, Ogre::Real z, Ogre::Radian angle,
  Ogre::Real l, Ogre::Real h, Ogre::Real w, int property) {
  Ogre::Entity* entity = sceneMgr->createEntity(name, "cube.mesh");
  Ogre::SceneNode* sceneNode = sceneMgr->getRootSceneNode()->createChildSceneNode(name);
  sceneNode->attachObject(entity);
  sceneNode->scale((l/50),(h/50),(w/50));
  sceneNode->yaw(angle);
  sceneNode->translate(x, y, z);
  bool invisible = property & 4;
  sceneNode->setVisible(!invisible);
  entity->setMaterialName("Examples/Rockwall");
  if (property & 1) {
    particle = sceneMgr->createParticleSystem(name + "cp", "Examples/PurpleFountain");
    particleNode = sceneNode->createChildSceneNode(name + "cp");
    particleNode->attachObject(particle);
    particle->fastForward(30);
  } else {
    particle = NULL;
    particleNode = NULL;
  }
  setNode(sceneNode);
}

Wall::~Wall(void) {
  if (particleNode && particle) {
    Ogre::SceneManager* sceneMgr = particleNode->getCreator();
    sceneMgr->destroyParticleSystem(particle);
    sceneMgr->destroyEntity(particleNode->getName());
    sceneMgr->destroySceneNode(particleNode);
  }
}