
  // 2^e, exponent -128..127 
  valuE pow2_[256] = { 
	  poW( 2.0, -128.0 ), poW( 2.0, -127.0 ), poW( 2.0, -126.0 ), poW( 2.0, -125.0 ), poW( 2.0, -124.0 ), poW( 2.0, -123.0 ),
	  poW( 2.0, -122.0 ), poW( 2.0, -121.0 ), poW( 2.0, -120.0 ), poW( 2.0, -119.0 ), poW( 2.0, -118.0 ), poW( 2.0, -117.0 ),
	  poW( 2.0, -116.0 ), poW( 2.0, -115.0 ), poW( 2.0, -114.0 ), poW( 2.0, -113.0 ), poW( 2.0, -112.0 ), poW( 2.0, -111.0 ),
	  poW( 2.0, -110.0 ), poW( 2.0, -109.0 ), poW( 2.0, -108.0 ), poW( 2.0, -107.0 ), poW( 2.0, -106.0 ), poW( 2.0, -105.0 ),
	  poW( 2.0, -104.0 ), poW( 2.0, -103.0 ), poW( 2.0, -102.0 ), poW( 2.0, -101.0 ), poW( 2.0, -100.0 ), poW( 2.0, -99.0 ),
	  poW( 2.0, -98.0 ), poW( 2.0, -97.0 ), poW( 2.0, -96.0 ), poW( 2.0, -95.0 ), poW( 2.0, -94.0 ), poW( 2.0, -93.0 ),
	  poW( 2.0, -92.0 ), poW( 2.0, -91.0 ), poW( 2.0, -90.0 ), poW( 2.0, -89.0 ), poW( 2.0, -88.0 ), poW( 2.0, -87.0 ),
	  poW( 2.0, -86.0 ), poW( 2.0, -85.0 ), poW( 2.0, -84.0 ), poW( 2.0, -83.0 ), poW( 2.0, -82.0 ), poW( 2.0, -81.0 ),
	  poW( 2.0, -80.0 ), poW( 2.0, -79.0 ), poW( 2.0, -78.0 ), poW( 2.0, -77.0 ), poW( 2.0, -76.0 ), poW( 2.0, -75.0 ),
	  poW( 2.0, -74.0 ), poW( 2.0, -73.0 ), poW( 2.0, -72.0 ), poW( 2.0, -71.0 ), poW( 2.0, -70.0 ), poW( 2.0, -69.0 ),
	  poW( 2.0, -68.0 ), poW( 2.0, -67.0 ), poW( 2.0, -66.0 ), poW( 2.0, -65.0 ), poW( 2.0, -64.0 ), poW( 2.0, -63.0 ),
	  poW( 2.0, -62.0 ), poW( 2.0, -61.0 ), poW( 2.0, -60.0 ), poW( 2.0, -59.0 ), poW( 2.0, -58.0 ), poW( 2.0, -57.0 ),
	  poW( 2.0, -56.0 ), poW( 2.0, -55.0 ), poW( 2.0, -54.0 ), poW( 2.0, -53.0 ), poW( 2.0, -52.0 ), poW( 2.0, -51.0 ),
	  poW( 2.0, -50.0 ), poW( 2.0, -49.0 ), poW( 2.0, -48.0 ), poW( 2.0, -47.0 ), poW( 2.0, -46.0 ), poW( 2.0, -45.0 ),
	  poW( 2.0, -44.0 ), poW( 2.0, -43.0 ), poW( 2.0, -42.0 ), poW( 2.0, -41.0 ), poW( 2.0, -40.0 ), poW( 2.0, -39.0 ),
	  poW( 2.0, -38.0 ), poW( 2.0, -37.0 ), poW( 2.0, -36.0 ), poW( 2.0, -35.0 ), poW( 2.0, -34.0 ), poW( 2.0, -33.0 ),
	  poW( 2.0, -32.0 ), poW( 2.0, -31.0 ), poW( 2.0, -30.0 ), poW( 2.0, -29.0 ), poW( 2.0, -28.0 ), poW( 2.0, -27.0 ),
	  poW( 2.0, -26.0 ), poW( 2.0, -25.0 ), poW( 2.0, -24.0 ), poW( 2.0, -23.0 ), poW( 2.0, -22.0 ), poW( 2.0, -21.0 ),
	  poW( 2.0, -20.0 ), poW( 2.0, -19.0 ), poW( 2.0, -18.0 ), poW( 2.0, -17.0 ), poW( 2.0, -16.0 ), poW( 2.0, -15.0 ),
	  poW( 2.0, -14.0 ), poW( 2.0, -13.0 ), poW( 2.0, -12.0 ), poW( 2.0, -11.0 ), poW( 2.0, -10.0 ), poW( 2.0, -9.0 ),
	  poW( 2.0, -8.0 ), poW( 2.0, -7.0 ), poW( 2.0, -6.0 ), poW( 2.0, -5.0 ), poW( 2.0, -4.0 ), poW( 2.0, -3.0 ),
	  poW( 2.0, -2.0 ), poW( 2.0, -1.0 ), poW( 2.0, 0.0 ), poW( 2.0, 1.0 ), poW( 2.0, 2.0 ), poW( 2.0, 3.0 ),
	  poW( 2.0, 4.0 ), poW( 2.0, 5.0 ), poW( 2.0, 6.0 ), poW( 2.0, 7.0 ), poW( 2.0, 8.0 ), poW( 2.0, 9.0 ),
	  poW( 2.0, 10.0 ), poW( 2.0, 11.0 ), poW( 2.0, 12.0 ), poW( 2.0, 13.0 ), poW( 2.0, 14.0 ), poW( 2.0, 15.0 ),
	  poW( 2.0, 16.0 ), poW( 2.0, 17.0 ), poW( 2.0, 18.0 ), poW( 2.0, 19.0 ), poW( 2.0, 20.0 ), poW( 2.0, 21.0 ),
	  poW( 2.0, 22.0 ), poW( 2.0, 23.0 ), poW( 2.0, 24.0 ), poW( 2.0, 25.0 ), poW( 2.0, 26.0 ), poW( 2.0, 27.0 ),
	  poW( 2.0, 28.0 ), poW( 2.0, 29.0 ), poW( 2.0, 30.0 ), poW( 2.0, 31.0 ), poW( 2.0, 32.0 ), poW( 2.0, 33.0 ),
	  poW( 2.0, 34.0 ), poW( 2.0, 35.0 ), poW( 2.0, 36.0 ), poW( 2.0, 37.0 ), poW( 2.0, 38.0 ), poW( 2.0, 39.0 ),
	  poW( 2.0, 40.0 ), poW( 2.0, 41.0 ), poW( 2.0, 42.0 ), poW( 2.0, 43.0 ), poW( 2.0, 44.0 ), poW( 2.0, 45.0 ),
	  poW( 2.0, 46.0 ), poW( 2.0, 47.0 ), poW( 2.0, 48.0 ), poW( 2.0, 49.0 ), poW( 2.0, 50.0 ), poW( 2.0, 51.0 ),
	  poW( 2.0, 52.0 ), poW( 2.0, 53.0 ), poW( 2.0, 54.0 ), poW( 2.0, 55.0 ), poW( 2.0, 56.0 ), poW( 2.0, 57.0 ),
	  poW( 2.0, 58.0 ), poW( 2.0, 59.0 ), poW( 2.0, 60.0 ), poW( 2.0, 61.0 ), poW( 2.0, 62.0 ), poW( 2.0, 63.0 ),
	  poW( 2.0, 64.0 ), poW( 2.0, 65.0 ), poW( 2.0, 66.0 ), poW( 2.0, 67.0 ), poW( 2.0, 68.0 ), poW( 2.0, 69.0 ),
  	  poW( 2.0, 70.0 ), poW( 2.0, 71.0 ), poW( 2.0, 72.0 ), poW( 2.0, 73.0 ), poW( 2.0, 74.0 ), poW( 2.0, 75.0 ),
  	  poW( 2.0, 76.0 ), poW( 2.0, 77.0 ), poW( 2.0, 78.0 ), poW( 2.0, 79.0 ), poW( 2.0, 80.0 ), poW( 2.0, 81.0 ),
  	  poW( 2.0, 82.0 ), poW( 2.0, 83.0 ), poW( 2.0, 84.0 ), poW( 2.0, 85.0 ), poW( 2.0, 86.0 ), poW( 2.0, 87.0 ),
  	  poW( 2.0, 88.0 ), poW( 2.0, 89.0 ), poW( 2.0, 90.0 ), poW( 2.0, 91.0 ), poW( 2.0, 92.0 ), poW( 2.0, 93.0 ),
  	  poW( 2.0, 94.0 ), poW( 2.0, 95.0 ), poW( 2.0, 96.0 ), poW( 2.0, 97.0 ), poW( 2.0, 98.0 ), poW( 2.0, 99.0 ),
  	  poW( 2.0, 100.0 ), poW( 2.0, 101.0 ), poW( 2.0, 102.0 ), poW( 2.0, 103.0 ), poW( 2.0, 104.0 ), poW( 2.0, 105.0 ),
  	  poW( 2.0, 106.0 ), poW( 2.0, 107.0 ), poW( 2.0, 108.0 ), poW( 2.0, 109.0 ), poW( 2.0, 110.0 ), poW( 2.0, 111.0 ),
  	  poW( 2.0, 112.0 ), poW( 2.0, 113.0 ), poW( 2.0, 114.0 ), poW( 2.0, 115.0 ), poW( 2.0, 116.0 ), poW( 2.0, 117.0 ),
  	  poW( 2.0, 118.0 ), poW( 2.0, 119.0 ), poW( 2.0, 120.0 ), poW( 2.0, 121.0 ), poW( 2.0, 122.0 ), poW( 2.0, 123.0 ),
  	  poW( 2.0, 124.0 ), poW( 2.0, 125.0 ), poW( 2.0, 126.0 ), poW( 2.0, 127.0 )
  };








  // HDRIMAGE
  class hdrimagE {
      public:
	      DWORD w, h;
		  BYTE *c;
		  float *sat;  // summed-area table


		  hdrimagE( void ) { reseT(); };
		  ~hdrimagE( void ) { deletealL(); };

          void reseT( void );
          void deletealL( void );
          void copY( hdrimagE *hdri );
          void copY( hdrimagE *hdri, long i, long j );

		  inline void setcoloR( DWORD i, DWORD j, BYTE r, BYTE g, BYTE b, BYTE e );
	      inline void setcoloR( DWORD i, DWORD j, const coloR& c_ );
		  inline void getcoloR( long i, long j, BYTE *r, BYTE *g, BYTE *b, BYTE *e );
		  inline coloR getcoloR( long i, long j );
		  inline coloR getcoloR( valuE s, valuE t, DWORD wrapping_mode, DWORD interpolation );

		  inline void cleaR( void );
		  void calculatesummedareatablE( void );
		  inline coloR getsummedareA( long xl, long  yb, long xr, long yt );
  };


  inline void encodergbE( float r, float g, float b, BYTE *red, BYTE *green, BYTE *blue, BYTE *exponent );
  inline void decodergbE( BYTE r, BYTE g, BYTE b, BYTE e, float *red, float *green, float *blue );
  void gaussianbluR( hdrimagE *hdri_in, valuE s, hdrimagE *hdri_out );
  BOOL loadfloaT( char filename[1024], hdrimagE *hdri );
  BOOL savefloaT( char filename[1024], hdrimagE *hdri );
  BOOL loadhdR( char filename[1024], hdrimagE *hdri );
  BOOL savehdR( char filename[1024], hdrimagE *hdri );
  void loadhdrigL( hdrimagE *hdri, opengL *ogl, GLuint textureid, BOOL linear, BOOL mip, GLint texwrap, GLint envmode );






  void hdrimagE::reseT( void ) {
	  w = h = 0;  
	  c = NULL;
	  sat = NULL;
  }




  void hdrimagE::deletealL( void ) {
	  if( c ) free( c ); 
	  if( sat ) free( sat ); 

	  reseT();
  }




  void hdrimagE::copY( hdrimagE *hdri ) {
      if( hdri ) {
          hdri->deletealL();

          hdri->w = w;  
	      hdri->h = h;  
          hdri->c = (BYTE*)malloc( w*h*32/8*sizeof( BYTE ) );
     	  if( !hdri->c ) exit( EXIT_FAILURE );
          if( c ) CopyMemory( &hdri->c[0], &c[0], w*h*32/8*sizeof( BYTE ) );
		  if( sat ) {
	          hdri->sat = (float*)malloc( w*h*24/8*sizeof( float ) );
			  if( !hdri->sat ) exit( EXIT_FAILURE );
	          CopyMemory( &hdri->sat[0], &sat[0], w*h*24/8*sizeof( float ) );
		  }
      }
  }




  void hdrimagE::copY( hdrimagE *hdri, long i, long j ) {
      if( hdri ) {
		  register long l;
          long left, right, top, bottom;

          if( i >= 0 && i < hdri->w ) left = i; else 
          if( i < 0 ) left = 0; else left = hdri->w-1;
          if( j >= 0 && j < hdri->h ) top = j; else 
          if( j < 0 ) top = 0; else top = hdri->h-1;
          if( i+w >= 0 && i+w < hdri->w ) right = i+w; else 
          if( i+w < 0 ) right = 0; else right = hdri->w-1;
          if( j+h >= 0 && j+h < hdri->h ) bottom = j+h; else 
          if( j+h < 0 ) bottom = 0; else bottom = hdri->h-1;

		  if( c != NULL && hdri->c != NULL ) {
	          for( l = top;  l < bottom;  l++ )
		          CopyMemory( &hdri->c[32/8*( left+l*hdri->w )], &c[32/8*( left-i+( l-j )*w )], ( right-left )*32/8*sizeof( BYTE ) );
		  }
		  if( sat != NULL && hdri->sat != NULL ) {
	          for( l = top;  l < bottom;  l++ )
		          CopyMemory( &hdri->sat[24/8*( left+l*hdri->w )], &sat[24/8*( left-i+( l-j )*w )], ( right-left )*24/8*sizeof( float ) );
		  }
      }
  }




  inline void hdrimagE::setcoloR( DWORD i, DWORD j, BYTE r, BYTE g, BYTE b, BYTE e ) {
   	  if( c && w > 0 && h > 0 ) {
		  if( i >= w || j >= h ) return ;

          i = ( i+j*w )*4;
		  
		  c[i+0] = r;      
		  c[i+1] = g;      
		  c[i+2] = b;      
		  c[i+3] = e;      
	  }
  }




  inline void hdrimagE::setcoloR( DWORD i, DWORD j, const coloR& c_ ) {
   	  if( c && w > 0 && h > 0 ) {
		  if( i >= w || j >= h ) return ;

          i = ( i+j*w )*4;
		  
		  encodergbE( c_.r, c_.g, c_.b, &c[i+0], &c[i+1], &c[i+2], &c[i+3] ); 
	  }
  }




  inline void hdrimagE::getcoloR( long i, long j, BYTE *r, BYTE *g, BYTE *b, BYTE *e ) {
	  if( c && w > 0 && h > 0 ) {
		  if( i < 0 ) i = 0;
		  if( j < 0 ) j = 0;
		  if( i >= w ) i = w-1;
		  if( j >= h ) j = h-1;

          i = ( i+j*w )*4;

		  *r = c[i+0];      
		  *g = c[i+1];      
		  *b = c[i+2];      
		  *e = c[i+3];      
	  }
  }




  inline coloR hdrimagE::getcoloR( long i, long j ) {
	  if( c && w > 0 && h > 0 ) {
		  coloR c_;

		  if( i < 0 ) i = 0;
		  if( j < 0 ) j = 0;
		  if( i >= w ) i = w-1;
		  if( j >= h ) j = h-1;

          i = ( i+j*w )*4;

		  decodergbE( c[i+0], c[i+1], c[i+2], c[i+3], &c_.r, &c_.g, &c_.b );

		  return c_;
	  }
  }




  inline coloR hdrimagE::getcoloR( valuE s, valuE t, DWORD wrapping_mode, DWORD interpolation ) {
	  if( c && w > 0 && h > 0 ) {
		  long i0, i1, j0, j1;
		  valuE val;
		  coloR c00, c10, c11, c01;


		  s *= w;  t *= h; 

		  i0 = flooR( s );  j0 = flooR( t );
		  i1 = i0+1;  j1 = j0+1;

		  s -= i0;  t -= j0;

		  if( wrapping_mode == CLAMP ) {
		      if( i0 < 0 ) i0 = 0;
		      if( j0 < 0 ) j0 = 0;
		      if( i1 < 0 ) i1 = 0;
		      if( j1 < 0 ) j1 = 0;
			  if( i0 > w-1 ) i0 = w-1;
		      if( j0 > h-1 ) j0 = h-1;
		      if( i1 > w-1 ) i1 = w-1;
		      if( j1 > h-1 ) j1 = h-1;
		  } else
		  if( wrapping_mode == REPEAT ) {
			  i0 = i0 % w;
			  j0 = j0 % h;
			  i1 = i1 % w;
			  j1 = j1 % h;
		      if( i0 < 0 ) i0 = w-1-i0;
		      if( j0 < 0 ) j0 = h-1-j0;
		      if( i1 < 0 ) i1 = w-1-i1;
		      if( j1 < 0 ) j1 = h-1-j1;
		  } else
		  if( wrapping_mode == MIRROR ) {
			  val = 1.0/w;
			  if( ( (DWORD)flooR( i0*val ) % 2 ) == 0 ) i0 = i0 % w; else i0 = w-1-( i0 % w );
			  if( ( (DWORD)flooR( i1*val ) % 2 ) == 0 ) i1 = i1 % w; else i1 = w-1-( i1 % w );
			  val = 1.0/h;
			  if( ( (DWORD)flooR( j0*val ) % 2 ) == 0 ) j0 = j0 % h; else j0 = h-1-( j0 % h );
			  if( ( (DWORD)flooR( j1*val ) % 2 ) == 0 ) j1 = j1 % h; else j1 = h-1-( j1 % h );
			  i0 = abs( (long)i0 );
			  j0 = abs( (long)i1 );
			  i1 = abs( (long)j0 );
			  j1 = abs( (long)j1 );
		  } 


		  c00 = getcoloR( i0, j0 );
		  c10 = getcoloR( i1, j0 );
		  c11 = getcoloR( i1, j1 );
		  c01 = getcoloR( i0, j1 );


		  if( interpolation == NEAREST_NEIGHBOR ) {
			  return c00;
		  } else
		  if( interpolation == LINEAR ) {
			  return lerP( s, t, c00, c10, c11, c01 );
		  } else
		  if( interpolation == HERMITT ) {
			  return herminterP( s, t, c00, c10, c11, c01 );
		  } 
	  }

	  return coloR();
  }




  inline void hdrimagE::cleaR( void ) {
      if( c ) ZeroMemory( &c[0], w*h*32/8*sizeof( BYTE ) );
  }




  void hdrimagE::calculatesummedareatablE( void ) {
	  register long i, j;
	  long l, m;
	  float f[3];
	  coloR c_;


      if( sat ) free( sat );
      sat = (float*)malloc( w*h*24/8*sizeof( float ) );
  	  if( !sat ) exit( EXIT_FAILURE );

	  for( j = 0;  j < h;  j++ ) {
		  f[0] = f[1] = f[2] = 0.0;  // aktualna hodnota suctu v riadku
		  for( i = 0;  i < w;  i++ ) {
			  c_ = getcoloR( i, j );
			  f[0] += c_.r;  f[1] += c_.g;  f[2] += c_.b;
			  l = 3*( i+j*w );  m = 3*( i+max( 0, j-1 )*w );
              sat[l+0] = f[0]+sat[m+0];
              sat[l+1] = f[1]+sat[m+1];
              sat[l+2] = f[2]+sat[m+2];
		  }
	  }
  }




  inline coloR hdrimagE::getsummedareA( long xl, long  yb, long xr, long yt ) {  // summed area from xl, yb (excluding) to xr, yt (including)
	  if( sat != NULL && xl <= xr && yb <= yt ) {
		  valuE inner, left, bottom, outer;
		  coloR c;

		  outer = sat[3*( xr+yt*w )+0];
		  left = sat[3*( xl+yt*w )+0];
		  bottom = sat[3*( xr+yb*w )+0];
		  inner = sat[3*( xl+yb*w )+0];
		  c.r = outer-bottom-left+inner;

		  outer = sat[3*( xr+yt*w )+1];
		  left = sat[3*( xl+yt*w )+1];
		  bottom = sat[3*( xr+yb*w )+1];
		  inner = sat[3*( xl+yb*w )+1];
		  c.g = outer-bottom-left+inner;

		  outer = sat[3*( xr+yt*w )+2];
		  left = sat[3*( xl+yt*w )+2];
		  bottom = sat[3*( xr+yb*w )+2];
		  inner = sat[3*( xl+yb*w )+2];
		  c.b = outer-bottom-left+inner;

		  return c;
	  } else return coloR();
  }




  inline void encodergbE( float r, float g, float b, BYTE *red, BYTE *green, BYTE *blue, BYTE *exponent ) {
	  valuE val = max( max( r, g ), b );
	  long exp = min( max( 0, (long)ceiL( loG( val > EPSILON ? val : EPSILON )*INV_LOG2 )+128 ), 255 );

	  val = diV( 255.0, pow2_[exp], 0.0 );

	  *red = r*val; 
	  *green = g*val;
	  *blue = b*val;
	  *exponent = exp;
  }




  inline void decodergbE( BYTE r, BYTE g, BYTE b, BYTE e, float *red, float *green, float *blue ) {
	  valuE val = pow2_[e]*INV_255;

	  *red = r*val;
	  *green = g*val;
	  *blue = b*val;
  }




  void gaussianbluR( hdrimagE *hdri_in, valuE s, hdrimagE *hdri_out ) {
	  if( hdri_out ) {
		  register long i, j, k, l;
		  long n;
		  valuE val, val2;
		  coloR c;
		  valuearraY gf; // gaussian filter
		  hdrimagE hdri;

	
		  hdri_out->deletealL();
		  hdri.w = hdri_in->w;
		  hdri.h = hdri_in->h;
		  hdri.copY( hdri_out );

		  // gaussian filter
		  n = (DWORD)( SQRT2*s )+1;	
		  val = 0.0;
		  for( l = -n;  l <= n;  l++ )
			  for( k = -n;  k <= n;  k++ ) {
				  val2 = gaussiaN( k, l, s );
				  val += val2;
				  gf.inserT( -1, val2 );	
			  }
		  val = 1.0/val;
		  for( k = 0;  k < gf.num;  k++ ) gf.elem[k] *= val;	

		  for( j = 0;  j < hdri_in->h;  j++ ) {
			  for( i = 0;  i < hdri_in->w;  i++ ) {
				  c = coloR();
				  for( k = -n;  k <= n;  k++ ) 
					  for( l = -n;  l <= n;  l++ ) 
						  c += hdri_in->getcoloR( i+k, j+l )*gf.elem[( k+n )+( l+n )*( 2*n+1 )];

				  hdri_out->setcoloR( i, j, c );
			  }
		  }
	  }
  }




  BOOL loadfloaT( char filename[1024], hdrimagE *hdri ) {
      FILE *file;
	  register long i, j;
	  char str[128], fileex[128], filename_[1024];
	  float *f = NULL;
  	  ldiv_t lx; 
	  

	  hdri->deletealL();

	  if( !( file = fopen( filename, "rb" ) ) ) return FALSE;

	  // file extension
	  j = (long)strlen( filename )-1;  while( filename[j] != '.' ) j--;  
	  for( i = j+1;  i < strlen( filename );  i++ ) fileex[i-j-1] = filename[i];
	  fileex[i-j-1] = '\x0';


	  if( strcmp( fileex, "float" ) == 0 || strcmp( fileex, "raw" ) == 0 ) { // float, raw file
		  for( i = 0;  i < strlen( filename );  i++ ) {
			  if( filename[i] == '0' || filename[i] == '1' || filename[i] == '2' || filename[i] == '3' || 
				  filename[i] == '4' || filename[i] == '5' || filename[i] == '6' || filename[i] == '7' ||
				  filename[i] == '8' || filename[i] == '9' ) {
			      filename_[i] = filename[i];
			  } else {
				  filename_[i] = 'x';
			  }
		  }

		  // height
	      j--;  i = j;
		  while( i > 0 && filename_[i] != 'x' ) { str[j-i] = filename_[i];  i--; }
		  str[j-i] = '\x0'; 
		  strcpy( str, strrev( str ) );
		  hdri->h = atol( str );

		  // width
		  i--;  j = i;
		  while( i > 0 && filename_[i] != 'x' ) { str[j-i] = filename_[i];  i--; }
		  str[j-i] = '\x0';
		  strcpy( str, strrev( str ) );
		  hdri->w = atol( str );

	      if( !( hdri->c = (BYTE*)malloc( hdri->w*hdri->h*4*sizeof( BYTE ) ) ) ) return FALSE;
	      if( !( f = (float*)malloc( hdri->w*hdri->h*3*sizeof( float ) ) ) ) return FALSE;

  	      lx = ldiv( hdri->w*hdri->h*3*sizeof( float ), 3*sizeof( float )*5333 );  
	      fread( &f[0], 3*sizeof( float )*5333, lx.quot, file );
	      fread( &f[lx.quot*3*5333], lx.rem, 1, file );

		  for( j = 0;  j < hdri->h;  j++ ) 
			  for( i = 0;  i < hdri->w;  i++ )  
				  encodergbE( f[3*( i+j*hdri->w )+0], f[3*( i+j*hdri->w )+1], f[3*( i+j*hdri->w )+2], &hdri->c[( i+j*hdri->w )*4*sizeof( BYTE )+0], &hdri->c[( i+j*hdri->w )*4*sizeof( BYTE )+1], &hdri->c[( i+j*hdri->w )*4*sizeof( BYTE )+2], &hdri->c[( i+j*hdri->w )*4*sizeof( BYTE )+3] );

		  free( f );
	  } else {
	      fclose( file );  

		  return FALSE;
	  }

      fclose( file );  


	  return TRUE;
  }




  BOOL savefloaT( char filename[1024], hdrimagE *hdri ) {
      FILE *file;
	  register long i, j;
	  coloR c;


      if( !( file = fopen( filename, "wb" ) ) ) return FALSE;

	  for( j = 0;  j < hdri->h;  j++ ) 
		  for( i = 0;  i < hdri->w;  i++ ) {
			  c = hdri->getcoloR( i, j );

		      fwrite( &c.r, sizeof( float ), 1, file );  
		      fwrite( &c.g, sizeof( float ), 1, file );  
		      fwrite( &c.b, sizeof( float ), 1, file );  
		  }

	  fclose( file );


	  return TRUE;
  }




  BOOL loadhdR( char filename[1024], hdrimagE *hdri ) {
      FILE *file;
	  register long i, j;
	  long count;
	  char str[128], programtype[64];
	  valuE gamma = 1.0, exposure = 1.0;
	  BYTE rgbe[4], buf[2], *scanline_buffer, *ptr, *ptr_end;
	  

	  hdri->deletealL();

	  if( !( file = fopen( filename, "rb" ) ) ) return FALSE;


	  // header
	  if( !fgets( str, sizeof( str )/sizeof( str[0] ), file ) ) return FALSE;
	  if( ( str[0] != '#' ) || ( str[1] != '?' ) ) return FALSE; else {
		  for( i = 0;  i < sizeof( programtype )-1;  i++ ) {
			  if( ( str[i+2] == 0 ) || isspace( str[i+2] ) ) break;
	          programtype[i] = str[i+2];
		  }
	      programtype[i] = '\x0';
		  if( !fgets( str, sizeof( str )/sizeof( str[0] ), file ) ) return FALSE;
	  }
	  for( ; ; ) {
		  if( ( str[0] == 0 ) || ( str[0] == '\n' ) ) return FALSE;
	      else if( strcmp( str, "FORMAT=32-bit_rle_rgbe\n" ) == 0 ) break;  // format found so break out of loop
		  if( !fgets( str, sizeof( str )/sizeof( str[0] ), file ) ) return FALSE;
	  }
	  if( !fgets( str, sizeof( str )/sizeof( str[0] ), file ) ) return FALSE;
	  if( sscanf( str, "GAMMA=%f", &gamma ) == 1 ) 
	      if( !fgets( str, sizeof( str )/sizeof( str[0] ), file ) ) return FALSE;
	  if( sscanf( str, "EXPOSURE=%f", &exposure ) == 1 ) 
	      if( !fgets( str, sizeof( str )/sizeof( str[0] ), file ) ) return FALSE;
	  if( strcmp( str, "\n" ) != 0 ) return FALSE;
	  if( !fgets( str, sizeof( str )/sizeof( str[0] ), file ) ) return FALSE;
	  if( sscanf( str, "-Y %d +X %d", &hdri->h, &hdri->w ) < 2 ) return FALSE;


	  // data
      if( !( hdri->c = (BYTE*)malloc( hdri->w*hdri->h*4*sizeof( BYTE ) ) ) ) return FALSE;

	  if( ( hdri->w < 8 ) || ( hdri->w > 0x7fff ) ) {  // run length encoding is not allowed so read flat
          /* simple read routine, will not correctly handle run length encoding */
          for( j = hdri->h-1;  j >= 0;  j-- ) 
		      for( i = 0;  i < hdri->w;  i++ ) {
	              if( fread( rgbe, sizeof( rgbe ), 1, file ) < 1 ) return FALSE;  // read error
				  hdri->setcoloR( i, j, rgbe[0], rgbe[1], rgbe[2], rgbe[3] ); 
			  }

          return TRUE;
	  } else {
		  scanline_buffer = NULL;
	      j = hdri->h;
		  while( j > 0 ) {  // read in each successive scanline
			  if( fread( rgbe, sizeof( rgbe ), 1, file ) < 1 ) {
			  	  free( scanline_buffer );

	              return FALSE;
		      }
			  if( ( rgbe[0] != 2 ) || ( rgbe[1] != 2 ) || ( rgbe[2] & 0x80 ) ) {  // this file is not run length encoded
				  /* simple read routine, will not correctly handle run length encoding */
		          for( j = hdri->h-1;  j >= 0;  j-- ) 
					  for( i = ( j == hdri->h-1 ? 1 : 0 );  i < hdri->w;  i++ ) {  // vynechanie prveho bodu
			              if( fread( rgbe, sizeof( rgbe ), 1, file ) < 1 ) return FALSE;  // read error
						  hdri->setcoloR( i, j, rgbe[0], rgbe[1], rgbe[2], rgbe[3] ); 
					  }

		          return TRUE;
	          }
		      if( ( ( (int)rgbe[2] ) << 8 | rgbe[3] ) != hdri->w ) {
			      free( scanline_buffer );

				  return FALSE;  // wrong scanline width
	          }

		      if( scanline_buffer == NULL ) scanline_buffer = (BYTE*)malloc( 4*sizeof( BYTE )*hdri->w );
			  if( scanline_buffer == NULL ) return FALSE;  // unable to allocate buffer space
   
	          ptr = &scanline_buffer[0];
		      /* read each of the four channels for the scanline into the buffer */
			  for( i = 0;  i < 4;  i++ ) {
				  ptr_end = &scanline_buffer[( i+1 )*hdri->w];
				  while( ptr < ptr_end ) {
				  	  if( fread( buf, sizeof( buf[0] )*2, 1, file ) < 1 ) {
						  free( scanline_buffer );

		                  return FALSE;  // read error
  		              }
			          if( buf[0] > 128 ) {
  				          /* a run of the same value */
					      count = buf[0]-128;
						  if( ( count == 0 ) || ( count > ptr_end-ptr ) ) {
							  free( scanline_buffer );

		                      return FALSE;  // bad scanline data
		                  }
			              while( count-- > 0 ) *ptr++ = buf[1];
				      } else {
					      /* a non-run */
		                  count = buf[0];
		                  if( ( count == 0 ) || ( count > ptr_end-ptr ) ) {
			                  free( scanline_buffer );
	
		                      return FALSE;  // bad scanline data
			              }
				          *ptr++ = buf[1];
					      if( --count > 0 ) {
						      if( fread( ptr, sizeof( *ptr )*count, 1, file ) < 1 ) {
							      free( scanline_buffer );

							  	  return FALSE;  // read error
		                      }
		                      ptr += count;
			              }
		              }
		          }
			  }

			  /* now copy data from buffer */
		      for( i = 0;  i < hdri->w;  i++ ) {
			      rgbe[0] = scanline_buffer[i+0*hdri->w];
	              rgbe[1] = scanline_buffer[i+1*hdri->w];
		          rgbe[2] = scanline_buffer[i+2*hdri->w];
			      rgbe[3] = scanline_buffer[i+3*hdri->w];
				  hdri->setcoloR( i, j-1, rgbe[0], rgbe[1], rgbe[2], rgbe[3] );
	          }

		      j--;
	      }
		  free( scanline_buffer );
      }

      return TRUE;
  }




  BOOL savehdR( char filename[1024], hdrimagE *hdri ) {
	  FILE *file;
	  register long i, j;
	  BYTE rgbe[4];
	  coloR c;


      if( !( file = fopen( filename, "wb" ) ) ) return FALSE;

	  // header
	  fprintf( file, "#?%s\n", "RGBE" );
      fprintf( file, "GAMMA=%g\n", 1.0 );
      fprintf( file, "EXPOSURE=%g\n", 1.0 );
      fprintf( file, "FORMAT=32-bit_rle_rgbe\n\n" );
	  fprintf( file, "-Y %d +X %d\n", hdri->h, hdri->w );

	  // data
	  for( j = 0;  j < hdri->h;  j++ ) 
		  for( i = 0;  i < hdri->w;  i++ ) {
			  c = hdri->getcoloR( i, j );

			  encodergbE( c.r, c.g, c.b, &rgbe[0], &rgbe[1], &rgbe[2], &rgbe[3] );

              fwrite( rgbe, sizeof( rgbe ), 1, file );
		  }

	  fclose( file );


	  return TRUE;
  }




  void loadhdrigL( hdrimagE *hdri, opengL *ogl, GLuint textureid, BOOL linear, BOOL mip, GLint texwrap, GLint envmode ) {
	  register long i, j;
	  texturE<float> T, T_;

	  T_.w = hdri->w;
	  T_.h = hdri->h;
	  T_.bpp = 3*sizeof( float )*8;
	  T_.copY( &T );

	  for( i = 0;  i < T.w;  i++ ) 
		  for( j = 0;  j < T.h;  j++ ) T.setcoloR( i, j, hdri->getcoloR( i, j ) );

	  loadtexturegL( &T, ogl, textureid, linear, mip, texwrap, envmode );	
  }








  // HDRIMAGEARRAY
  class hdrimagearraY: public arraY_<hdrimagE> {};


  // LPHDRIMAGE
  typedef hdrimagE* lphdrimagE;


  // LPHDRIMAGEARRAY
  class lphdrimagearraY: public arraY__<lphdrimagE> {};
