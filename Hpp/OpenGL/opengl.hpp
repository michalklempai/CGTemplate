
  // OPENGL
  class opengL {
      public:
		  HGLRC hglrc;
		  HDC hdc;
		  const GLubyte *vendor, *renderer, *version, *extensions;
          GLint auxbuffers, maxtextureunitsarb;
          BOOL gl_arb_multitexture, gl_arb_imaging, gl_arb_texture_non_power_of_two;

          _GLextensionProcs extensionprocs;


          opengL( void );
          ~opengL( void );

		  BOOL iniT( HDC hdc );
		  void releasE( void );
  };


  void rendertexT( float x, float y, BYTE r, BYTE g, BYTE b, BYTE a, RECT rc, char str[2048] );






  opengL::opengL( void ) {
	  hglrc = NULL;
	  hdc = NULL;
	  vendor = renderer = version = extensions = NULL;
      auxbuffers = maxtextureunitsarb = gl_arb_texture_non_power_of_two = 0;
      gl_arb_multitexture = gl_arb_imaging = FALSE;
  }

  
  
  
  opengL::~opengL( void ) {
      releasE();
  }


		  

  BOOL opengL::iniT( HDC hdc ) {
      PIXELFORMATDESCRIPTOR pfd;
	  signed int iPixelFormat;


      this->hdc = hdc;

      ZeroMemory( &pfd, sizeof( pfd ) );

	  pfd.nSize =           sizeof( pfd );
	  pfd.nVersion =        1;
	  pfd.dwFlags =         PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_GENERIC_ACCELERATED;
	  pfd.iPixelType =      PFD_TYPE_RGBA;
      pfd.cColorBits =      32;
	  pfd.cRedBits =        0;
	  pfd.cRedShift =       0;
	  pfd.cGreenBits =      0;
	  pfd.cGreenShift =     0; 
	  pfd.cBlueBits =       0;
	  pfd.cBlueShift =      0;
	  pfd.cAlphaBits =      0;
	  pfd.cAlphaShift =     0;
	  pfd.cAccumBits =      0;
	  pfd.cAccumRedBits =   0;
	  pfd.cAccumGreenBits = 0;
	  pfd.cAccumBlueBits =  0;
	  pfd.cAccumAlphaBits = 0;
	  pfd.cDepthBits =      16;
	  pfd.cStencilBits =    8;
	  pfd.cAuxBuffers =     8;
	  pfd.iLayerType =      PFD_MAIN_PLANE;
	  pfd.bReserved =       0;
	  pfd.dwLayerMask =     0;
	  pfd.dwVisibleMask =   0;
	  pfd.dwDamageMask =    0;

	  if( !( iPixelFormat = ChoosePixelFormat( hdc, &pfd ) ) ) return FALSE;
      if( !SetPixelFormat( hdc, iPixelFormat, &pfd ) ) return FALSE;
	  if( !( hglrc = wglCreateContext( hdc ) ) ) return FALSE;
	  if( !wglMakeCurrent( hdc, hglrc ) ) return FALSE;


	  vendor = glGetString( GL_VENDOR );
	  renderer = glGetString( GL_RENDERER );
	  version = glGetString( GL_VERSION );
	  extensions = glGetString( GL_EXTENSIONS );


      glDisable( GL_ALPHA_TEST );
	  glDisable( GL_AUTO_NORMAL );
	  glDisable( GL_BLEND );
	  glDisable( GL_CLIP_PLANE0 );
	  glDisable( GL_CLIP_PLANE1 );
	  glDisable( GL_CLIP_PLANE2 );
	  glDisable( GL_CLIP_PLANE3 );
	  glDisable( GL_COLOR_MATERIAL );
	  glDisable( GL_CULL_FACE );
	  glDisable( GL_DEPTH_TEST );
	  glDisable( GL_DITHER );
	  glDisable( GL_FOG );
	  glDisable( GL_LIGHT0 );
	  glDisable( GL_LIGHT1 );
	  glDisable( GL_LIGHT2 );
	  glDisable( GL_LIGHT3 );
	  glDisable( GL_LIGHTING );
	  glDisable( GL_LINE_SMOOTH );
	  glDisable( GL_LINE_STIPPLE );
	  glDisable( GL_LOGIC_OP );
	  glDisable( GL_MAP1_COLOR_4 );
	  glDisable( GL_MAP1_INDEX );
	  glDisable( GL_MAP1_NORMAL );
	  glDisable( GL_MAP1_TEXTURE_COORD_1 );
	  glDisable( GL_MAP1_TEXTURE_COORD_2 );
	  glDisable( GL_MAP1_TEXTURE_COORD_3 );
	  glDisable( GL_MAP1_TEXTURE_COORD_4 );
	  glDisable( GL_MAP1_VERTEX_3 );
	  glDisable( GL_MAP1_VERTEX_4 );
	  glDisable( GL_MAP2_COLOR_4 );
	  glDisable( GL_MAP2_INDEX );
	  glDisable( GL_MAP2_NORMAL );
	  glDisable( GL_MAP2_TEXTURE_COORD_1 );
	  glDisable( GL_MAP2_TEXTURE_COORD_2 );
	  glDisable( GL_MAP2_TEXTURE_COORD_3 );
	  glDisable( GL_MAP2_TEXTURE_COORD_4 );
	  glDisable( GL_MAP2_VERTEX_3 );
  	  glDisable( GL_MAP2_VERTEX_4 );
	  glDisable( GL_NORMALIZE );
	  glDisable( GL_POINT_SMOOTH );
	  glDisable( GL_POLYGON_SMOOTH );
	  glDisable( GL_POLYGON_STIPPLE );
	  glDisable( GL_SCISSOR_TEST );
	  glDisable( GL_STENCIL_TEST );
	  glDisable( GL_TEXTURE_1D );
	  glDisable( GL_TEXTURE_2D );
	  glDisable( GL_TEXTURE_GEN_Q );
	  glDisable( GL_TEXTURE_GEN_R );
   	  glDisable( GL_TEXTURE_GEN_S );
	  glDisable( GL_TEXTURE_GEN_T );


      glGetIntegerv( GL_AUX_BUFFERS, &auxbuffers );
      // extensions
	  if( strstr( (char*)extensions, "GL_ARB_multitexture" ) != NULL ) {
          glGetIntegerv( GL_MAX_TEXTURE_UNITS_ARB, &maxtextureunitsarb );

          gl_arb_multitexture = TRUE;
	  } else gl_arb_multitexture = FALSE;
      gl_arb_imaging = ( strstr( (char*)extensions, "GL_ARB_imaging" ) != NULL );
      gl_arb_texture_non_power_of_two = ( strstr( (char*)extensions, "GL_ARB_texture_non_power_of_two" ) != NULL );

								 
	  return TRUE;
  }




  void opengL::releasE( void ) {
      wglMakeCurrent( hdc, hglrc );
	  wglDeleteContext( hglrc );
  }




  void rendertexT( float x, float y, BYTE r, BYTE g, BYTE b, BYTE a, RECT rc, char str[2048] ) {
      register long i = 0;

      glColor4ub( r, g, b, a );

      glMatrixMode( GL_MODELVIEW );
      glPushMatrix();
      glLoadIdentity();

      glMatrixMode( GL_PROJECTION );
      glPushMatrix();
      glLoadIdentity();
      glOrtho( -( rc.right-rc.left )*0.5, ( rc.right-rc.left )*0.5, 
               -( rc.bottom-rc.top )*0.5, ( rc.bottom-rc.top )*0.5,
               -10000, 10000 );

      glRasterPos2f( x-( rc.right-rc.left )*0.5, ( rc.bottom-rc.top )*0.5-y );
      while( str[i] != '\x0' ) {
          glutBitmapCharacter( GLUT_BITMAP_8_BY_13, str[i] );
          i++;
      }

      glPopMatrix();
      glMatrixMode( GL_MODELVIEW );
      glPopMatrix();
  }
