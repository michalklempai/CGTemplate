
  // MAP
  class maP {
      public:
		  poinT offset, tiling;
		  texturE<BYTE> *lpT;


          maP( void ) { reseT(); };
          ~maP( void ) { deletealL(); };
          
          void reseT( void );
          void deletealL( void );
          void copY( maP *map );
  };








  void maP::reseT( void ) {
      offset = tiling = poinT();
	  lpT = NULL;
  }




  void maP::deletealL( void ) {

      reseT();
  }




  void maP::copY( maP *map ) {
      if( map ) {
          map->deletealL();

    	  map->offset = offset;
	      map->tiling = tiling;
    	  map->lpT = lpT;
      }
  }


  




	 
  // MAPARRAY
  class maparraY: public arraY_<maP> {};


  // LPMAP
  typedef maP* lpmaP;


  // LPMAPARRAY
  class lpmaparraY: public arraY__<lpmaP> {};
