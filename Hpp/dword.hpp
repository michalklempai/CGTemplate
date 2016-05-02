  
  // DWORDARRAY
  class dwordarraY: public arraY<DWORD> {};


  void sortasC( dwordarraY *dwa );
  void sortdesC( dwordarraY *dwa );






  void sortasC( dwordarraY *dwa ) {
      register DWORD i;
      BOOL sorted = FALSE;
      DWORD dw, j = 1;

      while( !sorted ) {
          sorted = TRUE;
          for( i = 0;  i < dwa->num-j;  i++ ) {
              if( dwa->elem[i] > dwa->elem[i+1] ) {
                  dw = dwa->elem[i];
                  dwa->elem[i] = dwa->elem[i+1];
                  dwa->elem[i+1] = dw;
                  sorted = FALSE;
              }
          }
          j++;
      }
  }




  void sortdesC( dwordarraY *dwa ) {
      register DWORD i;
      BOOL sorted = FALSE;
      DWORD dw, j = 1;

      while( !sorted ) {
          sorted = TRUE;
          for( i = 0;  i < dwa->num-j;  i++ ) {
              if( dwa->elem[i] < dwa->elem[i+1] ) {
                  dw = dwa->elem[i];
                  dwa->elem[i] = dwa->elem[i+1];
                  dwa->elem[i+1] = dw;
                  sorted = FALSE;
              }
          }
          j++;
      }
  }
