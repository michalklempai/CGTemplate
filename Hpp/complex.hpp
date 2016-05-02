
  // COMPLEX
  class compleX {
      public:
          valuE re, im; 


          compleX( void );
          compleX( valuE re, valuE im );
          compleX( const compleX& cx );

          compleX operator+( void ) const;
          compleX operator-( void ) const;

		  compleX operator+( valuE val ) const;
		  friend compleX operator+( valuE val, const compleX& cx );
		  compleX operator-( valuE val ) const;
		  friend compleX operator-( valuE val, const compleX& cx );
		  compleX operator*( valuE val ) const;
		  friend compleX operator*( valuE val, const compleX& cx );
		  compleX operator/( valuE val ) const;
		  friend compleX operator/( valuE val, const compleX& cx );
		  compleX& operator+=( valuE val );
          compleX& operator-=( valuE val );
		  compleX& operator*=( valuE val );
          compleX& operator/=( valuE val );

		  compleX operator+( const compleX& cx ) const;
          compleX operator-( const compleX& cx ) const;
          compleX operator*( const compleX& cx ) const;
          compleX operator/( const compleX& cx ) const;
		  compleX& operator+=( const compleX& cx );
          compleX& operator-=( const compleX& cx );
          compleX& operator*=( const compleX& cx );
          compleX& operator/=( const compleX& cx );
		  BOOL operator==( const compleX& cx ) const;
          BOOL operator!=( const compleX& cx ) const;
  };


  inline compleX identitY__( void );
  inline valuE norM( const compleX& cx );
  inline compleX conjugatE( const compleX& cx );
  inline valuE abS( const compleX& cx );
  inline valuE doT( const compleX& cx, const compleX& dx );
  inline compleX sqR( const compleX& cx );
  inline compleX sqrT( const compleX& cx );
  inline compleX siN( const compleX& cx );
  inline compleX coS( const compleX& cx );
  inline compleX multiplY( const compleX& cx, const compleX& dx );
  inline compleX inversE( const compleX& cx );
  inline compleX slerP( const compleX& cx, const compleX& dx, valuE t );






  inline compleX::compleX( void ) {
      re = im = 0.0;
  }




  inline compleX::compleX( valuE re, valuE im ) {
	  this->re = re;  this->im = im;
  }
  
  
  
  
  inline compleX::compleX( const compleX& cx ) {
      re = cx.re;  im = cx.im;
  }




  inline compleX compleX::operator+( void ) const {
      return *this;
  }
  
  
  
  
  inline compleX compleX::operator-( void ) const {
      return compleX( -re, -im );
  }




  inline compleX compleX::operator+( valuE val ) const {
      return compleX( re+val, im );
  }
  
  
  
  
  inline compleX operator+( valuE val, const compleX& cx ) {
      return compleX( val+cx.re, cx.im );
  }
  
  
  
  
  inline compleX compleX::operator-( valuE val ) const {
      return compleX( re-val, im );
  }
  
  
  
  
  inline compleX operator-( valuE val, const compleX& cx ) {
      return compleX( val-cx.re, cx.im );
  }
  
  
  
  
  inline compleX compleX::operator*( valuE val ) const {
      return compleX( re*val, im*val );
  }
  
  
  
  
  inline compleX operator*( valuE val, const compleX& cx ) {
      return compleX( val*cx.re, val*cx.im );
  }
  
  
  
  
  inline compleX compleX::operator/( valuE val ) const {
      if( abs( val ) > EPSILON ) {
    	  valuE inv_val = 1.0/val;

          return compleX( re*inv_val, im*inv_val );
      } else return compleX();
  }




  inline compleX operator/( valuE val, const compleX& cx ) {
	  valuE val2 = norM( cx );

	  if( abs( val2 ) > EPSILON ) {
		  val2 = 1.0/val2;

		  return compleX( val*cx.re*val2, -val*cx.im*val2 );
	  } else return compleX();
  }

  
  
  
  inline compleX& compleX::operator+=( valuE val ) {
      re+=val;

      return *this;
  }
  
  
  
  
  inline compleX& compleX::operator-=( valuE val ) {
      re-=val;

      return *this;
  }
  
  
  
  
  inline compleX& compleX::operator*=( valuE val ) {
      re*=val;  im*=val;

      return *this;
  }
  
  
  
  
  inline compleX& compleX::operator/=( valuE val ) {
      if( abs( val ) > EPSILON ) {
    	  valuE inv_val = 1.0/val;

          re*=inv_val;  im*=inv_val;
      }
      
      return *this;
  }
  
  
  

  inline compleX compleX::operator+( const compleX& cx ) const {
      return compleX( re+cx.re, im+cx.im );
  }
  
  
  
  
  inline compleX compleX::operator-( const compleX& cx ) const {
      return compleX( re-cx.re, im-cx.im );
  }
  
  
  
  
  inline compleX compleX::operator*( const compleX& cx ) const {
      return compleX( re*cx.re-im*cx.im, re*cx.im+im*cx.re );
  }
  
  
  
  
  inline compleX compleX::operator/( const compleX& cx ) const {
	  valuE val = norM( cx );

	  if( abs( val ) > EPSILON ) {
		  val = 1.0/val;

	      return compleX( ( re*cx.re+im*cx.im )*val, ( im*cx.re-re*cx.im )*val );
	  } else return compleX();
  }
  
  
  
  
  inline compleX& compleX::operator+=( const compleX& cx ) {
      re+=cx.re;  im+=cx.im;

      return *this;
  }
  
  
  
  
  inline compleX& compleX::operator-=( const compleX& cx ) {
      re-=cx.re;  im-=cx.im;

      return *this;
  }
  
  
  
  
  inline compleX& compleX::operator*=( const compleX& cx ) {
	  valuE re_ = re;

      re = re*cx.re-im*cx.im;
      im = re_*cx.im+im*cx.re;

      return *this;
  }




  inline compleX& compleX::operator/=( const compleX& cx ) {
	  valuE val = norM( cx ), re_;

	  if( abs( val ) > EPSILON ) {
		  val = 1.0/val;

		  re_ = re;
	      re = ( re_*cx.re+im*cx.im )*val;
		  im = ( im*cx.re-re_*cx.im )*val;
	  } else {
		  re = im = 0.0;
	  }

      return *this;
  }




  inline BOOL compleX::operator==( const compleX& cx ) const {
      return re == cx.re && im == cx.im;
  }
  
  
  
  
  inline BOOL compleX::operator!=( const compleX& cx ) const {
      return re != cx.re || im != cx.im;
  }




  inline compleX identitY__( void ) {
      return compleX( 1.0, 0.0 );
  }
  
  
  
  
  inline valuE norM( const compleX& cx ) {
      return cx.re*cx.re+cx.im*cx.im;
  }
  
  
  
  
  inline compleX conjugatE( const compleX& cx ) {
      return compleX( cx.re, -cx.im );
  }




  inline valuE abS( const compleX& cx ) {
	  return sqrT( sqR( cx.re )+sqR( cx.im ) );
  }




  inline valuE doT( const compleX& cx, const compleX& dx ) {
	  return cx.re*dx.re+cx.im*dx.im;
  }




  inline compleX sqR( const compleX& cx ) {
	  return cx*cx;
  }




  inline compleX sqrT( const compleX& cx ) {  // plus este riesenie, ktore ma -retvalue = -re, -im
	  valuE phi = atan( diV( cx.im, cx.re, 0.0 ) );

	  return compleX( cos( phi ), sin( phi ) )*sqrT( abS( cx ) );
  }




  inline compleX siN( const compleX& cx ) {
	  valuE e = exP( cx.im ), e_ = exP( -cx.im );

      return compleX( sin( cx.re )*( e+e_ )*0.5, cos( cx.re )*( e-e_ )*0.5 );
  }




  inline compleX coS( const compleX& cx ) {
	  valuE e = exP( cx.im ), e_ = exP( -cx.im );

      return compleX( cos( cx.re )*( e+e_ )*0.5, -sin( cx.re )*( e-e_ )*0.5 );
  }

  
  
  
  inline compleX multiplY( const compleX& cx, const compleX& dx ) {
      return compleX( cx.re*dx.re-cx.im*dx.im, cx.re*dx.im+cx.im*dx.re );
  }
  
  
  
  
  inline compleX inversE( const compleX& cx ) {
      return conjugatE( cx )/norM( cx );
  }
  
  
  
  
  inline compleX slerP( const compleX& cx, const compleX& dx, valuE t ) {
      valuE val = acos( cx.re*dx.re+cx.im*dx.im );
  
      return ( sin( val*( 1.0-t ) )*cx+sin( val*t )*dx )/sin( val );
  }






            

  // COMPLEXARRAY
  class complexarraY: public arraY<compleX> {};
