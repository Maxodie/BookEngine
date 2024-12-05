#pragma once
#include "Common/Event.hpp"

namespace Book
{
    // window events
    struct WindowMaximizeEvent {};

    struct WindowIconifyEvent {};

    struct WindowRestoreEvent {};

    struct WindowCloseEvent {};

    struct WindowResizeEvent
    {
        WindowResizeEvent(int32_t w, int32_t h)
            : Width(w), Height(h) {}

        int32_t Width{0};
        int32_t Height{0};
    };

    // key events
    struct KeyReleaseEvent
    {
        KeyReleaseEvent(int32_t key)
            : Key(key) {}

        int32_t Key{-1};
    };

    struct KeyPressedEvent
    {
        KeyPressedEvent(int32_t key)
            : Key(key) {}

        int32_t Key{-1};
    };

    struct KeyRepeatEvent
    {
        KeyRepeatEvent(int32_t key)
            : Key(key) {}

        int32_t Key{-1};
    };

    // mouse events
    struct MouseReleaseEvent
    {
        MouseReleaseEvent(int32_t button)
            : Button(button) {}

        int32_t Button{-1};
    };

    struct MouseDownEvent
    {
        MouseDownEvent(int32_t button)
            : Button(button) {}

        int32_t Button{-1};
    };

    struct MouseDragEvent
    {
        MouseDragEvent(double deltaX, double deltaY)
            : DeltaX(deltaX), DeltaY(deltaY) {}

        double DeltaX{0.0}, DeltaY{0.0};
    };

    struct MouseMotionEvent
    {
        MouseMotionEvent(double targetX, double targetY)
            : TargetX(targetX), TargetY(targetY) {}

        double TargetX{0.0}, TargetY{0.0};
    };

    struct MouseWheelEvent
    {
        MouseWheelEvent(double scrollX, double scrollY)
            : ScrollX(scrollX), ScrollY(scrollY) {}

        double ScrollX{0.0}, ScrollY{0.0};
    };


}
