 
  // FACE         
  class facE {
      public:
          dwordarraY Via, Eia, Fia; 
		  planE pl;
		  valuE area;


          facE( void ) { reseT(); };
          ~facE( void ) { deletealL(); };
          
          void reseT( void );
          void deletealL( void );
          void copY( facE *F );
  };


  planE faceplanE( facE *F, vertexarraY *Va );
  valuE faceareA( facE *F, vertexarraY *Va );
  BOOL triangleraY( facE *F, vertexarraY *Va, const raY& r, BOOL cull_faces, valuE *t, valuE *u, valuE *v, poinT *Q );
  BOOL faceraY( facE *F, vertexarraY *Va, const raY& r, valuE *t, BOOL cull_faces, valuE *u, valuE *v, poinT *Q, DWORD *i );
  long faceplanE( facE *F, vertexarraY *Va, const planE& pl );
  BOOL faceaabboX( facE *F, vertexarraY *Va, const aabboX& aabb );
  BOOL faceobboX( facE *F, vertexarraY *Va, const oobboX& oobb );
  BOOL facebspherE( facE *F, vertexarraY *Va, const bspherE& bsph );
  BOOL faceedgE( facE *F, vertexarraY *Va1, edgE *E, vertexarraY *Va2 );
  BOOL triangletrianglE( facE *F1, vertexarraY *Va1, facE *F2, vertexarraY *Va2 );






  void facE::reseT( void ) {
      Via.reseT();
      Eia.reseT();
      Fia.reseT();
	  pl = planE();
	  area = 0.0;
  }




  void facE::deletealL( void ) {
      Via.deletealL();
      Eia.deletealL();
      Fia.deletealL();

      reseT();
  }




  void facE::copY( facE *F ) {
      if( F ) {
          F->deletealL();

          Via.copY( &F->Via ); 
          Eia.copY( &F->Eia ); 
          Fia.copY( &F->Fia ); 
	      F->pl = pl;
    	  F->area = area;
      }
  }




  planE faceplanE( facE *F, vertexarraY *Va ) {
	  vectoR u;
      poinT pt;

	  for( register DWORD i = 0;  i < F->Via.num;  i++ ) {
		  u.x+=( Va->elem[F->Via.elem[i]].v.y-Va->elem[F->Via.elem[( i+1 ) % F->Via.num]].v.y )*( Va->elem[F->Via.elem[i]].v.z+Va->elem[F->Via.elem[( i+1 ) % F->Via.num]].v.z );
		  u.y+=( Va->elem[F->Via.elem[i]].v.z-Va->elem[F->Via.elem[( i+1 ) % F->Via.num]].v.z )*( Va->elem[F->Via.elem[i]].v.x+Va->elem[F->Via.elem[( i+1 ) % F->Via.num]].v.x );
		  u.z+=( Va->elem[F->Via.elem[i]].v.x-Va->elem[F->Via.elem[( i+1 ) % F->Via.num]].v.x )*( Va->elem[F->Via.elem[i]].v.y+Va->elem[F->Via.elem[( i+1 ) % F->Via.num]].v.y );
		  pt+=Va->elem[F->Via.elem[i]].v;
	  }

	  F->pl = planE( normalizE( u ), pt/F->Via.num );

      return F->pl;
  }




  valuE faceareA( facE *F, vertexarraY *Va ) {
	  vectoR u, v;

	  F->area = 0.0;
	  u = Va->elem[F->Via.elem[1]].v-Va->elem[F->Via.elem[0]].v;
      for( register DWORD i = 2;  i < F->Via.num;  i++ ) {
		  v = Va->elem[F->Via.elem[i]].v-Va->elem[F->Via.elem[0]].v;
    	  F->area+=lengtH( crosS( u, v ) );
		  u = v;
	  }
	  F->area*=0.5;

      return F->area;
  }




  BOOL triangleraY( facE *F, vertexarraY *Va, const raY& r, BOOL cull_faces, valuE *t, valuE *u, valuE *v, poinT *Q ) {
	  vectoR e1, e2, p_, s, q;
	  valuE a, f;

      if( cull_faces ) { if( doT( F->pl.n, r.q ) > -EPSILON ) return FALSE; } else { if( abs( doT( F->pl.n, r.q ) ) < EPSILON ) return FALSE; }
	  e1 = Va->elem[F->Via.elem[1]].v-Va->elem[F->Via.elem[0]].v;
	  e2 = Va->elem[F->Via.elem[2]].v-Va->elem[F->Via.elem[0]].v;
	  p_ = crosS( r.q, e2 );
	  a = doT( e1, p_ );
	  if( abs( a ) < EPSILON ) return FALSE;
	  f = 1.0/a;
	  s = r.A-Va->elem[F->Via.elem[0]].v;
	  *u = f*doT( s, p_ );
	  if( *u < -EPSILON || *u > 1.0+EPSILON ) return FALSE;
	  q = crosS( s, e1 );
	  *v = f*doT( r.q, q );
	  if( *v < -EPSILON || *u+*v > 1.0+EPSILON ) return FALSE;
	  *t = f*doT( e2, q );
	  if( *t < 0.0 ) return FALSE;
	  *Q = r.A+*t*r.q;  

	  return TRUE;
  }



       
  BOOL faceraY( facE *F, vertexarraY *Va, const raY& r, BOOL cull_faces, valuE *t, valuE *u, valuE *v, poinT *Q, DWORD *i ) {
	  register DWORD ii = 2;
	  BOOL inter = FALSE;
	  vectoR e1, e2, p_, s, q;
	  valuE a, f;

      if( cull_faces ) { if( doT( F->pl.n, r.q ) > -EPSILON ) return FALSE; } else { if( abs( doT( F->pl.n, r.q ) ) < EPSILON ) return FALSE; }
      do {	   
		  e1 = Va->elem[F->Via.elem[ii-1]].v-Va->elem[F->Via.elem[0]].v;
		  e2 = Va->elem[F->Via.elem[ii]].v-Va->elem[F->Via.elem[0]].v;
		  
		  p_ = crosS( r.q, e2 );
		  a = doT( e1, p_ );
		  if( abs( a ) > EPSILON ) {
			  f = 1.0/a;
			  s = r.A-Va->elem[F->Via.elem[0]].v;
			  *u = f*doT( s, p_ );

			  if( *u > -EPSILON && *u <= 1.0+EPSILON ) {
				  q = crosS( s, e1 );
				  *v = f*doT( r.q, q );

				  if( *v > -EPSILON && *u+*v <= 1.0+EPSILON ) {
					  *t = f*doT( e2, q );

					  if( *t >= 0.0 ) {
						  *Q = r.A+r.q**t;
						  inter = TRUE;
					  }
				  }
			  }
		  }
	  } while( !inter && ++ii < F->Via.num );

	  if( inter ) {
		  *i = ii;

		  return TRUE; 
	  } else return FALSE;
  }



          
  long faceplanE( facE *F, vertexarraY *Va, const planE& pl ) {
      BOOL b, b2, b3;
      valuE val;


      b = b2 = b3 = TRUE;
      for( register long i = 0;  i < F->Via.num;  i++ ) {
          val = planepoinT( pl, Va->elem[F->Via.elem[i]].v );
          if( val >= EPSILON ) {
              b = FALSE;
              b2 = FALSE;
          } else
          if( val <= -EPSILON ) {
              b = FALSE;
              b3 = FALSE;
          } 
      }

      if( b ) return 0;
      if( b2 ) return -1;
      if( b3 ) return 1;

      return 0;
  }




  BOOL faceaabboX( facE *F, vertexarraY *Va, const aabboX& aabb ) {
	  register DWORD i;
	  valuE a, b, c;
	  vectoR v, w;
      poinT pt;


	  for( i = 0;  i < F->Via.num;  i++ ) 
		  if( aabboxpoinT( aabb, Va->elem[F->Via.elem[i]].v ) ) return TRUE;
  

	  if( faceplanE( F, Va, planE( 1.0, 0.0, 0.0, -aabb.max.x ) ) > 0 ) return FALSE;
	  if( faceplanE( F, Va, planE( -1.0, 0.0, 0.0, aabb.min.x ) ) > 0 ) return FALSE;
	  if( faceplanE( F, Va, planE( 0.0, 1.0, 0.0, -aabb.max.y ) ) > 0 ) return FALSE;
	  if( faceplanE( F, Va, planE( 0.0, -1.0, 0.0, aabb.min.y ) ) > 0 ) return FALSE;
	  if( faceplanE( F, Va, planE( 0.0, 0.0, 1.0, -aabb.max.z ) ) > 0 ) return FALSE;
	  if( faceplanE( F, Va, planE( 0.0, 0.0, -1.0, aabb.min.z ) ) > 0 ) return FALSE;

	  if( faceplanE( F, Va, planE( 1.0, 0.0, 1.0, -aabb.max.x-aabb.max.z ) ) > 0 ) return FALSE;
	  if( faceplanE( F, Va, planE( 1.0, 0.0, -1.0, aabb.min.z-aabb.max.x ) ) > 0 ) return FALSE;
	  if( faceplanE( F, Va, planE( -1.0, 0.0, -1.0, aabb.min.x+aabb.min.z ) ) > 0 ) return FALSE;
	  if( faceplanE( F, Va, planE( -1.0, 0.0, 1.0, aabb.min.x-aabb.max.z ) ) > 0 ) return FALSE;
	  if( faceplanE( F, Va, planE( 0.0, 1.0, 1.0, -aabb.max.y-aabb.max.z ) ) > 0 ) return FALSE;
	  if( faceplanE( F, Va, planE( 0.0, 1.0, -1.0, aabb.min.z-aabb.max.y ) ) > 0 ) return FALSE;
	  if( faceplanE( F, Va, planE( 0.0, -1.0, -1.0, aabb.min.y+aabb.min.z ) ) > 0 ) return FALSE;
	  if( faceplanE( F, Va, planE( 0.0, -1.0, 1.0, aabb.min.y-aabb.max.z ) ) > 0 ) return FALSE;
	  if( faceplanE( F, Va, planE( 1.0, 1.0, 0.0, -aabb.max.x-aabb.max.y ) ) > 0 ) return FALSE;
	  if( faceplanE( F, Va, planE( 1.0, -1.0, 0.0, aabb.min.y-aabb.max.x ) ) > 0 ) return FALSE;
	  if( faceplanE( F, Va, planE( -1.0, -1.0, 0.0, aabb.min.x+aabb.min.y ) ) > 0 ) return FALSE;
	  if( faceplanE( F, Va, planE( -1.0, 1.0, 0.0, aabb.min.x-aabb.max.y ) ) > 0 ) return FALSE;
    
	  if( faceplanE( F, Va, planE( 1.0, 1.0, 1.0, -aabb.max.x-aabb.max.y-aabb.max.z ) ) > 0 ) return FALSE;
	  if( faceplanE( F, Va, planE( 1.0, 1.0, -1.0, aabb.min.z-aabb.max.x-aabb.max.y ) ) > 0 ) return FALSE;
	  if( faceplanE( F, Va, planE( 1.0, -1.0, 1.0, aabb.min.y-aabb.max.x-aabb.max.z ) ) > 0 ) return FALSE;
	  if( faceplanE( F, Va, planE( -1.0, 1.0, 1.0, aabb.min.x-aabb.max.y-aabb.max.z ) ) > 0 ) return FALSE;
	  if( faceplanE( F, Va, planE( 1.0, -1.0, -1.0, aabb.min.y+aabb.min.z-aabb.max.x ) ) > 0 ) return FALSE;
	  if( faceplanE( F, Va, planE( -1.0, 1.0, -1.0, aabb.min.x-aabb.max.y+aabb.min.z ) ) > 0 ) return FALSE;
	  if( faceplanE( F, Va, planE( -1.0, -1.0, 1.0, aabb.min.x+aabb.min.y-aabb.max.z ) ) > 0 ) return FALSE;
	  if( faceplanE( F, Va, planE( -1.0, -1.0, -1.0, aabb.min.x+aabb.min.y+aabb.min.z ) ) > 0 ) return FALSE;


	  for( i = 0;  i < F->Via.num;  i++ ) 
	      if( aabboxraY( aabb, raY( Va->elem[F->Via.elem[i]].v, Va->elem[F->Via.elem[( i+1 ) % F->Via.num]].v-Va->elem[F->Via.elem[i]].v ), &a ) )
		   	  if( a <= 1.0 ) return TRUE;

                
	  pt = aabb.min;
	  v = aabb.max-pt;
	  a = abs( doT( F->pl.n, v ) );

	  w = poinT( aabb.min.x, aabb.max.y, aabb.max.z )-poinT( aabb.max.x, aabb.min.y, aabb.min.z );
	  b = abs( doT( F->pl.n, w ) );
	  if( b > a ) { 
		  a = b;  
		  pt = poinT( aabb.max.x, aabb.min.y, aabb.min.z );
		  v = w; 
	  }

	  w = poinT( aabb.min.x, aabb.max.y, aabb.min.z )-poinT( aabb.max.x, aabb.min.y, aabb.max.z );
	  b = abs( doT( F->pl.n, w ) );
	  if( b > a ) { 
		  a = b;  
		  pt = poinT( aabb.max.x, aabb.min.y, aabb.max.z );
		  v = w; 
	  }

	  w = poinT( aabb.max.x, aabb.max.y, aabb.min.z )-poinT( aabb.min.x, aabb.min.y, aabb.max.z );
	  b = abs( doT( F->pl.n, w ) );
	  if( b > a ) { 
		  a = b;  
		  pt = poinT( aabb.min.x, aabb.min.y, aabb.max.z );
		  v = w; 
	  }

      if( faceraY( F, Va, raY( pt, v ), FALSE, &a, &b, &c, &pt, &i ) )
	   	  if( a <= 1.0 ) return TRUE;


	  return FALSE;
  }




  BOOL faceobboX( facE *F, vertexarraY *Va, const oobboX& oobb ) {
	  register DWORD i;
	  valuE a, b, c;
	  vectoR u;
      poinT pt;


	  for( i = 0;  i < F->Via.num;  i++ ) 
		  if( obboxpoinT( oobb, Va->elem[F->Via.elem[i]].v ) ) return TRUE;
  

      u = oobb.hu*oobb.u;
	  if( faceplanE( F, Va, planE( oobb.u, oobb.C+u ) ) > 0 ) return FALSE;
	  if( faceplanE( F, Va, planE( oobb.u, oobb.C-u ) ) > 0 ) return FALSE;
      u = oobb.hv*oobb.v;
	  if( faceplanE( F, Va, planE( oobb.v, oobb.C+u ) ) > 0 ) return FALSE;
	  if( faceplanE( F, Va, planE( oobb.v, oobb.C-u ) ) > 0 ) return FALSE;
      u = oobb.hw*oobb.w;
	  if( faceplanE( F, Va, planE( oobb.w, oobb.C+u ) ) > 0 ) return FALSE;
	  if( faceplanE( F, Va, planE( oobb.w, oobb.C-u ) ) > 0 ) return FALSE;


	  for( i = 0;  i < F->Via.num;  i++ ) 
	      if( obboxraY( oobb, raY( Va->elem[F->Via.elem[i]].v, Va->elem[F->Via.elem[( i+1 ) % F->Via.num]].v-Va->elem[F->Via.elem[i]].v ), &a ) )
		   	  if( a <= 1.0 ) return TRUE;


      if( faceraY( F, Va, raY( oobb.C-oobb.u-oobb.v-oobb.w, 2.0*( oobb.u+oobb.v+oobb.w ) ), FALSE, &a, &b, &c, &pt, &i ) )
	   	  if( a <= 1.0 ) return TRUE;

      if( faceraY( F, Va, raY( oobb.C+oobb.u-oobb.v-oobb.w, 2.0*( -oobb.u+oobb.v+oobb.w ) ), FALSE, &a, &b, &c, &pt, &i ) )
	   	  if( a <= 1.0 ) return TRUE;

      if( faceraY( F, Va, raY( oobb.C-oobb.u-oobb.v+oobb.w, 2.0*( oobb.u+oobb.v-oobb.w ) ), FALSE, &a, &b, &c, &pt, &i ) )
	   	  if( a <= 1.0 ) return TRUE;

      if( faceraY( F, Va, raY( oobb.C+oobb.u-oobb.v+oobb.w, 2.0*( -oobb.u+oobb.v-oobb.w ) ), FALSE, &a, &b, &c, &pt, &i ) )
	   	  if( a <= 1.0 ) return TRUE;


	  return FALSE;
  }



             
  BOOL facebspherE( facE *F, vertexarraY *Va, const bspherE& bsph ) {
      register DWORD i;
	  valuE a, b, c;
	  vectoR u;
      poinT pt;


	  for( i = 0;  i < F->Via.num;  i++ ) 
		  if( bspherevectoR( bsph, Va->elem[F->Via.elem[i]].v ) ) return TRUE;
  
	  for( i = 0;  i < F->Via.num;  i++ ) 
	      if( bsphereraY( bsph, raY( Va->elem[F->Via.elem[i]].v, Va->elem[F->Via.elem[( i+1 ) % F->Via.num]].v-Va->elem[F->Via.elem[i]].v ), &a ) )
		   	  if( a <= 1.0 ) return TRUE;

	  u = F->pl.n*bsph.r;
      if( faceraY( F, Va, raY( bsph.C+u, -u*2.0 ), FALSE, &a, &b, &c, &pt, &i ) )
	   	  if( a <= 1.0 ) return TRUE;


	  return FALSE;
  }




  BOOL faceedgE( facE *F, vertexarraY *Va1, edgE *E, vertexarraY *Va2 ) {
      register DWORD i;
	  valuE a, b, c;
	  poinT pt;

      if( faceraY( F, Va1, raY( Va2->elem[E->Via.elem[0]].v, Va2->elem[E->Via.elem[1]].v-Va2->elem[E->Via.elem[0]].v ), FALSE, &a, &b, &c, &pt, &i ) )
	   	  if( a <= 1.0 ) return TRUE;

	  return FALSE;
  }




  BOOL triangletrianglE( facE *F1, vertexarraY *Va1, facE *F2, vertexarraY *Va2 ) {
	  register DWORD i, j;
      valuE a, b, c;
	  poinT pt;


	  if( faceplanE( F1, Va1, F2->pl ) != 0 ) return FALSE;
	  if( faceplanE( F2, Va2, F1->pl ) != 0 ) return FALSE;

	  for( i = 0;  i < F1->Via.num;  i++ ) 
	      if( faceraY( F2, Va2, raY( Va1->elem[F1->Via.elem[i]].v, Va1->elem[F1->Via.elem[( i+1 ) % F1->Via.num]].v-Va1->elem[F1->Via.elem[i]].v ), FALSE, &a, &b, &c, &pt, &j ) )
		   	  if( a <= 1.0 ) return TRUE;

	  for( i = 0;  i < F2->Via.num;  i++ ) 
	      if( faceraY( F1, Va1, raY( Va2->elem[F2->Via.elem[i]].v, Va2->elem[F2->Via.elem[( i+1 ) % F2->Via.num]].v-Va2->elem[F2->Via.elem[i]].v ), FALSE, &a, &b, &c, &pt, &j ) )
		   	  if( a <= 1.0 ) return TRUE;


	  return FALSE;
  }
  
  



   						 


  // FACEARRAY
  class facearraY: public arraY_<facE> {};


  // LPFACE
  typedef facE* lpfacE;


  // LPFACEARRAY
  class lpfacearraY: public arraY__<lpfacE> {};


  BOOL triangleplanE( facearraY *Fa, vertexarraY *Va, DWORD Fi, const planE& pl, dwordarraY *dwa_left, dwordarraY *dwa_, dwordarraY *dwa_right );






  BOOL triangleplanE( facearraY *Fa, vertexarraY *Va, DWORD Fi, const planE& pl, dwordarraY *dwa_left, dwordarraY *dwa_, dwordarraY *dwa_right ) {
      long l[4];
      valuE val;
      poinT pt;
      verteX *V1, *V2;


      dwa_left->deletealL();
      dwa_->deletealL();
      dwa_right->deletealL();


      val = planepoinT( pl, Va->elem[Fa->elem[Fi].Via.elem[0]].v );
      if( val <= -EPSILON ) l[0] = -1; else if( val >= EPSILON ) l[0] = 1; else l[0] = 0; 
      val = planepoinT( pl, Va->elem[Fa->elem[Fi].Via.elem[1]].v );
      if( val <= -EPSILON ) l[1] = -1; else if( val >= EPSILON ) l[1] = 1; else l[1] = 0; 
      val = planepoinT( pl, Va->elem[Fa->elem[Fi].Via.elem[2]].v );
      if( val <= -EPSILON ) l[2] = -1; else if( val >= EPSILON ) l[2] = 1; else l[2] = 0; 
      l[3] = l[0]+l[1]+l[2];


      if( l[0] == 0 && l[1] == 0 && l[2] == 0 ) {
          dwa_->inserT( -1, Fi );

          return FALSE;
      } else
      if( l[0] <= 0 && l[1] <= 0 && l[2] <= 0 ) {
          dwa_left->inserT( -1, Fi );

          return FALSE;
      } else
      if( l[0] >= 0 && l[1] >= 0 && l[2] >= 0 ) {
          dwa_right->inserT( -1, Fi );

          return FALSE;
      } else
      if( l[3] == 0 ) {
          if( ( l[0] == -1 && l[1] == 0 && l[2] == 1 ) || ( l[0] == 1 && l[1] == 0 && l[2] == -1 ) ) {
              Va->inserT( -1, NULL );

              V1 = &Va->elem[Fa->elem[Fi].Via.elem[2]];
              V2 = &Va->elem[Fa->elem[Fi].Via.elem[0]];

              planeraY( pl, raY( V1->v, V2->v-V1->v ), FALSE, &val, &pt );
              
              Va->elem[Va->num-1].v = pt;
              Va->elem[Va->num-1].n = V1->n+( V2->n-V1->n )*val;
              Va->elem[Va->num-1].t = V1->t+( V2->t-V1->t )*val;
              Va->elem[Va->num-1].t2 = V1->t2+( V2->t2-V1->t2 )*val;
              Va->elem[Va->num-1].c = V1->c+( V2->c-V1->c )*val;

              Fa->inserT( -1, NULL );
              Fa->elem[Fa->num-1].Via.inserT( -1, 0, 3 );
              Fa->elem[Fa->num-1].Via.elem[0] = Fa->elem[Fi].Via.elem[2];
              Fa->elem[Fa->num-1].Via.elem[1] = Va->num-1;
              Fa->elem[Fa->num-1].Via.elem[2] = Fa->elem[Fi].Via.elem[1];
              Fa->elem[Fa->num-1].pl = Fa->elem[Fi].pl;

              Fa->elem[Fi].Via.elem[2] = Va->num-1;

              if( l[0] == -1 && l[1] == 0 && l[2] == 1 ) {
                  dwa_left->inserT( -1, Fi );
                  dwa_right->inserT( -1, Fa->num-1 );
              } else {
                  dwa_left->inserT( -1, Fa->num-1 );
                  dwa_right->inserT( -1, Fi );
              }
          } else
          if( ( l[0] == -1 && l[1] == 1 && l[2] == 0 ) || ( l[0] == 1 && l[1] == -1 && l[2] == 0 ) ) {
              Va->inserT( -1, NULL );

              V1 = &Va->elem[Fa->elem[Fi].Via.elem[0]];
              V2 = &Va->elem[Fa->elem[Fi].Via.elem[1]];

              planeraY( pl, raY( V1->v, V2->v-V1->v ), FALSE, &val, &pt );
              
              Va->elem[Va->num-1].v = pt;
              Va->elem[Va->num-1].n = V1->n+( V2->n-V1->n )*val;
              Va->elem[Va->num-1].t = V1->t+( V2->t-V1->t )*val;
              Va->elem[Va->num-1].t2 = V1->t2+( V2->t2-V1->t2 )*val;
              Va->elem[Va->num-1].c = V1->c+( V2->c-V1->c )*val;

              Fa->inserT( -1, NULL );
              Fa->elem[Fa->num-1].Via.inserT( -1, 0, 3 );
              Fa->elem[Fa->num-1].Via.elem[0] = Fa->elem[Fi].Via.elem[0];
              Fa->elem[Fa->num-1].Via.elem[1] = Va->num-1;
              Fa->elem[Fa->num-1].Via.elem[2] = Fa->elem[Fi].Via.elem[2];
              Fa->elem[Fa->num-1].pl = Fa->elem[Fi].pl;

              Fa->elem[Fi].Via.elem[0] = Va->num-1;

              if( l[0] == -1 && l[1] == 1 && l[2] == 0 ) {
                  dwa_left->inserT( -1, Fa->num-1 );
                  dwa_right->inserT( -1, Fi );
              } else {
                  dwa_left->inserT( -1, Fi );
                  dwa_right->inserT( -1, Fa->num-1 );
              }
          } else
          if( ( l[0] == 0 && l[1] == -1 && l[2] == 1 ) || ( l[0] == 0 && l[1] == 1 && l[2] == -1 ) ) {
              Va->inserT( -1, NULL );

              V1 = &Va->elem[Fa->elem[Fi].Via.elem[1]];
              V2 = &Va->elem[Fa->elem[Fi].Via.elem[2]];

              planeraY( pl, raY( V1->v, V2->v-V1->v ), FALSE, &val, &pt );
              
              Va->elem[Va->num-1].v = pt;
              Va->elem[Va->num-1].n = V1->n+( V2->n-V1->n )*val;
              Va->elem[Va->num-1].t = V1->t+( V2->t-V1->t )*val;
              Va->elem[Va->num-1].t2 = V1->t2+( V2->t2-V1->t2 )*val;
              Va->elem[Va->num-1].c = V1->c+( V2->c-V1->c )*val;

              Fa->inserT( -1, NULL );
              Fa->elem[Fa->num-1].Via.inserT( -1, 0, 3 );
              Fa->elem[Fa->num-1].Via.elem[0] = Fa->elem[Fi].Via.elem[0];
              Fa->elem[Fa->num-1].Via.elem[1] = Fa->elem[Fi].Via.elem[1];
              Fa->elem[Fa->num-1].Via.elem[2] = Va->num-1;
              Fa->elem[Fa->num-1].pl = Fa->elem[Fi].pl;

              Fa->elem[Fi].Via.elem[1] = Va->num-1;

              if( l[0] == 0 && l[1] == -1 && l[2] == 1 ) {
                  dwa_left->inserT( -1, Fa->num-1 );
                  dwa_right->inserT( -1, Fi );
              } else {
                  dwa_left->inserT( -1, Fi );
                  dwa_right->inserT( -1, Fa->num-1 );
              }
          }

          return TRUE;
      } else {
          if( ( l[0] == -1 && l[1] == -1 && l[2] == 1 ) || ( l[0] == 1 && l[1] == 1 && l[2] == -1 ) ) {
              Va->inserT( -1, NULL, 2 );

              V1 = &Va->elem[Fa->elem[Fi].Via.elem[1]];
              V2 = &Va->elem[Fa->elem[Fi].Via.elem[2]];

              planeraY( pl, raY( V1->v, V2->v-V1->v ), FALSE, &val, &pt );
              
              Va->elem[Va->num-2].v = pt;
              Va->elem[Va->num-2].n = V1->n+( V2->n-V1->n )*val;
              Va->elem[Va->num-2].t = V1->t+( V2->t-V1->t )*val;
              Va->elem[Va->num-2].t2 = V1->t2+( V2->t2-V1->t2 )*val;
              Va->elem[Va->num-2].c = V1->c+( V2->c-V1->c )*val;

              V1 = &Va->elem[Fa->elem[Fi].Via.elem[2]];
              V2 = &Va->elem[Fa->elem[Fi].Via.elem[0]];

              planeraY( pl, raY( V1->v, V2->v-V1->v ), FALSE, &val, &pt );
              
              Va->elem[Va->num-1].v = pt;
              Va->elem[Va->num-1].n = V1->n+( V2->n-V1->n )*val;
              Va->elem[Va->num-1].t = V1->t+( V2->t-V1->t )*val;
              Va->elem[Va->num-1].t2 = V1->t2+( V2->t2-V1->t2 )*val;
              Va->elem[Va->num-1].c = V1->c+( V2->c-V1->c )*val;


              Fa->inserT( -1, NULL, 2 );

              Fa->elem[Fa->num-2].Via.inserT( -1, 0, 3 );
              Fa->elem[Fa->num-2].Via.elem[0] = Fa->elem[Fi].Via.elem[0];
              Fa->elem[Fa->num-2].Via.elem[1] = Va->num-2;
              Fa->elem[Fa->num-2].Via.elem[2] = Va->num-1;
              Fa->elem[Fa->num-2].pl = Fa->elem[Fi].pl;

              Fa->elem[Fa->num-1].Via.inserT( -1, 0, 3 );
              Fa->elem[Fa->num-1].Via.elem[0] = Va->num-1;
              Fa->elem[Fa->num-1].Via.elem[1] = Va->num-2;
              Fa->elem[Fa->num-1].Via.elem[2] = Fa->elem[Fi].Via.elem[2];
              Fa->elem[Fa->num-1].pl = Fa->elem[Fi].pl;

              Fa->elem[Fi].Via.elem[2] = Va->num-2;


              if( l[0] == -1 && l[1] == -1 && l[2] == 1 ) {
                  dwa_left->inserT( -1, Fi );
                  dwa_left->inserT( -1, Fa->num-2 );
                  dwa_right->inserT( -1, Fa->num-1 );
              } else {
                  dwa_left->inserT( -1, Fa->num-1 );
                  dwa_right->inserT( -1, Fi );
                  dwa_right->inserT( -1, Fa->num-2 );
              }
          } else
          if( ( l[0] == -1 && l[1] == 1 && l[2] == -1 ) || ( l[0] == 1 && l[1] == -1 && l[2] == 1 ) ) {
              Va->inserT( -1, NULL, 2 );

              V1 = &Va->elem[Fa->elem[Fi].Via.elem[0]];
              V2 = &Va->elem[Fa->elem[Fi].Via.elem[1]];

              planeraY( pl, raY( V1->v, V2->v-V1->v ), FALSE, &val, &pt );
              
              Va->elem[Va->num-2].v = pt;
              Va->elem[Va->num-2].n = V1->n+( V2->n-V1->n )*val;
              Va->elem[Va->num-2].t = V1->t+( V2->t-V1->t )*val;
              Va->elem[Va->num-2].t2 = V1->t2+( V2->t2-V1->t2 )*val;
              Va->elem[Va->num-2].c = V1->c+( V2->c-V1->c )*val;

              V1 = &Va->elem[Fa->elem[Fi].Via.elem[1]];
              V2 = &Va->elem[Fa->elem[Fi].Via.elem[2]];

              planeraY( pl, raY( V1->v, V2->v-V1->v ), FALSE, &val, &pt );
              
              Va->elem[Va->num-1].v = pt;
              Va->elem[Va->num-1].n = V1->n+( V2->n-V1->n )*val;
              Va->elem[Va->num-1].t = V1->t+( V2->t-V1->t )*val;
              Va->elem[Va->num-1].t2 = V1->t2+( V2->t2-V1->t2 )*val;
              Va->elem[Va->num-1].c = V1->c+( V2->c-V1->c )*val;


              Fa->inserT( -1, NULL, 2 );

              Fa->elem[Fa->num-2].Via.inserT( -1, 0, 3 );
              Fa->elem[Fa->num-2].Via.elem[0] = Fa->elem[Fi].Via.elem[0];
              Fa->elem[Fa->num-2].Via.elem[1] = Va->num-2;
              Fa->elem[Fa->num-2].Via.elem[2] = Va->num-1;
              Fa->elem[Fa->num-2].pl = Fa->elem[Fi].pl;

              Fa->elem[Fa->num-1].Via.inserT( -1, 0, 3 );
              Fa->elem[Fa->num-1].Via.elem[0] = Va->num-1;
              Fa->elem[Fa->num-1].Via.elem[1] = Va->num-2;
              Fa->elem[Fa->num-1].Via.elem[2] = Fa->elem[Fi].Via.elem[1];
              Fa->elem[Fa->num-1].pl = Fa->elem[Fi].pl;

              Fa->elem[Fi].Via.elem[1] = Va->num-1;


              if( l[0] == -1 && l[1] == 1 && l[2] == -1 ) {
                  dwa_left->inserT( -1, Fi );
                  dwa_left->inserT( -1, Fa->num-2 );
                  dwa_right->inserT( -1, Fa->num-1 );
              } else {
                  dwa_left->inserT( -1, Fa->num-1 );
                  dwa_right->inserT( -1, Fi );
                  dwa_right->inserT( -1, Fa->num-2 );
              }
          } else
          if( ( l[0] == -1 && l[1] == 1 && l[2] == 1 ) || ( l[0] == 1 && l[1] == -1 && l[2] == -1 ) ) {
              Va->inserT( -1, NULL, 2 );

              V1 = &Va->elem[Fa->elem[Fi].Via.elem[0]];
              V2 = &Va->elem[Fa->elem[Fi].Via.elem[1]];

              planeraY( pl, raY( V1->v, V2->v-V1->v ), FALSE, &val, &pt );
              
              Va->elem[Va->num-2].v = pt;
              Va->elem[Va->num-2].n = V1->n+( V2->n-V1->n )*val;
              Va->elem[Va->num-2].t = V1->t+( V2->t-V1->t )*val;
              Va->elem[Va->num-2].t2 = V1->t2+( V2->t2-V1->t2 )*val;
              Va->elem[Va->num-2].c = V1->c+( V2->c-V1->c )*val;

              V1 = &Va->elem[Fa->elem[Fi].Via.elem[2]];
              V2 = &Va->elem[Fa->elem[Fi].Via.elem[0]];

              planeraY( pl, raY( V1->v, V2->v-V1->v ), FALSE, &val, &pt );
              
              Va->elem[Va->num-1].v = pt;
              Va->elem[Va->num-1].n = V1->n+( V2->n-V1->n )*val;
              Va->elem[Va->num-1].t = V1->t+( V2->t-V1->t )*val;
              Va->elem[Va->num-1].t2 = V1->t2+( V2->t2-V1->t2 )*val;
              Va->elem[Va->num-1].c = V1->c+( V2->c-V1->c )*val;


              Fa->inserT( -1, NULL, 2 );

              Fa->elem[Fa->num-2].Via.inserT( -1, 0, 3 );
              Fa->elem[Fa->num-2].Via.elem[0] = Fa->elem[Fi].Via.elem[2];
              Fa->elem[Fa->num-2].Via.elem[1] = Va->num-1;
              Fa->elem[Fa->num-2].Via.elem[2] = Va->num-2;
              Fa->elem[Fa->num-2].pl = Fa->elem[Fi].pl;

              Fa->elem[Fa->num-1].Via.inserT( -1, 0, 3 );
              Fa->elem[Fa->num-1].Via.elem[0] = Va->num-2;
              Fa->elem[Fa->num-1].Via.elem[1] = Va->num-1;
              Fa->elem[Fa->num-1].Via.elem[2] = Fa->elem[Fi].Via.elem[0];
              Fa->elem[Fa->num-1].pl = Fa->elem[Fi].pl;

              Fa->elem[Fi].Via.elem[0] = Va->num-2;


              if( l[0] == -1 && l[1] == 1 && l[2] == 1 ) {
                  dwa_left->inserT( -1, Fa->num-1 );
                  dwa_right->inserT( -1, Fi );
                  dwa_right->inserT( -1, Fa->num-2 );
              } else {
                  dwa_left->inserT( -1, Fi );
                  dwa_left->inserT( -1, Fa->num-2 );
                  dwa_right->inserT( -1, Fa->num-1 );
              }
          } 

          return TRUE;
      }
  }
