#include "MotionState.h"

MotionState::MotionState(const btTransform &initialpos, Graphics* graphic, std::string name) {
  graphics = graphic;
  mPos1 = initialpos;
  nodeName = name;
}

MotionState::~MotionState() {
}

void MotionState::getWorldTransform(btTransform &worldTrans) const {
  worldTrans = mPos1;
}

void MotionState::setWorldTransform(const btTransform &worldTrans) {
  btVector3 pos = worldTrans.getOrigin();
  graphics->setObjectPosition(nodeName, pos.x(), pos.y(), pos.z());
  btQuaternion rot = worldTrans.getRotation();
  graphics->setObjectOrientation(nodeName, rot.w(), rot.x(), rot.y(), rot.z());
}