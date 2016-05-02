
  #undef AMBIENT_LIGHT
  #undef DIRECTIONAL_LIGHT
  #undef POINT_LIGHT 
  #undef OMNI_LIGHT 
  #undef OMNIDIRECTIONAL_LIGHT 
  #undef SPOT_LIGHT
  #undef WARN_LIGHT
  #undef HDRI_LIGHT

  #define AMBIENT_LIGHT 0
  #define DIRECTIONAL_LIGHT 1
  #define POINT_LIGHT 2
  #define OMNI_LIGHT 2
  #define OMNIDIRECTIONAL_LIGHT 2
  #define SPOT_LIGHT 4
  #define WARN_LIGHT 4
  #define HDRI_LIGHT 5








  // LIGHT         
  class lighT {
      public:
          DWORD type;
          poinT pos;
          vectoR dir; 
		  coloR color;
		  valuE innrng, outrng, hotspot, falloff;
		  matriX mat;


          lighT( void ) { reseT(); };
		  lighT( const coloR& color );
		  lighT( const vectoR& dir, const coloR& color );
		  lighT( const poinT& pos, const coloR& color, valuE innrng, valuE outrng );
		  lighT( const poinT& pos, const vectoR& dir, const coloR& color, valuE innrng, valuE outrng, valuE hotspot, valuE falloff );
          ~lighT( void ) { deletealL(); };

          void reseT( void );
          void deletealL( void );
          void copY( lighT *L );
  };


  void resetxforM( lighT *L );






  lighT::lighT( const coloR& color ) {
	  reseT();

	  type = AMBIENT_LIGHT;
	  this->color = color;
  }




  lighT::lighT( const vectoR& dir, const coloR& color ) {
	  reseT();

	  type = DIRECTIONAL_LIGHT;
      this->dir = dir;
	  this->color = color;
  }




  lighT::lighT( const poinT& pos, const coloR& color, valuE innrng, valuE outrng ) {
	  reseT();

	  type = POINT_LIGHT;
      this->pos = pos;
	  this->color = color;
	  this->innrng = innrng;
	  this->outrng = outrng;
  }




  lighT::lighT( const poinT& pos, const vectoR& dir, const coloR& color, valuE innrng, valuE outrng, valuE hotspot, valuE falloff ) {
	  reseT();

	  type = SPOT_LIGHT;
      this->pos = pos;
      this->dir = dir;
	  this->color = color;
	  this->innrng = innrng;
	  this->outrng = outrng;
	  this->hotspot = hotspot;
	  this->falloff = falloff;
  }




  void lighT::reseT( void ) {
	  type = AMBIENT_LIGHT;
      pos = poinT();
      dir = vectoR();
	  color = coloR();
	  innrng = outrng = hotspot = falloff = 0.0;
	  mat = matriX();
  }




  void lighT::deletealL( void ) {

      reseT();
  }




  void lighT::copY( lighT *L ) {
      if( L ) {
          L->deletealL();

    	  L->type = type;
	      L->pos = pos;
    	  L->dir = dir;
	      L->color = color;
    	  L->innrng = innrng;
	      L->outrng = outrng;
    	  L->hotspot = hotspot;
	      L->falloff = falloff;
          L->mat = mat;
      }
  }




  void resetxforM( lighT *L ) {
      poinT pt, pt2;

      pt = multiplY( L->pos, L->mat );
      pt2 = multiplY( L->pos+L->dir, L->mat );
      L->dir = normalizE( pt2-pt );
      L->pos = pt;
      L->mat = identitY();
  }


  




	 
  // LIGHTARRAY
  class lightarraY: public arraY_<lighT> {};


  // LPLIGHT
  typedef lighT* lplighT;


  // LPLIGHTARRAY
  class lplightarraY: public arraY__<lplighT> {};
