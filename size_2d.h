#ifndef RCSC_GEOM_SIZE2D_H
#define RCSC_GEOM_SIZE2D_H

#include <ostream>
#include <cmath>

namespace rcsc {

/*!
  \class Size2D
  \brief 2D size definition class
 */
class Size2D {
private:
    //! x range
    double M_length;

    //! y range
    double M_width;

public:

    /*!
      \brief default constructor.
    */
    Size2D()
        : M_length( 0.0 )
        , M_width( 0.0 )
      { }

    /*!
      \brief constructor with variables
      \param length x range
      \param width y range
     */
    Size2D( const double & length,
            const double & width )
        : M_length( std::fabs( length ) )
        , M_width( std::fabs( width ) )
      { }

    /*!
      \brief assign new range directly.
      \param length new X range
      \param width new Y range
      \return reference to itself
    */
    const
    Size2D & assign( const double & length,
                     const double & width )
      {
          M_length = std::fabs( length );
          M_width = std::fabs( width );
          return *this;
      }

    /*!
      \brief set new X range
      \param length new X range
      \return reference to itself
    */
    const
    Size2D & setLength( const double & length )
      {
          M_length = std::fabs( length );
          return *this;
      }

    /*!
      \brief set new Y range
      \param width new Y range
      \return reference to itself
    */
    const
    Size2D & setWidth( const double & width )
      {
          M_width = std::fabs( width );
          return *this;
      }

    /*!
      \brief get the value of X range
      \return value of X range
     */
    const
    double & length() const
      {
          return M_length;
      }

    /*!
      \brief get the value of Y range
      \return value of Y range
     */
    const
    double & width() const
      {
          return M_width;
      }

    /*!
      \brief get the length of diagonal line
      \return length of diagonal line
     */
    double diagonal() const
      {
          return std::sqrt( length() * length()
                            + width() * width() );
      }

    /*!
      \brief output values to stream.
      \param os reference to the output stream
      \return reference to the output stream
     */
    std::ostream & print( std::ostream & os ) const
      {
          os << "(" << length() << ", " << width() << ")";
          return os;
      }

};

} // end of namespace

#endif
