/*--------------------------------------------------------------------------*\
 |                                                                          |
 |  Copyright (C) 1998                                                      |
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

/**
 * 
 */

namespace Splines {

  using namespace std ; // load standard namspace

  /*
  //   _   _                     _ _       
  //  | | | | ___ _ __ _ __ ___ (_) |_ ___ 
  //  | |_| |/ _ \ '__| '_ ` _ \| | __/ _ \
  //  |  _  |  __/ |  | | | | | | | ||  __/
  //  |_| |_|\___|_|  |_| |_| |_|_|\__\___|
  */
  void
  Hermite3( valueType const x, valueType const H, valueType base[4] ) {
    valueType X = x/H ;
    base[1] = X*X*(3-2*X)   ;
    base[0] = 1-base[1]     ;
    base[2] = x*(X*(X-2)+1) ;
    base[3] = x*X*(X-1)     ;
  } ;

  void
  Hermite3_D( valueType const x, valueType const H, valueType base_D[4] ) {
    valueType X = x/H ;
    base_D[0] = 6.0*X*(X-1.0)/H ;
    base_D[1] = -base_D[0];
    base_D[2] = ((3*X-4)*X+1);
    base_D[3] = X*(3*X-2);
  }

  void
  Hermite3_DD( valueType const x, valueType const H, valueType base_DD[4] ) {
    valueType X = x/H ;
    base_DD[0] = (12*X-6)/(H*H) ;
    base_DD[1] = -base_DD[0] ;
    base_DD[2] = (6*X-4)/H ;
    base_DD[3] = (6*X-2)/H ;
  }

  void
  Hermite3_DDD( valueType const x, valueType const H, valueType base_DDD[4] ) {
    base_DDD[0] = 12/(H*H*H) ;
    base_DDD[1] = -base_DDD[0] ;
    base_DDD[2] = 6/(H*H) ;
    base_DDD[3] = base_DDD[2] ;
  }

  // --------------------------------------------------------------------------

  void
  Hermite5( valueType const t, valueType const h, valueType base[6] ) {
    valueType t1  = h*h ;
    valueType t2  = 6 * t ;
    valueType t3  = h - t ;
    valueType t4  = 3 * t ;
    valueType t5  = 1 / h ;
    valueType t6  = t5 * t5 ;
    valueType t7  = t6 * t6 ;
    valueType t8  = t5 * t7 ;
              t5 *= t6 ;
              t6  = t3 * t3 ;
    valueType t9  = t3 * t6 ;
    valueType t10 = t * t   ;
    valueType t11 = t * t10 ;
    base[0] = (t1 + (3 * h + t2) * t) * t9 * t8;
    base[1] = t11 * (10 * t1 + (-15 * h + t2) * t) * t8;
    base[2] = t * (h + t4) * t9 * t7;
    base[3] = -t11 * (4 * h - t4) * t3 * t7;
    base[4] = 0.5 * (t10 * t9 * t5) ;
    base[5] = 0.5 * (t11 * t6 * t5) ;
  } ;

  void
  Hermite5_D( valueType const t, valueType const h, valueType base_D[6] ) {
    valueType t1  = h - t ;
    valueType t2  = 5 * t ;
    valueType t3  = 3 * t ;
    valueType t4  = 2 * h ;
    valueType t5  = 1 / h ;
    valueType t6  = t5 * t5 ;
    valueType t7  = t6 * t6 ;
              t6 *= t5 ;
    valueType t8  = t1 * t1 ;
    valueType t9  = t * t ;
              t5 *= 30 * t8 * t9 * t7 ;
    base_D[0] = -t5 ;
    base_D[1] =  t5 ;
    base_D[2] = t8 * (h + t2) * (h - t3) * t7 ;
    base_D[3] = -t9 * (6 * h - t2) * (t4 - t3) * t7 ;
    base_D[4] = 0.5 * t * t8 * (t4 - t2) * t6 ;
    base_D[5] = 0.5 * t1 * t9 * (3 * h - t2) * t6 ;
  }

  void
  Hermite5_DD( valueType const t, valueType const h, valueType base_DD[6] ) {
    valueType t1 = h - t ;
    valueType t2 = -5 * t ;
    valueType t3 = h * h ;
    valueType t4 = 10 * t ;
    valueType t5 = 1 / h ;
    valueType t6 = t5 * t5 ;
    valueType t7 = t6 * t6 ;
              t6 *= t5 ;
              t5 *= 60 * t * t1 * (h - 2 * t ) * t7;
    valueType t8 = -12 * t * t1 ;
    base_DD[0] = -t5;
    base_DD[1] = t5;
    base_DD[2] = t8 * (3 * h + t2) * t7;
    base_DD[3] = t8 * (2 * h + t2) * t7;
    base_DD[4] = t1 * (t3 + (t4 - 8 * h) * t) * t6 ;
    base_DD[5] = t * (3 * t3 + (t4 - 12 * h) * t) * t6 ;
  }

  void
  Hermite5_DDD( valueType const t, valueType const h, valueType base_DDD[6] ) {
    valueType t1 = h * h ;
    valueType t2 = 15 * t ;
    valueType t3 = 3 * t1 ;
    valueType t4 = -12 ;
    valueType t5 = 10 * t ;
    valueType t6 = 1 / h;
    valueType t7 = t6 * t6 ;
    valueType t8 = t7 * t7 ;
              t7 *= t6 ;
              t6 *= 60 * ( t1 + 6 * t * (t-h) ) * t8;
    base_DDD[0] = -t6 ;
    base_DDD[1] =  t6 ;
    base_DDD[2] =  t4 * (t3 + (t2 - 16 * h) * t) * t8;
    base_DDD[3] =  t4 * (2 * t1 + (t2 - 14 * h) * t) * t8;
    base_DDD[4] = -3*(t3 + (t4 * h + t5) * t) * t7 ;
    base_DDD[5] =  3*(t1 + (t5 - 8 * h) * t) * t7 ;
  }

  void
  Hermite5_DDDD( valueType const t, valueType const h, valueType base_DDDD[6] ) {
    valueType t1 = -15 * t ;
    valueType t2 = -5 * t ;
    valueType t3 = 1 / h ;
    valueType t4 = t3 * t3 ;
    valueType t5 = t4 * t4 ;
    t4 *= t3 ;
    t3 *= (-720 * t + 360 * h) * t5;
    base_DDDD[0] =  t3 ;
    base_DDDD[1] = -t3 ;
    base_DDDD[2] =  (192 * h + 24 * t1) * t5 ;
    base_DDDD[3] =  (168 * h + 24 * t1) * t5 ;
    base_DDDD[4] =  (36 * h + 12 * t2) * t4 ;
    base_DDDD[5] = -(24 * h + 12 * t2) * t4 ;
  }

  void
  Hermite5_DDDDD( valueType const t, valueType const h, valueType base_DDDDD[6] ) {
    valueType t1 = 1 / h ;
    valueType t2 = t1 * t1 ;
    valueType t3 = t2 * t2 ;
    valueType t4 = 720 * t1 * t3 ;
              t3 *= -360 ;
              t1 *= 60 * t2 ;
    base_DDDDD[0] = -t4 ;
    base_DDDDD[1] =  t4 ;
    base_DDDDD[2] =  t3 ;
    base_DDDDD[3] =  t3 ;
    base_DDDDD[4] = -t1 ;
    base_DDDDD[5] =  t1 ;
  }

}