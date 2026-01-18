#include "stdafx.h"
#include "matrix_2d.h"

namespace rcsc {

/*-------------------------------------------------------------------*/
/*!

 */
Matrix2D
Matrix2D::inverted() const
{
    double determinant = det();
    if ( determinant == 0.0 )
    {
        // never invertible
        return Matrix2D(); // default matrix
    }

    double dinv = 1.0 / determinant;
    return Matrix2D( M_22 * dinv, -M_12 * dinv,
                     -M_21 * dinv, M_11 * dinv,
                     (M_12*M_dy - M_dx*M_22) * dinv,
                     (M_dx*M_21 - M_11*M_dy) * dinv );
}

/*-------------------------------------------------------------------*/
/*!

 */
Matrix2D &
Matrix2D::rotate( const AngleDeg & angle )
{
    // rotate matrix
    // R = ( cona, -sina, 0 )
    //     ( sina,  cosa, 0 )
    //     (    0,     0, 1 )

    // this = R * this
    // *this = create_rotation(angle) * *this;

    double sina = angle.sin();
    double cosa = angle.cos();

    double tm11 = M_11*cosa - M_21*sina;
    double tm12 = M_12*cosa - M_22*sina;
    double tm21 = M_11*sina + M_21*cosa;
    double tm22 = M_12*sina + M_22*cosa;
    double tdx = M_dx*cosa - M_dy*sina;
    double tdy = M_dx*sina + M_dy*cosa;
    M_11 = tm11; M_12 = tm12; M_dx = tdx;
    M_21 = tm21; M_22 = tm22; M_dy = tdy;
    return *this;
}


}
