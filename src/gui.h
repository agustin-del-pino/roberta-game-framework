#ifndef ROBERTA_GUI_COMPONENTS
#define ROBERTA_GUI_COMPONENTS

#include "raylib.h"

#define NO_SCALE 1.0f

// A simple button pretended to be used for GUI.
typedef struct Button
{
    Rectangle bounds; // Button area for checking the mouse clik.
    bool isPressed;   // Flag for indicate when the button is pressed.
} Button;

// CreateButton returns the pointer of a new Button. (Pretended to be used as object's data).
Button *CreateButton(float x, float y, float width, float height, float scale);

#endif