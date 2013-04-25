#include "Physics.h"

Physics::Physics(Graphics* graphic) {
  collisionConfiguration = new btDefaultCollisionConfiguration();
  dispatcher = new btCollisionDispatcher(collisionConfiguration);
  overlappingPairCache = new btDbvtBroadphase();
  solver = new btSequentialImpulseConstraintSolver();
  dynamicWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
  dynamicWorld->setGravity(btVector3(0,-1,0));
  dynamicWorld->getSolverInfo().m_splitImpulse = true;
  graphics = graphic;
}

Physics::~Physics(void) {
  delete dynamicWorld;
}

void Physics::step(void) {
  dynamicWorld->stepSimulation(1.f/60.f);
}

void Physics::initialize(void) {
  addPenguin("penguin");
  addGround("ground", 0, 0, 0, 1500, 0, 1500);
  //addWall("wall0", 0, 100, 250, 0, 100, 100, 100);
}

void Physics::addGameObject(PhysicsBody* obj, int type, std::string name, btScalar x, btScalar y, btScalar z, btScalar angle, btScalar l, btScalar h, btScalar w) {
  gameBodies.push_back(obj);
  dynamicWorld->addRigidBody(obj->getBody());
  //obj->getBody()->setUserPointer(gameBodies[gameBodies.size()-1]);
  graphics->addGameObject(type, name, x, y, z, angle, l, h, w);
}

void Physics::addPenguin(std::string name) {
  MotionState* motionState = new MotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,10,0)), graphics, name);

//   btCollisionShape* shape = new btBoxShape(btVector3(61.7703 / 2, 47.0496 / 2, 48.3053 / 2));
  btCollisionShape* shape = new btBoxShape(btVector3(10, 10, 10));
  //btCollisionShape* shape = new btSphereShape(2);
  btScalar mass = 1;
  btVector3 inertia(0,0,0);
  shape->calculateLocalInertia(mass,inertia);
  btRigidBody::btRigidBodyConstructionInfo info(mass,motionState,shape,inertia);
  btRigidBody* body = new btRigidBody(info);

  body->setRestitution(.78);
  body->setFriction(1);
  body->setDamping(.4,.2);
//   body->setRestitution(0);
//   body->setFriction(0);
//   body->setDamping(0,0);
  body->setActivationState(DISABLE_DEACTIVATION);

  PhysicsBody* physicsBody = new PhysicsBody(body, motionState);
  addGameObject(physicsBody, 0, name, 0, 0, 0, 0, 0, 0, 0);
}

void Physics::addGround(std::string name, btScalar x, btScalar y, btScalar z, btScalar l, btScalar h, btScalar w) {
  btCollisionShape* shape = new btStaticPlaneShape(btVector3(0,1,0),1);

  btScalar mass(0.);
  btVector3 inertia(0,0,0);
  MotionState* motionState = new MotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)), graphics, name);
  btRigidBody::btRigidBodyConstructionInfo info(mass, motionState, shape, inertia);
  btRigidBody* body = new btRigidBody(info);

  body->setRestitution(.75);
  body->setFriction(.5);
  body->setDamping(.4,.2);
  //body->setRestitution(0);
  //body->setFriction(0);
  //body->setDamping(0,0);
  body->setActivationState(DISABLE_DEACTIVATION);

  PhysicsBody* physicsBody = new PhysicsBody(body, motionState);
  addGameObject(physicsBody, 1, name, x, y, z, 0, l, h, w);
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
  body->setLinearVelocity(btVector3(0,0,0));
  body->setFriction(1);
  body->setDamping(0,.2);
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
  btTransform tr;
  tr.setIdentity();
  btQuaternion quat;
  quat.setEuler(angle,0,0); //or quat.setEulerZYX depending on the ordering you want
  tr.setRotation(quat);
  btTransform transform = body->getWorldTransform();
  body->setWorldTransform(tr * transform);
}

void Physics::stop(int index) {
  //std::cout << "stopped" << std::endl;
  btRigidBody* body = gameBodies.at(index)->getBody();
  //body->setLinearVelocity(btVector3(0, 0, 0));
}