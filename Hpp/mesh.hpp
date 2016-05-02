
  // BSPTREENODE         
  class bsptreenodE {
      public:
		  dwordarraY Ia;
          bsptreenodE *left_node, *right_node;        
	      aabboX aabb;
	      planE pl;


          bsptreenodE( void ) { reseT(); };
          ~bsptreenodE( void ) { deletealL(); };
          
          void reseT( void );
          void deletealL( void );
  };


  void releasebsptreE_( bsptreenodE *bsptn );
  void releasebsptreE( bsptreenodE *bsptroot );






  void bsptreenodE::reseT( void ) {
      Ia.reseT();
	  left_node = right_node = NULL;
	  aabb = aabboX();
	  pl = planE();
  }




  void bsptreenodE::deletealL( void ) {
      Ia.deletealL();

      reseT();
  }




  void releasebsptreE_( bsptreenodE *bsptn ) {
	  if( bsptn->left_node ) {
		  releasebsptreE_( bsptn->left_node );  
		  delete bsptn->left_node;  
	  } 
	  if( bsptn->right_node ) {
		  releasebsptreE_( bsptn->right_node );  
		  delete bsptn->right_node;  
	  } 
	  bsptn->deletealL();
  }




  void releasebsptreE( bsptreenodE *bsptroot ) {
      releasebsptreE_( bsptroot );  

      bsptroot->reseT();
  }








  // LPBSPTREENODE
  typedef bsptreenodE* lpbsptreenodE;


  // LPBSPTREENODEARRAY
  class lpbsptreenodearraY: public arraY__<lpbsptreenodE> {};
  















  // MESH       
  class mesH : public objecT {
      private:
          void createbsptreE( vertexarraY *Va, bsptreenodE *bsptn_, DWORD depth );
		  void releasebsptreE( bsptreenodE *bsptn_ );
          DWORD createbsptreE2( vertexarraY *Va, facearraY *Fa, bsptreenodE *bsptn_ );
		  void releasebsptreE2( bsptreenodE *bsptn_ );


      public:
	      vertexarraY Va;
		  edgearraY Ea;
		  facearraY Fa;
          bsptreenodE bsptroot;
          lpbsptreenodearraY lpbsptna;
          bsptreenodE bsptroot2;
          lpbsptreenodearraY lpbsptna2;


          mesH( void ) { reseT(); };
          ~mesH( void ) { deletealL(); };
          
          void reseT( void );
          void deletealL( void );
          void copY( mesH *M );
          
		  poinT calculatecenterofmasS( void );
		  aabboX findaabboX( void );
		  oobboX findoobboX( void );
		  bspherE findbspherE( void );
		  void findconvexhulL( void );
		  void findprojectedconvexhulL( camerA *C );
		  void resetxforM( void );

          void createbsptreE( DWORD maxdepth = 16 );
          void releasebsptreE( void );
          DWORD createbsptreE2( void );
          void releasebsptreE2( void );
  };


  void meshexplodE( mesH *M );
  void meshdetacH( mesH *M, dwordarraY *dwa, mesH *M2, mesH *M3 );
  void meshtriangulatE( mesH *M );
  void transformvertexnormalS( mesH *M, matriX mat );
  void calculateplaneS( mesH *M );
  void calculateareaS( mesH *M );
  void calculatevertexnormalS( mesH *M, valuE thres );
  void calculateadjacencY( mesH *M );
  BOOL meshraY( mesH *M, const raY& r, BOOL cull_faces, valuE *t, verteX *V, planE *pl, DWORD *Fi, DWORD *i );
  void meshplanE( mesH *M, bsptreenodE *bsptn, const planE& pl, dwordarraY *dwa1, dwordarraY *dwa2, dwordarraY *dwa3 );
  BOOL meshplanE( mesH *M, const planE& pl, dwordarraY *dwa1, dwordarraY *dwa2, dwordarraY *dwa3 );
  void meshaabboX( mesH *M, bsptreenodE *bsptn, const aabboX& aabb, dwordarraY *dwa );
  BOOL meshaabboX( mesH *M, const aabboX& aabb, dwordarraY *dwa );
  void meshbspherE( mesH *M, bsptreenodE *bsptn, const bspherE& bsph, dwordarraY *dwa );
  BOOL meshbspherE( mesH *M, const bspherE& bsph, dwordarraY *dwa );
  void meshmesH( mesH *M1, bsptreenodE *bsptn1, mesH *M2, bsptreenodE *bsptn2, dwordarraY *dwa );
  BOOL meshmesH( mesH *M1, mesH *M2, dwordarraY *dwa );
  BOOL loadasC( char filename[512], mesH *M );






  void mesH::reseT( void ) {
      Va.reseT();
      Ea.reseT();
      Fa.reseT();
      aabb = aabboX();
      oobb = oobboX();
      bsph = bspherE();
	  mata.reseT();
	  mtrla.reseT();
      bsptroot.reseT();
      lpbsptna.reseT();
      bsptroot2.reseT();
      lpbsptna2.reseT();
      convexhull.reseT();
	  projected_ch.reseT();
  }




  void mesH::deletealL( void ) {
      Va.deletealL();
      Ea.deletealL();
      Fa.deletealL();
      mata.deletealL();
      mtrla.deletealL();
      releasebsptreE();
      lpbsptna.deletealL();
      releasebsptreE2();
      lpbsptna2.deletealL();
      convexhull.deletealL();
      projected_ch.deletealL();

      reseT();
  }




  void mesH::copY( mesH *M ) {
      if( M ) {
          M->deletealL();

          Va.copY( &M->Va ); 
          Ea.copY( &M->Ea ); 
          Fa.copY( &M->Fa ); 
          M->aabb = aabb; 
          M->oobb = oobb; 
          M->bsph = bsph; 
          mata.copY( &M->mata );
          mtrla.copY( &M->mtrla );
          convexhull.copY( &M->convexhull );
          projected_ch.copY( &M->projected_ch );
      }
  }




  void mesH::createbsptreE( vertexarraY *Va, bsptreenodE *bsptn_, DWORD depth ) {
      if( depth > 0 && bsptn_->Ia.num > 16 && ( ( bsptn_->pl.n.x == -1.0 && min( bsptn_->pl.d-bsptn_->aabb.min.x, bsptn_->aabb.max.x-bsptn_->pl.d ) > EPSILON ) || 
		                                        ( bsptn_->pl.n.y == -1.0 && min( bsptn_->pl.d-bsptn_->aabb.min.y, bsptn_->aabb.max.y-bsptn_->pl.d ) > EPSILON ) || 
												( bsptn_->pl.n.z == -1.0 && min( bsptn_->pl.d-bsptn_->aabb.min.z, bsptn_->aabb.max.z-bsptn_->pl.d ) > EPSILON ) ) ) {
          long l;


	      bsptn_->left_node = new bsptreenodE;
          bsptn_->right_node = new bsptreenodE;

		  bsptn_->left_node->aabb = bsptn_->right_node->aabb = bsptn_->aabb;
		  if( bsptn_->pl.n.x == -1.0 ) {
              bsptn_->left_node->aabb.max.x = bsptn_->right_node->aabb.min.x = bsptn_->pl.d;
		  } else
          if( bsptn_->pl.n.y == -1.0 ) {
              bsptn_->left_node->aabb.max.y = bsptn_->right_node->aabb.min.y = bsptn_->pl.d;
		  } else
          if( bsptn_->pl.n.z == -1.0 ) {
              bsptn_->left_node->aabb.max.z = bsptn_->right_node->aabb.min.z = bsptn_->pl.d;
		  } 

		  // LEFT
		  if( bsptn_->left_node->aabb.max.x-bsptn_->left_node->aabb.min.x >= max( bsptn_->left_node->aabb.max.y-bsptn_->left_node->aabb.min.y, bsptn_->left_node->aabb.max.z-bsptn_->left_node->aabb.min.z ) ) {
			  bsptn_->left_node->pl.n = -E0;
              bsptn_->left_node->pl.d = ( bsptn_->left_node->aabb.min.x+bsptn_->left_node->aabb.max.x )*0.5;
		  } else
		  if( bsptn_->left_node->aabb.max.y-bsptn_->left_node->aabb.min.y >= max( bsptn_->left_node->aabb.max.x-bsptn_->left_node->aabb.min.x, bsptn_->left_node->aabb.max.z-bsptn_->left_node->aabb.min.z ) ) {
			  bsptn_->left_node->pl.n = -E1;
              bsptn_->left_node->pl.d = ( bsptn_->left_node->aabb.min.y+bsptn_->left_node->aabb.max.y )*0.5;
		  } else {
			  bsptn_->left_node->pl.n = -E2;
              bsptn_->left_node->pl.d = ( bsptn_->left_node->aabb.min.z+bsptn_->left_node->aabb.max.z )*0.5;
		  }

		  // RIGHT
		  if( bsptn_->right_node->aabb.max.x-bsptn_->right_node->aabb.min.x >= max( bsptn_->right_node->aabb.max.y-bsptn_->right_node->aabb.min.y, bsptn_->right_node->aabb.max.z-bsptn_->right_node->aabb.min.z ) ) {
			  bsptn_->right_node->pl.n = -E0;
              bsptn_->right_node->pl.d = ( bsptn_->right_node->aabb.min.x+bsptn_->right_node->aabb.max.x )*0.5;
		  } else
		  if( bsptn_->right_node->aabb.max.y-bsptn_->right_node->aabb.min.y >= max( bsptn_->right_node->aabb.max.x-bsptn_->right_node->aabb.min.x, bsptn_->right_node->aabb.max.z-bsptn_->right_node->aabb.min.z ) ) {
			  bsptn_->right_node->pl.n = -E1;
              bsptn_->right_node->pl.d = ( bsptn_->right_node->aabb.min.y+bsptn_->right_node->aabb.max.y )*0.5;
		  } else {
			  bsptn_->right_node->pl.n = -E2;
              bsptn_->right_node->pl.d = ( bsptn_->right_node->aabb.min.z+bsptn_->right_node->aabb.max.z )*0.5;
		  }

          for( register DWORD i = 0;  i < bsptn_->Ia.num;  i++ ) {
              l = faceplanE( &Fa.elem[bsptn_->Ia.elem[i]], Va, bsptn_->pl );
			  if( l >= 0 ) bsptn_->left_node->Ia.inserT( -1, bsptn_->Ia.elem[i] );
			  if( l <= 0 ) bsptn_->right_node->Ia.inserT( -1, bsptn_->Ia.elem[i] );
		  }
		  bsptn_->Ia.deletealL();

          depth--;
          createbsptreE( Va, bsptn_->left_node, depth );
          createbsptreE( Va, bsptn_->right_node, depth );
	  } 
  }




  void mesH::releasebsptreE( bsptreenodE *bsptn_ ) {
	  if( bsptn_->left_node ) {
		  releasebsptreE( bsptn_->left_node );  
		  delete bsptn_->left_node;  
	  } 
	  if( bsptn_->right_node ) {
		  releasebsptreE( bsptn_->right_node );  
		  delete bsptn_->right_node;  
	  } 
	  bsptn_->deletealL();
  }




  DWORD mesH::createbsptreE2( vertexarraY *Va, facearraY *Fa, bsptreenodE *bsptn_ ) {
      BOOL b;
      register long i, j;
      DWORD dw, k, l;
      poinT pt;
      dwordarraY dwa, dwa_left, dwa_, dwa_right;


      // convex
      b = TRUE;
      for( i = 0;  i < bsptn_->Ia.num;  i++ ) 
          for( j = 0;  j < bsptn_->Ia.num;  j++ ) 
              if( i != j ) 
                  if( planepoinT( Fa->elem[bsptn_->Ia.elem[i]].pl, Va->elem[Fa->elem[bsptn_->Ia.elem[j]].Via.elem[0]].v ) >= EPSILON ||
                      planepoinT( Fa->elem[bsptn_->Ia.elem[i]].pl, Va->elem[Fa->elem[bsptn_->Ia.elem[j]].Via.elem[1]].v ) >= EPSILON ||
                      planepoinT( Fa->elem[bsptn_->Ia.elem[i]].pl, Va->elem[Fa->elem[bsptn_->Ia.elem[j]].Via.elem[2]].v ) >= EPSILON ) {

                      b = FALSE;
                      goto END;
                  }
      END:

      if( !b ) {
          // find split face
          l = 0;
          dw = ULONG_MAX; 
          for( i = 0;  i < bsptn_->Ia.num;  i++ ) {
              k = 0;
              for( j = 0;  j < bsptn_->Ia.num;  j++ ) 
                  if( i != j && faceplanE( &Fa->elem[bsptn_->Ia.elem[j]], Va, Fa->elem[bsptn_->Ia.elem[i]].pl ) != 0 ) k++;

              if( abs( (long)k-(long)( bsptn_->Ia.num*0.75 ) ) < dw ) {
                  dw = abs( (long)k-(long)( bsptn_->Ia.num*0.75 ) );
                  l = i;
              }
          }

          bsptn_->pl = Fa->elem[bsptn_->Ia.elem[l]].pl; 
          dw = bsptn_->Ia.elem[l];
          bsptn_->Ia.deletE( l );
          bsptn_->Ia.inserT( 0, dw );


	      bsptn_->left_node = new bsptreenodE;
          bsptn_->right_node = new bsptreenodE;
	
          dwa.inserT( -1, bsptn_->Ia.elem[0] );

          for( i = 1;  i < bsptn_->Ia.num;  i++ ) {
              triangleplanE( Fa, Va, bsptn_->Ia.elem[i], bsptn_->pl, &dwa_left, &dwa_, &dwa_right );

              bsptn_->left_node->Ia.inserT( -1, 0, dwa_left.num );
              for( j = 0;  j < dwa_left.num;  j++ )
                  bsptn_->left_node->Ia.elem[bsptn_->left_node->Ia.num-j-1] = dwa_left.elem[j];

              dwa.inserT( -1, 0, dwa_.num );
              for( j = 0;  j < dwa_.num;  j++ )
                  dwa.elem[dwa.num-j-1] = dwa_.elem[j];

              bsptn_->right_node->Ia.inserT( -1, 0, dwa_right.num );
              for( j = 0;  j < dwa_right.num;  j++ )
                  bsptn_->right_node->Ia.elem[bsptn_->right_node->Ia.num-j-1] = dwa_right.elem[j];
		  }

          if( bsptn_->left_node->Ia.num == 0 ) {
              delete bsptn_->left_node;
              bsptn_->left_node = NULL;
          }
          if( bsptn_->right_node->Ia.num == 0 ) {
              delete bsptn_->right_node;
              bsptn_->right_node = NULL;
          }

		  bsptn_->Ia.deletealL();
          bsptn_->Ia.inserT( -1, 0, dwa.num );
          for( i = 0;  i < dwa.num;  i++ ) 
              bsptn_->Ia.elem[bsptn_->Ia.num-i-1] = dwa.elem[i];

		  // LEFT
          if( bsptn_->left_node ) {
              aabb.min = poinT( INFINITY, INFINITY, INFINITY );
              aabb.max = poinT( -INFINITY, -INFINITY, -INFINITY );
              for( i = 0;  i < bsptn_->left_node->Ia.num;  i++ ) 
                  for( j = 0;  j < Fa->elem[bsptn_->left_node->Ia.elem[i]].Via.num;  j++ ) {
                      pt = Va->elem[Fa->elem[bsptn_->left_node->Ia.elem[i]].Via.elem[j]].v;
                      if( pt.x < aabb.min.x ) aabb.min.x = pt.x;
                      if( pt.x > aabb.max.x ) aabb.max.x = pt.x; 	  
                      if( pt.y < aabb.min.y ) aabb.min.y = pt.y; 
   	                  if( pt.y > aabb.max.y ) aabb.max.y = pt.y; 	  
                      if( pt.z < aabb.min.z ) aabb.min.z = pt.z; 
                      if( pt.z > aabb.max.z ) aabb.max.z = pt.z; 	  
                  }
	    	  bsptn_->left_node->aabb = aabb;  
          }

		  // RIGHT
          if( bsptn_->right_node ) {
              aabb.min = poinT( INFINITY, INFINITY, INFINITY );
              aabb.max = poinT( -INFINITY, -INFINITY, -INFINITY );
              for( i = 0;  i < bsptn_->right_node->Ia.num;  i++ ) 
                  for( j = 0;  j < Fa->elem[bsptn_->right_node->Ia.elem[i]].Via.num;  j++ ) {
                      pt = Va->elem[Fa->elem[bsptn_->right_node->Ia.elem[i]].Via.elem[j]].v;
                      if( pt.x < aabb.min.x ) aabb.min.x = pt.x;
                      if( pt.x > aabb.max.x ) aabb.max.x = pt.x; 	  
                      if( pt.y < aabb.min.y ) aabb.min.y = pt.y; 
   	                  if( pt.y > aabb.max.y ) aabb.max.y = pt.y; 	  
                      if( pt.z < aabb.min.z ) aabb.min.z = pt.z; 
                      if( pt.z > aabb.max.z ) aabb.max.z = pt.z; 	  
                  }
	    	  bsptn_->right_node->aabb = aabb;
          }

          i = j = 0;
          if( bsptn_->left_node ) i = createbsptreE2( Va, Fa, bsptn_->left_node );
          if( bsptn_->right_node ) j = createbsptreE2( Va, Fa, bsptn_->right_node );
          return max( i, j )+1;
	  } 

      return 0;
  }




  void mesH::releasebsptreE2( bsptreenodE *bsptn_ ) {
	  if( bsptn_->left_node ) {
		  releasebsptreE2( bsptn_->left_node );  
		  delete bsptn_->left_node;  
	  } 
	  if( bsptn_->right_node ) {
		  releasebsptreE2( bsptn_->right_node );  
		  delete bsptn_->right_node;  
	  } 
	  bsptn_->deletealL();
  }




  void mesH::createbsptreE( DWORD maxdepth ) {
	  register DWORD i;
      vertexarraY Va;


  	  releasebsptreE();

      this->Va.copY( &Va );
      for( i = 0;  i < this->Va.num;  i++ ) 
		  Va.elem[i].v = multiplY( this->Va.elem[i].v, mata.elem[0] );

      bsptroot.Ia.inserT( -1, 0, Fa.num );
	  for( i = 1;  i < Fa.num;  i++ ) bsptroot.Ia.elem[i] = i;
      
	  bsptroot.aabb = aabb;
	  if( aabb.max.x-aabb.min.x >= max( aabb.max.y-aabb.min.y, aabb.max.z-aabb.min.z ) ) {
	      bsptroot.pl.n = -E0;
	      bsptroot.pl.d = ( aabb.min.x+aabb.max.x )*0.5;
 	  } else
	  if( aabb.max.y-aabb.min.y >= max( aabb.max.x-aabb.min.x, aabb.max.z-aabb.min.z ) ) {
	      bsptroot.pl.n = -E1;
	      bsptroot.pl.d = ( aabb.min.y+aabb.max.y )*0.5;
	  } else {
	      bsptroot.pl.n = -E2;
	      bsptroot.pl.d = ( aabb.min.z+aabb.max.z )*0.5;
  	  }

      createbsptreE( &Va, &bsptroot, maxdepth );
  }




  void mesH::releasebsptreE( void ) {
      releasebsptreE( &bsptroot );  

      bsptroot.reseT();
  }




  DWORD mesH::createbsptreE2( void ) {
	  register DWORD i, j;
      poinT pt;
      aabboX aabb;


	  releasebsptreE2();

      if( Fa.num > 0 ) {
          bsptroot2.Ia.inserT( -1, 0, Fa.num );
    	  for( i = 1;  i < Fa.num;  i++ ) bsptroot2.Ia.elem[i] = i;

          aabb.min = poinT( INFINITY, INFINITY, INFINITY );
          aabb.max = poinT( -INFINITY, -INFINITY, -INFINITY );
          for( i = 0;  i < bsptroot2.Ia.num;  i++ ) 
              for( j = 0;  j < Fa.elem[bsptroot2.Ia.elem[i]].Via.num;  j++ ) {
                  pt = Va.elem[Fa.elem[bsptroot2.Ia.elem[i]].Via.elem[j]].v;
                  if( pt.x < aabb.min.x ) aabb.min.x = pt.x;
                  if( pt.x > aabb.max.x ) aabb.max.x = pt.x; 	  
                  if( pt.y < aabb.min.y ) aabb.min.y = pt.y; 
                  if( pt.y > aabb.max.y ) aabb.max.y = pt.y; 	  
                  if( pt.z < aabb.min.z ) aabb.min.z = pt.z; 
                  if( pt.z > aabb.max.z ) aabb.max.z = pt.z; 	  
              }
    	  bsptroot2.aabb = aabb;
                                 
          return createbsptreE2( &Va, &Fa, &bsptroot2 );
      } 

      return 0;
  }




  void mesH::releasebsptreE2( void ) {
      releasebsptreE2( &bsptroot2 );  

      bsptroot2.reseT();
  }




  poinT mesH::calculatecenterofmasS( void ) {
	  com = poinT( 0.0, 0.0, 0.0 );

	  for( register DWORD i = 0;  i < Va.num;  i++ ) com += Va.elem[i].v;
	  if (Va.num > 0) com /= (valuE) Va.num;

      return com;
  }




  aabboX mesH::findaabboX( void ) {
      aabb.min = poinT( INFINITY, INFINITY, INFINITY );
      aabb.max = poinT( -INFINITY, -INFINITY, -INFINITY );

      for( register DWORD i = 0;  i < Va.num;  i++ ) {
          if( Va.elem[i].v.x < aabb.min.x ) aabb.min.x = Va.elem[i].v.x;
          if( Va.elem[i].v.x > aabb.max.x ) aabb.max.x = Va.elem[i].v.x; 	  
          if( Va.elem[i].v.y < aabb.min.y ) aabb.min.y = Va.elem[i].v.y; 
   	      if( Va.elem[i].v.y > aabb.max.y ) aabb.max.y = Va.elem[i].v.y; 	  
          if( Va.elem[i].v.z < aabb.min.z ) aabb.min.z = Va.elem[i].v.z; 
          if( Va.elem[i].v.z > aabb.max.z ) aabb.max.z = Va.elem[i].v.z; 	  
      }

      return aabb;
  }




  oobboX mesH::findoobboX( void ) {
      register long i;
      long l;
      valuE val, val2;
      poinT pt, _00, _01, _02,
                _10, _11, _12,
                _20, _21, _22;
      valuearraY vala;
      pointarraY pta, convexhull;
      planearraY convexhull_;

      
      pta.inserT( -1, poinT(), Va.num );
      for( i = 0;  i < Va.num;  i++ ) pta.elem[i] = Va.elem[i].v;

      l = quickhull3D( &pta, &convexhull/*, &convexhull_*/ );
      if( l == 3 ) { // 3d cloud
          // area
          val = 0.0;
          vala.inserT( -1, 0.0, convexhull.num/3 );
          for( i = 0;  i < convexhull.num/3;  i++ ) {
              vala.elem[i] = lengtH( crosS( convexhull.elem[3*i+1]-convexhull.elem[3*i], convexhull.elem[3*i+2]-convexhull.elem[3*i] ) )*0.5; 
              val+=vala.elem[i];
          }
          val = 1.0/val; 

          // centroid
          pta.deletealL();
          pt = poinT( 0.0, 0.0, 0.0 );
          pta.inserT( -1, poinT(), convexhull.num/3 );
          for( i = 0;  i < convexhull.num/3;  i++ ) {
              pta.elem[i] = ( convexhull.elem[3*i]+convexhull.elem[3*i+1]+convexhull.elem[3*i+2] )/3.0; 
              pt+=vala.elem[i]*pta.elem[i];
          }
          pt*=val;


          val2 = 0.0;
          for( i = 0;  i < convexhull.num/3;  i++ ) val2+=vala.elem[i]*( 9.0*pta.elem[i].x*pta.elem[i].x + convexhull.elem[3*i].x*convexhull.elem[3*i].x + 
                                                          convexhull.elem[3*i+1].x*convexhull.elem[3*i+1].x + convexhull.elem[3*i+2].x*convexhull.elem[3*i+2].x );  
          _00.x = _00.y = _00.z = val*val2/12.0-pt.x*pt.x;

          val2 = 0.0;
          for( i = 0;  i < convexhull.num/3;  i++ ) val2+=vala.elem[i]*( 9.0*pta.elem[i].x*pta.elem[i].y + convexhull.elem[3*i].x*convexhull.elem[3*i].y + 
                                                          convexhull.elem[3*i+1].x*convexhull.elem[3*i+1].y + convexhull.elem[3*i+2].x*convexhull.elem[3*i+2].y );  
          _01.x = _01.y = _01.z = val*val2/12.0-pt.x*pt.y;

          val2 = 0.0;
          for( i = 0;  i < convexhull.num/3;  i++ ) val2+=vala.elem[i]*( 9.0*pta.elem[i].x*pta.elem[i].z + convexhull.elem[3*i].x*convexhull.elem[3*i].z + 
                                                          convexhull.elem[3*i+1].x*convexhull.elem[3*i+1].z + convexhull.elem[3*i+2].x*convexhull.elem[3*i+2].z );  
          _02.x = _02.y = _02.z = val*val2/12.0-pt.x*pt.z;

          _10 = _01;

          val2 = 0.0;
          for( i = 0;  i < convexhull.num/3;  i++ ) val2+=vala.elem[i]*( 9.0*pta.elem[i].y*pta.elem[i].y + convexhull.elem[3*i].y*convexhull.elem[3*i].y + 
                                                          convexhull.elem[3*i+1].y*convexhull.elem[3*i+1].y + convexhull.elem[3*i+2].y*convexhull.elem[3*i+2].y );  
          _11.x = _11.y = _11.z = val*val2/12.0-pt.y*pt.y;

          val2 = 0.0;
          for( i = 0;  i < convexhull.num/3;  i++ ) val2+=vala.elem[i]*( 9.0*pta.elem[i].y*pta.elem[i].z + convexhull.elem[3*i].y*convexhull.elem[3*i].z + 
                                                          convexhull.elem[3*i+1].y*convexhull.elem[3*i+1].z + convexhull.elem[3*i+2].y*convexhull.elem[3*i+2].z );  
          _12.x = _12.y = _12.z = val*val2/12.0-pt.y*pt.z;

          _20 = _02;

          _21 = _12;

          val2 = 0.0;
          for( i = 0;  i < convexhull.num/3;  i++ ) val2+=vala.elem[i]*( 9.0*pta.elem[i].z*pta.elem[i].z + convexhull.elem[3*i].z*convexhull.elem[3*i].z + 
                                                          convexhull.elem[3*i+1].z*convexhull.elem[3*i+1].z + convexhull.elem[3*i+2].z*convexhull.elem[3*i+2].z );  
          _22.x = _22.y = _22.z = val*val2/12.0-pt.z*pt.z;


          // vyp. eigenvectors...
      } // else pre 2d 1d 0d ...


      return oobb;
  }




  bspherE mesH::findbspherE( void ) {
      register DWORD i;
      valuE a;
      vectoR v;
      poinT pt;


      bsph.C = poinT( 0.0, 0.0, 0.0 );
      for( i = 0;  i < Va.num;  i++ ) bsph.C += Va.elem[i].v;
      bsph.C /= Va.num;

      bsph.r = -INFINITY;
      for( i = 0;  i < Va.num;  i++ ) {
          v = Va.elem[i].v-bsph.C;
          a = doT( v, v );
          if( a > bsph.r ) {
              bsph.r = a;
              pt = Va.elem[i].v;
          }
      }
      bsph.r = lengtH( pt-bsph.C );

      return bsph;
  }




  void mesH::findconvexhulL( void ) {
      pointarraY pta;

      pta.inserT( -1, poinT(), Va.num );
      for( register DWORD i = 0;  i < Va.num;  i++ ) pta.elem[i] = Va.elem[i].v;

      quickhull3D( &pta, &convexhull );
  }




  void mesH::findprojectedconvexhulL( camerA *C ) {
	  register DWORD i;
      pointarraY pta;

	  if( Va.num < 1000 ) {
	      pta.inserT( -1, poinT(), Va.num );
	      for( i = 0;  i < pta.num;  i++ ) pta.elem[i] = projecT( C, Va.elem[i].v );

	      quickhull2D( &pta, &projected_ch );
	  } else {
		  pta.inserT( -1, poinT(), 8 );
		  pta.elem[0] = poinT( aabb.min.x, aabb.min.y, aabb.min.z ); 
		  pta.elem[1] = poinT( aabb.max.x, aabb.min.y, aabb.min.z ); 
		  pta.elem[2] = poinT( aabb.min.x, aabb.max.y, aabb.min.z ); 
		  pta.elem[3] = poinT( aabb.min.x, aabb.min.y, aabb.max.z ); 
		  pta.elem[4] = poinT( aabb.max.x, aabb.max.y, aabb.min.z ); 
		  pta.elem[5] = poinT( aabb.max.x, aabb.min.y, aabb.max.z ); 
		  pta.elem[6] = poinT( aabb.min.x, aabb.max.y, aabb.max.z ); 
		  pta.elem[7] = poinT( aabb.max.x, aabb.max.y, aabb.max.z ); 
		  for( i = 0;  i < pta.num;  i++ ) pta.elem[i] = projecT( C, pta.elem[i] );

		  quickhull2D( &pta, &projected_ch );
	  }
  }




  void mesH::resetxforM( void ) {
      if( mata.num > 0 ) {
          register DWORD i;
          poinT pt;
	      matriX mat = mata.elem[0];


    	  mat._[3][0] = mat._[3][1] = mat._[3][2] = 0.0;
	      mat = transposE( inversE( mat ) );

    	  for( i = 0;  i < Va.num;  i++ ) {
	          Va.elem[i].v = multiplY( Va.elem[i].v, mata.elem[0] );
	          Va.elem[i].n = normalizE( multiplY( Va.elem[i].n, mat ) );		 
    	  }

	      for( i = 0;  i < Fa.num;  i++ ) {
		      Fa.elem[i].pl.n = normalizE( multiplY( Fa.elem[i].pl.n, mat ) );
              pt = Va.elem[Fa.elem[i].Via.elem[0]].v; 
    	      Fa.elem[i].pl.d = -doT( vectoR( pt.x, pt.y, pt.z ), Fa.elem[i].pl.n );
	      }

    	  mata.elem[0] = identitY();
      }
  }




  void meshexplodE( mesH *M ) {
	  register DWORD i, j;
	  verteX V;
	  facE F;
	  mesH M_;


	  M->copY( &M_ );
	  M_.Va.deletealL();
	  M_.Ea.deletealL();
	  M_.Fa.deletealL();

	  for( i = 0;  i < M->Fa.num;  i++ ) {
		  for( j = 0;  j < M->Fa.elem[i].Via.num;  j++ ) {
			  M->Va.elem[M->Fa.elem[i].Via.elem[j]].copY( &V );
			  V.Eia.deletealL();
			  V.Fia.deletealL();

			  M_.Va.inserT( -1, &V );
			  V.deletealL();
			  F.Via.inserT( -1, M_.Va.num-1 );
		  }

		  F.pl = M->Fa.elem[i].pl;
		  F.area = M->Fa.elem[i].area;
		  M_.Fa.inserT( -1, &F );
		  F.deletealL();
	  }

	  M->deletealL();
	  M_.copY( M );
	  M_.deletealL();
  }




  void meshdetacH( mesH *M, dwordarraY *dwa, mesH *M2, mesH *M3 ) {
	  register long i, j;
	  BOOL b;


	  M->copY( M2 );
	  M->copY( M3 );


	  // POLYGON
	  for( i = M2->Fa.num-1;  i >= 0;  i-- ) {
		  b = FALSE;
		  for( j = 0;  j < dwa->num;  j++ ) 
			  if( i == dwa->elem[j] ) {
				  b = TRUE;
				  j = dwa->num;
			  }

		  if( b ) M2->Fa.deletE( i );
	  }

	  // VERTEX
	  M2->Va.deletealL();

	  for( i = 0;  i < M2->Fa.num;  i++ ) 
		  for( j = 0;  j < M2->Fa.elem[i].Via.num;  j++ ) {
			  M2->Va.inserT( -1, &M->Va.elem[M2->Fa.elem[i].Via.elem[j]] );
			  M2->Fa.elem[i].Via.elem[j] = M2->Va.num-1;
		  }


	  // POLYGON
	  for( i = M3->Fa.num-1;  i >= 0;  i-- ) {
		  b = FALSE;
		  for( j = 0;  j < dwa->num;  j++ ) 
			  if( i == dwa->elem[j] ) {
				  b = TRUE;
				  j = dwa->num;
			  }

		  if( !b ) M3->Fa.deletE( i );
	  }

	  // VERTEX
	  M3->Va.deletealL();

	  for( i = 0;  i < M3->Fa.num;  i++ ) 
		  for( j = 0;  j < M3->Fa.elem[i].Via.num;  j++ ) {
			  M3->Va.inserT( -1, &M->Va.elem[M3->Fa.elem[i].Via.elem[j]] );
			  M3->Fa.elem[i].Via.elem[j] = M3->Va.num-1;
		  }
  }




  void meshtriangulatE( mesH *M ) {
	  register DWORD i, j;
	  facE F;


	  for( i = 0;  i < M->Fa.num;  i++ ) 
		  if( M->Fa.elem[i].Via.num > 3 ) {
			  for( j = 2;  j < M->Fa.elem[i].Via.num;  j++ ) {
				  F.deletealL();
		
				  F.Via.inserT( -1, M->Fa.elem[i].Via.elem[0], 3 );
				  F.Via.elem[F.Via.num-2] = M->Fa.elem[i].Via.elem[j-1];
				  F.Via.elem[F.Via.num-1] = M->Fa.elem[i].Via.elem[j];

				  M->Fa.inserT( -1, &F );

				  faceplanE( &M->Fa.elem[M->Fa.num-1], &M->Va ); 
				  faceareA( &M->Fa.elem[M->Fa.num-1], &M->Va ); 
			  }

			  M->Fa.deletE( i );
		  }
  }




  void transformvertexnormalS( mesH *M, matriX mat ) {
   	  mat._[3][0] = mat._[3][1] = mat._[3][2] = 0.0;
      mat = transposE( inversE( mat ) );

   	  for( register DWORD i = 0;  i < M->Va.num;  i++ ) 
          M->Va.elem[i].n = normalizE( multiplY( M->Va.elem[i].n, mat ) );		 
  }




  void calculateplaneS( mesH *M ) {
      for( register DWORD i = 0;  i < M->Fa.num;  i++ ) faceplanE( &M->Fa.elem[i], &M->Va );
  }




  void calculateareaS( mesH *M ) {
      for( register DWORD i = 0;  i < M->Fa.num;  i++ ) faceareA( &M->Fa.elem[i], &M->Va );
  }




  void calculatevertexnormalS( mesH *M, valuE thres ) {
	  register DWORD i, j, k, l, m;
	  dwordarraY dwa[4096];
	  boolarraY ba;
	  vertexarraY Va;
	  verteX V;


	  Va.inserT( -1, NULL, M->Va.num );

	  for( i = 0;  i < M->Va.num;  i++ ) 
		  for( j = 0;  j < M->Fa.num;  j++ ) 
			  for( k = 0;  k < M->Fa.elem[j].Via.num;  k++ ) 
				  if( M->Va.elem[i].v == M->Va.elem[M->Fa.elem[j].Via.elem[k]].v ) 
					  Va.elem[i].Fia.inserT( -1, j );

	  for( i = 0;  i < Va.num;  i++ ) {
		  ba.inserT( -1, FALSE, Va.elem[i].Fia.num );
	
		  l = 0;
		  for( j = 0;  j < Va.elem[i].Fia.num;  j++ ) 
			  if( !ba.elem[j] ) {
                  ba.elem[j] = TRUE;
				  dwa[l].inserT( -1, Va.elem[i].Fia.elem[j] );

				  for( k = j+1;  k < Va.elem[i].Fia.num;  k++ ) 
					  if( !ba.elem[k] && doT( M->Fa.elem[Va.elem[i].Fia.elem[j]].pl.n, M->Fa.elem[Va.elem[i].Fia.elem[k]].pl.n ) >= thres ) {
		                  ba.elem[k] = TRUE;
						  dwa[l].inserT( -1, Va.elem[i].Fia.elem[k] );
					  }
					   
				  l++; 
				  if( l > 4096 ) exit( EXIT_FAILURE );
			  }
		  
		  M->Va.elem[i].n = vectoR();
		  for( j = 0;  j < dwa[0].num;  j++ ) M->Va.elem[i].n+=M->Fa.elem[dwa[0].elem[j]].pl.n;
		  M->Va.elem[i].n = normalizE( M->Va.elem[i].n );

		  M->Va.elem[i].copY( &V );
		  V.Eia.deletealL();
		  V.Fia.deletealL();
		  for( j = 1;  j < l;  j++ ) {
			  M->Va.inserT( -1, &V );
  
			  M->Va.elem[M->Va.num-1].n = vectoR();
			  for( k = 0;  k < dwa[j].num;  k++ ) {
				  for( m = 0;  m < M->Fa.elem[dwa[j].elem[k]].Via.num;  m++ )
					  if( M->Fa.elem[dwa[j].elem[k]].Via.elem[m] == i ) {
						  M->Fa.elem[dwa[j].elem[k]].Via.elem[m] = M->Va.num-1;
						  m = M->Fa.elem[dwa[j].elem[k]].Via.num;
					  }

                  M->Va.elem[M->Va.num-1].n+=M->Fa.elem[dwa[j].elem[k]].pl.n;
			  }
			  M->Va.elem[M->Va.num-1].n = normalizE( M->Va.elem[M->Va.num-1].n );
		  }	

		  ba.deletealL();
		  for( j = 0;  j < l;  j++ ) dwa[j].deletealL();
	  }
  
	  V.deletealL();
	  Va.deletealL();
  }




  void calculateadjacencY( mesH *M ) {
   	  register DWORD i, j, k, l;
	  BOOL b;
	  edgE E;


	  for( i = 0;  i < M->Va.num;  i++ ) {
		  M->Va.elem[i].Eia.deletealL();
		  M->Va.elem[i].Fia.deletealL();
	  }

	  M->Ea.deletealL();

	  for( i = 0;  i < M->Fa.num;  i++ ) {
		  M->Fa.elem[i].Eia.deletealL();
		  M->Fa.elem[i].Fia.deletealL();
	  }


	  // EDGE - VIA, FIA;  POLYGON - EIA
 	  for( i = 0;  i < M->Fa.num;  i++ ) 
		  for( j = 0;  j < M->Fa.elem[i].Via.num;  j++ ) {
			  b = FALSE;
			  for( k = 0;  k < M->Ea.num;  k++ ) 
				  if( ( M->Va.elem[M->Fa.elem[i].Via.elem[j]].v == M->Va.elem[M->Ea.elem[k].Via.elem[0]].v && 
					  M->Va.elem[M->Fa.elem[i].Via.elem[( j+1 )%M->Fa.elem[i].Via.num]].v == M->Va.elem[M->Ea.elem[k].Via.elem[1]].v ) || 
					  ( M->Va.elem[M->Fa.elem[i].Via.elem[j]].v == M->Va.elem[M->Ea.elem[k].Via.elem[1]].v && 
					  M->Va.elem[M->Fa.elem[i].Via.elem[( j+1 )%M->Fa.elem[i].Via.num]].v == M->Va.elem[M->Ea.elem[k].Via.elem[0]].v ) ) {
					  b = TRUE;
					  l = k;
					  k = M->Ea.num;
				  }

			  if( b ) {
				  b = FALSE;
				  for( k = 0;  k < M->Ea.elem[l].Fia.num;  k++ ) 
					  if( M->Ea.elem[l].Fia.elem[k] == i ) {
					  	  b = TRUE; 
						  k = M->Ea.elem[l].Fia.num;
					  }
				  if( !b ) M->Ea.elem[l].Fia.inserT( -1, i );

				  b = FALSE;
				  for( k = 0;  k < M->Fa.elem[i].Eia.num;  k++ ) 
					  if( M->Fa.elem[i].Eia.elem[k] == l ) {
					  	  b = TRUE; 
						  k = M->Fa.elem[i].Eia.num;
					  }
				  if( !b ) M->Fa.elem[i].Eia.inserT( -1, l );
			  } else {
				  E.deletealL();
				  E.Via.inserT( -1, M->Fa.elem[i].Via.elem[j] );
				  E.Via.inserT( -1, M->Fa.elem[i].Via.elem[( j+1 )%M->Fa.elem[i].Via.num] );
				  E.Fia.inserT( -1, i );
				  M->Ea.inserT( -1, &E );
				  M->Fa.elem[i].Eia.inserT( -1, M->Ea.num-1 );
			  }
		  }

	  // VERTEX - EIA, FIA
	  for( i = 0;  i < M->Va.num;  i++ ) {
		  for( j = 0;  j < M->Ea.num;  j++ ) 
			  for( k = 0;  k < M->Ea.elem[j].Via.num;  k++ ) 
				  if( M->Va.elem[i].v == M->Va.elem[M->Ea.elem[j].Via.elem[k]].v ) 
					  M->Va.elem[i].Eia.inserT( -1, j );

		  for( j = 0;  j < M->Fa.num;  j++ ) 
			  for( k = 0;  k < M->Fa.elem[j].Via.num;  k++ ) 
				  if( M->Va.elem[i].v == M->Va.elem[M->Fa.elem[j].Via.elem[k]].v ) 
					  M->Va.elem[i].Fia.inserT( -1, j );
	  }

	  // EDGE - EIA
	  for( i = 0;  i < M->Ea.num;  i++ ) 
		  for( j = 0;  j < M->Ea.elem[i].Via.num;  j++ ) 
			  for( k = 0;  k < M->Va.elem[M->Ea.elem[i].Via.elem[j]].Eia.num;  k++ ) 
				  if( M->Va.elem[M->Ea.elem[i].Via.elem[j]].Eia.elem[k] != i ) M->Ea.elem[i].Eia.inserT( -1, M->Va.elem[M->Ea.elem[i].Via.elem[j]].Eia.elem[k] );

	  // POLYGON - FIA
	  for( i = 0;  i < M->Fa.num;  i++ ) 
		  for( j = 0;  j < M->Fa.elem[i].Eia.num;  j++ ) 
			  for( k = 0;  k < M->Ea.elem[M->Fa.elem[i].Eia.elem[j]].Fia.num;  k++ ) 
				  if( M->Ea.elem[M->Fa.elem[i].Eia.elem[j]].Fia.elem[k] != i ) M->Fa.elem[i].Fia.inserT( -1, M->Ea.elem[M->Fa.elem[i].Eia.elem[j]].Fia.elem[k] );
  }

  


  void meshraY_( bsptreenodE *bsptn, mesH *M, const raY& r, BOOL cull_faces, valuE *t, poinT *P, DWORD *Fi, DWORD *i, valuE *u, valuE *v ) {
      bsptreenodE *bsptnnear, *bsptnfar;
      valuE tray, tnear, tfar, ti, ui, vi;
      poinT Pi;
      register DWORD j, ii;


	  if( aabboxraY( aabboX( bsptn->aabb.min-vectoR( 0.5, 0.5, 0.5 ), bsptn->aabb.max+vectoR( 0.5, 0.5, 0.5 ) ), r, &tnear, &tfar ) && *t > tnear ) {
	      if( bsptn->left_node == NULL ) {  // leaf
		      for( j = 0;  j < bsptn->Ia.num;  j++ ) 
				  if( faceraY( &M->Fa.elem[bsptn->Ia.elem[j]], &M->Va, r, cull_faces, &ti, &ui, &vi, &Pi, &ii ) ) {
					  if( ti < *t ) {
				          *t = ti;
						  *P = Pi;
						  *u = ui;
						  *v = vi;
						  *Fi = bsptn->Ia.elem[j];
						  *i = ii;
		   			  }
				  }
		  } else {
			  if( bsptn->pl.n.x == -1.0 ) {
				  if( r.A.x < bsptn->pl.d ) {
					  bsptnnear = bsptn->left_node;  bsptnfar = bsptn->right_node;
				      if( r.q.x <= 0.0 ) tray = tfar+1.0; else tray = ( bsptn->pl.d-r.A.x )/r.q.x;
				  } else 
				  if( r.A.x == bsptn->pl.d ) {
					  bsptnnear = bsptn->left_node;  bsptnfar = bsptn->right_node;
				      if( r.q.x <= 0.0 ) tray = tfar+1.0; else tray = tnear-1.0;
				  } else {
					  bsptnnear = bsptn->right_node;  bsptnfar = bsptn->left_node;
				      if( r.q.x >= 0.0 ) tray = tfar+1.0; else tray = ( bsptn->pl.d-r.A.x )/r.q.x;
				  }
			  } else
			  if( bsptn->pl.n.y == -1.0 ) {
				  if( r.A.y < bsptn->pl.d ) {
					  bsptnnear = bsptn->left_node;  bsptnfar = bsptn->right_node;
				      if( r.q.y <= 0.0 ) tray = tfar+1.0; else tray = ( bsptn->pl.d-r.A.y )/r.q.y;
				  } else 
				  if( r.A.y == bsptn->pl.d ) {
					  bsptnnear = bsptn->left_node;  bsptnfar = bsptn->right_node;
					  if( r.q.y <= 0.0 ) tray = tfar+1.0; else tray = tnear-1.0;
				  } else {
					  bsptnnear = bsptn->right_node;  bsptnfar = bsptn->left_node;
				      if( r.q.y >= 0.0 ) tray = tfar+1.0; else tray = ( bsptn->pl.d-r.A.y )/r.q.y;
				  }
			  } else {
				  if( r.A.z < bsptn->pl.d ) {
					  bsptnnear = bsptn->left_node;  bsptnfar = bsptn->right_node;
				      if( r.q.z <= 0.0 ) tray = tfar+1.0; else tray = ( bsptn->pl.d-r.A.z )/r.q.z;
				  } else 
				  if( r.A.z == bsptn->pl.d ) {
					  bsptnnear = bsptn->left_node;  bsptnfar = bsptn->right_node;
					  if( r.q.z <= 0.0 ) tray = tfar+1.0; else tray = tnear-1.0;
				  } else {
					  bsptnnear = bsptn->right_node;  bsptnfar = bsptn->left_node;
				      if( r.q.z >= 0.0 ) tray = tfar+1.0; else tray = ( bsptn->pl.d-r.A.z )/r.q.z;
				  }
			  }

			  if( tray >= tfar ) meshraY_( bsptnnear, M, r, cull_faces, t, P, Fi, i, u, v ); else
			  if( tray <= tnear ) meshraY_( bsptnfar, M, r, cull_faces, t, P, Fi, i, u, v ); else {
				  meshraY_( bsptnfar, M, r, cull_faces, t, P, Fi, i, u, v );
				  meshraY_( bsptnnear, M, r, cull_faces, t, P, Fi, i, u, v );
			  }
		  }
	  }
  }




  BOOL meshraY( mesH *M, const raY& r, BOOL cull_faces, valuE *t, verteX *V, planE *pl, DWORD *Fi, DWORD *i ) {
      if( M ) {
		  valuE u, v, w;
		  poinT P;
		  raY r_;
		  matriX invmat;

		
		  if( M->inv_mata.num > 0 ) invmat = M->inv_mata.elem[0];

	      r_.A = multiplY( r.A, invmat );  
	      r_.q = multiplY( r.A+r.q, invmat )-r_.A;

		  *t = INFINITY;
		  meshraY_( &M->bsptroot, M, r_, cull_faces, t, &P, Fi, i, &u, &v );

		  if( *t != INFINITY ) {
			  verteX A, B, C;

		      A.n = M->Va.elem[M->Fa.elem[*Fi].Via.elem[0]].n;  
			  A.t = M->Va.elem[M->Fa.elem[*Fi].Via.elem[0]].t;  
			  A.c = M->Va.elem[M->Fa.elem[*Fi].Via.elem[0]].c;  
			  B.n = M->Va.elem[M->Fa.elem[*Fi].Via.elem[*i-1]].n;  
		      B.t = M->Va.elem[M->Fa.elem[*Fi].Via.elem[*i-1]].t;  
			  B.c = M->Va.elem[M->Fa.elem[*Fi].Via.elem[*i-1]].c;  
			  C.n = M->Va.elem[M->Fa.elem[*Fi].Via.elem[*i]].n;  
		      C.t = M->Va.elem[M->Fa.elem[*Fi].Via.elem[*i]].t;  
			  C.c = M->Va.elem[M->Fa.elem[*Fi].Via.elem[*i]].c;  

			  w = 1.0-( u+v );
					
			  V->v = multiplY( P, M->mata.elem[0] );
			  V->n = A.n*w+B.n*u+C.n*v;  
			  invmat = M->mata.elem[0];
			  invmat._[3][0] = invmat._[3][1] = invmat._[3][2] = 0.0;
			  invmat = transposE( inversE( invmat ) );
			  V->n = normalizE( multiplY( V->n, invmat ) );		 
			  V->t = A.t*w+B.t*u+C.t*v;  
			  V->c = A.c*w+B.c*u+C.c*v;  
	
			  pl->n = normalizE( multiplY( M->Fa.elem[*Fi].pl.n, invmat ) );
			  pl->d = -doT( vectoR( V->v.x, V->v.y, V->v.z ), pl->n );

			  return TRUE;
		  }
	  }

	  return FALSE;
  }




  void meshplanE( mesH *M, bsptreenodE *bsptn, const planE& pl, dwordarraY *dwa1, dwordarraY *dwa2, dwordarraY *dwa3 ) {
	  register DWORD i, j;
	  BOOL b;

      if( aabboxplanE( bsptn->aabb, pl ) == 1 ) {
		  if( bsptn->left_node == NULL && bsptn->right_node == NULL ) {
			  for( i = 0;  i < bsptn->Ia.num;  i++ ) {
				  b = FALSE;
				  for( j = 0;  j < dwa1->num;  j++ ) 
					  if( bsptn->Ia.elem[i] == dwa1->elem[j] ) {
						  b = TRUE;
						  j = dwa1->num;
					  }

				  if( !b ) dwa1->inserT( -1, bsptn->Ia.elem[i] );
			  }
		  } else { 
			  meshplanE( M, bsptn->left_node, pl, dwa1, dwa2, dwa3 );
			  meshplanE( M, bsptn->right_node, pl, dwa1, dwa2, dwa3 );
		  }
	  } else 
      if( aabboxplanE( bsptn->aabb, pl ) == 0 ) {
		  if( bsptn->left_node == NULL && bsptn->right_node == NULL ) {
			  for( i = 0;  i < bsptn->Ia.num;  i++ ) 
				  if( faceplanE( &M->Fa.elem[bsptn->Ia.elem[i]], &M->Va, pl ) ) {
					  b = FALSE;
					  for( j = 0;  j < dwa2->num;  j++ ) 
						  if( bsptn->Ia.elem[i] == dwa2->elem[j] ) {
							  b = TRUE;
							  j = dwa2->num;
						  }

					  if( !b ) dwa2->inserT( -1, bsptn->Ia.elem[i] );
				  }
		  } else { 
			  meshplanE( M, bsptn->left_node, pl, dwa1, dwa2, dwa3 );
			  meshplanE( M, bsptn->right_node, pl, dwa1, dwa2, dwa3 );
		  }
	  } else {
		  if( bsptn->left_node == NULL && bsptn->right_node == NULL ) {
			  for( i = 0;  i < bsptn->Ia.num;  i++ ) {
				  b = FALSE;
				  for( j = 0;  j < dwa3->num;  j++ ) 
					  if( bsptn->Ia.elem[i] == dwa3->elem[j] ) {
						  b = TRUE;
						  j = dwa3->num;
					  }

				  if( !b ) dwa3->inserT( -1, bsptn->Ia.elem[i] );
			  }
		  } else { 
			  meshplanE( M, bsptn->left_node, pl, dwa1, dwa2, dwa3 );
			  meshplanE( M, bsptn->right_node, pl, dwa1, dwa2, dwa3 );
		  }
	  }
  }




  BOOL meshplanE( mesH *M, const planE& pl, dwordarraY *dwa1, dwordarraY *dwa2, dwordarraY *dwa3 ) {
	  dwa1->deletealL();  dwa2->deletealL();  dwa3->deletealL();
      meshplanE( M, &M->bsptroot, pl, dwa1, dwa2, dwa3 );
	  if( dwa2->num > 0 ) return TRUE; else return FALSE;
  }




  void meshaabboX( mesH *M, bsptreenodE *bsptn, const aabboX& aabb, dwordarraY *dwa ) {
      if( aabboxaabboX( bsptn->aabb, aabb ) ) {
		  if( bsptn->left_node == NULL && bsptn->right_node == NULL ) {
			  register DWORD i, j;
			  BOOL b;

			  for( i = 0;  i < bsptn->Ia.num;  i++ ) 
				  if( faceaabboX( &M->Fa.elem[bsptn->Ia.elem[i]], &M->Va, aabb ) ) {
					  b = FALSE;
					  for( j = 0;  j < dwa->num;  j++ ) 
						  if( bsptn->Ia.elem[i] == dwa->elem[j] ) {
							  b = TRUE;
							  j = dwa->num;
						  }

					  if( !b ) dwa->inserT( -1, bsptn->Ia.elem[i] );
				  }
		  } else { 
			  meshaabboX( M, bsptn->left_node, aabb, dwa );
			  meshaabboX( M, bsptn->right_node, aabb, dwa );
		  }
	  } 
  }




  BOOL meshaabboX( mesH *M, const aabboX& aabb, dwordarraY *dwa ) {
	  dwa->deletealL();
      meshaabboX( M, &M->bsptroot, aabb, dwa );
	  if( dwa->num > 0 ) return TRUE; else return FALSE;
  }



  
  void meshbspherE( mesH *M, bsptreenodE *bsptn, const bspherE& bsph, dwordarraY *dwa ) {
      if( bsphereaabboX( bsph, bsptn->aabb ) ) {
		  if( bsptn->left_node == NULL && bsptn->right_node == NULL ) {
			  register DWORD i, j;
			  BOOL b;

			  for( i = 0;  i < bsptn->Ia.num;  i++ ) 
				  if( facebspherE( &M->Fa.elem[bsptn->Ia.elem[i]], &M->Va, bsph ) ) {
					  b = FALSE;
					  for( j = 0;  j < dwa->num;  j++ ) 
						  if( bsptn->Ia.elem[i] == dwa->elem[j] ) {
							  b = TRUE;
							  j = dwa->num;
						  }

					  if( !b ) dwa->inserT( -1, bsptn->Ia.elem[i] );
				  }
		  } else { 
			  meshbspherE( M, bsptn->left_node, bsph, dwa );
			  meshbspherE( M, bsptn->right_node, bsph, dwa );
		  }
	  } 
  }




  BOOL meshbspherE( mesH *M, const bspherE& bsph, dwordarraY *dwa ) {
	  dwa->deletealL();
      meshbspherE( M, &M->bsptroot, bsph, dwa );
	  if( dwa->num > 0 ) return TRUE; else return FALSE;
  }
	



  void meshmesH( mesH *M1, bsptreenodE *bsptn1, mesH *M2, bsptreenodE *bsptn2, dwordarraY *dwa ) {
      if( aabboxaabboX( bsptn1->aabb, bsptn2->aabb ) ) {
		  if( bsptn1->left_node == NULL && bsptn1->right_node == NULL ) {
			  if( bsptn2->left_node == NULL && bsptn2->right_node == NULL ) {
				  for( register DWORD i = 0;  i < bsptn1->Ia.num;  i++ )
					  for( register DWORD j = 0;  j < bsptn2->Ia.num;  j++ )
						  if( triangletrianglE( &M1->Fa.elem[bsptn1->Ia.elem[i]], &M1->Va, &M2->Fa.elem[bsptn2->Ia.elem[j]], &M2->Va ) ) {
							  dwa->inserT( -1, bsptn1->Ia.elem[i], 2 );
							  dwa->elem[dwa->num-1] = bsptn2->Ia.elem[j];
						  }
			  } else {
				  meshmesH( M1, bsptn1, M2, bsptn2->left_node, dwa );
				  meshmesH( M1, bsptn1, M2, bsptn2->right_node, dwa );
			  }
		  } else {
			  meshmesH( M1, bsptn1->left_node, M2, bsptn2, dwa );
			  meshmesH( M1, bsptn1->right_node, M2, bsptn2, dwa );
		  }
	  }
  }




  BOOL meshmesH( mesH *M1, mesH *M2, dwordarraY *dwa ) {
	  dwa->deletealL();
      meshmesH( M1, &M1->bsptroot, M2, &M2->bsptroot, dwa );
	  if( dwa->num > 0 ) return TRUE; else return FALSE;
  }




  BOOL loadasC( char filename[512], mesH *M ) {
	  char str[1024], *endptr, str2[1024], *endptr2;
	  DWORD vertices, faces, *smoothing;
      FILE *file;
	  fpos_t pos;
	  register long i, j;
	  register DWORD k, l, m;
	  dwordarraY dwa[4096];
	  boolarraY ba;
	  vertexarraY Va;
	  vectoR u, n;
      verteX V;
	  facE F;
	  

	  M->deletealL();


	  if( !( file = fopen( filename, "rt" ) ) ) return FALSE;

	  while( !feof( file ) ) {
		  fscanf( file, "%s", str );

		  if( strcmp( str, "Vertices:" ) == 0 ) {
			  fscanf( file, "%s", str );
			  vertices = strtol( str, &endptr, 10 );
		  } else
		  if( strcmp( str, "Faces:" ) == 0 ) {
			  fscanf( file, "%s", str );
			  faces = strtol( str, &endptr, 10 );

			  smoothing = NULL;
			  smoothing = (DWORD*)malloc( faces*sizeof( DWORD ) );
  			  if( smoothing == NULL ) exit( EXIT_FAILURE );
		  } else
		  if( strcmp( str, "Vertex" ) == 0 ) {
			  fscanf( file, "%s", str );
   	
			  if( strcmp( str, "list:" ) == 0 ) {
				  for( i = 0;  i < vertices;  i++ ) {
					  fscanf( file, "%s", str );
					  fscanf( file, "%s", str );

					  fscanf( file, "%s", str );
					  fscanf( file, "%s", str );
					  for( j = 0;  j < strlen( str );  j++ ) if( str[j] == ',' ) str[j] = '.';
         			  V.v.x = strtod( str, &endptr );

					  fscanf( file, "%s", str );
					  fscanf( file, "%s", str );
					  for( j = 0;  j < strlen( str );  j++ ) if( str[j] == ',' ) str[j] = '.';
         			  V.v.y = strtod( str, &endptr );
					  
					  fscanf( file, "%s", str );
					  fscanf( file, "%s", str );
					  for( j = 0;  j < strlen( str );  j++ ) if( str[j] == ',' ) str[j] = '.';
         			  V.v.z = strtod( str, &endptr );

					  M->Va.inserT( -1, &V );
				  }
			  } 
		  } else
		  if( strcmp( str, "Face" ) == 0 ) {
			  fscanf( file, "%s", str );
   	
			  if( strcmp( str, "list:" ) == 0 ) {
				  l = 0;

				  for( i = 0;  i < faces;  i++ ) {
					  fscanf( file, "%s", str );
					  fscanf( file, "%s", str );

					  for( j = 0;  j < 3;  j++ ) {
						  fscanf( file, "%s", str );
						  str[0] = *strrev( &str[0] );
						  strncpy( str2, str, strlen( str )-2 );
						  str2[strlen( str )-2] = '\x0';
						  str2[0] = *strrev( &str2[0] );
						  k = strtol( str2, &endptr2, 10 );
						  F.Via.inserT( -1, k );
					  }

					  fscanf( file, "%s", str );
					  fscanf( file, "%s", str );
					  fscanf( file, "%s", str );

					  fgetpos( file, &pos );
					  fscanf( file, "%s", str );
					  if( strcmp( str, "Smoothing:" ) == 0 ) {
						  smoothing[l] = j = 0;
						  do {
							  if( fscanf( file, "%d", &j ) < 1 ) break;
  							  smoothing[l]|=j;
						  } while( fscanf( file, "," ) == 0 );
					  } else fsetpos( file, &pos );

					  M->Fa.inserT( -1, &F );
					  F.deletealL();

					  l++;
				  }
			  } 
		  } 
	  }
      
	  fclose( file );  


	  M->findaabboX();
	  calculateplaneS( M );


      Va.inserT( -1, NULL, M->Va.num );

      for( i = 0;  i < M->Fa.num;  i++ ) 
	      for( j = 0;  j < M->Fa.elem[i].Via.num;  j++ ) 
			  Va.elem[M->Fa.elem[i].Via.elem[j]].Fia.inserT( -1, i ); 

	  for( i = 0;  i < Va.num;  i++ ) {
		  ba.inserT( -1, FALSE, Va.elem[i].Fia.num );
	
		  l = 0;
		  for( j = 0;  j < Va.elem[i].Fia.num;  j++ ) 
			  if( !ba.elem[j] ) {
                  ba.elem[j] = TRUE;
				  dwa[l].inserT( -1, Va.elem[i].Fia.elem[j] );

				  for( k = j+1;  k < Va.elem[i].Fia.num;  k++ ) 
					  if( !ba.elem[k] && ( smoothing[Va.elem[i].Fia.elem[j]] & smoothing[Va.elem[i].Fia.elem[k]] ) > 0 ) {
		                  ba.elem[k] = TRUE;
						  dwa[l].inserT( -1, Va.elem[i].Fia.elem[k] );
					  }
					   
				  l++; 
				  if( l > 4096 ) exit( EXIT_FAILURE );
			  }
		  
		  M->Va.elem[i].n = vectoR();
		  for( j = 0;  j < dwa[0].num;  j++ ) M->Va.elem[i].n+=M->Fa.elem[dwa[0].elem[j]].pl.n;
		  M->Va.elem[i].n = normalizE( M->Va.elem[i].n );

		  M->Va.elem[i].copY( &V );
		  V.Eia.deletealL();
		  V.Fia.deletealL();
		  for( j = 1;  j < l;  j++ ) {
			  M->Va.inserT( -1, &V );
  
			  M->Va.elem[M->Va.num-1].n = vectoR();
			  for( k = 0;  k < dwa[j].num;  k++ ) {
				  for( m = 0;  m < M->Fa.elem[dwa[j].elem[k]].Via.num;  m++ )
					  if( M->Fa.elem[dwa[j].elem[k]].Via.elem[m] == i ) {
						  M->Fa.elem[dwa[j].elem[k]].Via.elem[m] = M->Va.num-1;
						  m = M->Fa.elem[dwa[j].elem[k]].Via.num;
					  }

                  M->Va.elem[M->Va.num-1].n+=M->Fa.elem[dwa[j].elem[k]].pl.n;
			  }
			  M->Va.elem[M->Va.num-1].n = normalizE( M->Va.elem[M->Va.num-1].n );
		  }	

		  ba.deletealL();
		  for( j = 0;  j < l;  j++ ) dwa[j].deletealL();
	  }
  
	  V.deletealL();
	  Va.deletealL();


      // eliminate degenerated trinagles
      for( i = M->Fa.num-1;  i >= 0;  i-- ) 
          if( faceareA( &M->Fa.elem[i], &M->Va ) < EPSILON ) M->Fa.deletE( i );
      

	  return TRUE;
  }








  // MESHARRAY
  class mesharraY: public arraY_<mesH> {};


  // LPMESH
  typedef mesH* lpmesH;


  // LPMESHARRAY
  class lpmesharraY: public arraY__<lpmesH> {};
