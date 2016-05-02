
  // OOBBOX
  class oobboX {
      public:
          poinT C;
		  vectoR u, v, w;
          valuE hu, hv, hw;


		  oobboX( void );
		  oobboX( const poinT& C, const vectoR& u, const vectoR& v, const vectoR& w, valuE hu, valuE hv, valuE hw ); 
		  oobboX( const aabboX& aabb ); 
		  oobboX( const oobboX& oobb ); 

          BOOL operator==( const oobboX& oobb ) const;
          BOOL operator!=( const oobboX& oobb ) const;
  };


  inline oobboX multiplY( const oobboX& oobb, const matriX& mat );
  inline BOOL oobboxpoinT( const oobboX& oobb, const poinT& pt );
  inline BOOL oobboxraY( const oobboX& oobb, const raY& r, valuE *tmin_, valuE *tmax_ );
  inline BOOL oobboxraY( const oobboX& oobb, const raY& r );
  inline BOOL oobboxraY( const oobboX& oobb, const raY& r, valuE *t );
  inline long oobboxplanE( const oobboX& oobb, const planE& pl );
  inline BOOL oobboxaabboX( const oobboX& oobb, const aabboX& aabb );
  inline BOOL oobboxoobboX( const oobboX& oobb1, const oobboX& oobb2 );






  inline oobboX::oobboX( void ) {
      C = poinT();
      u = v = w = vectoR();
      hu = hv = hw = 0.0;
  }




  inline oobboX::oobboX( const poinT& C, const vectoR& u, const vectoR& v, const vectoR& w, valuE hu, valuE hv, valuE hw ) { 
      this->C = C;  this->u = u;  this->v = v;  this->w = w;  this->hu = hu;  this->hv = hv;  this->hw = hw;
  }




  inline oobboX::oobboX( const aabboX& aabb ) {
      C = ( aabb.min+aabb.max )*0.5;
      u = E0;  v = E1;  w = E2;
      hu = ( aabb.max.x-aabb.min.x )*0.5;
      hv = ( aabb.max.y-aabb.min.y )*0.5;
      hw = ( aabb.max.z-aabb.min.z )*0.5;
  }




  inline oobboX::oobboX( const oobboX& oobb ) {
	  this->C = oobb.C;
	  this->u = oobb.u;
	  this->v = oobb.v;
	  this->w = oobb.w;
	  this->hu = oobb.hu;
	  this->hv = oobb.hv;
	  this->hw = oobb.hw;
  }




  inline BOOL oobboX::operator==( const oobboX& oobb ) const {
	  if( C == oobb.C && u == oobb.u && v == oobb.v && w == oobb.w && hu == oobb.hu && hv == oobb.hv && hw == oobb.hw ) return TRUE; else return FALSE;
  }




  inline BOOL oobboX::operator!=( const oobboX& oobb ) const {
	  return !( ( *this ) == oobb );
  }




  inline oobboX multiplY( const oobboX& oobb, const matriX& mat ) {
      poinT S;
      vectoR u, v, w;
      valuE hu, hv, hw;
                                                    
      S = multiplY( oobb.C, mat );
      u = multiplY( oobb.C+oobb.hu*oobb.u, mat )-S;
      v = multiplY( oobb.C+oobb.hv*oobb.v, mat )-S;
      w = multiplY( oobb.C+oobb.hw*oobb.w, mat )-S;
      hu = lengtH( u );
      hv = lengtH( v );
      hw = lengtH( w );

      return oobboX( S, u/hu, v/hv, w/hw, hu, hv, hw );
  }




  inline BOOL obboxpoinT( const oobboX& oobb, const poinT& pt ) {
      vectoR v = pt-oobb.C;

      if( abs( doT( oobb.u, v ) ) > oobb.hu ) return FALSE; else
      if( abs( doT( oobb.v, v ) ) > oobb.hv ) return FALSE; else
      if( abs( doT( oobb.w, v ) ) > oobb.hw ) return FALSE; else return TRUE;
  }

  


  inline BOOL obboxraY( const oobboX& oobb, const raY& r, valuE *tmin_, valuE *tmax_ ) {
      valuE tmin, tmax, t1, t2, a, e, f;
      vectoR p;


	  tmin = -INFINITY; 
	  tmax = INFINITY;
      p = oobb.C-r.A;

      e = doT( oobb.u, p );
      f = doT( oobb.u, r.q );
      if( abs( f ) > EPSILON ) {
          a = 1.0/f;
          t1 = ( e+oobb.hu )*a;    
          t2 = ( e-oobb.hu )*a;    
		  if( t1 > t2 ) {
		      a = t1;
			  t1 = t2;
			  t2 = a;
		  }
		  if( t1 > tmin ) tmin = t1;
		  if( t2 < tmax ) tmax = t2;
		  if( tmin > tmax ) return FALSE;
		  if( tmax < 0.0 ) return FALSE;
      } else
      if( -oobb.hu > e || oobb.hu < e ) return FALSE;

      e = doT( oobb.v, p );
      f = doT( oobb.v, r.q );
      if( abs( f ) > EPSILON ) {
          a = 1.0/f;
          t1 = ( e+oobb.hv )*a;    
          t2 = ( e-oobb.hv )*a;    
		  if( t1 > t2 ) {
		      a = t1;
			  t1 = t2;
			  t2 = a;
		  }
		  if( t1 > tmin ) tmin = t1;
		  if( t2 < tmax ) tmax = t2;
		  if( tmin > tmax ) return FALSE;
		  if( tmax < 0.0 ) return FALSE;
      } else
      if( -oobb.hv > e || oobb.hv < e ) return FALSE;

      e = doT( oobb.w, p );
      f = doT( oobb.w, r.q );
      if( abs( f ) > EPSILON ) {
          a = 1.0/f;
          t1 = ( e+oobb.hw )*a;    
          t2 = ( e-oobb.hw )*a;    
		  if( t1 > t2 ) {
		      a = t1;
			  t1 = t2;
			  t2 = a;
		  }
		  if( t1 > tmin ) tmin = t1;
		  if( t2 < tmax ) tmax = t2;
		  if( tmin > tmax ) return FALSE;
		  if( tmax < 0.0 ) return FALSE;
      } else
      if( -oobb.hw > e || oobb.hw < e ) return FALSE;

      
      *tmin_ = tmin;
	  *tmax_ = tmax;

	  
	  return TRUE; 
  }




  inline BOOL obboxraY( const oobboX& oobb, const raY& r ) {
	  valuE a;

	  return obboxraY( oobb, r, &a, &a );
  }




  inline BOOL obboxraY( const oobboX& oobb, const raY& r, valuE *t ) {
	  valuE tmin, tmax;

	  if( obboxraY( oobb, r, &tmin, &tmax ) ) {
		  if( tmin >= 0.0 ) *t = tmin; else *t = tmax;
	  
		  return TRUE; 
	  } else return FALSE;
  }




  inline long obboxplanE( const oobboX& oobb, const planE& pl ) {
      valuE a, r;

      r = abs( oobb.hu*doT( pl.n, oobb.u ) )+abs( oobb.hv*doT( pl.n, oobb.v ) )+abs( oobb.hw*doT( pl.n, oobb.w ) );
      a = planepoinT( pl, oobb.C );
      if( a-r > EPSILON ) return 1; else 
  	  if( a+r < -EPSILON ) return -1; else return 0;
  }




  inline BOOL oobboxaabboX( const oobboX& oobb, const aabboX& aabb ) {
      return oobboxoobboX( oobb, oobboX( aabb ) );
  }




  inline BOOL oobboxoobboX( const oobboX& obb1, const oobboX& obb2 ) {
      vectoR t;
      valuE r, rA, rB;


      t = obb2.C-obb1.C;

      // oobb1
      r = abs( doT( t, obb1.u ) );
      rA = obb1.hu;
      rB = obb2.hu*abs( doT( obb2.u, obb1.u ) )+obb2.hv*abs( doT( obb2.v, obb1.u ) )+obb2.hw*abs( doT( obb2.w, obb1.u ) );
      if( rA+rB < r ) return FALSE;

      r = abs( doT( t, obb1.v ) );
      rA = obb1.hv;
      rB = obb2.hu*abs( doT( obb2.u, obb1.v ) )+obb2.hv*abs( doT( obb2.v, obb1.v ) )+obb2.hw*abs( doT( obb2.w, obb1.v ) );
      if( rA+rB < r ) return FALSE;

      r = abs( doT( t, obb1.w ) );
      rA = obb1.hw;
      rB = obb2.hu*abs( doT( obb2.u, obb1.w ) )+obb2.hv*abs( doT( obb2.v, obb1.w ) )+obb2.hw*abs( doT( obb2.w, obb1.w ) );
      if( rA+rB < r ) return FALSE;
      //

      // obb2
      r = abs( doT( t, obb2.u ) );
      rA = obb1.hu*abs( doT( obb1.u, obb2.u ) )+obb1.hv*abs( doT( obb1.v, obb2.u ) )+obb1.hw*abs( doT( obb1.w, obb2.u ) );
      rB = obb2.hu;
      if( rA+rB < r ) return FALSE;

      r = abs( doT( t, obb2.v ) );
      rA = obb1.hu*abs( doT( obb1.u, obb2.v ) )+obb1.hv*abs( doT( obb1.v, obb2.v ) )+obb1.hw*abs( doT( obb1.w, obb2.v ) );
      rB = obb2.hv;
      if( rA+rB < r ) return FALSE;

      r = abs( doT( t, obb2.w ) );
      rA = obb1.hu*abs( doT( obb1.u, obb2.w ) )+obb1.hv*abs( doT( obb1.v, obb2.w ) )+obb1.hw*abs( doT( obb1.w, obb2.w ) );
      rB = obb2.hw;
      if( rA+rB < r ) return FALSE;
      //

      // no whole test...


      return TRUE;
  }








  // OOBBOXARRAY
  class oobboxarraY: public arraY<oobboX> {};
