#ifndef __Penguin_h_
#define __Penguin_h_

#include <Ogre.h>
#include "GraphicsBody.h"

class Penguin : public GraphicsBody {
  public:
    Penguin(Ogre::SceneManager* sceneMgr, std::string name);
    virtual ~Penguin(void);
  private:
    Ogre::SceneNode* cameraNode;
};

#endif // #ifndef __Penguin_h_