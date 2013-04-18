#ifndef GAME_STATE_H
#define GAME_STATE_H
 
#include "AppState.h"
 
class GameState : public AppState
{
public:
    GameState();
 
	DECLARE_APPSTATE_CLASS(GameState)
 
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
        void getInput();
private:
        bool faceRight;
        Ogre::SceneNode *PenguinNode;
	bool m_bQuit;
};
 
#endif
