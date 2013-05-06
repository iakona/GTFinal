#include "Physics.h"

btVector3 checkpoint;

#define BIT(x) (1<<(x))
enum collisiontypes {
    COL_NOTHING = 0, //<Collide with nothing
    COL_PENGUIN = BIT(0), //<Collide with penguins
    COL_WALL = BIT(1), //<Collide with walls
    COL_KILLBOX = BIT(2) //<Collide with killboxes
};

Physics::Physics(Graphics* graphic) {
  collisionConfiguration = new btDefaultCollisionConfiguration();
  dispatcher = new btCollisionDispatcher(collisionConfiguration);
  overlappingPairCache = new btDbvtBroadphase();
  solver = new btSequentialImpulseConstraintSolver();
  dynamicWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
  dynamicWorld->setGravity(btVector3(0,-300,0));
  dynamicWorld->getSolverInfo().m_splitImpulse = true;
  graphics = graphic;
}

Physics::~Physics(void) {
  delete dynamicWorld;
}

void Physics::step(void) {
  dynamicWorld->stepSimulation(1.f/60.f);
  int numManifolds = dynamicWorld->getDispatcher()->getNumManifolds();
  for (int i = 0; i < numManifolds; i++) {
    btPersistentManifold* contactManifold =  dynamicWorld->getDispatcher()->getManifoldByIndexInternal(i);
    btCollisionObject* obA = static_cast<btCollisionObject*>(contactManifold->getBody0());
    btCollisionObject* obB = static_cast<btCollisionObject*>(contactManifold->getBody1());
    btBroadphaseProxy* obA_proxy = obA->getBroadphaseHandle();
    btBroadphaseProxy* obB_proxy = obB->getBroadphaseHandle();
    if (obA_proxy->m_collisionFilterGroup & obB_proxy->m_collisionFilterMask) {
      std::cout << obA_proxy->m_collisionFilterGroup << " " << obB_proxy->m_collisionFilterGroup << std::endl;
      if (obA_proxy->m_collisionFilterGroup == COL_PENGUIN && obB_proxy->m_collisionFilterGroup == COL_KILLBOX) {
        PhysicsBody* object = reinterpret_cast<PhysicsBody*>(obA->getUserPointer());
        resetObject(object);
      }
    }
//     if (obB->getCollisionFlags() & (btCollisionObject::CF_NO_CONTACT_RESPONSE | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK)) {
//       PhysicsBody* object = reinterpret_cast<PhysicsBody*>(obA->getUserPointer());
//       resetObject(object);
//     }
  }
}

void Physics::resetObject(PhysicsBody* object) {
  btRigidBody* body = object->getBody();
  body->setLinearVelocity(btVector3(0,0,0));
  body->setAngularVelocity(btVector3(0,0,0));
  btVector3 translate = body->getCenterOfMassPosition();
  body->translate(-translate);
  body->translate(checkpoint);
}

void Physics::initialize(void) {
  addPenguin("penguin");
  addKillBox("killBox0", 0, 0, 0, 0, 4000, 0, 4000);
  addWall("wall0", 0, 440, 0, 0, 80, 40, 120);   // start
  addWall("wall1", 0, 520, 160, 0, 80, 40, 40);  // stairs 1
  addWall("wall2", 0, 600, 240, 0, 80, 40, 40);
  addWall("wall3", 0, 680, 360, 0, 80, 40, 80);
  addWall("wall4", 0, 680, 1080, 0, 240, 40, 240);  // platform 1
  addWall("wall5", -520, 600, 1160, 0, 40, 40, 80);  // stairs right of platform, this is a small jumping puzzle leading to the first room
  addWall("wall6", -760, 400, 1640, 0, 40, 80, 40);
  addWall("wall7", -1080, 480, 2000, 0, 80, 20, 80);
  addWall("wall8", -920, 560, 2160, 0, 20, 20, 120);
  addWall("wall9", -800, 640, 2280, 0, 40, 30, 40);
  addWall("wall10", -880, 720, 1880, 0, 40, 20, 80);
  addWall("wall11", -880, 780, 1760, 0, 40, 40, 40);
  addWall("wall12", -720, 880, 2200, 45, 80, 20, 320); // end of jump puzzle 1
  addWall("wall12_2", -230, 940, 2200, 0, 15, 10, 40);
  addWall("wall12_3", -170, 1020, 2140, 0, 15, 10, 40);
  addWall("wall12_4", -110, 1090, 2080, 0, 15, 10, 40);
  addWall("wall12_5", -50, 1160, 2210, 0, 15, 10, 40);
  addWall("wall12_6", -10, 900, 1880, 0, 15, 10, 40);
  addWall("wall12_7", -40, 750, 1480, 0, 50, 5, 50);
  addWall("wall12_8", 30, 1250, 2280, 0, 32, 20, 25);
  addWall("wall12_9", 60, 1450, 2500, 0, 80, 20, 50);
  addWall("wall13", -160, 715, 3240, 0, 120, 10, 120); // platform on other side of wall
  addWall("wall14", 96, 390, 2690, 0, 804, 400, 50);   // Big Wall Bottom
  addWall("wall15", 100, 1190, 2680, 0, 800, 400, 40); // Big Wall Top
  addWall("wall16", -60, 795, 3640, 0, 100, 10, 100); // End?

}

void Physics::addGameObject(PhysicsBody* obj, int type, std::string name, btScalar x, btScalar y, btScalar z, btScalar angle, btScalar l, btScalar h, btScalar w) {
  gameBodies.push_back(obj);
  int penguinCollidesWith = COL_WALL | COL_KILLBOX;
  int wallCollidesWith = COL_PENGUIN;
  int killboxCollidesWith = COL_PENGUIN;
  if (type == 0)
    dynamicWorld->addRigidBody(obj->getBody(), COL_PENGUIN, penguinCollidesWith);
  else if (type == 1)
    dynamicWorld->addRigidBody(obj->getBody(), COL_WALL, wallCollidesWith);
  else if (type == 2)
    dynamicWorld->addRigidBody(obj->getBody(), COL_KILLBOX, killboxCollidesWith);
  obj->getBody()->setUserPointer(gameBodies[gameBodies.size()-1]);
  graphics->addGameObject(type, name, x, y, z, angle, l, h, w);
}

void Physics::addPenguin(std::string name) {
  MotionState* motionState = new MotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,505,0)), graphics, name);
  //MotionState* motionState = new MotionState(btTransform(btQuaternion(0,0,0,1),btVector3(-720,945,2200)), graphics, name);
//   btCollisionShape* shape = new btBoxShape(btVector3(61.7703 / 2, 47.0496 / 2, 48.3053 / 2));
  btCollisionShape* shape = new btBoxShape(btVector3(30, 25, 25));
  //btCollisionShape* shape = new btSphereShape(2);
  btScalar mass = 1;
  btVector3 inertia(0,0,0);
  shape->calculateLocalInertia(mass,inertia);
  btRigidBody::btRigidBodyConstructionInfo info(mass,motionState,shape,inertia);
  btRigidBody* body = new btRigidBody(info);

  //body->setRestitution(.78);
  body->setFriction(1);
  body->setDamping(.4,.2);
  body->setRestitution(0);
//   body->setFriction(0);
//   body->setDamping(0,0);
  body->setActivationState(DISABLE_DEACTIVATION);
  body->setAngularFactor(btVector3(0, 1, 0));

  PhysicsBody* physicsBody = new PhysicsBody(body, motionState);
  addGameObject(physicsBody, 0, name, 0, 0, 0, 0, 0, 0, 0);
  checkpoint = btVector3(0, 505, 0);
}

void Physics::addWall(std::string name, btScalar x, btScalar y, btScalar z, btScalar angle, btScalar l, btScalar h, btScalar w) {
  btCollisionShape* shape = new btBoxShape(btVector3(l,h,w));

  btScalar mass = 0;
  btVector3 intertia(0,0,0);
  shape->calculateLocalInertia(mass,intertia);

  MotionState* motionState = new MotionState(btTransform(btQuaternion(angle, 0, 0),btVector3(x, y, z)), graphics, name);

  btRigidBody::btRigidBodyConstructionInfo info(mass,motionState,shape,intertia);
  btRigidBody* body = new btRigidBody(info);
  body->setRestitution(.85);
  //body->setRestitution(0);
  body->setLinearVelocity(btVector3(0,0,0));
  body->setFriction(1);
  body->setDamping(0,.2);
  body->setActivationState(DISABLE_DEACTIVATION);

  PhysicsBody* physicsBody = new PhysicsBody(body, motionState);
  addGameObject(physicsBody, 1, name, x, y, z, angle, l, h, w);
}

void Physics::addKillBox(std::string name, btScalar x, btScalar y, btScalar z, btScalar angle, btScalar l, btScalar h, btScalar w) {
  btCollisionShape* shape = new btBoxShape(btVector3(l,h,w));

  btScalar mass = 0;
  btVector3 intertia(0,0,0);
  shape->calculateLocalInertia(mass,intertia);

  MotionState* motionState = new MotionState(btTransform(btQuaternion(angle, 0, 0),btVector3(x, y, z)), graphics, name);

  btRigidBody::btRigidBodyConstructionInfo info(mass,motionState,shape,intertia);
  btRigidBody* body = new btRigidBody(info);
  //body->setCollisionFlags
  body->setActivationState(DISABLE_DEACTIVATION);

  PhysicsBody* physicsBody = new PhysicsBody(body, motionState);
  addGameObject(physicsBody, 2, name, x, y, z, angle, l, h, w);
}

void Physics::translate(int index, btScalar x, btScalar y, btScalar z) {
  //std::cout << "moving" << std::endl;
  btRigidBody* body = gameBodies.at(index)->getBody();
  body->translate(btVector3(x, y, z));
  //body->translate(btVector3(1000, 0, 0));
  //body->setLinearVelocity(btVector3(x, y, z));
  //body->applyCentralForce(btVector3(x, y, z));
}

void Physics::rotate(int index, btScalar angle) {
  btRigidBody* body = gameBodies.at(index)->getBody();
  /*btTransform transform = body->getWorldTransform();
  btQuaternion rotate = transform.getRotation();
  btVector3 axis = rotate.getAxis();
  axis.setX(0);
  axis.setY(1);
  axis.setZ(0);
  std::cout << rotate.getAngle() << std::endl;
  rotate.setRotation(axis, rotate.getAngle() + angle);
  transform.setRotation(rotate);
  body->setWorldTransform(transform);*/
  //btTransform tr;
  //tr.setIdentity();
  btQuaternion quat;
  quat.setEuler(angle,0,0); //or quat.setEulerZYX depending on the ordering you want
  //tr.setRotation(quat);
  btTransform transform = body->getCenterOfMassTransform();
  transform.setRotation(transform.getRotation() * quat);
  //tr.setBasis(transform.getBasis());
  //tr.setOrigin(transform.getOrigin());
  //transform.setRotation(transform.getRotation() + quat);
  //body->setCenterOfMassTransform(tr * transform);
  body->setCenterOfMassTransform(transform);
}

void Physics::applyForce(int index, btScalar x, btScalar y, btScalar z) {
  btRigidBody* body = gameBodies.at(index)->getBody();
  body->applyCentralForce(btVector3(x, y, z));
}

void Physics::stop(int index) {
  //std::cout << "stopped" << std::endl;
  //btRigidBody* body = gameBodies.at(index)->getBody();
  //body->setLinearVelocity(btVector3(0, 0, 0));
}
