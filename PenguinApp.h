#ifndef PENGUINAPP_H
#define PENGUINAPP_H
 
#include "AdvancedOgreFramework.h"
#include "AppStateManager.h"
#include "MenuState.h"
#include "GameState.h"
#include "InstructionState.h"
 
class PenguinApp {
  public:
    PenguinApp();
    ~PenguinApp();
    void startGame();
 
  private:
    AppStateManager* m_pAppStateManager;
};
 
#endif
