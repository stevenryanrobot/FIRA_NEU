#include "stdafx.h"
#include "vector_2d.h"

#include <limits>

namespace rcsc {

const double Vector2D::EPSILON = 1.0e-6;

const double Vector2D::ERROR_VALUE = 5000.0000;

const Vector2D Vector2D::INVALIDATED( Vector2D::ERROR_VALUE, Vector2D::ERROR_VALUE );

}
