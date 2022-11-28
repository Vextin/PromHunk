#include "Mouse.h"

void CMouse::Initialize()
{
    hWnd = GetActiveWindow();
}

void CMouse::HandleButtonPressed(bool down, bool& hasPressed, bool& pressed) {
    if (down) {
        if (!hasPressed) {
            pressed = true;
            hasPressed = true;
        }
        else {
            pressed = false;
        }
    }
    else {
        hasPressed = false;
        pressed = false;
    }
}

void CMouse::HandleButtonReleased(bool down, bool& hasReleased, bool& released) {
    if (down) {
        hasReleased = false;
        released = false;
    }
    else {
        if (!hasReleased) {
            released = true;
            hasReleased = true;
        }
        else {
            released = false;
        }
    }
}

bool CMouse::TriggerDown(eMouseButton e) {
    switch (e) {
    case eMouseButton::Left:
        return m_bLeftDown;
        break;
    case eMouseButton::Right:
        return m_bRightDown;
        break;
    case eMouseButton::Middle:
        return m_bMiddleDown;
        break;
    }
}

bool CMouse::TriggerPressed(eMouseButton e) {
    switch (e) {
    case eMouseButton::Left:
        return m_bLeftPressed;
        break;
    case eMouseButton::Right:
        return m_bRightPressed;
        break;
    case eMouseButton::Middle:
        return m_bMiddlePressed;
        break;
    }
}

bool CMouse::TriggerReleased(eMouseButton e) {
    switch (e) {
    case eMouseButton::Left:
        return m_bLeftReleased;
        break;
    case eMouseButton::Right:
        return m_bRightReleased;
        break;
    case eMouseButton::Middle:
        return m_bMiddleReleased;
        break;
    }
}

void CMouse::GetState() {
    POINT p;
    GetCursorPos(&p);
    ScreenToClient(hWnd, &p);
    m_iX = p.x;
    m_iY = p.y;

    //Check if we're holding down the middle right or left mouse button
    m_bLeftDown = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
    m_bRightDown = (GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0;
    m_bMiddleDown = (GetAsyncKeyState(VK_MBUTTON) & 0x8000) != 0;

    //Handle the pressed vents for our mouse buttons
    HandleButtonPressed(m_bLeftDown, m_bHasLeftPressed, m_bLeftPressed);
    HandleButtonPressed(m_bRightDown, m_bHasRightPressed, m_bRightPressed);
    HandleButtonPressed(m_bMiddleDown, m_bHasMiddlePressed, m_bMiddlePressed);

    //Handle the released events for our mouse buttons
    HandleButtonReleased(m_bLeftDown, m_bHasLeftReleased, m_bLeftReleased);
    HandleButtonReleased(m_bRightDown, m_bHasRightReleased, m_bRightReleased);
    HandleButtonReleased(m_bMiddleDown, m_bHasMiddleReleased, m_bMiddleReleased);

    //Assign the position
    Position = Vector2(m_iX, m_iY);
}

