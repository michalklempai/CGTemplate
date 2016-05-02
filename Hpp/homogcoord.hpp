
  // HOMOGCOORD
  class homogcoorD {
      public:
          valuE x, y, z, w; 


          homogcoorD( void );
          homogcoorD( const vectoR& v );
          homogcoorD( const poinT& pt );
          homogcoorD( valuE x, valuE y, valuE z = 0.0, valuE w = 1.0 );
          homogcoorD( const homogcoorD& hc );

          homogcoorD operator+( void ) const;
          homogcoorD operator-( void ) const;
          
          homogcoorD operator*( valuE val ) const;
          friend homogcoorD operator*( valuE val, const homogcoorD& hc );
          homogcoorD operator/( valuE val ) const;
          homogcoorD& operator*=( valuE val );
          homogcoorD& operator/=( valuE val );
          
          homogcoorD operator+( const vectoR& v ) const;
          friend homogcoorD operator+( const vectoR& v, const homogcoorD& hc );
          homogcoorD operator-( const vectoR& v ) const;
          friend homogcoorD operator-( const vectoR& v, const homogcoorD& hc );
   		  homogcoorD& operator+=( const vectoR& v );
          homogcoorD& operator-=( const vectoR& v );
		  BOOL operator==( const vectoR& v ) const;
          BOOL operator!=( const vectoR& v ) const;

          homogcoorD operator+( const poinT& pt ) const;
          friend homogcoorD operator+( const poinT& pt, const homogcoorD& hc );
          homogcoorD operator-( const poinT& pt ) const;
          friend homogcoorD operator-( const poinT& pt, const homogcoorD& hc );
   		  homogcoorD& operator+=( const poinT& pt );
          homogcoorD& operator-=( const poinT& pt );
		  BOOL operator==( const poinT& pt ) const;
          BOOL operator!=( const poinT& pt ) const;

          homogcoorD operator+( const homogcoorD& hc ) const;
          homogcoorD operator-( const homogcoorD& hc ) const;
   		  homogcoorD& operator+=( const homogcoorD& hc );
   		  homogcoorD& operator-=( const homogcoorD& hc );
		  BOOL operator==( const homogcoorD& hc ) const;
          BOOL operator!=( const homogcoorD& hc ) const;
  };

         
  inline BOOL isvectoR( const homogcoorD& hc ); 
  inline BOOL ispoinT( const homogcoorD& hc ); 
  inline homogcoorD normalizeweighT( const homogcoorD& hc );






  inline homogcoorD::homogcoorD( void ) {
      x = y = z = w = 0.0;
  }




  inline homogcoorD::homogcoorD( const vectoR& v ) {
      x = v.x;  y = v.y;  z = v.z;  w = 0.0;
  }
  
  
  
  
  inline homogcoorD::homogcoorD( const poinT& pt ) {
      x = pt.x;  y = pt.y;  z = pt.z;  w = 1.0;
  }




  inline homogcoorD::homogcoorD( valuE x, valuE y, valuE z, valuE w ) {
      this->x = x;  this->y = y;  this->z = z;  this->w = w; 
  }




  inline homogcoorD::homogcoorD( const homogcoorD& hc ) {
      x = hc.x;  y = hc.y;  z = hc.z;  w = hc.w;
  }




  inline homogcoorD homogcoorD::operator+( void ) const {
      return *this;
  }
  
  
  
  
  inline homogcoorD homogcoorD::operator-( void ) const {
      return homogcoorD( -x, -y, -z, -w );
  }
  
  
  
  
  inline homogcoorD homogcoorD::operator*( valuE val ) const {
      return homogcoorD( x*val, y*val, z*val, w*val );
  }
  
  
  
  
  inline homogcoorD operator*( valuE val, const homogcoorD& hc ) {
      return homogcoorD( val*hc.x, val*hc.y, val*hc.z, val*hc.w );
  }
  
  
  
  
  inline homogcoorD homogcoorD::operator/( valuE val ) const {
      if( abs( val ) > EPSILON ) {
    	  valuE inv_val = 1.0/val;

          return homogcoorD( x*inv_val, y*inv_val, z*inv_val, w*inv_val );
      } else return homogcoorD();
  }
  
  
  
  
  inline homogcoorD& homogcoorD::operator*=( valuE val ) {
      x*=val;  y*=val;  z*=val;  w*=val;

      return *this;
  }



  
  inline homogcoorD& homogcoorD::operator/=( valuE val ) {
      if( abs( val ) > EPSILON ) {
    	  valuE inv_val = 1.0/val;

          x*=inv_val;  y*=inv_val;  z*=inv_val;  w*=inv_val;
      }
      
      return *this;
  }



  
  inline homogcoorD homogcoorD::operator+( const vectoR& v ) const {
      return homogcoorD( x+v.x, y+v.y, z+v.z, w );
  }
  
  
  
  
  inline homogcoorD operator+( const vectoR& v, const homogcoorD& hc ) {
      return homogcoorD( v.x+hc.x, v.y+hc.y, v.z+hc.z, hc.w );
  }
  
  
  
  
  inline homogcoorD homogcoorD::operator-( const vectoR& v ) const {
      return homogcoorD( x-v.x, y-v.y, z-v.z, w );
  }
  
  
  
  
  inline homogcoorD operator-( const vectoR& v, const homogcoorD& hc ) {
      return homogcoorD( v.x-hc.x, v.y-hc.y, v.z-hc.z, -hc.w );
  }
  
  
  
  
  inline homogcoorD& homogcoorD::operator+=( const vectoR& v ) {
      x+=v.x;  y+=v.y;  z+=v.z;

      return *this;
  }
  
  
  
  
  inline homogcoorD& homogcoorD::operator-=( const vectoR& v ) {
      x-=v.x;  y-=v.y;  z-=v.z;

      return *this;
  }
  
  
  
  
  inline BOOL homogcoorD::operator==( const vectoR& v ) const {
      return x == v.x && y == v.y && z == v.z && w == 0.0;
  }
  
  
  
  
  inline BOOL homogcoorD::operator!=( const vectoR& v ) const {
      return x != v.x || y != v.y || z != v.z || w != 0.0;
  }
  
  
  

  inline homogcoorD homogcoorD::operator+( const poinT& pt ) const {
      return homogcoorD( x+pt.x, y+pt.y, z+pt.z, w+1.0 );
  }
  
  
  
  
  inline homogcoorD operator+( const poinT& pt, const homogcoorD& hc ) {
      return homogcoorD( pt.x+hc.x, pt.y+hc.y, pt.z+hc.z, 1.0+hc.w );
  }
  
  
  
  
  inline homogcoorD homogcoorD::operator-( const poinT& pt ) const {
      return homogcoorD( x-pt.x, y-pt.y, z-pt.z, w-1.0 );
  }
  
  
  
  
  inline homogcoorD operator-( const poinT& pt, const homogcoorD& hc ) {
      return homogcoorD( pt.x-hc.x, pt.y-hc.y, pt.z-hc.z, 1.0-hc.w );
  }
  
  
  
  
  inline homogcoorD& homogcoorD::operator+=( const poinT& pt ) {
      x+=pt.x;  y+=pt.y;  z+=pt.z;  w+=1.0;

      return *this;
  }
  
  
  
  
  inline homogcoorD& homogcoorD::operator-=( const poinT& pt ) {
      x-=pt.x;  y-=pt.y;  z-=pt.z;  w-=1.0;

      return *this;
  }
  
  
  
  
  inline BOOL homogcoorD::operator==( const poinT& pt ) const {
      return x == pt.x && y == pt.y && z == pt.z && w == 1.0;
  }
  
  
  
  
  inline BOOL homogcoorD::operator!=( const poinT& pt ) const {
      return x != pt.x || y != pt.y || z != pt.z || w != 1.0;
  }
  
  
  

  inline homogcoorD homogcoorD::operator+( const homogcoorD& hc ) const {
      return homogcoorD( x+hc.x, y+hc.y, z+hc.z, w+hc.w );
  }
  
  
  
  
  inline homogcoorD homogcoorD::operator-( const homogcoorD& hc ) const {
      return homogcoorD( x-hc.x, y-hc.y, z-hc.z, w-hc.w );
  }
  
  
  
  
  inline homogcoorD& homogcoorD::operator+=( const homogcoorD& hc ) {
      x+=hc.x;  y+=hc.y;  z+=hc.z;  w+=hc.w;

      return *this;
  }
  
  
  
  
  inline homogcoorD& homogcoorD::operator-=( const homogcoorD& hc ) {
      x-=hc.x;  y-=hc.y;  z-=hc.z;  w-=hc.w;

      return *this;
  }
  
  
  
  
  inline BOOL homogcoorD::operator==( const homogcoorD& hc ) const {
      return x == hc.x && y == hc.y && z == hc.z && w == hc.w;
  }
  
  
  
  
  inline BOOL homogcoorD::operator!=( const homogcoorD& hc ) const {
      return x != hc.x || y != hc.y || z != hc.z || w != hc.w;
  }




  inline BOOL isvectoR( const homogcoorD& hc ) {
      return abs( hc.w ) < EPSILON ? TRUE : FALSE;
  }




  inline BOOL ispoinT( const homogcoorD& hc ) {
      return abs( hc.w ) >= EPSILON ? TRUE : FALSE;
  }




  inline homogcoorD normalizeweighT( const homogcoorD& hc ) {
      if( abs( hc.w ) >= EPSILON ) {	  
          valuE val = 1.0/hc.w;
          
    	  return homogcoorD( hc.x*val, hc.y*val, hc.z*val, 1.0 );
      } else {
    	  return homogcoorD( hc.x, hc.y, hc.z, 0.0 );
      }
  }






            

  // HOMOGCOORDARRAY
  class homogcoordarraY: public arraY<homogcoorD> {};
