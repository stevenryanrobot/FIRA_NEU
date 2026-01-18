#include "stdafx.h"

#include "line_2d.h"

#include <iostream>
#include <limits>

namespace rcsc {

const double Line2D::EPSILON = 1.0e-10;
const double Line2D::ERROR_VALUE = 5000.0000;

/*-------------------------------------------------------------------*/
/*!

 */
Vector2D
Line2D::intersection( const Line2D & line1,
                      const Line2D & line2 )
{
    double tmp = line1.a() * line2.b() - line1.b() * line2.a();
    if ( std::fabs( tmp ) < EPSILON )
    {
        return Vector2D::INVALIDATED;
    }

    return Vector2D( (line1.b() * line2.c() - line2.b() * line1.c()) / tmp,
                     (line2.a() * line1.c() - line1.a() * line2.c()) / tmp );
}

/*-------------------------------------------------------------------*/
/*!

 */
Line2D
Line2D::perpendicular_bisector( const Vector2D & p1,
                                const Vector2D & p2 )
{
    if( std::fabs( p2.x - p1.x ) < EPSILON
        && std::fabs( p2.y - p1.y ) < EPSILON )
    {
        // input points have same coordiate values.
        std::cerr << "(Line2D::perpendicular_bisector)"
                  << " ***ERROR*** input points have same coordinate values "
                  << p1 << p2
                  << std::endl;
        return Line2D( p1, Vector2D( p1.x + 1.0, p1.y ) );
    }

    double tmp = ( p2.x*p2.x - p1.x*p1.x
                   + p2.y*p2.y - p1.y*p1.y ) * -0.5 ;
    return Line2D( p2.x - p1.x,
                   p2.y - p1.y,
                   tmp );
}

}
