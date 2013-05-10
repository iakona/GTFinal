#ifndef GAME_OVER_STATE_H
#define GAME_OVER_STATE_H
 
#include "AppState.h"

class GameOverState : public AppState {
  public:
    GameOverState();
 
    DECLARE_APPSTATE_CLASS(GameOverState)
 
    void enter();
    void createScene();
    void exit();
 
    bool keyPressed(const OIS::KeyEvent &keyEventRef);
    bool keyReleased(const OIS::KeyEvent &keyEventRef);
 
    bool mouseMoved(const OIS::MouseEvent &evt);
    bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
    bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
 
    void update(double timeSinceLastFrame);
    bool backToTitle(const CEGUI::EventArgs &e);
    
  private:
    bool m_bQuit;
};
 
#endif
