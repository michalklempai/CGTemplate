
  inline void getcurrentdiR( char *current_dir, DWORD nBufferLength ) {
	  ZeroMemory( current_dir, nBufferLength );
      GetCurrentDirectoryA( nBufferLength, current_dir );
  }




  inline void parsefilenamE( char path[1024], char *filename ) {
	  register long i, j;

	  i = strlen( path )-1;  j = 0;
	  while( path[i] != '\\' ) {
		  filename[j] = path[i];
	      i--;  j++;
	  }
      filename[j] = '\x0';
	  strcpy( filename, strrev( filename ) );
  }




  inline char readchaR( FILE *file ) {
      if( !feof( file ) ) return fgetc( file ); else return ' ';
  }




  inline void readstrinG( FILE *file, char *str ) {
      DWORD i = 0;
      char ch = readchaR( file );

      while( ch == ' ' || ch == '\t' || ch == '\n' ) ch = readchaR( file );
      while( ch != ' ' && ch != '\t' && ch != '\n' ) {
          str[i] = ch;
          i++;
          ch = readchaR( file );
      }
      str[i] = '\x0';
  }




  inline void readstrinG_( FILE *file, char *str ) {  // nacita string ohraniceny ""
      DWORD i = 0;
      char ch = readchaR( file );

      while( ch != '"' ) ch = readchaR( file );
	  ch = readchaR( file );
	  do {
          str[i] = ch;
          i++;
          ch = readchaR( file );
	  } while( ch != '"' && ch != '\t' && ch != '\n' );
      str[i] = '\x0';
  }




  inline DWORD readdworD( FILE *file ) {
      char str[64], *endptr;

      readstrinG( file, &str[0] );

      return strtoul( &str[0], &endptr, 10 ); 
  }




  inline FLOAT readfloaT( FILE *file ) {
      char str[64], *endptr;

      readstrinG( file, &str[0] );
      
      return strtod( &str[0], &endptr ); 
  }




  void readmeshverteX( FILE *file, verteX *V ) {
      readdworD( file );
      V->v.x = readfloaT( file );
      V->v.y = readfloaT( file );
      V->v.z = readfloaT( file );
  }




  void readmeshvertexlisT( FILE *file, vertexarraY *Va ) {
      char str[64];

	  Va->deletealL();

      do {
          readstrinG( file, &str[0] );

          // MESH_VERTEX
          if( strcmp( "*MESH_VERTEX", str ) == 0 ) {
			  Va->inserT( -1, NULL );
              readmeshverteX( file, &Va->elem[Va->num-1] );    
          } 
      } while( strcmp( "}", str ) != 0 );
  }




  void readmeshfacE( FILE *file, facE *F ) {
      char str[64];

	  readstrinG( file, &str[0] );
	  readstrinG( file, &str[0] );
      F->Via.inserT( -1, readdworD( file ) );
	  readstrinG( file, &str[0] );
      F->Via.inserT( -1, readdworD( file ) );
	  readstrinG( file, &str[0] );
      F->Via.inserT( -1, readdworD( file ) );
	  // ...
  }




  void readmeshsmoothinG( FILE *file, facE *F ) {
      readdworD( file );
  }




  void readmeshmtliD( FILE *file, facE *F ) {
      readdworD( file );
  }




  void readmeshfacelisT( FILE *file, facearraY *Fa ) {
      char str[64];

	  Fa->deletealL();

      do {
          readstrinG( file, &str[0] );

          // MESH_FACE
          if( strcmp( "*MESH_FACE", str ) == 0 ) {
			  Fa->inserT( -1, NULL );
              readmeshfacE( file, &Fa->elem[Fa->num-1] );    
          } else
          // MESH_SMOOTHING
          if( strcmp( "*MESH_SMOOTHING", str ) == 0 ) {
			  readmeshsmoothinG( file, &Fa->elem[Fa->num-1] );    
          } else
          // MESH_MTLID
          if( strcmp( "*MESH_MTLID", str ) == 0 ) {
			  readmeshmtliD( file, &Fa->elem[Fa->num-1] );    
          } 
      } while( strcmp( "}", str ) != 0 );
  }




  void readmeshfacenormaL( FILE *file, vertexarraY *Va, facearraY *Fa ) {
	  DWORD dw = readdworD( file );

      Fa->elem[dw].pl.n.x = readfloaT( file );
      Fa->elem[dw].pl.n.y = readfloaT( file );
      Fa->elem[dw].pl.n.z = readfloaT( file );
	  Fa->elem[dw].pl.d = -doT( Fa->elem[dw].pl.n, vectoR( Va->elem[Fa->elem[dw].Via.elem[0]].v.x, Va->elem[Fa->elem[dw].Via.elem[0]].v.y, Va->elem[Fa->elem[dw].Via.elem[0]].v.z ) );
  }




  void readmeshvertexnormaL( FILE *file, vectorarraY *Vna, vertexarraY *Va ) {
	  DWORD dw = readdworD( file );

      Va->elem[dw].n.x = readfloaT( file );
      Va->elem[dw].n.y = readfloaT( file );
      Va->elem[dw].n.z = readfloaT( file );

	  Vna->inserT( -1, Va->elem[dw].n );
  }




  void readmeshnormalS( FILE *file, vectorarraY *Vna, vertexarraY *Va, facearraY *Fa ) {
      char str[64];

      do {
          readstrinG( file, &str[0] );

          // MESH_FACENORMAL
          if( strcmp( "*MESH_FACENORMAL", str ) == 0 ) {
              readmeshfacenormaL( file, Va, Fa );    
          } else
          // MESH_VERTEXNORMAL
          if( strcmp( "*MESH_VERTEXNORMAL", str ) == 0 ) {
              readmeshvertexnormaL( file, Vna, Va );    
          } 
      } while( strcmp( "}", str ) != 0 );
  }




  void readmeshtverT( FILE *file, poinT *pt ) {
      readdworD( file );
      pt->x = readfloaT( file );
      pt->y = readfloaT( file );
      pt->z = readfloaT( file );
  }




  void readmeshtvertlisT( FILE *file, pointarraY *tca ) {
      char str[64];
      poinT pt;

      do {
          readstrinG( file, &str[0] );

          // MESH_TVERT
          if( strcmp( "*MESH_TVERT", str ) == 0 ) {
              readmeshtverT( file, &pt );    
              tca->inserT( -1, pt );
          } 
      } while( strcmp( "}", str ) != 0 );
  }




  void readmeshtfacE( FILE *file, dwordarraY *tfa ) {
      readdworD( file );
	  for( register long i = 0;  i < 3;  i++ ) tfa->inserT( -1, readdworD( file ) );	  
  }




  void readmeshtfacelisT( FILE *file, dwordarraY *tfa ) {
      char str[64];


      do {
          readstrinG( file, &str[0] );

          // MESH_TFACE
          if( strcmp( "*MESH_TFACE", str ) == 0 ) {
              readmeshtfacE( file, tfa );    
          }
      } while( strcmp( "}", str ) != 0 );
  }




  void readmesH( FILE *file, mesH *M ) {
	  register long i;
      char str[64];
	  long l;
	  dwordarraY tfa;
	  vectorarraY Vna;
	  pointarraY tca;


      readstrinG( file, &str[0] );
      do {
          readstrinG( file, &str[0] );

          // MESH_VERTEX_LIST
		  if( strcmp( "*MESH_VERTEX_LIST", str ) == 0 ) {
			  readmeshvertexlisT( file, &M->Va ); 
		  } else
          // MESH_FACE_LIST
		  if( strcmp( "*MESH_FACE_LIST", str ) == 0 ) {
			  readmeshfacelisT( file, &M->Fa ); 
		  } else
          // MESH_TVERTLIST
          if( strcmp( "*MESH_TVERTLIST", str ) == 0 ) {
              readmeshtvertlisT( file, &tca ); 
	      } else
          // MESH_TFACELIST
          if( strcmp( "*MESH_TFACELIST", str ) == 0 ) {
              readmeshtfacelisT( file, &tfa ); 
          } else
          // MESH_NORMALS
		  if( strcmp( "*MESH_NORMALS", str ) == 0 ) {
			  readmeshnormalS( file, &Vna, &M->Va, &M->Fa ); 
		  } else
          // ...
          if( strcmp( "{", str ) == 0 ) {
			  l = 1;
			  do { 
				  readstrinG( file, &str[0] ); 
				  if( strcmp( "}", str ) == 0 ) l--; else if( strcmp( "{", str ) == 0 ) l++;
			  } while( l > 0 );
              str[0] = '/x0';
          }
      } while( strcmp( "}", str ) != 0 );


	  // dopocitanie normal vertexov, negeneruje navyse vertexy lebo preto sa v readmeshvertexnormaL nacitavaju vertex normalu do M->Va, pricom tam vlastne zostane posledne nacitana, takze vdaka tomu pre tu normalu nebudeme vytvarat novy vertex 
	  for( i = 0;  i < Vna.num;  i+=3 ) {
		  // 0 
		  if( M->Va.elem[M->Fa.elem[i/3].Via.elem[0]].n != Vna.elem[i+0] ) {  // treba vytvorit novy vertex
			  M->Va.inserT( -1, NULL );
			  M->Va.elem[M->Fa.elem[i/3].Via.elem[0]].copY( &M->Va.elem[M->Va.num-1] );
			  M->Va.elem[M->Va.num-1].n = Vna.elem[i+0];
			  M->Fa.elem[i/3].Via.elem[0] = M->Va.num-1;
		  }
		  // 1 
		  if( M->Va.elem[M->Fa.elem[i/3].Via.elem[1]].n != Vna.elem[i+1] ) {  // treba vytvorit novy vertex
			  M->Va.inserT( -1, NULL );
			  M->Va.elem[M->Fa.elem[i/3].Via.elem[1]].copY( &M->Va.elem[M->Va.num-1] );
			  M->Va.elem[M->Va.num-1].n = Vna.elem[i+1];
			  M->Fa.elem[i/3].Via.elem[1] = M->Va.num-1;
		  }
		  // 2 
		  if( M->Va.elem[M->Fa.elem[i/3].Via.elem[2]].n != Vna.elem[i+2] ) {  // treba vytvorit novy vertex
			  M->Va.inserT( -1, NULL );
			  M->Va.elem[M->Fa.elem[i/3].Via.elem[2]].copY( &M->Va.elem[M->Va.num-1] );
			  M->Va.elem[M->Va.num-1].n = Vna.elem[i+2];
			  M->Fa.elem[i/3].Via.elem[2] = M->Va.num-1;
		  }
	  }

	  // dopocitanie mapovacich suradnic, generuje navyse vertexy
	  if( tca.num > 0 && tfa.num > 0 ) {
		  for( i = 0;  i < tfa.num;  i+=3 ) {
			  // 0 
			  if( M->Va.elem[M->Fa.elem[i/3].Via.elem[0]].t != tca.elem[tfa.elem[i+0]] ) {  // treba vytvorit novy vertex
				  M->Va.inserT( -1, NULL );
				  M->Va.elem[M->Fa.elem[i/3].Via.elem[0]].copY( &M->Va.elem[M->Va.num-1] );
				  M->Va.elem[M->Va.num-1].t = tca.elem[tfa.elem[i+0]];
				  M->Fa.elem[i/3].Via.elem[0] = M->Va.num-1;
			  }
			  // 1 
			  if( M->Va.elem[M->Fa.elem[i/3].Via.elem[1]].t != tca.elem[tfa.elem[i+1]] ) {  // treba vytvorit novy vertex
				  M->Va.inserT( -1, NULL );
				  M->Va.elem[M->Fa.elem[i/3].Via.elem[1]].copY( &M->Va.elem[M->Va.num-1] );
				  M->Va.elem[M->Va.num-1].t = tca.elem[tfa.elem[i+1]];
				  M->Fa.elem[i/3].Via.elem[1] = M->Va.num-1;
			  }
			  // 2 
			  if( M->Va.elem[M->Fa.elem[i/3].Via.elem[2]].t != tca.elem[tfa.elem[i+2]] ) {  // treba vytvorit novy vertex
				  M->Va.inserT( -1, NULL );
				  M->Va.elem[M->Fa.elem[i/3].Via.elem[2]].copY( &M->Va.elem[M->Va.num-1] );
				  M->Va.elem[M->Va.num-1].t = tca.elem[tfa.elem[i+2]];
				  M->Fa.elem[i/3].Via.elem[2] = M->Va.num-1;
			  }
		  }
	  }


	  if( M->mata.num == 0 ) M->mata.inserT( -1, identitY() ); 
	  transformvertexnormalS( M, M->mata.elem[0] );
	  M->mata.elem[0] = identitY();
      M->findaabboX();
	  if( M->mtrla.num == 0 ) M->mtrla.inserT( -1, NULL ); 
	  M->mtrla.elem[0].ciora.inserT( -1, complexioR( 0.0, 1.55, 0.0 ) ); // neskor nacitavaj zo suboru
	  M->mtrla.elem[0].roughness = 0.18; // neskor nacitavaj zo suboru
  }




  void readtmrow0( FILE *file, matriX *mat ) {
	  mat->_[0][0] = readfloaT( file );
	  mat->_[0][1] = readfloaT( file );
	  mat->_[0][2] = readfloaT( file );
  }




  void readtmrow1( FILE *file, matriX *mat ) {
	  mat->_[1][0] = readfloaT( file );
	  mat->_[1][1] = readfloaT( file );
	  mat->_[1][2] = readfloaT( file );
  }




  void readtmrow2( FILE *file, matriX *mat ) {
	  mat->_[2][0] = readfloaT( file );
	  mat->_[2][1] = readfloaT( file );
	  mat->_[2][2] = readfloaT( file );
  }




  void readtmrow3( FILE *file, matriX *mat ) {
	  mat->_[3][0] = readfloaT( file );
	  mat->_[3][1] = readfloaT( file );
	  mat->_[3][2] = readfloaT( file );
  }




  void readnodetM( FILE *file, mesH *M ) {
      char str[64];


      readstrinG( file, &str[0] );
      do {
          readstrinG( file, &str[0] );

          // TM_ROW0
		  if( strcmp( "*TM_ROW0", str ) == 0 ) {
			  M->mata.inserT( -1, identitY() );
			  readtmrow0( file, &M->mata.elem[M->mata.num-1] );
		  } else
          // TM_ROW1
		  if( strcmp( "*TM_ROW1", str ) == 0 ) {
			  readtmrow1( file, &M->mata.elem[M->mata.num-1] );
		  } else
          // TM_ROW2
		  if( strcmp( "*TM_ROW2", str ) == 0 ) {
			  readtmrow2( file, &M->mata.elem[M->mata.num-1] );
		  } else
          // TM_ROW3
		  if( strcmp( "*TM_ROW3", str ) == 0 ) {
			  readtmrow3( file, &M->mata.elem[M->mata.num-1] );
		  } // ...
      } while( strcmp( "}", str ) != 0 );
  }




  void readmaP( FILE *file, maP *map, texturearraY<BYTE> *Ta ) {
      char str[1024], str2[1024], current_dir[1024], filename[256];
	  long l;


      readstrinG( file, &str[0] );
      do {
          readstrinG( file, &str[0] );

          // BITMAP
		  if( strcmp( "*BITMAP", str ) == 0 ) {
			  readstrinG_( file, &str[0] );

			  Ta->inserT( -1, NULL );
			  parsefilenamE( str, &filename[0] );
			  getcurrentdiR( &current_dir[0], sizeof( current_dir ) );
			  sprintf( str2, "%s\\%s", current_dir, filename );
			  if( loadtgA( str2, &Ta->elem[Ta->num-1] ) || loadtgA( str, &Ta->elem[Ta->num-1] ) ) map->lpT = &Ta->elem[Ta->num-1]; else {
				  map->lpT = NULL;

				  sprintf( str2, "Error: Texture \"%s\" not loaded!", str );
			  	  MessageBoxExA( NULL, str2, NULL, MB_OK | MB_ICONERROR | MB_APPLMODAL | MB_SETFOREGROUND | MB_TOPMOST, 0 );
			  }
		  } else
          // UVW_U_OFFSET
		  if( strcmp( "*UVW_U_OFFSET", str ) == 0 ) {
			  map->offset.x = readfloaT( file );
		  } else
          // UVW_V_OFFSET
		  if( strcmp( "*UVW_V_OFFSET", str ) == 0 ) {
			  map->offset.y = readfloaT( file );
		  } else
          // UVW_U_TILING
		  if( strcmp( "*UVW_U_TILING", str ) == 0 ) {
			  map->tiling.x = readfloaT( file );
		  } else
          // UVW_V_TILING
		  if( strcmp( "*UVW_V_TILING", str ) == 0 ) {
			  map->tiling.y = readfloaT( file );
		  } else
		  //...
          if( strcmp( "{", str ) == 0 ) {
			  l = 1;
			  do { 
				  readstrinG( file, &str[0] ); 
				  if( strcmp( "}", str ) == 0 ) l--; else if( strcmp( "{", str ) == 0 ) l++;
			  } while( l > 0 );
              str[0] = '/x0';
          }
      } while( strcmp( "}", str ) != 0 );
  }




  coloR readsceneambientstatiC( FILE *file ) {
	  coloR c;

	  c.r = readfloaT( file );
	  c.g = readfloaT( file );
	  c.b = readfloaT( file );
	  c.a = 0.0;

	  return c;
  }




  void readscenE( FILE *file, scenE *S ) {
	  char str[128];
	  long l;


      readstrinG( file, &str[0] );
      do {
          readstrinG( file, &str[0] );

          // SCENE_AMBIENT_STATIC
          if( strcmp( "*SCENE_AMBIENT_STATIC", str ) == 0 ) {
			  S->La.inserT( -1, &lighT( readsceneambientstatiC( file ) ) );
          } else
		  if( strcmp( "{", str ) == 0 ) {
			  l = 1;
			  do { 
				  readstrinG( file, &str[0] ); 
				  if( strcmp( "}", str ) == 0 ) l--; else if( strcmp( "{", str ) == 0 ) l++;
			  } while( l > 0 );
		      str[0] = '/x0';
	      }
      } while( strcmp( "}", str ) != 0 );
  }




  void readgeomobjecT( FILE *file, scenE *S, arraY_<materialarraY> *mtrlaa ) {
	  char str[128];
	  long l;
	  DWORD dw;


      S->lpobja.inserT( -1, lpobjecT(new mesH()) );

      readstrinG( file, &str[0] );
      do {
          readstrinG( file, &str[0] );

          // MESH
          if( strcmp( "*MESH", str ) == 0 ) {
              readmesH( file, (lpmesH)S->lpobja.elem[S->lpobja.num-1] );
          } else
          // NODE_TM
          if( strcmp( "*NODE_TM", str ) == 0 ) {
              readnodetM( file, (lpmesH)S->lpobja.elem[S->lpobja.num-1] );
          } else
		  // MATERIAL_REF
		  if( strcmp( "*MATERIAL_REF", str ) == 0 ) {
			  dw = readdworD( file );
			  if( dw < mtrlaa->num ) mtrlaa->elem[dw].copY( &S->lpobja.elem[S->lpobja.num-1]->mtrla );
		  } else
		  if( strcmp( "{", str ) == 0 ) {
			  l = 1;
			  do { 
				  readstrinG( file, &str[0] ); 
				  if( strcmp( "}", str ) == 0 ) l--; else if( strcmp( "{", str ) == 0 ) l++;
			  } while( l > 0 );
		      str[0] = '/x0';
	      }
      } while( strcmp( "}", str ) != 0 );
  }




  void readgrouP( FILE *file, scenE *S, arraY_<materialarraY> *mtrlaa ) {
	  char str[128];
	  long l;


	  readstrinG_( file, &str[0] );
      readstrinG( file, &str[0] );
	  do {
          readstrinG( file, &str[0] );

          // GEOMOBJECT
          if( strcmp( "*GEOMOBJECT", str ) == 0 ) {
			  readgeomobjecT( file, S, mtrlaa );
          } else
		  // GROUP
          if( strcmp( "*GROUP", str ) == 0 ) {
              readgrouP( file, S, mtrlaa );
		  } else
          if( strcmp( "{", str ) == 0 ) {
			  l = 1;
			  do { 
				  readstrinG( file, &str[0] ); 
				  if( strcmp( "}", str ) == 0 ) l--; else if( strcmp( "{", str ) == 0 ) l++;
			  } while( l > 0 );
              str[0] = '/x0';
          }
      } while( strcmp( "}", str ) != 0 );
  }




  void readmateriaL( FILE *file, materialarraY *mtrla, texturearraY<BYTE> *Ta ) {
      char str[64];
	  long l;


	  mtrla->inserT( -1, NULL );  // zatial nacitavam len jeden submaterial

      readstrinG( file, &str[0] );
      readstrinG( file, &str[0] );
      do {
          readstrinG( file, &str[0] );

          // MATERIAL_AMBIENT
		  if( strcmp( "*MATERIAL_AMBIENT", str ) == 0 ) {
			  mtrla->elem[0].ambient.r = readfloaT( file );
			  mtrla->elem[0].ambient.g = readfloaT( file );
			  mtrla->elem[0].ambient.b = readfloaT( file );
		  } else
          // MATERIAL_DIFFUSE
		  if( strcmp( "*MATERIAL_DIFFUSE", str ) == 0 ) {
			  mtrla->elem[0].diffuse.r = readfloaT( file );
			  mtrla->elem[0].diffuse.g = readfloaT( file );
			  mtrla->elem[0].diffuse.b = readfloaT( file );
		  } else
          // MATERIAL_SPECULAR
		  if( strcmp( "*MATERIAL_SPECULAR", str ) == 0 ) {
			  mtrla->elem[0].specular.r = readfloaT( file );
			  mtrla->elem[0].specular.g = readfloaT( file );
			  mtrla->elem[0].specular.b = readfloaT( file );
		  } else
          // MATERIAL_SHINE
		  if( strcmp( "*MATERIAL_SHINE", str ) == 0 ) {
			  mtrla->elem[0].roughness = 1.0-readfloaT( file );
			  mtrla->elem[0].shininess = 64.0*( 1.0-mtrla->elem[0].roughness );
		  } else
          // MATERIAL_SHINESTRENGTH
		  if( strcmp( "*MATERIAL_SHINESTRENGTH", str ) == 0 ) {
			  mtrla->elem[0].specular *= readfloaT( file );
			  mtrla->elem[0].specular = clamP( mtrla->elem[0].specular );
		  } else
          // MATERIAL_TRANSPARENCY
		  if( strcmp( "*MATERIAL_TRANSPARENCY", str ) == 0 ) {
			  mtrla->elem[0].transparency.r = readfloaT( file );
			  mtrla->elem[0].transparency.g = mtrla->elem[0].transparency.b = mtrla->elem[0].transparency.r;
		  } else
          // MATERIAL SELFILLUM
		  if( strcmp( "*MATERIAL_SELFILLUM", str ) == 0 ) {
			  mtrla->elem[0].emissive = mtrla->elem[0].diffuse*readfloaT( file );
		  } else
          // MATERIAL_SHADING
		  if( strcmp( "*MATERIAL_SHADING", str ) == 0 ) {
			  readstrinG( file, &str[0] );
			  if( strcmp( "Phong", str ) == 0 ) mtrla->elem[0].shader_type = PHONG_SHADER; else
//			  if( strcmp( "Blinn", str ) == 0 ) mtrla->elem[0].shader_type = /*BLINN_SHADER*/PHONG_SHADER; else
			  if( strcmp( "Metal", str ) == 0 ) mtrla->elem[0].shader_type = COOK_TORRANCE_SHADER; else
												mtrla->elem[0].shader_type = -1;  // default	
		  } else
          // MAP_DIFFUSE
		  if( strcmp( "*MAP_DIFFUSE", str ) == 0 ) {
			  readmaP( file, &mtrla->elem[0].diffuse_, Ta );
		  } else
		  //...
          if( strcmp( "{", str ) == 0 ) {
			  l = 1;
			  do { 
				  readstrinG( file, &str[0] ); 
				  if( strcmp( "}", str ) == 0 ) l--; else if( strcmp( "{", str ) == 0 ) l++;
			  } while( l > 0 );
              str[0] = '/x0';
          }
      } while( strcmp( "}", str ) != 0 );
  }




  BOOL loadasE( char filename[1024], scenE *S ) {
      FILE *file;
      char str[64];
	  arraY_<materialarraY> mtrlaa;


      if( ( file = fopen( filename, "rt" ) ) == NULL ) return FALSE;

      while( !feof( file ) ) {
          readstrinG( file, &str[0] );

		  // SCENE
          if( strcmp( "*SCENE", str ) == 0 ) {
			  readscenE( file, S );
          } else
          // GEOMOBJECT
          if( strcmp( "*GEOMOBJECT", str ) == 0 ) {
			  readgeomobjecT( file, S, &mtrlaa );
          } else
		  // GROUP
          if( strcmp( "*GROUP", str ) == 0 ) {
              readgrouP( file, S, &mtrlaa );
		  } else
          // MATERIAL_LIST
          if( strcmp( "*MATERIAL_LIST", str ) == 0 ) {
              readstrinG( file, &str[0] );

              do {
                  readstrinG( file, &str[0] );

                  // MATERIAL
				  if( strcmp( "*MATERIAL", str ) == 0 ) {
					  mtrlaa.inserT( -1, NULL );
                      readmateriaL( file, &mtrlaa.elem[mtrlaa.num-1], &S->Ta );
				  }
              } while( strcmp( "}", str ) != 0 );
          } 
      }

      fclose( file );


      return TRUE;
  }


