#pragma once
#include "raylib.h"

typedef struct ncEditorData
{
    Vector2 anchor01;

    bool editorBoxActive;
    bool bodyTypeEditMode;
    int bodyTypeActive;
    float massMinValue;
    float massMaxValue;
    float dampingValue;
    float gravityScaleValue;
    float gravitationValue;
} ncEditorData_t;

extern ncEditorData_t ncEditorData;
extern bool ncEditorActive;
extern bool ncEditorIntersect;

void InitEditor();
void UpdateEditor(Vector2 position);
void DrawEditor(Vector2 position);