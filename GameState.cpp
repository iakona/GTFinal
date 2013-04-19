#include "GameState.h"
 
using namespace Ogre;

CEGUI::MouseButton convertButton2(OIS::MouseButtonID buttonID) {
  switch (buttonID) {
    case OIS::MB_Left:
      return CEGUI::LeftButton;
    case OIS::MB_Right:
      return CEGUI::RightButton;
    case OIS::MB_Middle:
      return CEGUI::MiddleButton;

    default:
      return CEGUI::LeftButton;
  }
}

GameState::GameState() {
  m_bQuit     = false;
  m_FrameEvent  = Ogre::FrameEvent();
  faceRight     = true;
}
 
void GameState::enter() {
  OgreFramework::getSingletonPtr()->m_pLog->logMessage("Entering GameState...");
 
  m_pSceneMgr = OgreFramework::getSingletonPtr()->m_pRoot->createSceneManager(ST_GENERIC, "GameSceneMgr");
  m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.3f, 0.6f, 0.8f));
  m_pSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
 
  m_pCamera = m_pSceneMgr->createCamera("GameCam");
  m_pCamera->setPosition(Vector3(0, 15, 300));
  m_pCamera->lookAt(Vector3(0, 15, 0));
  m_pCamera->setNearClipDistance(1);
 
  m_pCamera->setAspectRatio(Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualWidth()) /
    Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualHeight()));

  OgreFramework::getSingletonPtr()->m_pViewport->setCamera(m_pCamera);

  createScene();
}

void GameState::createScene() {
  // game objects for demo
  Ogre::Entity* entPenguin = m_pSceneMgr->createEntity("Penguin", "penguin.mesh");
    entPenguin->setCastShadows(true);
  PenguinNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("PenguinNode", Ogre::Vector3(0,30,0));
  PenguinNode->attachObject(entPenguin);
  PenguinNode->yaw( Ogre::Degree( 90 ) );
  faceRight = true;

  Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
  Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
  plane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

  Ogre::Entity* entGround = m_pSceneMgr->createEntity("Ground", "ground");
  m_pSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);
  entGround->setMaterialName("Examples/Frost");
  entGround->setCastShadows(false);

   CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
  CEGUI::Window *gameWindow = wmgr.createWindow("DefaultWindow", "CEGUI/GameGUI");
  // text for demo
  CEGUI::Window *demoText = wmgr.createWindow("TaharezLook/StaticText", "CEGUI/Underconstruction");
  demoText->setText("Hello player, this is just a demo of game concept. We'll add\nphysics and more features in the coming weeks.\nEnjoy the demo!\n \nControls:\n      A or left arrow to move left\n      D or right arrow to move right\n \nPress esc, to go back to title");
  demoText->setSize(CEGUI::UVector2(CEGUI::UDim(0.5, 0), CEGUI::UDim(0.25, 0)));
  demoText->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0), CEGUI::UDim(0.0, 0)));
  gameWindow->addChildWindow(demoText);
  CEGUI::System::getSingleton().setGUISheet(gameWindow);
}
 
void GameState::exit() {
  OgreFramework::getSingletonPtr()->m_pLog->logMessage("Leaving GameState...");
 
  m_pSceneMgr->destroyCamera(m_pCamera);
  if(m_pSceneMgr)
    OgreFramework::getSingletonPtr()->m_pRoot->destroySceneManager(m_pSceneMgr);
 
  /*OgreFramework::getSingletonPtr()->m_pTrayMgr->clearAllTrays();
  OgreFramework::getSingletonPtr()->m_pTrayMgr->destroyAllWidgets();
  OgreFramework::getSingletonPtr()->m_pTrayMgr->setListener(0);*/
}

bool GameState::keyPressed(const OIS::KeyEvent &keyEventRef) {
  if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_ESCAPE))
  {
    CEGUI::WindowManager::getSingleton().destroyWindow( "CEGUI/GameGUI" );
    popAllAndPushAppState(findByName("MenuState"));
    return true;
  }

  OgreFramework::getSingletonPtr()->keyPressed(keyEventRef);
  CEGUI::System &sys = CEGUI::System::getSingleton();
  sys.injectKeyDown(keyEventRef.key);
  sys.injectChar(keyEventRef.text);
  return true;
}
 
bool GameState::keyReleased(const OIS::KeyEvent &keyEventRef) {
  OgreFramework::getSingletonPtr()->keyReleased(keyEventRef);
  //CEGUI::System::getSingleton().injectKeyUp(keyEventRef.key);
  return true;
}
 
bool GameState::mouseMoved(const OIS::MouseEvent &evt) {
  CEGUI::System &sys = CEGUI::System::getSingleton();
  sys.injectMouseMove(evt.state.X.rel, evt.state.Y.rel);
  // Scroll wheel.
  if (evt.state.Z.rel)
    sys.injectMouseWheelChange(evt.state.Z.rel / 120.0f);
  // if(OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseMove(evt)) return true;
  return true;
}
 
bool GameState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
  CEGUI::System::getSingleton().injectMouseButtonDown(convertButton2(id));
  // if(OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseDown(evt, id)) return true;
  return true;
}
 
bool GameState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
  CEGUI::System::getSingleton().injectMouseButtonUp(convertButton2(id));
  // if(OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseUp(evt, id)) return true;
  return true;
}

void GameState::update(double timeSinceLastFrame) {
  m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
  CEGUI::System::getSingleton().injectTimePulse(m_FrameEvent.timeSinceLastFrame);
  // OgreFramework::getSingletonPtr()->m_pTrayMgr->frameRenderingQueued(m_FrameEvent);
  getInput();
  if(m_bQuit == true) {
    shutdown();
    return;
  }
}

void GameState::getInput() {
  if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_A)||OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_LEFT)) {
    if(faceRight) {
      PenguinNode->yaw( Ogre::Degree( 180 ) );
      faceRight = false;
    }
    PenguinNode->translate(-5.0f,0.0f,0.0f);
  }

  if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_D)||OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_RIGHT)) {
    if(!faceRight) {
      PenguinNode->yaw( Ogre::Degree( 180 ) );
      faceRight = true;
    }
    PenguinNode->translate(5.0f,0.0f,0.0f);
  }
}
