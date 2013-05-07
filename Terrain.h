#ifndef __Terrain_h_
#define __Terrain_h_

#include <Ogre.h>
#include "GraphicsBody.h"

class Terrain : public GraphicsBody {
  public:
    Terrain(Ogre::SceneManager* sceneMgr, std::string name, Ogre::Real x, Ogre::Real y, Ogre::Real z, Ogre::Radian angle, Ogre::Real l, Ogre::Real h, Ogre::Real w);
    virtual ~Terrain(void);

  private:
    
};

#endif // #ifndef __Terrain_h_