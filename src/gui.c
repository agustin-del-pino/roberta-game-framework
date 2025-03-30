#include "./gui.h"
#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>

Button *CreateButton(float x, float y, float width, float height, float scale) {
    Button *btn = malloc(sizeof(Button));
    btn->bounds = (Rectangle){x, y, width*scale, height*scale};
    btn->isPressed = false;
    return btn;
}
