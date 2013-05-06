#ifndef __AnimatedGraphicsBody_h_
#define __AnimatedGraphicsBody_h_

#include <Ogre.h>
#include "GraphicsBody.h"

class AnimatedGraphicsBody : public GraphicsBody {
  public:
    void animate() { mAnimationState->addTime(1.f/60.f); }
  protected:
    Ogre::AnimationState *mAnimationState;

};

#endif // #ifndef __AnimatedGraphicsBody_h_