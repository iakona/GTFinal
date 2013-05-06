#ifndef __Penguin_h_
#define __Penguin_h_

#include <Ogre.h>
#include "AnimatedGraphicsBody.h"

class Penguin : public AnimatedGraphicsBody {
  public:
    Penguin(Ogre::SceneManager* sceneMgr, std::string name);
    virtual ~Penguin(void);
  private:
    Ogre::SceneNode* cameraNode;
};

#endif // #ifndef __Penguin_h_