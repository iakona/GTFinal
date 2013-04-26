#ifndef __MotionState_h_
#define __MotionState_h_

#include <btBulletDynamicsCommon.h>
#include "Graphics.h"

class Graphics;

class MotionState : public btMotionState {
  public:
    MotionState(const btTransform &initialpos, Graphics* graphic, std::string name);
    virtual ~MotionState();
    virtual void getWorldTransform(btTransform &worldTrans) const;
    virtual void setWorldTransform(const btTransform &worldTrans);

  protected:
    btTransform mPos1;
    Graphics* graphics;
    std::string nodeName;
    btScalar prev;
    bool jumping;
};

#endif // #ifndef __MotionState_h_