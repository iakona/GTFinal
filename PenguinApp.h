#ifndef PENGUINAPP_H
#define PENGUINAPP_H
 
#include "AdvancedOgreFramework.h"
#include "AppStateManager.h"
 
class PenguinApp {
  public:
    PenguinApp();
    ~PenguinApp();
    void startGame();
 
  private:
    AppStateManager* m_pAppStateManager;
};
 
#endif
