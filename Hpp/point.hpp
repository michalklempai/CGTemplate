
  // POINT
  class poinT {
      public:
          valuE x, y, z; 


          poinT( void );
          poinT( valuE x, valuE y, valuE z = 0.0 );
          poinT( const poinT& pt );

          poinT operator+( void ) const;
          poinT operator-( void ) const;

          poinT operator*( valuE val ) const;
          friend poinT operator*( valuE val, const poinT& pt );
          poinT operator/( valuE val ) const;
          poinT& operator*=( valuE val );
          poinT& operator/=( valuE val );

          poinT operator+( const vectoR& v ) const;
          friend poinT operator+( const vectoR& v, const poinT& pt );
          poinT operator-( const vectoR& v ) const;
          friend poinT operator-( const vectoR& v, const poinT& pt );
   		  poinT& operator+=( const vectoR& v );
          poinT& operator-=( const vectoR& v );

          poinT operator+( const poinT& pt ) const;
          vectoR operator-( const poinT& pt ) const;
   		  poinT& operator+=( const poinT& pt );
		  BOOL operator==( const poinT& pt ) const;
          BOOL operator!=( const poinT& pt ) const;
  };

         
  inline valuE distancE( const poinT& A, const poinT& B );
  inline valuE distancE( const poinT& A, const poinT& B, const poinT& P, BOOL abscissa = FALSE );
  inline poinT lerP( valuE x, const poinT& A, const poinT& B );
  inline poinT herminterP( valuE x, const poinT& A, const poinT& B );
  inline valuE triangleareA( const poinT& A, const poinT& B, const poinT& C );
  inline poinT randompoinT( const poinT& min = poinT( -1.0, -1.0, -1.0 ), const poinT& max = poinT( 1.0, 1.0, 1.0 ) );
  inline void planE_( const vectoR& n, const poinT& pt, valuE *a, valuE *b, valuE *c );
  inline void planE_( const poinT& A, const poinT& B, valuE *a, valuE *b, valuE *c );
  inline valuE planepoinT( valuE a, valuE b, valuE c, const poinT& pt );
  inline BOOL linelinE( const poinT& O1, const vectoR& d1, const poinT& O2, const vectoR& d2, valuE *s, valuE *t = NULL );






  inline poinT::poinT( void ) {
      x = y = z = 0.0;
  }




  inline poinT::poinT( valuE x, valuE y, valuE z ) {
      this->x = x;  this->y = y;  this->z = z;
  }




  inline poinT::poinT( const poinT& pt ) {
      x = pt.x;  y = pt.y;  z = pt.z;
  }




  inline poinT poinT::operator+( void ) const {
      return *this;
  }
  
  
  
  
  inline poinT poinT::operator-( void ) const {
      return poinT( -x, -y, -z );
  }
  
  
  
  
  inline poinT poinT::operator*( valuE val ) const {
      return poinT( x*val, y*val, z*val );
  }
  
  
  
  
  inline poinT operator*( valuE val, const poinT& pt ) {
      return poinT( val*pt.x, val*pt.y, val*pt.z );
  }
  
  
  
  
  inline poinT poinT::operator/( valuE val ) const {
      if( abs( val ) > EPSILON ) {
    	  valuE inv_val = 1.0/val;

          return poinT( x*inv_val, y*inv_val, z*inv_val );
      } else return poinT();
  }
  
  
  
  
  inline poinT& poinT::operator*=( valuE val ) {
      x*=val;  y*=val;  z*=val;

      return *this;
  }
  
  
  
  
  inline poinT& poinT::operator/=( valuE val ) {
      if( abs( val ) > EPSILON ) {
    	  valuE inv_val = 1.0/val;

          x*=inv_val;  y*=inv_val;  z*=inv_val;
      }

      return *this;
  }
  
  
  
  
  inline poinT poinT::operator+( const vectoR& v ) const {
      return poinT( x+v.x, y+v.y, z+v.z );
  }
  
  
  
  
  inline poinT operator+( const vectoR& v, const poinT& pt ) {
      return poinT( v.x+pt.x, v.y+pt.y, v.z+pt.z );
  }
  
  
  
  
  inline poinT poinT::operator-( const vectoR& v ) const {
      return poinT( x-v.x, y-v.y, z-v.z );
  }
  
  
  
  
  inline poinT operator-( const vectoR& v, const poinT& pt ) {
      return poinT( v.x-pt.x, v.y-pt.y, v.z-pt.z );
  }
  
  
  
  
  inline poinT& poinT::operator+=( const vectoR& v ) {
      x+=v.x;  y+=v.y;  z+=v.z;

      return *this;
  }
  
  
  
  
  inline poinT& poinT::operator-=( const vectoR& v ) {
      x-=v.x;  y-=v.y;  z-=v.z;

      return *this;
  }
  
  
  
  
  inline poinT poinT::operator+( const poinT& pt ) const {
      return poinT( x+pt.x, y+pt.y, z+pt.z );
  }
  
  
  
  
  inline vectoR poinT::operator-( const poinT& pt ) const {
      return vectoR( x-pt.x, y-pt.y, z-pt.z );
  }
  
  
  
  
  inline poinT& poinT::operator+=( const poinT& pt ) {
      x+=pt.x;  y+=pt.y;  z+=pt.z;

      return *this;
  }
  
  
  
  
  inline BOOL poinT::operator==( const poinT& pt ) const {
      return x == pt.x && y == pt.y && z == pt.z;
  }
  
  
  
  
  inline BOOL poinT::operator!=( const poinT& pt ) const {
      return x != pt.x || y != pt.y || z != pt.z;
  }




  inline valuE distancE( const poinT& A, const poinT& B ) {
	  return lengtH( B-A );
  }




  inline valuE distancE( const poinT& A, const poinT& B, const poinT& P, BOOL abscissa ) {
      valuE a;
      vectoR q = B-A;

      a = diV( doT( q, P-A ), doT( q, q ), 0.0 );
      if( abscissa ) {
          if( a < 0.0 ) return distancE( A, P ); else
          if( a > 1.0 ) return distancE( B, P ); else return distancE( A+a*q, P );
      } else {
          return distancE( A+a*q, P );
      }
  }




  inline poinT lerP( valuE x, const poinT& A, const poinT& B ) {
	  return A+( B-A )*x;
  }




  inline poinT herminterP( valuE x, const poinT& A, const poinT& B ) {
	  return A+( B-A )*( 3.0*x*x-2.0*x*x*x );
  }




  inline valuE triangleareA( const poinT& A, const poinT& B, const poinT& C ) {
	  return ( B.x-A.x )*( C.y-A.y )-( B.y-A.y )*( C.x-A.x );
  }




  inline poinT randompoinT( const poinT& min, const poinT& max ) {
	  return poinT( randomvaluE( min.x, max.x ), randomvaluE( min.y, max.y ), randomvaluE( min.z, max.z ) );
  }




  inline void planE_( const vectoR& n, const poinT& pt, valuE *a, valuE *b, valuE *c ) {
	  valuE val = diV( 1.0, sqrT( n.x*n.x+n.y*n.y ), 0.0 );

	  *a = n.x*val;
	  *b = n.y*val;
	  *c = -( *a*pt.x+*b*pt.y );
  }




  inline void planE_( const poinT& A, const poinT& B, valuE *a, valuE *b, valuE *c ) {
	  valuE val;

	  *a = B.y-A.y;  
	  *b = A.x-B.x;
	  val = diV( 1.0, sqrT( sqR( *a )+sqR( *b ) ), 0.0 );
	  *a *= val;  *b *= val;
	  *c = -( *a*A.x+*b*A.y );
  }




  inline valuE planepoinT( valuE a, valuE b, valuE c, const poinT& pt ) {
	  return a*pt.x+b*pt.y+c;
  }




  inline BOOL linelinE( const poinT& O1, const vectoR& d1, const poinT& O2, const vectoR& d2, valuE *s, valuE *t ) {
      valuE val;
      vectoR v;

      v = crosS( d1, d2 );
      val = doT( v, v );
      if( abs( val ) < EPSILON ) return FALSE;
      val = 1.0/val;
      *s = doT( crosS( O2-O1, d2 ), v )*val;
      if( t != NULL ) *t = doT( crosS( O1-O2, d1 ), v )*val;

      return TRUE;
  }








  // POINTARRAY
  class pointarraY: public arraY<poinT> {};


  BOOL pointinpolygoN( const poinT& T, pointarraY *pta );
  void offsetpolygoN( valuE val, pointarraY *pta, BOOL closed, pointarraY *pta2 );
  BOOL trianglelinE( const poinT& A, const poinT& B, const poinT& C, const poinT& P, const poinT& Q, pointarraY *pta_left, pointarraY *pta_, pointarraY *pta_right );
  void incrementalplaneintersecT( const poinT& A, const poinT& B, pointarraY *pta );






  BOOL pointinpolygoN( const poinT& T, pointarraY *pta ) {
	  if( pta != NULL && pta->num > 0 ) {
	      register long i;
		  long crossings;
	      BOOL y0, y1, x0;
		  poinT pt0, pt1;


	      pt0 = pta->elem[pta->num-1];
		  pt1 = pta->elem[0];
	      y0 = ( pt0.y >= T.y );
		  crossings = 0;
	      for( i = 1;  i <= pta->num;  i++ ) {
			  y1 = ( pt1.y >= T.y );
	          if( y0 != y1 ) {
  				  x0 = ( pt0.x >= T.x );
  			      if( x0 == ( pt1.x >= T.x ) ) {
		    	      if( x0 ) crossings+=( y0 ? -1 : 1 );
	  	          } else {
	    			  if( ( pt1.x-( pt1.y-T.y )*( pt0.x-pt1.x )/( pt0.y-pt1.y ) ) >= T.x ) crossings+=( y0 ? -1 : 1 );
				  }
			  }

		      y0 = y1;
	          pt0 = pt1;
			  if( i < pta->num ) pt1 = pta->elem[i];
		  }

	      return ( crossings != 0 );
	  } else return FALSE;
  }




  void offsetpolygoN( valuE val, pointarraY *pta, BOOL closed, pointarraY *pta2 ) {
      if( pta->num > 1 ) {
          register long i;
          valuE a, b;
          vectoR u, v, w, p;


          pta2->deletealL();

          if( !closed ) {
              u = pta->elem[1]-pta->elem[0];
              v = normalizE( vectoR( u.y, -u.x, 0.0 ) )*val;
              pta2->inserT( -1, pta->elem[0]+v );

              for( i = 1;  i < pta->num-1;  i++ ) {
                  w = u;
                  u = pta->elem[i+1]-pta->elem[i];
                  v = normalizE( vectoR( u.y, -u.x, 0.0 ) )*val;

                  if( linelinE( pta2->elem[pta2->num-1], w, pta->elem[i]+v, u, &a, &b ) ) {
                      pta2->inserT( -1, pta2->elem[pta2->num-1]+w*a );
                  } else {
                      if( doT( w, u ) >= 0.0 ) {
                          pta2->inserT( -1, pta->elem[i]+v );
                      } else {
                          pta2->inserT( -1, pta->elem[i]+normalizE( vectoR( w.y, -w.x, 0.0 ) )*val+normalizE( w )*abs( val ) );
                          pta2->inserT( -1, pta->elem[i]+v-normalizE( u )*abs( val ) );
                      }
                  }
              }

              u = pta->elem[pta->num-1]-pta->elem[pta->num-2];
              v = normalizE( vectoR( u.y, -u.x, 0.0 ) )*val;
              pta2->inserT( -1, pta->elem[pta->num-1]+v );
          } else {
              u = pta->elem[1]-pta->elem[0];
              v = normalizE( vectoR( u.y, -u.x, 0.0 ) )*val;
              for( i = 1;  i < pta->num+1;  i++ ) {
                  w = u;
                  p = v;
                  u = pta->elem[( i+1 ) % pta->num]-pta->elem[i % pta->num];
                  v = normalizE( vectoR( u.y, -u.x, 0.0 ) )*val;

                  if( linelinE( pta->elem[i-1]+p, w, pta->elem[i % pta->num]+v, u, &a, &b ) ) {
                      pta2->inserT( -1, pta->elem[i-1]+p+w*a );
                  } else {
                      if( doT( w, u ) >= 0.0 ) {
                          pta2->inserT( -1, pta->elem[i % pta->num]+v );
                      } else {
                          pta2->inserT( -1, pta->elem[i % pta->num]+p+normalizE( w )*abs( val ) );
                          pta2->inserT( -1, pta->elem[i % pta->num]+v-normalizE( u )*abs( val ) );
                      }
                  }
              }
          }
      }
  }




  BOOL trianglelinE( const poinT& A, const poinT& B, const poinT& C, const poinT& P, const poinT& Q, pointarraY *pta_left, pointarraY *pta_, pointarraY *pta_right ) {
      long l[4];
      valuE val, val2;
      vectoR u;
      poinT pt, pt2;


      pta_left->deletealL();
      pta_->deletealL();
      pta_right->deletealL();


	  u = Q-P;
	  val2 = P.y*Q.x-P.x*Q.y;
	  val = u.y*A.x-u.x*A.y+val2;
      if( val <= -EPSILON ) l[0] =  -1; else if( val >= EPSILON ) l[0] = 1; else l[0] = 0; 
	  val = u.y*B.x-u.x*B.y+val2;
      if( val <= -EPSILON ) l[1] = -1; else if( val >= EPSILON ) l[1] = 1; else l[1] = 0; 
	  val = u.y*C.x-u.x*C.y+val2;
      if( val <= -EPSILON ) l[2] = -1; else if( val >= EPSILON ) l[2] = 1; else l[2] = 0; 
      l[3] = l[0]+l[1]+l[2];


      if( l[0] == 0 && l[1] == 0 && l[2] == 0 ) {
          pta_->inserT( -1, A );  pta_->inserT( -1, B );  pta_->inserT( -1, C );

          return FALSE;
      } else
      if( l[0] <= 0 && l[1] <= 0 && l[2] <= 0 ) {
          pta_left->inserT( -1, A );  pta_left->inserT( -1, B );  pta_left->inserT( -1, C );

          return FALSE;
      } else
      if( l[0] >= 0 && l[1] >= 0 && l[2] >= 0 ) {
          pta_right->inserT( -1, A );  pta_right->inserT( -1, B );  pta_right->inserT( -1, C );

          return FALSE;
      } else
      if( l[3] == 0 ) {
          if( ( l[0] == -1 && l[1] == 0 && l[2] == 1 ) || ( l[0] == 1 && l[1] == 0 && l[2] == -1 ) ) {
              linelinE( P, u, C, A-C, &val, &val2 ); 
              pt = P+u*val;

              if( l[0] == -1 && l[1] == 0 && l[2] == 1 ) {
                  pta_left->inserT( -1, A );  pta_left->inserT( -1, B );  pta_left->inserT( -1, pt );
                  pta_right->inserT( -1, C );  pta_right->inserT( -1, pt );  pta_right->inserT( -1, B );
              } else {
                  pta_left->inserT( -1, B );  pta_left->inserT( -1, C );  pta_left->inserT( -1, pt );
                  pta_right->inserT( -1, A );  pta_right->inserT( -1, B );  pta_right->inserT( -1, pt );
              }
          } else
          if( ( l[0] == -1 && l[1] == 1 && l[2] == 0 ) || ( l[0] == 1 && l[1] == -1 && l[2] == 0 ) ) {
              linelinE( P, u, A, B-A, &val, &val2 ); 
              pt = P+u*val;

              if( l[0] == -1 && l[1] == 1 && l[2] == 0 ) {
                  pta_left->inserT( -1, C );  pta_left->inserT( -1, A );  pta_left->inserT( -1, pt );
                  pta_right->inserT( -1, B );  pta_right->inserT( -1, C );  pta_right->inserT( -1, pt );
              } else {
                  pta_left->inserT( -1, B );  pta_left->inserT( -1, C );  pta_left->inserT( -1, pt );
                  pta_right->inserT( -1, C );  pta_right->inserT( -1, A );  pta_right->inserT( -1, pt );
              }
          } else
          if( ( l[0] == 0 && l[1] == -1 && l[2] == 1 ) || ( l[0] == 0 && l[1] == 1 && l[2] == -1 ) ) {
              linelinE( P, u, B, C-B, &val, &val2 ); 
              pt = P+u*val;

              if( l[0] == 0 && l[1] == -1 && l[2] == 1 ) {
                  pta_left->inserT( -1, A );  pta_left->inserT( -1, B );  pta_left->inserT( -1, pt );
                  pta_right->inserT( -1, C );  pta_right->inserT( -1, A );  pta_right->inserT( -1, pt );
              } else {
                  pta_left->inserT( -1, C );  pta_left->inserT( -1, A );  pta_left->inserT( -1, pt );
                  pta_right->inserT( -1, A );  pta_right->inserT( -1, B );  pta_right->inserT( -1, pt );
              }
          }

          return TRUE;
      } else {
          if( ( l[0] == -1 && l[1] == -1 && l[2] == 1 ) || ( l[0] == 1 && l[1] == 1 && l[2] == -1 ) ) {
              linelinE( P, u, C, A-C, &val, &val2 ); 
              pt = P+u*val;
              linelinE( P, u, B, C-B, &val, &val2 ); 
              pt2 = P+u*val;

              if( l[0] == -1 && l[1] == -1 && l[2] == 1 ) {
                  pta_left->inserT( -1, B );  pta_left->inserT( -1, pt2 );  pta_left->inserT( -1, pt );
                  pta_left->inserT( -1, B );  pta_left->inserT( -1, pt );  pta_left->inserT( -1, A );
                  pta_right->inserT( -1, C );  pta_right->inserT( -1, pt );  pta_right->inserT( -1, pt2 );
              } else {
                  pta_left->inserT( -1, C );  pta_left->inserT( -1, pt );  pta_left->inserT( -1, pt2 );
                  pta_right->inserT( -1, B );  pta_right->inserT( -1, pt2 );  pta_right->inserT( -1, pt );
                  pta_right->inserT( -1, B );  pta_right->inserT( -1, pt );  pta_right->inserT( -1, A );
              }
          } else
          if( ( l[0] == -1 && l[1] == 1 && l[2] == -1 ) || ( l[0] == 1 && l[1] == -1 && l[2] == 1 ) ) {
              linelinE( P, u, A, B-A, &val, &val2 ); 
              pt = P+u*val;
              linelinE( P, u, B, C-B, &val, &val2 ); 
              pt2 = P+u*val;

              if( l[0] == -1 && l[1] == 1 && l[2] == -1 ) {
                  pta_left->inserT( -1, A );  pta_left->inserT( -1, pt );  pta_left->inserT( -1, pt2 );
                  pta_left->inserT( -1, A );  pta_left->inserT( -1, pt2 );  pta_left->inserT( -1, C );
                  pta_right->inserT( -1, B );  pta_right->inserT( -1, pt2 );  pta_right->inserT( -1, pt );
              } else {
                  pta_left->inserT( -1, B );  pta_left->inserT( -1, pt2 );  pta_left->inserT( -1, pt );
                  pta_right->inserT( -1, A );  pta_right->inserT( -1, pt );  pta_right->inserT( -1, pt2 );
                  pta_right->inserT( -1, A );  pta_right->inserT( -1, pt2 );  pta_right->inserT( -1, C );
              }
          } else
          if( ( l[0] == -1 && l[1] == 1 && l[2] == 1 ) || ( l[0] == 1 && l[1] == -1 && l[2] == -1 ) ) {
              linelinE( P, u, A, B-A, &val, &val2 ); 
              pt = P+u*val;
              linelinE( P, u, C, A-C, &val, &val2 ); 
              pt2 = P+u*val;

              if( l[0] == -1 && l[1] == 1 && l[2] == 1 ) {
                  pta_left->inserT( -1, A );  pta_left->inserT( -1, pt );  pta_left->inserT( -1, pt2 );
                  pta_right->inserT( -1, C );  pta_right->inserT( -1, pt2 );  pta_right->inserT( -1, pt );
                  pta_right->inserT( -1, C );  pta_right->inserT( -1, pt );  pta_right->inserT( -1, B );
              } else {
                  pta_left->inserT( -1, C );  pta_left->inserT( -1, pt2 );  pta_left->inserT( -1, pt );
                  pta_left->inserT( -1, C );  pta_left->inserT( -1, pt );  pta_left->inserT( -1, B );
                  pta_right->inserT( -1, A );  pta_right->inserT( -1, pt );  pta_right->inserT( -1, pt2 );
              }
          } 

          return TRUE;
      }
  }




  void incrementalplaneintersecT( const poinT& A, const poinT& B, pointarraY *pta ) {
	  BOOL b_ = TRUE;  // ze vstupnu priamku pridavame do vystupu
	  register long i;
	  valuE val, a, b, c, a2, b2, c2, d, e;  
	  vectoR v;
	  poinT pt, pt0, pt1;


//	  planE_( A, B, &a, &b, &c );
	  a = B.y-A.y;  
	  b = A.x-B.x;
	  c = -( a*A.x+b*A.y );

	  
	  v = vectoR( -b, a, 0.0 );
	  pt0 = ( A+B )*0.5-INFINITY*v;	
	  pt1 = ( A+B )*0.5+INFINITY*v;	

	  for( i = pta->num-2;  i >= 0;  i-=2 ) {
//		  planE_( pta->elem[i], pta->elem[i+1], &a2, &b2, &c2 );
		  a2 = pta->elem[i+1].y-pta->elem[i].y;  
		  b2 = pta->elem[i].x-pta->elem[i+1].x;
		  c2 = -( a2*pta->elem[i].x+b2*pta->elem[i].y );

          d = planepoinT( a2, b2, c2, pt0 );
	      e = planepoinT( a2, b2, c2, pt1 );

		  if( linelinE( A, v, pta->elem[i], pta->elem[i+1]-pta->elem[i], &val ) ) {
			  pt = A+val*v;


			  if( d < -EPSILON ) {
				  if( e < -EPSILON ) {
				      b_ = FALSE;
					  i = 0;  // skoncime, vstupna usecka bola vylucena nejakou useckov z prieniku
				  } else 
				  if( e > EPSILON ) {
					  pt0 = pt;
				  } else {
				      b_ = FALSE;
					  i = 0;  // skoncime, vstupna usecka bola vylucena nejakou useckov z prieniku
				  }
			  } else 
			  if( d > EPSILON ) {
				  if( e < -EPSILON ) {
					  pt1 = pt;
				  } else 
				  if( e > EPSILON ) {
				  } else {
				  }
			  } else {
				  if( e < -EPSILON ) {
				      b_ = FALSE;
					  i = 0;  // skoncime, vstupna usecka bola vylucena nejakou useckov z prieniku
				  } else 
				  if( e > EPSILON ) {
				  } else {
				      b_ = FALSE;
					  i = 0;  // skoncime, vstupna usecka bola vylucena nejakou useckov z prieniku
				  }
			  }


			  if( b_ ) {
				  d = planepoinT( a, b, c, pta->elem[i] );
			      e = planepoinT( a, b, c, pta->elem[i+1] );

				  if( d < -EPSILON ) {
					  if( e < -EPSILON ) {
					      pta->deletE( i );	
						  pta->deletE( i );	
					  } else 
					  if( e > EPSILON ) {
						  pta->elem[i] = pt;
					  } else {
					      pta->deletE( i );	
						  pta->deletE( i );	
					  }
				  } else 
				  if( d > EPSILON ) {
					  if( e < -EPSILON ) {
						  pta->elem[i+1] = pt;
					  } else 
					  if( e > EPSILON ) {
					  } else {
					  }
				  } else {
					  if( e < -EPSILON ) {
					      pta->deletE( i );	
						  pta->deletE( i );	
					  } else 
					  if( e > EPSILON ) {
					  } else {
					      pta->deletE( i );	
						  pta->deletE( i );	
					  }
				  }
			  }
		  } else {  // su rovnobezne
			  if( planepoinT( a, b, c, pta->elem[i] ) < 0.0 ) {  // ak je pridavana priamka pred vysetrovanou
			      pta->deletE( i );	
			      pta->deletE( i );	
			  } else {
				  b_ = FALSE;
				  i = 0;  // skoncime, vstupna usecka bola vylucena nejakou useckov z prieniku
			  }
		  }
	  }
	  
	  if( b_ && sqR( pt1.x-pt0.x )+sqR( pt1.y-pt0.y ) > EPSILON ) {
		  pta->inserT( -1, pt0, 2 );
		  pta->elem[pta->num-1] = pt1;
	  }
  }
