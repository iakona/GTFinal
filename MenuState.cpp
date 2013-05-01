#include "MenuState.h"
 
using namespace Ogre;

CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID) {
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

MenuState::MenuState() {
  m_bQuit = false;
  m_FrameEvent = Ogre::FrameEvent();
  created = false;
}
 
void MenuState::enter() {
  OgreFramework::getSingletonPtr()->m_pLog->logMessage("Entering MenuState...");
 
  m_pSceneMgr = OgreFramework::getSingletonPtr()->m_pRoot->createSceneManager(ST_GENERIC, "MenuSceneMgr");
  m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.7f, 0.7f, 0.7f));
 
  m_pCamera = m_pSceneMgr->createCamera("MenuCam");
  m_pCamera->setPosition(Vector3(0, 25, -50));
  m_pCamera->lookAt(Vector3(0, 0, 0));
  m_pCamera->setNearClipDistance(1);
 
  m_pCamera->setAspectRatio(Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualWidth()) / Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualHeight()));
 
  OgreFramework::getSingletonPtr()->m_pViewport->setCamera(m_pCamera);

  // create an imageset for the title
  CEGUI::ImagesetManager *im = &(CEGUI::ImagesetManager::getSingleton());
  CEGUI::NamedXMLResourceManager<CEGUI::Imageset, CEGUI::Imageset_xmlHandler> *castedIm = NULL;
  castedIm = (CEGUI::NamedXMLResourceManager<CEGUI::Imageset, CEGUI::Imageset_xmlHandler>*) im;
  castedIm->create( "Title.imageset" );

  // show cursor
  CEGUI::MouseCursor::getSingleton().show();

  createScene();
}

void MenuState::createScene() {
  CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
  CEGUI::Window *window = wmgr.createWindow("DefaultWindow", "CEGUI/MenuWindow");

  // title logo
  CEGUI::Window *si = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticImage", "TitlePng");
  si->setSize(CEGUI::UVector2(CEGUI::UDim(0.8, 0), CEGUI::UDim(0.25, 0)));
  si->setPosition(CEGUI::UVector2(CEGUI::UDim(0.1, 0), CEGUI::UDim(0.05, 0)));
  si->setProperty("Image","set:Title image:full_image");
  si->setProperty("FrameEnabled", "False");
  si->setProperty("BackgroundEnabled", "False");
  window->addChildWindow(si);

  // new game button
  CEGUI::Window *new_game = wmgr.createWindow("TaharezLook/Button", "CEGUI/NewGameButton");
  new_game->setText("Start Game");
  new_game->setSize(CEGUI::UVector2(CEGUI::UDim(0.5, 0), CEGUI::UDim(0.15, 0)));
  new_game->setPosition(CEGUI::UVector2(CEGUI::UDim(0.25, 0), CEGUI::UDim(0.34, 0)));
  window->addChildWindow(new_game);

  // quit button
  CEGUI::Window *quit = wmgr.createWindow("TaharezLook/Button", "CEGUI/QuitButton");
  quit->setText("Exit Game");
  quit->setSize(CEGUI::UVector2(CEGUI::UDim(0.5, 0), CEGUI::UDim(0.15, 0)));
  quit->setPosition(CEGUI::UVector2(CEGUI::UDim(0.25, 0), CEGUI::UDim(0.53, 0)));
  window->addChildWindow(quit);
  CEGUI::System::getSingleton().setGUISheet(window);

  // events
  new_game->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MenuState::start, this));
  quit->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MenuState::quit, this));
}
 
void MenuState::exit() {
  OgreFramework::getSingletonPtr()->m_pLog->logMessage("Leaving MenuState...");
 
  m_pSceneMgr->destroyCamera(m_pCamera);
  if (m_pSceneMgr)
    OgreFramework::getSingletonPtr()->m_pRoot->destroySceneManager(m_pSceneMgr);
 
  /*OgreFramework::getSingletonPtr()->m_pTrayMgr->clearAllTrays();
  OgreFramework::getSingletonPtr()->m_pTrayMgr->destroyAllWidgets();
  OgreFramework::getSingletonPtr()->m_pTrayMgr->setListener(0);*/
}

bool MenuState::keyPressed(const OIS::KeyEvent &keyEventRef) {
  if (OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_ESCAPE)) {
    m_bQuit = true;
    return true;
  }
 
  //OgreFramework::getSingletonPtr()->keyPressed(keyEventRef);
  CEGUI::System &sys = CEGUI::System::getSingleton();
  sys.injectKeyDown(keyEventRef.key);
  sys.injectChar(keyEventRef.text);
  return true;
}
 
bool MenuState::keyReleased(const OIS::KeyEvent &keyEventRef) {
  //OgreFramework::getSingletonPtr()->keyReleased(keyEventRef);
  CEGUI::System::getSingleton().injectKeyUp(keyEventRef.key);
  return true;
}
 
bool MenuState::mouseMoved(const OIS::MouseEvent &evt) {
  CEGUI::System &sys = CEGUI::System::getSingleton();
  sys.injectMouseMove(evt.state.X.rel, evt.state.Y.rel);
  // Scroll wheel.
  if (evt.state.Z.rel)
    sys.injectMouseWheelChange(evt.state.Z.rel / 120.0f);
  // if(OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseMove(evt)) return true;
  return true;
}
 
bool MenuState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
  CEGUI::System::getSingleton().injectMouseButtonDown(convertButton(id));
  // if(OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseDown(evt, id)) return true;
  return true;
}
 
bool MenuState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
  CEGUI::System::getSingleton().injectMouseButtonUp(convertButton(id));
  // if(OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseUp(evt, id)) return true;
  return true;
}

void MenuState::update(double timeSinceLastFrame) {
  m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
  CEGUI::System::getSingleton().injectTimePulse(m_FrameEvent.timeSinceLastFrame);
  // OgreFramework::getSingletonPtr()->m_pTrayMgr->frameRenderingQueued(m_FrameEvent);
 
  if (m_bQuit == true) {
    shutdown();
    return;
  }
}

bool MenuState::start(const CEGUI::EventArgs &e) {
  CEGUI::WindowManager::getSingleton().destroyWindow( "CEGUI/MenuWindow" );
  changeAppState(findByName("GameState"));
}

bool MenuState::quit(const CEGUI::EventArgs &e) {
  m_bQuit = true;
  return true;
}
