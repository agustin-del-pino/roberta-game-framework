#ifndef ROBERTA_GAME_FRAMEWORK
#define ROBERTA_GAME_FRAMEWORK

#include "raylib.h"
#include <stddef.h>

// Object can have any pointer as data.
// This struct is used for store data in stage.
typedef struct Object
{
    void *data; // Object data pointer.
} Object;

// Stage is used as level/scenes for the game.
typedef struct Stage
{
    Object *objects;         // Allocated list of objects.
    size_t counter;          // The number of allocated objects.
    void (*OnInit)();        // Only executed once, when the stage is loaded.
    void (*OnPreUpdate)();   // Executed every frame after the init.
    void (*OnUpdate)();      // Executed every frame after the pre-update.
    void (*OnPostUpdate)();  // Executed every frame after the update.
    void (*OnPreDraw)();     // Executed every frame after the post-update. Draw operations can be performed.
    void (*OnDraw)();        // Executed every frame after the pre-draw. Draw operations can be performed.
    void (*OnPostDraw)();    // Executed every frame after the draw. Draw operations can be performed.
    void (*OnPreDrawGUI)();  // Executed every frame after the post-draw. Draw operations can be performed.
    void (*OnDrawGUI)();     // Executed every frame after the pre-draw-gui. Draw operations can be performed.
    void (*OnPostDrawGUI)(); // Executed every frame after the draw-gui. Draw operations can be performed.
    void (*OnExit)();        // Only executed when the current stage of the game changes.
} Stage;

// Function that represent the construction of a Stage.
typedef Stage (*StageConstructor)();

// InitGame must be called firts. Initilize raylib and the game instance.
void InitGame(const char *title, int width, int height, int fps, unsigned int screen);

// SetStages sets the stage constructor to be used in the game.
void SetStages(StageConstructor constructors[], size_t stages);
// NextStage changes the current stage to the next one in the list.
void NextStage();
// PreviousStage changes the current stage to the previous one in the list.
void PreviousStage();
// SelectStage changes the current stage by its id.
void SelectStage(unsigned int stage);
// SelectLastStage change the current stage to last stage.
void SelectLastStage();
// GetStage returns the id of the current stage.
unsigned int GetStage();
// GetLastStage returns the id of the last stage.
unsigned int GetLastStage();

// LoadTileset loads the tileset of the game graphics.
void LoadTileset(const char *path);
// GetTileset returns the current loaded tileset.
Texture2D GetTileset();

// Run performs the gameloop starting at the first stage.
void Run();
// ExitGame allows to end the gameloop, thus exiting the game.
void ExitGame();

// AddObject adds object to the current stage.
void AddObject(void *data);
// AddManyObjects adds a list of objects to the current stage.
void AddManyObjects(size_t counter, void **data);
// GetObject returns an object from the list by its id.
Object GetObject(unsigned int id);

#endif