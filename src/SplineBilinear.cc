/*--------------------------------------------------------------------------*\
 |                                                                          |
 |  Copyright (C) 2016                                                      |
 |                                                                          |
 |         , __                 , __                                        |
 |        /|/  \               /|/  \                                       |
 |         | __/ _   ,_         | __/ _   ,_                                | 
 |         |   \|/  /  |  |   | |   \|/  /  |  |   |                        |
 |         |(__/|__/   |_/ \_/|/|(__/|__/   |_/ \_/|/                       |
 |                           /|                   /|                        |
 |                           \|                   \|                        |
 |                                                                          |
 |      Enrico Bertolazzi                                                   |
 |      Dipartimento di Ingegneria Industriale                              |
 |      Universita` degli Studi di Trento                                   |
 |      email: enrico.bertolazzi@unitn.it                                   |
 |                                                                          |
\*--------------------------------------------------------------------------*/

#include "Splines.hh"
#include <cmath>
#include <iomanip>
/**
 * 
 */

namespace Splines {

  using namespace std; // load standard namspace

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  BilinearSpline::operator () ( real_type x, real_type y ) const {
    integer   i   = this->search_x( x );
    integer   j   = this->search_y( y );
    real_type DX  = this->X[size_t(i+1)] - this->X[size_t(i)];
    real_type DY  = this->Y[size_t(j+1)] - this->Y[size_t(j)];
    real_type u   = (x-this->X[size_t(i)])/DX;
    real_type v   = (y-this->Y[size_t(j)])/DY;
    real_type u1  = 1-u;
    real_type v1  = 1-v;
    real_type Z00 = this->Z[size_t(this->ipos_C(i,j))];
    real_type Z01 = this->Z[size_t(this->ipos_C(i,j+1))];
    real_type Z10 = this->Z[size_t(this->ipos_C(i+1,j))];
    real_type Z11 = this->Z[size_t(this->ipos_C(i+1,j+1))];
    return u1 * ( Z00 * v1 + Z01 * v ) +
           u  * ( Z10 * v1 + Z11 * v );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  BilinearSpline::Dx( real_type x, real_type y ) const {
    integer   i   = this->search_x( x );
    integer   j   = this->search_y( y );
    real_type DX  = this->X[size_t(i+1)] - this->X[size_t(i)];
    real_type DY  = this->Y[size_t(j+1)] - this->Y[size_t(j)];
    real_type v   = (y-this->Y[size_t(j)])/DY;
    real_type Z00 = this->Z[size_t(ipos_C(i,j))];
    real_type Z01 = this->Z[size_t(ipos_C(i,j+1))];
    real_type Z10 = this->Z[size_t(ipos_C(i+1,j))];
    real_type Z11 = this->Z[size_t(ipos_C(i+1,j+1))];
    return ( (Z10-Z00) * (1-v) + (Z11-Z01) * v ) / DX;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  BilinearSpline::Dy( real_type x, real_type y ) const {
    integer   i   = this->search_x( x );
    integer   j   = this->search_y( y );
    real_type DX  = this->X[size_t(i+1)] - this->X[size_t(i)];
    real_type DY  = this->Y[size_t(j+1)] - this->Y[size_t(j)];
    real_type u   = (x-this->X[size_t(i)])/DX;
    real_type Z00 = this->Z[size_t(ipos_C(i,j))];
    real_type Z01 = this->Z[size_t(ipos_C(i,j+1))];
    real_type Z10 = this->Z[size_t(ipos_C(i+1,j))];
    real_type Z11 = this->Z[size_t(ipos_C(i+1,j+1))];
    return ( ( Z01-Z00 ) * (1-u) + ( Z11-Z10 ) * u ) / DY;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  BilinearSpline::D( real_type x, real_type y, real_type d[3] ) const {
    integer   i   = this->search_x( x );
    integer   j   = this->search_y( y );
    real_type DX  = this->X[size_t(i+1)] - this->X[size_t(i)];
    real_type DY  = this->Y[size_t(j+1)] - this->Y[size_t(j)];
    real_type u   = (x-this->X[size_t(i)])/DX;
    real_type v   = (y-this->Y[size_t(j)])/DY;
    real_type u1  = 1-u;
    real_type v1  = 1-v;
    real_type Z00 = this->Z[size_t(this->ipos_C(i,j))];
    real_type Z01 = this->Z[size_t(this->ipos_C(i,j+1))];
    real_type Z10 = this->Z[size_t(this->ipos_C(i+1,j))];
    real_type Z11 = this->Z[size_t(this->ipos_C(i+1,j+1))];
    d[0] = u1 * ( Z00 * v1 + Z01 * v ) + u * ( Z10 * v1 + Z11 * v );
    d[1] = v1 * (Z10-Z00) + v * (Z11-Z01); d[1] /= DX;
    d[2] = u1 * (Z01-Z00) + u * (Z11-Z10); d[2] /= DY;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  BilinearSpline::DD( real_type x, real_type y, real_type d[6] ) const {
    this->D( x, y, d );
    d[3] = d[4] = d[5] = 0; // second derivative are 0
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  BilinearSpline::writeToStream( ostream_type & s ) const {
    integer ny = integer(Y.size());
    s << "Nx = " << X.size() << " Ny = " << Y.size() << '\n';
    for ( integer i = 1; i < integer(this->X.size()); ++i ) {
      for ( integer j = 1; j < integer(this->Y.size()); ++j ) {
        size_t i00 = size_t(this->ipos_C(i-1,j-1,ny));
        size_t i10 = size_t(this->ipos_C(i,j-1,ny));
        size_t i01 = size_t(this->ipos_C(i-1,j,ny));
        size_t i11 = size_t(this->ipos_C(i,j,ny));
        s << "patch (" << i << "," << j << ")\n"
          <<  "DX = "  << setw(10) << left << this->X[size_t(i)]-this->X[size_t(i-1)]
          << " DY = "  << setw(10) << left << this->Y[size_t(j)]-this->Y[size_t(j-1)]
          << " Z00 = " << setw(10) << left << this->Z[i00]
          << " Z01 = " << setw(10) << left << this->Z[i01]
          << " Z10 = " << setw(10) << left << this->Z[i10]
          << " Z11 = " << setw(10) << left << this->Z[i11]
          << '\n';
      }
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  char const *
  BilinearSpline::type_name() const
  { return "bilinear"; }

}
