#ifndef __GraphicsObject_h_
#define __GraphicsObject_h_

#include <Ogre.h>

class GraphicsBody {
  public:
    GraphicsBody(Ogre::SceneNode* sceneNode);
    GraphicsBody();
    virtual ~GraphicsBody(void);
    Ogre::SceneNode* getSceneNode();
    void setNode(Ogre::SceneNode* sceneN);
    
  private:
    Ogre::SceneNode* sceneNode;
};

#endif // #ifndef __GraphicsObject_h_