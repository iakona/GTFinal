noinst_HEADERS = AppState.h SoundManager.h AdvancedOgreFramework.h AppStateManager.h MenuState.h GameState.h PenguinApp.h GraphicsBody.h KillBox.h Penguin.h Wall.h Graphics.h MotionState.h PhysicsBody.h Physics.h InstructionState.h Goal.h Terrain.h GameOverState.h

bin_PROGRAMS = PenguinQuest
PenguinQuest_CPPFLAGS = -I$(top_srcdir)
PenguinQuest_SOURCES = main.cpp SoundManager.cpp AdvancedOgreFramework.cpp AppStateManager.cpp MenuState.cpp GameState.cpp PenguinApp.cpp GraphicsBody.cpp KillBox.cpp Wall.cpp Penguin.cpp Graphics.cpp MotionState.cpp PhysicsBody.cpp Physics.cpp InstructionState.cpp Goal.cpp Terrain.cpp GameOverState.cpp

PenguinQuest_CXXFLAGS = $(OGRE_CFLAGS) $(OIS_CFLAGS) $(bullet_CFLAGS) $(sdl_CFLAGS) $(SDL_net_CFLAGS) $(CEGUI_CFLAGS) $(CEGUI_OGRE_CFLAGS)
PenguinQuest_LDADD = $(OGRE_LIBS) $(OIS_LIBS) $(bullet_LIBS) $(sdl_LIBS) $(SDL_net_LIBS) $(CEGUI_LIBS) $(CEGUI_OGRE_LIBS)

EXTRA_DIST = buildit makeit
AUTOMAKE_OPTIONS = foreign
