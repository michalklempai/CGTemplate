
  #undef WHITE
  #undef BLACK
  #undef RED
  #undef GREEN
  #undef BLUE
  #undef CYAN
  #undef MAGENTA
  #undef YELLOW
  #undef GRAY

  #define WHITE coloR( 1.0, 1.0, 1.0, 0.0 )
  #define BLACK coloR( 0.0, 0.0, 0.0, 0.0 )
  #define RED coloR( 1.0, 0.0, 0.0, 0.0 )
  #define GREEN coloR( 0.0, 1.0, 0.0, 0.0 )
  #define BLUE coloR( 0.0, 0.0, 1.0, 0.0 )
  #define CYAN coloR( 0.0, 1.0, 1.0, 0.0 )
  #define MAGENTA coloR( 1.0, 0.0, 1.0, 0.0 )
  #define YELLOW coloR( 1.0, 1.0, 0.0, 0.0 )
  #define GRAY coloR( 0.5, 0.5, 0.5, 0.0 )








  // COLOR
  class coloR {
      public:
          valuE r, g, b, a; 


          coloR( void );
          coloR( DWORD argb );
          coloR( valuE r, valuE g, valuE b, valuE a );
          coloR( const coloR& c );

          operator DWORD( void ) const;

          coloR operator+( void ) const;
          coloR operator-( void ) const;

          coloR operator*( valuE val ) const;
          friend coloR operator*( valuE val, const coloR& c );
          coloR operator/( valuE val ) const;
          coloR& operator*=( valuE val );
          coloR& operator/=( valuE val );

		  coloR operator+( const coloR& c ) const;
          coloR operator-( const coloR& c ) const;
          coloR operator*( const coloR& c ) const;
		  coloR& operator+=( const coloR& c );
          coloR& operator-=( const coloR& c );
          coloR& operator*=( const coloR& c );
		  BOOL operator==( const coloR& c ) const;
          BOOL operator!=( const coloR& c ) const;
  };


  inline valuE getI( const coloR& c );
  inline coloR clamP( const coloR& c, valuE a = 0.0, valuE b = 1.0 ); 
  inline coloR miX( valuE x, const coloR& cA, const coloR& cB );
  inline coloR lerP( valuE x, const coloR& cA, const coloR& cB );
  inline coloR herminterP( valuE x, const coloR& cA, const coloR& cB );
  inline coloR cubicbezierinterP( valuE x, const coloR& c0, const coloR& c1, const coloR& c2, const coloR& c3 );
  inline coloR lerP( valuE x, valuE y, const coloR& cA, const coloR& cB, const coloR& cC, const coloR& cD );
  inline coloR herminterP( valuE x, valuE y, const coloR& cA, const coloR& cB, const coloR& cC, const coloR& cD );
  inline coloR cubicbezierinterP( valuE x, valuE y, const coloR& c00, const coloR& c10, const coloR& c20, const coloR& c30, const coloR& c01, const coloR& c11, const coloR& c21, const coloR& c31, const coloR& c02, const coloR& c12, const coloR& c22, const coloR& c32, const coloR& c03, const coloR& c13, const coloR& c23, const coloR& c33 );
  inline coloR rgb_hsV( const coloR& rgb );
  inline coloR hsv_rgB( const coloR& hsv );
  inline void rgb_spectruM( const coloR& rgb, DWORD dw, valuearraY *spec );
  inline coloR spectrum_rgB( valuearraY *spec );
  inline valuE getspectrumvaluE( valuE lambda, valuearraY *vala, valuE *val = NULL );
  BOOL loadspectruM( char filename[512], valuearraY *spec );  // 380-720nm
  inline void rendergL( valuearraY *spec );






  inline coloR::coloR( void ) {
      r = g = b = a = 0.0;
  }




  inline coloR::coloR( DWORD argb ) {
      r = INV_255*(valuE)(unsigned char)( argb >> 16 );
      g = INV_255*(valuE)(unsigned char)( argb >> 8 );
      b = INV_255*(valuE)(unsigned char)( argb >> 0 );
      a = INV_255*(valuE)(unsigned char)( argb >> 24 );
  }




  inline coloR::coloR( valuE r, valuE g, valuE b, valuE a ) {
      this->r = r;  this->g = g;  this->b = b;  this->a = a;
  }




  inline coloR::coloR( const coloR& c ) {
      r = c.r;  g = c.g;  b = c.b;  a = c.a;
  }




  inline coloR::operator DWORD( void ) const {
      DWORD dwR = r >= 1.0 ? 0xff : r <= 0.0 ? 0x00 : (DWORD)( r*255.0+0.5 );
      DWORD dwG = g >= 1.0 ? 0xff : g <= 0.0 ? 0x00 : (DWORD)( g*255.0+0.5 );
      DWORD dwB = b >= 1.0 ? 0xff : b <= 0.0 ? 0x00 : (DWORD)( b*255.0+0.5 );
      DWORD dwA = a >= 1.0 ? 0xff : a <= 0.0 ? 0x00 : (DWORD)( a*255.0+0.5 );

      return ( dwA << 24 ) | ( dwR << 16 ) | ( dwG << 8 ) | dwB;
  }




  inline coloR coloR::operator+( void ) const {
      return *this;
  }




  inline coloR coloR::operator-( void ) const {
      return coloR( -r, -g, -b, -a );  
  }




  inline coloR coloR::operator*( valuE val ) const {
      return coloR( r*val, g*val, b*val, a*val );
  }




  inline coloR operator*( valuE val, const coloR& c ) {
      return coloR( val*c.r, val*c.g, val*c.b, val*c.a );
  }




  inline coloR coloR::operator/( valuE val ) const {
      if( abs( val ) > EPSILON ) {
    	  valuE inv_val = 1.0/val;

          return coloR( r*inv_val, g*inv_val, b*inv_val, a*inv_val );
      } else return coloR();
  }




  inline coloR& coloR::operator*=( valuE val ) {
      r*=val;  g*=val;  b*=val;  a*=val;

      return *this;
  }




  inline coloR& coloR::operator/=( valuE val ) {
      if( abs( val ) > EPSILON ) {
    	  valuE inv_val = 1.0/val;

          r*=inv_val;  g*=inv_val;  b*=inv_val;  a*=inv_val;
      }
      
      return *this;
  }




  inline coloR coloR::operator+( const coloR& c ) const {
      return coloR( r+c.r, g+c.g, b+c.b, a+c.a );
  }




  inline coloR coloR::operator-( const coloR& c ) const {
      return coloR( r-c.r, g-c.g, b-c.b, a-c.a );
  }




  inline coloR coloR::operator*( const coloR& c ) const {
      return coloR( r*c.r, g*c.g, b*c.b, a*c.a );
  }




  inline coloR& coloR::operator+=( const coloR& c ) {
      r+=c.r;  g+=c.g;  b+=c.b;  a+=c.a;

      return *this;
  }




  inline coloR& coloR::operator-=( const coloR& c ) {
      r-=c.r;  g-=c.g;  b-=c.b;  a-=c.a;

      return *this;
  }




  inline coloR& coloR::operator*=( const coloR& c ) {
      r *= c.r;  g *= c.g;  b *= c.b;  a *= c.a;

      return *this;
  }
  
  
  
  
  inline BOOL coloR::operator==( const coloR& c ) const {
      return r == c.r && g == c.g && b == c.b && a == c.a;
  }




  inline BOOL coloR::operator!=( const coloR& c ) const {
      return r != c.r || g != c.g || b != c.b || a != c.a;
  }




  inline valuE getI( const coloR& c ) {
//	  return 0.299*c.r+0.587*c.g+0.114*c.b;
	  return 0.2125*c.r+0.7154*c.g+0.0721*c.b;
  }




  inline coloR clamP( const coloR& c, valuE a, valuE b ) { 
   	  return coloR( clamP( c.r, a, b ), clamP( c.g, a, b ), clamP( c.b, a, b ), clamP( c.a, a, b ) );
  }




  inline coloR miX( valuE x, const coloR& cA, const coloR& cB ) {
	  return (valuE)( 1.0-x )*cA+x*cB;
  }
  
  
  
  
  inline coloR lerP( valuE x, const coloR& cA, const coloR& cB ) {
	  return cA+( cB-cA )*x;
  }




  inline coloR herminterP( valuE x, const coloR& cA, const coloR& cB ) {
	  return cA+( cB-cA )*(valuE)( 3.0*x*x-2.0*x*x*x );
  }




  inline coloR cubicbezierinterP( valuE x, const coloR& c0, const coloR& c1, const coloR& c2, const coloR& c3 ) {
	  valuE u = 1.0/3.0*( 1.0+x );
	  coloR c;
	  poinT A, B, P[4], W, left[4], right[4];


	  // red
	  // interpolation
	  A = 4.5*poinT( 0.0, c1.r, 0.0 )-4.0/3.0*poinT( -1.0, c0.r, 0.0 )-2.0/3.0*poinT( 2.0, c3.r, 0.0 );
	  B = 4.5*poinT( 1.0, c2.r, 0.0 )-2.0/3.0*poinT( -1.0, c0.r, 0.0 )-4.0/3.0*poinT( 2.0, c3.r, 0.0 );
	  P[0] = poinT( -1.0, c0.r, 0.0 );
	  P[1] = poinT( 2.0*A.x-B.x, 2.0*A.y-B.y, 2.0*A.z-B.z )/3.0;
	  P[2] = poinT( A.x-2.0*P[1].x, A.y-2.0*P[1].y, A.z-2.0*P[1].z );
	  P[3] = poinT( 2.0, c3.r, 0.0 );

	  // deCasteljau
      left[0] = P[0];
      left[1] = P[0]+u*( P[1]-P[0] );
      W = P[1]+u*( P[2]-P[1] );
      left[2] = left[1]+u*( W-left[1] ); 
      right[3] = P[3];
      right[2] = P[2]+u*( P[3]-P[2] );
      right[1] = W+u*( right[2]-W );

      c.r = left[2].y+u*( right[1].y-left[2].y ); 

	  // green
	  // interpolation
	  A = 4.5*poinT( 0.0, c1.g, 0.0 )-4.0/3.0*poinT( -1.0, c0.g, 0.0 )-2.0/3.0*poinT( 2.0, c3.g, 0.0 );
	  B = 4.5*poinT( 1.0, c2.g, 0.0 )-2.0/3.0*poinT( -1.0, c0.g, 0.0 )-4.0/3.0*poinT( 2.0, c3.g, 0.0 );
	  P[0] = poinT( -1.0, c0.g, 0.0 );
	  P[1] = poinT( 2.0*A.x-B.x, 2.0*A.y-B.y, 2.0*A.z-B.z )/3.0;
	  P[2] = poinT( A.x-2.0*P[1].x, A.y-2.0*P[1].y, A.z-2.0*P[1].z );
	  P[3] = poinT( 2.0, c3.g, 0.0 );

	  // deCasteljau
      left[0] = P[0];
      left[1] = P[0]+u*( P[1]-P[0] );
      W = P[1]+u*( P[2]-P[1] );
      left[2] = left[1]+u*( W-left[1] ); 
      right[3] = P[3];
      right[2] = P[2]+u*( P[3]-P[2] );
      right[1] = W+u*( right[2]-W );

      c.g = left[2].y+u*( right[1].y-left[2].y ); 

	  // blue
	  // interpolation
	  A = 4.5*poinT( 0.0, c1.b, 0.0 )-4.0/3.0*poinT( -1.0, c0.b, 0.0 )-2.0/3.0*poinT( 2.0, c3.b, 0.0 );
	  B = 4.5*poinT( 1.0, c2.b, 0.0 )-2.0/3.0*poinT( -1.0, c0.b, 0.0 )-4.0/3.0*poinT( 2.0, c3.b, 0.0 );
	  P[0] = poinT( -1.0, c0.b, 0.0 );
	  P[1] = poinT( 2.0*A.x-B.x, 2.0*A.y-B.y, 2.0*A.z-B.z )/3.0;
	  P[2] = poinT( A.x-2.0*P[1].x, A.y-2.0*P[1].y, A.z-2.0*P[1].z );
	  P[3] = poinT( 2.0, c3.b, 0.0 );

	  // deCasteljau
      left[0] = P[0];
      left[1] = P[0]+u*( P[1]-P[0] );
      W = P[1]+u*( P[2]-P[1] );
      left[2] = left[1]+u*( W-left[1] ); 
      right[3] = P[3];
      right[2] = P[2]+u*( P[3]-P[2] );
      right[1] = W+u*( right[2]-W );

      c.b = left[2].y+u*( right[1].y-left[2].y ); 


	  return c;
  }




  inline coloR lerP( valuE x, valuE y, const coloR& cA, const coloR& cB, const coloR& cC, const coloR& cD ) {
	  return lerP( y, lerP( x, cA, cB ), lerP( x, cD, cC ) );
  }




  inline coloR herminterP( valuE x, valuE y, const coloR& cA, const coloR& cB, const coloR& cC, const coloR& cD ) {
	  return herminterP( y, herminterP( x, cA, cB ), herminterP( x, cD, cC ) );
  }




  inline coloR cubicbezierinterP( valuE x, valuE y, const coloR& c00, const coloR& c10, const coloR& c20, const coloR& c30, const coloR& c01, const coloR& c11, const coloR& c21, const coloR& c31, const coloR& c02, const coloR& c12, const coloR& c22, const coloR& c32, const coloR& c03, const coloR& c13, const coloR& c23, const coloR& c33 ) {
	  return cubicbezierinterP( y, cubicbezierinterP( x, c00, c10, c20, c30 ), cubicbezierinterP( x, c01, c11, c21, c31 ), cubicbezierinterP( x, c02, c12, c22, c32 ), cubicbezierinterP( x, c03, c13, c23, c33 ) );
  }




  inline coloR rgb_hsV( const coloR& rgb ) {
      valuE min, max, delta;
      coloR hsv;

      min = min( rgb.r, min( rgb.g, rgb.b ) );
      max = max( rgb.r, max( rgb.g, rgb.b ) );
      hsv.b = max;
      if( max == 0.0 ) hsv.g = 0.0; else hsv.g = ( max-min )/max;

      if( hsv.g == 0.0 ) {
          hsv.r = -1.0; // hsv.r = UNDEF
      } else {
          delta = max-min;
          if( rgb.r == max ) hsv.r = ( rgb.g-rgb.b )/delta; else
          if( rgb.g == max ) hsv.r = 2.0+( rgb.b-rgb.r )/delta; else hsv.r = 4.0+( rgb.r-rgb.g )/delta;
          hsv.r*=60.0;
          if( hsv.r < 0.0 ) hsv.r+=360.0;
      }
      hsv.a = rgb.a;
      
      return hsv;
  }




  inline coloR hsv_rgB( const coloR& hsv ) {
      long i;
      valuE f, p, q, t;
      coloR rgb;

      if( hsv.g == 0.0 ) { // hsv.r = UNDEF
          rgb = coloR( hsv.b, hsv.b, hsv.b, hsv.a );
      } else {
          i = (long)flooR( hsv.r*0.01666666 );
          f = hsv.r*0.01666666-i;
          p = hsv.b*( 1.0-hsv.g );
          q = hsv.b*( 1.0-( hsv.g*f ) );
          t = hsv.b*( 1.0-( hsv.g*( 1.0-f ) ) );
          switch( i ) {
              case 0: rgb = coloR( hsv.b, t, p, hsv.a ); break;
              case 1: rgb = coloR( q, hsv.b, p, hsv.a ); break;
              case 2: rgb = coloR( p, hsv.b, t, hsv.a ); break;
              case 3: rgb = coloR( p, q, hsv.b, hsv.a ); break;
              case 4: rgb = coloR( t, p, hsv.b, hsv.a ); break;
              case 5: rgb = coloR( hsv.b, p, q, hsv.a ); break;
          }
      }

      return rgb;
  }




  inline void rgb_spectruM( const coloR& rgb, DWORD dw, valuearraY *spec ) {
	  register long i;
	  valuE val, val2, val3;
	  valuE whiteSpec[10] = { 1.0, 1.0, 0.9999, 0.9993, 0.9992, 0.9998, 1.0, 1.0, 1.0, 1.0 }, 
		    cyanSpec[10] = { 0.971, 0.9426, 1.0007, 1.0007, 1.0007, 1.0007, 0.1564, 0.0, 0.0, 0.0 }, 
			magentaSpec[10] = { 1.0, 1.0, 0.9685, 0.2229, 0.0, 0.0458, 0.8369, 1.0, 1.0, 0.9959 }, 
			yellowSpec[10] = { 0.0001, 0.0, 0.1088, 0.6651, 1.0, 1.0, 0.9996, 0.9586, 0.9685, 0.9840 }, 
			redSpec[10] = { 0.1012, 0.0515, 0.0, 0.0, 0.0, 0.0, 0.8325, 1.0149, 1.0149, 1.0149 }, 
			greenSpec[10] = { 0.0, 0.0, 0.0273, 0.7937, 1.0, 0.9418, 0.1719, 0.0, 0.0, 0.0025 }, 
			blueSpec[10] = { 1.0, 1.0, 0.8916, 0.3323, 0.0, 0.0, 0.0003, 0.0369, 0.0483, 0.0496 };

	  spec->deletealL();

	  spec->inserT( -1, 0.0, dw );
	  if( rgb.r <= rgb.g && rgb.r <= rgb.b ) {
		  for( i = 0;  i < spec->num;  i++ ) {
			  val = ( (valuE)i/(valuE)( spec->num-1 ) )*9.0;
			  spec->elem[i] += rgb.r*lerP( val-(long)val, whiteSpec[(long)val], whiteSpec[min( (long)val+1, 9 )] );
		  }
	
		  if( rgb.g <= rgb.b ) {
			  val = rgb.g-rgb.r;
			  val2 = rgb.b-rgb.g;
			  for( i = 0;  i < spec->num;  i++ ) {
				  val3 = ( (valuE)i/(valuE)( spec->num-1 ) )*9.0;
				  spec->elem[i] += val*lerP( val3-(long)val3, cyanSpec[(long)val3], cyanSpec[min( (long)val3+1, 9 )] ) + 
					               val2*lerP( val3-(long)val3, blueSpec[(long)val3], blueSpec[min( (long)val3+1, 9 )] );
			  }
		  } else {
			  val = rgb.b-rgb.r;
			  val2 = rgb.g-rgb.b;
			  for( i = 0;  i < spec->num;  i++ ) {
				  val3 = ( (valuE)i/(valuE)( spec->num-1 ) )*9.0;
				  spec->elem[i] += val*lerP( val3-(long)val3, cyanSpec[(long)val3], cyanSpec[min( (long)val3+1, 9 )] ) + 
					               val2*lerP( val3-(long)val3, greenSpec[(long)val3], greenSpec[min( (long)val3+1, 9 )] );
			  }
		  }
	  } else
	  if( rgb.g <= rgb.r && rgb.g <= rgb.b ) {
		  for( i = 0;  i < spec->num;  i++ ) {
			  val = ( (valuE)i/(valuE)( spec->num-1 ) )*9.0;
			  spec->elem[i] += rgb.g*lerP( val-(long)val, whiteSpec[(long)val], whiteSpec[min( (long)val+1, 9 )] );
		  }
	
		  if( rgb.r <= rgb.b ) {
			  val = rgb.r-rgb.g;
			  val2 = rgb.b-rgb.r;
			  for( i = 0;  i < spec->num;  i++ ) {
				  val3 = ( (valuE)i/(valuE)( spec->num-1 ) )*9.0;
				  spec->elem[i] += val*lerP( val3-(long)val3, magentaSpec[(long)val3], magentaSpec[min( (long)val3+1, 9 )] ) + 
					               val2*lerP( val3-(long)val3, blueSpec[(long)val3], blueSpec[min( (long)val3+1, 9 )] );
			  }
		  } else {
			  val = rgb.b-rgb.g;
			  val2 = rgb.r-rgb.b;
			  for( i = 0;  i < spec->num;  i++ ) {
				  val3 = ( (valuE)i/(valuE)( spec->num-1 ) )*9.0;
				  spec->elem[i] += val*lerP( val3-(long)val3, magentaSpec[(long)val3], magentaSpec[min( (long)val3+1, 9 )] ) + 
					               val2*lerP( val3-(long)val3, redSpec[(long)val3], redSpec[min( (long)val3+1, 9 )] );
			  }
		  }
	  } else { // rgb.b <= rgb.r && rgb.b <= rgb.g
		  for( i = 0;  i < spec->num;  i++ ) {
			  val = ( (valuE)i/(valuE)( spec->num-1 ) )*9.0;
			  spec->elem[i] += rgb.b*lerP( val-(long)val, whiteSpec[(long)val], whiteSpec[min( (long)val+1, 9 )] );
		  }
	
		  if( rgb.r <= rgb.g ) {
			  val = rgb.r-rgb.b;
			  val2 = rgb.g-rgb.r;
			  for( i = 0;  i < spec->num;  i++ ) {
				  val3 = ( (valuE)i/(valuE)( spec->num-1 ) )*9.0;
				  spec->elem[i] += val*lerP( val3-(long)val3, yellowSpec[(long)val3], yellowSpec[min( (long)val3+1, 9 )] ) + 
					               val2*lerP( val3-(long)val3, greenSpec[(long)val3], greenSpec[min( (long)val3+1, 9 )] );
			  }
		  } else {
			  val = rgb.g-rgb.b;
			  val2 = rgb.r-rgb.g;
			  for( i = 0;  i < spec->num;  i++ ) {
				  val3 = ( (valuE)i/(valuE)( spec->num-1 ) )*9.0;
				  spec->elem[i] += val*lerP( val3-(long)val3, yellowSpec[(long)val3], yellowSpec[min( (long)val3+1, 9 )] ) + 
					               val2*lerP( val3-(long)val3, redSpec[(long)val3], redSpec[min( (long)val3+1, 9 )] );
			  }
		  }
	  }
  }




  inline coloR spectrum_rgB( valuearraY *spec ) { // spec obsahuje hodnoty spektra pre lambda od 380-720nm
	  register long i;
	  valuE val, lambda, k, x, y, z, X, Y, Z;
	  ciexyz31 xyz;

	  k = X = Y = Z = 0.0;
	  val = diV( 720.0-380.0, spec->num-1, 0.0 ); // uroven delenia
	  for( i = 0;  i < spec->num;  i++ ) {
		  lambda = 380.0+i*val;

		  xyz.getxyZ( lambda, &x, &y, &z );
		  k += y;
		  X += spec->elem[i]*x;
		  Y += spec->elem[i]*y;
		  Z += spec->elem[i]*z;
	  }
	  val *= 0.001;
	  k *= val;  X *= val;  Y *= val;  Z *= val;
	  k = 1.0/k;
	  X *= k;  Y *= k;  Z *= k;

	  return coloR( 3.241*X-1.5374*Y-0.4986*Z, -0.9692*X+1.876*Y+0.0416*Z, 0.0556*X-0.204*Y+1.057*Z, 0.0 );
  }




  inline valuE getspectrumvaluE( valuE lambda, valuearraY *vala, valuE *val ) {
	  register long i;
	  valuE val_;


	  if( vala->num == 1 ) {
		  val_ = vala->elem[0];
	  } else 
	  if( vala->num > 1 ) {
		  if( lambda <= 0.38 ) { // extrapolacia
			  val_ = lerP( lambda, vala->elem[0], vala->elem[1], 0.38, 0.38+( 0.72-0.38 )/( vala->num-1 ) );
		  } else 
		  if( lambda >= 0.72 ) { // extrapolacia
			  val_ = lerP( lambda, vala->elem[vala->num-2], vala->elem[vala->num-1], 0.72-( 0.72-0.38 )/( vala->num-1 ), 0.72 );
		  } else { // interpolacia
			  i = 1;
			  while( i < vala->num && lambda > 0.38+i*( ( 0.72-0.38 )/( vala->num-1 ) ) ) i++;

			  val_ = lerP( lambda, vala->elem[i-1], vala->elem[i], 0.38+( i-1 )*( ( 0.72-0.38 )/( vala->num-1 ) ), 0.38+i*( ( 0.72-0.38 )/( vala->num-1 ) ) );
		  }
	  }

	  
	  if( val != NULL ) *val = val_;


	  return val_;
  }




  BOOL loadspectruM( char filename[512], valuearraY *spec ) {  // 380-720nm
	  char str[128];
      FILE *file;
	  

	  spec->deletealL();

	  if( !( file = fopen( filename, "rt" ) ) ) return FALSE;

	  while( !feof( file ) ) {
		  ZeroMemory( &str[0], sizeof( str ) );
		  fscanf( file, "%s", str );
		  spec->inserT( -1, atof( &str[0] ) );		  	
	  }

      fclose( file );  


	  return TRUE;
  }




  inline void rendergL( valuearraY *spec ) {
      register long i, j;
	  valuE val;
	  coloR c;
	  RECT rc;
	  valuearraY vala;


      glMatrixMode( GL_MODELVIEW );
      glPushMatrix();
      glLoadIdentity();

      glMatrixMode( GL_PROJECTION );
      glPushMatrix();
      glLoadIdentity();
      glOrtho( 0.0, 1.0, 0.0, 1.0, -10000, 10000 );


	  rc.left = rc.top = 0;  
	  rc.right = rc.bottom = 1; 


	  glBegin( GL_LINES );
		  // horizontal
		  glColor3f( 0.35, 0.35, 0.35 );
	      glVertex2f( 0.1, 0.9 );
	      glVertex2f( 0.9, 0.9 );
		  glColor3f( 0.15, 0.15, 0.15 );
	      glVertex2f( 0.1, 0.5 );
	      glVertex2f( 0.9, 0.5 );
		  glColor3f( 0.1, 0.1, 0.1 );
	      glVertex2f( 0.1, 0.3 );
	      glVertex2f( 0.9, 0.3 );
	      glVertex2f( 0.1, 0.7 );
	      glVertex2f( 0.9, 0.7 );
		  glColor3f( 0.075, 0.075, 0.075 );
	      glVertex2f( 0.1, 0.2 );
	      glVertex2f( 0.9, 0.2 );
	      glVertex2f( 0.1, 0.4 );
	      glVertex2f( 0.9, 0.4 );
	      glVertex2f( 0.1, 0.6 );
	      glVertex2f( 0.9, 0.6 );
	      glVertex2f( 0.1, 0.8 );
	      glVertex2f( 0.9, 0.8 );

		  // vertical
		  glColor3f( 0.075, 0.075, 0.075 );
	      glVertex2f( 0.1, 0.1 );
	      glVertex2f( 0.1, 0.9 );
	      glVertex2f( 0.3, 0.1 );
	      glVertex2f( 0.3, 0.9 );
	      glVertex2f( 0.5, 0.1 );
	      glVertex2f( 0.5, 0.9 );
	      glVertex2f( 0.7, 0.1 );
	      glVertex2f( 0.7, 0.9 );
	      glVertex2f( 0.9, 0.1 );
	      glVertex2f( 0.9, 0.9 );
	  glEnd();


	  // spectrum
	  vala.inserT( -1, 0.0, 43 );
	  val = diV( 720.0-380.0, vala.num-1, 0.0 );  // uroven delenia
	  glBegin( GL_QUAD_STRIP );
	  for( i = 0;  i < vala.num;  i++ ) {
		  for( j = 0;  j < vala.num;  j++ ) vala.elem[j] = 0.0;
          vala.elem[i] = 1.0;
		  c = spectrum_rgB( &vala );	

		  glColor3f( c.r, c.g, c.b );

		  glVertex2f( 0.1+0.8*( (valuE)i/(valuE)( vala.num-1 ) ), 0.105 );	  
		  glVertex2f( 0.1+0.8*( (valuE)i/(valuE)( vala.num-1 ) ), 0.095 );	  
	  }
	  glEnd();
	

	  glLineWidth( 1.5 );
	  val = diV( 720.0-380.0, spec->num-1, 0.0 );  // uroven delenia
	  glBegin( GL_LINE_STRIP );
	  for( i = 0;  i < spec->num;  i++ ) {
		  glColor3f( randomvaluE(), randomvaluE(), randomvaluE() );
		  glVertex2f( 0.1+0.8*( (valuE)i/(valuE)( spec->num-1 ) ), 0.1+0.8*spec->elem[i] );	  
	  }
	  glEnd();
	  glLineWidth( 1.0 );


	  rendertexT( 0.03, 0.905, 255, 255, 255, 128, rc, "380nm" );
	  rendertexT( 0.905, 0.905, 255, 255, 255, 128, rc, "720nm" );
	  rendertexT( 0.91, 0.105, 255*0.35, 255*0.35, 255*0.35, 255, rc, "1.0" );
	  rendertexT( 0.91, 0.505, 255*0.15, 255*0.15, 255*0.15, 255, rc, "0.5" );
	  rendertexT( 0.3, 0.935, 255, 255, 255, 128, rc, "Color Spectrum Visualizer" );



      glPopMatrix();
      glMatrixMode( GL_MODELVIEW );
      glPopMatrix();
}

  






  // COLORARRAY
  class colorarraY: public arraY<coloR> {};
