#include "PenguinApp.h"
 
#include "MenuState.h"
#include "GameState.h"
 
PenguinApp::PenguinApp() {
  m_pAppStateManager = 0;
}
 
PenguinApp::~PenguinApp() {
  delete m_pAppStateManager;
        delete OgreFramework::getSingletonPtr();
}
 
void PenguinApp::startGame() {
  new OgreFramework();
  if(!OgreFramework::getSingletonPtr()->initOgre("AdvancedOgreFramework", 0, 0))
    return;
 
  OgreFramework::getSingletonPtr()->m_pLog->logMessage("Game initialized!");
 
  m_pAppStateManager = new AppStateManager();
 
  MenuState::create(m_pAppStateManager, "MenuState");
  GameState::create(m_pAppStateManager, "GameState");
        //PauseState::create(m_pAppStateManager, "PauseState");
 
  m_pAppStateManager->start(m_pAppStateManager->findByName("MenuState"));
}
