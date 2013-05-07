#ifndef __Wall_h_
#define __Wall_h_

#include <Ogre.h>
#include "GraphicsBody.h"

class Wall : public GraphicsBody {
  public:
    Wall(Ogre::SceneManager* sceneMgr, std::string name, Ogre::Real x, Ogre::Real y, Ogre::Real z, Ogre::Radian angle);
    Wall(Ogre::SceneManager* sceneMgr, std::string name, Ogre::Real x, Ogre::Real y, Ogre::Real z, Ogre::Radian angle, Ogre::Real l, Ogre::Real h, Ogre::Real w, int property = 0);
    virtual ~Wall(void);

  private:
    Ogre::SceneNode* particleNode;
    Ogre::ParticleSystem* particle;
};

#endif // #ifndef __Wall_h_