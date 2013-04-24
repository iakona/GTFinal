#ifndef __Physics_h_
#define __Physics_h_

#include "PhysicsBody.h"
#include "Penguin.h"
#include "Terrain.h"
#include "Wall.h"

class Graphics;
class PhysicsBody;

class Physics {
  public:
    Physics(Graphics*);
    virtual ~Physics(void);
    void step(void);
    void initialize(void);
    void addGameObject(PhysicsBody* obj, int type, std::string name, btScalar x, btScalar y, btScalar z, btScalar angle, btScalar l, btScalar h, btScalar w);
    void addPenguin(std::string name);
    void addGround(std::string name, btScalar x, btScalar y, btScalar z, btScalar l, btScalar h, btScalar w);
    void addWall(std::string name, btScalar x, btScalar y, btScalar z, btScalar angle, btScalar l, btScalar h, btScalar w);
    void translate(int index, btScalar x, btScalar y, btScalar z);
    void rotate(int index, btScalar angle);
    void stop(int index);

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