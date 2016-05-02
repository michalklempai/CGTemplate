
  // AABBOX
  class aabboX {
      public:
		  poinT min, max;


          aabboX( void );
          aabboX( valuE minx, valuE miny, valuE minz, valuE maxx, valuE maxy, valuE maxz );
		  aabboX( const poinT& min, const poinT& max ); 
          aabboX( const aabboX& aabb );

          BOOL operator==( const aabboX& aabb ) const;
          BOOL operator!=( const aabboX& aabb ) const;
  };


  inline BOOL aabboxpoinT( const aabboX& aabb, const poinT& pt );
  inline BOOL aabboxraY( const aabboX& aabb, const raY& r, valuE *tmin_, valuE *tmax_ );
  inline BOOL aabboxraY( const aabboX& aabb, const raY& r );
  inline BOOL aabboxraY( const aabboX& aabb, const raY& r, valuE *t );
  inline long aabboxplanE( const aabboX& aabb, const planE& pl );
  inline BOOL aabboxaabboX( const aabboX& aabb1, const aabboX& aabb2 );
  inline void rendergL( const aabboX& aabb );






  inline aabboX::aabboX( void ) {
      min = max = poinT();
  }




  inline aabboX::aabboX( valuE minx, valuE miny, valuE minz, valuE maxx, valuE maxy, valuE maxz ) {
      min.x = minx;  min.y = miny;  min.z = minz;
      max.x = maxx;  max.y = maxy;  max.z = maxz;
  }




  inline aabboX::aabboX( const poinT& min, const poinT& max ) {
      this->min = min;  this->max = max;
  } 




  inline aabboX::aabboX( const aabboX& aabb ) {
      min = aabb.min;  max = aabb.max;
  }




  inline BOOL aabboX::operator==( const aabboX& aabb ) const {
      return min == aabb.min && max == aabb.max;
  }




  inline BOOL aabboX::operator!=( const aabboX& aabb ) const {
      return min != aabb.min || max != aabb.max;
  }




  inline BOOL aabboxpoinT( const aabboX& aabb, const poinT& pt ) {
      if( pt.x < aabb.min.x || pt.x > aabb.max.x ) return FALSE; else
      if( pt.y < aabb.min.y || pt.y > aabb.max.y ) return FALSE; else
      if( pt.z < aabb.min.z || pt.z > aabb.max.z ) return FALSE; else return TRUE;
  }

  


  inline BOOL aabboxraY( const aabboX& aabb, const raY& r, valuE *tmin_, valuE *tmax_ ) {
	  valuE tmin, tmax, t1, t2, a;


	  tmin = -INFINITY;  tmax = INFINITY;

	  if( abs( r.q.x ) > EPSILON ) {
	      a = 1.0/r.q.x;
          t1 = ( aabb.max.x-r.A.x )*a;    
	      t2 = ( aabb.min.x-r.A.x )*a;    
		  if( t1 > t2 ) {
		      a = t1;
			  t1 = t2;
			  t2 = a;
		  }
		  if( t1 > tmin ) tmin = t1;
		  if( t2 < tmax ) tmax = t2;
		  if( tmin > tmax ) return FALSE;
		  if( tmax < 0.0 ) return FALSE;
	  }	else
	  if( r.A.x > aabb.max.x || r.A.x < aabb.min.x ) return FALSE;

	  if( abs( r.q.y ) > EPSILON ) {
          a = 1.0/r.q.y;
	      t1 = ( aabb.max.y-r.A.y )*a;    
	      t2 = ( aabb.min.y-r.A.y )*a;    
		  if( t1 > t2 ) {
		      a = t1;
			  t1 = t2;
			  t2 = a;
		  }
		  if( t1 > tmin ) tmin = t1;
		  if( t2 < tmax ) tmax = t2;
		  if( tmin > tmax ) return FALSE;
		  if( tmax < 0.0 ) return FALSE;
	  }	else
	  if( r.A.y > aabb.max.y || r.A.y < aabb.min.y ) return FALSE;

	  if( abs( r.q.z ) > EPSILON ) {
          a = 1.0/r.q.z;
	      t1 = ( aabb.max.z-r.A.z )*a;    
	      t2 = ( aabb.min.z-r.A.z )*a;    
		  if( t1 > t2 ) {
		      a = t1;
			  t1 = t2;
			  t2 = a;
		  }
		  if( t1 > tmin ) tmin = t1;
		  if( t2 < tmax ) tmax = t2;
		  if( tmin > tmax ) return FALSE;
		  if( tmax < 0.0 ) return FALSE;
	  }	else
	  if( r.A.z > aabb.max.z || r.A.z < aabb.min.z ) return FALSE;

	  
	  *tmin_ = tmin;  *tmax_ = tmax;

	  
	  return TRUE; 
  }




  inline BOOL aabboxraY( const aabboX& aabb, const raY& r ) {
	  valuE tmin, tmax, t1, t2, a;


	  tmin = -INFINITY;  tmax = INFINITY;

	  if( abs( r.q.x ) > EPSILON ) {
	      a = 1.0/r.q.x;
          t1 = ( aabb.max.x-r.A.x )*a;    
	      t2 = ( aabb.min.x-r.A.x )*a;    
		  if( t1 > t2 ) {
		      a = t1;
			  t1 = t2;
			  t2 = a;
		  }
		  if( t1 > tmin ) tmin = t1;
		  if( t2 < tmax ) tmax = t2;
		  if( tmin > tmax ) return FALSE;
		  if( tmax < 0.0 ) return FALSE;
	  }	else
	  if( r.A.x > aabb.max.x || r.A.x < aabb.min.x ) return FALSE;

	  if( abs( r.q.y ) > EPSILON ) {
          a = 1.0/r.q.y;
	      t1 = ( aabb.max.y-r.A.y )*a;    
	      t2 = ( aabb.min.y-r.A.y )*a;    
		  if( t1 > t2 ) {
		      a = t1;
			  t1 = t2;
			  t2 = a;
		  }
		  if( t1 > tmin ) tmin = t1;
		  if( t2 < tmax ) tmax = t2;
		  if( tmin > tmax ) return FALSE;
		  if( tmax < 0.0 ) return FALSE;
	  }	else
	  if( r.A.y > aabb.max.y || r.A.y < aabb.min.y ) return FALSE;

	  if( abs( r.q.z ) > EPSILON ) {
          a = 1.0/r.q.z;
	      t1 = ( aabb.max.z-r.A.z )*a;    
	      t2 = ( aabb.min.z-r.A.z )*a;    
		  if( t1 > t2 ) {
		      a = t1;
			  t1 = t2;
			  t2 = a;
		  }
		  if( t1 > tmin ) tmin = t1;
		  if( t2 < tmax ) tmax = t2;
		  if( tmin > tmax ) return FALSE;
		  if( tmax < 0.0 ) return FALSE;
	  }	else
	  if( r.A.z > aabb.max.z || r.A.z < aabb.min.z ) return FALSE;

	  
	  return TRUE; 
  }




  inline BOOL aabboxraY( const aabboX& aabb, const raY& r, valuE *t ) {
	  valuE tmin, tmax, t1, t2, a;


	  tmin = -INFINITY;  tmax = INFINITY;

	  if( abs( r.q.x ) > EPSILON ) {
	      a = 1.0/r.q.x;
          t1 = ( aabb.max.x-r.A.x )*a;    
	      t2 = ( aabb.min.x-r.A.x )*a;    
		  if( t1 > t2 ) {
		      a = t1;
			  t1 = t2;
			  t2 = a;
		  }
		  if( t1 > tmin ) tmin = t1;
		  if( t2 < tmax ) tmax = t2;
		  if( tmin > tmax ) return FALSE;
		  if( tmax < 0.0 ) return FALSE;
	  }	else
	  if( r.A.x > aabb.max.x || r.A.x < aabb.min.x ) return FALSE;

	  if( abs( r.q.y ) > EPSILON ) {
          a = 1.0/r.q.y;
	      t1 = ( aabb.max.y-r.A.y )*a;    
	      t2 = ( aabb.min.y-r.A.y )*a;    
		  if( t1 > t2 ) {
		      a = t1;
			  t1 = t2;
			  t2 = a;
		  }
		  if( t1 > tmin ) tmin = t1;
		  if( t2 < tmax ) tmax = t2;
		  if( tmin > tmax ) return FALSE;
		  if( tmax < 0.0 ) return FALSE;
	  }	else
	  if( r.A.y > aabb.max.y || r.A.y < aabb.min.y ) return FALSE;

	  if( abs( r.q.z ) > EPSILON ) {
          a = 1.0/r.q.z;
	      t1 = ( aabb.max.z-r.A.z )*a;    
	      t2 = ( aabb.min.z-r.A.z )*a;    
		  if( t1 > t2 ) {
		      a = t1;
			  t1 = t2;
			  t2 = a;
		  }
		  if( t1 > tmin ) tmin = t1;
		  if( t2 < tmax ) tmax = t2;
		  if( tmin > tmax ) return FALSE;
		  if( tmax < 0.0 ) return FALSE;
	  }	else
	  if( r.A.z > aabb.max.z || r.A.z < aabb.min.z ) return FALSE;


      if( tmin >= 0.0 ) *t = tmin; else *t = tmax;

	  
	  return TRUE; 
  }




  inline long aabboxplanE( const aabboX& aabb, const planE& pl ) {
	  poinT ptmin, ptmax;

	  if( pl.n.x >= 0.0 ) {
	      ptmin.x = aabb.min.x;    
	      ptmax.x = aabb.max.x;    
	  } else {
	      ptmin.x = aabb.max.x;    
	      ptmax.x = aabb.min.x;    
	  }
	  if( pl.n.y >= 0.0 ) {
	      ptmin.y = aabb.min.y;    
	      ptmax.y = aabb.max.y;    
	  } else {
	      ptmin.y = aabb.max.y;    
	      ptmax.y = aabb.min.y;    
	  }
	  if( pl.n.z >= 0.0 ) {
	      ptmin.z = aabb.min.z;    
	      ptmax.z = aabb.max.z;    
	  } else {
	      ptmin.z = aabb.max.z;    
	      ptmax.z = aabb.min.z;    
	  }

	  if( planepoinT( pl, ptmin ) > EPSILON ) return 1;
	  if( planepoinT( pl, ptmax ) >= -EPSILON ) return 0; else return -1;
  }




  inline BOOL aabboxaabboX( const aabboX& aabb1, const aabboX& aabb2 ) {
      if( aabb1.max.x < aabb2.min.x ) return FALSE; else
      if( aabb2.max.x < aabb1.min.x ) return FALSE; else
      if( aabb1.max.y < aabb2.min.y ) return FALSE; else
      if( aabb2.max.y < aabb1.min.y ) return FALSE; else
      if( aabb1.max.z < aabb2.min.z ) return FALSE; else
      if( aabb2.max.z < aabb1.min.z ) return FALSE; else return TRUE;
  }




  inline void rendergL( const aabboX& aabb ) {
      glBegin( GL_LINE_LOOP );
          glVertex3f( aabb.min.x, aabb.min.y, aabb.min.z );
          glVertex3f( aabb.max.x, aabb.min.y, aabb.min.z );
          glVertex3f( aabb.max.x, aabb.min.y, aabb.max.z );
          glVertex3f( aabb.min.x, aabb.min.y, aabb.max.z );
      glEnd();
      glBegin( GL_LINE_LOOP );
          glVertex3f( aabb.min.x, aabb.max.y, aabb.min.z );
          glVertex3f( aabb.max.x, aabb.max.y, aabb.min.z );
          glVertex3f( aabb.max.x, aabb.max.y, aabb.max.z );
          glVertex3f( aabb.min.x, aabb.max.y, aabb.max.z );
      glEnd();
      glBegin( GL_LINES );
          glVertex3f( aabb.min.x, aabb.min.y, aabb.min.z );
          glVertex3f( aabb.min.x, aabb.max.y, aabb.min.z );
          glVertex3f( aabb.max.x, aabb.min.y, aabb.min.z );
          glVertex3f( aabb.max.x, aabb.max.y, aabb.min.z );
          glVertex3f( aabb.max.x, aabb.min.y, aabb.max.z );
          glVertex3f( aabb.max.x, aabb.max.y, aabb.max.z );
          glVertex3f( aabb.min.x, aabb.min.y, aabb.max.z );
          glVertex3f( aabb.min.x, aabb.max.y, aabb.max.z );
      glEnd();
  }








  // AABBOXARRAY
  class aabboxarraY: public arraY<aabboX> {};


  inline void aabboxintersectioN( const aabboX& aabb1, const aabboX& aabb2, aabboxarraY *aabba );
  inline void aabboxdifferencE( const aabboX& aabb1, const aabboX& aabb2, aabboxarraY *aabba );
  inline void aabboxunioN( const aabboX& aabb1, const aabboX& aabb2, aabboxarraY *aabba );






  inline void aabboxintersectioN( const aabboX& aabb1, const aabboX& aabb2, aabboxarraY *aabba ) {
      aabba->deletealL();

      if( aabboxaabboX( aabb1, aabb2 ) ) {
          aabba->inserT( -1, aabb1 );

          if( aabb2.min.x > aabba->elem[0].min.x && aabb2.min.x < aabba->elem[0].max.x ) 
              aabba->elem[0] = aabboX( poinT( aabb2.min.x, aabba->elem[0].min.y, aabba->elem[0].min.z ), aabba->elem[0].max );

          if( aabb2.max.x > aabba->elem[0].min.x && aabb2.max.x < aabba->elem[0].max.x ) 
              aabba->elem[0] = aabboX( aabba->elem[0].min, poinT( aabb2.max.x, aabba->elem[0].max.y, aabba->elem[0].max.z ) );
            
          if( aabb2.min.y > aabba->elem[0].min.y && aabb2.min.y < aabba->elem[0].max.y )
              aabba->elem[0] = aabboX( poinT( aabba->elem[0].min.x, aabb2.min.y, aabba->elem[0].min.z ), aabba->elem[0].max );

          if( aabb2.max.y > aabba->elem[0].min.y && aabb2.max.y < aabba->elem[0].max.y )
              aabba->elem[0] = aabboX( aabba->elem[0].min, poinT( aabba->elem[0].max.x, aabb2.max.y, aabba->elem[0].max.z ) );

          if( aabb2.min.z > aabba->elem[0].min.z && aabb2.min.z < aabba->elem[0].max.z )
              aabba->elem[0] = aabboX( poinT( aabba->elem[0].min.x, aabba->elem[0].min.y, aabb2.min.z ), aabba->elem[0].max );

          if( aabb2.max.z > aabba->elem[0].min.z && aabb2.max.z < aabba->elem[0].max.z )
              aabba->elem[0] = aabboX( aabba->elem[0].min, poinT( aabba->elem[0].max.x, aabba->elem[0].max.y, aabb2.max.z ) );
      }
  }




  inline void aabboxdifferencE( const aabboX& aabb1, const aabboX& aabb2, aabboxarraY *aabba ) {
      register long i;
      BOOL b;
      aabboX aabb;
      aabboxarraY aabba2;


      aabba->deletealL();
      aabba2.inserT( -1, aabb1 );

      for( i = aabba2.num-1;  i >= 0;  i-- ) {
          aabb = aabba2.elem[i];
          if( aabb2.min.x > aabb.min.x && aabb2.min.x < aabb.max.x ) {
              aabba2.deletE( i );

              aabba->inserT( -1, aabboX( aabb.min.x, aabb.min.y, aabb.min.z, aabb2.min.x, aabb.max.y, aabb.max.z ) );
              aabba2.inserT( -1, aabboX( aabb2.min.x, aabb.min.y, aabb.min.z, aabb.max.x, aabb.max.y, aabb.max.z ) );
          }
      }

      for( i = aabba2.num-1;  i >= 0;  i-- ) {
          aabb = aabba2.elem[i];
          if( aabb2.max.x > aabb.min.x && aabb2.max.x < aabb.max.x ) {
              aabba2.deletE( i );

              aabba2.inserT( -1, aabboX( aabb.min.x, aabb.min.y, aabb.min.z, aabb2.max.x, aabb.max.y, aabb.max.z ) );
              aabba->inserT( -1, aabboX( aabb2.max.x, aabb.min.y, aabb.min.z, aabb.max.x, aabb.max.y, aabb.max.z ) );
          }
      }

      for( i = aabba2.num-1;  i >= 0;  i-- ) {
          aabb = aabba2.elem[i];
          if( aabb2.min.y > aabb.min.y && aabb2.min.y < aabb.max.y ) {
              aabba2.deletE( i );

              aabba->inserT( -1, aabboX( aabb.min.x, aabb.min.y, aabb.min.z, aabb.max.x, aabb2.min.y, aabb.max.z ) );
              aabba2.inserT( -1, aabboX( aabb.min.x, aabb2.min.y, aabb.min.z, aabb.max.x, aabb.max.y, aabb.max.z ) );
          }
      }

      for( i = aabba2.num-1;  i >= 0;  i-- ) {
          aabb = aabba2.elem[i];
          if( aabb2.max.y > aabb.min.y && aabb2.max.y < aabb.max.y ) {
              aabba2.deletE( i );

              aabba2.inserT( -1, aabboX( aabb.min.x, aabb.min.y, aabb.min.z, aabb.max.x, aabb2.max.y, aabb.max.z ) );
              aabba->inserT( -1, aabboX( aabb.min.x, aabb2.max.y, aabb.min.z, aabb.max.x, aabb.max.y, aabb.max.z ) );
          }
      }

      for( i = aabba2.num-1;  i >= 0;  i-- ) {
          aabb = aabba2.elem[i];
          if( aabb2.min.z > aabb.min.z && aabb2.min.z < aabb.max.z ) {
              aabba2.deletE( i );

              aabba->inserT( -1, aabboX( aabb.min.x, aabb.min.y, aabb.min.z, aabb.max.x, aabb.max.y, aabb2.min.z ) );
              aabba2.inserT( -1, aabboX( aabb.min.x, aabb.min.y, aabb2.min.z, aabb.max.x, aabb.max.y, aabb.max.z ) );
          }
      }

      for( i = aabba2.num-1;  i >= 0;  i-- ) {
          aabb = aabba2.elem[i];
          if( aabb2.max.z > aabb.min.z && aabb2.max.z < aabb.max.z ) {
              aabba2.deletE( i );

              aabba2.inserT( -1, aabboX( aabb.min.x, aabb.min.y, aabb.min.z, aabb.max.x, aabb.max.y, aabb2.max.z ) );
              aabba->inserT( -1, aabboX( aabb.min.x, aabb.min.y, aabb2.max.z, aabb.max.x, aabb.max.y, aabb.max.z ) );
          }
      }


      for( i = 0;  i < aabba2.num;  i++ ) {
          if( aabba2.elem[i].max.x <= aabb2.min.x ) b = FALSE; else
          if( aabb2.max.x <= aabba2.elem[i].min.x ) b = FALSE; else
          if( aabba2.elem[i].max.y <= aabb2.min.y ) b = FALSE; else
          if( aabb2.max.y <= aabba2.elem[i].min.y ) b = FALSE; else
          if( aabba2.elem[i].max.z <= aabb2.min.z ) b = FALSE; else
          if( aabb2.max.z <= aabba2.elem[i].min.z ) b = FALSE; else b = TRUE;

          if( !b ) aabba->inserT( -1, aabba2.elem[i] );
      }
  }




  inline void aabboxunioN( const aabboX& aabb1, const aabboX& aabb2, aabboxarraY *aabba ) {
      aabboxdifferencE( aabb1, aabb2, aabba );
      if( aabba->num > 3 ) {
          aabboxdifferencE( aabb2, aabb1, aabba );
          aabba->inserT( -1, aabb1 );
      } else aabba->inserT( -1, aabb2 );
  }
