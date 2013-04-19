#ifndef __Terrain_h_
#define __Terrain_h_

#include <Ogre.h>
#include "GraphicsBody.h"

class Terrain : public GraphicsBody {
  public:
    Terrain(Ogre::SceneManager* sceneMgr, std::string name);
    Terrain(Ogre::SceneManager* sceneMgr, std::string name, Ogre::Real x, Ogre::Real y, Ogre::Real z, Ogre::Real scalex, Ogre::Real scaley, Ogre::Real scalez);
    virtual ~Terrain(void);
};

#endif // #ifndef __Terrain_h_