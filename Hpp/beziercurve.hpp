
  // CUBICBEZIERCURVE
  class cubicbeziercurvE {
      public:
  		  poinT P[4];


          cubicbeziercurvE( void ) { reseT(); };
          ~cubicbeziercurvE( void ) { deletealL(); };

          void reseT( void );
		  void deletealL( void );
		  void copY( cubicbeziercurvE *cbc );

          valuE B( DWORD i, valuE t );
		  valuE dB( DWORD i, valuE t );
		  valuE ddB( DWORD i, valuE t );
		  valuE dddB( DWORD i, valuE t );
		  poinT Q( valuE u, poinT *A = NULL );
		  poinT dQ( valuE u, poinT *dA = NULL );
		  poinT ddQ( valuE u, poinT *ddA = NULL );
		  poinT dddQ( valuE u, poinT *dddA = NULL );
		  poinT decasteljaU( valuE u, poinT *A = NULL );
          void spliT( valuE u, cubicbeziercurvE *cbc_left, cubicbeziercurvE *cbc_right );
          vectoR centraldifferencE( valuE a, vectoR ha, vectoR ddha, valuE b, vectoR hb, vectoR ddhb, vectoR *hmid, vectoR *ddhmid );
		  void interpolatE( const poinT& pt0, const poinT& pt1, const poinT& pt2, const poinT& pt3 ); 
  };                   








  inline void cubicbeziercurvE::reseT( void ) {
      P[0] = P[1] = P[2] = P[3] = poinT();
  }

  


  inline void cubicbeziercurvE::deletealL( void ) {

	  reseT();
  }




  inline void cubicbeziercurvE::copY( cubicbeziercurvE *cbc ) {
      cbc->deletealL();

      cbc->P[0] = P[0];  
      cbc->P[1] = P[1];  
      cbc->P[2] = P[2];  
      cbc->P[3] = P[3];
  }




  inline valuE cubicbeziercurvE::B( DWORD i, valuE t ) {
      if( i == 0 ) {
          return -t*t*t+3.0*t*t-3.0*t+1.0;
      } else 
      if( i == 1 ) {
          return 3.0*t*t*t-6.0*t*t+3.0*t;
      } else 
      if( i == 2 ) {
          return -3.0*t*t*t+3.0*t*t;
      } else 
      if( i == 3 ) {
          return t*t*t;
      } 
  }




  inline valuE cubicbeziercurvE::dB( DWORD i, valuE t ) {
      if( i == 0 ) {
          return -3.0*t*t+6.0*t-3.0;
      } else 
      if( i == 1 ) {
          return 9.0*t*t-12.0*t+3.0;
      } else 
      if( i == 2 ) {
          return -9.0*t*t+6.0*t;
      } else 
      if( i == 3 ) {
          return 3.0*t*t;
      } 
  }




  inline valuE cubicbeziercurvE::ddB( DWORD i, valuE t ) {
      if( i == 0 ) {
          return -6.0*t+6.0;
      } else 
      if( i == 1 ) {
          return 18.0*t-12.0;
      } else 
      if( i == 2 ) {
          return -18.0*t+6.0;
      } else 
      if( i == 3 ) {
          return 6.0*t;
      } 
  }




  inline valuE cubicbeziercurvE::dddB( DWORD i, valuE t ) {
      if( i == 0 ) {
          return -6.0;
      } else 
      if( i == 1 ) {
          return 18.0;
      } else 
      if( i == 2 ) {
          return -18.0;
      } else 
      if( i == 3 ) {
          return 6.0;
      } 
  }




  inline poinT cubicbeziercurvE::Q( valuE u, poinT *A ) {
      if( A ) return *A = P[0]*B( 0, u )+P[1]*B( 1, u )+P[2]*B( 2, u )+P[3]*B( 3, u ); else
              return P[0]*B( 0, u )+P[1]*B( 1, u )+P[2]*B( 2, u )+P[3]*B( 3, u ); 
  }




  inline poinT cubicbeziercurvE::dQ( valuE u, poinT *dA ) {
      if( dA ) return *dA = P[0]*dB( 0, u )+P[1]*dB( 1, u )+P[2]*dB( 2, u )+P[3]*dB( 3, u ); else
               return P[0]*dB( 0, u )+P[1]*dB( 1, u )+P[2]*dB( 2, u )+P[3]*dB( 3, u ); 
  }




  inline poinT cubicbeziercurvE::ddQ( valuE u, poinT *ddA ) {
      if( ddA ) return *ddA = P[0]*ddB( 0, u )+P[1]*ddB( 1, u )+P[2]*ddB( 2, u )+P[3]*ddB( 3, u ); else
                return P[0]*ddB( 0, u )+P[1]*ddB( 1, u )+P[2]*ddB( 2, u )+P[3]*ddB( 3, u ); 
  }




  inline poinT cubicbeziercurvE::dddQ( valuE u, poinT *dddA ) {
      if( dddA ) return *dddA = P[0]*dddB( 0, u )+P[1]*dddB( 1, u )+P[2]*dddB( 2, u )+P[3]*dddB( 3, u ); else
                 return P[0]*dddB( 0, u )+P[1]*dddB( 1, u )+P[2]*dddB( 2, u )+P[3]*dddB( 3, u );
  }




  inline poinT cubicbeziercurvE::decasteljaU( valuE u, poinT *A ) {
      poinT W, left[4], right[4];

      left[0] = P[0];
      left[1] = P[0]+u*( P[1]-P[0] );
      W = P[1]+u*( P[2]-P[1] );
      left[2] = left[1]+u*( W-left[1] ); 
      right[3] = P[3];
      right[2] = P[2]+u*( P[3]-P[2] );
      right[1] = W+u*( right[2]-W );

      if( A ) return *A = left[3] = right[0] = left[2]+u*( right[1]-left[2] ); else
              return left[3] = right[0] = left[2]+u*( right[1]-left[2] ); 
  }




  inline void cubicbeziercurvE::spliT( valuE u, cubicbeziercurvE *cbc_left, cubicbeziercurvE *cbc_right ) {
      poinT W;


      cbc_left->deletealL();
      cbc_right->deletealL();

      cbc_left->P[0] = P[0];
      cbc_left->P[1] = P[0]+u*( P[1]-P[0] );
      W = P[1]+u*( P[2]-P[1] );
      cbc_left->P[2] = cbc_left->P[1]+u*( W-cbc_left->P[1] ); 
      cbc_right->P[3] = P[3];
      cbc_right->P[2] = P[2]+u*( P[3]-P[2] );
      cbc_right->P[1] = W+u*( cbc_right->P[2]-W );
      cbc_left->P[3] = cbc_right->P[0] = cbc_left->P[2]+u*( cbc_right->P[1]-cbc_left->P[2] );
  }




  inline vectoR cubicbeziercurvE::centraldifferencE( valuE a, vectoR ha, vectoR ddha, valuE b, vectoR hb, vectoR ddhb, vectoR *hmid, vectoR *ddhmid ) {
      vectoR secondterm;

      *ddhmid = ( ddha+ddhb )*0.5;
      secondterm = -pow( ( b-a )*0.5, 2.0 )**ddhmid*0.25;
      *hmid = ( ha+hb )*0.5+secondterm;

      return secondterm;
  }




  inline void cubicbeziercurvE::interpolatE( const poinT& pt0, const poinT& pt1, const poinT& pt2, const poinT& pt3 ) {
	  poinT A, B;

	  deletealL();

	  A = 4.5*pt1-4.0/3.0*pt0-2.0/3.0*pt3;
	  B = 4.5*pt2-2.0/3.0*pt0-4.0/3.0*pt3;
	  P[0] = pt0;
	  P[1] = poinT( 2.0*A.x-B.x, 2.0*A.y-B.y, 2.0*A.z-B.z )/3.0;
	  P[2] = poinT( A.x-2.0*P[1].x, A.y-2.0*P[1].y, A.z-2.0*P[1].z );
	  P[3] = pt3;
  }








  // CUBICBEZIERCURVEARRAY
  class cubicbeziercurvearraY: public arraY_<cubicbeziercurvE> {};


  // LPCUBICBEZIERCURVE
  typedef cubicbeziercurvE* lpcubicbeziercurvE;


  // LPCUBICBEZIERCURVEARRAY
  class lpcubicbeziercurvearraY: public arraY__<lpcubicbeziercurvE> {};
















  // RATIONALCUBICBEZIERCURVE
  class rationalcubicbeziercurvE {
      public:
  		  poinT P[4];
          valuE w[4];


          rationalcubicbeziercurvE( void ) { reseT(); };
          ~rationalcubicbeziercurvE( void ) { deletealL(); };

          void reseT( void );
		  void deletealL( void );
		  void copY( rationalcubicbeziercurvE *rcbc );

          valuE B( DWORD i, valuE t );
		  valuE dB( DWORD i, valuE t );
		  valuE ddB( DWORD i, valuE t );
		  poinT Q( valuE u, poinT *A = NULL );
		  poinT dQ( valuE u, poinT *dA = NULL );
		  poinT ddQ( valuE u, poinT *ddA = NULL );
		  poinT decasteljaU( valuE u, poinT *A = NULL );
          void spliT( valuE u, rationalcubicbeziercurvE *rcbc_left, rationalcubicbeziercurvE *rcbc_right );
  };                   






  inline void rationalcubicbeziercurvE::reseT( void ) {
      P[0] = P[1] = P[2] = P[3] = poinT();
      w[0] = w[1] = w[2] = w[3] = 0.0;
  }

  


  inline void rationalcubicbeziercurvE::deletealL( void ) {
	  reseT();
  }




  inline void rationalcubicbeziercurvE::copY( rationalcubicbeziercurvE *rcbc ) {
      rcbc->deletealL();

      rcbc->P[0] = P[0];  
      rcbc->P[1] = P[1];  
      rcbc->P[2] = P[2];  
      rcbc->P[3] = P[3];
      rcbc->w[0] = w[0];  
      rcbc->w[1] = w[1];  
      rcbc->w[2] = w[2];  
      rcbc->w[3] = w[3];
  }




  inline valuE rationalcubicbeziercurvE::B( DWORD i, valuE t ) {
      if( i == 0 ) {
          return -t*t*t+3.0*t*t-3.0*t+1.0;
      } else 
      if( i == 1 ) {
          return 3.0*t*t*t-6.0*t*t+3.0*t;
      } else 
      if( i == 2 ) {
          return -3.0*t*t*t+3.0*t*t;
      } else 
      if( i == 3 ) {
          return t*t*t;
      } 
  }




  inline valuE rationalcubicbeziercurvE::dB( DWORD i, valuE t ) {
      if( i == 0 ) {
          return -3.0*t*t+6.0*t-3.0;
      } else 
      if( i == 1 ) {
          return 9.0*t*t-12.0*t+3.0;
      } else 
      if( i == 2 ) {
          return -9.0*t*t+6.0*t;
      } else 
      if( i == 3 ) {
          return 3.0*t*t;
      } 
  }




  inline valuE rationalcubicbeziercurvE::ddB( DWORD i, valuE t ) {
      if( i == 0 ) {
          return -6.0*t+6.0;
      } else 
      if( i == 1 ) {
          return 18.0*t-12.0;
      } else 
      if( i == 2 ) {
          return -18.0*t+6.0;
      } else 
      if( i == 3 ) {
          return 6.0*t;
      } 
  }




  inline poinT rationalcubicbeziercurvE::Q( valuE u, poinT *A ) {
      valuE a, b;
      poinT Q;

      b = 0.0;
      Q = poinT( 0.0, 0.0, 0.0 );
      for( register DWORD i = 0;  i < 4;  i++ ) {
  	      a = w[i]*B( i, u );
		  Q+=P[i]*a;
          b+=a;
      }

      if( A ) return *A = Q/b; else return Q/b;
  }




  inline poinT rationalcubicbeziercurvE::dQ( valuE u, poinT *dA ) {
      valuE a, b, c, d;
      poinT Q, R;

      c = d = 0.0;
      Q = R = poinT( 0.0, 0.0, 0.0 );
      for( register DWORD i = 0;  i < 4;  i++ ) {
  	      a = w[i]*B( i, u );
  	      b = w[i]*dB( i, u );
		  Q+=P[i]*a;
		  R+=P[i]*b;
          c+=a;
          d+=b;
      }

      if( dA ) return *dA = poinT( R.x/c-Q.x*( d/( c*c ) ), R.y/c-Q.y*( d/( c*c ) ), R.z/c-Q.z*( d/( c*c ) ) ); else 
               return poinT( R.x/c-Q.x*( d/( c*c ) ), R.y/c-Q.y*( d/( c*c ) ), R.z/c-Q.z*( d/( c*c ) ) );
  }




  inline poinT rationalcubicbeziercurvE::ddQ( valuE u, poinT *ddA ) {
      valuE a, b, c, d, e, f;
      poinT Q, R, S;

      d = e = f = 0.0;
      Q = R = S = poinT( 0.0, 0.0, 0.0 );
      for( register DWORD i = 0;  i < 4;  i++ ) {
  	      a = w[i]*B( i, u );
  	      b = w[i]*dB( i, u );
  	      c = w[i]*ddB( i, u );
		  Q+=P[i]*a;
		  R+=P[i]*b;
		  S+=P[i]*c;
          d+=a;
          e+=b;
          f+=c;
      }

	  if( ddA ) return *ddA = S/d-2.0*R*( e/( d*d ) )-Q*( f/( d*d ) )+2.0*Q*( ( e*e )/( d*d*d ) ); else 
                return S/d-2.0*R*( e/( d*d ) )-Q*( f/( d*d ) )+2.0*Q*( ( e*e )/( d*d*d ) );
  }




  inline poinT rationalcubicbeziercurvE::decasteljaU( valuE u, poinT *A ) {
      valuE val, left_w[4], right_w[4];
      poinT W, PP[4], left_P[4], right_P[4];


      PP[0] = P[0]*w[0];
      PP[1] = P[1]*w[1];
      PP[2] = P[2]*w[2];
      PP[3] = P[3]*w[3];

      left_P[0] = PP[0];
      left_P[1] = PP[0]+u*( PP[1]-PP[0] );
      W = PP[1]+u*( PP[2]-PP[1] );
      left_P[2] = left_P[1]+u*( W-left_P[1] ); 
      right_P[3] = PP[3];
      right_P[2] = PP[2]+u*( PP[3]-PP[2] );
      right_P[1] = W+u*( right_P[2]-W );
      left_P[3] = right_P[0] = left_P[2]+u*( right_P[1]-left_P[2] );
      left_w[0] = w[0];
      left_w[1] = w[0]+u*( w[1]-w[0] );
      val = w[1]+u*( w[2]-w[1] );
      left_w[2] = left_w[1]+u*( val-left_w[1] ); 
      right_w[3] = w[3];
      right_w[2] = w[2]+u*( w[3]-w[2] );
      right_w[1] = val+u*( right_w[2]-val );
      left_w[3] = right_w[0] = left_w[2]+u*( right_w[1]-left_w[2] );

      if( A ) return *A = left_P[3]/left_w[3]; else return left_P[3]/left_w[3];
  }




  inline void rationalcubicbeziercurvE::spliT( valuE u, rationalcubicbeziercurvE *rcbc_left, rationalcubicbeziercurvE *rcbc_right ) {
      valuE val;
      poinT W, PP[4];


      rcbc_left->deletealL();
      rcbc_right->deletealL();

      PP[0] = P[0]*w[0];
      PP[1] = P[1]*w[1];
      PP[2] = P[2]*w[2];
      PP[3] = P[3]*w[3];

      rcbc_left->P[0] = PP[0];
      rcbc_left->P[1] = PP[0]+u*( PP[1]-PP[0] );
      W = PP[1]+u*( PP[2]-PP[1] );
      rcbc_left->P[2] = rcbc_left->P[1]+u*( W-rcbc_left->P[1] ); 
      rcbc_right->P[3] = PP[3];
      rcbc_right->P[2] = PP[2]+u*( PP[3]-PP[2] );
      rcbc_right->P[1] = W+u*( rcbc_right->P[2]-W );
      rcbc_left->P[3] = rcbc_right->P[0] = rcbc_left->P[2]+u*( rcbc_right->P[1]-rcbc_left->P[2] );
      rcbc_left->w[0] = w[0];
      rcbc_left->w[1] = w[0]+u*( w[1]-w[0] );
      val = w[1]+u*( w[2]-w[1] );
      rcbc_left->w[2] = rcbc_left->w[1]+u*( val-rcbc_left->w[1] ); 
      rcbc_right->w[3] = w[3];
      rcbc_right->w[2] = w[2]+u*( w[3]-w[2] );
      rcbc_right->w[1] = val+u*( rcbc_right->w[2]-val );
      rcbc_left->w[3] = rcbc_right->w[0] = rcbc_left->w[2]+u*( rcbc_right->w[1]-rcbc_left->w[2] );

      rcbc_left->P[0]/=rcbc_left->w[0];
      rcbc_left->P[1]/=rcbc_left->w[1];
      rcbc_left->P[2]/=rcbc_left->w[2];
      rcbc_left->P[3]/=rcbc_left->w[3];
      rcbc_right->P[0]/=rcbc_right->w[0];
      rcbc_right->P[1]/=rcbc_right->w[1];
      rcbc_right->P[2]/=rcbc_right->w[2];
      rcbc_right->P[3]/=rcbc_right->w[3];
  }








  // RATIONALCUBICBEZIERCURVEARRAY
  class rationalcubicbeziercurvearraY: public arraY_<rationalcubicbeziercurvE> {};


  // LPRATIONALCUBICBEZIERCURVE
  typedef rationalcubicbeziercurvE* lprationalcubicbeziercurvE;


  // LPRATIONALCUBICBEZIERCURVEARRAY
  class lprationalcubicbeziercurvearraY: public arraY__<lprationalcubicbeziercurvE> {};
















  // BEZIERCURVE
  class beziercurvE {
      public:
          DWORD n;
  		  pointarraY P;


          beziercurvE( void ) { reseT(); };
          ~beziercurvE( void ) { deletealL(); };

          void reseT( void );
		  void deletealL( void );
		  void copY( beziercurvE *bc );

		  poinT decasteljaU( valuE u, poinT *A = NULL );
          void spliT( valuE u, beziercurvE *bc_left, beziercurvE *bc_right );
          void differentiatecurvE( beziercurvE *dbc );
  };                   





  void beziercurvelinE_( beziercurvE *bc, valuE a, valuE b, valuE c, pointarraY *pta );
  inline BOOL beziercurvelinE( beziercurvE *bc, const poinT& A, const poinT& B, pointarraY *pta );








  void beziercurvE::reseT( void ) {
      n = 0;
      P.reseT();
  }

  


  void beziercurvE::deletealL( void ) {
      P.deletealL();

	  reseT();
  }




  inline void beziercurvE::copY( beziercurvE *bc ) {
      bc->deletealL();

      bc->n = n;
      P.copY( &bc->P );
  }




  poinT beziercurvE::decasteljaU( valuE u, poinT *A ) {
	  register long i, j;
      valuE val = 1.0-u;
	  pointarraY pta;


	  pta.inserT( -1, poinT(), n*n );

	  for( i = 0;  i < n;  i++ ) pta.elem[i+0*n] = P.elem[i];

	  for( j = 1;  j < n;  j++ )
		  for( i = j;  i < n;  i++ ) 
			  pta.elem[i+j*n] = u*pta.elem[i-1+( j-1 )*n]+val*pta.elem[i+( j-1 )*n];

      if( A ) return *A = pta.elem[n-1+( n-1 )*n]; else return pta.elem[n-1+( n-1 )*n];
  }




  void beziercurvE::spliT( valuE u, beziercurvE *bc_left, beziercurvE *bc_right ) {
	  register long i, j;
      valuE val = 1.0-u;
	  pointarraY pta;


	  pta.inserT( -1, poinT(), n*n );

	  for( i = 0;  i < n;  i++ ) pta.elem[i+0*n] = P.elem[i];

	  for( j = 1;  j < n;  j++ )
		  for( i = j;  i < n;  i++ ) 
			  pta.elem[i+j*n] = u*pta.elem[i-1+( j-1 )*n]+val*pta.elem[i+( j-1 )*n];

	  if( bc_left != NULL ) {
	      bc_left->deletealL();	
		  bc_left->n = n;

	      bc_left->P.inserT( -1, poinT(), bc_left->n );
		  for( i = 0;  i < n;  i++ ) bc_left->P.elem[i] = pta.elem[i+i*n];
	  }
	  if( bc_right != NULL ) {
          bc_right->deletealL();
	      bc_right->n = n;

	      bc_right->P.inserT( -1, poinT(), bc_right->n );
		  for( i = 0;  i < n;  i++ ) bc_right->P.elem[i] = pta.elem[n-1+i*n];
	  }
  }




  void beziercurvE::differentiatecurvE( beziercurvE *dbc ) {
      register long i;
      vectoR v;

      dbc->deletealL();

      dbc->P.inserT( -1, poinT(), n-1 );
      for( i = 0;  i < n-1;  i++ ) {
          v = P.elem[i+1]-P.elem[i];
          dbc->P.elem[i] = ( n-1 )*poinT( v.x, v.y, v.z );
      }
      dbc->n = n-1;
  }




  void beziercurvelinE_( beziercurvE *bc, valuE a, valuE b, valuE c, pointarraY *pta ) {
	  BOOL ypos, yneg;
	  register long i;
	  valuE val, x, u0, u1;
	  pointarraY d, ch;
	  beziercurvE bc_, bc_left, bc_right;


	  d.inserT( -1, poinT(), bc->n );
	  val = 1.0/( bc->n-1.0 );
	  ypos = yneg = FALSE;
	  for( i = 0;  i < bc->n;  i++ ) {
		  d.elem[i].x = i*val;
		  d.elem[i].y = a*bc->P.elem[i].x+b*bc->P.elem[i].y+c;

		  if( d.elem[i].y >= 0.0 ) ypos = TRUE;
		  if( d.elem[i].y <= 0.0 ) yneg = TRUE;
	  }
	  if( !( ypos && yneg ) ) return ; // neexistuje priesecnik s x-osou

	  // najdeme konvexnu obalku
	  quickhull2D( &d, &ch );

	  // priesecniky s x-osou
	  u0 = INFINITY;  u1 = -INFINITY;
	  for( i = 0;  i < ch.num;  i+=2 ) 
		  if( ch.elem[i].y*ch.elem[i+1].y <= 0.0 ) {
			  if( ch.elem[i].y == 0.0 && ch.elem[i+1].y == 0.0 ) {
				  x = ch.elem[i].x;
				  if( x < u0 ) u0 = x;
				  if( x > u1 ) u1 = x;
				  x = ch.elem[i+1].x;
				  if( x < u0 ) u0 = x;
				  if( x > u1 ) u1 = x;
			  } else {
			      val = -ch.elem[i].y/( ch.elem[i+1].y-ch.elem[i].y );    		      	
				  x = ch.elem[i].x+val*( ch.elem[i+1].x-ch.elem[i].x );
				  if( x < u0 ) u0 = x;
				  if( x > u1 ) u1 = x;
			  }
		  }

	  if( u1-u0 < EPSILON )	{ // ak je krivka dostatocne mala
		  pta->inserT( -1, bc->decasteljaU( ( u0+u1 )*0.5 ) );
	  } else {
		  bc->spliT( u0, NULL, &bc_ );
		  bc_.spliT( ( u1-u0 )/( 1.0-u0 ), &bc_, NULL );

		  if( u1-u0 > 0.8 ) { // pravdepodobne existuje viac rieseni
			  bc_.spliT( 0.5, &bc_left, &bc_right );	
			  beziercurvelinE_( &bc_left, a, b, c, pta );	      	
			  beziercurvelinE_( &bc_right, a, b, c, pta );	      	
		  } else {
			  beziercurvelinE_( &bc_, a, b, c, pta );	      	
		  }
	  }
  }




  inline BOOL beziercurvelinE( beziercurvE *bc, const poinT& A, const poinT& B, pointarraY *pta ) {
	  valuE a, b, c;

	  pta->deletealL();

	  planE_( A, B, &a, &b, &c );

	  beziercurvelinE_( bc, a, b, c, pta );

	  if( pta->num > 0 ) return TRUE; else return FALSE;
  }








  // BEZIERCURVEARRAY
  class beziercurvearraY: public arraY_<beziercurvE> {};


  // LPBEZIERCURVE
  typedef beziercurvE* lpbeziercurvE;


  // LPBEZIERCURVEARRAY
  class lpbeziercurvearraY: public arraY__<lpbeziercurvE> {};
