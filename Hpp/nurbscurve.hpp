
  // NURBSCURVE
  class nurbscurvE {
      public:
          DWORD n, p;
          valuearraY w, U; 
          pointarraY P;


          nurbscurvE( void ) { reseT(); };
          ~nurbscurvE( void ) { deletealL(); };

          void reseT( void );
		  void deletealL( void );
		  void copY( nurbscurvE *nc );

          valuE N( DWORD i, DWORD p, valuE u );
          valuE dN( DWORD i, DWORD p, valuE u );
          valuE ddN( DWORD i, DWORD p, valuE u );
          poinT Q( valuE u, poinT *A = NULL );
          poinT dQ( valuE u, poinT *dA = NULL );
          poinT ddQ( valuE u, poinT *ddA = NULL );
          poinT debooR( valuE u, poinT *A = NULL );
          void insertknoT( valuE u );
          void spliT( valuE u, nurbscurvE *nc_left, nurbscurvE *nc_right );
		  void interpolatE( pointarraY *pta ); 
          BOOL nurbstobezieR( rationalcubicbeziercurvearraY *rcbca );
  };                   


  void circlE( const poinT& center, valuE radius, nurbscurvE *nc );
  void circlE2( const poinT& center, valuE radius, nurbscurvE *nc );






  void nurbscurvE::reseT( void ) {
      n = p = 0;
      w.reseT();
      U.reseT();
      P.reseT();
  }

  


  void nurbscurvE::deletealL( void ) {
      w.deletealL();
      U.deletealL();
      P.deletealL();

	  reseT();
  }




  void nurbscurvE::copY( nurbscurvE *nc ) {
      nc->deletealL();

      nc->n = n;
      nc->p = p;
      w.copY( &nc->w );
      U.copY( &nc->U );
      P.copY( &nc->P );
  }




  valuE nurbscurvE::N( DWORD i, DWORD p, valuE u ) {
	  if( p > 1 ) {
          return diV( ( u-U.elem[i] )*N( i, p-1, u ), U.elem[i+p]-U.elem[i], 0.0 )+
                 diV( ( U.elem[i+p+1]-u )*N( i+1, p-1, u ), U.elem[i+p+1]-U.elem[i+1], 0.0 );
	  } else {
		  if( p == 1 ) {
			  valuE sum = 0.0;

		      if( u >= U.elem[i] && u < U.elem[i+1] ) sum+=diV( u-U.elem[i], U.elem[i+p]-U.elem[i], 0.0 );
			  if( u >= U.elem[i+1] && u < U.elem[i+2] ) sum+=diV( U.elem[i+p+1]-u, U.elem[i+p+1]-U.elem[i+1], 0.0 );

			  return sum;
		  } else { // p = 0
              if( u >= U.elem[i] && u < U.elem[i+1] ) return 1.0; else return 0.0;  
		  }
	  }
  }




  valuE nurbscurvE::dN( DWORD i, DWORD p, valuE u ) {
      if( p > 1 ) {
          return diV( N( i, p-1, u )+( u-U.elem[i] )*dN( i, p-1, u ), U.elem[i+p]-U.elem[i], 0.0 )+
                 diV( ( U.elem[i+p+1]-u )*dN( i+1, p-1, u )-N( i+1, p-1, u ), U.elem[i+p+1]-U.elem[i+1], 0.0 );
      } else {
          if( p == 1 ) {
			  valuE sum = 0.0;

		      if( u >= U.elem[i] && u < U.elem[i+1] ) sum+=diV( 1.0, U.elem[i+p]-U.elem[i], 0.0 );
			  if( u >= U.elem[i+1] && u < U.elem[i+2] ) sum+=diV( -1.0, U.elem[i+p+1]-U.elem[i+1], 0.0 );

			  return sum;
          } else { // p = 0
              return 0.0;
          }
      }
  }




  valuE nurbscurvE::ddN( DWORD i, DWORD p, valuE u ) {
      if( p > 2 ) {
          return diV( 2.0*dN( i, p-1, u )+( u-U.elem[i] )*ddN( i, p-1, u ), U.elem[i+p]-U.elem[i], 0.0 )+
                 diV( ( U.elem[i+p+1]-u )*ddN( i+1, p-1, u )-2.0*dN( i+1, p-1, u ), U.elem[i+p+1]-U.elem[i+1], 0.0 );
      } else {
          if( p == 2 ) {
              return diV( 2.0*dN( i, p-1, u ), U.elem[i+p]-U.elem[i], 0.0 )+
                     diV( -2.0*dN( i+1, p-1, u ), U.elem[i+p+1]-U.elem[i+1], 0.0 );
          } else { // p == 0 || p == 1
              return 0.0;
          }
      }
  }




  poinT nurbscurvE::Q( valuE u, poinT *A ) {
	  if( n > p ) {
	      valuE a, b;
          poinT Q;

	      u = clamP( u, U.elem[p]+EPSILON, U.elem[n]-EPSILON );

          b = 0.0;
		  Q = poinT( 0.0, 0.0, 0.0 );
		  for( register DWORD i = 0;  i < n;  i++ ) 
			  if( u >= U.elem[i] && u < U.elem[i+p+1] ) {
			      a = w.elem[i]*N( i, p, u );
				  Q+=P.elem[i]*a;
	              b+=a;
	          }

		  if( A ) return *A = Q/b; else return Q/b;
      }
  }




  poinT nurbscurvE::dQ( valuE u, poinT *dA ) {
/*	  if( n > p ) {
	      valuE a, b, c, d;
          poinT Q, R;

          c = d = 0.0;
		  Q = R = poinT( 0.0, 0.0, 0.0 );
		  for( register DWORD i = 0;  i < n;  i++ ) 
			  if( u >= U.elem[i] && u < U.elem[i+p+1] ) {
			      a = w.elem[i]*N( i, p, u );
                  b = w.elem[i]*dN( i, p, u );
				  Q+=P.elem[i]*a;
				  R+=P.elem[i]*b;
	              c+=a;
	              d+=b;
	          }

		  if( dA ) return *dA = poinT( R.x/c-Q.x*( d/( c*c ) ), R.y/c-Q.y*( d/( c*c ) ), R.z/c-Q.z*( d/( c*c ) ) ); else 
                   return poinT( R.x/c-Q.x*( d/( c*c ) ), R.y/c-Q.y*( d/( c*c ) ), R.z/c-Q.z*( d/( c*c ) ) );
      }*/

	  if( n > p ) {
	      valuE a, b;
          poinT dQ;

          b = 0.0;
		  dQ = poinT( 0.0, 0.0, 0.0 );
		  for( register DWORD i = 0;  i < n;  i++ ) 
			  if( u >= U.elem[i] && u < U.elem[i+p+1] ) {
			      a = w.elem[i]*dN( i, p, u );
				  dQ+=P.elem[i]*a;
	              b+=a;
	          }

		  if( dA ) return *dA = dQ/b; else return dQ/b;
      }
  }




  poinT nurbscurvE::ddQ( valuE u, poinT *ddA ) {
	  if( n > p ) {
	      valuE a, b, c, d, e, f;
          poinT Q, R, S;

          d = e = f = 0.0;
		  Q = R = S = poinT( 0.0, 0.0, 0.0 );
		  for( register DWORD i = 0;  i < n;  i++ ) 
			  if( u >= U.elem[i] && u < U.elem[i+p+1] ) {
			      a = w.elem[i]*N( i, p, u );
                  b = w.elem[i]*dN( i, p, u );
                  c = w.elem[i]*ddN( i, p, u );
				  Q+=P.elem[i]*a;
				  R+=P.elem[i]*b;
				  S+=P.elem[i]*c;
	              d+=a;
	              e+=b;
	              f+=c;
	          }

          if( ddA ) return *ddA = S/d-2.0*R*( e/( d*d ) )-Q*( f/( d*d ) )+2.0*Q*( ( e*e )/( d*d*d ) ); else 
                    return S/d-2.0*R*( e/( d*d ) )-Q*( f/( d*d ) )+2.0*Q*( ( e*e )/( d*d*d ) );
      }
  }




  poinT nurbscurvE::debooR( valuE u, poinT *A ) {
	  if( n > p ) {
    	  register long i, j, k;
	      pointarraY P_;
    	  valuearraY w_, alpha;

			  
	      u = clamP( u, U.elem[p]+EPSILON, U.elem[n]-EPSILON );

    	  P_.inserT( -1, poinT(), n*( p+1 ) );
	      w_.inserT( -1, 0.0, n*( p+1 ) );
    	  alpha.inserT( -1, 0.0, n*( p+1 ) );

    	  for( i = 0;  i < n;  i++ ) {
	    	  P_.elem[i+0*n] = P.elem[i];
		      w_.elem[i+0*n] = w.elem[i];
    	  }

    	  for( i = p;  i < n;  i++ )
	    	  if( u >= U.elem[i] && u <= U.elem[i+1] ) {
		    	  k = i;
    			  i = n;
	    	  }
				 
    	  for( j = 1;  j <= p;  j++ ) 
	    	  for( i = k-p+j;  i <= k;  i++ ) {
		    	  alpha.elem[i+j*n] = diV( u-U.elem[i], U.elem[i+p-j+1]-U.elem[i], 0.0 );
			      w_.elem[i+j*n] = ( 1.0-alpha.elem[i+j*n] )*w_.elem[i-1+( j-1 )*n] + alpha.elem[i+j*n]*w_.elem[i+( j-1 )*n];
    			  P_.elem[i+j*n] = ( ( 1.0-alpha.elem[i+j*n] )*w_.elem[i-1+( j-1 )*n]*P_.elem[i-1+( j-1 )*n] + alpha.elem[i+j*n]*w_.elem[i+( j-1 )*n]*P_.elem[i+( j-1 )*n] )/w_.elem[i+j*n];
	    	  }

          if( A ) return *A = P_.elem[k+p*n]; else return P_.elem[k+p*n];
      }
  }




  void nurbscurvE::insertknoT( valuE u ) {
      register long i, k;
      valuE a, b, oldPw, hPw;
      poinT oldP, hP;


	  u = clamP( u, U.elem[p]+EPSILON, U.elem[n]-EPSILON );

	  for( i = p;  i < n;  i++ )
		  if( u >= U.elem[i] && u <= U.elem[i+1] ) {
			  k = i;
			  i = n;
		  }

      P.inserT( k, P.elem[k] );  w.inserT( k, w.elem[k] );
      oldP = P.elem[k-p];  oldPw = w.elem[k-p];
      for( i = k-p+1;  i <= k;  i++ ) {
          hP = P.elem[i];  hPw = w.elem[i];

          a = diV( u-U.elem[i], U.elem[i+p]-U.elem[i], 0.0 );
          b = oldPw*( 1.0-a )+w.elem[i]*a;
		  P.elem[i] = ( oldP*( 1.0-a )*oldPw+P.elem[i]*a*w.elem[i] )/b;
          w.elem[i] = b;                               

          oldP = hP;  oldPw = hPw;
      }

      U.inserT( k+1, u );
	  n = P.num;
  }




  void nurbscurvE::spliT( valuE u, nurbscurvE *nc_left, nurbscurvE *nc_right ) {
      register long i, k;
      DWORD dw;
      valuE val = 1.0-u;
      nurbscurvE nc;             


	  u = clamP( u, U.elem[p]+EPSILON, U.elem[n]-EPSILON );
      
      copY( &nc );
      dw = 0;
      for( i = 0;  i < U.num;  i++ ) if( u == U.elem[i] ) dw++; 
      for( i = dw;  i <= p;  i++ ) nc.insertknoT( u );

	  for( i = p;  i < n;  i++ )
		  if( u >= U.elem[i] && u <= U.elem[i+1] ) {
			  k = i;
			  i = n;
		  }
  
      nc_left->deletealL();  nc_right->deletealL();
      nc_left->p = nc_right->p = nc.p;

	  nc_left->n = k+1;
      nc_left->P.inserT( -1, poinT(), nc_left->n );
      nc_left->w.inserT( -1, 0.0, nc_left->n );
      for( i = 0;  i <= k;  i++ ) {
		  nc_left->P.elem[i] = nc.P.elem[i];
		  nc_left->w.elem[i] = nc.w.elem[i];
	  }
      nc_left->U.inserT( -1, 0.0, k+nc.p+1 );
      for( i = 0;  i < k+nc.p+1;  i++ ) nc_left->U.elem[i] = diV( nc.U.elem[i], u, 0.0 );

	  nc_right->n = nc.n-k;
      nc_right->P.inserT( -1, poinT(), nc_right->n );
      nc_right->w.inserT( -1, 0.0, nc_right->n );
      for( i = k;  i < nc.n;  i++ ) {
		  nc_right->P.elem[i-k] = nc.P.elem[i];
		  nc_right->w.elem[i-k] = nc.w.elem[i];
	  }
      nc_right->U.inserT( -1, 0.0, nc_right->n+nc.p+1 );
      for( i = k;  i < k+nc_right->n+nc.p+1;  i++ ) nc_right->U.elem[i-k] = diV( nc.U.elem[i]-u, val, 0.0 );
  }




  void nurbscurvE::interpolatE( pointarraY *pta ) {
      register long i;
      valuE val;
      vectoR beta;
      vectorarraY a, b, c, gamma;
      pointarraY d, delta;


	  if( pta->num < 4 ) return ;

	  deletealL();

      a.inserT( -1, vectoR( 0.0, 0.0, 0.0 ), pta->num );
      a.elem[0] = vectoR( 0.0, 0.0, 0.0 );
      a.elem[1] = vectoR( 1.5, 1.5, 1.5 );
      for( i = 2;  i < pta->num-2;  i++ ) a.elem[i] = vectoR( 1.0, 1.0, 1.0 );
      a.elem[pta->num-2] = vectoR( 1.0, 1.0, 1.0 );
      a.elem[pta->num-1] = vectoR( 0.0, 0.0, 0.0 );

      b.inserT( -1, vectoR( 0.0, 0.0, 0.0 ), pta->num );
      b.elem[0] = vectoR( 1.0, 1.0, 1.0 );
      b.elem[1] = vectoR( 3.5, 3.5, 3.5 );
      for( i = 2;  i < pta->num-2;  i++ ) b.elem[i] = vectoR( 4.0, 4.0, 4.0 );
      b.elem[pta->num-2] = vectoR( 3.5, 3.5, 3.5 );
      b.elem[pta->num-1] = vectoR( 1.0, 1.0, 1.0 );

      c.inserT( -1, vectoR( 0.0, 0.0, 0.0 ), pta->num );
      c.elem[0] = vectoR( 0.0, 0.0, 0.0 );
      c.elem[1] = vectoR( 1.0, 1.0, 1.0 );
      for( i = 2;  i < pta->num-2;  i++ ) c.elem[i] = vectoR( 1.0, 1.0, 1.0 );
      c.elem[pta->num-2] = vectoR( 1.5, 1.5, 1.5 );
      c.elem[pta->num-1] = vectoR( 0.0, 0.0, 0.0 );

      d.inserT( -1, poinT( 0.0, 0.0, 0.0 ), pta->num );
      d.elem[0] = 1.0*pta->elem[0];
      d.elem[1] = 6.0*pta->elem[1];
      for( i = 2;  i < pta->num-2;  i++ ) d.elem[i] = 6.0*pta->elem[i];
      d.elem[pta->num-2] = 6.0*pta->elem[pta->num-2];
      d.elem[pta->num-1] = 1.0*pta->elem[pta->num-1];

      // forward elimination sweep
      gamma.inserT( -1, vectoR( 0.0, 0.0, 0.0 ), pta->num );
      delta.inserT( -1, poinT( 0.0, 0.0, 0.0 ), pta->num );

      beta = vectoR( 1.0/b.elem[0].x, 1.0/b.elem[0].y, 1.0/b.elem[0].z );
      gamma.elem[0] = vectoR( c.elem[0].x*beta.x, c.elem[0].y*beta.y, c.elem[0].z*beta.z );
      delta.elem[0] = poinT( d.elem[0].x*beta.x, d.elem[0].y*beta.y, d.elem[0].z*beta.z );
      for( i = 1;  i < pta->num;  i++ ) {
          beta = vectoR( 1.0/( b.elem[i].x-a.elem[i].x*gamma.elem[i-1].x ), 1.0/( b.elem[i].y-a.elem[i].y*gamma.elem[i-1].y ), 1.0/( b.elem[i].z-a.elem[i].z*gamma.elem[i-1].z ) );
          gamma.elem[i] = vectoR( c.elem[i].x*beta.x, c.elem[i].y*beta.y, c.elem[i].z*beta.z );
          delta.elem[i] = poinT( ( d.elem[i].x-a.elem[i].x*delta.elem[i-1].x )*beta.x, ( d.elem[i].y-a.elem[i].y*delta.elem[i-1].y )*beta.y, ( d.elem[i].z-a.elem[i].z*delta.elem[i-1].z )*beta.z );
      }
  
      // backward substitution sweep
      P.inserT( -1, poinT( 0.0, 0.0, 0.0 ), pta->num );
      P.elem[pta->num-1] = delta.elem[pta->num-1];
      for( i = pta->num-2;  i >= 0;  i-- ) 
          P.elem[i] = delta.elem[i]-vectoR( gamma.elem[i].x*P.elem[i+1].x, gamma.elem[i].y*P.elem[i+1].y, gamma.elem[i].z*P.elem[i+1].z );

      P.inserT( 0, P.elem[0] );
      P.inserT( -1, P.elem[P.num-1] );
         
      p = 3;
      n = P.num;
      w.inserT( -1, 1.0, n ); 
      U.inserT( -1, 0.0 );
      U.inserT( -1, 0.0 );
      U.inserT( -1, 0.0 );
      U.inserT( -1, 0.0 );
	  val = 1.0/( n-p );
	  for( i = 1;  i < n-p;  i++ ) U.inserT( -1, i*val );
      U.inserT( -1, 1.0 );
      U.inserT( -1, 1.0 );
      U.inserT( -1, 1.0 );
      U.inserT( -1, 1.0 ); 
  }




  BOOL nurbscurvE::nurbstobezieR( rationalcubicbeziercurvearraY *rcbca ) {
      if( p < 4 ) {
          register long i, j;
          DWORD dw;
          valuE val2[2], val[3];
          poinT U_[2], V_[3];
          nurbscurvE nc;


          rcbca->deletealL();

          copY( &nc );

          for( i = 0;  i < nc.U.num;  i++ ) {
              dw = i+1;
              while( nc.U.elem[i] == nc.U.elem[dw] ) dw++;
              dw-=i;
              if( dw > nc.p+1 ) dw = nc.p+1;

              for( j = dw;  j < nc.p+1;  j++ ) 
                  nc.insertknoT( nc.U.elem[i] );

              i+=nc.p; 
          }

          for( i = 0;  i < (long)( nc.U.num-nc.p-1 );  i++ ) {
              rcbca->inserT( -1, NULL );

              if( nc.p == 0 ) {
                  nc.P.elem[i]*=nc.w.elem[i];

                  U_[0] = nc.P.elem[i];
                  U_[1] = nc.P.elem[i];
                  val2[0] = nc.w.elem[i];
                  val2[1] = nc.w.elem[i];

                  U_[0]/=val2[0];
                  U_[1]/=val2[1];


                  U_[0]*=val2[0];
                  U_[1]*=val2[1];

                  V_[0] = U_[0];
                  V_[1] = ( U_[0]+U_[1] )*0.5;
                  V_[2] = U_[1];
                  val[0] = val2[0];
                  val[1] = ( val2[0]+val2[1] )*0.5;
                  val[2] = val2[1];

                  V_[0]/=val[0];
                  V_[1]/=val[1];
                  V_[2]/=val[2];


                  V_[0]*=val[0];
                  V_[1]*=val[1];
                  V_[2]*=val[2];

                  rcbca->elem[rcbca->num-1].P[0] = V_[0];
                  rcbca->elem[rcbca->num-1].P[1] = ( V_[0]+2.0*V_[1] )/3.0;
                  rcbca->elem[rcbca->num-1].P[2] = ( 2.0*V_[1]+V_[2] )/3.0;
                  rcbca->elem[rcbca->num-1].P[3] = V_[2];
                  rcbca->elem[rcbca->num-1].w[0] = val[0];
                  rcbca->elem[rcbca->num-1].w[1] = ( val[0]+2.0*val[1] )/3.0;
                  rcbca->elem[rcbca->num-1].w[2] = ( 2.0*val[1]+val[2] )/3.0;
                  rcbca->elem[rcbca->num-1].w[3] = val[2];

                  rcbca->elem[rcbca->num-1].P[0]/=rcbca->elem[rcbca->num-1].w[0];
                  rcbca->elem[rcbca->num-1].P[1]/=rcbca->elem[rcbca->num-1].w[1];
                  rcbca->elem[rcbca->num-1].P[2]/=rcbca->elem[rcbca->num-1].w[2];
                  rcbca->elem[rcbca->num-1].P[3]/=rcbca->elem[rcbca->num-1].w[3];
              } else
              if( nc.p == 1 ) {
                  nc.P.elem[i]*=nc.w.elem[i];
                  nc.P.elem[i+1]*=nc.w.elem[i+1];

                  V_[0] = nc.P.elem[i];
                  V_[1] = ( nc.P.elem[i]+nc.P.elem[i+1] )*0.5;
                  V_[2] = nc.P.elem[i+1];
                  val[0] = nc.w.elem[i];
                  val[1] = ( nc.w.elem[i]+nc.w.elem[i+1] )*0.5;
                  val[2] = nc.w.elem[i+1];

                  V_[0]/=val[0];
                  V_[1]/=val[1];
                  V_[2]/=val[2];


                  V_[0]*=val[0];
                  V_[1]*=val[1];
                  V_[2]*=val[2];

                  rcbca->elem[rcbca->num-1].P[0] = V_[0];
                  rcbca->elem[rcbca->num-1].P[1] = ( V_[0]+2.0*V_[1] )/3.0;
                  rcbca->elem[rcbca->num-1].P[2] = ( 2.0*V_[1]+V_[2] )/3.0;
                  rcbca->elem[rcbca->num-1].P[3] = V_[2];
                  rcbca->elem[rcbca->num-1].w[0] = val[0];
                  rcbca->elem[rcbca->num-1].w[1] = ( val[0]+2.0*val[1] )/3.0;
                  rcbca->elem[rcbca->num-1].w[2] = ( 2.0*val[1]+val[2] )/3.0;
                  rcbca->elem[rcbca->num-1].w[3] = val[2];

                  rcbca->elem[rcbca->num-1].P[0]/=rcbca->elem[rcbca->num-1].w[0];
                  rcbca->elem[rcbca->num-1].P[1]/=rcbca->elem[rcbca->num-1].w[1];
                  rcbca->elem[rcbca->num-1].P[2]/=rcbca->elem[rcbca->num-1].w[2];
                  rcbca->elem[rcbca->num-1].P[3]/=rcbca->elem[rcbca->num-1].w[3];
              } else
              if( nc.p == 2 ) {
                  nc.P.elem[i]*=nc.w.elem[i];
                  nc.P.elem[i+1]*=nc.w.elem[i+1];
                  nc.P.elem[i+2]*=nc.w.elem[i+2];

                  rcbca->elem[rcbca->num-1].P[0] = nc.P.elem[i];
                  rcbca->elem[rcbca->num-1].P[1] = ( nc.P.elem[i]+2.0*nc.P.elem[i+1] )/3.0;
                  rcbca->elem[rcbca->num-1].P[2] = ( 2.0*nc.P.elem[i+1]+nc.P.elem[i+2] )/3.0;
                  rcbca->elem[rcbca->num-1].P[3] = nc.P.elem[i+2];
                  rcbca->elem[rcbca->num-1].w[0] = nc.w.elem[i];
                  rcbca->elem[rcbca->num-1].w[1] = ( nc.w.elem[i]+2.0*nc.w.elem[i+1] )/3.0;
                  rcbca->elem[rcbca->num-1].w[2] = ( 2.0*nc.w.elem[i+1]+nc.w.elem[i+2] )/3.0;
                  rcbca->elem[rcbca->num-1].w[3] = nc.w.elem[i+2];

                  rcbca->elem[rcbca->num-1].P[0]/=rcbca->elem[rcbca->num-1].w[0];
                  rcbca->elem[rcbca->num-1].P[1]/=rcbca->elem[rcbca->num-1].w[1];
                  rcbca->elem[rcbca->num-1].P[2]/=rcbca->elem[rcbca->num-1].w[2];
                  rcbca->elem[rcbca->num-1].P[3]/=rcbca->elem[rcbca->num-1].w[3];
              } else
              if( nc.p == 3 ) {
                  nc.P.elem[i]*=nc.w.elem[i];
                  nc.P.elem[i+1]*=nc.w.elem[i+1];
                  nc.P.elem[i+2]*=nc.w.elem[i+2];
                  nc.P.elem[i+3]*=nc.w.elem[i+3];

                  rcbca->elem[rcbca->num-1].P[0] = nc.P.elem[i];
                  rcbca->elem[rcbca->num-1].P[1] = nc.P.elem[i+1];
                  rcbca->elem[rcbca->num-1].P[2] = nc.P.elem[i+2];
                  rcbca->elem[rcbca->num-1].P[3] = nc.P.elem[i+3];
                  rcbca->elem[rcbca->num-1].w[0] = nc.w.elem[i];
                  rcbca->elem[rcbca->num-1].w[1] = nc.w.elem[i+1];
                  rcbca->elem[rcbca->num-1].w[2] = nc.w.elem[i+2];
                  rcbca->elem[rcbca->num-1].w[3] = nc.w.elem[i+3];

                  rcbca->elem[rcbca->num-1].P[0]/=rcbca->elem[rcbca->num-1].w[0];
                  rcbca->elem[rcbca->num-1].P[1]/=rcbca->elem[rcbca->num-1].w[1];
                  rcbca->elem[rcbca->num-1].P[2]/=rcbca->elem[rcbca->num-1].w[2];
                  rcbca->elem[rcbca->num-1].P[3]/=rcbca->elem[rcbca->num-1].w[3];
              } 

              i+=nc.p; 
          }

          return TRUE;
      } else return FALSE;
  }




  void circlE( const poinT& center, valuE radius, nurbscurvE *nc ) {
      if( nc != NULL ) {
    	  nc->deletealL();

	      nc->P.inserT( -1, poinT(), 9 );
	      nc->w.inserT( -1, 0.0, 9 );
	      nc->U.inserT( -1, 0.0, 12 );
	      nc->n = 9;
	      nc->p = 2;
    	  
	      nc->P.elem[0].x = center.x+radius;  nc->P.elem[0].y = center.y;
	      nc->P.elem[1].x = nc->P.elem[0].x;  nc->P.elem[1].y = center.y+radius;
	      nc->P.elem[2].x = center.x;         nc->P.elem[2].y = nc->P.elem[1].y;
	      nc->P.elem[3].x = center.x-radius;  nc->P.elem[3].y = nc->P.elem[1].y;
	      nc->P.elem[4].x = nc->P.elem[3].x;  nc->P.elem[4].y = center.y;
	      nc->P.elem[5].x = nc->P.elem[3].x;  nc->P.elem[5].y = center.y-radius;
	      nc->P.elem[6].x = center.x;         nc->P.elem[6].y = nc->P.elem[5].y;
	      nc->P.elem[7].x = nc->P.elem[0].x;  nc->P.elem[7].y = nc->P.elem[5].y;
	      nc->P.elem[8].x = nc->P.elem[0].x;  nc->P.elem[8].y = center.y;

	      nc->w.elem[0] = 1.0;
	      nc->w.elem[1] = INV_SQRT2;
	      nc->w.elem[2] = 1.0;
	      nc->w.elem[3] = INV_SQRT2;
	      nc->w.elem[4] = 1.0;
	      nc->w.elem[5] = INV_SQRT2;
	      nc->w.elem[6] = 1.0;
	      nc->w.elem[7] = INV_SQRT2;
	      nc->w.elem[8] = 1.0;

	      nc->U.elem[0] = 0.0;
	      nc->U.elem[1] = 0.0;
	      nc->U.elem[2] = 0.0;
	      nc->U.elem[3] = 0.25;
	      nc->U.elem[4] = 0.25;
	      nc->U.elem[5] = 0.5;
	      nc->U.elem[6] = 0.5;
	      nc->U.elem[7] = 0.75;
	      nc->U.elem[8] = 0.75;
	      nc->U.elem[9] = 1.0;
	      nc->U.elem[10] = 1.0;
	      nc->U.elem[11] = 1.0;
      }
  }




  void circlE2( const poinT& center, valuE radius, nurbscurvE *nc ) {
      if( nc != NULL ) {
    	  valuE val = SQRT3*radius;

	      nc->deletealL();

    	  nc->P.inserT( -1, poinT(), 7 );
	      nc->w.inserT( -1, 0.0, 7 );
    	  nc->U.inserT( -1, 0.0, 10 );
	      nc->n = 7;
    	  nc->p = 2;

	      nc->P.elem[1].x = center.x;                                 nc->P.elem[1].y = center.y-2.0*radius;
    	  nc->P.elem[3].x = center.x-val;                             nc->P.elem[3].y = center.y+radius;
	      nc->P.elem[4].x = center.x;                                 nc->P.elem[4].y = nc->P.elem[3].y;
    	  nc->P.elem[5].x = center.x+val;                             nc->P.elem[5].y = nc->P.elem[3].y;
	      nc->P.elem[2].x = ( nc->P.elem[1].x+nc->P.elem[3].x )*0.5;  nc->P.elem[2].y = ( nc->P.elem[1].y+nc->P.elem[3].y )*0.5;
    	  nc->P.elem[0].x = ( nc->P.elem[1].x+nc->P.elem[5].x )*0.5;  nc->P.elem[0].y = ( nc->P.elem[1].y+nc->P.elem[5].y )*0.5;
	      nc->P.elem[6].x = nc->P.elem[0].x;                          nc->P.elem[6].y = nc->P.elem[0].y;
            
    	  nc->w.elem[0] = 1.0;
	      nc->w.elem[1] = 0.5;
    	  nc->w.elem[2] = 1.0;
    	  nc->w.elem[3] = 0.5;
	      nc->w.elem[4] = 1.0;
    	  nc->w.elem[5] = 0.5;
	      nc->w.elem[6] = 1.0;
    
	      nc->U.elem[0] = 0.0;
	      nc->U.elem[1] = 0.0;
	      nc->U.elem[2] = 0.0;
    	  nc->U.elem[3] = 0.33333333;
	      nc->U.elem[4] = 0.33333333;
          nc->U.elem[5] = 0.66666666;
    	  nc->U.elem[6] = 0.66666666;
	      nc->U.elem[7] = 1.0;
    	  nc->U.elem[8] = 1.0;
	      nc->U.elem[9] = 1.0;
      }
  }








  // NURBSCURVEARRAY
  class nurbscurvearraY: public arraY_<nurbscurvE> {};


  // LPNURBSCURVE
  typedef nurbscurvE* lpnurbscurvE;


  // LPNURBSCURVEARRAY
  class lpnurbscurvearraY: public arraY__<lpnurbscurvE> {};
