#pragma once
#include <windows.h>
#include "Defines.h"

/// <summary>
    /// Enum Representing which Mouse we want to check
    /// </summary>
enum eMouseButton {
    Left,
    Right,
    Middle
};

class CMouse {
public:
    /// <summary>
    /// Initialized this mouse object.
    /// </summary>
    void Initialize();

    /// <summary>
    /// Sets the data for this mouse object.
    /// </summary>
    void GetState();

    /// <summary>
    ///  Returns true if the mouse button is down.
    /// </summary>
    bool TriggerDown(eMouseButton button);

    /// <summary>
    /// Returns true if the mouse button is pressed.
    /// </summary>
    bool TriggerReleased(eMouseButton button);

    /// <summary>
    /// Returns true if the mouse button is released.
    /// </summary>
    bool TriggerPressed(eMouseButton button);

    /// <summary>
    /// Position of the mouse
    /// </summary>
    Vector2 Position;

    /// <summary>
    /// Reference to our window handler
    /// </summary>
    HWND hWnd;

private:

    /// <summary>
    /// The X position of the mouse relative to the top left of the window
    /// </summary>
    int m_iX;

    /// <summary>
    /// The Y position of the mouse relative to the top left of the window
    /// </summary>
    int m_iY;

    /// <summary>
    /// A boolean which indicates if we're holding down the left mouse button
    /// </summary>
    bool m_bLeftDown;

    /// <summary>
    /// A boolean which indicates if we've pressed the left mouse button
    /// </summary>
    bool m_bLeftPressed;

    /// <summary>
    /// A boolean which indicates if we've released the left mouse button
    /// </summary>
    bool m_bLeftReleased;

    /// <summary>
    /// Is the right mouse button down?
    /// </summary>
    bool m_bRightDown;

    /// <summary>
    /// Has the right mouse button been pressed?
    /// </summary>
    bool m_bRightPressed;

    /// <summary>
    /// Has the right mouse button been released?
    /// </summary>
    bool m_bRightReleased;

    /// <summary>
    /// Is the middle mouse button down?
    /// </summary>
    bool m_bMiddleDown;

    /// <summary>
    /// Has the middle mouse button been pressed?
    /// </summary>
    bool m_bMiddlePressed;

    /// <summary>
    /// Has the middle mouse button been released?
    /// </summary>
    bool m_bMiddleReleased;

    bool m_bHasLeftPressed;
    bool m_bHasRightPressed;
    bool m_bHasMiddlePressed;

    bool m_bHasLeftReleased;
    bool m_bHasRightReleased;
    bool m_bHasMiddleReleased;

    void HandleButtonPressed(bool down, bool& hasPressed, bool& pressed);
    void HandleButtonReleased(bool down, bool& hasReleased, bool& released);
};