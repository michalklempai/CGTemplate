
  // QUATERNION
  class quaternioN {
      public:
          valuE x, y, z, w; 


          quaternioN( void );
          quaternioN( const vectoR& v, valuE val );
          quaternioN( valuE x, valuE y, valuE z, valuE w );
          quaternioN( const quaternioN& q );

          quaternioN operator+( void ) const;
          quaternioN operator-( void ) const;

		  quaternioN operator*( valuE val ) const;
		  friend quaternioN operator*( valuE val, const quaternioN& q );
		  quaternioN operator/( valuE val ) const;
		  quaternioN& operator*=( valuE val );
          quaternioN& operator/=( valuE val );

		  quaternioN operator+( const quaternioN& q ) const;
          quaternioN operator-( const quaternioN& q ) const;
          quaternioN operator*( const quaternioN& q ) const;
		  quaternioN& operator+=( const quaternioN& q );
          quaternioN& operator-=( const quaternioN& q );
          quaternioN& operator*=( const quaternioN& q );
		  BOOL operator==( const quaternioN& q ) const;
          BOOL operator!=( const quaternioN& q ) const;
  };


  inline quaternioN identitY_( void );
  inline valuE norM( const quaternioN& q );
  inline quaternioN conjugatE( const quaternioN& q );
  inline valuE doT( const quaternioN& q, const quaternioN& r );
  inline quaternioN multiplY( const quaternioN& q, const quaternioN& r );
  inline quaternioN inversE( const quaternioN& q );
  inline quaternioN slerP( const quaternioN& q, const quaternioN& r, valuE t );






  inline quaternioN::quaternioN( void ) {
      x = y = z = 0.0;
      w = 1.0;
  }




  inline quaternioN::quaternioN( const vectoR& v, valuE val ) {
      valuE a = sin( val );
      
      x = a*v.x;
      y = a*v.y;
      z = a*v.z;
      w = cos( val );
  }
  
  
  
  
  inline quaternioN::quaternioN( valuE x, valuE y, valuE z, valuE w ) {
      this->x = x;  this->y = y;  this->z = z;  this->w = w; 
  }




  inline quaternioN::quaternioN( const quaternioN& q ) {
      x = q.x;  y = q.y;  z = q.z;  w = q.w;
  }




  inline quaternioN quaternioN::operator+( void ) const {
      return *this;
  }
  
  
  
  
  inline quaternioN quaternioN::operator-( void ) const {
      return quaternioN( -x, -y, -z, -w );
  }




  inline quaternioN quaternioN::operator*( valuE val ) const {
      return quaternioN( x*val, y*val, z*val, w*val );
  }
  
  
  
  
  inline quaternioN operator*( valuE val, const quaternioN& q ) {
      return quaternioN( val*q.x, val*q.y, val*q.z, val*q.w );
  }
  
  
  
  
  inline quaternioN quaternioN::operator/( valuE val ) const {
      if( abs( val ) > EPSILON ) {
    	  valuE inv_val = 1.0/val;

          return quaternioN( x*inv_val, y*inv_val, z*inv_val, w*inv_val );
      } else return quaternioN();
  }
  
  
  
  
  inline quaternioN& quaternioN::operator*=( valuE val ) {
      x*=val;  y*=val;  z*=val;  w*=val;

      return *this;
  }
  
  
  
  
  inline quaternioN& quaternioN::operator/=( valuE val ) {
      if( abs( val ) > EPSILON ) {
    	  valuE inv_val = 1.0/val;

          x*=inv_val;  y*=inv_val;  z*=inv_val;  w*=inv_val;
      }
      
      return *this;
  }
  
  
  

  inline quaternioN quaternioN::operator+( const quaternioN& q ) const {
      return quaternioN( x+q.x, y+q.y, z+q.z, w+q.w );
  }
  
  
  
  
  inline quaternioN quaternioN::operator-( const quaternioN& q ) const {
      return quaternioN( x-q.x, y-q.y, z-q.z, w-q.w );
  }
  
  
  
  
  inline quaternioN quaternioN::operator*( const quaternioN& q ) const {
      vectoR v = crosS( vectoR( x, y, z ), vectoR( q.x, q.y, q.z ) );
  
      return quaternioN( v.x+q.w*x+w*q.x, v.y+q.w*y+w*q.y, v.z+q.w*z+w*q.z, w*q.w-( x*q.x+y*q.y+z*q.z ) );
  }
  
  
  
  
  inline quaternioN& quaternioN::operator+=( const quaternioN& q ) {
      x+=q.x;  y+=q.y;  z+=q.z;  w+=q.w;

      return *this;
  }
  
  
  
  
  inline quaternioN& quaternioN::operator-=( const quaternioN& q ) {
      x-=q.x;  y-=q.y;  z-=q.z;  w-=q.w;

      return *this;
  }
  
  
  
  
  inline quaternioN& quaternioN::operator*=( const quaternioN& q ) {
      vectoR u = vectoR( x, y, z ), v = crosS( u, vectoR( q.x, q.y, q.z ) );
  
      x = v.x+q.w*u.x+w*q.x;
      y = v.y+q.w*u.y+w*q.y;
      z = v.z+q.w*u.z+w*q.z;
      w = w*q.w-( u.x*q.x+u.y*q.y+u.z*q.z );

      return *this;
  }
  
  
  
  
  inline BOOL quaternioN::operator==( const quaternioN& q ) const {
      return x == q.x && y == q.y && z == q.z && w == q.w;
  }
  
  
  
  
  inline BOOL quaternioN::operator!=( const quaternioN& q ) const {
      return x != q.x || y != q.y || z != q.z || w != q.w;
  }




  inline quaternioN identitY_( void ) {
      return quaternioN( 0.0, 0.0, 0.0, 1.0 );
  }
  
  
  
  
  inline valuE norM( const quaternioN& q ) {
      return q.x*q.x+q.y*q.y+q.z*q.z+q.w*q.w;
  }
  
  
  
  
  inline quaternioN conjugatE( const quaternioN& q ) {
      return quaternioN( -q.x, -q.y, -q.z, q.w );
  }




  inline valuE doT( const quaternioN& q, const quaternioN& r ) {
      return q.x*r.x+q.y*r.y+q.z*r.z+q.w*r.w;
  }
  
  
  
  
  inline quaternioN multiplY( const quaternioN& q, const quaternioN& r ) {
      vectoR v = crosS( vectoR( q.x, q.y, q.z ), vectoR( r.x, r.y, r.z ) );
  
      return quaternioN( v.x+r.w*q.x+q.w*r.x, v.y+r.w*q.y+q.w*r.y, v.z+r.w*q.z+q.w*r.z, q.w*r.w-( q.x*r.x+q.y*r.y+q.z*r.z ) );
  }
  
  
  
  
  inline quaternioN inversE( const quaternioN& q ) {
      return conjugatE( q )/norM( q );
  }
  
  
  
  
  inline quaternioN slerP( const quaternioN& q, const quaternioN& r, valuE t ) {
      valuE val = acos( doT( q, r ) );
  
      return ( sin( val*( 1.0-t ) )*q+sin( val*t )*r )/sin( val );
  }






            

  // QUATERNIONARRAY
  class quaternionarraY: public arraY<quaternioN> {};
