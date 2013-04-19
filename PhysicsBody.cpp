#include "PhysicsBody.h"

PhysicsBody::PhysicsBody(btRigidBody* rigidBody, MotionState* motionState) {
  body = rigidBody;
  ms = motionState;
}

PhysicsBody::~PhysicsBody(void) {
  delete body;
  delete ms;
}

btRigidBody* PhysicsBody::getBody() {
  return body;
}

btRigidBody* PhysicsBody::setBody(btRigidBody* rigidBody) {
  body = rigidBody;
}

btRigidBody* PhysicsBody::setMotion(MotionState* motionState) {
  ms = motionState;
}