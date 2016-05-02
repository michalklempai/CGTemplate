
  // CAMERA
  class camerA {
      public:
          poinT eye; 
          vectoR u, v, w; 
		  valuE viewangle, aspect, znear, zfar;
		  matriX mat;


          camerA( void ) { reseT(); };
		  camerA( const poinT& eye, const vectoR& u, const vectoR& v, const vectoR& w, valuE viewangle, valuE aspect, valuE znear, valuE zfar, matriX mat );
          ~camerA( void ) { deletealL(); };

          void reseT( void );
          void deletealL( void );
          void copY( camerA *C );

		  void yaW( valuE angle );
		  void pitcH( valuE angle );
		  void rolL( valuE angle );
		  void slidE( const vectoR& v );
  };


  void resetxforM( camerA *C );
  poinT projecT( camerA *C, const poinT& pt );






  camerA::camerA( const poinT& eye, const vectoR& u, const vectoR& v, const vectoR& w, valuE viewangle, valuE aspect, valuE znear, valuE zfar, matriX mat ) {
	  reseT();

      this->eye = eye;
	  this->u = u;
	  this->v = v;
	  this->w = w; 
	  this->viewangle = viewangle;
	  this->aspect = aspect;
	  this->znear = znear;
	  this->zfar = zfar;
	  this->mat = mat;
  }




  void camerA::reseT( void ) {
      eye = poinT();
      u = v = w = vectoR(); 
      viewangle = aspect = znear = zfar = 0.0;
	  mat = matriX();
  }




  void camerA::deletealL( void ) {
      reseT();
  }




  void camerA::copY( camerA *C ) {
      if( C ) {  
          C->deletealL();

    	  C->eye = eye;
    	  C->u = u;
    	  C->v = v;
    	  C->w = w;
    	  C->viewangle = viewangle;
    	  C->aspect = aspect;
    	  C->znear = znear;
    	  C->zfar = zfar;
	      C->mat = mat;
      }
  }




  void camerA::yaW( valuE angle ) {
      valuE a = sin( angle*DEG_RAD ), b = cos( angle*DEG_RAD );

	  u = u*b+w*a;
	  w = w*b-u*a;
  }




  void camerA::pitcH( valuE angle ) {
      valuE a = sin( angle*DEG_RAD ), b = cos( angle*DEG_RAD );

	  v = v*b+w*a;
	  w = w*b-v*a;
  }




  void camerA::rolL( valuE angle ) {
      valuE a = sin( angle*DEG_RAD ), b = cos( angle*DEG_RAD );

	  u = u*b+v*a;
	  v = v*b-u*a;
  }




  void camerA::slidE( const vectoR& v ) {
	  eye.x+=this->u.x*v.x+this->v.x*v.y+this->w.x*v.z;
	  eye.y+=this->u.y*v.x+this->v.y*v.y+this->w.y*v.z;
	  eye.z+=this->u.z*v.x+this->v.z*v.y+this->w.z*v.z;
  }




  void resetxforM( camerA *C ) {
      poinT pt, pt2;

      pt = multiplY( C->eye, C->mat );
      pt2 = multiplY( C->eye+C->u, C->mat );
      C->u = normalizE( pt2-pt );
      pt2 = multiplY( C->eye+C->v, C->mat );
      C->v = normalizE( pt2-pt );
      pt2 = multiplY( C->eye+C->w, C->mat );
      C->w = normalizE( pt2-pt );
      C->eye = pt;
      C->mat = identitY();
  }




  poinT projecT( camerA *C, const poinT& pt ) {
	  valuE val, w, h;

	  val = abs( C->znear/doT( C->w, pt-C->eye ) );

      w = 2.0*C->znear*tan( C->viewangle*C->aspect*0.5*DEG_RAD );
      h = 2.0*C->znear*tan( C->viewangle*0.5*DEG_RAD );

	  return poinT( planepoinT( planE( C->u, C->eye ), pt )*val/w, planepoinT( planE( C->v, C->eye ), pt )*val/h, 0.0 );
  }

  






  // CAMERAARRAY
  class cameraarraY: public arraY_<camerA> {};


  // LPCAMERA
  typedef camerA* lpcamerA;


  // LPCAMERAARRAY
  class lpcameraarraY: public arraY__<lpcamerA> {};
