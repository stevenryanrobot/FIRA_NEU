#include "stdafx.h"


#include "ray_2d.h"

namespace rcsc {

/*-------------------------------------------------------------------*/
/*!

 */
Vector2D
Ray2D::intersection( const Line2D & other ) const
{
    Line2D my_line = this->line();

    Vector2D tmp_sol = my_line.intersection( other );

    if ( ! tmp_sol.isValid() )
    {
        return Vector2D::INVALIDATED;
    }

    if ( ! inRightDir( tmp_sol ) )
    {
        return Vector2D::INVALIDATED;
    }

    return tmp_sol;
}

/*-------------------------------------------------------------------*/
/*!

 */
Vector2D
Ray2D::intersection( const Ray2D & other ) const
{
    Vector2D tmp_sol = this->line().intersection( other.line() );

    if ( ! tmp_sol.isValid() )
    {
        return Vector2D::INVALIDATED;
    }

    if ( ! this->inRightDir( tmp_sol )
        || ! other.inRightDir( tmp_sol ) )
    {
        return Vector2D::INVALIDATED;
    }

    return tmp_sol;

}

}
