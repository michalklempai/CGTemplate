
  // SCENE       
  class scenE {
      private:
          void createbsptreE( bsptreenodE *bsptn_, DWORD depth );
		  void releasebsptreE( bsptreenodE *bsptn_ );


      public:
		  lpobjectarraY lpobja;
	      lightarraY La;
	      texturearraY<BYTE> Ta;
          aabboX aabb;
          oobboX oobb;
          bspherE bsph;
          bsptreenodE bsptroot;
          lpbsptreenodearraY lpbsptna;
          vectorarraY convexhull;


          scenE( void ) { reseT(); };
          ~scenE( void ) { releasealL(); };

          void reseT( void );
          void deletealL( void );
          void releasealL( void );
          void copY( scenE *S );

          void createbsptreE( DWORD maxdepth = 16 );
          void releasebsptreE( void );
  };


  void sceneaabboX( scenE *S );
  BOOL sceneraY( scenE *S, arraY_<pointarraY> *proj_off_ch, long k, long l, const raY& r, DWORD Li, BOOL cull_faces, valuE *t, verteX *V, planE *pl, DWORD *Fi, DWORD *edgi, DWORD *obji );






  void scenE::reseT( void ) {
	  lpobja.reseT();
      La.reseT();
      Ta.reseT();
      aabb = aabboX();
      oobb = oobboX();
      bsph = bspherE();
      bsptroot.reseT();
      lpbsptna.reseT();
      convexhull.reseT();
  }




  void scenE::deletealL( void ) {
	  lpobja.deletealL();
      La.deletealL();
      Ta.deletealL();
      releasebsptreE();
      lpbsptna.deletealL();
      convexhull.deletealL();

      reseT();
  }




  void scenE::releasealL( void ) {
	  lpobja.releasealL();
      La.deletealL();
      Ta.deletealL();
      releasebsptreE();
      lpbsptna.deletealL();
      convexhull.deletealL();

      reseT();
  }




  void scenE::copY( scenE *S ) {
      if( S ) {
          S->releasealL();

		  lpobja.copY( &S->lpobja );
          La.copY( &S->La ); 
          Ta.copY( &S->Ta ); 
          S->aabb = aabb; 
          S->oobb = oobb; 
          S->bsph = bsph; 
          convexhull.copY( &S->convexhull );
      }
  }




  void scenE::createbsptreE( bsptreenodE *bsptn_, DWORD depth ) {
      if( depth > 0 && bsptn_->Ia.num > 32 ) {
	      bsptn_->left_node = new bsptreenodE;
          bsptn_->right_node = new bsptreenodE;
          bsptn_->left_node->reseT();  
          bsptn_->right_node->reseT();
				

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
			  if( aabboxplanE( lpobja.elem[bsptn_->Ia.elem[i]]->aabb, bsptn_->pl ) >= 0 ) 
                  bsptn_->left_node->Ia.inserT( -1, bsptn_->Ia.elem[i] );

			  if( aabboxplanE( lpobja.elem[bsptn_->Ia.elem[i]]->aabb, bsptn_->pl ) <= 0 ) 
                  bsptn_->right_node->Ia.inserT( -1, bsptn_->Ia.elem[i] );
		  }

		  bsptn_->Ia.deletealL();

          depth--;
          createbsptreE( bsptn_->left_node, depth );
          createbsptreE( bsptn_->right_node, depth );
	  } 
  }




  void scenE::releasebsptreE( bsptreenodE *bsptn_ ) {
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




  void scenE::createbsptreE( DWORD maxdepth ) {
	  releasebsptreE();

      bsptroot.Ia.inserT( -1, 0, lpobja.num ); 
      for( register DWORD i = 1;  i < lpobja.num;  i++ ) bsptroot.Ia.elem[i] = i;
      
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

      createbsptreE( &bsptroot, maxdepth );
  }




  void scenE::releasebsptreE( void ) {
      releasebsptreE( &bsptroot );  

      bsptroot.reseT();
  }




  void sceneaabboX( scenE *S ) {
	  register DWORD i;

      S->aabb.min = poinT( INFINITY, INFINITY, INFINITY );  
      S->aabb.max = poinT( -INFINITY, -INFINITY, -INFINITY );

      for( i = 0;  i < S->lpobja.num;  i++ ) {
          if( S->lpobja.elem[i]->aabb.min.x < S->aabb.min.x ) S->aabb.min.x = S->lpobja.elem[i]->aabb.min.x;
		  if( S->lpobja.elem[i]->aabb.min.y < S->aabb.min.y ) S->aabb.min.y = S->lpobja.elem[i]->aabb.min.y; 
	      if( S->lpobja.elem[i]->aabb.min.z < S->aabb.min.z ) S->aabb.min.z = S->lpobja.elem[i]->aabb.min.z; 
	      if( S->lpobja.elem[i]->aabb.max.x > S->aabb.max.x ) S->aabb.max.x = S->lpobja.elem[i]->aabb.max.x; 	  
   	      if( S->lpobja.elem[i]->aabb.max.y > S->aabb.max.y ) S->aabb.max.y = S->lpobja.elem[i]->aabb.max.y; 	  
		  if( S->lpobja.elem[i]->aabb.max.z > S->aabb.max.z ) S->aabb.max.z = S->lpobja.elem[i]->aabb.max.z; 	  
	  }
  }

  
  

  BOOL sceneraY( scenE *S, arraY_<pointarraY> *proj_off_ch, long k, long l, const raY& r, DWORD Li, BOOL cull_faces, valuE *t, verteX *V, planE *pl, DWORD *Fi, DWORD *edgi, DWORD *obji ) {
	  if( S && aabboxraY( S->aabb, r ) ) 
		  if( S->lpobja.num < /*32*/LONG_MAX || proj_off_ch != NULL ) {
			  valuE ti;
			  poinT pt;
			  verteX Vi;
			  planE pli;
			  register DWORD j, ii;
			  DWORD Fii;

				
			  *t = INFINITY;
			  for( j = 0;  j < S->lpobja.num;  j++ ) {
				  if( ( proj_off_ch == NULL && bsphereraY( S->lpobja.elem[j]->bsph, r ) ) || ( proj_off_ch != NULL && j >= proj_off_ch->num && bsphereraY( S->lpobja.elem[j]->bsph, r ) ) || ( proj_off_ch != NULL && j < proj_off_ch->num && pointinpolygoN( poinT( k, l ), &proj_off_ch->elem[j] ) ) ) {
					  if( typeid( *S->lpobja.elem[j] ) == typeid( mesH ) ) {
						  if( meshraY( lpmesH(S->lpobja.elem[j]), r, cull_faces, &ti, &Vi, &pli, &Fii, &ii ) ) {
							  if( ti < *t ) {
							      *t = ti;
								  *V = Vi;
								  *pl = pli;
								  *Fi = Fii;
								  *edgi = ii;
								  *obji = j;
							  }
						  }
					  } else
					  if( typeid( *S->lpobja.elem[j] ) == typeid( beziersurfacE ) ) {
						  if( beziersurfaceraY( lpbeziersurfacE(S->lpobja.elem[j]), r, &ti, &Vi ) ) {
							  if( ti < *t ) {
								  *t = ti;
								  *V = Vi;
								  *pl = planE();
								  *Fi = -1;
								  *edgi = -1;
								  *obji = j;
							  }
						  }
					  }
				  }
			  }

			  if( *t != INFINITY ) return TRUE; 
		  } else {
/*		      bsptreenodE *bsptn, *bsptnnear, *bsptnfar;
			  valuE tray, tnear, tfar, ti;
			  verteX Vi;
			  planE pli;
			  register DWORD j, ii;
			  DWORD Fii;

		
			  *t = INFINITY;
			  S->lpbsptna.num = 1;
			  S->lpbsptna.inserT( -1, &S->bsptroot );
			  do {
                  bsptn = S->lpbsptna.elem[S->lpbsptna.num-1];
		          S->lpbsptna.deletE( -1 );
				
				  if( aabboxraY( bsptn->aabb, r, &tnear, &tfar ) && *t > tnear ) {
					  if( bsptn->left_node == NULL ) {
						  for( j = 0;  j < bsptn->Ia.num;  j++ ) {
							  if( bsphereraY( S->Ma.elem[bsptn->Ia.elem[j]].bsph, r ) )
								  if( meshraY( &S->Ma.elem[bsptn->Ia.elem[j]], r, cull_faces, &ti, &Vi, &pli, &Fii, &ii ) ) 
									  if( ti < *t ) {
										  *t = ti;
										  *V = Vi;
										  *pl = pli;
										  *Fi = Fii;
										  *i = ii;
										  *Mi = bsptn->Ia.elem[j];
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

						  if( tray >= tfar ) S->lpbsptna.inserT( -1, bsptnnear ); else
						  if( tray <= tnear ) S->lpbsptna.inserT( -1, bsptnfar ); else {
							  S->lpbsptna.inserT( -1, bsptnfar, 2 );
							  S->lpbsptna.elem[S->lpbsptna.num-1] = bsptnnear;
						  }
					  }
				  }
			  } while( S->lpbsptna.num > 1 );

			  if( *t != INFINITY ) return TRUE; */

			  return FALSE; //
		  }

	  return FALSE;
  }








  // SCENEARRAY
  class scenearraY: public arraY_<scenE> {};


  // LPSCENE
  typedef scenE* lpscenE;


  // LPSCENEARRAY
  class lpscenearraY: public arraY__<lpscenE> {};
		