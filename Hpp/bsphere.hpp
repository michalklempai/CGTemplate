
  // BSPHERE
  class bspherE {
      public:
		  poinT C;
		  valuE r;


		  bspherE( void );
		  bspherE( valuE Cx, valuE Cy, valuE Cz, valuE r ); 
		  bspherE( const poinT& C, valuE r ); 
		  bspherE( const bspherE& bsph ); 

          BOOL operator==( const bspherE& bsph ) const;
          BOOL operator!=( const bspherE& bsph ) const;
  };


  inline BOOL bspherepoinT( const bspherE& bsph, const poinT& pt );
  inline long bsphereraY( const bspherE& bsph, const raY& r, valuE *tmin, valuE *tmax );
  inline BOOL bsphereraY( const bspherE& bsph, const raY& r );
  inline BOOL bsphereraY( const bspherE& bsph, const raY& r, valuE *t );
  inline long bsphereplanE( const bspherE& bsph, const planE& pl );
  inline BOOL bsphereaabboX( const bspherE& bsph, const aabboX& aabb );
  inline BOOL bsphereoobboX( const bspherE& bsph, const oobboX& oobb );
  inline BOOL bspherebspherE( const bspherE& bsph1, const bspherE& bsph2 );        






  inline bspherE::bspherE( void ) {
      C = poinT();
	  r = 0.0;
  }




  inline bspherE::bspherE( valuE Cx, valuE Cy, valuE Cz, valuE r ) {
	  C = poinT( Cx, Cy, Cz );  this->r = r;
  }




  inline bspherE::bspherE( const poinT& C, valuE r ) { 
	  this->C = C;  this->r = r;
  } 




  inline bspherE::bspherE( const bspherE& bsph ) { 
	  this->C = bsph.C;  this->r = bsph.r;
  } 




  inline BOOL bspherE::operator==( const bspherE& bsph ) const {
	  if( C == bsph.C && r == bsph.r ) return TRUE; else return FALSE;
  }




  inline BOOL bspherE::operator!=( const bspherE& bsph ) const {
	  return !( ( *this ) == bsph );
  }




  inline BOOL bspherevectoR( const bspherE& bsph, const poinT& pt ) {
	  if( sqR( bsph.C.x-pt.x )+sqR( bsph.C.y-pt.y )+sqR( bsph.C.z-pt.z ) <= bsph.r*bsph.r ) return TRUE; else return FALSE;
  }

  


  inline long bsphereraY( const bspherE& bsph, const raY& r, valuE *tmin, valuE *tmax ) {
	  valuE rr, d, ll, mm, q;
	  vectoR l;


	  rr = bsph.r*bsph.r;
	  l = bsph.C-r.A;
	  d = doT( l, r.q );
	  ll = doT( l, l );
	  if( d < 0.0 && ll > rr ) return -1;
	  mm = ll-d*d;
	  if( mm > rr ) return -1;
	  q = sqrt( rr-mm );
	  if( ll > rr ) {
	      *tmin = d-q;
		  *tmax = d+q;

		  return 1;
	  } else {
	      *tmin = d+q;

		  return 0;
	  }
  }




  inline BOOL bsphereraY( const bspherE& bsph, const raY& r ) {
	  valuE rr, d, ll;
	  vectoR l;


	  rr = bsph.r*bsph.r;
	  l = bsph.C-r.A;
	  d = doT( l, r.q );
	  ll = doT( l, l );
	  if( ( ll-d*d > rr ) || ( d < 0.0 && ll > rr ) ) return FALSE;

	  return TRUE;
  }




  inline BOOL bsphereraY( const bspherE& bsph, const raY& r, valuE *t ) {
	  valuE tmin, tmax;
	  long l = bsphereraY( bsph, r, &tmin, &tmax );

	  if( l != -1 ) {
		  *t = tmin; 
	  
		  return TRUE; 
	  } else return FALSE;
  }




  inline long bsphereplanE( const bspherE& bsph, const planE& pl ) {
      valuE a = planepoinT( pl, bsph.C );

      if( abs( a )-EPSILON <= bsph.r ) {
          return 0; 
      } else {
          if( a > 0.0 ) return 1; else return -1;
      }
  }




  inline BOOL bsphereaabboX( const bspherE& bsph, const aabboX& aabb ) {
	  valuE d = 0.0;

	  if( bsph.C.x < aabb.min.x ) d+=sqR( bsph.C.x-aabb.min.x ); else
	  if( bsph.C.x > aabb.max.x ) d+=sqR( bsph.C.x-aabb.max.x ); 
	  if( bsph.C.y < aabb.min.y ) d+=sqR( bsph.C.y-aabb.min.y ); else
	  if( bsph.C.y > aabb.max.y ) d+=sqR( bsph.C.y-aabb.max.y ); 
	  if( bsph.C.z < aabb.min.z ) d+=sqR( bsph.C.z-aabb.min.z ); else
	  if( bsph.C.z > aabb.max.z ) d+=sqR( bsph.C.z-aabb.max.z ); 

	  if( d > bsph.r*bsph.r ) return FALSE; else return TRUE;
  }




  inline BOOL bsphereoobboX( const bspherE& bsph, const oobboX& oobb ) {
      vectoR v = bsph.C-oobb.C;

      return bsphereaabboX( bspherE( poinT( doT( oobb.u, v ), doT( oobb.v, v ), doT( oobb.w, v ) ), bsph.r ), 
                            aabboX( poinT( -oobb.hu, -oobb.hv, -oobb.hw ), poinT( oobb.hu, oobb.hv, oobb.hw ) ) );
  }




  inline BOOL bspherebspherE( const bspherE& bsph1, const bspherE& bsph2 ) {
	  if( sqR( bsph1.C.x-bsph2.C.x )+sqR( bsph1.C.y-bsph2.C.y )+sqR( bsph1.C.z-bsph2.C.z ) <= sqR( bsph1.r+bsph2.r ) ) return TRUE; else return FALSE;
  }








  // BSPHEREARRAY
  class bspherearraY: public arraY<bspherE> {};
