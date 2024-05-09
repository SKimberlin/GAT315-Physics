#include "editor.h"
#define RAYGUI_IMPLEMENTATION
#include "../../raygui/src/raygui.h"

bool ncEditorActive = true;
bool ncEditorIntersect = false;
ncEditorData_t ncEditorData;

Rectangle editorRect;

Texture2D cursorTexture;

void InitEditor()
{
    GuiLoadStyle("raygui/styles/cyber/style_cyber.rgs");

    Image image = LoadImage("resources/reticle.png");
    cursorTexture = LoadTextureFromImage(image);
    UnloadImage(image);
    HideCursor();

    ncEditorData.anchor01 = (Vector2){ 840, 24 };

    ncEditorData.editorBoxActive = true;
    ncEditorData.massMinValue = 1;
    ncEditorData.massMaxValue = 1;
    ncEditorData.gravitationValue = 0;
    ncEditorData.bodyTypeEditMode = false;
    ncEditorData.bodyTypeActive = 0;
    ncEditorData.dampingValue = 0;
    ncEditorData.gravityScaleValue = 0;
    
    editorRect = (Rectangle){ ncEditorData.anchor01.x + 0, ncEditorData.anchor01.y + 0, 240, 576 };
}

void UpdateEditor(Vector2 position)
{
    if (IsKeyPressed(KEY_TAB)) ncEditorData.editorBoxActive != !ncEditorData.editorBoxActive;
}

void DrawEditor(Vector2 position)
{
    if (ncEditorData.bodyTypeEditMode) GuiLock();

    if (ncEditorData.editorBoxActive)
    {
        ncEditorData.editorBoxActive = !GuiWindowBox((Rectangle) { ncEditorData.anchor01.x + 0, ncEditorData.anchor01.y + 0, 240, 576 }, "Editor");
        GuiGroupBox((Rectangle) { ncEditorData.anchor01.x + 16, ncEditorData.anchor01.y + 40, 208, 192 }, "Body");
        GuiGroupBox((Rectangle) { ncEditorData.anchor01.x + 16, ncEditorData.anchor01.y + 240, 208, 144 }, "World");
        GuiSlider((Rectangle) { ncEditorData.anchor01.x + 96, ncEditorData.anchor01.y + 80, 120, 16 }, "Mass Min", NULL, & ncEditorData.massMinValue, 0.1f, 100);
        GuiSlider((Rectangle) { ncEditorData.anchor01.x + 96, ncEditorData.anchor01.y + 104, 120, 16 }, "Mass Max", NULL, & ncEditorData.massMaxValue, 0.1f, 100);
        GuiSlider((Rectangle) { ncEditorData.anchor01.x + 96, ncEditorData.anchor01.y + 128, 120, 16 }, "Damping", NULL, & ncEditorData.dampingValue, 0, 1);
        GuiSlider((Rectangle) { ncEditorData.anchor01.x + 96, ncEditorData.anchor01.y + 152, 120, 16 }, "Gravity Scale", NULL, & ncEditorData.gravityScaleValue, 0, 1);
        GuiSliderBar((Rectangle) { ncEditorData.anchor01.x + 96, ncEditorData.anchor01.y + 248, 120, 16 }, "Gravitation", NULL, & ncEditorData.gravitationValue, 0, 100);
        if (GuiDropdownBox((Rectangle) { ncEditorData.anchor01.x + 24, ncEditorData.anchor01.y + 48, 192, 24 }, "STATIC; KINEMATIC; DYNAMIC", & ncEditorData.bodyTypeActive, ncEditorData.bodyTypeEditMode)) ncEditorData.bodyTypeEditMode = !ncEditorData.bodyTypeEditMode;
    }

    DrawTexture(cursorTexture, (int)position.x - cursorTexture.width / 2, (int)position.y - cursorTexture.height / 2, WHITE);

    GuiUnlock();
    
}
