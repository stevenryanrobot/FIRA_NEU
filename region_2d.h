// -*-c++-*-
#ifndef RCSC_GEOM_REGION2D_H
#define RCSC_GEOM_REGION2D_H

namespace rcsc {

class Vector2D;

/*!
  \class Region2D
  \brief abstract 2D region class
*/
class Region2D {
protected:

    /*!
      \brief accessible only from derived classes
     */
    Region2D()
      { }

public:

    /*!
      \brief virtual destructor.
     */
    virtual
    ~Region2D()
      { }

    /*!
      \brief get the area of this region
      \return value of the area
     */
    virtual
    double area() const = 0;

    /*!
      \brief check if this region contains 'point'.
      \param point considerd point
      \return true or false
    */
    virtual
    bool contains( const Vector2D & point ) const = 0;

};

}

#endif
