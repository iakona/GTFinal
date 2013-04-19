#include "GraphicsBody.h"

GraphicsBody::GraphicsBody(Ogre::SceneNode* sceneN) {
  sceneNode = sceneN;
}

GraphicsBody::GraphicsBody() {
}

GraphicsBody::~GraphicsBody(void) {
  Ogre::SceneManager* sceneMgr = sceneNode->getCreator();
  sceneMgr->destroyEntity(sceneNode->getName());
  sceneMgr->destroySceneNode(sceneNode);
}

Ogre::SceneNode* GraphicsBody::getSceneNode() {
  return sceneNode;
}

void GraphicsBody::setNode(Ogre::SceneNode* sceneN) {
  sceneNode = sceneN;
}