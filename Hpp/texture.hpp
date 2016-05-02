
  // wrapping mode
  #undef CLAMP
  #undef TILE
  #undef WRAP
  #undef REPEAT
  #undef MIRROR
  // interpolation
  #undef NEAREST_NEIGHBOR
  #undef NEAREST_NEIGHBOUR
  #undef LINEAR
  #undef HERMITT
  #undef CUBIC_BEZIER

  #define CLAMP 0
  #define TILE 0
  #define WRAP 0
  #define REPEAT 1
  #define MIRROR 2
  #define NEAREST_NEIGHBOR 0
  #define NEAREST_NEIGHBOUR 0
  #define LINEAR 1
  #define HERMITT 2
  #define CUBIC_BEZIER 3








  // TEXTURE TEMPLATE
  template <typename T> class texturE {
      public:
	      DWORD w, h, bpp;
		  T *c;


		  texturE( void ) { reseT(); };
		  ~texturE( void ) { deletealL(); };

          void reseT( void );
          void deletealL( void );
          void copY( texturE<T> *T_ );
          void copY( texturE<T> *T_, long i, long j );

		  void setcoloR( DWORD i, DWORD j, T r, T g, T b, T a );
	      void setcoloR( DWORD i, DWORD j, const coloR& c_ );
		  void setreD( DWORD i, DWORD j, T r );
		  void setgreeN( DWORD i, DWORD j, T g );
		  void setbluE( DWORD i, DWORD j, T b );
		  void setalphA( DWORD i, DWORD j, T a );
		  void getcoloR( long i, long j, T *r, T *g, T *b, T *a );
		  T getreD( long i, long j );
		  T getgreeN( long i, long j );
		  T getbluE( long i, long j );
		  T getalphA( long i, long j );
		  coloR getcoloR( long i, long j );
		  coloR getcoloR( valuE s, valuE t, DWORD wrapping_mode, DWORD interpolation );

		  void cleaR( void );
		  void fliphorizontaL( void );
		  void flipverticaL( void );
  };


  template <typename T> void gaussianbluR( texturE<T> *T_in, valuE s, texturE<T> *T_out );
  template <typename T> BOOL loadtgA( char filename[1024], texturE<T> *T_ );
  template <typename T> BOOL savetgA( char filename[1024], texturE<T> *T_ );
  template <typename T> BOOL loadfloaT( char filename[1024], texturE<T> *T_ );
  template <typename T> BOOL savefloaT( char filename[1024], texturE<T> *T_ );
  template <typename T> BOOL savehdR( char filename[1024], texturE<T> *T_ );
  template <typename T> void loadtexturegL( texturE<T> *T_, opengL *ogl, GLuint textureid, BOOL linear, BOOL mip, GLint texwrap, GLint envmode );
  template <typename T> void rasterizelinE( long Ax, long Ay, long Bx, long By, const coloR& c, texturE<T> *T_ );






  template <typename T> inline void texturE<T>::reseT( void ) {
	  w = h = bpp = 0;  
	  c = NULL;
  }




  template <typename T> inline void texturE<T>::deletealL( void ) {
	  if( c ) free( c ); 

	  reseT();
  }




  template <typename T> void texturE<T>::copY( texturE<T> *T_ ) {
      if( T_ ) {
          T_->deletealL();

          T_->w = w;  
	      T_->h = h;  
	      T_->bpp = bpp;
          T_->c = (T*)malloc( w*h*bpp );
     	  if( !T_->c ) exit( EXIT_FAILURE );
          if( c ) CopyMemory( &T_->c[0], &c[0], w*h*bpp );
      }
  }




  template <typename T> void texturE<T>::copY( texturE<T> *T_, long i, long j ) {
      if( T_ && bpp == T_->bpp ) {
          long left, right, top, bottom;

          if( i >= 0 && i < T_->w ) left = i; else 
          if( i < 0 ) left = 0; else left = T_->w-1;
          if( j >= 0 && j < T_->h ) top = j; else 
          if( j < 0 ) top = 0; else top = T_->h-1;
          if( i+w >= 0 && i+w < T_->w ) right = i+w; else 
          if( i+w < 0 ) right = 0; else right = T_->w-1;
          if( j+h >= 0 && j+h < T_->h ) bottom = j+h; else 
          if( j+h < 0 ) bottom = 0; else bottom = T_->h-1;

		  if( c != NULL && T_->c != NULL ) {
	          for( register long l = top;  l < bottom;  l++ )
		          CopyMemory( &T_->c[T_->bpp/8*( left+l*T_->w )], &c[bpp/8*( left-i+( l-j )*w )], ( right-left )*bpp );
		  }
      }
  }




  template <typename T> void texturE<T>::setcoloR( DWORD i, DWORD j, T r, T g, T b, T a ) {
   	  if( c && w > 0 && h > 0 ) {
		  if( i >= w || j >= h ) return ;

          i = i+j*w;
		  
		  if( bpp/sizeof( T ) == 32 ) {
			  c[i*4+0] = r;      
			  c[i*4+1] = g;      
			  c[i*4+2] = b;      
			  c[i*4+3] = a;      
		  } else
		  if( bpp/sizeof( T ) == 24 ) {
			  c[i*3+0] = r;      
			  c[i*3+1] = g;      
			  c[i*3+2] = b;      
		  } else
		  if( bpp/sizeof( T ) == 16 ) {
			  c[i*2+0] = r;      
			  c[i*2+1] = g;      
		  } else
		  if( bpp/sizeof( T ) == 8 ) {
			  c[i+0] = r;      
		  } 
	  }
  }




  template <typename T> void texturE<T>::setcoloR( DWORD i, DWORD j, const coloR& c_ ) {
   	  if( c && w > 0 && h > 0 ) {
		  if( i >= w || j >= h ) return ;

          i = i+j*w;
		  
		  if( typeid( T ) == typeid( BYTE ) || typeid( T ) == typeid( unsigned char ) ) {
			  if( bpp/sizeof( T ) == 32 ) {
				  c[i*4+0] = c_.r*255.0;      
				  c[i*4+1] = c_.g*255.0;      
				  c[i*4+2] = c_.b*255.0;      
				  c[i*4+3] = c_.a*255.0;      
			  } else
			  if( bpp/sizeof( T ) == 24 ) {
				  c[i*3+0] = c_.r*255.0;      
				  c[i*3+1] = c_.g*255.0;      
				  c[i*3+2] = c_.b*255.0;      
			  } else
			  if( bpp/sizeof( T ) == 16 ) {
				  c[i*2+0] = c_.r*255.0;      
				  c[i*2+1] = c_.g*255.0;      
			  } else
			  if( bpp/sizeof( T ) == 8 ) {
				  c[i+0] = c_.r*255.0;      
			  } 
		  } else 
		  if( typeid( T ) == typeid( float ) ) {
			  if( bpp/sizeof( T ) == 32 ) {
				  c[i*4+0] = c_.r;      
				  c[i*4+1] = c_.g;      
				  c[i*4+2] = c_.b;      
				  c[i*4+3] = c_.a;      
			  } else
			  if( bpp/sizeof( T ) == 24 ) {
				  c[i*3+0] = c_.r;      
				  c[i*3+1] = c_.g;      
				  c[i*3+2] = c_.b;      
			  } else
			  if( bpp/sizeof( T ) == 16 ) {
				  c[i*2+0] = c_.r;      
				  c[i*2+1] = c_.g;      
			  } else
			  if( bpp/sizeof( T ) == 8 ) {
				  c[i+0] = c_.r;      
			  } 
		  } 
	  }
  }




  template <typename T> void texturE<T>::setreD( DWORD i, DWORD j, T r ) {
   	  if( c && w > 0 && h > 0 ) {
		  if( i >= w || j >= h ) return ;

          i = i+j*w;
		  
		  if( bpp/sizeof( T ) == 32 ) {
			  c[i*4+0] = r;      
		  } else
		  if( bpp/sizeof( T ) == 24 ) {
			  c[i*3+0] = r;      
		  } else
		  if( bpp/sizeof( T ) == 16 ) {
			  c[i*2+0] = r;      
		  } else
		  if( bpp/sizeof( T ) == 8 ) {
			  c[i+0] = r;      
		  } 
	  }
  }




  template <typename T> void texturE<T>::setgreeN( DWORD i, DWORD j, T g ) {
   	  if( c && w > 0 && h > 0 ) {
		  if( i >= w || j >= h ) return ;

          i = i+j*w;
		  
		  if( bpp/sizeof( T ) == 32 ) {
			  c[i*4+1] = g;      
		  } else
		  if( bpp/sizeof( T ) == 24 ) {
			  c[i*3+1] = g;      
		  } else
		  if( bpp/sizeof( T ) == 16 ) {
			  c[i*2+1] = g;      
		  } else
		  if( bpp/sizeof( T ) == 8 ) {
		  } 
	  }
  }




  template <typename T> void texturE<T>::setbluE( DWORD i, DWORD j, T b ) {
   	  if( c && w > 0 && h > 0 ) {
		  if( i >= w || j >= h ) return ;

          i = i+j*w;
		  
		  if( bpp/sizeof( T ) == 32 ) {
			  c[i*4+2] = b;      
		  } else
		  if( bpp/sizeof( T ) == 24 ) {
			  c[i*3+2] = b;      
		  } else
		  if( bpp/sizeof( T ) == 16 ) {
		  } else
		  if( bpp/sizeof( T ) == 8 ) {
		  } 
	  }
  }




  template <typename T> void texturE<T>::setalphA( DWORD i, DWORD j, T a ) {
   	  if( c && w > 0 && h > 0 ) {
		  if( i >= w || j >= h ) return ;

          i = i+j*w;
		  
		  if( bpp/sizeof( T ) == 32 ) {
			  c[i*4+3] = a;      
		  } else
		  if( bpp/sizeof( T ) == 24 ) {
		  } else
		  if( bpp/sizeof( T ) == 16 ) {
		  } else
		  if( bpp/sizeof( T ) == 8 ) {
		  } 
	  }
  }




  template <typename T> void texturE<T>::getcoloR( long i, long j, T *r, T *g, T *b, T *a ) {
	  if( c && w > 0 && h > 0 ) {
		  if( i < 0 ) i = 0;
		  if( j < 0 ) j = 0;
		  if( i >= w ) i = w-1;
		  if( j >= h ) j = h-1;

          i = i+j*w;

		  if( bpp/sizeof( T ) == 32 ) {
			  *r = c[i*4+0];      
			  *g = c[i*4+1];      
			  *b = c[i*4+2];      
			  *a = c[i*4+3];      
		  } else
		  if( bpp/sizeof( T ) == 24 ) {
			  *r = c[i*3+0];      
			  *g = c[i*3+1];      
			  *b = c[i*3+2];      
			  *a = 0;
		  } else
		  if( bpp/sizeof( T ) == 16 ) {
			  *r = c[i*2+0];      
			  *g = c[i*2+1];      
			  *b = *a = 0;
		  } else
		  if( bpp/sizeof( T ) == 8 ) {
			  *r = c[i+0];      
			  *g = *b = *a = 0;
		  } else { *r = *g = *b = *a = 0; }
	  }
  }




  template <typename T> T texturE<T>::getreD( long i, long j ) {
	  if( c && w > 0 && h > 0 ) {
		  if( i < 0 ) i = 0;
		  if( j < 0 ) j = 0;
		  if( i >= w ) i = w-1;
		  if( j >= h ) j = h-1;

          i = i+j*w;

		  if( bpp/sizeof( T ) == 32 ) {
			  return c[i*4+0];      
		  } else
		  if( bpp/sizeof( T ) == 24 ) {
			  return c[i*3+0];      
		  } else
		  if( bpp/sizeof( T ) == 16 ) {
			  return c[i*2+0];      
		  } else
		  if( bpp/sizeof( T ) == 8 ) {
			  return c[i+0];      
		  } else { return 0; }
	  }
  }




  template <typename T> T texturE<T>::getgreeN( long i, long j ) {
	  if( c && w > 0 && h > 0 ) {
		  if( i < 0 ) i = 0;
		  if( j < 0 ) j = 0;
		  if( i >= w ) i = w-1;
		  if( j >= h ) j = h-1;

          i = i+j*w;

		  if( bpp/sizeof( T ) == 32 ) {
			  return c[i*4+1];      
		  } else
		  if( bpp/sizeof( T ) == 24 ) {
			  return c[i*3+1];      
		  } else
		  if( bpp/sizeof( T ) == 16 ) {
			  return c[i*2+1];      
		  } else
		  if( bpp/sizeof( T ) == 8 ) {
			  return 0;
		  } else { return 0; }
	  }
  }




  template <typename T> T texturE<T>::getbluE( long i, long j ) {
	  if( c && w > 0 && h > 0 ) {
		  if( i < 0 ) i = 0;
		  if( j < 0 ) j = 0;
		  if( i >= w ) i = w-1;
		  if( j >= h ) j = h-1;

          i = i+j*w;

		  if( bpp/sizeof( T ) == 32 ) {
			  return c[i*4+2];      
		  } else
		  if( bpp/sizeof( T ) == 24 ) {
			  return c[i*3+2];      
		  } else
		  if( bpp/sizeof( T ) == 16 ) {
			  return 0;      
		  } else
		  if( bpp/sizeof( T ) == 8 ) {
			  return 0;
		  } else { return 0; }
	  }
  }




  template <typename T> T texturE<T>::getalphA( long i, long j ) {
	  if( c && w > 0 && h > 0 ) {
		  if( i < 0 ) i = 0;
		  if( j < 0 ) j = 0;
		  if( i >= w ) i = w-1;
		  if( j >= h ) j = h-1;

          i = i+j*w;

		  if( bpp/sizeof( T ) == 32 ) {
			  return c[i*4+3];      
		  } else
		  if( bpp/sizeof( T ) == 24 ) {
			  return 0;
		  } else
		  if( bpp/sizeof( T ) == 16 ) {
			  return 0;
		  } else
		  if( bpp/sizeof( T ) == 8 ) {
			  return 0;
		  } else { return 0; }
	  }
  }




  template <typename T> coloR texturE<T>::getcoloR( long i, long j ) {
	  if( c && w > 0 && h > 0 ) {
		  if( i < 0 ) i = 0;
		  if( j < 0 ) j = 0;
		  if( i >= w ) i = w-1;
		  if( j >= h ) j = h-1;

          i = i+j*w;

		  if( typeid( T ) == typeid( BYTE ) || typeid( T ) == typeid( unsigned char ) ) {
			  if( bpp/sizeof( T ) == 32 ) {
				  return coloR( c[i*4+0], c[i*4+1], c[i*4+2], c[i*4+3] )*(valuE)INV_255;
			  } else
			  if( bpp/sizeof( T ) == 24 ) {
				  return coloR( c[i*3+0]*INV_255, c[i*3+1]*INV_255, c[i*3+2]*INV_255, 0.0 );
			  } else
			  if( bpp/sizeof( T ) == 16 ) {
				  return coloR( c[i*2+0]*INV_255, c[i*2+1]*INV_255, 0.0, 0.0 );
			  } else
			  if( bpp/sizeof( T ) == 8 ) {
				  return coloR( c[i*1+0]*INV_255, 0.0, 0.0, 0.0 );
			  } else { return coloR(); }
		  } else
		  if( typeid( T ) == typeid( float ) ) {
			  if( bpp/sizeof( T ) == 32 ) {
				  return coloR( c[i*4+0], c[i*4+1], c[i*4+2], c[i*4+3] );
			  } else
			  if( bpp/sizeof( T ) == 24 ) {
				  return coloR( c[i*3+0], c[i*3+1], c[i*3+2], 0.0 );
			  } else
			  if( bpp/sizeof( T ) == 16 ) {
				  return coloR( c[i*2+0], c[i*2+1], 0.0, 0.0 );
			  } else
			  if( bpp/sizeof( T ) == 8 ) {
				  return coloR( c[i*1+0], 0.0, 0.0, 0.0 );
			  } else { return coloR(); }
		  } 
	  }
  }




  template <typename T> coloR texturE<T>::getcoloR( valuE s, valuE t, DWORD wrapping_mode, DWORD interpolation ) {
	  if( c && w > 0 && h > 0 ) {
		  long i_1, i0, i1, i2, j_1, j0, j1, j2;
		  valuE val;
		  coloR c_1_1, c0_1, c1_1, c2_1, c_10, c00, c10, c20, c_11, c01, c11, c21, c_12, c02, c12, c22;


		  s *= w;  t *= h; 

		  i0 = flooR( s );  j0 = flooR( t );
		  i1 = i0+1;  j1 = j0+1;
		  if( interpolation == CUBIC_BEZIER ) {
			  i_1 = i0-1;  j_1 = j0-1;
			  i2 = i0+2;  j2 = j0+2;
		  }

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

			  if( interpolation == CUBIC_BEZIER ) {
				  if( i_1 < 0 ) i_1 = 0;
			      if( j_1 < 0 ) j_1 = 0;
			      if( i2 < 0 ) i2 = 0;
				  if( j2 < 0 ) j2 = 0;
			      if( i_1 > w-1 ) i_1 = w-1;
			      if( j_1 > h-1 ) j_1 = h-1;
			      if( i2 > w-1 ) i2 = w-1;
				  if( j2 > h-1 ) j2 = h-1;
			  }
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

			  if( interpolation == CUBIC_BEZIER ) {
				  i_1 = i_1 % w;
				  j_1 = j_1 % h;
				  i2 = i2 % w;
				  j2 = j2 % h;
				  if( i_1 < 0 ) i_1 = w-1-i_1;
			      if( j_1 < 0 ) j_1 = h-1-j_1;
			      if( i2 < 0 ) i2 = w-1-i2;
			      if( j2 < 0 ) j2 = h-1-j2;
			  }
		  } else
		  if( wrapping_mode == MIRROR ) {
			  val = 1.0/w;
			  if( ( (DWORD)flooR( i0*val ) % 2 ) == 0 ) i0 = i0 % w; else i0 = w-1-( i0 % w );
			  if( ( (DWORD)flooR( i1*val ) % 2 ) == 0 ) i1 = i1 % w; else i1 = w-1-( i1 % w );
			  val = 1.0/h;
			  if( ( (DWORD)flooR( j0*val ) % 2 ) == 0 ) j0 = j0 % h; else j0 = h-1-( j0 % h );
			  if( ( (DWORD)flooR( j1*val ) % 2 ) == 0 ) j1 = j1 % h; else j1 = h-1-( j1 % h );
			  i0 = abs( (long)i0 );
			  j0 = abs( (long)j0 );
			  i1 = abs( (long)i1 );
			  j1 = abs( (long)j1 );

			  if( interpolation == CUBIC_BEZIER ) {
				  val = 1.0/w;
				  if( ( (DWORD)flooR( i_1*val ) % 2 ) == 0 ) i_1 = i_1 % w; else i_1 = w-1-( i_1 % w );
				  if( ( (DWORD)flooR( i2*val ) % 2 ) == 0 ) i2 = i2 % w; else i2 = w-1-( i2 % w );
				  val = 1.0/h;
				  if( ( (DWORD)flooR( j_1*val ) % 2 ) == 0 ) j_1 = j_1 % h; else j_1 = h-1-( j_1 % h );
				  if( ( (DWORD)flooR( j2*val ) % 2 ) == 0 ) j2 = j2 % h; else j2 = h-1-( j2 % h );
				  i_1 = abs( (long)i_1 );
				  j_1 = abs( (long)j_1 );
				  i2 = abs( (long)i2 );
				  j2 = abs( (long)j2 );
			  }	
		  } 


		  c00 = getcoloR( i0, j0 );
		  c10 = getcoloR( i1, j0 );
		  c11 = getcoloR( i1, j1 );
		  c01 = getcoloR( i0, j1 );

		  if( interpolation == CUBIC_BEZIER ) {
			  c_1_1 = getcoloR( i_1, j_1 );
			  c0_1 = getcoloR( i0, j_1 );
			  c1_1 = getcoloR( i1, j_1 );
			  c2_1 = getcoloR( i2, j_1 );

			  c_10 = getcoloR( i_1, j0 );
//			  c00 = getcoloR( i0, j0 );
//			  c10 = getcoloR( i1, j0 );
			  c20 = getcoloR( i2, j0 );

			  c_11 = getcoloR( i_1, j1 );
//			  c01 = getcoloR( i0, j1 );
//			  c11 = getcoloR( i1, j1 );
			  c21 = getcoloR( i2, j1 );

			  c_12 = getcoloR( i_1, j2 );
			  c02 = getcoloR( i0, j2 );
			  c12 = getcoloR( i1, j2 );
			  c22 = getcoloR( i2, j2 );
		  }


		  if( interpolation == NEAREST_NEIGHBOR ) {
		      return c00;    	
		  } else
		  if( interpolation == LINEAR ) {
			  return lerP( s, t, c00, c10, c11, c01 );
		  } else
		  if( interpolation == HERMITT ) {
			  return herminterP( s, t, c00, c10, c11, c01 );
		  } else
		  if( interpolation == CUBIC_BEZIER ) {
			  return cubicbezierinterP( s, t, c_1_1, c0_1, c1_1, c2_1, c_10, c00, c10, c20, c_11, c01, c11, c21, c_12, c02, c12, c22 );
		  }
	  }

	  return coloR();
  }




  template <typename T> inline void texturE<T>::cleaR( void ) {
      if( c ) ZeroMemory( &c[0], w*h*bpp );
  }




  template <typename T> inline void texturE<T>::fliphorizontaL( void ) {
	  register long i, j, k;
	  coloR c;

	  i = 0;  j = w-1;
	  while( i < j ) {
		  for( k = 0;  k < h;  k++ ) {
			  // swap [i, k], [j, k]
              c = getcoloR( i, k );
			  setcoloR( i, k, getcoloR( j, k ) );
			  setcoloR( j, k, c );
		  }

		  i++;  j--;
	  }
  }




  template <typename T> inline void texturE<T>::flipverticaL( void ) {
	  register long i, j, k;
	  coloR c;

	  i = 0;  j = h-1;
	  while( i < j ) {
		  for( k = 0;  k < w;  k++ ) {
			  // swap [k, i], [k, j]
              c = getcoloR( k, i );
			  setcoloR( k, i, getcoloR( k, j ) );
			  setcoloR( k, j, c );
		  }

		  i++;  j--;
	  }
  }




  template <typename T> void gaussianbluR( texturE<T> *T_in, valuE s, texturE<T> *T_out ) {
	  if( T_out ) {
		  register long i, j, k, l;
		  long n;
		  valuE val, val2;
		  coloR c;
		  valuearraY gf; // gaussian filter
		  texturE<T> T;

	
		  T.w = T_in->w;
		  T.h = T_in->h;
		  T.bpp = T_in->bpp;
		  T.copY( T_out );

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

		  for( j = 0;  j < T_in->h;  j++ ) {
			  for( i = 0;  i < T_in->w;  i++ ) {
				  c = coloR();
				  for( k = -n;  k <= n;  k++ ) 
					  for( l = -n;  l <= n;  l++ ) 
						  c += T_in->getcoloR( i+k, j+l )*gf.elem[( k+n )+( l+n )*( 2*n+1 )];

				  T_out->setcoloR( i, j, c );
			  }
		  }
	  }
  }




  template <typename T> BOOL loadtgA( char filename[1024], texturE<T> *T_ ) {
	  if( typeid( T ) == typeid( BYTE ) || typeid( T ) == typeid( unsigned char ) ) {
	      FILE *file;
		  register long i, j;
		  BYTE r, g, b, a;
	  	  ldiv_t lx; 
		  
	
		  T_->deletealL();
	
		  if( !( file = fopen( filename, "rb" ) ) ) return FALSE;
	
	      fseek( file, 12, 0 ); 
		  fread( &T_->w, 2, 1, file ); 
		  fread( &T_->h, 2, 1, file );
		  fread( &T_->bpp, 1, 1, file );  
	      fseek( file, 18, 0 ); 
	
	      if( !( T_->c = (BYTE*)malloc( T_->w*T_->h*T_->bpp ) ) ) return FALSE;
	
		  if( T_->bpp == 32 ) {
	  	      lx = ldiv( T_->w*T_->h*T_->bpp/8, 64000 );  
		      fread( &T_->c[0], 64000, lx.quot, file );
		      fread( &T_->c[lx.quot*64000], lx.rem, 1, file );
		  } else  
		  if( T_->bpp == 24 ) {
	  	      lx = ldiv( T_->w*T_->h*T_->bpp/8, 63999 );  
		      fread( &T_->c[0], 63999, lx.quot, file );
		      fread( &T_->c[lx.quot*63999], lx.rem, 1, file );
		  } else 
		  if( T_->bpp == 8 ) {
	  	      lx = ldiv( T_->w*T_->h*T_->bpp/8, 64000 );  
		      fread( &T_->c[0], 64000, lx.quot, file );
		      fread( &T_->c[lx.quot*64000], lx.rem, 1, file );
		  } else return FALSE; 
	
		  if( T_->bpp == 32 || T_->bpp == 24 )
		      for( j = 0;  j < T_->h;  j++ ) 
				  for( i = 0;  i < T_->w;  i++ ) {
				      T_->getcoloR( i, j, &b, &g, &r, &a );
					  T_->setcoloR( i, j, r, g, b, a );
				  }
	
	      fclose( file );  
	
	
		  return TRUE;
      } else return FALSE;
  }




  template <typename T> BOOL savetgA( char filename[1024], texturE<T> *T_ ) {
      FILE *file;
	  register long i, j;
	  BYTE a;
	  coloR c;
	
	
      if( !( file = fopen( filename, "wb" ) ) ) return FALSE;
	
	  a = 0;  for( i = 0;  i < 18;  i++ ) fwrite( &a, 1, 1, file );
      fseek( file, 2, 0 );  if( T_->bpp/sizeof( T ) == 32 || T_->bpp/sizeof( T ) == 24 ) a = 2; else a = 3;  fwrite( &a, 1, 1, file );
      fseek( file, 12, 0 );  fwrite( &T_->w, 2, 1, file );
      fseek( file, 14, 0 );  fwrite( &T_->h, 2, 1, file );
	  fseek( file, 16, 0 );  a = T_->bpp/sizeof( T );  fwrite( &a, 1, 1, file );
      fseek( file, 18, 0 ); 
	
	  if( T_->bpp/sizeof( T ) == 32 ) {
          for( j = T_->h-1;  j >= 0;  j-- ) 
			  for( i = 0;  i < T_->w;  i++ ) {
			      c = clamP( T_->getcoloR( i, j ), 0.0, 1.0 )*(valuE)255.0;
	
				  a = c.b;  fwrite( &a, 1, 1, file );  
			      a = c.g;  fwrite( &a, 1, 1, file );  
			      a = c.r;  fwrite( &a, 1, 1, file );  
			      a = c.a;  fwrite( &a, 1, 1, file );  
			  }
	  } else
	  if( T_->bpp/sizeof( T ) == 24 ) {
          for( j = T_->h-1;  j >= 0;  j-- ) 
			  for( i = 0;  i < T_->w;  i++ ) {
			      c = clamP( T_->getcoloR( i, j ), 0.0, 1.0 )*(valuE)255.0;
	
			      a = c.b;  fwrite( &a, 1, 1, file );  
			      a = c.g;  fwrite( &a, 1, 1, file );  
			      a = c.r;  fwrite( &a, 1, 1, file );  
			  }
	  } else
	  if( T_->bpp/sizeof( T ) == 8 ) {
          for( j = T_->h-1;  j >= 0;  j-- ) 
			  for( i = 0;  i < T_->w;  i++ ) {
			      c = clamP( T_->getcoloR( i, j ), 0.0, 1.0 )*(valuE)255.0;
	
			      a = c.r;  fwrite( &a, 1, 1, file );  
			  }
	  } else return FALSE;
	
	  fclose( file );
	
	
	  return TRUE;
  }




  template <typename T> BOOL loadfloaT( char filename[1024], texturE<T> *T_ ) {
	  if( typeof( T ) == float ) {
	      FILE *file;
		  register long i, j;
		  char str[128], fileex[128], filename_[1024];
		  T t[3];
	  

		  T_->deletealL();

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
			  i--;  j = i;
			  while( i > 0 && filename_[i] != 'x' ) { str[j-i] = filename_[i];  i--; }
			  str[j-i] = '\x0'; 
			  strcpy( str, strrev( str ) );
			  T_->h = atol( str );

			  // width
			  i--;  j = i;
			  while( i > 0 && filename_[i] != 'x' ) { str[j-i] = filename_[i];  i--; }
			  str[j-i] = '\x0';
			  strcpy( str, strrev( str ) );
			  T_->w = atol( str );


		      if( !( T_->c = (T*)malloc( T_->w*T_->h*T_->bpp ) ) ) return FALSE;

			  for( i = 0;  i < T_->w;  i++ ) 
				  for( j = 0;  j < T_->h;  j++ ) {
					  fread( &t[0], 3*sizeof( T ), 1, file );
	
					  hdri->c[( i+j*T_->w )*T_->bpp+0] = t[0];
					  hdri->c[( i+j*T_->w )*T_->bpp+1] = t[1];
					  hdri->c[( i+j*T_->w )*T_->bpp+2] = t[2];
				  }
		  } else {
			  fclose( file );  

			  return FALSE;
		  }

	      fclose( file );  


		  return TRUE;
	  } else return FALSE;
  }




  template <typename T> BOOL savefloaT( char filename[1024], texturE<T> *T_ ) {
	  if( typeid( T ) == typeid( float ) ) {
	      FILE *file;
		  register long i, j;
		  coloR c;


		  if( !( file = fopen( filename, "wb" ) ) ) return FALSE;

		  for( j = T_->h-1;  j >= 0;  j-- ) 
			  for( i = 0;  i < T_->w;  i++ ) {
				  c = T_->getcoloR( i, j );

			      fwrite( &c.r, sizeof( float ), 1, file );  
			      fwrite( &c.g, sizeof( float ), 1, file );  
			      fwrite( &c.b, sizeof( float ), 1, file );  
			  }

		  fclose( file );


		  return TRUE;
	  } else return FALSE;
  }




  template <typename T> BOOL savehdR( char filename[1024], texturE<T> *T_ ) {
	  if( typeid( T ) == typeid( float ) ) {
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
		  fprintf( file, "-Y %d +X %d\n", T_->h, T_->w );

		  // data
		  for( j = 0;  j < T_->h;  j++ ) 
			  for( i = 0;  i < T_->w;  i++ ) {
				  c = T_->getcoloR( i, j );

				  encodergbE( c.r, c.g, c.b, &rgbe[0], &rgbe[1], &rgbe[2], &rgbe[3] );

		          fwrite( rgbe, sizeof( rgbe ), 1, file );
			  }

		  fclose( file );


		  return TRUE;
	  } else return FALSE;
  }




  template <typename T> void loadtexturegL( texturE<T> *T_, opengL *ogl, GLuint textureid, BOOL linear, BOOL mip, GLint texwrap, GLint envmode ) {
	  register long i;
      texturE<T> T__, T___;


      if( textureid == -1 ) glGenTextures( 1, &textureid );

	  glBindTexture( GL_TEXTURE_2D, textureid );

	  glPixelStorei( GL_PACK_ALIGNMENT, 1 );
	  glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texwrap );
	  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texwrap );
	  if( linear ) glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ); else
		           glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	  glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, envmode );

	  if( !ogl->gl_arb_texture_non_power_of_two ) {
		  i = 1;  while( poW( 2.0, i ) < T_->w ) i++;
		  T___.w = (DWORD)poW( 2.0, i-1 );
		  i = 1;  while( poW( 2.0, i ) < T_->h ) i++;
		  T___.h = (DWORD)poW( 2.0, i-1 );
		  T___.bpp = T_->bpp;
		  T___.copY( &T__ );

		  for( i = 0;  i < T__.w;  i++ ) 
			  for( j = 0;  j < T__.h;  j++ ) 
				  T__.setcoloR( i, j, T_->getcoloR( (valuE)i/(valuE)( T__.w-1 ), (valuE)j/(valuE)( T__.h-1 ), CLAMP, linear == TRUE ? LINEAR : NEAREST_NEIGHBOUR ) );


		  if( mip ) {
			  if( linear ) glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST ); else
				           glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST );

			  if( typeid( T ) == typeid( BYTE ) || typeid( T ) == typeid( unsigned char ) ) {
				  if( T__.bpp/sizeof( T ) == 32 ) 
					  gluBuild2DMipmaps( GL_TEXTURE_2D, 4, T__.w, T__.h, GL_RGBA, GL_UNSIGNED_BYTE, T__.c );
				  else 
				  if( T__.bpp/sizeof( T ) == 24 ) 
					  gluBuild2DMipmaps( GL_TEXTURE_2D, 3, T__.w, T__.h, GL_RGB, GL_UNSIGNED_BYTE, T__.c );
				  else 
				  if( T__.bpp/sizeof( T ) == 8 ) 
					  gluBuild2DMipmaps( GL_TEXTURE_2D, 1, T__.w, T__.h, GL_LUMINANCE, GL_UNSIGNED_BYTE, T__.c );
			  } else
			  if( typeid( T ) == typeid( float ) ) {
				  if( T__.bpp/sizeof( T ) == 32 ) 
					  gluBuild2DMipmaps( GL_TEXTURE_2D, 4, T__.w, T__.h, GL_RGBA, GL_FLOAT, T__.c );
				  else 
				  if( T__.bpp/sizeof( T ) == 24 ) 
					  gluBuild2DMipmaps( GL_TEXTURE_2D, 3, T__.w, T__.h, GL_RGB, GL_FLOAT, T__.c );
				  else 
				  if( T__.bpp/sizeof( T ) == 8 ) 
					  gluBuild2DMipmaps( GL_TEXTURE_2D, 1, T__.w, T__.h, GL_LUMINANCE, GL_FLOAT, T__.c );
			  }
		  } else {
			  if( linear ) glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR ); else
				           glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
			
			  if( typeid( T ) == typeid( BYTE ) || typeid( T ) == typeid( unsigned char ) ) {
				  if( T__.bpp/sizeof( T ) == 32 ) 			
					  glTexImage2D( GL_TEXTURE_2D, 0, 4, T__.w, T__.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, T__.c );
				  else 
				  if( T__.bpp/sizeof( T ) == 24 ) 
					  glTexImage2D( GL_TEXTURE_2D, 0, 3, T__.w, T__.h, 0, GL_RGB, GL_UNSIGNED_BYTE, T__.c );
				  else 
				  if( T__.bpp/sizeof( T ) == 8 ) 
					  glTexImage2D( GL_TEXTURE_2D, 0, 1, T__.w, T__.h, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, T__.c );
			  } else
			  if( typeid( T ) == typeid( float ) ) {
				  if( T__.bpp/sizeof( T ) == 32 ) 			
					  glTexImage2D( GL_TEXTURE_2D, 0, 4, T__.w, T__.h, 0, GL_RGBA, GL_FLOAT, T__.c );
				  else 
				  if( T__.bpp/sizeof( T ) == 24 ) 
					  glTexImage2D( GL_TEXTURE_2D, 0, 3, T__.w, T__.h, 0, GL_RGB, GL_FLOAT, T__.c );
				  else 
				  if( T__.bpp/sizeof( T ) == 8 ) 
					  glTexImage2D( GL_TEXTURE_2D, 0, 1, T__.w, T__.h, 0, GL_LUMINANCE, GL_FLOAT, T__.c );
			  }
		  }
	  } else {
		  if( mip ) {
			  if( linear ) glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST ); else
				           glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST );

			  if( typeid( T ) == typeid( BYTE ) || typeid( T ) == typeid( unsigned char ) ) {
				  if( T_->bpp/sizeof( T ) == 32 ) 
					  gluBuild2DMipmaps( GL_TEXTURE_2D, 4, T_->w, T_->h, GL_RGBA, GL_UNSIGNED_BYTE, T_->c );
				  else 
				  if( T_->bpp/sizeof( T ) == 24 ) 
					  gluBuild2DMipmaps( GL_TEXTURE_2D, 3, T_->w, T_->h, GL_RGB, GL_UNSIGNED_BYTE, T_->c );
				  else 
				  if( T_->bpp/sizeof( T ) == 8 ) 
					  gluBuild2DMipmaps( GL_TEXTURE_2D, 1, T_->w, T_->h, GL_LUMINANCE, GL_UNSIGNED_BYTE, T_->c );
			  } else
			  if( typeid( T ) == typeid( float ) ) {
				  if( T_->bpp/sizeof( T ) == 32 ) 
					  gluBuild2DMipmaps( GL_TEXTURE_2D, 4, T_->w, T_->h, GL_RGBA, GL_FLOAT, T_->c );
				  else 
				  if( T_->bpp/sizeof( T ) == 24 ) 
					  gluBuild2DMipmaps( GL_TEXTURE_2D, 3, T_->w, T_->h, GL_RGB, GL_FLOAT, T_->c );
				  else 
				  if( T_->bpp/sizeof( T ) == 8 ) 
					  gluBuild2DMipmaps( GL_TEXTURE_2D, 1, T_->w, T_->h, GL_LUMINANCE, GL_FLOAT, T_->c );
			  }
		  } else {
			  if( linear ) glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR ); else
				           glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
			
			  if( typeid( T ) == typeid( BYTE ) || typeid( T ) == typeid( unsigned char ) ) {
				  if( T_->bpp/sizeof( T ) == 32 ) 			
					  glTexImage2D( GL_TEXTURE_2D, 0, 4, T_->w, T_->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, T_->c );
				  else 
				  if( T_->bpp/sizeof( T ) == 24 ) 
					  glTexImage2D( GL_TEXTURE_2D, 0, 3, T_->w, T_->h, 0, GL_RGB, GL_UNSIGNED_BYTE, T_->c );
				  else 
				  if( T_->bpp/sizeof( T ) == 8 ) 
					  glTexImage2D( GL_TEXTURE_2D, 0, 1, T_->w, T_->h, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, T_->c );
			  } else
			  if( typeid( T ) == typeid( float ) ) {
				  if( T_->bpp/sizeof( T ) == 32 ) 			
					  glTexImage2D( GL_TEXTURE_2D, 0, 4, T_->w, T_->h, 0, GL_RGBA, GL_FLOAT, T_->c );
				  else 
				  if( T_->bpp/sizeof( T ) == 24 ) 
					  glTexImage2D( GL_TEXTURE_2D, 0, 3, T_->w, T_->h, 0, GL_RGB, GL_FLOAT, T_->c );
				  else 
				  if( T_->bpp/sizeof( T ) == 8 ) 
					  glTexImage2D( GL_TEXTURE_2D, 0, 1, T_->w, T_->h, 0, GL_LUMINANCE, GL_FLOAT, T_->c );
			  }
		  }
	  }
  }




  template <typename T> void rasterizelinE( long Ax, long Ay, long Bx, long By, const coloR& c, texturE<T> *T_ ) {
	  if( typeid( T ) == typeid( BYTE ) || typeid( T ) == typeid( unsigned char ) ) {
		  long l, x, y, dx, dy, D, step;
		  valuE val, a, b, c_, inv_a, inv_b, t0, t1, t, o1, o2;
	
	
		  a = Ay-By;  b = Bx-Ax;
		  val = 1.0/sqrT( a*a+b*b );
		  a *= val;  b *= val;
		  c_ = -( a*Ax+b*Ay );
	      inv_a = diV( 1.0, a, 0.0 );  inv_b = diV( 1.0, b, 0.0 );
	
		  dx = abs( Bx-Ax );  dy = abs( By-Ay );
		  if( dx >= dy ) {
			  if( Ax > Bx ) {
				  l = Ax;  Ax = Bx;  Bx = l;
				  l = Ay;  Ay = By;  By = l;
			  }
			  if( Ay > By ) step = -1; else step = 1;
	
		      D = 2*dy-dx; 
			  y = Ay; 
		      for( x = Ax;  x <= Bx;  x++ ) {
				  if( D <= 0 ) { 
					  D += 2*dy; 
				  } else {
			          D += 2*( dy-dx ); 
					  y += step;
		          }
	
				  t = -( a*x+b*y+b*0.5+c_ )*inv_a;
				  t0 = fabs( a*t );
				  t1 = fabs( a*( 1.0-t ) );
	
				  if( t > 1.0 ) {
					  o1 = 0.0;	
					  o2 = clamP( t1+( t0-t1 )*0.5, 0.0, 1.0 );
				  } else 
				  if( t >= 0.0 ) {
					  if( step == 1 ) {
						  o1 = clamP( t1*( 1.0-t )*0.5, 0.0, 1.0 );
						  o2 = clamP( t0*t*0.5, 0.0, 1.0 );	
					  } else {
						  o1 = clamP( t0*t*0.5, 0.0, 1.0 );	
						  o2 = clamP( t1*( 1.0-t )*0.5, 0.0, 1.0 );
					  }
				  } else {
					  o1 = 0.0;	
					  o2 = clamP( t0+( t1-t0 )*0.5, 0.0, 1.0 );
				  }	
	
				  val = 1.0-o1-o2;
				  if( ( x == Ax && y == Ay ) || ( x == Bx && y == By ) ) val *= 0.5;
				  if( T_->bpp == 32 ) {
					  T_->setcoloR( x, y, val*255.0*c.r+( 1.0-val )*T_->getreD( x, y ), val*255.0*c.g+( 1.0-val )*T_->getgreeN( x, y ), val*255.0*c.b+( 1.0-val )*T_->getbluE( x, y ), val*255.0*c.a+( 1.0-val )*T_->getalphA( x, y ) );
				  } else 
				  if( T_->bpp == 24 ) {
					  T_->setcoloR( x, y, val*255.0*c.r+( 1.0-val )*T_->getreD( x, y ), val*255.0*c.g+( 1.0-val )*T_->getgreeN( x, y ), val*255.0*c.b+( 1.0-val )*T_->getbluE( x, y ), 0 );
				  } else
				  if( T_->bpp == 16 ) {
					  T_->setcoloR( x, y, val*255.0*c.r+( 1.0-val )*T_->getreD( x, y ), val*255.0*c.g+( 1.0-val )*T_->getgreeN( x, y ), 0, 0 );
				  } else
				  if( T_->bpp == 8 ) {
					  T_->setreD( x, y, val*255.0*c.r+( 1.0-val )*T_->getreD( x, y ) );
				  }
				  val = o1;
				  if( T_->bpp == 32 ) {
					  T_->setcoloR( x, y+1, val*255.0*c.r+( 1.0-val )*T_->getreD( x, y+1 ), val*255.0*c.g+( 1.0-val )*T_->getgreeN( x, y+1 ), val*255.0*c.b+( 1.0-val )*T_->getbluE( x, y+1 ), val*255.0*c.a+( 1.0-val )*T_->getalphA( x, y+1 ) );
				  } else 
				  if( T_->bpp == 24 ) {
					  T_->setcoloR( x, y+1, val*255.0*c.r+( 1.0-val )*T_->getreD( x, y+1 ), val*255.0*c.g+( 1.0-val )*T_->getgreeN( x, y+1 ), val*255.0*c.b+( 1.0-val )*T_->getbluE( x, y+1 ), 0 );
				  } else
				  if( T_->bpp == 16 ) {
					  T_->setcoloR( x, y+1, val*255.0*c.r+( 1.0-val )*T_->getreD( x, y+1 ), val*255.0*c.g+( 1.0-val )*T_->getgreeN( x, y+1 ), 0, 0 );
				  } else
				  if( T_->bpp == 8 ) {
					  T_->setreD( x, y+1, val*255.0*c.r+( 1.0-val )*T_->getreD( x, y+1 ) );
				  }
				  val = o2;
				  if( T_->bpp == 32 ) {
					  T_->setcoloR( x, y-1, val*255.0*c.r+( 1.0-val )*T_->getreD( x, y-1 ), val*255.0*c.g+( 1.0-val )*T_->getgreeN( x, y-1 ), val*255.0*c.b+( 1.0-val )*T_->getbluE( x, y-1 ), val*255.0*c.a+( 1.0-val )*T_->getalphA( x, y-1 ) );
				  } else 
				  if( T_->bpp == 24 ) {
					  T_->setcoloR( x, y-1, val*255.0*c.r+( 1.0-val )*T_->getreD( x, y-1 ), val*255.0*c.g+( 1.0-val )*T_->getgreeN( x, y-1 ), val*255.0*c.b+( 1.0-val )*T_->getbluE( x, y-1 ), 0 );
				  } else
				  if( T_->bpp == 16 ) {
					  T_->setcoloR( x, y-1, val*255.0*c.r+( 1.0-val )*T_->getreD( x, y-1 ), val*255.0*c.g+( 1.0-val )*T_->getgreeN( x, y-1 ), 0, 0 );
				  } else
				  if( T_->bpp == 8 ) {
					  T_->setreD( x, y-1, val*255.0*c.r+( 1.0-val )*T_->getreD( x, y-1 ) );
				  }
			  }
		  } else {
			  if( Ay > By ) {
				  l = Ax;  Ax = Bx;  Bx = l;
				  l = Ay;  Ay = By;  By = l;
			  }
			  if( Ax > Bx ) step = -1; else step = 1;
	
		      D = 2*dx-dy; 
			  x = Ax; 
		      for( y = Ay;  y <= By;  y++ ) {
				  if( D <= 0 ) { 
					  D += 2*dx; 
				  } else {
			          D += 2*( dx-dy ); 
					  x += step;
		          }
	
				  t = -( a*x+b*y+a*0.5+c_ )*inv_b;
				  t0 = fabs( b*t );
				  t1 = fabs( b*( 1.0-t ) );
	
				  if( t > 1.0 ) {
					  o1 = 0.0;	
					  o2 = clamP( t1+( t0-t1 )*0.5, 0.0, 1.0 );
				  } else 
				  if( t >= 0.0 ) {
					  if( step == 1 ) {
						  o1 = clamP( t1*( 1.0-t )*0.5, 0.0, 1.0 );
						  o2 = clamP( t0*t*0.5, 0.0, 1.0 );	
					  } else {
						  o1 = clamP( t0*t*0.5, 0.0, 1.0 );	
						  o2 = clamP( t1*( 1.0-t )*0.5, 0.0, 1.0 );
					  }
				  } else {
					  o1 = 0.0;	
					  o2 = clamP( t0+( t1-t0 )*0.5, 0.0, 1.0 );
				  }	
	
				  val = 1.0-o1-o2;
				  if( ( x == Ax && y == Ay ) || ( x == Bx && y == By ) ) val *= 0.5;
				  if( T_->bpp == 32 ) {
					  T_->setcoloR( x, y, val*255.0*c.r+( 1.0-val )*T_->getreD( x, y ), val*255.0*c.g+( 1.0-val )*T_->getgreeN( x, y ), val*255.0*c.b+( 1.0-val )*T_->getbluE( x, y ), val*255.0*c.a+( 1.0-val )*T_->getalphA( x, y ) );
				  } else 
				  if( T_->bpp == 24 ) {
					  T_->setcoloR( x, y, val*255.0*c.r+( 1.0-val )*T_->getreD( x, y ), val*255.0*c.g+( 1.0-val )*T_->getgreeN( x, y ), val*255.0*c.b+( 1.0-val )*T_->getbluE( x, y ), 0 );
				  } else
				  if( T_->bpp == 16 ) {
					  T_->setcoloR( x, y, val*255.0*c.r+( 1.0-val )*T_->getreD( x, y ), val*255.0*c.g+( 1.0-val )*T_->getgreeN( x, y ), 0, 0 );
				  } else
				  if( T_->bpp == 8 ) {
					  T_->setreD( x, y, val*255.0*c.r+( 1.0-val )*T_->getreD( x, y ) );
				  }
				  val = o1;
				  if( T_->bpp == 32 ) {
					  T_->setcoloR( x+1, y, val*255.0*c.r+( 1.0-val )*T_->getreD( x+1, y ), val*255.0*c.g+( 1.0-val )*T_->getgreeN( x+1, y ), val*255.0*c.b+( 1.0-val )*T_->getbluE( x+1, y ), val*255.0*c.a+( 1.0-val )*T_->getalphA( x+1, y ) );
				  } else 
				  if( T_->bpp == 24 ) {
					  T_->setcoloR( x+1, y, val*255.0*c.r+( 1.0-val )*T_->getreD( x+1, y ), val*255.0*c.g+( 1.0-val )*T_->getgreeN( x+1, y ), val*255.0*c.b+( 1.0-val )*T_->getbluE( x+1, y ), 0 );
				  } else
				  if( T_->bpp == 16 ) {
					  T_->setcoloR( x+1, y, val*255.0*c.r+( 1.0-val )*T_->getreD( x+1, y ), val*255.0*c.g+( 1.0-val )*T_->getgreeN( x+1, y ), 0, 0 );
				  } else
				  if( T_->bpp == 8 ) {
					  T_->setreD( x+1, y, val*255.0*c.r+( 1.0-val )*T_->getreD( x+1, y ) );
				  }
				  val = o2;
				  if( T_->bpp == 32 ) {
					  T_->setcoloR( x-1, y, val*255.0*c.r+( 1.0-val )*T_->getreD( x-1, y ), val*255.0*c.g+( 1.0-val )*T_->getgreeN( x-1, y ), val*255.0*c.b+( 1.0-val )*T_->getbluE( x-1, y ), val*255.0*c.a+( 1.0-val )*T_->getalphA( x-1, y ) );
				  } else 
				  if( T_->bpp == 24 ) {
					  T_->setcoloR( x-1, y, val*255.0*c.r+( 1.0-val )*T_->getreD( x-1, y ), val*255.0*c.g+( 1.0-val )*T_->getgreeN( x-1, y ), val*255.0*c.b+( 1.0-val )*T_->getbluE( x-1, y ), 0 );
				  } else
				  if( T_->bpp == 16 ) {
					  T_->setcoloR( x-1, y, val*255.0*c.r+( 1.0-val )*T_->getreD( x-1, y ), val*255.0*c.g+( 1.0-val )*T_->getgreeN( x-1, y ), 0, 0 );
				  } else
				  if( T_->bpp == 8 ) {
					  T_->setreD( x-1, y, val*255.0*c.r+( 1.0-val )*T_->getreD( x-1, y ) );
				  }
			  }
		  }
	  }
  }








  // TEXTUREARRAY TEMPLATE
  template <typename T> class texturearraY: public arraY_< texturE<T> > {};
