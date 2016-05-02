
  // VERTEX         
  class verteX {
      public:
          dwordarraY Eia, Fia; 
          poinT v, t, t2;
          vectoR n; 
		  coloR c;


          verteX( void ) { reseT(); };
          ~verteX( void ) { deletealL(); };
          
          void reseT( void );
          void deletealL( void );
          void copY( verteX *V );
  };








  void verteX::reseT( void ) {
      Eia.reseT();
      Fia.reseT();
      v = t = t2 = poinT();
      n = vectoR();
	  c = coloR();
  }

                  


  void verteX::deletealL( void ) {
      Eia.deletealL();
      Fia.deletealL();

      reseT();
  }




  void verteX::copY( verteX *V ) {
      if( V ) {
          V->deletealL();

          Eia.copY( &V->Eia ); 
          Fia.copY( &V->Fia ); 
	      V->v = v;
	      V->t = t;
	      V->t2 = t2;
	      V->n = n;
	      V->c = c;
      }
  }


  



						 

  // VERTEXARRAY
  class vertexarraY: public arraY_<verteX> {};


  // LPVERTEX
  typedef verteX* lpverteX;


  // LPVERTEXARRAY
  class lpvertexarraY: public arraY__<lpverteX> {};
	