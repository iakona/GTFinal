#ifndef __Physics_h_
#define __Physics_h_

#include "PhysicsBody.h"
#include "Penguin.h"
#include "KillBox.h"
#include "Wall.h"
#include "Goal.h"
#include "Terrain.h"

class Graphics;
class PhysicsBody;

class Physics {
  public:
    Physics(Graphics*);
    virtual ~Physics(void);
    void step(void);
    void resetObject(PhysicsBody* object);
    void initialize(void);
    void nextStage(void);
    void addStage0(void);
    void addStage1(void);
    void addStage2(void);
    void movePenguin(btVector3 location);
    void penguinOutOfHealth(void);
    void addGameObject(PhysicsBody* obj, int type, std::string name, btScalar x, btScalar y, btScalar z, btScalar angle, btScalar l, btScalar h, btScalar w, int property = 0);
    void addPenguin(std::string name);
    void addWall(std::string name, btScalar x, btScalar y, btScalar z, btScalar angle, btScalar l, btScalar h, btScalar w, int property = 0);
    void addKillBox(std::string name, btScalar x, btScalar y, btScalar z, btScalar angle, btScalar l, btScalar h, btScalar w);
    void addGoal(std::string name, btScalar x, btScalar y, btScalar z, btScalar angle);
    void addGround(std::string name, btScalar x, btScalar y, btScalar z, btScalar angle, btScalar l, btScalar h, btScalar w, int property = 0);
    void removeStage(void);
    void translate(int index, btScalar x, btScalar y, btScalar z);
    void rotate(int index, btScalar angle);
    void applyForce(int index, btScalar x, btScalar y, btScalar z);
    int getLives() { return lives; };
    bool gameOver();

  private:
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btBroadphaseInterface* overlappingPairCache;
    btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld* dynamicWorld;
    btAlignedObjectArray<PhysicsBody*> gameBodies;
    Graphics* graphics;
    int stageNumber;
    int lives;
};

#endif // #ifndef __Physics_h_
