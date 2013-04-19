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

/** type:
* 0 = penguin
* 1 = ground
* 2 = wall
*/
void Graphics::addGameObject(int type, std::string name, Ogre::Real x, Ogre::Real y, Ogre::Real z, Ogre::Real angle, Ogre::Real l, Ogre::Real h, Ogre::Real w) {
  GraphicsBody* obj;
  if (type == 0) {
    obj = new Penguin(sceneMgr, name);
  } else if (type == 1) {
    obj = new Terrain(sceneMgr, name, x, y, z, l, h, w);
  } else if (type == 2) {
    obj = new Wall(sceneMgr, name, x, y, z, Ogre::Radian(angle), l, h, w);
  }
  gameObjects.push_back(obj);
}