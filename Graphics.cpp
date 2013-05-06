#include "Graphics.h"

Graphics::Graphics(Ogre::SceneManager* mSceneMgr) {
  sceneMgr = mSceneMgr;
  jumping = false;
  if(SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO) < 0){
   std::cout << "Unable to init SDL: " << SDL_GetError() << std::endl;
  }     
  soundMgr = SoundManager::getInstance();
}

Graphics::~Graphics(void) {
}

void Graphics::loadSounds(void) {
  golfPutt = new Sound("media/sounds/golf_putt.wav");
  wallHit = new Sound("media/sounds/golf_hit_metal.wav");
  inTheHole = new Sound("media/sounds/ball_in_hole.wav");
}

/** num:
* 0 = golfPutt
* 1 = wallHit
* 2 = inTheHole
*/
void Graphics::playSound(int num) {
  if (num == 0) {
    soundMgr->playSound(golfPutt);
  } else if (num == 1) {
    soundMgr->playSound(wallHit);
  } else if (num == 2) {
    soundMgr->playSound(inTheHole);
  }
}

void Graphics::setObjectPosition(std::string name, Ogre::Real x, Ogre::Real y, Ogre::Real z) {
  sceneMgr->getSceneNode(name)->setPosition(x, y, z);
}

void Graphics::setObjectOrientation(std::string name, Ogre::Real w, Ogre::Real x, Ogre::Real y, Ogre::Real z) {
  sceneMgr->getSceneNode(name)->setOrientation(w, x, y, z);
}

/** type:
* 0 = penguin
* 1 = wall
* 2 = killbox
* 3 = goal
*/
void Graphics::addGameObject(int type, std::string name, Ogre::Real x, Ogre::Real y, Ogre::Real z, Ogre::Real angle, Ogre::Real l, Ogre::Real h, Ogre::Real w) {
  GraphicsBody* obj;
  if (type == 0) {
    obj = new Penguin(sceneMgr, name);
  } else if (type == 1) {
    obj = new Wall(sceneMgr, name, x, y, z, Ogre::Radian(angle), l, h, w);
  } else if (type == 2) {
    obj = new KillBox(sceneMgr, name, x, y, z, Ogre::Radian(angle), l, h, w);
  } else if (type == 3) {
    obj = new Goal(sceneMgr, name, x, y, z, Ogre::Radian(angle));
  }
  gameObjects.push_back(obj);
}

void Graphics::removeObject(int pos) {
  GraphicsBody* obj = gameObjects.at(pos);
  gameObjects.erase(gameObjects.begin() + pos);
  delete obj;
}

void Graphics::setJumping(bool jump) {
 jumping = jump; 
}

bool Graphics::getJumping() {
  return jumping;
}
