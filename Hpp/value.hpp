
  // VALUE 
  typedef FLOAT valuE;


  inline valuE radianS( valuE x );
  inline valuE degreeS( valuE x );
  inline valuE sigN( valuE x );
  inline valuE sqR( valuE x );
  inline valuE sqrT( valuE x );
  inline valuE poW( valuE x, valuE y );
  inline valuE clamP( valuE x, valuE min = 0.0, valuE max = 1.0 ); 
  inline valuE flooR( valuE x );
  inline valuE ceiL( valuE x );
  inline valuE rounD( valuE x );
  inline valuE moD( valuE x, valuE y );
  inline valuE steP( valuE x, valuE min = 0.0 );
  inline valuE smoothsteP( valuE x, valuE min = 0.0, valuE max = 1.0 );
  inline valuE randomvaluE( valuE min = 0.0, valuE max = 1.0 );
  inline valuE gaussrandomvaluE( valuE min = 0.0, valuE max = 1.0, DWORD n = 5 );
//  inline valuE ran1( long *idnum );
//  inline valuE gammalN(  ); // treba dorobit!!!
//  inline valuE poissonrandomvaluE( valuE xm, long *idum );
  inline valuE diV( valuE x, valuE y, valuE c = 0.0 );
  inline valuE loG( valuE x ); 
  inline valuE lG( valuE x );
  inline valuE lN( valuE x );
  inline valuE exP( valuE x );
  inline valuE sinH( valuE x );
  inline valuE cosH( valuE x );
  inline valuE arctanH( valuE x );
  inline valuE arccotH( valuE x );
  inline valuE erF( valuE x );
  inline valuE erfC( valuE x );
  inline valuE gaussiaN( valuE x, valuE y, valuE s );
  inline valuE lerP( valuE x, valuE yA, valuE yB, valuE xA = 0.0, valuE xB = 1.0 );
  inline valuE herminterP( valuE x, valuE yA, valuE yB, valuE xA = 0.0, valuE xB = 1.0 );
  inline valuE lerP( valuE x, valuE y, valuE zA, valuE zB, valuE zC, valuE zD, valuE xA = 0.0, valuE yA = 0.0, valuE xC = 1.0, valuE yC = 1.0 );
  inline valuE herminterP( valuE x, valuE y, valuE zA, valuE zB, valuE zC, valuE zD, valuE xA = 0.0, valuE yA = 0.0, valuE xC = 1.0, valuE yC = 1.0 );






  inline valuE radianS( valuE x ) {
      return x*DEG_RAD; 
  }




  inline valuE degreeS( valuE x ) {
      return x*RAD_DEG; 
  }




  inline valuE sigN( valuE x ) {
	  if( x < -EPSILON ) return -1.0; else
	  if( x > EPSILON ) return 1.0; else return 0.0;
  }




  inline valuE sqR( valuE x ) {
	  return x*x;
  }




  inline valuE sqrT( valuE x ) {
	  return x >= 0.0 ? pow( x, (valuE)0.5 ) : 0.0;
  }




  inline valuE poW( valuE x, valuE y ) {
	  return pow( x, y );
  }




  inline valuE clamP( valuE x, valuE min, valuE max ) { 
      if( x < min ) return min; else if( x > max ) return max; else return x; 
  }




  inline valuE flooR( valuE x ) {
      return floor( x );
  }




  inline valuE ceiL( valuE x ) {
      return ceil( x );
  }




  inline valuE rounD( valuE x ) {
	  return x-(long)x < 0.5 ? (long)x : (long)x+1;
  }




  inline valuE moD( valuE x, valuE y ) {
	  return fmod( x, y );
  }




  inline valuE steP( valuE x, valuE min ) {
      return x < min ? 0.0 : 1.0;
  }




  inline valuE smoothsteP( valuE x, valuE min, valuE max ) {
      if( x <= min ) return 0.0; else 
      if( x >= max ) return 1.0; else {
      	  valuE x_ = ( x-min )/( max-min );

          return abs( max-min ) < EPSILON ? 0.0 : ( 3.0*x_*x_-2.0*x_*x_*x_ );
      }
  }




  inline valuE randomvaluE( valuE min, valuE max ) {
      return min+( max-min )*( ( rand() % 32001 )*0.00003125 );
  }




  inline valuE gaussrandomvaluE( valuE min, valuE max, DWORD n ) {
	  valuE a = 0.0;

	  for( register DWORD i = 0;  i < n;  i++ ) a += randomvaluE( min, max );
      
	  return a/n;
  }



/*
  inline valuE ran1( long *idum ) {  // "Minimal" random number generator of Park and Miller with Bays-Durham shuffle and added safeguards. 
      int j;
      long k;
      static long iy = 0;
      static long iv[32];
      valuE temp;

      if( *idum <= 0 || !iy ) {  // Initialize.
          if( -( *idum ) < 1 ) *idum = 1;  // Be sure to prevent idum = 0.
          else *idum = -( *idum );

          for( j = 32+7; j >= 0;  j-- ) {  // Load the shuffle table (after 8 warm-ups).
              k = ( *idum )/127773;
              *idum = 16807*( *idum-k*127773 )-2836*k;
              if( *idum < 0 ) *idum += 2147483647;
              if( j < 32 ) iv[j] = *idum;
          }
          iy = iv[0];
      }

      k = ( *idum )/127773;  // Start here when not initializing.
      *idum = 16807*( *idum-k*127773 )-2836*k;  // Compute idnum = ( 16807*idnum ) % 2147483647 without over-flows by Schrage's method.
	  if( *idum < 0 ) *idum += 2147483647;
	  j = iy/( 1+( 2147483647-1 )/32 );  // Will be in the range 0..NTAB-1.
      iy = iv[j];  // Output previously stored value and refill the shuffle table. 
	  iv[j] = *idum;

      if( ( temp = ( 1.0/2147483647 )*iy ) > ( 1.0-EPSILON ) ) return ( 1.0-EPSILON );  // Because users don’t expect endpoint values.
      else return temp;
  }




  inline valuE gammln( valuE xx ) {  // Returns the value ln[gamma(xx)] for xx > 0.
      int j;
      double ser, stp, tmp, x, y, cof[6];  // Internal arithmetic will be done in double precision, a nicety that you can omit if five-figure accuracy is good enough.
      
	  SAVE cof,stp;
      DATA cof,stp/76.18009172947146d0,-86.50532032941677d0, * 24.01409824083091d0,-1.231739572450155d0,.1208650973866179d-2, * -.5395239384953d-5,2.5066282746310005d0/;
      x = xx;
      y = x;
      tmp = x+5.5d0;
      tmp = ( x+0.5d0 )*loG( tmp )-tmp;
      ser = 1.000000000190015d0;
      do 11 j=1,6
          y=y+1.d0
          ser=ser+cof(j)/y
      enddo 11

	  return tmp+loG( stp*ser/x );
  }




  inline valuE poissonrandomvaluE( valuE xm, long *idum ) {  // Returns as a floating-point number an integer value that is a random deviate drawn from a Poisson distribution of mean xm, using ran1(idum) as a source of uniform random deviates.
      static valuE sq, alxm, g, oldm = -1.0;  // oldm is a flag for whether xm has changed since last call. 
	  valuE em, t, y;

      if( xm < 12.0 ) {  // Use direct method.
          if( xm != oldm ) {
              oldm = xm;
              g = exP( -xm );  // If xm is new, compute the exponential.
          }
          em = -1;
          t = 1.0;
          do {  // Instead of adding exponential deviates it is equivalent to multiply uniform deviates. We never actually have to take the log, merely compare to the pre-computed exponential.
              ++em;
              t *= ran1( idum );
          } while( t > g );
      } else {  // Use rejection method.
          if( xm != oldm ) {  // If xm has changed since the last call, then precompute some functions that occur below. oldm=xm;
              sq = sqrT( 2.0*xm );
              alxm = loG( xm );
              g = xm*alxm-gammlN( xm+1.0 );  // The function gammln is the natural log of the gamma function.
          }
          do {
              do {  // y is a deviate from a Lorentzian comparison function.
                  y = tan( PI*ran1( idum ) );
                  em = sq*y+xm;  // em is y, shifted and scaled.
              } while( em < 0.0 );  // Reject if in regime of zero probability.
              em = flooR( em );  // The trick for integer-valued distributions.
              t = 0.9*( 1.0+y*y )*exP( em*alxm-gammlN( em+1.0 )-g );  // The ratio of the desired distribution to the comparison function; we accept or reject by comparing it to another uniform deviate. The factor 0.9 is chosen so that t never exceeds 1.
          } while( ran1( idum ) > t );
      }

      return em;
  }
*/



  inline valuE diV( valuE x, valuE y, valuE c ) {
	  return abs( y ) < EPSILON ? c : x/y; 
  }




  inline valuE loG( valuE x ) {  // base 10
	  return x < EPSILON ? -INFINITY : log10( x );
  }




  inline valuE lG( valuE x ) {  // base e
	  return x < EPSILON ? -INFINITY : log( x );
  }




  inline valuE lN( valuE x ) {  // base e
	  return x < EPSILON ? -INFINITY : log( x );
  }




  inline valuE exP( valuE x ) {
	  return pow( (valuE)EULER_NUMBER, x );
  }




  inline valuE sinH( valuE x ) {
	  return ( exP( x )-exP( -x ) )*0.5;
  }




  inline valuE cosH( valuE x ) {
	  return ( exP( x )+exP( -x ) )*0.5;
  }




  inline valuE arctanH( valuE x ) {
	  return x < -1.0 || x > 1.0 ? 0.5*log( ( 1.0+x )/( 1.0-x ) ) : 0.0;
  }




  inline valuE arccotH( valuE x ) {
	  return x < -1.0 || x > 1.0 ? 0.5*log( ( x+1.0 )/( x-1.0 ) ) : 0.0;
  }




  inline valuE erF( valuE x ) { // error function
	  return 1.0-erfC( x );
  }




  inline valuE erfC( valuE x ) { // complementary error function
	  // the parameters of the Chebyshev fit
      valuE a1 = -1.26551223, a2 = 1.00002368, a3 = 0.37409196, a4 = 0.09678418, a5 = -0.18628806, 
		    a6 = 0.27886807, a7 = -1.13520398, a8 = 1.48851587, a9 = -0.82215223, a10 = 0.17087277,
	        val = 1.0, z = abs( x ), t;

      if( z <= EPSILON ) return val; // erfc( 0.0 ) = 1.0

	  t = 1.0/( 1.0+0.5*z );
      val = t*exP( -z*z+a1+t*( a2+t*( a3+t*( a4+t*( a5+t*( a6+t*( a7+t*( a8+t*( a9+t*a10 ) ) ) ) ) ) ) ) );

      if( x < 0.0 ) val = 2.0-val; // erfc( -x ) = 2.0-erfc( x )

      return val;
  }




  inline valuE gaussiaN( valuE x, valuE y, valuE s ) {
	  valuE val = diV( 1.0, sqR( s ), INFINITY );

	  return exP( -( sqR( x )+sqR( y ) )*val )*INV_PI*val;
  }




  inline valuE lerP( valuE x, valuE yA, valuE yB, valuE xA, valuE xB ) {
	  return abs( xB-xA ) < EPSILON ? 0.0 : yA+( yB-yA )*( ( x-xA )/( xB-xA ) );
  }




  inline valuE herminterP( valuE x, valuE yA, valuE yB, valuE xA, valuE xB ) {
	  valuE x_ = ( x-xA )/( xB-xA );

	  return abs( xB-xA ) < EPSILON ? 0.0 : yA+( 3.0*x_*x_-2.0*x_*x_*x_ )*( yB-yA );
  }




  inline valuE lerP( valuE x, valuE y, valuE zA, valuE zB, valuE zC, valuE zD, valuE xA, valuE yA, valuE xC, valuE yC ) {
	  return lerP( y, lerP( x, zA, zB, xA, xC ), lerP( x, zD, zC, xA, xC ), yA, yC );
  }




  inline valuE herminterP( valuE x, valuE y, valuE zA, valuE zB, valuE zC, valuE zD, valuE xA, valuE yA, valuE xC, valuE yC ) {
	  return herminterP( y, herminterP( x, zA, zB, xA, xC ), herminterP( x, zD, zC, xA, xC ), yA, yC );
  }








  // VALUEARRAY
  class valuearraY: public arraY<valuE> {};


  void sortasC( valuearraY *vala );
  void sortdesC( valuearraY *vala );






  void sortasC( valuearraY *vala ) {
      register DWORD i;
      BOOL sorted = FALSE;
      DWORD j = 1;
      valuE val;

      while( !sorted ) {
          sorted = TRUE;
          for( i = 0;  i < vala->num-j;  i++ ) {
              if( vala->elem[i] > vala->elem[i+1] ) {
                  val = vala->elem[i];
                  vala->elem[i] = vala->elem[i+1];
                  vala->elem[i+1] = val;
                  sorted = FALSE;
              }
          }
          j++;
      }
  }




  void sortdesC( valuearraY *vala ) {
      register DWORD i;
      BOOL sorted = FALSE;
      DWORD j = 1;
      valuE val;

      while( !sorted ) {
          sorted = TRUE;
          for( i = 0;  i < vala->num-j;  i++ ) {
              if( vala->elem[i] < vala->elem[i+1] ) {
                  val = vala->elem[i];
                  vala->elem[i] = vala->elem[i+1];
                  vala->elem[i+1] = val;
                  sorted = FALSE;
              }
          }
          j++;
      }
  }
