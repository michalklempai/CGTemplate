
  // COMPLEXIOR
  class complexioR {
      public:
          valuE lambda, n, k;  // lambda - wavelength, n = lambda0/lambda - ratio of wavelengths in vacuum(lambda0 = c) and study medium; k - extinction coefficient


          complexioR( void );
          complexioR( valuE lambda, valuE n, valuE k );
          complexioR( const complexioR& cior );

		  BOOL operator==( const complexioR& cior ) const;
          BOOL operator!=( const complexioR& cior ) const;
  };

         






  inline complexioR::complexioR( void ) {
      lambda = n = k = 0.0;
  }




  inline complexioR::complexioR( valuE lambda, valuE n, valuE k ) {
      this->lambda = lambda;  this->n = n;  this->k = k;
  }




  inline complexioR::complexioR( const complexioR& cior ) {
	  lambda = cior.lambda;  n = cior.n;  k = cior.k;
  }




  inline BOOL complexioR::operator==( const complexioR& cior ) const {
	  return lambda == cior.lambda && n == cior.n && k == cior.k;
  }




  inline BOOL complexioR::operator!=( const complexioR& cior ) const {
	  return lambda != cior.lambda || n != cior.n || k != cior.k;
  }








  // COMPLEXIORARRAY
  class complexiorarraY: public arraY<complexioR> {};


  inline complexioR getcioR( valuE lambda, complexiorarraY *ciora, valuE *n = NULL, valuE *k = NULL );
  inline compleX getcioR_( valuE lambda, complexiorarraY *ciora, compleX *cior = NULL );
  inline valuE getN( valuE lambda, complexiorarraY *ciora, valuE *n = NULL );
  inline valuE getK( valuE lambda, complexiorarraY *ciora, valuE *k = NULL );
  BOOL loadcioR( char filename[512], complexiorarraY *ciora );






  inline complexioR getcioR( valuE lambda, complexiorarraY *ciora, valuE *n, valuE *k ) {
	  register long i;
	  complexioR cior;


	  cior.lambda = lambda;

	  if( ciora->num == 1 ) {
		  cior.n = ciora->elem[0].n;
		  cior.k = ciora->elem[0].k;
	  } else 
	  if( ciora->num > 1 ) {
		  if( lambda <= ciora->elem[0].lambda ) { // extrapolacia
			  cior.n = lerP( lambda, ciora->elem[0].n, ciora->elem[1].n, ciora->elem[0].lambda, ciora->elem[1].lambda );
			  cior.k = lerP( lambda, ciora->elem[0].k, ciora->elem[1].k, ciora->elem[0].lambda, ciora->elem[1].lambda );
		  } else 
		  if( lambda >= ciora->elem[ciora->num-1].lambda ) { // extrapolacia
			  cior.n = lerP( lambda, ciora->elem[ciora->num-2].n, ciora->elem[ciora->num-1].n, ciora->elem[ciora->num-2].lambda, ciora->elem[ciora->num-1].lambda );
			  cior.k = lerP( lambda, ciora->elem[ciora->num-2].k, ciora->elem[ciora->num-1].k, ciora->elem[ciora->num-2].lambda, ciora->elem[ciora->num-1].lambda );
		  } else { // interpolacia
			  i = 1;
			  while( i < ciora->num && lambda > ciora->elem[i].lambda ) i++;

			  cior.n = lerP( lambda, ciora->elem[i-1].n, ciora->elem[i].n, ciora->elem[i-1].lambda, ciora->elem[i].lambda );
			  cior.k = lerP( lambda, ciora->elem[i-1].k, ciora->elem[i].k, ciora->elem[i-1].lambda, ciora->elem[i].lambda );
		  }
	  }

	  
	  if( n != NULL ) *n = cior.n;
	  if( k != NULL ) *k = cior.k;


	  return cior;
  }




  inline compleX getcioR_( valuE lambda, complexiorarraY *ciora, compleX *cior ) {
	  register long i;
	  compleX cx;


	  if( ciora->num == 1 ) {
		  cx.re = ciora->elem[0].n;
		  cx.im = ciora->elem[0].k;
	  } else 
	  if( ciora->num > 1 ) {
		  if( lambda <= ciora->elem[0].lambda ) { // extrapolacia
			  cx.re = lerP( lambda, ciora->elem[0].n, ciora->elem[1].n, ciora->elem[0].lambda, ciora->elem[1].lambda );
			  cx.im = lerP( lambda, ciora->elem[0].k, ciora->elem[1].k, ciora->elem[0].lambda, ciora->elem[1].lambda );
		  } else 
		  if( lambda >= ciora->elem[ciora->num-1].lambda ) { // extrapolacia
			  cx.re = lerP( lambda, ciora->elem[ciora->num-2].n, ciora->elem[ciora->num-1].n, ciora->elem[ciora->num-2].lambda, ciora->elem[ciora->num-1].lambda );
			  cx.im = lerP( lambda, ciora->elem[ciora->num-2].k, ciora->elem[ciora->num-1].k, ciora->elem[ciora->num-2].lambda, ciora->elem[ciora->num-1].lambda );
		  } else { // interpolacia
			  i = 1;
			  while( i < ciora->num && lambda > ciora->elem[i].lambda ) i++;

			  cx.re = lerP( lambda, ciora->elem[i-1].n, ciora->elem[i].n, ciora->elem[i-1].lambda, ciora->elem[i].lambda );
			  cx.im = lerP( lambda, ciora->elem[i-1].k, ciora->elem[i].k, ciora->elem[i-1].lambda, ciora->elem[i].lambda );
		  }
	  }


	  if( cior != NULL ) *cior = cx;


	  return cx;
  }




  inline valuE getN( valuE lambda, complexiorarraY *ciora, valuE *n ) {
	  register long i;
	  valuE n_ = 0.0;


	  if( ciora->num == 1 ) {
		  n_ = ciora->elem[0].n;
	  } else 
	  if( ciora->num > 1 ) {
		  if( lambda <= ciora->elem[0].lambda ) { // extrapolacia
			  n_ = lerP( lambda, ciora->elem[0].n, ciora->elem[1].n, ciora->elem[0].lambda, ciora->elem[1].lambda );
		  } else 
		  if( lambda >= ciora->elem[ciora->num-1].lambda ) { // extrapolacia
			  n_ = lerP( lambda, ciora->elem[ciora->num-2].n, ciora->elem[ciora->num-1].n, ciora->elem[ciora->num-2].lambda, ciora->elem[ciora->num-1].lambda );
		  } else { // interpolacia
			  i = 1;
			  while( i < ciora->num && lambda > ciora->elem[i].lambda ) i++;

			  n_ = lerP( lambda, ciora->elem[i-1].n, ciora->elem[i].n, ciora->elem[i-1].lambda, ciora->elem[i].lambda );
		  }
	  }


	  if( n != NULL ) *n = n_;


	  return n_;
  }




  inline valuE getK( valuE lambda, complexiorarraY *ciora, valuE *k ) {
	  register long i;
	  valuE k_;


	  if( ciora->num == 1 ) {
		  k_ = ciora->elem[0].k;
	  } else 
	  if( ciora->num > 1 ) {
		  if( lambda <= ciora->elem[0].lambda ) { // extrapolacia
			  k_ = lerP( lambda, ciora->elem[0].k, ciora->elem[1].k, ciora->elem[0].lambda, ciora->elem[1].lambda );
		  } else 
		  if( lambda >= ciora->elem[ciora->num-1].lambda ) { // extrapolacia
			  k_ = lerP( lambda, ciora->elem[ciora->num-2].k, ciora->elem[ciora->num-1].k, ciora->elem[ciora->num-2].lambda, ciora->elem[ciora->num-1].lambda );
		  } else { // interpolacia
			  i = 1;
			  while( i < ciora->num && lambda > ciora->elem[i].lambda ) i++;

			  k_ = lerP( lambda, ciora->elem[i-1].k, ciora->elem[i].k, ciora->elem[i-1].lambda, ciora->elem[i].lambda );
		  }
	  }


	  if( k != NULL ) *k = k_;


	  return k_;
  }




  BOOL loadcioR( char filename[512], complexiorarraY *ciora ) {
      FILE *file;
	  register long i, j;
	  long l;
	  char str[512], fileex[128];
	  valuE lambda, n, k;
	  

	  ciora->deletealL();

	  if( !( file = fopen( filename, "rt" ) ) ) return FALSE;

	  // file extension
	  j = (long)strlen( filename )-1;  while( filename[j] != '.' ) j--;  
	  for( i = j+1;  i < strlen( filename );  i++ ) fileex[i-j-1] = filename[i];
	  fileex[i-j-1] = '\x0';

	  if( strcmp( fileex, "cior" ) == 0 || strcmp( fileex, "ior" ) == 0 ) { // cior, ior file
		  while( !feof( file ) ) {
			  ZeroMemory( &str[0], sizeof( str ) );
			  fgets( &str[0], 512, file );

			  lambda = n = k = 0.0;
			  l = sscanf( &str[0], "%f %f %f", &lambda, &n, &k );

			  if( l == 2 || l == 3 ) {
				  ciora->inserT( -1, complexioR( lambda, n, k ) );		  	
			  } else {
				  fclose( file );

				  return FALSE;
			  }
		  }
	  } else {
	      fclose( file );  

		  return FALSE;
	  }

      fclose( file );  


	  return TRUE;
  }
