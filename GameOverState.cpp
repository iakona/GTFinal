#include "GameOverState.h"
 
using namespace Ogre;

CEGUI::MouseButton convertButton4(OIS::MouseButtonID buttonID) {
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

GameOverState::GameOverState() {
  m_bQuit = false;
  m_FrameEvent = Ogre::FrameEvent();
}
 
void GameOverState::enter() {
  OgreFramework::getSingletonPtr()->m_pLog->logMessage("Entering InstructionState...");
 
  m_pSceneMgr = OgreFramework::getSingletonPtr()->m_pRoot->createSceneManager(ST_GENERIC, "InstructionSceneMgr");
  m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.7f, 0.7f, 0.7f));
 
  m_pCamera = m_pSceneMgr->createCamera("InstructCam");
  m_pCamera->setPosition(Vector3(0, 25, -50));
  m_pCamera->lookAt(Vector3(0, 0, 0));
  m_pCamera->setNearClipDistance(1);
 
  m_pCamera->setAspectRatio(Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualWidth()) / Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualHeight()));
 
  OgreFramework::getSingletonPtr()->m_pViewport->setCamera(m_pCamera);

  // create an imageset for gameover
  CEGUI::ImagesetManager *im = &(CEGUI::ImagesetManager::getSingleton());
  CEGUI::NamedXMLResourceManager<CEGUI::Imageset, CEGUI::Imageset_xmlHandler> *castedIm = NULL;
  castedIm = (CEGUI::NamedXMLResourceManager<CEGUI::Imageset, CEGUI::Imageset_xmlHandler>*) im;
  castedIm->create( "GameOver.imageset" );

  CEGUI::MouseCursor::getSingleton().show();

  createScene();
}

void GameOverState::createScene() {
  CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
  CEGUI::Window *window = wmgr.createWindow("DefaultWindow", "CEGUI/InstructionWindow");

  // Game Over image
  CEGUI::Window *si = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticImage", "GameOverPng");
  si->setSize(CEGUI::UVector2(CEGUI::UDim(0.8, 0), CEGUI::UDim(0.25, 0)));
  si->setPosition(CEGUI::UVector2(CEGUI::UDim(0.1, 0), CEGUI::UDim(0.35, 0)));
  si->setProperty("Image","set:GameOver image:full_image");
  si->setProperty("FrameEnabled", "False");
  si->setProperty("BackgroundEnabled", "False");
  window->addChildWindow(si);

  // back to title button
  CEGUI::Window *back_to_title = wmgr.createWindow("TaharezLook/Button", "CEGUI/backToTitleButton");
  back_to_title->setText("Back to Title");
  back_to_title->setSize(CEGUI::UVector2(CEGUI::UDim(0.3, 0), CEGUI::UDim(0.05, 0)));
  back_to_title->setPosition(CEGUI::UVector2(CEGUI::UDim(0.6, 0), CEGUI::UDim(0.9, 0)));
  window->addChildWindow(back_to_title);

  CEGUI::System::getSingleton().setGUISheet(window);

  // event calls
  back_to_title->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GameOverState::backToTitle, this));
}
 
void GameOverState::exit() {
  OgreFramework::getSingletonPtr()->m_pLog->logMessage("Leaving InstructionState...");
 
  m_pSceneMgr->destroyCamera(m_pCamera);
  if (m_pSceneMgr)
    OgreFramework::getSingletonPtr()->m_pRoot->destroySceneManager(m_pSceneMgr);
}

bool GameOverState::keyPressed(const OIS::KeyEvent &keyEventRef) {
  if (OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_ESCAPE)) {
    CEGUI::WindowManager::getSingleton().destroyWindow( "CEGUI/InstructionWindow" );
    popAllAndPushAppState(findByName("MenuState"));
    return true;
  }
 
  CEGUI::System &sys = CEGUI::System::getSingleton();
  sys.injectKeyDown(keyEventRef.key);
  sys.injectChar(keyEventRef.text);
  return true;
}
 
bool GameOverState::keyReleased(const OIS::KeyEvent &keyEventRef) {
  CEGUI::System::getSingleton().injectKeyUp(keyEventRef.key);
  return true;
}
 
bool GameOverState::mouseMoved(const OIS::MouseEvent &evt) {
  CEGUI::System &sys = CEGUI::System::getSingleton();
  sys.injectMouseMove(evt.state.X.rel, evt.state.Y.rel);
  // Scroll wheel.
  if (evt.state.Z.rel)
    sys.injectMouseWheelChange(evt.state.Z.rel / 120.0f);
  return true;
}
 
bool GameOverState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
  CEGUI::System::getSingleton().injectMouseButtonDown(convertButton4(id));
  return true;
}
 
bool GameOverState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
  CEGUI::System::getSingleton().injectMouseButtonUp(convertButton4(id));
  return true;
}

void GameOverState::update(double timeSinceLastFrame) {
  m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
  CEGUI::System::getSingleton().injectTimePulse(m_FrameEvent.timeSinceLastFrame);
}

bool GameOverState::backToTitle(const CEGUI::EventArgs &e) {
  CEGUI::WindowManager::getSingleton().destroyWindow( "CEGUI/InstructionWindow" );
  changeAppState(findByName("MenuState"));
}
