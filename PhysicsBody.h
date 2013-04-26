#ifndef __PhysicsBody_h_
#define __PhysicsBody_h_

#include "MotionState.h"

class MotionState;

class PhysicsBody {
  public:
    PhysicsBody(btRigidBody* rigidBody, btMotionState* ms);
    virtual ~PhysicsBody(void);
    btRigidBody* getBody();
    btRigidBody* setBody(btRigidBody* rigidBody);
    btRigidBody* setMotion(btMotionState* motionState);
    
  private:
    btRigidBody* body;
    btMotionState* ms;
};

#endif // #ifndef __PhysicsBody_h_