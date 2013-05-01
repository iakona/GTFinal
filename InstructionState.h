#ifndef INSTRUCTION_STATE_H
#define INSTRUCTION_STATE_H
 
#include "AppState.h"

class InstructionState : public AppState {
  public:
    InstructionState();
 
    DECLARE_APPSTATE_CLASS(InstructionState)
 
    void enter();
    void createScene();
    void exit();
 
    bool keyPressed(const OIS::KeyEvent &keyEventRef);
    bool keyReleased(const OIS::KeyEvent &keyEventRef);
 
    bool mouseMoved(const OIS::MouseEvent &evt);
    bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
    bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
 
    //void buttonHit(OgreBites::Button* button);
 
    void update(double timeSinceLastFrame);
    bool backToTitle(const CEGUI::EventArgs &e);
    
  private:
    bool m_bQuit;
    // bool created;
};
 
#endif
