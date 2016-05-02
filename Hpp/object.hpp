
  // OBJECT TEMPLATE      
  class objecT {
      private:


      public:
		  poinT com;  // center of mass
          aabboX aabb;
          oobboX oobb;
          bspherE bsph;
		  matrixarraY mata, inv_mata;
		  materialarraY mtrla;
          pointarraY convexhull, projected_ch;


          objecT( void ) { reseT(); };
          ~objecT( void ) { deletealL(); };
          
          virtual void reseT( void );
          virtual void deletealL( void );
          virtual void copY( objecT *O );

		  virtual poinT calculatecenterofmasS( void ) = 0; // pure virtual function
		  virtual aabboX findaabboX( void ) = 0;
		  virtual oobboX findoobboX( void ) = 0;
		  virtual bspherE findbspherE( void ) = 0;
		  virtual void findconvexhulL( void ) = 0;
		  virtual void findprojectedconvexhulL( camerA *C ) = 0;
		  virtual void resetxforM( void ) = 0;
  };








  void objecT::reseT( void ) {
	  com = poinT();
      aabb = aabboX();
      oobb = oobboX();
      bsph = bspherE();
	  mata.reseT();
	  inv_mata.reseT();
	  mtrla.reseT();
      convexhull.reseT();
	  projected_ch.reseT();
  }




  void objecT::deletealL( void ) {
      mata.deletealL();
      inv_mata.deletealL();
      mtrla.deletealL();
      convexhull.deletealL();
      projected_ch.deletealL();

      reseT();
  }




  void objecT::copY( objecT *O ) {
      if( O ) {
          O->deletealL();

		  O->com = com;
          O->aabb = aabb; 
          O->oobb = oobb; 
          O->bsph = bsph; 
          mata.copY( &O->mata );
          inv_mata.copY( &O->inv_mata );
          mtrla.copY( &O->mtrla );
          convexhull.copY( &O->convexhull );
          projected_ch.copY( &O->projected_ch );
      }
  }








  // OBJECTARRAY
  class objectarraY: public arraY_<objecT> {};


  // LPOBJECT
  typedef objecT* lpobjecT;


  // LPOBJECTARRAY
  class lpobjectarraY: public arraY__<lpobjecT> {};
