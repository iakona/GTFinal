#include "Goal.h"

Goal::Goal(Ogre::SceneManager* sceneMgr, std::string name, Ogre::Real x, Ogre::Real y, Ogre::Real z, Ogre::Radian angle) {
  Ogre::Entity* entGoal = sceneMgr->createEntity(name, "geosphere8000.mesh");
  entGoal->setMaterialName("Examples/Aureola", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
  entGoal->setCastShadows(true);
  Ogre::SceneNode* goalNode = sceneMgr->getRootSceneNode()->createChildSceneNode(name, Ogre::Vector3(0,30,0));
  goalNode->attachObject(entGoal);
  goalNode->scale(0.25, 0.25, 0.25);
  goalNode->yaw(angle);
  goalNode->translate(x, y, z);
  setNode(goalNode);
  Ogre::ParticleSystem* aureola = sceneMgr->createParticleSystem(name + "particle", "Examples/GreenyNimbus");
  Ogre::SceneNode* aureolaNode = goalNode->createChildSceneNode(name + "particleNode");
  aureolaNode->attachObject(aureola);
  aureola->fastForward(30);
  aureolaNode->translate(0, -50, 0);
}

Goal::~Goal(void) {

}
