#ifndef MENU_STATE_H
#define MENU_STATE_H
 
#include "AppState.h"
 
class MenuState : public AppState
{
public:
    MenuState();
 
	DECLARE_APPSTATE_CLASS(MenuState)
 
	void enter();
	void createScene();
	void exit();
 
	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	bool keyReleased(const OIS::KeyEvent &keyEventRef);
 
	bool mouseMoved(const OIS::MouseEvent &evt);
	bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
 
	void buttonHit(OgreBites::Button* button);
 
	void update(double timeSinceLastFrame);
        bool start(const CEGUI::EventArgs &e);
        bool quit(const CEGUI::EventArgs &e);
private:
	bool m_bQuit;
};
 
#endif
