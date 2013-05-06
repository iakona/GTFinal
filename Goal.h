#ifndef __Goal_h_
#define __Goal_h_

#include <Ogre.h>
#include "GraphicsBody.h"

class Goal : public GraphicsBody {
  public:
    Goal(Ogre::SceneManager* sceneMgr, std::string name, Ogre::Real x, Ogre::Real y, Ogre::Real z, Ogre::Radian angle);
    virtual ~Goal(void);
  private:

};

#endif // #ifndef __Goal_h_
