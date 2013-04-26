#include "MotionState.h"

MotionState::MotionState(const btTransform &initialpos, Graphics* graphic, std::string name) {
  graphics = graphic;
  mPos1 = initialpos;
  nodeName = name;
  prev = 0;
  jumping = false;
}

MotionState::~MotionState() {
}

void MotionState::getWorldTransform(btTransform &worldTrans) const {
  worldTrans = mPos1;
}

void MotionState::setWorldTransform(const btTransform &worldTrans) {
  //std::cout << "update" << std::endl;
  btVector3 pos = worldTrans.getOrigin();
  graphics->setObjectPosition(nodeName, pos.x(), pos.y(), pos.z());
  if (graphics->getJumping() && prev - pos.y() < .01 && prev - pos.y() > -.01)
    graphics->setJumping(false);
  prev = pos.y();
  //std::cout << pos.x() << " " << pos.y() << " " << pos.z() << std::endl;
  btQuaternion rot = worldTrans.getRotation();
  graphics->setObjectOrientation(nodeName, rot.w(), rot.x(), rot.y(), rot.z());
}