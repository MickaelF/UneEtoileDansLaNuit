#pragma once
#include <UneEtoile/input/abstractcontrolscheme.h>
#include <UneEtoile/input/action.h>

class CameraManipulation : public AbstractControlScheme
{
public:
    CameraManipulation();

    Vector2Action Move;
    RangeAction Zoom;
    BinaryAction Rotate;
};
