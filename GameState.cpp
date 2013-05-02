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
  m_bQuit = false;
  m_FrameEvent = Ogre::FrameEvent();
}
 
void GameState::enter() {
  OgreFramework::getSingletonPtr()->m_pLog->logMessage("Entering GameState...");
 
  m_pSceneMgr = OgreFramework::getSingletonPtr()->m_pRoot->createSceneManager(ST_GENERIC, "GameSceneMgr");
  m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.4f, 0.4f, 0.4f));
  m_pSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
 
  m_pCamera = m_pSceneMgr->createCamera("GameCam");
  m_pCamera->setPosition(Vector3(0, 15, -300));
  m_pCamera->lookAt(Vector3(0, 15, 0));
  m_pCamera->setNearClipDistance(1);
 
  m_pCamera->setAspectRatio(Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualWidth()) / Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualHeight()));

  limit = 0.0;

  OgreFramework::getSingletonPtr()->m_pViewport->setCamera(m_pCamera);

  // create an imageset for the face portrait
  CEGUI::ImagesetManager *im = &(CEGUI::ImagesetManager::getSingleton());
  CEGUI::NamedXMLResourceManager<CEGUI::Imageset, CEGUI::Imageset_xmlHandler> *castedIm = NULL;
  castedIm = (CEGUI::NamedXMLResourceManager<CEGUI::Imageset, CEGUI::Imageset_xmlHandler>*) im;
  castedIm->create( "Face.imageset" );

  // hide cursor
  CEGUI::MouseCursor::getSingleton().hide();

  createScene();
}

void GameState::createScene() {
  graphics = new Graphics(m_pSceneMgr);
  physics = new Physics(graphics);
  graphics->setPhysics(physics);
  physics->initialize();
  PenguinNode = m_pSceneMgr->getSceneNode("penguin");

  m_pSceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8);

  CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
  CEGUI::Window *gameWindow = wmgr.createWindow("DefaultWindow", "CEGUI/GameGUI");

  // penguin portrait
  CEGUI::Window *face = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticImage", "FacePng");
  face->setSize(CEGUI::UVector2(CEGUI::UDim(0.1, 0), CEGUI::UDim(0.13, 0)));
  face->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0), CEGUI::UDim(0, 0)));
  face->setProperty("Image","set:Face image:full_image");
  face->setProperty("FrameEnabled", "False");
  face->setProperty("BackgroundEnabled", "False");
  gameWindow->addChildWindow(face);

  CEGUI::System::getSingleton().setGUISheet(gameWindow);
}
 
void GameState::exit() {
  OgreFramework::getSingletonPtr()->m_pLog->logMessage("Leaving GameState...");
 
  m_pSceneMgr->destroyCamera(m_pCamera);
  if (m_pSceneMgr)
    OgreFramework::getSingletonPtr()->m_pRoot->destroySceneManager(m_pSceneMgr);
 
  /*OgreFramework::getSingletonPtr()->m_pTrayMgr->clearAllTrays();
  OgreFramework::getSingletonPtr()->m_pTrayMgr->destroyAllWidgets();
  OgreFramework::getSingletonPtr()->m_pTrayMgr->setListener(0);*/
}

bool GameState::keyPressed(const OIS::KeyEvent &keyEventRef) {
  if (OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_ESCAPE)) {
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

  physics->rotate(0, Ogre::Degree(-evt.state.X.rel * 0.1).valueRadians());
  
  if((evt.state.Y.rel > 0 && limit <= 180) || (evt.state.Y.rel < 0 && limit >= -30)){
    limit += evt.state.Y.rel;
      m_pCamera->move(Ogre::Vector3(0.0,evt.state.Y.rel,0.0));
      m_pCamera->pitch(Ogre::Degree(-evt.state.Y.rel*0.1));
  }
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
  physics->step();
  if (m_bQuit == true) {
    shutdown();
    return;
  }
}

void GameState::getInput() {
  OIS::Keyboard* keyboard = OgreFramework::getSingletonPtr()->m_pKeyboard;
  //bool moving = false;
  if (keyboard->isKeyDown(OIS::KC_Q)) {
    //PenguinNode->yaw(Ogre::Degree(5));
    physics->rotate(0, Ogre::Degree(3).valueRadians());
  }
  if (keyboard->isKeyDown(OIS::KC_E)) {
    //PenguinNode->yaw(Ogre::Degree(-5));
    physics->rotate(0, Ogre::Degree(-3).valueRadians());
  }
  Ogre::Vector3 dir = PenguinNode->getOrientation() * Ogre::Vector3::UNIT_Z;
  if (keyboard->isKeyDown(OIS::KC_W) || keyboard->isKeyDown(OIS::KC_UP)) {
    //PenguinNode->translate(5.0f * dir[0], 0.0f, 5.0f * dir[2]);
    physics->translate(0, 5.0f * dir[0], 0.0f, 5.0f * dir[2]);
    //moving = true;
  }
  if (keyboard->isKeyDown(OIS::KC_S) || keyboard->isKeyDown(OIS::KC_DOWN)) {
    //PenguinNode->translate(-5.0f * dir[0], 0.0f, -5.0f * dir[2]);
    physics->translate(0, -5.0f * dir[0], 0.0f, -5.0f * dir[2]);
    //moving = true;
  }
  if (keyboard->isKeyDown(OIS::KC_A) || keyboard->isKeyDown(OIS::KC_LEFT)) {
    //PenguinNode->translate(5.0f * dir[2], 0.0f, -5.0f * dir[0]);
    physics->translate(0, 5.0f * dir[2], 0.0f, -5.0f * dir[0]);
    //moving = true;
  }
  if (keyboard->isKeyDown(OIS::KC_D) || keyboard->isKeyDown(OIS::KC_RIGHT)) {
    //PenguinNode->translate(-5.0f * dir[2], 0.0f, 5.0f * dir[0]);
    physics->translate(0, -5.0f * dir[2], 0.0f, 5.0f * dir[0]);
    //moving = true;
  }
  if (keyboard->isKeyDown(OIS::KC_SPACE)) {
    //std::cout << "jump" << std::endl;
    if(!graphics->getJumping()){
      physics->applyForce(0, 0, 14000, 0);
      graphics->setJumping(true);
    }
  }
  //if (!moving)
    //physics->stop(0);
}
