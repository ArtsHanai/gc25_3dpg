#include "Input.h"
#include <assert.h>

namespace {
    static char prevKey[256];
    static char currentKey[256];
    static int prevMouse;
    static int currentMouse;
    static POINT mousePoint;
};

Input::Input()
{
    DontDestroyOnSceneChange();
    SetDrawOrder(10000);

    memset(prevKey, 1, 256);
    memset(currentKey, 1, 256);
    prevMouse = -1;
    currentMouse = 0;
    mousePoint.x = -1;
    mousePoint.y = -1;
}

Input* Input::Create()
{
    Input* obj = FindGameObject<Input>();
    if (obj == nullptr) {
        obj = new Input();
    }
    return obj;
}

Input::~Input()
{
}

void Input::Update()
{
    memcpy(prevKey, currentKey, 256);
    GetHitKeyStateAll(currentKey);
    prevMouse = currentMouse;
    currentMouse = GetMouseInput();
    int x, y;
    GetMousePoint(&x, &y);
    mousePoint.x = x;
    mousePoint.y = y;
}

void Input::Draw()
{
}

bool Input::IsKeyPress(int key)
{
    assert(key>=0 && key<256);
    return currentKey[key] != 0;
}

bool Input::IsKeyOnTrig(int key)
{
    assert(key >= 0 && key < 256);
    return currentKey[key] != 0 && prevKey[key] == 0;
}

bool Input::IsMousePress(int key)
{
    return (currentMouse & key) != 0;
}

bool Input::IsMouseOnTrig(int button)
{
    return (currentMouse & ~prevMouse & button) != 0;
}

bool Input::IsMouseOffTrig(int button)
{
    return (~currentMouse & prevMouse & button) != 0;
}

const POINT& Input::MousePosition()
{
    return mousePoint;
}