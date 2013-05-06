#ifndef __KillBox_h_
#define __KillBox_h_

#include <Ogre.h>
#include "GraphicsBody.h"

class KillBox : public GraphicsBody {
  public:
    KillBox(Ogre::SceneManager* sceneMgr, std::string name, Ogre::Real x, Ogre::Real y, Ogre::Real z, Ogre::Radian angle, Ogre::Real l, Ogre::Real h, Ogre::Real w);
    virtual ~KillBox(void);

  private:
    
};

#endif // #ifndef __KillBox_h_