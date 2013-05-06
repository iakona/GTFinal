#include "Penguin.h"

Penguin::Penguin(Ogre::SceneManager* sceneMgr, std::string name) {
  Ogre::Entity* entPenguin = sceneMgr->createEntity(name, "penguin.mesh");
  entPenguin->setCastShadows(true);
  Ogre::SceneNode* penguinNode = sceneMgr->getRootSceneNode()->createChildSceneNode(name, Ogre::Vector3(0,30,0));
  penguinNode->attachObject(entPenguin);
  penguinNode->scale(60 / 61.7703, 50 / 47.0496, 50 / 48.3053);
  Ogre::Camera* cam = sceneMgr->getCamera("GameCam");
  cameraNode = penguinNode->createChildSceneNode("CameraNode");
  cameraNode->attachObject(cam);

  setNode(penguinNode);
}

Penguin::~Penguin(void) {
  delete cameraNode;
}
