
  #undef E0
  #undef E1
  #undef E2

  #define E0 vectoR( 1.0, 0.0, 0.0 )
  #define E1 vectoR( 0.0, 1.0, 0.0 )
  #define E2 vectoR( 0.0, 0.0, 1.0 )








  // VECTOR
  class vectoR {
      public:
          valuE x, y, z; 


          vectoR( void );
          vectoR( valuE alpha, valuE beta );  // <0.0, 2.0*PI) x <0.0, PI>
          vectoR( valuE x, valuE y, valuE z );
          vectoR( const vectoR& v );

          vectoR operator+( void ) const;
          vectoR operator-( void ) const;

		  vectoR operator*( valuE val ) const;
		  friend vectoR operator*( valuE val, const vectoR& v );
		  vectoR operator/( valuE val ) const;
		  vectoR& operator*=( valuE val );
          vectoR& operator/=( valuE val );

		  vectoR operator+( const vectoR& v ) const;
          vectoR operator-( const vectoR& v ) const;
		  vectoR& operator+=( const vectoR& v );
          vectoR& operator-=( const vectoR& v );
		  BOOL operator==( const vectoR& v ) const;
          BOOL operator!=( const vectoR& v ) const;
  };

         
  inline valuE lengtH( const vectoR& v ); 
  inline valuE squarelengtH( const vectoR& v ); 
  inline vectoR normalizE( const vectoR& v );
  inline valuE doT( const vectoR& u, const vectoR& v );
  inline vectoR crosS( const vectoR& u, const vectoR& v );
  inline vectoR reflecT( const vectoR& u, const vectoR& v );
  inline vectoR refracT( const vectoR& u, const vectoR& v, valuE ni, valuE nt );
  inline vectoR halfwaY( const vectoR& u, const vectoR& v );
  inline vectoR randomvectoR( void );
  inline void orthonormalbasE( const vectoR& w, vectoR *u, vectoR *v );  // w must be normalized
  inline BOOL lindependenT( const vectoR& u, const vectoR& v );
  inline void sphericalcoorD( const vectoR& u, valuE *s, valuE *t );  // <0.0, 1.0) x <0.0, 1.0>
  inline void hemisphericalcoorD( const vectoR& u, valuE *s, valuE *t );  
  inline void cubecoorD( const vectoR& u, valuE *s, valuE *t );
  inline void lightprobecoorD( const vectoR& u, valuE *s, valuE *t );
  inline vectoR inverselightprobecoorD( valuE s, valuE t, vectoR *u = NULL );  // <0.0, 1.0> x <0.0, 1.0>






  inline vectoR::vectoR( void ) {
      x = y = z = 0.0;
  }




  inline vectoR::vectoR( valuE alpha, valuE beta ) {
	  y = cos( beta-PI_OVER2 );
	  x = sin( alpha )*y;
	  z = cos( alpha )*y;
	  y = sin( beta-PI_OVER2 );
  }




  inline vectoR::vectoR( valuE x, valuE y, valuE z ) {
      this->x = x;  this->y = y;  this->z = z;
  }




  inline vectoR::vectoR( const vectoR& v ) {
      x = v.x;  y = v.y;  z = v.z;
  }




  inline vectoR vectoR::operator+( void ) const {
      return *this;
  }




  inline vectoR vectoR::operator-( void ) const {
      return vectoR( -x, -y, -z );  
  }




  inline vectoR vectoR::operator*( valuE val ) const {
      return vectoR( x*val, y*val, z*val );
  }




  inline vectoR operator*( valuE val, const vectoR& v ) {
      return vectoR( val*v.x, val*v.y, val*v.z );
  }




  inline vectoR vectoR::operator/( valuE val ) const {
      if( abs( val ) > EPSILON ) {
    	  valuE inv_val = 1.0/val;

          return vectoR( x*inv_val, y*inv_val, z*inv_val );
      } else return vectoR();
  }




  inline vectoR& vectoR::operator*=( valuE val ) {
      x*=val;  y*=val;  z*=val;

      return *this;
  }




  inline vectoR& vectoR::operator/=( valuE val ) {
      if( abs( val ) > EPSILON ) {
    	  valuE inv_val = 1.0/val;

          x*=inv_val;  y*=inv_val;  z*=inv_val;
      }
      
      return *this;
  }




  inline vectoR vectoR::operator+( const vectoR& v ) const {
      return vectoR( x+v.x, y+v.y, z+v.z );
  }




  inline vectoR vectoR::operator-( const vectoR& v ) const {
      return vectoR( x-v.x, y-v.y, z-v.z );
  }




  inline vectoR& vectoR::operator+=( const vectoR& v ) {
      x+=v.x;  y+=v.y;  z+=v.z;

      return *this;
  }




  inline vectoR& vectoR::operator-=( const vectoR& v ) {
      x-=v.x;  y-=v.y;  z-=v.z;

      return *this;
  }




  inline BOOL vectoR::operator==( const vectoR& v ) const {
      return x == v.x && y == v.y && z == v.z;
  }




  inline BOOL vectoR::operator!=( const vectoR& v ) const {
      return x != v.x || y != v.y || z != v.z;
  }




  inline valuE lengtH( const vectoR& v ) { 
      return sqrt( v.x*v.x+v.y*v.y+v.z*v.z ); 
  }




  inline valuE squarelengtH( const vectoR& v ) { 
      return v.x*v.x+v.y*v.y+v.z*v.z; 
  }




  inline vectoR normalizE( const vectoR& v ) {
	  valuE val = sqrt( v.x*v.x+v.y*v.y+v.z*v.z );

      if( abs( val ) < EPSILON ) {
          return vectoR();
      } else {
          val = 1.0/val;

          return vectoR( v.x*val, v.y*val, v.z*val );
      }
  }




  inline valuE doT( const vectoR& u, const vectoR& v ) {
      return u.x*v.x+u.y*v.y+u.z*v.z;
  }




  inline vectoR crosS( const vectoR& u, const vectoR& v ) {
      return vectoR( u.y*v.z-u.z*v.y, u.z*v.x-u.x*v.z, u.x*v.y-u.y*v.x );
  }




  inline vectoR reflecT( const vectoR& u, const vectoR& v ) {
	  valuE a = 2.0*doT( u, v );

	  return v*a-u;
  }




  inline vectoR refracT( const vectoR& u, const vectoR& v, valuE ni, valuE nt ) {
	  valuE eta = ni/nt, a = doT( u, v ), b = 1.0-eta*eta*( 1.0-a*a );

	  return b < 0.0 ? vectoR() : ( v*a-u )*eta-v*sqrt( b );
  }




  inline vectoR halfwaY( const vectoR& u, const vectoR& v ) {
	  return normalizE( u+v );
  }




  inline vectoR randomvectoR( void ) {
	  vectoR v;

      do {
	      v.x = randomvaluE( -1.0, 1.0 );
		  v.y = randomvaluE( -1.0, 1.0 );
		  v.z = randomvaluE( -1.0, 1.0 );
	  } while( squarelengtH( v ) > 1.0 );

	  return normalizE( v );
  }




  inline void orthonormalbasE( const vectoR& w, vectoR *u, vectoR *v ) {
	  valuE val;

	  if( abs( w.x ) <= abs( w.y ) ) {
		  if( abs( w.x ) <= abs( w.z ) ) { // min abs( w.x )
			  u->x = 0.0;  u->y = -w.z;  u->z = w.y;
			  val = diV( 1.0, sqrT( sqR( u->y )+sqR( u->z ) ), 0.0 );	
			  u->y *= val;  u->z *= val;  
		  } else { // min abs( w.z )
			  u->x = -w.y;  u->y = w.x;  u->z = 0.0;
			  val = diV( 1.0, sqrT( sqR( u->x )+sqR( u->y ) ), 0.0 );	
			  u->x *= val;  u->y *= val;  
		  }
	  } else {
		  if( abs( w.y ) <= abs( w.z ) ) { // min abs( w.y )
			  u->x = w.z;  u->y = 0.0;  u->z = -w.x;
			  val = diV( 1.0, sqrT( sqR( u->x )+sqR( u->z ) ), 0.0 );	
			  u->x *= val;  u->z *= val;  
		  } else { // min abs( w.z )
			  u->x = -w.y;  u->y = w.x;  u->z = 0.0;
			  val = diV( 1.0, sqrT( sqR( u->x )+sqR( u->y ) ), 0.0 );	
			  u->x *= val;  u->y *= val;  
		  }
	  }

	  *v = normalizE( crosS( *u, w ) );
  }




  inline void sphericalcoorD( const vectoR& u, valuE *s, valuE *t ) {
	  if( abs( u.y ) > 1.0-EPSILON ) {
		  *s = 0.0;
		  if( u.y >= 0.0 ) *t = 1.0; else *t = -1.0;
	  } else {
		  *t = acos( -u.y )*INV_PI;
		  if( u.x >= 0.0 ) *s = acos( u.z/sqrT( sqR( u.x )+sqR( u.z ) ) )*INV_PI_TIMES2; else 
			               *s = 0.5+acos( -u.z/sqrT( sqR( u.x )+sqR( u.z ) ) )*INV_PI_TIMES2;
	  }
  }




  inline void hemisphericalcoorD( const vectoR& u, valuE *s, valuE *t ) {
	  if( abs( u.y ) > 1.0-EPSILON ) {
		  *s = 0.0;
		  *t = 1.0; 
	  } else {
		  if( u.y >= 0.0 ) *t = acos( -u.y )*INV_PI*2.0-1.0; else *t = 1.0-acos( -u.y )*INV_PI*2.0;
		  if( u.x >= 0.0 ) *s = acos( u.z/sqrT( sqR( u.x )+sqR( u.z ) ) )*INV_PI_TIMES2; else 
			               *s = 0.5+acos( -u.z/sqrT( sqR( u.x )+sqR( u.z ) ) )*INV_PI_TIMES2;
	  }
  }




  inline void cubecoorD( const vectoR& u, valuE *s, valuE *t ) {
	  valuE val;
	  vectoR v = vectoR( abs( u.x ), abs( u.y ), abs( u.z ) );

	  if( v.x >= v.y ) {
		  if( v.x >= v.z ) {
			  val = 1.0/v.x;
			  *s = ( u.z*val+1.0 )*0.5;
			  *t = ( u.y*val+1.0 )*0.5;

			  if( u.x >= 0.0 ) {
				  *s = ( *s+3.0 )*0.25;
				  *t = ( *t+1.0 )/3.0;
			  } else {
				  *s = ( 2.0-*s )*0.25;
				  *t = ( *t+1.0 )/3.0;
			  }
		  } else {
			  val = 1.0/v.z;
			  *s = ( u.x*val+1.0 )*0.5;
			  *t = ( u.y*val+1.0 )*0.5;

			  if( u.z >= 0.0 ) {
				  *s = ( 1.0-*s )*0.25;
				  *t = ( *t+1.0 )/3.0;
			  } else {
				  *s = ( *s+2.0 )*0.25;
				  *t = ( *t+1.0 )/3.0;
			  }
		  }
	  } else {
		  if( v.y >= v.z ) {
			  val = 1.0/v.y;
			  *s = ( u.z*val+1.0 )*0.5;
			  *t = ( u.x*val+1.0 )*0.5;

			  if( u.y >= 0.0 ) {
				  *s = ( 2.0-*s )*0.25;
				  *t = ( *t+2.0 )/3.0;
			  } else {
				  *s = ( 2.0-*s )*0.25;
				  *t = ( 1.0-*t )/3.0;
			  }
		  } else {
			  val = 1.0/v.z;
			  *s = ( u.x*val+1.0 )*0.5;
			  *t = ( u.y*val+1.0 )*0.5;

			  if( u.z >= 0.0 ) {
				  *s = ( 1.0-*s )*0.25;
				  *t = ( *t+1.0 )/3.0;
			  } else {
				  *s = ( *s+2.0 )*0.25;
				  *t = ( *t+1.0 )/3.0;
			  }
		  }
	  }
  }




  inline void lightprobecoorD( const vectoR& u, valuE *s, valuE *t ) {
	  valuE val;

	  val = diV( acos( u.z ), sqrT( sqR( u.x )+sqR( u.y ) ), 0.0 )*INV_PI*0.5;

	  *s = u.x*val+0.5;
	  *t = 0.5-u.y*val;
  }




  inline vectoR inverselightprobecoorD( valuE s, valuE t, vectoR *u ) {
      valuE val, theta, phi;
	  vectoR v;

	  theta = atan2( t, s );
	  phi = sqrT( sqR( s )+sqR( t ) )*PI;

	  val = -sin( phi );
	  v = vectoR( val*cos( -theta ), val*sin( -theta ), -cos( phi ) );	

	  if( u != NULL ) return *u = v; else return v;
  }




  inline BOOL lindependenT( const vectoR& u, const vectoR& v ) {
      valuE val;

      val = doT( normalizE( u ), normalizE( v ) );      
      if( val > 0.0 ) {
          if( val < 1.0-EPSILON ) return FALSE;
      } else {
          if( val > -1.0+EPSILON ) return FALSE;
      }

      return TRUE;
  }








  // VECTORARRAY
  class vectorarraY: public arraY<vectoR> {};
