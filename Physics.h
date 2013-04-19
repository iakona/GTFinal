#ifndef __Physics_h_
#define __Physics_h_

#include "PhysicsBody.h"

class Graphics;
class PhysicsBody;

class Physics {
  public:
    Physics(Graphics*);
    virtual ~Physics(void);
    void step(void);
    void initialize(void);

  private:
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btBroadphaseInterface* overlappingPairCache;
    btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld* dynamicWorld;
    btAlignedObjectArray<PhysicsBody*> gameBodies;
    Graphics* graphics;
};

#endif // #ifndef __Physics_h_