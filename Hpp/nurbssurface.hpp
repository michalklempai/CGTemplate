
  // NURBSSURFACE
  class nurbssurfacE {
      public:
          DWORD n, m, p, q;
          valuearraY w, U, V; 
          pointarraY P;


          nurbssurfacE( void ) { reseT(); };
          ~nurbssurfacE( void ) { deletealL(); };

		  void reseT( void );
		  void deletealL( void );
		  void copY( nurbssurfacE *ns );

          valuE Nu( DWORD i, DWORD p, valuE u );
          valuE Nv( DWORD j, DWORD q, valuE v );
		  valuE dNu( DWORD i, DWORD p, valuE u );
		  valuE dNv( DWORD j, DWORD q, valuE v );
          poinT Q( valuE u, valuE v, poinT *A = NULL );
//		  poinT Q( valuE u, valuE v, poinT *A, vectoR *dAu, vectoR *dAv ); //
          void insertknotU( valuE u ); 
          void insertknotV( valuE v ); 
          void splitU( valuE u, nurbssurfacE *ns_left, nurbssurfacE *ns_right ); 
          void splitV( valuE v, nurbssurfacE *ns_top, nurbssurfacE *ns_bottom ); 
          BOOL nurbstobezieR( rationalbicubicbeziersurfacearraY *rbbsa ); 
  };                   


  void ruledsurfacE( nurbscurvE *nc, nurbssurfacE *ns );






  void nurbssurfacE::reseT( void ) {
      n = m = p = q = 0;
      w.reseT();
      U.reseT();
      V.reseT();
      P.reseT();
  }

  


  void nurbssurfacE::deletealL( void ) {
      w.deletealL();
      U.deletealL();
      V.deletealL();
      P.deletealL();

	  reseT();
  }




  void nurbssurfacE::copY( nurbssurfacE *ns ) {
      ns->deletealL();

      ns->n = n;
      ns->m = m;
      ns->p = p;
      ns->q = q;
      w.copY( &ns->w );
      U.copY( &ns->U );
      V.copY( &ns->V );
      P.copY( &ns->P );
  }




  valuE nurbssurfacE::Nu( DWORD i, DWORD p, valuE u ) {
	  if( p > 1 ) {
          return diV( ( u-U.elem[i] )*Nu( i, p-1, u ), U.elem[i+p]-U.elem[i], 0.0 )+
                 diV( ( U.elem[i+p+1]-u )*Nu( i+1, p-1, u ), U.elem[i+p+1]-U.elem[i+1], 0.0 );
	  } else {
		  if( p == 1 ) {
			  valuE sum = 0.0;

		      if( u >= U.elem[i] && u < U.elem[i+1] ) sum+=diV( u-U.elem[i], U.elem[i+p]-U.elem[i], 0.0 );
			  if( u >= U.elem[i+1] && u < U.elem[i+2] ) sum+=diV( U.elem[i+p+1]-u, U.elem[i+p+1]-U.elem[i+1], 0.0 );

			  return sum;
		  } else {
              if( u >= U.elem[i] && u < U.elem[i+1] ) return 1.0; else return 0.0;  
		  }
	  }
  }




  valuE nurbssurfacE::Nv( DWORD j, DWORD q, valuE v ) {
	  if( q > 1 ) {
          return diV( ( v-V.elem[j] )*Nv( j, q-1, v ), V.elem[j+q]-V.elem[j], 0.0 )+
                 diV( ( V.elem[j+q+1]-v )*Nv( j+1, q-1, v ), V.elem[j+q+1]-V.elem[j+1], 0.0 );
	  } else {
		  if( q == 1 ) {
			  valuE sum = 0.0;

		      if( v >= V.elem[j] && v < V.elem[j+1] ) sum+=diV( v-V.elem[j], V.elem[j+q]-V.elem[j], 0.0 );
			  if( v >= V.elem[j+1] && v < V.elem[j+2] ) sum+=diV( V.elem[j+q+1]-v, V.elem[j+q+1]-V.elem[j+1], 0.0 );

			  return sum;
		  } else {
	          if( v >= V.elem[j] && v < V.elem[j+1] ) return 1.0; else return 0.0;  
		  }
	  }
  }




  valuE nurbssurfacE::dNu( DWORD i, DWORD p, valuE u ) {
      if( p > 1 ) {
          return diV( Nu( i, p-1, u )+( u-U.elem[i] )*dNu( i, p-1, u ), U.elem[i+p]-U.elem[i], 0.0 )+
                 diV( ( U.elem[i+p+1]-u )*dNu( i+1, p-1, u )-Nu( i+1, p-1, u ), U.elem[i+p+1]-U.elem[i+1], 0.0 );
      } else {
          if( p == 1 ) {
              return diV( Nu( i, p-1, u ), U.elem[i+p]-U.elem[i], 0.0 )+
                     diV( -Nu( i+1, p-1, u ), U.elem[i+p+1]-U.elem[i+1], 0.0 );
          } else {
              return 0.0;
          }
      }
  }




  valuE nurbssurfacE::dNv( DWORD j, DWORD q, valuE v ) {
      if( q > 1 ) {
          return diV( Nv( j, q-1, v )+( v-V.elem[j] )*dNv( j, q-1, v ), V.elem[j+q]-V.elem[j], 0.0 )+
                 diV( ( V.elem[j+q+1]-v )*dNv( j+1, q-1, v )-Nv( j+1, q-1, v ), V.elem[j+q+1]-V.elem[j+1], 0.0 );
      } else {
          if( q == 1 ) {
              return diV( Nv( j, q-1, v ), V.elem[j+q]-V.elem[j], 0.0 )+
                     diV( -Nv( j+1, q-1, v ), V.elem[j+q+1]-V.elem[j+1], 0.0 );
          } else {
              return 0.0;
          }
      }
  }




  poinT nurbssurfacE::Q( valuE u, valuE v, poinT *A ) {
	  if( n > p && m > q ) {
          register DWORD i, j; 
	      valuE a, b, c;
          poinT R;

    	  u = clamP( u, U.elem[p]+EPSILON, U.elem[n]-EPSILON );
          v = clamP( v, V.elem[q]+EPSILON, V.elem[m]-EPSILON );

          c = 0.0;
	      R = poinT( 0.0, 0.0, 0.0 );
		  for( i = 0;  i < n;  i++ ) 
			  if( u >= U.elem[i] && u < U.elem[i+p+1] ) {
				  b = Nu( i, p, u );

				  for( j = 0;  j < m;  j++ ) 
					  if( v >= V.elem[j] && v < V.elem[j+q+1] ) {
			              a = w.elem[i+j*n]*b*Nv( j, q, v );
				          R+=P.elem[i+j*n]*a;  
			              c+=a;
					  }
			  }

	      if( A ) return *A = R/c; else return R/c;
	  }
  }



/*
  void nurbssurfacE::Q( valuE u, valuE v, poinT *A, vectoR *dAu, vectoR *dAv ) {
	  if( n > p && m > q ) {
          register DWORD i, j; 
	      valuE a, b, c, d, f;
		  DWORD dw;

	      A->x = A->y = A->z = dAu->x = dAu->y = dAu->z = dAv->x = dAv->y = dAv->z = c = 0.0;
		  for( i = 0;  i < n;  i++ ) 
			  if( u >= U.elem[i] && u < U.elem[i+p+1] ) {
				  b = Nu( i, p, u );
				  d = dNu( i, p, u );

				  for( j = 0;  j < m;  j++ ) 
					  if( v >= V.elem[j] && v < V.elem[j+q+1] ) {
						  f = Nv( j, q, v );
						  dw = i+j*n;

			              a = w.elem[dw]*b*f;
				          *A+=P.elem[dw]*a;  
			              c+=a;

				          *dAu+=P.elem[dw]*d*f;  
					      *dAv+=P.elem[dw]*b*dNv( j, q, v );  
					  }
			  }
	      *A/=c;  
	  }


/*
          valuE x, y, z;
          //xxx
          y = 0.0;
          for( i = 0;  i < n;  i++ ) y+=w[i
          // dorob derivaciu
	      dAu->x = dAu->y = dAu->z = 0.0;
		  for( i = 0;  i < n;  i++ ) 
			  if( u >= U.elem[i] && u < U.elem[i+p+1] ) {
				  for( j = 0;  j < m;  j++ ) 
					  if( v >= V.elem[j] && v < V.elem[j+q+1] ) {
						  dw = i+j*n;

			              a = w.elem[dw]*b*e;
				          *A+=P.elem[dw]*a;  
			              c+=a;
/*
				          *dAu+=P.elem[dw]*d*e;  
					      *dAv+=P.elem[dw]*b*dNv( j, q, v );  */
/*					  }
			  }
	      *A/=c;  
  
	  }
  */
/*  }*/

  


  void nurbssurfacE::insertknotU( valuE u ) {
      register long i, k, l;
      valuE a, b, c, oldPw, hPw;
      poinT oldP, hP;


	  u = clamP( u, U.elem[p]+EPSILON, U.elem[n]-EPSILON );

	  for( i = p;  i < n;  i++ )
		  if( u >= U.elem[i] && u <= U.elem[i+1] ) {
			  k = i;
			  i = n;
		  }

	  for( l = ( m-1 )*n;  l >= 0;  l-=n ) {
	      P.inserT( k+l, P.elem[k+l] );  w.inserT( k+l, w.elem[k+l] );
		  oldP = P.elem[k+l-p];  oldPw = w.elem[k+l-p];

          for( i = k+l-p+1;  i <= k+l;  i++ ) {
	          hP = P.elem[i];  hPw = w.elem[i];
		
		      a = diV( u-U.elem[i-l], U.elem[i-l+p]-U.elem[i-l], 0.0 );
			  c = 1.0-a;
			  b = oldPw*c+w.elem[i]*a;
			  P.elem[i] = ( oldP*c*oldPw+P.elem[i]*a*w.elem[i] )/b;
	          w.elem[i] = b;                               

		      oldP =  hP;  oldPw =  hPw;
	      }
	  }
	  
      U.inserT( k+1, u );
	  n++; 
  }

  


  void nurbssurfacE::insertknotV( valuE v ) {
      register long i, k, l;
	  DWORD dw;
      valuE a, b, c, oldPw, hPw;
      poinT oldP, hP;


      v = clamP( v, V.elem[q]+EPSILON, V.elem[m]-EPSILON );

	  for( i = q;  i < m;  i++ )
		  if( v >= V.elem[i] && v <= V.elem[i+1] ) {
			  k = i;
			  i = m;
		  }

	  for( l = n-1;  l >= 0;  l-- ) { 
		  P.inserT( k*n+n, P.elem[k*n+l] );  
		  w.inserT( k*n+n, w.elem[k*n+l] ); 
	  }

	  for( l = n-1;  l >= 0;  l-- ) {
		  oldP = P.elem[( k-q )*n+l];  oldPw = w.elem[( k-q )*n+l];

          for( i = k-q+1;  i <= k;  i++ ) {
			  dw = l+i*n;

	          hP = P.elem[dw];  hPw = w.elem[dw];
		
		      a = diV( v-V.elem[i], V.elem[i+q]-V.elem[i], 0.0 );
			  c = 1.0-a;
			  b = oldPw*c+w.elem[dw]*a;
			  P.elem[dw] = ( oldP*c*oldPw+P.elem[dw]*a*w.elem[dw] )/b;
	          w.elem[dw] = b;                               

		      oldP =  hP;  oldPw =  hPw;
	      }
	  }
	  
      V.inserT( k+1, v );
	  m++; 
  }

  


  void nurbssurfacE::splitU( valuE u, nurbssurfacE *ns_left, nurbssurfacE *ns_right ) {
      register long i, j, k;
      DWORD dw;
      nurbssurfacE ns;


      u = clamP( u, U.elem[p]+EPSILON, U.elem[n]-EPSILON );

      copY( &ns );
      dw = 0;
      for( i = 0;  i < U.num;  i++ ) if( u == U.elem[i] ) dw++; 
      for( i = dw;  i <= p;  i++ ) ns.insertknotU( u );

	  for( i = p;  i < n;  i++ )
		  if( u >= U.elem[i] && u <= U.elem[i+1] ) {
			  k = i;
			  i = n;
		  }

      ns_left->deletealL();  ns_right->deletealL();
      ns_left->p = ns_right->p = ns.p;
      ns_left->q = ns_right->q = ns.q;

	  ns_left->n = k+1;
	  for( j = 0;  j < ns.m;  j++ ) 
	      for( i = 0;  i <= k;  i++ ) {
			  ns_left->P.inserT( -1, ns.P.elem[i+j*ns.n] );
			  ns_left->w.inserT( -1, ns.w.elem[i+j*ns.n] );
		  }
      for( i = 0;  i < ns_left->n+ns.p+1;  i++ ) ns_left->U.inserT( -1, diV( ns.U.elem[i], u, 0.0 ) );
	  ns.V.copY( &ns_left->V );

	  ns_right->n = ns.n-k;
	  for( j = 0;  j < ns.m;  j++ ) 
	      for( i = k;  i < ns.n;  i++ ) {
			  ns_right->P.inserT( -1, ns.P.elem[i+j*ns.n] );
			  ns_right->w.inserT( -1, ns.w.elem[i+j*ns.n] );
		  }
      for( i = k;  i < k+ns_right->n+ns.p+1;  i++ ) ns_right->U.inserT( -1, diV( ns.U.elem[i]-u, 1.0-u, 0.0 ) );
	  ns.V.copY( &ns_right->V );
  
      ns_left->m = ns_right->m = ns.m;
  }




  void nurbssurfacE::splitV( valuE v, nurbssurfacE *ns_top, nurbssurfacE *ns_bottom ) {
      register long i, j, k;
      DWORD dw;
      nurbssurfacE ns;


      v = clamP( v, V.elem[q]+EPSILON, V.elem[m]-EPSILON );

      copY( &ns );
      dw = 0;
      for( i = 0;  i < V.num;  i++ ) if( v == V.elem[i] ) dw++; 
      for( i = dw;  i <= q;  i++ ) ns.insertknotV( v );

	  for( i = q;  i < m;  i++ )
		  if( v >= V.elem[i] && v <= V.elem[i+1] ) {
			  k = i;
			  i = m;
		  }

      ns_top->deletealL();  ns_bottom->deletealL();
      ns_top->p = ns_bottom->p = ns.p;
      ns_top->q = ns_bottom->q = ns.q;

	  ns_top->m = k+1;
      for( j = 0;  j <= k;  j++ )
	      for( i = 0;  i < ns.n;  i++ ) {
			  ns_top->P.inserT( -1, ns.P.elem[i+j*ns.n] );
			  ns_top->w.inserT( -1, ns.w.elem[i+j*ns.n] );
		  }
	  ns.U.copY( &ns_top->U );
      for( i = 0;  i < ns_top->m+ns.q+1;  i++ ) ns_top->V.inserT( -1, diV( ns.V.elem[i], v, 0.0 ) );

	  ns_bottom->m = ns.m-k;
      for( j = k;  j < ns.m;  j++ ) 
		  for( i = 0;  i < ns.n;  i++ ) {
			  ns_bottom->P.inserT( -1, ns.P.elem[i+j*ns.n] );
			  ns_bottom->w.inserT( -1, ns.w.elem[i+j*ns.n] );
		  }
	  ns.U.copY( &ns_bottom->U );
      for( i = k;  i < k+ns_bottom->m+ns.q+1;  i++ ) ns_bottom->V.inserT( -1, diV( ns.V.elem[i]-v, 1.0-v, 0.0 ) );
  
      ns_top->n = ns_bottom->n = ns.n;
  }


  

  BOOL nurbssurfacE::nurbstobezieR( rationalbicubicbeziersurfacearraY *rbbsa ) {
      if( p < 4 && q < 4 ) {
          register long i, j, k, l;
          DWORD dw;
          valuE val2[4][4], val[4][4], val3[4][4];
          poinT U_[4][4], V_[4][4], W_[4][4];
          nurbssurfacE ns;


          rbbsa->deletealL();

          copY( &ns );

          for( i = 0;  i < ns.U.num;  i++ ) {
              dw = i+1;
              while( ns.U.elem[i] == ns.U.elem[dw] ) dw++;
              dw-=i;
              if( dw > ns.p+1 ) dw = ns.p+1;

              for( j = dw;  j < ns.p+1;  j++ ) 
                  ns.insertknotU( ns.U.elem[i] );

              i+=ns.p; 
          }

          for( i = 0;  i < ns.V.num;  i++ ) {
              dw = i+1;
              while( ns.V.elem[i] == ns.V.elem[dw] ) dw++;
              dw-=i;
              if( dw > ns.q+1 ) dw = ns.q+1;

              for( j = dw;  j < ns.q+1;  j++ ) 
                  ns.insertknotV( ns.V.elem[i] );

              i+=ns.q; 
          }

          for( i = 0;  i < ns.U.num-ns.p-1;  i++ ) {
              for( j = 0;  j < ns.V.num-ns.q-1;  j++ ) {
                  rbbsa->inserT( -1, NULL );


                  if( ns.q == 0 ) {
                      for( k = i;  k <= i+ns.p;  k++ ) 
                          for( l = j;  l <= j+ns.q;  l++ ) 
                              ns.P.elem[k+l*ns.n]*=ns.w.elem[k+l*ns.n];

                      for( k = 0;  k < ns.p+1;  k++ ) {
                          U_[k][0] = ns.P.elem[k+i+( 0+j )*ns.n];
                          U_[k][1] = ns.P.elem[k+i+( 0+j )*ns.n];
                          val2[k][0] = ns.w.elem[k+i+( 0+j )*ns.n];
                          val2[k][1] = ns.w.elem[k+i+( 0+j )*ns.n];
                      }

                      for( k = 0;  k < ns.p+1;  k++ ) 
                          for( l = 0;  l < 2;  l++ ) U_[k][l]/=val2[k][l];


                      for( k = 0;  k < ns.p+1;  k++ ) 
                          for( l = 0;  l < 2;  l++ ) U_[k][l]*=val2[k][l];

                      for( k = 0;  k < ns.p+1;  k++ ) {
                          V_[k][0] = U_[k][0];
                          V_[k][1] = ( U_[k][0]+U_[k][1] )*0.5;
                          V_[k][2] = U_[k][1];
                          val[k][0] = val2[k][0];
                          val[k][1] = ( val2[k][0]+val2[k][1] )*0.5;
                          val[k][2] = val2[k][1];
                      }

                      for( k = 0;  k < ns.p+1;  k++ ) 
                          for( l = 0;  l < 3;  l++ ) V_[k][l]/=val[k][l];


                      for( k = 0;  k < ns.p+1;  k++ ) 
                          for( l = 0;  l < 3;  l++ ) V_[k][l]*=val[k][l];

                      for( k = 0;  k < ns.p+1;  k++ ) {
                          rbbsa->elem[rbbsa->num-1].P[k][0] = V_[k][0];
                          rbbsa->elem[rbbsa->num-1].P[k][1] = ( V_[k][0]+2.0*V_[k][1] )/3.0;
                          rbbsa->elem[rbbsa->num-1].P[k][2] = ( 2.0*V_[k][1]+V_[k][2] )/3.0;
                          rbbsa->elem[rbbsa->num-1].P[k][3] = V_[k][2];
                          rbbsa->elem[rbbsa->num-1].w[k][0] = val[k][0];
                          rbbsa->elem[rbbsa->num-1].w[k][1] = ( val[k][0]+2.0*val[k][1] )/3.0;
                          rbbsa->elem[rbbsa->num-1].w[k][2] = ( 2.0*val[k][1]+val[k][2] )/3.0;
                          rbbsa->elem[rbbsa->num-1].w[k][3] = val[k][2];
                      }

                      for( k = 0;  k < ns.p+1;  k++ ) 
                          for( l = 0;  l < 4;  l++ ) 
                              rbbsa->elem[rbbsa->num-1].P[k][l]/=rbbsa->elem[rbbsa->num-1].w[k][l];
                  } else 
                  if( ns.q == 1 ) {
                      for( k = i;  k <= i+ns.p;  k++ ) 
                          for( l = j;  l <= j+ns.q;  l++ ) 
                              ns.P.elem[k+l*ns.n]*=ns.w.elem[k+l*ns.n];

                      for( k = 0;  k < ns.p+1;  k++ ) {
                          V_[k][0] = ns.P.elem[k+i+( 0+j )*ns.n];
                          V_[k][1] = ( ns.P.elem[k+i+( 0+j )*ns.n]+ns.P.elem[k+i+( 1+j )*ns.n] )*0.5;
                          V_[k][2] = ns.P.elem[k+i+( 1+j )*ns.n];
                          val[k][0] = ns.w.elem[k+i+( 0+j )*ns.n];
                          val[k][1] = ( ns.w.elem[k+i+( 0+j )*ns.n]+ns.w.elem[k+i+( 1+j )*ns.n] )*0.5;
                          val[k][2] = ns.w.elem[k+i+( 1+j )*ns.n];
                      }

                      for( k = 0;  k < ns.p+1;  k++ ) 
                          for( l = 0;  l < 3;  l++ ) V_[k][l]/=val[k][l];


                      for( k = 0;  k < ns.p+1;  k++ ) 
                          for( l = 0;  l < 3;  l++ ) V_[k][l]*=val[k][l];

                      for( k = 0;  k < ns.p+1;  k++ ) {
                          rbbsa->elem[rbbsa->num-1].P[k][0] = V_[k][0];
                          rbbsa->elem[rbbsa->num-1].P[k][1] = ( V_[k][0]+2.0*V_[k][1] )/3.0;
                          rbbsa->elem[rbbsa->num-1].P[k][2] = ( 2.0*V_[k][1]+V_[k][2] )/3.0;
                          rbbsa->elem[rbbsa->num-1].P[k][3] = V_[k][2];
                          rbbsa->elem[rbbsa->num-1].w[k][0] = val[k][0];
                          rbbsa->elem[rbbsa->num-1].w[k][1] = ( val[k][0]+2.0*val[k][1] )/3.0;
                          rbbsa->elem[rbbsa->num-1].w[k][2] = ( 2.0*val[k][1]+val[k][2] )/3.0;
                          rbbsa->elem[rbbsa->num-1].w[k][3] = val[k][2];
                      }

                      for( k = 0;  k < ns.p+1;  k++ ) 
                          for( l = 0;  l < 4;  l++ ) 
                              rbbsa->elem[rbbsa->num-1].P[k][l]/=rbbsa->elem[rbbsa->num-1].w[k][l];
                  } else 
                  if( ns.q == 2 ) {
                      for( k = i;  k <= i+ns.p;  k++ ) 
                          for( l = j;  l <= j+ns.q;  l++ ) 
                              ns.P.elem[k+l*ns.n]*=ns.w.elem[k+l*ns.n];

                      for( k = 0;  k < ns.p+1;  k++ ) {
                          rbbsa->elem[rbbsa->num-1].P[k][0] = ns.P.elem[k+i+( 0+j )*ns.n];
                          rbbsa->elem[rbbsa->num-1].P[k][1] = ( ns.P.elem[k+i+( 0+j )*ns.n]+2.0*ns.P.elem[k+i+( 1+j )*ns.n] )/3.0;
                          rbbsa->elem[rbbsa->num-1].P[k][2] = ( 2.0*ns.P.elem[k+i+( 1+j )*ns.n]+ns.P.elem[k+i+( 2+j )*ns.n] )/3.0;
                          rbbsa->elem[rbbsa->num-1].P[k][3] = ns.P.elem[k+i+( 2+j )*ns.n];
                          rbbsa->elem[rbbsa->num-1].w[k][0] = ns.w.elem[k+i+( 0+j )*ns.n];
                          rbbsa->elem[rbbsa->num-1].w[k][1] = ( ns.w.elem[k+i+( 0+j )*ns.n]+2.0*ns.w.elem[k+i+( 1+j )*ns.n] )/3.0;
                          rbbsa->elem[rbbsa->num-1].w[k][2] = ( 2.0*ns.w.elem[k+i+( 1+j )*ns.n]+ns.w.elem[k+i+( 2+j )*ns.n] )/3.0;
                          rbbsa->elem[rbbsa->num-1].w[k][3] = ns.w.elem[k+i+( 2+j )*ns.n];
                      }

                      for( k = 0;  k < ns.p+1;  k++ ) 
                          for( l = 0;  l < 4;  l++ ) 
                              rbbsa->elem[rbbsa->num-1].P[k][l]/=rbbsa->elem[rbbsa->num-1].w[k][l];
                  } else 
                  if( ns.q == 3 ) {
                      for( k = i;  k <= i+ns.p;  k++ ) 
                          for( l = j;  l <= j+ns.q;  l++ ) 
                              ns.P.elem[k+l*ns.n]*=ns.w.elem[k+l*ns.n];

                      for( k = 0;  k < ns.p+1;  k++ ) 
                          for( l = 0;  l < 4;  l++ ) {
                              rbbsa->elem[rbbsa->num-1].P[k][l] = ns.P.elem[k+i+( l+j )*ns.n];
                              rbbsa->elem[rbbsa->num-1].w[k][l] = ns.w.elem[k+i+( l+j )*ns.n];
                          }

                      for( k = 0;  k < ns.p+1;  k++ ) 
                          for( l = 0;  l < 4;  l++ ) 
                              rbbsa->elem[rbbsa->num-1].P[k][l]/=rbbsa->elem[rbbsa->num-1].w[k][l];
                  } 


                  for( k = 0;  k < ns.p+1;  k++ ) 
                      for( l = 0;  l < 4;  l++ ) {
                          W_[k][l] = rbbsa->elem[rbbsa->num-1].P[k][l];
                          val3[k][l] = rbbsa->elem[rbbsa->num-1].w[k][l];
                      }


                  if( ns.p == 0 ) {
                      for( k = 0;  k < ns.p+1;  k++ ) 
                          for( l = 0;  l < 4;  l++ ) 
                              W_[k][l]*=val3[k][l];

                      for( l = 0;  l < 4;  l++ ) {
                          U_[0][l] = W_[0][l];
                          U_[1][l] = W_[0][l];
                          val2[0][l] = val3[0][l];
                          val2[1][l] = val3[0][l];
                      }

                      for( k = 0;  k < ns.p+1+1;  k++ ) 
                          for( l = 0;  l < 4;  l++ ) U_[k][l]/=val2[k][l];


                      for( k = 0;  k < ns.p+1+1;  k++ ) 
                          for( l = 0;  l < 4;  l++ ) U_[k][l]*=val2[k][l];

                      for( l = 0;  l < 4;  l++ ) {
                          V_[0][l] = U_[0][l];
                          V_[1][l] = ( U_[0][l]+U_[1][l] )*0.5;
                          V_[2][l] = U_[1][l];
                          val[0][l] = val2[0][l];
                          val[1][l] = ( val2[0][l]+val2[1][l] )*0.5;
                          val[2][l] = val2[1][l];
                      }

                      for( k = 0;  k < ns.p+1+1+1;  k++ ) 
                          for( l = 0;  l < 4;  l++ ) V_[k][l]/=val[k][l];


                      for( k = 0;  k < ns.p+1+1+1;  k++ ) 
                          for( l = 0;  l < 4;  l++ ) V_[k][l]*=val[k][l];

                      for( l = 0;  l < 4;  l++ ) {
                          rbbsa->elem[rbbsa->num-1].P[0][l] = V_[0][l];
                          rbbsa->elem[rbbsa->num-1].P[1][l] = ( V_[0][l]+2.0*V_[1][l] )/3.0;
                          rbbsa->elem[rbbsa->num-1].P[2][l] = ( 2.0*V_[1][l]+V_[2][l] )/3.0;
                          rbbsa->elem[rbbsa->num-1].P[3][l] = V_[2][l];
                          rbbsa->elem[rbbsa->num-1].w[0][l] = val[0][l];
                          rbbsa->elem[rbbsa->num-1].w[1][l] = ( val[0][l]+2.0*val[1][l] )/3.0;
                          rbbsa->elem[rbbsa->num-1].w[2][l] = ( 2.0*val[1][l]+val[2][l] )/3.0;
                          rbbsa->elem[rbbsa->num-1].w[3][l] = val[2][l];
                      }

                      for( k = 0;  k < ns.p+1+1+1+1;  k++ ) 
                          for( l = 0;  l < 4;  l++ ) 
                              rbbsa->elem[rbbsa->num-1].P[k][l]/=rbbsa->elem[rbbsa->num-1].w[k][l];
                  } else 
                  if( ns.p == 1 ) {
                      for( k = 0;  k < ns.p+1;  k++ ) 
                          for( l = 0;  l < 4;  l++ ) 
                              W_[k][l]*=val3[k][l];

                      for( l = 0;  l < 4;  l++ ) {
                          V_[0][l] = W_[0][l];
                          V_[1][l] = ( W_[0][l]+W_[1][l] )*0.5;
                          V_[2][l] = W_[1][l];
                          val[0][l] = val3[0][l];
                          val[1][l] = ( val3[0][l]+val3[1][l] )*0.5;
                          val[2][l] = val3[1][l];
                      }

                      for( k = 0;  k < ns.p+1+1;  k++ ) 
                          for( l = 0;  l < 4;  l++ ) V_[k][l]/=val[k][l];


                      for( k = 0;  k < ns.p+1+1;  k++ ) 
                          for( l = 0;  l < 4;  l++ ) V_[k][l]*=val[k][l];

                      for( l = 0;  l < 4;  l++ ) {
                          rbbsa->elem[rbbsa->num-1].P[0][l] = V_[0][l];
                          rbbsa->elem[rbbsa->num-1].P[1][l] = ( V_[0][l]+2.0*V_[1][l] )/3.0;
                          rbbsa->elem[rbbsa->num-1].P[2][l] = ( 2.0*V_[1][l]+V_[2][l] )/3.0;
                          rbbsa->elem[rbbsa->num-1].P[3][l] = V_[2][l];
                          rbbsa->elem[rbbsa->num-1].w[0][l] = val[0][l];
                          rbbsa->elem[rbbsa->num-1].w[1][l] = ( val[0][l]+2.0*val[1][l] )/3.0;
                          rbbsa->elem[rbbsa->num-1].w[2][l] = ( 2.0*val[1][l]+val[2][l] )/3.0;
                          rbbsa->elem[rbbsa->num-1].w[3][l] = val[2][l];
                      }

                      for( k = 0;  k < ns.p+1+1+1;  k++ ) 
                          for( l = 0;  l < 4;  l++ ) 
                              rbbsa->elem[rbbsa->num-1].P[k][l]/=rbbsa->elem[rbbsa->num-1].w[k][l];
                  } else 
                  if( ns.p == 2 ) {
                      for( k = 0;  k < ns.p+1;  k++ ) 
                          for( l = 0;  l < 4;  l++ ) 
                              W_[k][l]*=val3[k][l];

                      for( l = 0;  l < 4;  l++ ) {
                          rbbsa->elem[rbbsa->num-1].P[0][l] = W_[0][l];
                          rbbsa->elem[rbbsa->num-1].P[1][l] = ( W_[0][l]+2.0*W_[1][l] )/3.0;
                          rbbsa->elem[rbbsa->num-1].P[2][l] = ( 2.0*W_[1][l]+W_[2][l] )/3.0;
                          rbbsa->elem[rbbsa->num-1].P[3][l] = W_[2][l];
                          rbbsa->elem[rbbsa->num-1].w[0][l] = val3[0][l];
                          rbbsa->elem[rbbsa->num-1].w[1][l] = ( val3[0][l]+2.0*val3[1][l] )/3.0;
                          rbbsa->elem[rbbsa->num-1].w[2][l] = ( 2.0*val3[1][l]+val3[2][l] )/3.0;
                          rbbsa->elem[rbbsa->num-1].w[3][l] = val3[2][l];
                      }

                      for( k = 0;  k < ns.p+1+1;  k++ ) 
                          for( l = 0;  l < 4;  l++ ) 
                              rbbsa->elem[rbbsa->num-1].P[k][l]/=rbbsa->elem[rbbsa->num-1].w[k][l];
                  } 

                  j+=ns.q;
              }

              i+=ns.p; 
          }
  
          return TRUE;
      } else return FALSE;
  }




  void ruledsurfacE( nurbscurvE *nc, nurbssurfacE *ns ) {
      register long i;
      poinT pt;


      ns->deletealL();

      ns->P.inserT( -1, poinT(), 9*nc->n );
      ns->w.inserT( -1, 0.0, 9*nc->n );
      ns->n = 9;  ns->m = nc->n;
      ns->p = 2;  ns->q = nc->p;
      
      ns->U.inserT( -1, 0.0, 12 );
      ns->U.elem[0] = 0.0;
      ns->U.elem[1] = 0.0;
      ns->U.elem[2] = 0.0;
      ns->U.elem[3] = 0.25;
      ns->U.elem[4] = 0.25;
      ns->U.elem[5] = 0.5;
      ns->U.elem[6] = 0.5;
      ns->U.elem[7] = 0.75;
      ns->U.elem[8] = 0.75;
      ns->U.elem[9] = 1.0;
      ns->U.elem[10] = 1.0;
      ns->U.elem[11] = 1.0;
      
      nc->U.copY( &ns->V );

      for( i = 0;  i < nc->n;  i++ ) {
          pt = nc->P.elem[i];

          ns->P.elem[0+i*ns->n] = poinT( pt.x, pt.y, pt.z );
          ns->P.elem[1+i*ns->n] = poinT( pt.x+pt.z, pt.y, pt.z-pt.x );
          ns->P.elem[2+i*ns->n] = poinT( pt.z, pt.y, -pt.x );
          ns->P.elem[3+i*ns->n] = poinT( pt.z-pt.x, pt.y, -pt.x-pt.z );
          ns->P.elem[4+i*ns->n] = poinT( -pt.x, pt.y, -pt.z );
          ns->P.elem[5+i*ns->n] = poinT( -pt.x-pt.z, pt.y, -pt.z+pt.x );
          ns->P.elem[6+i*ns->n] = poinT( -pt.z, pt.y, pt.x );
          ns->P.elem[7+i*ns->n] = poinT( -pt.z+pt.x, pt.y, pt.x+pt.z );
          ns->P.elem[8+i*ns->n] = poinT( pt.x, pt.y, pt.z );

          ns->w.elem[0+i*ns->n] = nc->w.elem[i]*1.0;
          ns->w.elem[1+i*ns->n] = nc->w.elem[i]*SQRT2*0.5;
          ns->w.elem[2+i*ns->n] = nc->w.elem[i]*1.0;
          ns->w.elem[3+i*ns->n] = nc->w.elem[i]*SQRT2*0.5;
          ns->w.elem[4+i*ns->n] = nc->w.elem[i]*1.0;
          ns->w.elem[5+i*ns->n] = nc->w.elem[i]*SQRT2*0.5;
          ns->w.elem[6+i*ns->n] = nc->w.elem[i]*1.0;
          ns->w.elem[7+i*ns->n] = nc->w.elem[i]*SQRT2*0.5;
          ns->w.elem[8+i*ns->n] = nc->w.elem[i]*1.0;
      }
  }





   


  // NURBSSURFACEARRAY
  class nurbssurfacearraY: public arraY_<nurbssurfacE> {};


  // LPNURBSSURFACE
  typedef nurbssurfacE* lpnurbssurfacE;


  // LPNURBSSURFACEARRAY
  class lpnurbssurfacearraY: public arraY__<lpnurbssurfacE> {};
  