
  #undef PHONG_SHADER
  #undef BLINN_SHADER
  #undef COOK_TORRANCE_SHADER
  #undef HE_TORRANCE_SHADER

  #define PHONG_SHADER 0
  #define BLINN_SHADER 1
  #define COOK_TORRANCE_SHADER 2
  #define HE_TORRANCE_SHADER 3








  // MATERIAL         
  class materiaL {
      public:
		  DWORD shader_type;
		  coloR ambient, diffuse, specular, emissive, transparency, translucency; 
		  valuE shininess, bumpiness, roughness; 
		  complexiorarraY ciora;
		  maP ambient_, diffuse_, specular_, emissive_, transparency_, translucency_, shininess_, bump_, bumpyness_, roughness_;


          materiaL( void ) { reseT(); };
          ~materiaL( void ) { deletealL(); };
          
          void reseT( void );
          void deletealL( void );
          void copY( materiaL *mtrl );
  };








  void materiaL::reseT( void ) {
	  shader_type = PHONG_SHADER;
      ambient = diffuse = specular = emissive = transparency = translucency = coloR();
	  shininess = bumpiness = roughness = 0.0;
	  ciora.reseT();
	  ambient_.reseT();
	  diffuse_.reseT();
	  specular_.reseT();
	  emissive_.reseT();
	  transparency_.reseT();
	  translucency_.reseT();
	  shininess_.reseT();
	  bump_.reseT();
	  bumpyness_.reseT();
	  roughness_.reseT();
  }




  void materiaL::deletealL( void ) {
	  ciora.deletealL();
	  ambient_.deletealL();
	  diffuse_.deletealL();
	  specular_.deletealL();
	  emissive_.deletealL();
	  transparency_.deletealL();
	  translucency_.deletealL();
	  shininess_.deletealL();
	  bump_.deletealL();
	  bumpyness_.deletealL();
	  roughness_.deletealL();

      reseT();
  }




  void materiaL::copY( materiaL *mtrl ) {
      if( mtrl ) {
          mtrl->deletealL();

    	  mtrl->shader_type = shader_type;
    	  mtrl->ambient = ambient;
	      mtrl->diffuse = diffuse;
    	  mtrl->specular = specular;
	      mtrl->emissive = emissive;
    	  mtrl->transparency = transparency;
	      mtrl->translucency = translucency;
    	  mtrl->shininess = shininess;
	      mtrl->bumpiness = bumpiness;
	      mtrl->roughness = roughness;
    	  ciora.copY( &mtrl->ciora );
    	  ambient_.copY( &mtrl->ambient_ );
    	  diffuse_.copY( &mtrl->diffuse_ );
    	  specular_.copY( &mtrl->specular_ );
    	  emissive_.copY( &mtrl->emissive_ );
    	  transparency_.copY( &mtrl->transparency_ );
    	  translucency_.copY( &mtrl->translucency_ );
    	  shininess_.copY( &mtrl->shininess_ );
    	  bump_.copY( &mtrl->bump_ );
    	  bumpyness_.copY( &mtrl->bumpyness_ );
    	  roughness_.copY( &mtrl->roughness_ );
      }
  }


  




	 
  // MATERIALARRAY
  class materialarraY: public arraY_<materiaL> {};


  // LPMATERIAL
  typedef materiaL* lpmateriaL;


  // LPMATERIALARRAY
  class lpmaterialarraY: public arraY__<lpmateriaL> {};
