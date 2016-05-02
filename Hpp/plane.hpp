
  // PLANE
  class planE {
      public:
          vectoR n;
		  valuE d;


          planE( void );
		  planE( const vectoR& n, valuE d );
		  planE( const vectoR& n, const poinT& pt );
		  planE( const poinT& A, const poinT& B, const poinT& C );
		  planE( valuE a, valuE b, valuE c, valuE d );
		  planE( const planE& pl );
          
          planE operator+( void ) const;
          planE operator-( void ) const;
          
          BOOL operator==( const planE& pl ) const;
          BOOL operator!=( const planE& pl ) const;
  };


  inline valuE planepoinT( const planE& pl, const poinT& pt );
  inline BOOL planeraY( const planE& pl, const raY& r, BOOL cull, valuE *t, poinT *pt );
  inline BOOL planeplanE( const planE& pl0, const planE& pl1, const planE& pl2, poinT *pt );






  inline planE::planE( void ) {
	  n = vectoR();
      d = 0.0;
  }
  
  
  
  
  inline planE::planE( const vectoR& n, valuE d ) {
      this->n = n;  this->d = d;
  }
  
  
  
  
  inline planE::planE( const vectoR& n, const poinT& pt ) {
      this->n = n;
      d = -( n.x*pt.x+n.y*pt.y+n.z*pt.z );
  }
  
  
  
  
  inline planE::planE( const poinT& A, const poinT& B, const poinT& C ) {
	  n = normalizE( crosS( B-A, C-A ) );
	  d = -( n.x*A.x+n.y*A.y+n.z*A.z );
  }
  
  
  
  
  inline planE::planE( valuE a, valuE b, valuE c, valuE d ) {
      n = vectoR( a, b, c );  
      this->d = d;
  }
  
  
  
  
  inline planE::planE( const planE& pl ) {
      n = pl.n;  d = pl.d;
  }
  
  
  
  
  inline planE planE::operator+( void ) const {
      return *this;
  }
  
  
  
  
  inline planE planE::operator-( void ) const {
      return planE( -n, -d );
  }
  
  
  
  
  inline BOOL planE::operator==( const planE& pl ) const {
      return n == pl.n && d == pl.d;
  }
  
  
  
  
  inline BOOL planE::operator!=( const planE& pl ) const {
      return n != pl.n || d != pl.d;
  }




  inline valuE planepoinT( const planE& pl, const poinT& pt ) {
      return pl.n.x*pt.x+pl.n.y*pt.y+pl.n.z*pt.z+pl.d;
  }




  inline BOOL planeraY( const planE& pl, const raY& r, BOOL cull, valuE *t, poinT *pt ) {
	  valuE a = doT( pl.n, r.q ); 

      if( cull ) { if( a > -EPSILON ) return FALSE; } else { if( abs( a ) < EPSILON ) return FALSE; }
	  *t = -planepoinT( pl, r.A )/a;
	  if( *t < 0.0 ) return FALSE;
	  *pt = r.A+r.q**t;

	  return TRUE;
  }




  inline BOOL planeplanE( const planE& pl0, const planE& pl1, const planE& pl2, poinT *pt ) {
      valuE a;          

      a = pl0.n.x*pl1.n.y*pl2.n.z + pl0.n.y*pl1.n.z*pl2.n.x + pl0.n.z*pl1.n.x*pl2.n.y-
        ( pl0.n.z*pl1.n.y*pl2.n.x + pl0.n.x*pl1.n.z*pl2.n.y + pl0.n.y*pl1.n.x*pl2.n.z );

      if( abs( a ) < EPSILON ) return FALSE; 

      a = 1.0/a; 
      *pt = poinT( -( pl0.d*pl1.n.y*pl2.n.z + pl0.n.y*pl1.n.z*pl2.d + pl0.n.z*pl1.d*pl2.n.y-
                    ( pl0.n.z*pl1.n.y*pl2.d + pl0.d*pl1.n.z*pl2.n.y + pl0.n.y*pl1.d*pl2.n.z ) )*a,
                   -( pl0.n.x*pl1.d*pl2.n.z + pl0.d*pl1.n.z*pl2.n.x + pl0.n.z*pl1.n.x*pl2.d-
                    ( pl0.n.z*pl1.d*pl2.n.x + pl0.n.x*pl1.n.z*pl2.d + pl0.d*pl1.n.x*pl2.n.z ) )*a, 
                   -( pl0.n.x*pl1.n.y*pl2.d + pl0.n.y*pl1.d*pl2.n.x + pl0.d*pl1.n.x*pl2.n.y-
                    ( pl0.d*pl1.n.y*pl2.n.x + pl0.n.x*pl1.d*pl2.n.y + pl0.n.y*pl1.n.x*pl2.d ) )*a );

      return TRUE;
  }








  // PLANEARRAY
  class planearraY: public arraY<planE> {};
