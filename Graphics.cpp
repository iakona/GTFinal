#include "Graphics.h"

Graphics::Graphics(Ogre::SceneManager* mSceneMgr) {
  sceneMgr = mSceneMgr;
}

Graphics::~Graphics(void) {
}

void Graphics::setObjectPosition(std::string name, Ogre::Real x, Ogre::Real y, Ogre::Real z) {
  sceneMgr->getSceneNode(name)->getParentSceneNode()->setPosition(x, y, z);
}

void Graphics::setObjectOrientation(std::string name, Ogre::Real w, Ogre::Real x, Ogre::Real y, Ogre::Real z) {
  sceneMgr->getSceneNode(name)->setOrientation(w, x, y, z);
}