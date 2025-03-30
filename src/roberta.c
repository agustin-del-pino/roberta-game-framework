#include "./roberta.h"
#include "./gui.h"
#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct Game
{
    unsigned int lastStageIndex;
    unsigned int stageIndex;
    Texture2D tileset;
    StageConstructor *constructors;
    Stage stage;
    bool exit;
} Game;

Game game = {
    .lastStageIndex = 0,
    .stageIndex = 0,
    .constructors = NULL,
    .exit = false};

void InitGame(
    const char *title,
    int width, int height,
    int fps, unsigned int screen)
{  
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(width, height, title);

    if (screen == FLAG_WINDOW_MAXIMIZED) {
        MaximizeWindow();
    }

    if (screen == FLAG_WINDOW_MINIMIZED) {
        MinimizeWindow();
    }

    if (screen == FLAG_FULLSCREEN_MODE) {
        ToggleFullscreen();
    }

    SetTargetFPS(fps);
}

void SetStages(StageConstructor constructors[], size_t stages)
{
    game.constructors = realloc(game.constructors, stages * sizeof(StageConstructor));

    if (game.constructors == NULL)
    {
        return;
    }

    for (int i = 0; i < stages; i++)
    {
        game.constructors[i] = constructors[i];
    }
}

void NextStage()
{
    game.lastStageIndex = game.stageIndex;
    game.stageIndex++;
    printf("%d %d\n", game.lastStageIndex, game.stageIndex);
}
void PreviousStage()
{
    game.lastStageIndex = game.stageIndex;
    game.stageIndex--;
}
void SelectStage(unsigned int stage)
{
    game.lastStageIndex = game.stageIndex;
    game.stageIndex = stage;
}
void SelectLastStage()
{
    SelectStage(game.lastStageIndex);
}
unsigned int GetStage()
{
    return game.stageIndex;
}
unsigned int GetLastStage()
{
    return game.lastStageIndex;
}

void LoadTileset(const char *path)
{
    game.tileset = LoadTexture(path);
}

Texture2D GetTileset()
{
    return game.tileset;
}

void FreeStage()
{
    for (size_t i = 0; i < game.stage.counter; i++)
    {
        free(game.stage.objects[i].data);
    }
    free(game.stage.objects);
}

void Run()
{
    bool init = false;

    game.stage = game.constructors[game.stageIndex]();

    while (!WindowShouldClose())
    {
        unsigned int stage = game.stageIndex;

        if (game.stage.OnInit != NULL && !init)
        {
            game.stage.OnInit();
            init = true;
        }

        // Pre Update
        if (game.stage.OnPreUpdate != NULL)
        {
            game.stage.OnPreUpdate();
        }

        // Update
        if (game.stage.OnUpdate != NULL)
        {
            game.stage.OnUpdate();
        }
        // Post Update
        if (game.stage.OnPostUpdate != NULL)
        {
            game.stage.OnPostUpdate();
        }

        BeginDrawing();
        // Pre Draw
        if (game.stage.OnPreDraw != NULL)
        {
            game.stage.OnPreDraw();
        }
        // Draw
        if (game.stage.OnDraw != NULL)
        {
            game.stage.OnDraw();
        }
        // Post Draw
        if (game.stage.OnPostDraw != NULL)
        {
            game.stage.OnPostDraw();
        }
        // Pre Draw GUI
        if (game.stage.OnPreDrawGUI != NULL)
        {
            game.stage.OnPreDrawGUI();
        }
        // Draw GUI
        if (game.stage.OnDrawGUI != NULL)
        {
            game.stage.OnDrawGUI();
        }
        // Post Draw GUI
        if (game.stage.OnPostDrawGUI != NULL)
        {
            game.stage.OnPostDrawGUI();
        }
        EndDrawing();

        if (game.exit)
        {
            FreeStage();
            break;
        }

        // Exit
        if (stage != game.stageIndex)
        {
            if (game.stage.OnExit != NULL) {
                game.stage.OnExit();
            }
            printf("free \n");
            FreeStage();
            printf("getting constructor \n");
            game.stage = game.constructors[game.stageIndex]();
            printf("change stage \n");
        }
    }
    free(game.constructors);
    UnloadTexture(game.tileset);
    CloseWindow();
}

void ExitGame()
{
    game.exit = true;
}

void AddObject(void *data)
{
    game.stage.objects = realloc(game.stage.objects, (game.stage.counter + 1) * sizeof(Object));

    if (game.stage.objects == NULL)
    {
        return;
    }

    game.stage.objects[game.stage.counter].data = data;
    game.stage.counter++;
}

void AddManyObjects(size_t counter, void **data)
{
    size_t c = game.stage.counter + counter;
    game.stage.objects = realloc(game.stage.objects, c * sizeof(Object));

    if (game.stage.objects == NULL)
    {
        return;
    }

    for (int i = game.stage.counter; i < c; i++)
    {
        game.stage.objects[i] = (Object){.data = data[i]};
    }

    game.stage.counter += counter;
}

Object GetObject(unsigned int id)
{
    return game.stage.objects[id];
}