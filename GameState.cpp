#include "GameState.h"
 
using namespace Ogre;

CEGUI::MouseButton convertButton2(OIS::MouseButtonID buttonID)
{
    switch (buttonID)
    {
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

GameState::GameState()
{
    m_bQuit         = false;
    m_FrameEvent    = Ogre::FrameEvent();
}
 
void GameState::enter()
{
    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Entering GameState...");
 
    m_pSceneMgr = OgreFramework::getSingletonPtr()->m_pRoot->createSceneManager(ST_GENERIC, "MenuSceneMgr");
    m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.7f, 0.7f, 0.7f));
 
    m_pCamera = m_pSceneMgr->createCamera("MenuCam");
    m_pCamera->setPosition(Vector3(0, 25, -50));
    m_pCamera->lookAt(Vector3(0, 0, 0));
    m_pCamera->setNearClipDistance(1);
 
    m_pCamera->setAspectRatio(Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualWidth()) /
        Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualHeight()));
 
    OgreFramework::getSingletonPtr()->m_pViewport->setCamera(m_pCamera);

    createScene();
}

void GameState::createScene()
{
    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
    CEGUI::Window *gameWindow = wmgr.createWindow("DefaultWindow", "CEGUI/GameWindow");
    // title label
    CEGUI::Window *title = wmgr.createWindow("TaharezLook/StaticText", "CEGUI/Underconstruction");
    // title->setHorizontalAlignment(CEGUI::HA_CENTRE);
    title->setText("Dear Adventurer,\n We haven't started creating the core game yet, but that is our next step!\n\n   -Team Penguin");
    //title->setFont("Batang-26.font");
    title->setSize(CEGUI::UVector2(CEGUI::UDim(0.8, 0), CEGUI::UDim(0.25, 0)));
    title->setPosition(CEGUI::UVector2(CEGUI::UDim(0.1, 0), CEGUI::UDim(0.05, 0)));
    gameWindow->addChildWindow(title);

    // new game button
    CEGUI::Window *new_game = wmgr.createWindow("TaharezLook/Button", "CEGUI/BackButton");
    new_game->setText("Back To Title");
    //new_game->setFont("DejaVuSans-10");
    new_game->setSize(CEGUI::UVector2(CEGUI::UDim(0.5, 0), CEGUI::UDim(0.15, 0)));
    new_game->setPosition(CEGUI::UVector2(CEGUI::UDim(0.25, 0), CEGUI::UDim(0.34, 0)));
    gameWindow->addChildWindow(new_game);

    // quit button
    CEGUI::Window *quit = wmgr.createWindow("TaharezLook/Button", "CEGUI/ExitButton");
    quit->setText("Exit Game");
    //quit->setFont("DejaVuSans-10");
    quit->setSize(CEGUI::UVector2(CEGUI::UDim(0.5, 0), CEGUI::UDim(0.15, 0)));
    quit->setPosition(CEGUI::UVector2(CEGUI::UDim(0.25, 0), CEGUI::UDim(0.53, 0)));
    gameWindow->addChildWindow(quit);
    CEGUI::System::getSingleton().setGUISheet(gameWindow);

    new_game->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GameState::back, this));
    quit->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GameState::quit, this));
}
 
void GameState::exit()
{
    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Leaving GameState...");
 
    m_pSceneMgr->destroyCamera(m_pCamera);
    if(m_pSceneMgr)
        OgreFramework::getSingletonPtr()->m_pRoot->destroySceneManager(m_pSceneMgr);
 
    /*OgreFramework::getSingletonPtr()->m_pTrayMgr->clearAllTrays();
    OgreFramework::getSingletonPtr()->m_pTrayMgr->destroyAllWidgets();
    OgreFramework::getSingletonPtr()->m_pTrayMgr->setListener(0);*/
}

bool GameState::keyPressed(const OIS::KeyEvent &keyEventRef)
{
    if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_ESCAPE))
    {
        m_bQuit = true;
        return true;
    }
 
    //OgreFramework::getSingletonPtr()->keyPressed(keyEventRef);
    CEGUI::System &sys = CEGUI::System::getSingleton();
    sys.injectKeyDown(keyEventRef.key);
    sys.injectChar(keyEventRef.text);
    return true;
}
 
bool GameState::keyReleased(const OIS::KeyEvent &keyEventRef)
{
    //OgreFramework::getSingletonPtr()->keyReleased(keyEventRef);
    CEGUI::System::getSingleton().injectKeyUp(keyEventRef.key);
    return true;
}
 
bool GameState::mouseMoved(const OIS::MouseEvent &evt)
{
    CEGUI::System &sys = CEGUI::System::getSingleton();
    sys.injectMouseMove(evt.state.X.rel, evt.state.Y.rel);
    // Scroll wheel.
    if (evt.state.Z.rel)
      sys.injectMouseWheelChange(evt.state.Z.rel / 120.0f);
    // if(OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseMove(evt)) return true;
    return true;
}
 
bool GameState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    CEGUI::System::getSingleton().injectMouseButtonDown(convertButton2(id));
    // if(OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseDown(evt, id)) return true;
    return true;
}
 
bool GameState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    CEGUI::System::getSingleton().injectMouseButtonUp(convertButton2(id));
    // if(OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseUp(evt, id)) return true;
    return true;
}

void GameState::update(double timeSinceLastFrame)
{
    m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
    CEGUI::System::getSingleton().injectTimePulse(m_FrameEvent.timeSinceLastFrame);
    // OgreFramework::getSingletonPtr()->m_pTrayMgr->frameRenderingQueued(m_FrameEvent);
 
    if(m_bQuit == true)
    {
        shutdown();
        return;
    }
}

bool GameState::back(const CEGUI::EventArgs &e)
{
  CEGUI::WindowManager::getSingleton().destroyWindow( "CEGUI/GameWindow" );
  popAllAndPushAppState(findByName("MenuState"));
}

bool GameState::quit(const CEGUI::EventArgs &e)
{
  m_bQuit = true;
  return true;
}
