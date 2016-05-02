
  // MATRIX
  class matriX {
      public:
  		  valuE _[4][4];


          matriX( void );
          matriX( valuE _00, valuE _01, valuE _02, valuE _03, valuE _10, valuE _11, valuE _12, valuE _13, 
			      valuE _20, valuE _21, valuE _22, valuE _23, valuE _30, valuE _31, valuE _32, valuE _33 );
          matriX( const matriX& mat );			      

          matriX operator+( void ) const;
          matriX operator-( void ) const;
          
          matriX operator*( valuE val ) const;
          friend matriX operator*( valuE val, const matriX& mat );
          matriX operator/( valuE val ) const;
          matriX& operator*=( valuE val );
          matriX& operator/=( valuE val );
          
          matriX operator+( const matriX& mat ) const;
          matriX operator-( const matriX& mat ) const;
          matriX operator*( const matriX& mat ) const;
          matriX& operator+=( const matriX& mat );
          matriX& operator-=( const matriX& mat );
          matriX& operator*=( const matriX& mat );
          BOOL operator==( const matriX& mat ) const;
          BOOL operator!=( const matriX& mat ) const;
  };


  inline matriX zerO( void );
  inline matriX identitY( void );
  inline homogcoorD multiplY( const homogcoorD& hc, const matriX& mat );
  inline vectoR multiplY( const vectoR& v, const matriX& mat );
  inline vectoR multiplytransposE( const vectoR& v, const matriX& mat );
  inline poinT multiplY( const poinT& pt, const matriX& mat );
  inline poinT multiplytransposE( const poinT& pt, const matriX& mat );
  inline matriX multiplY( const matriX& mat1, const matriX& mat2 );
  inline matriX multiplytransposE( const matriX& mat1, const matriX& mat2 );
  inline matriX transposE( const matriX& mat );
  inline valuE determinanT( const matriX& mat );
  inline matriX inversE( const matriX& mat );
  inline matriX translatE( const vectoR& t );
  inline matriX scalE( const vectoR& s );
  inline matriX rotateX( valuE a );
  inline matriX rotateY( valuE a );
  inline matriX rotateZ( valuE a );
  inline matriX rotatE( valuE a, const vectoR& v );
  inline matriX rotatE( const vectoR& u, const vectoR& v );
  inline matriX shearxY( valuE sh );
  inline matriX shearxZ( valuE sh );
  inline matriX shearyX( valuE sh );
  inline matriX shearyZ( valuE sh );
  inline matriX shearzX( valuE sh );
  inline matriX shearzY( valuE sh );
  inline matriX euleR( valuE head, valuE pitch, valuE roll );
  inline void euleR( const matriX& mat, valuE *head, valuE *pitch, valuE *roll );
  inline matriX mirroR( const planE& pl );
  inline matriX projecT( const planE& pl, const poinT& pt );
  inline matriX orthographiC( valuE l, valuE r, valuE b, valuE t, valuE n, valuE f );
  inline matriX perspectivE( valuE l, valuE r, valuE b, valuE t, valuE n, valuE f );
  inline matriX vieW( const poinT& C, const vectoR& n, const vectoR& v, BOOL lh = TRUE );
  inline matriX matrixinterP( valuE x, const matriX& mat, const matriX& mat2 );

  




  inline matriX::matriX( void ) {
      _[0][0] = 1.0;  _[0][1] = 0.0;  _[0][2] = 0.0;  _[0][3] = 0.0;
      _[1][0] = 0.0;  _[1][1] = 1.0;  _[1][2] = 0.0;  _[1][3] = 0.0;
      _[2][0] = 0.0;  _[2][1] = 0.0;  _[2][2] = 1.0;  _[2][3] = 0.0;
      _[3][0] = 0.0;  _[3][1] = 0.0;  _[3][2] = 0.0;  _[3][3] = 1.0;
  }
  
  
  
  
  inline matriX::matriX( valuE _00, valuE _01, valuE _02, valuE _03, valuE _10, valuE _11, valuE _12, valuE _13, 
		                 valuE _20, valuE _21, valuE _22, valuE _23, valuE _30, valuE _31, valuE _32, valuE _33 ) {
      _[0][0] = _00;  _[0][1] = _01;  _[0][2] = _02;  _[0][3] = _03;
      _[1][0] = _10;  _[1][1] = _11;  _[1][2] = _12;  _[1][3] = _13;
      _[2][0] = _20;  _[2][1] = _21;  _[2][2] = _22;  _[2][3] = _23;
      _[3][0] = _30;  _[3][1] = _31;  _[3][2] = _32;  _[3][3] = _33;
  }
  
  
  
  
  inline matriX::matriX( const matriX& mat ) {
      _[0][0] = mat._[0][0];  _[0][1] = mat._[0][1];  _[0][2] = mat._[0][2];  _[0][3] = mat._[0][3];
      _[1][0] = mat._[1][0];  _[1][1] = mat._[1][1];  _[1][2] = mat._[1][2];  _[1][3] = mat._[1][3];
      _[2][0] = mat._[2][0];  _[2][1] = mat._[2][1];  _[2][2] = mat._[2][2];  _[2][3] = mat._[2][3];
      _[3][0] = mat._[3][0];  _[3][1] = mat._[3][1];  _[3][2] = mat._[3][2];  _[3][3] = mat._[3][3];
  }
  
  
  

  inline matriX matriX::operator+( void ) const {
      return *this;
  }
  
  
  
  
  inline matriX matriX::operator-( void ) const {
   	  return matriX( -_[0][0], -_[0][1], -_[0][2], -_[0][3],
		             -_[1][0], -_[1][1], -_[1][2], -_[1][3],
					 -_[2][0], -_[2][1], -_[2][2], -_[2][3],
					 -_[3][0], -_[3][1], -_[3][2], -_[3][3] );
  }



  
  inline matriX matriX::operator*( valuE val ) const {
   	  return matriX( _[0][0]*val, _[0][1]*val, _[0][2]*val, _[0][3]*val,
		             _[1][0]*val, _[1][1]*val, _[1][2]*val, _[1][3]*val,
					 _[2][0]*val, _[2][1]*val, _[2][2]*val, _[2][3]*val,
					 _[3][0]*val, _[3][1]*val, _[3][2]*val, _[3][3]*val );
  }
  
  
  
  
  inline matriX operator*( valuE val, const matriX& mat ) {
   	  return matriX( val*mat._[0][0], val*mat._[0][1], val*mat._[0][2], val*mat._[0][3],
		             val*mat._[1][0], val*mat._[1][1], val*mat._[1][2], val*mat._[1][3],
					 val*mat._[2][0], val*mat._[2][1], val*mat._[2][2], val*mat._[2][3],
					 val*mat._[3][0], val*mat._[3][1], val*mat._[3][2], val*mat._[3][3] );
  }
  
  
  
  
  inline matriX matriX::operator/( valuE val ) const {
      if( abs( val ) > EPSILON ) {
    	  valuE inv_val = 1.0/val;

   	      return matriX( _[0][0]*inv_val, _[0][1]*inv_val, _[0][2]*inv_val, _[0][3]*inv_val,
		                 _[1][0]*inv_val, _[1][1]*inv_val, _[1][2]*inv_val, _[1][3]*inv_val,
					     _[2][0]*inv_val, _[2][1]*inv_val, _[2][2]*inv_val, _[2][3]*inv_val,
					     _[3][0]*inv_val, _[3][1]*inv_val, _[3][2]*inv_val, _[3][3]*inv_val );
      } else return matriX();
  }
  
  
  
  
  inline matriX& matriX::operator*=( valuE val ) {
   	  _[0][0]*=val;  _[0][1]*=val;  _[0][2]*=val;  _[0][3]*=val;
	  _[1][0]*=val;  _[1][1]*=val;  _[1][2]*=val;  _[1][3]*=val;
	  _[2][0]*=val;  _[2][1]*=val;  _[2][2]*=val;  _[2][3]*=val;
	  _[3][0]*=val;  _[3][1]*=val;  _[3][2]*=val;  _[3][3]*=val;
  
      return *this;
  }
  
  
  
  
  inline matriX& matriX::operator/=( valuE val ) {
      if( abs( val ) > EPSILON ) {
    	  valuE inv_val = 1.0/val;
  
   	      _[0][0]*=inv_val;  _[0][1]*=inv_val;  _[0][2]*=inv_val;  _[0][3]*=inv_val;
	      _[1][0]*=inv_val;  _[1][1]*=inv_val;  _[1][2]*=inv_val;  _[1][3]*=inv_val;
	      _[2][0]*=inv_val;  _[2][1]*=inv_val;  _[2][2]*=inv_val;  _[2][3]*=inv_val;
	      _[3][0]*=inv_val;  _[3][1]*=inv_val;  _[3][2]*=inv_val;  _[3][3]*=inv_val;
      }
  
      return *this;
  }
  
  
  
  
  inline matriX matriX::operator+( const matriX& mat ) const {
	  return matriX( _[0][0]+mat._[0][0], _[0][1]+mat._[0][1], _[0][2]+mat._[0][2], _[0][3]+mat._[0][3],
		             _[1][0]+mat._[1][0], _[1][1]+mat._[1][1], _[1][2]+mat._[1][2], _[1][3]+mat._[1][3],
					 _[2][0]+mat._[2][0], _[2][1]+mat._[2][1], _[2][2]+mat._[2][2], _[2][3]+mat._[2][3],
					 _[3][0]+mat._[3][0], _[3][1]+mat._[3][1], _[3][2]+mat._[3][2], _[3][3]+mat._[3][3] );
  }
  
  
  
  
  inline matriX matriX::operator-( const matriX& mat ) const {
	  return matriX( _[0][0]-mat._[0][0], _[0][1]-mat._[0][1], _[0][2]-mat._[0][2], _[0][3]-mat._[0][3],
		             _[1][0]-mat._[1][0], _[1][1]-mat._[1][1], _[1][2]-mat._[1][2], _[1][3]-mat._[1][3],
					 _[2][0]-mat._[2][0], _[2][1]-mat._[2][1], _[2][2]-mat._[2][2], _[2][3]-mat._[2][3],
					 _[3][0]-mat._[3][0], _[3][1]-mat._[3][1], _[3][2]-mat._[3][2], _[3][3]-mat._[3][3] );
  }
  
  
  
  
  inline matriX matriX::operator*( const matriX& mat ) const {
      return matriX( _[0][0]*mat._[0][0] + _[0][1]*mat._[1][0] + _[0][2]*mat._[2][0] + _[0][3]*mat._[3][0], 
	                 _[0][0]*mat._[0][1] + _[0][1]*mat._[1][1] + _[0][2]*mat._[2][1] + _[0][3]*mat._[3][1],
	                 _[0][0]*mat._[0][2] + _[0][1]*mat._[1][2] + _[0][2]*mat._[2][2] + _[0][3]*mat._[3][2],
	                 _[0][0]*mat._[0][3] + _[0][1]*mat._[1][3] + _[0][2]*mat._[2][3] + _[0][3]*mat._[3][3],
	                 _[1][0]*mat._[0][0] + _[1][1]*mat._[1][0] + _[1][2]*mat._[2][0] + _[1][3]*mat._[3][0],
	                 _[1][0]*mat._[0][1] + _[1][1]*mat._[1][1] + _[1][2]*mat._[2][1] + _[1][3]*mat._[3][1],
	                 _[1][0]*mat._[0][2] + _[1][1]*mat._[1][2] + _[1][2]*mat._[2][2] + _[1][3]*mat._[3][2],
	                 _[1][0]*mat._[0][3] + _[1][1]*mat._[1][3] + _[1][2]*mat._[2][3] + _[1][3]*mat._[3][3],
 	                 _[2][0]*mat._[0][0] + _[2][1]*mat._[1][0] + _[2][2]*mat._[2][0] + _[2][3]*mat._[3][0],
	                 _[2][0]*mat._[0][1] + _[2][1]*mat._[1][1] + _[2][2]*mat._[2][1] + _[2][3]*mat._[3][1],
	                 _[2][0]*mat._[0][2] + _[2][1]*mat._[1][2] + _[2][2]*mat._[2][2] + _[2][3]*mat._[3][2],
	                 _[2][0]*mat._[0][3] + _[2][1]*mat._[1][3] + _[2][2]*mat._[2][3] + _[2][3]*mat._[3][3],
	                 _[3][0]*mat._[0][0] + _[3][1]*mat._[1][0] + _[3][2]*mat._[2][0] + _[3][3]*mat._[3][0],
	                 _[3][0]*mat._[0][1] + _[3][1]*mat._[1][1] + _[3][2]*mat._[2][1] + _[3][3]*mat._[3][1],
	                 _[3][0]*mat._[0][2] + _[3][1]*mat._[1][2] + _[3][2]*mat._[2][2] + _[3][3]*mat._[3][2],
	                 _[3][0]*mat._[0][3] + _[3][1]*mat._[1][3] + _[3][2]*mat._[2][3] + _[3][3]*mat._[3][3] );
  }
  
  
  
  
  inline matriX& matriX::operator+=( const matriX& mat ) {
   	  _[0][0]+=mat._[0][0];  _[0][1]+=mat._[0][1];  _[0][2]+=mat._[0][2];  _[0][3]+=mat._[0][3];
	  _[1][0]+=mat._[1][0];  _[1][1]+=mat._[1][1];  _[1][2]+=mat._[1][2];  _[1][3]+=mat._[1][3];
	  _[2][0]+=mat._[2][0];  _[2][1]+=mat._[2][1];  _[2][2]+=mat._[2][2];  _[2][3]+=mat._[2][3];
	  _[3][0]+=mat._[3][0];  _[3][1]+=mat._[3][1];  _[3][2]+=mat._[3][2];  _[3][3]+=mat._[3][3];
	  
	  return *this;
  }
  
  
  
  
  inline matriX& matriX::operator-=( const matriX& mat ) {
   	  _[0][0]-=mat._[0][0];  _[0][1]-=mat._[0][1];  _[0][2]-=mat._[0][2];  _[0][3]-=mat._[0][3];
	  _[1][0]-=mat._[1][0];  _[1][1]-=mat._[1][1];  _[1][2]-=mat._[1][2];  _[1][3]-=mat._[1][3];
	  _[2][0]-=mat._[2][0];  _[2][1]-=mat._[2][1];  _[2][2]-=mat._[2][2];  _[2][3]-=mat._[2][3];
	  _[3][0]-=mat._[3][0];  _[3][1]-=mat._[3][1];  _[3][2]-=mat._[3][2];  _[3][3]-=mat._[3][3];
	  
	  return *this;
  }
  
  
  
  
  inline matriX& matriX::operator*=( const matriX& mat ) {
      matriX mat2 = *this;

	  _[0][0] = mat2._[0][0]*mat._[0][0] + mat2._[0][1]*mat._[1][0] + mat2._[0][2]*mat._[2][0] + mat2._[0][3]*mat._[3][0];
	  _[0][1] = mat2._[0][0]*mat._[0][1] + mat2._[0][1]*mat._[1][1] + mat2._[0][2]*mat._[2][1] + mat2._[0][3]*mat._[3][1];
	  _[0][2] = mat2._[0][0]*mat._[0][2] + mat2._[0][1]*mat._[1][2] + mat2._[0][2]*mat._[2][2] + mat2._[0][3]*mat._[3][2];
	  _[0][3] = mat2._[0][0]*mat._[0][3] + mat2._[0][1]*mat._[1][3] + mat2._[0][2]*mat._[2][3] + mat2._[0][3]*mat._[3][3];
	  _[1][0] = mat2._[1][0]*mat._[0][0] + mat2._[1][1]*mat._[1][0] + mat2._[1][2]*mat._[2][0] + mat2._[1][3]*mat._[3][0];
	  _[1][1] = mat2._[1][0]*mat._[0][1] + mat2._[1][1]*mat._[1][1] + mat2._[1][2]*mat._[2][1] + mat2._[1][3]*mat._[3][1];
	  _[1][2] = mat2._[1][0]*mat._[0][2] + mat2._[1][1]*mat._[1][2] + mat2._[1][2]*mat._[2][2] + mat2._[1][3]*mat._[3][2];
	  _[1][3] = mat2._[1][0]*mat._[0][3] + mat2._[1][1]*mat._[1][3] + mat2._[1][2]*mat._[2][3] + mat2._[1][3]*mat._[3][3];
	  _[2][0] = mat2._[2][0]*mat._[0][0] + mat2._[2][1]*mat._[1][0] + mat2._[2][2]*mat._[2][0] + mat2._[2][3]*mat._[3][0];
	  _[2][1] = mat2._[2][0]*mat._[0][1] + mat2._[2][1]*mat._[1][1] + mat2._[2][2]*mat._[2][1] + mat2._[2][3]*mat._[3][1];
	  _[2][2] = mat2._[2][0]*mat._[0][2] + mat2._[2][1]*mat._[1][2] + mat2._[2][2]*mat._[2][2] + mat2._[2][3]*mat._[3][2];
	  _[2][3] = mat2._[2][0]*mat._[0][3] + mat2._[2][1]*mat._[1][3] + mat2._[2][2]*mat._[2][3] + mat2._[2][3]*mat._[3][3];
	  _[3][0] = mat2._[3][0]*mat._[0][0] + mat2._[3][1]*mat._[1][0] + mat2._[3][2]*mat._[2][0] + mat2._[3][3]*mat._[3][0];
	  _[3][1] = mat2._[3][0]*mat._[0][1] + mat2._[3][1]*mat._[1][1] + mat2._[3][2]*mat._[2][1] + mat2._[3][3]*mat._[3][1];
	  _[3][2] = mat2._[3][0]*mat._[0][2] + mat2._[3][1]*mat._[1][2] + mat2._[3][2]*mat._[2][2] + mat2._[3][3]*mat._[3][2];
	  _[3][3] = mat2._[3][0]*mat._[0][3] + mat2._[3][1]*mat._[1][3] + mat2._[3][2]*mat._[2][3] + mat2._[3][3]*mat._[3][3];
	                 
      return *this;	                 
  }
  
  
  
  
  inline BOOL matriX::operator==( const matriX& mat ) const {
	  return _[0][0] == mat._[0][0] && _[0][1] == mat._[0][1] && _[0][2] == mat._[0][2] && _[0][3] == mat._[0][3] &&
	    	 _[1][0] == mat._[1][0] && _[1][1] == mat._[1][1] && _[1][2] == mat._[1][2] && _[1][3] == mat._[1][3] &&
	   	     _[2][0] == mat._[2][0] && _[2][1] == mat._[2][1] && _[2][2] == mat._[2][2] && _[2][3] == mat._[2][3] &&
	   	     _[3][0] == mat._[3][0] && _[3][1] == mat._[3][1] && _[3][2] == mat._[3][2] && _[3][3] == mat._[3][3]; 
  }
  
  
  
  
  inline BOOL matriX::operator!=( const matriX& mat ) const {
	  return _[0][0] != mat._[0][0] || _[0][1] != mat._[0][1] || _[0][2] != mat._[0][2] || _[0][3] != mat._[0][3] ||
	    	 _[1][0] != mat._[1][0] || _[1][1] != mat._[1][1] || _[1][2] != mat._[1][2] || _[1][3] != mat._[1][3] ||
	   	     _[2][0] != mat._[2][0] || _[2][1] != mat._[2][1] || _[2][2] != mat._[2][2] || _[2][3] != mat._[2][3] ||
	   	     _[3][0] != mat._[3][0] || _[3][1] != mat._[3][1] || _[3][2] != mat._[3][2] || _[3][3] != mat._[3][3]; 
  }




  inline matriX zerO( void ) {
   	  return matriX( 0.0, 0.0, 0.0, 0.0,
		             0.0, 0.0, 0.0, 0.0,
					 0.0, 0.0, 0.0, 0.0,
					 0.0, 0.0, 0.0, 0.0 );
  }
  
  
  
  
  inline matriX identitY( void ) {
   	  return matriX( 1.0, 0.0, 0.0, 0.0,
		             0.0, 1.0, 0.0, 0.0,
					 0.0, 0.0, 1.0, 0.0,
					 0.0, 0.0, 0.0, 1.0 );
  }
  
  
  
  
  inline homogcoorD multiplY( const homogcoorD& hc, const matriX& mat ) {
  	  return homogcoorD( hc.x*mat._[0][0]+hc.y*mat._[1][0]+hc.z*mat._[2][0]+hc.w*mat._[3][0],
  	                     hc.x*mat._[0][1]+hc.y*mat._[1][1]+hc.z*mat._[2][1]+hc.w*mat._[3][1],
 			             hc.x*mat._[0][2]+hc.y*mat._[1][2]+hc.z*mat._[2][2]+hc.w*mat._[3][2], 
                         hc.x*mat._[0][3]+hc.y*mat._[1][3]+hc.z*mat._[2][3]+hc.w*mat._[3][3] );
  }




  inline vectoR multiplY( const vectoR& v, const matriX& mat ) {
   	  valuE a = v.x*mat._[0][3]+v.y*mat._[1][3]+v.z*mat._[2][3];

      if( abs( a ) >= EPSILON ) { // point	   
          a = 1.0/a;
          
    	  return vectoR( ( v.x*mat._[0][0]+v.y*mat._[1][0]+v.z*mat._[2][0] )*a,
  	                     ( v.x*mat._[0][1]+v.y*mat._[1][1]+v.z*mat._[2][1] )*a,
  			             ( v.x*mat._[0][2]+v.y*mat._[1][2]+v.z*mat._[2][2] )*a );
      } else { // vector
    	  return vectoR( v.x*mat._[0][0]+v.y*mat._[1][0]+v.z*mat._[2][0],
  	                     v.x*mat._[0][1]+v.y*mat._[1][1]+v.z*mat._[2][1],
 			             v.x*mat._[0][2]+v.y*mat._[1][2]+v.z*mat._[2][2] );
      }
  }




  inline vectoR multiplytransposE( const vectoR& v, const matriX& mat ) {
   	  valuE a = v.x*mat._[3][0]+v.y*mat._[3][1]+v.z*mat._[3][2];

      if( abs( a ) >= EPSILON ) { // point	   
          a = 1.0/a;
          
    	  return vectoR( ( v.x*mat._[0][0]+v.y*mat._[0][1]+v.z*mat._[0][2] )*a,
  	                     ( v.x*mat._[1][0]+v.y*mat._[1][1]+v.z*mat._[1][2] )*a,
  			             ( v.x*mat._[2][0]+v.y*mat._[2][1]+v.z*mat._[2][2] )*a );
      } else { // vector
    	  return vectoR( v.x*mat._[0][0]+v.y*mat._[0][1]+v.z*mat._[0][2],
  	                     v.x*mat._[1][0]+v.y*mat._[1][1]+v.z*mat._[1][2],
 			             v.x*mat._[2][0]+v.y*mat._[2][1]+v.z*mat._[2][2] );
      }
  }




  inline poinT multiplY( const poinT& pt, const matriX& mat ) {
   	  valuE a = pt.x*mat._[0][3]+pt.y*mat._[1][3]+pt.z*mat._[2][3]+mat._[3][3];

      if( abs( a ) >= EPSILON ) { // point
          a = 1.0/a;
          
    	  return poinT( ( pt.x*mat._[0][0]+pt.y*mat._[1][0]+pt.z*mat._[2][0]+mat._[3][0] )*a,
                        ( pt.x*mat._[0][1]+pt.y*mat._[1][1]+pt.z*mat._[2][1]+mat._[3][1] )*a,
 			            ( pt.x*mat._[0][2]+pt.y*mat._[1][2]+pt.z*mat._[2][2]+mat._[3][2] )*a );
      } else { // vector
    	  return poinT( pt.x*mat._[0][0]+pt.y*mat._[1][0]+pt.z*mat._[2][0]+mat._[3][0],
  	  	                pt.x*mat._[0][1]+pt.y*mat._[1][1]+pt.z*mat._[2][1]+mat._[3][1],
	  			        pt.x*mat._[0][2]+pt.y*mat._[1][2]+pt.z*mat._[2][2]+mat._[3][2] );
      }
  }




  inline poinT multiplytransposE( const poinT& pt, const matriX& mat ) {
   	  valuE a = pt.x*mat._[3][0]+pt.y*mat._[3][1]+pt.z*mat._[3][2]+mat._[3][3];

      if( abs( a ) >= EPSILON ) { // point
          a = 1.0/a;
          
    	  return poinT( ( pt.x*mat._[0][0]+pt.y*mat._[0][1]+pt.z*mat._[0][2]+mat._[0][3] )*a,
                        ( pt.x*mat._[1][0]+pt.y*mat._[1][1]+pt.z*mat._[1][2]+mat._[1][3] )*a,
 			            ( pt.x*mat._[2][0]+pt.y*mat._[2][1]+pt.z*mat._[2][2]+mat._[2][3] )*a );
      } else { // vector
    	  return poinT( pt.x*mat._[0][0]+pt.y*mat._[0][1]+pt.z*mat._[0][2]+mat._[0][3],
  	  	                pt.x*mat._[1][0]+pt.y*mat._[1][1]+pt.z*mat._[1][2]+mat._[1][3],
	  			        pt.x*mat._[2][0]+pt.y*mat._[2][1]+pt.z*mat._[2][2]+mat._[2][3] );
      }
  }

  
  
  
  inline matriX multiplY( const matriX& mat1, const matriX& mat2 ) {
      return matriX( mat1._[0][0]*mat2._[0][0] + mat1._[0][1]*mat2._[1][0] + mat1._[0][2]*mat2._[2][0] + mat1._[0][3]*mat2._[3][0],
                	 mat1._[0][0]*mat2._[0][1] + mat1._[0][1]*mat2._[1][1] + mat1._[0][2]*mat2._[2][1] + mat1._[0][3]*mat2._[3][1],
        	         mat1._[0][0]*mat2._[0][2] + mat1._[0][1]*mat2._[1][2] + mat1._[0][2]*mat2._[2][2] + mat1._[0][3]*mat2._[3][2],
	                 mat1._[0][0]*mat2._[0][3] + mat1._[0][1]*mat2._[1][3] + mat1._[0][2]*mat2._[2][3] + mat1._[0][3]*mat2._[3][3],
	                 mat1._[1][0]*mat2._[0][0] + mat1._[1][1]*mat2._[1][0] + mat1._[1][2]*mat2._[2][0] + mat1._[1][3]*mat2._[3][0],
	                 mat1._[1][0]*mat2._[0][1] + mat1._[1][1]*mat2._[1][1] + mat1._[1][2]*mat2._[2][1] + mat1._[1][3]*mat2._[3][1],
	                 mat1._[1][0]*mat2._[0][2] + mat1._[1][1]*mat2._[1][2] + mat1._[1][2]*mat2._[2][2] + mat1._[1][3]*mat2._[3][2],
	                 mat1._[1][0]*mat2._[0][3] + mat1._[1][1]*mat2._[1][3] + mat1._[1][2]*mat2._[2][3] + mat1._[1][3]*mat2._[3][3],
	                 mat1._[2][0]*mat2._[0][0] + mat1._[2][1]*mat2._[1][0] + mat1._[2][2]*mat2._[2][0] + mat1._[2][3]*mat2._[3][0],
	                 mat1._[2][0]*mat2._[0][1] + mat1._[2][1]*mat2._[1][1] + mat1._[2][2]*mat2._[2][1] + mat1._[2][3]*mat2._[3][1],
	                 mat1._[2][0]*mat2._[0][2] + mat1._[2][1]*mat2._[1][2] + mat1._[2][2]*mat2._[2][2] + mat1._[2][3]*mat2._[3][2],
	                 mat1._[2][0]*mat2._[0][3] + mat1._[2][1]*mat2._[1][3] + mat1._[2][2]*mat2._[2][3] + mat1._[2][3]*mat2._[3][3],
	                 mat1._[3][0]*mat2._[0][0] + mat1._[3][1]*mat2._[1][0] + mat1._[3][2]*mat2._[2][0] + mat1._[3][3]*mat2._[3][0],
	                 mat1._[3][0]*mat2._[0][1] + mat1._[3][1]*mat2._[1][1] + mat1._[3][2]*mat2._[2][1] + mat1._[3][3]*mat2._[3][1],
	                 mat1._[3][0]*mat2._[0][2] + mat1._[3][1]*mat2._[1][2] + mat1._[3][2]*mat2._[2][2] + mat1._[3][3]*mat2._[3][2],
	                 mat1._[3][0]*mat2._[0][3] + mat1._[3][1]*mat2._[1][3] + mat1._[3][2]*mat2._[2][3] + mat1._[3][3]*mat2._[3][3] );
  }




  inline matriX multiplytransposE( const matriX& mat1, const matriX& mat2 ) {
      return matriX( mat1._[0][0]*mat2._[0][0] + mat1._[0][1]*mat2._[1][0] + mat1._[0][2]*mat2._[2][0] + mat1._[0][3]*mat2._[3][0],
	                 mat1._[1][0]*mat2._[0][0] + mat1._[1][1]*mat2._[1][0] + mat1._[1][2]*mat2._[2][0] + mat1._[1][3]*mat2._[3][0],
	                 mat1._[2][0]*mat2._[0][0] + mat1._[2][1]*mat2._[1][0] + mat1._[2][2]*mat2._[2][0] + mat1._[2][3]*mat2._[3][0],
	                 mat1._[3][0]*mat2._[0][0] + mat1._[3][1]*mat2._[1][0] + mat1._[3][2]*mat2._[2][0] + mat1._[3][3]*mat2._[3][0],
                     mat1._[0][0]*mat2._[0][1] + mat1._[0][1]*mat2._[1][1] + mat1._[0][2]*mat2._[2][1] + mat1._[0][3]*mat2._[3][1],
	                 mat1._[1][0]*mat2._[0][1] + mat1._[1][1]*mat2._[1][1] + mat1._[1][2]*mat2._[2][1] + mat1._[1][3]*mat2._[3][1],
	                 mat1._[2][0]*mat2._[0][1] + mat1._[2][1]*mat2._[1][1] + mat1._[2][2]*mat2._[2][1] + mat1._[2][3]*mat2._[3][1],
	                 mat1._[3][0]*mat2._[0][1] + mat1._[3][1]*mat2._[1][1] + mat1._[3][2]*mat2._[2][1] + mat1._[3][3]*mat2._[3][1],
        	         mat1._[0][0]*mat2._[0][2] + mat1._[0][1]*mat2._[1][2] + mat1._[0][2]*mat2._[2][2] + mat1._[0][3]*mat2._[3][2],
	                 mat1._[1][0]*mat2._[0][2] + mat1._[1][1]*mat2._[1][2] + mat1._[1][2]*mat2._[2][2] + mat1._[1][3]*mat2._[3][2],
	                 mat1._[2][0]*mat2._[0][2] + mat1._[2][1]*mat2._[1][2] + mat1._[2][2]*mat2._[2][2] + mat1._[2][3]*mat2._[3][2],
	                 mat1._[3][0]*mat2._[0][2] + mat1._[3][1]*mat2._[1][2] + mat1._[3][2]*mat2._[2][2] + mat1._[3][3]*mat2._[3][2],
	                 mat1._[0][0]*mat2._[0][3] + mat1._[0][1]*mat2._[1][3] + mat1._[0][2]*mat2._[2][3] + mat1._[0][3]*mat2._[3][3],
	                 mat1._[1][0]*mat2._[0][3] + mat1._[1][1]*mat2._[1][3] + mat1._[1][2]*mat2._[2][3] + mat1._[1][3]*mat2._[3][3],
	                 mat1._[2][0]*mat2._[0][3] + mat1._[2][1]*mat2._[1][3] + mat1._[2][2]*mat2._[2][3] + mat1._[2][3]*mat2._[3][3],
	                 mat1._[3][0]*mat2._[0][3] + mat1._[3][1]*mat2._[1][3] + mat1._[3][2]*mat2._[2][3] + mat1._[3][3]*mat2._[3][3] );
  }
  
  
  
  
  inline matriX transposE( const matriX& mat ) {
      return matriX( mat._[0][0], mat._[1][0], mat._[2][0], mat._[3][0],
                     mat._[0][1], mat._[1][1], mat._[2][1], mat._[3][1],
                     mat._[0][2], mat._[1][2], mat._[2][2], mat._[3][2],
                     mat._[0][3], mat._[1][3], mat._[2][3], mat._[3][3] );
  }
  
  
  
  
  inline valuE determinanT( const matriX& mat ) {
	  valuE tmp[12], a[4];

	  tmp[0] = mat._[2][2]*mat._[3][3];
	  tmp[1] = mat._[2][3]*mat._[3][2];
	  tmp[2] = mat._[2][1]*mat._[3][3];
	  tmp[3] = mat._[2][3]*mat._[3][1];
	  tmp[4] = mat._[2][1]*mat._[3][2];
	  tmp[5] = mat._[2][2]*mat._[3][1];
	  tmp[6] = mat._[2][0]*mat._[3][3];
	  tmp[7] = mat._[2][3]*mat._[3][0];
	  tmp[8] = mat._[2][0]*mat._[3][2];
	  tmp[9] = mat._[2][2]*mat._[3][0];
	  tmp[10] = mat._[2][0]*mat._[3][1];
	  tmp[11] = mat._[2][1]*mat._[3][0];

	  a[0] = mat._[1][1]*tmp[0] + mat._[1][2]*tmp[3] + mat._[1][3]*tmp[4]-
		     mat._[1][3]*tmp[5] - mat._[1][1]*tmp[1] - mat._[1][2]*tmp[2];

	  a[1] = mat._[1][3]*tmp[9] + mat._[1][0]*tmp[1] + mat._[1][2]*tmp[6]-
			 mat._[1][0]*tmp[0] - mat._[1][2]*tmp[7] - mat._[1][3]*tmp[8];

	  a[2] = mat._[1][0]*tmp[2] + mat._[1][1]*tmp[7] + mat._[1][3]*tmp[10]-
		     mat._[1][3]*tmp[11] - mat._[1][0]*tmp[3] - mat._[1][1]*tmp[6];

	  a[3] = mat._[1][2]*tmp[11] + mat._[1][0]*tmp[5] + mat._[1][1]*tmp[8]-
		     mat._[1][0]*tmp[4] - mat._[1][1]*tmp[9] - mat._[1][2]*tmp[10];

	  return mat._[0][0]*a[0]+mat._[0][1]*a[1]+mat._[0][2]*a[2]+mat._[0][3]*a[3];
  }
  
  
  
  
  inline matriX inversE( const matriX& mat ) {
	  matriX inv_mat;
	  valuE tmp[12], det;


	  tmp[0] = mat._[2][2]*mat._[3][3];
	  tmp[1] = mat._[3][2]*mat._[2][3];
	  tmp[2] = mat._[1][2]*mat._[3][3];
	  tmp[3] = mat._[3][2]*mat._[1][3];
	  tmp[4] = mat._[1][2]*mat._[2][3];
	  tmp[5] = mat._[2][2]*mat._[1][3];
	  tmp[6] = mat._[0][2]*mat._[3][3];
	  tmp[7] = mat._[3][2]*mat._[0][3];
	  tmp[8] = mat._[0][2]*mat._[2][3];
	  tmp[9] = mat._[2][2]*mat._[0][3];
	  tmp[10] = mat._[0][2]*mat._[1][3];
	  tmp[11] = mat._[1][2]*mat._[0][3];

	  inv_mat._[0][0] = tmp[0]*mat._[1][1] + tmp[3]*mat._[2][1] + tmp[4]*mat._[3][1]-
		                tmp[1]*mat._[1][1] - tmp[2]*mat._[2][1] - tmp[5]*mat._[3][1];
	  inv_mat._[0][1] = tmp[1]*mat._[0][1] + tmp[6]*mat._[2][1] + tmp[9]*mat._[3][1]-
		                tmp[0]*mat._[0][1] - tmp[7]*mat._[2][1] - tmp[8]*mat._[3][1];
	  inv_mat._[0][2] = tmp[2]*mat._[0][1] + tmp[7]*mat._[1][1] + tmp[10]*mat._[3][1]-
		                tmp[3]*mat._[0][1] - tmp[6]*mat._[1][1] - tmp[11]*mat._[3][1];
      inv_mat._[0][3] = tmp[5]*mat._[0][1] + tmp[8]*mat._[1][1] + tmp[11]*mat._[2][1]-
		                tmp[4]*mat._[0][1] - tmp[9]*mat._[1][1] - tmp[10]*mat._[2][1];
	  inv_mat._[1][0] = tmp[1]*mat._[1][0] + tmp[2]*mat._[2][0] + tmp[5]*mat._[3][0]-
		                tmp[0]*mat._[1][0] - tmp[3]*mat._[2][0] - tmp[4]*mat._[3][0];
	  inv_mat._[1][1] = tmp[0]*mat._[0][0] + tmp[7]*mat._[2][0] + tmp[8]*mat._[3][0]-
		                tmp[1]*mat._[0][0] - tmp[6]*mat._[2][0] - tmp[9]*mat._[3][0];
	  inv_mat._[1][2] = tmp[3]*mat._[0][0] + tmp[6]*mat._[1][0] + tmp[11]*mat._[3][0]-
		                tmp[2]*mat._[0][0] - tmp[7]*mat._[1][0] - tmp[10]*mat._[3][0];
      inv_mat._[1][3] = tmp[4]*mat._[0][0] + tmp[9]*mat._[1][0] + tmp[10]*mat._[2][0]-
		                tmp[5]*mat._[0][0] - tmp[8]*mat._[1][0] - tmp[11]*mat._[2][0];

	  tmp[0] = mat._[2][0]*mat._[3][1];
	  tmp[1] = mat._[3][0]*mat._[2][1];
	  tmp[2] = mat._[1][0]*mat._[3][1];
	  tmp[3] = mat._[3][0]*mat._[1][1];
	  tmp[4] = mat._[1][0]*mat._[2][1];
	  tmp[5] = mat._[2][0]*mat._[1][1];
	  tmp[6] = mat._[0][0]*mat._[3][1];
	  tmp[7] = mat._[3][0]*mat._[0][1];
	  tmp[8] = mat._[0][0]*mat._[2][1];
	  tmp[9] = mat._[2][0]*mat._[0][1];
	  tmp[10] = mat._[0][0]*mat._[1][1];
	  tmp[11] = mat._[1][0]*mat._[0][1];

	  inv_mat._[2][0] = tmp[0]*mat._[1][3] + tmp[3]*mat._[2][3] + tmp[4]*mat._[3][3]-
		                tmp[1]*mat._[1][3] - tmp[2]*mat._[2][3] - tmp[5]*mat._[3][3];
	  inv_mat._[2][1] = tmp[1]*mat._[0][3] + tmp[6]*mat._[2][3] + tmp[9]*mat._[3][3]-
		                tmp[0]*mat._[0][3] - tmp[7]*mat._[2][3] - tmp[8]*mat._[3][3];
	  inv_mat._[2][2] = tmp[2]*mat._[0][3] + tmp[7]*mat._[1][3] + tmp[10]*mat._[3][3]-
		                tmp[3]*mat._[0][3] - tmp[6]*mat._[1][3] - tmp[11]*mat._[3][3];
      inv_mat._[2][3] = tmp[5]*mat._[0][3] + tmp[8]*mat._[1][3] + tmp[11]*mat._[2][3]-
		                tmp[4]*mat._[0][3] - tmp[9]*mat._[1][3] - tmp[10]*mat._[2][3];
	  inv_mat._[3][0] = tmp[2]*mat._[2][2] + tmp[5]*mat._[3][2] + tmp[1]*mat._[1][2]-
		                tmp[4]*mat._[3][2] - tmp[0]*mat._[1][2] - tmp[3]*mat._[2][2];
	  inv_mat._[3][1] = tmp[8]*mat._[3][2] + tmp[0]*mat._[0][2] + tmp[7]*mat._[2][2]-
		                tmp[6]*mat._[2][2] - tmp[9]*mat._[3][2] - tmp[1]*mat._[0][2];
	  inv_mat._[3][2] = tmp[6]*mat._[1][2] + tmp[11]*mat._[3][2] + tmp[3]*mat._[0][2]-
		                tmp[10]*mat._[3][2] - tmp[2]*mat._[0][2] - tmp[7]*mat._[1][2];
      inv_mat._[3][3] = tmp[10]*mat._[2][2] + tmp[4]*mat._[0][2] + tmp[9]*mat._[1][2]-
		                tmp[8]*mat._[1][2] - tmp[11]*mat._[2][2] - tmp[5]*mat._[0][2];

	  det = mat._[0][0]*inv_mat._[0][0]+mat._[1][0]*inv_mat._[0][1]+mat._[2][0]*inv_mat._[0][2]+mat._[3][0]*inv_mat._[0][3];
	  det = 1.0/det;
      inv_mat*=det;


	  return inv_mat;
  }
  
  
  
  
  inline matriX translatE( const vectoR& t ) {
	  matriX mat;

      mat._[0][0] = 1.0;  mat._[0][1] = 0.0;  mat._[0][2] = 0.0;  mat._[0][3] = 0.0;
      mat._[1][0] = 0.0;  mat._[1][1] = 1.0;  mat._[1][2] = 0.0;  mat._[1][3] = 0.0;
      mat._[2][0] = 0.0;  mat._[2][1] = 0.0;  mat._[2][2] = 1.0;  mat._[2][3] = 0.0;
      mat._[3][0] = t.x;  mat._[3][1] = t.y;  mat._[3][2] = t.z;  mat._[3][3] = 1.0;

	  return mat;
  }
  
  
  
  
  inline matriX scalE( const vectoR& s ) {
	  matriX mat;

      mat._[0][0] = s.x;  mat._[0][1] = 0.0;  mat._[0][2] = 0.0;  mat._[0][3] = 0.0;
      mat._[1][0] = 0.0;  mat._[1][1] = s.y;  mat._[1][2] = 0.0;  mat._[1][3] = 0.0;
      mat._[2][0] = 0.0;  mat._[2][1] = 0.0;  mat._[2][2] = s.z;  mat._[2][3] = 0.0;
      mat._[3][0] = 0.0;  mat._[3][1] = 0.0;  mat._[3][2] = 0.0;  mat._[3][3] = 1.0;

	  return mat;
  }
  
  
  
  
  inline matriX rotateX( valuE a ) {
	  valuE b = sin( a ), c = cos( a );
	  matriX mat;

      mat._[0][0] = 1.0;  mat._[0][1] = 0.0;  mat._[0][2] = 0.0;  mat._[0][3] = 0.0;
      mat._[1][0] = 0.0;  mat._[1][1] = c;    mat._[1][2] = b;    mat._[1][3] = 0.0;
      mat._[2][0] = 0.0;  mat._[2][1] = -b;   mat._[2][2] = c;    mat._[2][3] = 0.0;
      mat._[3][0] = 0.0;  mat._[3][1] = 0.0;  mat._[3][2] = 0.0;  mat._[3][3] = 1.0;

	  return mat;
  }
  
  
  
  
  inline matriX rotateY( valuE a ) {
	  valuE b = sin( a ), c = cos( a );
	  matriX mat;

      mat._[0][0] = c;    mat._[0][1] = 0.0;  mat._[0][2] = -b;   mat._[0][3] = 0.0;
      mat._[1][0] = 0.0;  mat._[1][1] = 1.0;  mat._[1][2] = 0.0;  mat._[1][3] = 0.0;
      mat._[2][0] = b;    mat._[2][1] = 0.0;  mat._[2][2] = c;    mat._[2][3] = 0.0;
      mat._[3][0] = 0.0;  mat._[3][1] = 0.0;  mat._[3][2] = 0.0;  mat._[3][3] = 1.0;

	  return mat;
  }
  
  
  
  
  inline matriX rotateZ( valuE a ) {
	  valuE b = sin( a ), c = cos( a );
	  matriX mat;

      mat._[0][0] = c;    mat._[0][1] = b;    mat._[0][2] = 0.0;  mat._[0][3] = 0.0;
      mat._[1][0] = -b;   mat._[1][1] = c;    mat._[1][2] = 0.0;  mat._[1][3] = 0.0;
      mat._[2][0] = 0.0;  mat._[2][1] = 0.0;  mat._[2][2] = 1.0;  mat._[2][3] = 0.0;
      mat._[3][0] = 0.0;  mat._[3][1] = 0.0;  mat._[3][2] = 0.0;  mat._[3][3] = 1.0;

	  return mat;
  }
  
  
  
  
  inline matriX rotatE( valuE a, const vectoR& v ) {
	  valuE b = sin( a ), c = cos( a ), d = 1.0-c;
	  matriX mat;

	  mat._[0][0] = c+d*v.x*v.x;      mat._[0][1] = d*v.x*v.y+v.z*b;  mat._[0][2] = d*v.x*v.z-v.y*b;  mat._[0][3] = 0.0;  
	  mat._[1][0] = d*v.x*v.y-v.z*b;  mat._[1][1] = c+d*v.y*v.y;      mat._[1][2] = d*v.y*v.z+v.x*b;  mat._[1][3] = 0.0;  
	  mat._[2][0] = d*v.x*v.z+v.y*b;  mat._[2][1] = d*v.y*v.z-v.x*b;  mat._[2][2] = c+d*v.z*v.z;      mat._[2][3] = 0.0;  
	  mat._[3][0] = 0.0;              mat._[3][1] = 0.0;              mat._[3][2] = 0.0;              mat._[3][3] = 1.0;

	  return mat;
  }
  
  
  
  
  inline matriX rotatE( const vectoR& u, const vectoR& v ) {
	  vectoR w = crosS( u, v );
	  valuE a = doT( u, v ), b = 1.0-a, c = lengtH( w );
	  matriX mat;

	  w/=c;
	  mat._[0][0] = a+b*w.x*w.x;      mat._[0][1] = b*w.x*w.y+c*w.z;  mat._[0][2] = b*w.x*w.z-c*w.y;  mat._[0][3] = 0.0;  
	  mat._[1][0] = b*w.x*w.y-c*w.z;  mat._[1][1] = a+b*w.y*w.y;      mat._[1][2] = b*w.y*w.z+c*w.x;  mat._[1][3] = 0.0;  
	  mat._[2][0] = b*w.x*w.z+c*w.y;  mat._[2][1] = b*w.y*w.z-c*w.x;  mat._[2][2] = a+b*w.z*w.z;      mat._[2][3] = 0.0;  
	  mat._[3][0] = 0.0;              mat._[3][1] = 0.0;              mat._[3][2] = 0.0;              mat._[3][3] = 1.0;

	  return mat;
  }
  
  
  
  
  inline matriX shearxY( valuE sh ) {
	  matriX mat;

      mat._[0][0] = 1.0;  mat._[0][1] = 0.0;  mat._[0][2] = 0.0;  mat._[0][3] = 0.0;
      mat._[1][0] = sh;   mat._[1][1] = 1.0;  mat._[1][2] = 0.0;  mat._[1][3] = 0.0;
      mat._[2][0] = 0.0;  mat._[2][1] = 0.0;  mat._[2][2] = 1.0;  mat._[2][3] = 0.0;
      mat._[3][0] = 0.0;  mat._[3][1] = 0.0;  mat._[3][2] = 0.0;  mat._[3][3] = 1.0;

	  return mat;
  }
  
  
  
  
  inline matriX shearxZ( valuE sh ) {
	  matriX mat;

      mat._[0][0] = 1.0;  mat._[0][1] = 0.0;  mat._[0][2] = 0.0;  mat._[0][3] = 0.0;
      mat._[1][0] = 0.0;  mat._[1][1] = 1.0;  mat._[1][2] = 0.0;  mat._[1][3] = 0.0;
      mat._[2][0] = sh;   mat._[2][1] = 0.0;  mat._[2][2] = 1.0;  mat._[2][3] = 0.0;
      mat._[3][0] = 0.0;  mat._[3][1] = 0.0;  mat._[3][2] = 0.0;  mat._[3][3] = 1.0;

	  return mat;
  }
  
  
  
  
  inline matriX shearyX( valuE sh ) {
	  matriX mat;

      mat._[0][0] = 1.0;  mat._[0][1] = sh;   mat._[0][2] = 0.0;  mat._[0][3] = 0.0;
      mat._[1][0] = 0.0;  mat._[1][1] = 1.0;  mat._[1][2] = 0.0;  mat._[1][3] = 0.0;
      mat._[2][0] = 0.0;  mat._[2][1] = 0.0;  mat._[2][2] = 1.0;  mat._[2][3] = 0.0;
      mat._[3][0] = 0.0;  mat._[3][1] = 0.0;  mat._[3][2] = 0.0;  mat._[3][3] = 1.0;

	  return mat;
  }
  
  
  
  
  inline matriX shearyZ( valuE sh ) {
	  matriX mat;

      mat._[0][0] = 1.0;  mat._[0][1] = 0.0;  mat._[0][2] = 0.0;  mat._[0][3] = 0.0;
      mat._[1][0] = 0.0;  mat._[1][1] = 1.0;  mat._[1][2] = 0.0;  mat._[1][3] = 0.0;
      mat._[2][0] = 0.0;  mat._[2][1] = sh;   mat._[2][2] = 1.0;  mat._[2][3] = 0.0;
      mat._[3][0] = 0.0;  mat._[3][1] = 0.0;  mat._[3][2] = 0.0;  mat._[3][3] = 1.0;

	  return mat;
  }
  
  
  
  
  inline matriX shearzX( valuE sh ) {
	  matriX mat;

      mat._[0][0] = 1.0;  mat._[0][1] = 0.0;  mat._[0][2] = sh;   mat._[0][3] = 0.0;
      mat._[1][0] = 0.0;  mat._[1][1] = 1.0;  mat._[1][2] = 0.0;  mat._[1][3] = 0.0;
      mat._[2][0] = 0.0;  mat._[2][1] = 0.0;  mat._[2][2] = 1.0;  mat._[2][3] = 0.0;
      mat._[3][0] = 0.0;  mat._[3][1] = 0.0;  mat._[3][2] = 0.0;  mat._[3][3] = 1.0;

	  return mat;
  }
  
  
  
  
  inline matriX shearzY( valuE sh ) {
	  matriX mat;

      mat._[0][0] = 1.0;  mat._[0][1] = 0.0;  mat._[0][2] = 0.0;  mat._[0][3] = 0.0;
      mat._[1][0] = 0.0;  mat._[1][1] = 1.0;  mat._[1][2] = sh;   mat._[1][3] = 0.0;
      mat._[2][0] = 0.0;  mat._[2][1] = 0.0;  mat._[2][2] = 1.0;  mat._[2][3] = 0.0;
      mat._[3][0] = 0.0;  mat._[3][1] = 0.0;  mat._[3][2] = 0.0;  mat._[3][3] = 1.0;

	  return mat;
  }
  
  
  
  
  inline matriX euleR( valuE head, valuE pitch, valuE roll ) {
      return rotateY( head )*rotateX( pitch )*rotateZ( roll );
  }
  
  
  
  
  inline void euleR( const matriX& mat, valuE *head, valuE *pitch, valuE *roll ) {
      if( abs( abs( mat._[2][1] )-1.0 ) > EPSILON ) {
          *head = atan2( -mat._[2][0], mat._[2][2] );
          *pitch = asin( mat._[2][1] );
          *roll = atan2( -mat._[0][1], mat._[1][1] );
      } else {
          *head = 0.0;
          *pitch = asin( mat._[2][1] );
          *roll = atan2( mat._[1][0], mat._[0][0] );
      }
  }
  
  
  
  
  inline matriX mirroR( const planE& pl ) {
      matriX mat;

	  mat._[0][0] = 1.0-2.0*pl.n.x*pl.n.x;    mat._[0][1] = -2.0*pl.n.x*pl.n.y;     mat._[0][2] = -2.0*pl.n.x*pl.n.z;     mat._[0][3] = -2.0*pl.n.x*pl.d;
	  mat._[1][0] = mat._[0][1];              mat._[1][1] = 1.0-2.0*pl.n.y*pl.n.y;  mat._[1][2] = -2.0*pl.n.y*pl.n.z;     mat._[1][3] = -2.0*pl.n.y*pl.d;
	  mat._[2][0] = mat._[0][2];              mat._[2][1] = mat._[1][2];            mat._[2][2] = 1.0-2.0*pl.n.z*pl.n.z;  mat._[2][3] = -2.0*pl.n.z*pl.d;
	  mat._[3][0] = 0.0;                      mat._[3][1] = 0.0;                    mat._[3][2] = 0.0;                    mat._[3][3] = 1.0;

	  return mat;
  }
  
  
  
  
  inline matriX projecT( const planE& pl, const poinT& pt ) {
      valuE val = pl.n.x*pt.x+pl.n.y*pt.y+pl.n.z*pt.z;
      matriX mat;

	  mat._[0][0] = val+pl.d-pt.x*pl.n.x;  mat._[0][1] = -pt.y*pl.n.x;          mat._[0][2] = -pt.z*pl.n.x;          mat._[0][3] = -pl.n.x;
	  mat._[1][0] = -pt.x*pl.n.y;          mat._[1][1] = val+pl.d-pt.y*pl.n.y;  mat._[1][2] = -pt.z*pl.n.y;          mat._[1][3] = -pl.n.y;
	  mat._[2][0] = -pt.x*pl.n.z;          mat._[2][1] = -pt.y*pl.n.z;          mat._[2][2] = val+pl.d-pt.z*pl.n.z;  mat._[2][3] = -pl.n.z;
	  mat._[3][0] = -pt.x*pl.d;            mat._[3][1] = -pt.y*pl.d;            mat._[3][2] = -pt.z*pl.d;            mat._[3][3] = val;

	  return mat;
  }
  
  
  
  
  inline matriX orthographiC( valuE l, valuE r, valuE b, valuE t, valuE n, valuE f ) {
	  matriX mat;

      mat._[0][0] = 2.0/( r-l );      mat._[0][1] = 0.0;              mat._[0][2] = 0.0;          mat._[0][3] = 0.0;
      mat._[1][0] = 0.0;              mat._[1][1] = 2.0/( t-b );      mat._[1][2] = 0.0;          mat._[1][3] = 0.0;
      mat._[2][0] = 0.0;              mat._[2][1] = 0.0;              mat._[2][2] = 1.0/( f-n );  mat._[2][3] = 0.0;
      mat._[3][0] = ( r+l )/( l-r );  mat._[3][1] = ( t+b )/( b-t );  mat._[3][2] = n/( n-f );    mat._[3][3] = 1.0;

	  return mat;
  }
  
  
  
  
  inline matriX perspectivE( valuE l, valuE r, valuE b, valuE t, valuE n, valuE f ) {
	  matriX mat;

      mat._[0][0] = ( 2.0*n )/( r-l );  mat._[0][1] = 0.0;                mat._[0][2] = 0.0;              mat._[0][3] = 0.0;
      mat._[1][0] = 0.0;                mat._[1][1] = ( 2.0*n )/( t-b );  mat._[1][2] = 0.0;              mat._[1][3] = 0.0;
      mat._[2][0] = ( r+l )/( l-r );    mat._[2][1] = ( t+b )/( b-t );    mat._[2][2] = f/( f-n );        mat._[2][3] = 1.0;
      mat._[3][0] = 0.0;                mat._[3][1] = 0.0;                mat._[3][2] = ( f*n )/( n-f );  mat._[3][3] = 0.0;

	  return mat;
  }
  
  
  
  
  inline matriX vieW( const poinT& C, const vectoR& n, const vectoR& v, BOOL lh ) {
	  vectoR u, n_, v_;
	  matriX mat;

	  n_ = normalizE( n );
	  v_ = normalizE( v-n_*doT( v, n_ ) );
	  if( lh == TRUE ) u = normalizE( crosS( n_, v_ ) ); else u = -normalizE( crosS( n_, v_ ) );

      mat._[0][0] = u.x;		                         mat._[0][1] = v_.x;			                     mat._[0][2] = n_.x;		                         mat._[0][3] = 0.0;
      mat._[1][0] = u.y;		                         mat._[1][1] = v_.y;			                     mat._[1][2] = n_.y;		                         mat._[1][3] = 0.0;
      mat._[2][0] = u.z;                                 mat._[2][1] = v_.z;			                     mat._[2][2] = n_.z;			                     mat._[2][3] = 0.0;
      mat._[3][0] = -doT( vectoR( C.x, C.y, C.z ), u );  mat._[3][1] = -doT( vectoR( C.x, C.y, C.z ), v_ );  mat._[3][2] = -doT( vectoR( C.x, C.y, C.z ), n_ );  mat._[3][3] = 1.0;

	  return mat;
  }
  
  
  
  
  inline matriX matrixinterP( valuE x, const matriX& mat, const matriX& mat2 ) {
	  valuE qw, rw, sw, u, a, b, c, d, e, f, g, h, i, s;
	  vectoR qv, rv, sv;
	  matriX mat3;


	  u = mat._[0][0]+mat._[1][1]+mat._[2][2];

	  if( mat._[0][0] > mat._[1][1] ) {
		  if( mat._[0][0] > mat._[2][2] ) {
			  if( mat._[0][0] > u ) {
				  // MAX 00
				  qv.x = 0.5*sqrt( mat._[0][0]-mat._[1][1]-mat._[2][2]+mat._[3][3] );
				  qw = ( mat._[1][2]-mat._[2][1] )/( 4.0*qv.x );
				  a = 1.0/( 4.0*qw );
				  qv.y = ( mat._[2][0]-mat._[0][2] )*a;
				  qv.z = ( mat._[0][1]-mat._[1][0] )*a;
			  } else {
				  // MAX u
				  qw = 0.5*sqrt( mat._[0][0]+mat._[1][1]+mat._[2][2]+mat._[3][3] );
				  a = 1.0/( 4.0*qw );
				  qv.x = ( mat._[1][2]-mat._[2][1] )*a;
				  qv.y = ( mat._[2][0]-mat._[0][2] )*a;
				  qv.z = ( mat._[0][1]-mat._[1][0] )*a;
			  }
		  } else {
			  if( mat._[2][2] > u ) {
				  // MAX 22
				  qv.z = 0.5*sqrt( -mat._[0][0]-mat._[1][1]+mat._[2][2]+mat._[3][3] );
				  qw = ( mat._[0][1]-mat._[1][0] )/( 4.0*qv.z );
				  a = 1.0/( 4.0*qw );
				  qv.x = ( mat._[1][2]-mat._[2][1] )*a;
				  qv.y = ( mat._[2][0]-mat._[0][2] )*a;
			  } else {
				  // MAX u
				  qw = 0.5*sqrt( mat._[0][0]+mat._[1][1]+mat._[2][2]+mat._[3][3] );
				  a = 1.0/( 4.0*qw );
				  qv.x = ( mat._[1][2]-mat._[2][1] )*a;
				  qv.y = ( mat._[2][0]-mat._[0][2] )*a;
				  qv.z = ( mat._[0][1]-mat._[1][0] )*a;
			  }
		  }
	  } else {
		  if( mat._[1][1] > mat._[2][2] ) {
			  if( mat._[1][1] > u ) {
				  // MAX 11
				  qv.y = 0.5*sqrt( -mat._[0][0]+mat._[1][1]-mat._[2][2]+mat._[3][3] );
				  qw = ( mat._[2][0]-mat._[0][2] )/( 4.0*qv.y );
				  a = 1.0/( 4.0*qw );
				  qv.x = ( mat._[1][2]-mat._[2][1] )*a;
				  qv.z = ( mat._[0][1]-mat._[1][0] )*a;
			  } else {
				  // MAX u
				  qw = 0.5*sqrt( mat._[0][0]+mat._[1][1]+mat._[2][2]+mat._[3][3] );
				  a = 1.0/( 4.0*qw );
				  qv.x = ( mat._[1][2]-mat._[2][1] )*a;
				  qv.y = ( mat._[2][0]-mat._[0][2] )*a;
				  qv.z = ( mat._[0][1]-mat._[1][0] )*a;
			  }
		  } else {
			  if( mat._[2][2] > u ) {
				  // MAX 22
				  qv.z = 0.5*sqrt( -mat._[0][0]-mat._[1][1]+mat._[2][2]+mat._[3][3] );
				  qw = ( mat._[0][1]-mat._[1][0] )/( 4.0*qv.z );
				  a = 1.0/( 4.0*qw );
				  qv.x = ( mat._[1][2]-mat._[2][1] )*a;
				  qv.y = ( mat._[2][0]-mat._[0][2] )*a;
			  } else {
				  // MAX u
				  qw = 0.5*sqrt( mat._[0][0]+mat._[1][1]+mat._[2][2]+mat._[3][3] );
				  a = 1.0/( 4.0*qw );
				  qv.x = ( mat._[1][2]-mat._[2][1] )*a;
				  qv.y = ( mat._[2][0]-mat._[0][2] )*a;
				  qv.z = ( mat._[0][1]-mat._[1][0] )*a;
			  }
		  }
	  }
	  

	  u = mat2._[0][0]+mat2._[1][1]+mat2._[2][2];

	  if( mat2._[0][0] > mat2._[1][1] ) {
		  if( mat2._[0][0] > mat2._[2][2] ) {
			  if( mat2._[0][0] > u ) {
				  // MAX 00
				  rv.x = 0.5*sqrt( mat2._[0][0]-mat2._[1][1]-mat2._[2][2]+mat2._[3][3] );
				  rw = ( mat2._[1][2]-mat2._[2][1] )/( 4.0*rv.x );
				  a = 1.0/( 4.0*rw );
				  rv.y = ( mat2._[2][0]-mat2._[0][2] )*a;
				  rv.z = ( mat2._[0][1]-mat2._[1][0] )*a;
			  } else {
				  // MAX u
				  rw = 0.5*sqrt( mat2._[0][0]+mat2._[1][1]+mat2._[2][2]+mat2._[3][3] );
				  a = 1.0/( 4.0*rw );
				  rv.x = ( mat2._[1][2]-mat2._[2][1] )*a;
				  rv.y = ( mat2._[2][0]-mat2._[0][2] )*a;
				  rv.z = ( mat2._[0][1]-mat2._[1][0] )*a;
			  }
		  } else {
			  if( mat2._[2][2] > u ) {
				  // MAX 22
				  rv.z = 0.5*sqrt( -mat2._[0][0]-mat2._[1][1]+mat2._[2][2]+mat2._[3][3] );
				  rw = ( mat2._[0][1]-mat2._[1][0] )/( 4.0*rv.z );
				  a = 1.0/( 4.0*rw );
				  rv.x = ( mat2._[1][2]-mat2._[2][1] )*a;
				  rv.y = ( mat2._[2][0]-mat2._[0][2] )*a;
			  } else {
				  // MAX u
				  rw = 0.5*sqrt( mat2._[0][0]+mat2._[1][1]+mat2._[2][2]+mat2._[3][3] );
				  a = 1.0/( 4.0*rw );
				  rv.x = ( mat2._[1][2]-mat2._[2][1] )*a;
				  rv.y = ( mat2._[2][0]-mat2._[0][2] )*a;
				  rv.z = ( mat2._[0][1]-mat2._[1][0] )*a;
			  }
		  }
	  } else {
		  if( mat2._[1][1] > mat2._[2][2] ) {
			  if( mat2._[1][1] > u ) {
				  // MAX 11
				  rv.y = 0.5*sqrt( -mat2._[0][0]+mat2._[1][1]-mat2._[2][2]+mat2._[3][3] );
				  rw = ( mat2._[2][0]-mat2._[0][2] )/( 4.0*rv.y );
				  a = 1.0/( 4.0*rw );
				  rv.x = ( mat2._[1][2]-mat2._[2][1] )*a;
				  rv.z = ( mat2._[0][1]-mat2._[1][0] )*a;
			  } else {
				  // MAX u
				  rw = 0.5*sqrt( mat2._[0][0]+mat2._[1][1]+mat2._[2][2]+mat2._[3][3] );
				  a = 1.0/( 4.0*rw );
				  rv.x = ( mat2._[1][2]-mat2._[2][1] )*a;
				  rv.y = ( mat2._[2][0]-mat2._[0][2] )*a;
				  rv.z = ( mat2._[0][1]-mat2._[1][0] )*a;
			  }
		  } else {
			  if( mat2._[2][2] > u ) {
				  // MAX 22
				  rv.z = 0.5*sqrt( -mat2._[0][0]-mat2._[1][1]+mat2._[2][2]+mat2._[3][3] );
				  rw = ( mat2._[0][1]-mat2._[1][0] )/( 4.0*rv.z );
				  a = 1.0/( 4.0*rw );
				  rv.x = ( mat2._[1][2]-mat2._[2][1] )*a;
				  rv.y = ( mat2._[2][0]-mat2._[0][2] )*a;
			  } else {
				  // MAX u
				  rw = 0.5*sqrt( mat2._[0][0]+mat2._[1][1]+mat2._[2][2]+mat2._[3][3] );
				  a = 1.0/( 4.0*rw );
				  rv.x = ( mat2._[1][2]-mat2._[2][1] )*a;
				  rv.y = ( mat2._[2][0]-mat2._[0][2] )*a;
				  rv.z = ( mat2._[0][1]-mat2._[1][0] )*a;
			  }
		  }
	  }


	  u = doT( qv, rv )+qw*rw;
	  if( 1.0-abs( u ) > EPSILON ) {
		  a = acos( abs( u ) );
		  b = 1.0/sin( a );
		  c = sin( ( 1.0-x )*a )*b;
		  d = sin( x*a )*b;
	  } else {
		  c = 1.0-x;
		  d = x;
	  }
      if( u < 0.0 ) d = -d;

	  sv = qv*c+rv*d;
	  sw = qw*c+rw*d;


	  a = sv.x*sv.x;  b = sv.y*sv.y;  c = sv.z*sv.z;  
	  d = sv.x*sv.y;  e = sv.x*sv.z;  f = sv.y*sv.z;
	  g = sw*sv.x;  h = sw*sv.y;  i = sw*sv.z;
	  s = 2.0/( doT( sv, sv )+sw*sw );
	  mat3._[0][0] = 1.0-s*( b+c );                                 mat3._[0][1] = s*( d+i );                                     mat3._[0][2] = s*( e-h );									 mat3._[0][3] = 0.0;  
	  mat3._[1][0] = s*( d-i );                                     mat3._[1][1] = 1.0-s*( a+c );                                 mat3._[1][2] = s*( f+g );									 mat3._[1][3] = 0.0;  
	  mat3._[2][0] = s*( e+h );                                     mat3._[2][1] = s*( f-g );                                     mat3._[2][2] = 1.0-s*( a+b );								 mat3._[2][3] = 0.0;  
	  mat3._[3][0] = mat._[3][0]+( mat2._[3][0]-mat._[3][0] )*x;	mat3._[3][1] = mat._[3][1]+( mat2._[3][1]-mat._[3][1] )*x;  mat3._[3][2] = mat._[3][2]+( mat2._[3][2]-mat._[3][2] )*x;  mat3._[3][3] = 1.0;  


	  return mat3;
  }








  // MATRIXARRAY
  class matrixarraY: public arraY<matriX> {};
