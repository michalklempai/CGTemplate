
  // ARRAY TEMPLATE 
  template <typename T> class arraY {
      public:
	      T *elem; 
	      DWORD num, n, m, l;


	      arraY( void ) { reseT(); };
	      ~arraY( void ) { deletealL(); };

          void reseT( void );
          void inserT( DWORD i, T elem_, DWORD numtimes = 1 ); 
          void deletE( DWORD i );
          void deletealL( void );
          void copY( arraY *elema );

          T operator()( DWORD i );
          T operator()( DWORD i, DWORD j );
          T operator()( DWORD i, DWORD j, DWORD k );
  };






  template <typename T> inline void arraY<T>::reseT( void ) {
      elem = NULL;
      num = n = m = l = 0;
  };




  template <typename T> void arraY<T>::inserT( DWORD i, T elem_, DWORD numtimes ) {
      register DWORD j;
      DWORD b;


      if( numtimes < 1 ) return;

      if( elem ) {  
          // num > 0
          if( i > num ) i = num;

          b = num+numtimes;
          if( b > (DWORD)pow( 2.0, flooR( log( (valuE)num )*INV_LN2 )+1.0 )-1 ) {
              elem = (T*)realloc( elem, ( (DWORD)pow( 2.0, flooR( log( (valuE)b )*INV_LN2 )+1.0 )-1 )*sizeof( T ) );
              if( !elem ) exit( EXIT_FAILURE );
          }

          for( j = b-1;  j > i+numtimes-1;  j-- ) elem[j] = elem[j-numtimes];
		  for( j = i;  j < i+numtimes;  j++ ) elem[j] = elem_;
          num = b;
      } else {  
          // num = 0
          elem = (T*)malloc( ( (DWORD)pow( 2.0, flooR( log( (valuE)numtimes )*INV_LN2 )+1.0 )-1 )*sizeof( T ) );
          if( !elem ) exit( EXIT_FAILURE );
		  for( j = 0;  j < numtimes;  j++ ) elem[j] = elem_;
          num = numtimes;
      }
  };




  template <typename T> void arraY<T>::deletE( DWORD i ) {
      if( elem ) {
          if( num == 1 ) {
              deletealL();
          } else {
		      if( i >= num ) i = num-1;

		      for( register DWORD j = i;  j < num-1;  j++ ) elem[j] = elem[j+1];

              if( (DWORD)flooR( log( (valuE)num )*INV_LN2 ) > (DWORD)flooR( log( (valuE)( num-1 ) )*INV_LN2 ) ) {
                  elem = (T*)realloc( elem, ( (DWORD)pow( 2.0, flooR( log( (valuE)( num-1 ) )*INV_LN2 )+1.0 )-1 )*sizeof( T ) );
                  if( !elem ) exit( EXIT_FAILURE );
              }

              num--;
          }
      }
  };




  template <typename T> inline void arraY<T>::deletealL( void ) {
      if( elem ) free( elem );
      
      reseT();
  };




  template <typename T> void arraY<T>::copY( arraY *elema ) {
      if( elema ) {
          elema->deletealL();

	      if( elem ) {
              elema->elem = (T*)malloc( ( (DWORD)pow( 2.0, flooR( log( (valuE)num )*INV_LN2 )+1.0 )-1 )*sizeof( T ) );
              if( !elema->elem ) exit( EXIT_FAILURE );
	    	  for( register DWORD j = 0;  j < num;  j++ ) elema->elem[j] = elem[j];
              elema->num = num;
	      }
      }
  };




  template <typename T> inline T arraY<T>::operator()( DWORD i ) {
      if( i >= 0 /*&& i < n*/ && i < num ) return elem[i]; 
  };




  template <typename T> inline T arraY<T>::operator()( DWORD i, DWORD j ) {
      DWORD a = i+j*n;

      if( i >= 0 && i < n && j >= 0 && j < m && a < num ) return elem[a]; 
  };




  template <typename T> inline T arraY<T>::operator()( DWORD i, DWORD j, DWORD k ) {
      DWORD a = i+j*n+k*n*m;

      if( i >= 0 && i < n && j >= 0 && j < m && k >= 0 && k < l && a < num ) return elem[a]; 
  };








  // ARRAY_ TEMPLATE 
  template <typename T> class arraY_ {
      public:
	      T *elem; 
   		  DWORD num, n, m, l;


	      arraY_( void ) { reseT(); };
	      ~arraY_( void ) { deletealL(); };

          void reseT( void );
          void inserT( DWORD i, T *elem_ = NULL, DWORD numtimes = 1 ); 
          void deletE( DWORD i );
          void deletealL( void );
          void copY( arraY_ *elema );

          T& operator()( DWORD i );
          T& operator()( DWORD i, DWORD j );
          T& operator()( DWORD i, DWORD j, DWORD k );
  };






  template <typename T> inline void arraY_<T>::reseT( void ) {
      elem = NULL;
      num = n = m = l = 0;
  };




  template <typename T> void arraY_<T>::inserT( DWORD i, T *elem_, DWORD numtimes ) {
      register DWORD j;
      DWORD b;


      if( numtimes < 1 ) return;

      if( elem ) {  
          // num > 0
	      if( i > num ) i = num;

          b = num+numtimes;
          if( b > (DWORD)pow( 2.0, flooR( log( (valuE)num )*INV_LN2 )+1.0 )-1 ) {
              elem = (T*)realloc( elem, ( (DWORD)pow( 2.0, flooR( log( (valuE)b )*INV_LN2 )+1.0 )-1 )*sizeof( T ) );
              if( !elem ) exit( EXIT_FAILURE );
          }

          for( j = num;  j < b;  j++ ) elem[j].reseT();
          for( j = b-1;  j > i+numtimes-1;  j-- ) elem[j-numtimes].copY( &elem[j] );
	      if( elem_ ) 
              for( j = i;  j < i+numtimes;  j++ ) elem_->copY( &elem[j] );
          num = b;
      } else {  
          // num = 0
          elem = (T*)malloc( ( (DWORD)pow( 2.0, flooR( log( (valuE)numtimes )*INV_LN2 )+1.0 )-1 )*sizeof( T ) );
          if( !elem ) exit( EXIT_FAILURE );
          for( j = 0;  j < numtimes;  j++ ) elem[j].reseT();
          if( elem_ ) 
              for( j = 0;  j < numtimes;  j++ ) elem_->copY( &elem[j] );
          num = numtimes;
      }
  };




  template <typename T> void arraY_<T>::deletE( DWORD i ) {
      if( elem ) {
          if( num == 1 ) {
              deletealL();
          } else {
			  if( i >= num ) i = num-1;

		      for( register DWORD j = i;  j < num-1;  j++ ) elem[j+1].copY( &elem[j] );
              elem[num-1].deletealL();

              if( (DWORD)flooR( log( (valuE)num )*INV_LN2 ) > (DWORD)flooR( log( (valuE)( num-1 ) )*INV_LN2 ) ) {
                  elem = (T*)realloc( elem, ( (DWORD)pow( 2.0, flooR( log( (valuE)( num-1 ) )*INV_LN2 )+1.0 )-1 )*sizeof( T ) );
                  if( !elem ) exit( EXIT_FAILURE );
              }

              num--;
          }
      }
  };




  template <typename T> inline void arraY_<T>::deletealL( void ) {
      for( register DWORD i = 0;  i < num;  i++ ) elem[i].deletealL();
      if( elem ) free( elem );

      reseT();
  };




  template <typename T> void arraY_<T>::copY( arraY_ *elema ) {
      if( elema ) {
          elema->deletealL();

	      if( elem ) 
              for( register DWORD j = 0;  j < num;  j++ ) elema->inserT( -1, &elem[j] ); 
      }
  };




  template <typename T> inline T& arraY_<T>::operator()( DWORD i ) {
      if( i >= 0 /*&& i < n*/ && i < num ) return &elem[i]; 
  };




  template <typename T> inline T& arraY_<T>::operator()( DWORD i, DWORD j ) {
      DWORD a = i+j*n;

      if( i >= 0 && i < m && j >= 0 && j < n && a < num ) return &elem[a]; 
  };




  template <typename T> inline T& arraY_<T>::operator()( DWORD i, DWORD j, DWORD k ) {
      DWORD a = i+j*n+k*n*m;

      if( i >= 0 && i < n && j >= 0 && j < m && k >= 0 && k < l && a < num ) return &elem[a]; 
  };








  // ARRAY__ TEMPLATE 
  template <typename T> class arraY__ {
      public:
	      T *elem; 
	      DWORD num, n, m, l;


	      arraY__( void ) { reseT(); };
	      ~arraY__( void ) { deletealL(); };

          void reseT( void );
          void inserT( DWORD i, T elem_, DWORD numtimes = 1 ); 
          void deletE( DWORD i );
          void deletealL( void );
          void releasE( DWORD i );
          void releasealL( void );
          void copY( arraY__ *elema );

          T operator()( DWORD i );
          T operator()( DWORD i, DWORD j );
          T operator()( DWORD i, DWORD j, DWORD k );
  };






  template <typename T> inline void arraY__<T>::reseT( void ) {
      elem = NULL;
      num = n = m = l = 0;
  };




  template <typename T> void arraY__<T>::inserT( DWORD i, T elem_, DWORD numtimes ) {
      register DWORD j;
      DWORD b;


      if( numtimes < 1 ) return;

      if( elem ) {  
          // num > 0
          if( i > num ) i = num;

          b = num+numtimes;
          if( b > (DWORD)pow( 2.0, flooR( log( (valuE)num )*INV_LN2 )+1.0 )-1 ) {
              elem = (T*)realloc( elem, ( (DWORD)pow( 2.0, flooR( log( (valuE)b )*INV_LN2 )+1.0 )-1 )*sizeof( T ) );
              if( !elem ) exit( EXIT_FAILURE );
          }

          for( j = b-1;  j > i+numtimes-1;  j-- ) elem[j] = elem[j-numtimes];
		  for( j = i;  j < i+numtimes;  j++ ) elem[j] = elem_;
          num = b;
      } else {  
          // num = 0
          elem = (T*)malloc( ( (DWORD)pow( 2.0, flooR( log( (valuE)numtimes )*INV_LN2 )+1.0 )-1 )*sizeof( T ) );
          if( !elem ) exit( EXIT_FAILURE );
		  for( j = 0;  j < numtimes;  j++ ) elem[j] = elem_;
          num = numtimes;
      }
  };




  template <typename T> void arraY__<T>::deletE( DWORD i ) {
      if( elem ) {
          if( num == 1 ) {
              deletealL();
          } else {
		      if( i >= num ) i = num-1;

		      for( register DWORD j = i;  j < num-1;  j++ ) elem[j] = elem[j+1];

              if( (DWORD)flooR( log( (valuE)num )*INV_LN2 ) > (DWORD)flooR( log( (valuE)( num-1 ) )*INV_LN2 ) ) {
                  elem = (T*)realloc( elem, ( (DWORD)pow( 2.0, flooR( log( (valuE)( num-1 ) )*INV_LN2 )+1.0 )-1 )*sizeof( T ) );
                  if( !elem ) exit( EXIT_FAILURE );
              }

              num--;
          }
      }
  };




  template <typename T> inline void arraY__<T>::deletealL( void ) {
      if( elem ) free( elem );
      
      reseT();
  };




  template <typename T> void arraY__<T>::releasE( DWORD i ) {
      if( elem ) {
          if( num == 1 ) {
              releasealL();
          } else {
			  if( i >= num ) i = num-1;

	          if( elem[i] ) {
		          elem[i]->deletealL();
		          elem[i] = NULL;
	          }
    	      for( register DWORD j = i;  j < num-1;  j++ ) elem[j] = elem[j+1];

              if( (DWORD)flooR( log( num )*INV_LN2 ) > (DWORD)flooR( log( num-1 )*INV_LN2 ) ) {
                  elem = (T*)realloc( elem, ( (DWORD)pow( 2.0, flooR( log( num-1 )*INV_LN2 )+1.0 )-1 )*sizeof( T ) );
                  if( !elem ) exit( EXIT_FAILURE );
              }

              num--;
          }
      }
  };




  template <typename T> inline void arraY__<T>::releasealL( void ) {
      for( register DWORD i = 0;  i < num;  i++ ) 
          if( elem[i] ) {
              elem[i]->deletealL();
              elem[i] = NULL;
          }

	  deletealL();
  };




  template <typename T> void arraY__<T>::copY( arraY__ *elema ) {
      if( elema ) {
          elema->deletealL();

	      if( elem ) {
              elema->elem = (T*)malloc( ( (DWORD)pow( 2.0, flooR( log( num )*INV_LN2 )+1.0 )-1 )*sizeof( T ) );
              if( !elema->elem ) exit( EXIT_FAILURE );
	    	  for( register DWORD j = 0;  j < num;  j++ ) elema->elem[j] = elem[j];
              elema->num = num;
	      }
      }
  };




  template <typename T> inline T arraY__<T>::operator()( DWORD i ) {
      if( i >= 0 /*&& i < n*/ && i < num ) return elem[i]; 
  };




  template <typename T> inline T arraY__<T>::operator()( DWORD i, DWORD j ) {
      DWORD a = i+j*n;

      if( i >= 0 && i < n && j >= 0 && j < m && a < num ) return elem[a]; 
  };




  template <typename T> inline T arraY__<T>::operator()( DWORD i, DWORD j, DWORD k ) {
      DWORD a = i+j*n+k*n*m;

      if( i >= 0 && i < n && j >= 0 && j < m && k >= 0 && k < l && a < num ) return elem[a]; 
  };
