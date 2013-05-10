#include "Penguin.h"

Penguin::Penguin(Ogre::SceneManager* sceneMgr, std::string name) {
  Ogre::Entity* entPenguin = sceneMgr->createEntity(name, "penguin.mesh");
  mAnimationState = entPenguin->getAnimationState("amuse");
  mAnimationState->setLoop(true);
  mAnimationState->setEnabled(true);
  entPenguin->setCastShadows(true);
  Ogre::SceneNode* penguinNode = sceneMgr->getRootSceneNode()->createChildSceneNode(name, Ogre::Vector3(0,30,0));
  penguinNode->attachObject(entPenguin);
  penguinNode->scale(60 / 63.0057, 50 / 47.99059, 50 / 49.27139);
  Ogre::Camera* cam = sceneMgr->getCamera("GameCam");
  cameraNode = penguinNode->createChildSceneNode("CameraNode");
  cameraNode->attachObject(cam);

  setNode(penguinNode);
}

Penguin::~Penguin(void) {
  delete cameraNode;
}
