#ifndef __Graphics_h_
#define __Graphics_h_

#include "GraphicsBody.h"
#include "Physics.h"
#include "SoundManager.h"

class Physics;

class Graphics {
  public:
    Graphics(Ogre::SceneManager* mSceneMgr);
    virtual ~Graphics(void);
    void loadSounds();
    void playSound(int num);
    void setPhysics(Physics* phys) { physics = phys; }
    void setObjectPosition(std::string name, Ogre::Real x, Ogre::Real y, Ogre::Real z);
    void setObjectOrientation(std::string name, Ogre::Real w, Ogre::Real x, Ogre::Real y, Ogre::Real z);
    void addGameObject(int type, std::string name, Ogre::Real x, Ogre::Real y, Ogre::Real z, Ogre::Real angle, Ogre::Real l, Ogre::Real w, Ogre::Real h);
    void removeObject(int pos);
    void setJumping(bool jump);
    bool getJumping();

  private:
    Ogre::SceneManager *sceneMgr;
    Physics* physics;
    std::vector<GraphicsBody*> gameObjects;
    bool jumping;
    SoundManager* soundMgr;
    Sound* golfPutt;
    Sound* wallHit;
    Sound* inTheHole;
};

#endif // #ifndef __Graphics_h_
