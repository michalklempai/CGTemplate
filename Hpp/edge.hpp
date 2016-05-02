
  // EDGE         
  class edgE {
      public:
          dwordarraY Via, Eia, Fia; 


          edgE( void ) { reseT(); };
          ~edgE( void ) { deletealL(); };
          
          void reseT( void );
          void deletealL( void );
          void copY( edgE *E );
  };








  void edgE::reseT( void ) {
      Via.reseT();
      Eia.reseT();
      Fia.reseT();
  }




  void edgE::deletealL( void ) {
      Via.deletealL();
      Eia.deletealL();
      Fia.deletealL();

      reseT();
  }




  void edgE::copY( edgE *E ) {
      if( E ) {
          E->deletealL();

          Via.copY( &E->Via ); 
          Eia.copY( &E->Eia ); 
          Fia.copY( &E->Fia ); 
      }
  }

  






  // EDGEARRAY
  class edgearraY: public arraY_<edgE> {};


  // LPEDGE
  typedef edgE* lpedgE;


  // LPEDGEARRAY
  class lpedgearraY: public arraY__<lpedgE> {};
