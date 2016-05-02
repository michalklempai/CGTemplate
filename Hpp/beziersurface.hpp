
  // BICUBICBEZIERSURFACE
  class bicubicbeziersurfacE {
      public:
  		  poinT P[4][4];


          bicubicbeziersurfacE( void ) { reseT(); };
          ~bicubicbeziersurfacE( void ) { deletealL(); };

          void reseT( void );
		  void deletealL( void );
		  void copY( bicubicbeziersurfacE *bbs );

          valuE B( DWORD i, valuE t );
		  valuE dB( DWORD i, valuE t );
		  valuE ddB( DWORD i, valuE t );
		  valuE dddB( DWORD i, valuE t );
		  poinT Q( valuE u, valuE v, poinT *A = NULL );
		  poinT dQu( valuE u, valuE v, poinT *dAu = NULL );
		  poinT dQv( valuE u, valuE v, poinT *dAv = NULL );
		  poinT ddQu( valuE u, valuE v, poinT *ddAu = NULL );
		  poinT ddQv( valuE u, valuE v, poinT *ddAv = NULL );
		  poinT dddQu( valuE u, valuE v, poinT *dddAu = NULL );
		  poinT dddQv( valuE u, valuE v, poinT *dddAv = NULL );
		  poinT decasteljaU( valuE u, valuE v, poinT *A = NULL );
          void splitU( valuE u, bicubicbeziersurfacE *bbbs_left, bicubicbeziersurfacE *bbbs_right );
          void splitV( valuE v, bicubicbeziersurfacE *bbbs_top, bicubicbeziersurfacE *bbbs_bottom );
  };                   








  inline void bicubicbeziersurfacE::reseT( void ) {
      P[0][0] = P[1][0] = P[2][0] = P[3][0] = 
      P[0][1] = P[1][1] = P[2][1] = P[3][1] = 
      P[0][2] = P[1][2] = P[2][2] = P[3][2] = 
      P[0][3] = P[1][3] = P[2][3] = P[3][3] = poinT();
  }

  


  inline void bicubicbeziersurfacE::deletealL( void ) {
	  reseT();
  }




  inline void bicubicbeziersurfacE::copY( bicubicbeziersurfacE *bbs ) {
      bbs->deletealL();

      bbs->P[0][0] = P[0][0];  bbs->P[1][0] = P[1][0];  bbs->P[2][0] = P[2][0];  bbs->P[3][0] = P[3][0];
      bbs->P[0][1] = P[0][1];  bbs->P[1][1] = P[1][1];  bbs->P[2][1] = P[2][1];  bbs->P[3][1] = P[3][1];
      bbs->P[0][2] = P[0][2];  bbs->P[1][2] = P[1][2];  bbs->P[2][2] = P[2][2];  bbs->P[3][2] = P[3][2];
      bbs->P[0][3] = P[0][3];  bbs->P[1][3] = P[1][3];  bbs->P[2][3] = P[2][3];  bbs->P[3][3] = P[3][3];
  }




  inline valuE bicubicbeziersurfacE::B( DWORD i, valuE t ) {
      if( i == 0 ) {
          return -t*t*t+3.0*t*t-3.0*t+1.0;
      } else 
      if( i == 1 ) {
          return 3.0*t*t*t-6.0*t*t+3.0*t;
      } else 
      if( i == 2 ) {
          return -3.0*t*t*t+3.0*t*t;
      } else 
      if( i == 3 ) {
          return t*t*t;
      }
  }




  inline valuE bicubicbeziersurfacE::dB( DWORD i, valuE t ) {
      if( i == 0 ) {
          return -3.0*t*t+6.0*t-3.0;
      } else 
      if( i == 1 ) {
          return 9.0*t*t-12.0*t+3.0;
      } else 
      if( i == 2 ) {
          return -9.0*t*t+6.0*t;
      } else 
      if( i == 3 ) {
          return 3.0*t*t;
      }
  }




  inline valuE bicubicbeziersurfacE::ddB( DWORD i, valuE t ) {
      if( i == 0 ) {
          return -6.0*t+6.0;
      } else 
      if( i == 1 ) {
          return 18.0*t-12.0;
      } else 
      if( i == 2 ) {
          return -18.0*t+6.0;
      } else 
      if( i == 3 ) {
          return 6.0*t;
      }
  }




  inline valuE bicubicbeziersurfacE::dddB( DWORD i, valuE t ) {
      if( i == 0 ) {
          return -6.0;
      } else 
      if( i == 1 ) {
          return 18.0;
      } else 
      if( i == 2 ) {
          return -18.0;
      } else 
      if( i == 3 ) {
          return 6.0;
      }
  }




  inline poinT bicubicbeziersurfacE::Q( valuE u, valuE v, poinT *A ) {
      valuE val[4][2];

      val[0][0] = B( 0, u );  val[1][0] = B( 1, u );  val[2][0] = B( 2, u );  val[3][0] = B( 3, u );
      val[0][1] = B( 0, v );  val[1][1] = B( 1, v );  val[2][1] = B( 2, v );  val[3][1] = B( 3, v );

      if( A ) return *A = P[0][0]*val[0][0]*val[0][1]+P[1][0]*val[1][0]*val[0][1]+P[2][0]*val[2][0]*val[0][1]+P[3][0]*val[3][0]*val[0][1]+
                          P[0][1]*val[0][0]*val[1][1]+P[1][1]*val[1][0]*val[1][1]+P[2][1]*val[2][0]*val[1][1]+P[3][1]*val[3][0]*val[1][1]+
                          P[0][2]*val[0][0]*val[2][1]+P[1][2]*val[1][0]*val[2][1]+P[2][2]*val[2][0]*val[2][1]+P[3][2]*val[3][0]*val[2][1]+
                          P[0][3]*val[0][0]*val[3][1]+P[1][3]*val[1][0]*val[3][1]+P[2][3]*val[2][0]*val[3][1]+P[3][3]*val[3][0]*val[3][1]; else
              return P[0][0]*val[0][0]*val[0][1]+P[1][0]*val[1][0]*val[0][1]+P[2][0]*val[2][0]*val[0][1]+P[3][0]*val[3][0]*val[0][1]+
                     P[0][1]*val[0][0]*val[1][1]+P[1][1]*val[1][0]*val[1][1]+P[2][1]*val[2][0]*val[1][1]+P[3][1]*val[3][0]*val[1][1]+
                     P[0][2]*val[0][0]*val[2][1]+P[1][2]*val[1][0]*val[2][1]+P[2][2]*val[2][0]*val[2][1]+P[3][2]*val[3][0]*val[2][1]+
                     P[0][3]*val[0][0]*val[3][1]+P[1][3]*val[1][0]*val[3][1]+P[2][3]*val[2][0]*val[3][1]+P[3][3]*val[3][0]*val[3][1];
   }




  inline poinT bicubicbeziersurfacE::dQu( valuE u, valuE v, poinT *dAu ) {
      valuE val[4][2];

      val[0][0] = dB( 0, u );  val[1][0] = dB( 1, u );  val[2][0] = dB( 2, u );  val[3][0] = dB( 3, u );
      val[0][1] = B( 0, v );  val[1][1] = B( 1, v );  val[2][1] = B( 2, v );  val[3][1] = B( 3, v );

      if( dAu ) return *dAu = P[0][0]*val[0][0]*val[0][1]+P[1][0]*val[1][0]*val[0][1]+P[2][0]*val[2][0]*val[0][1]+P[3][0]*val[3][0]*val[0][1]+
                              P[0][1]*val[0][0]*val[1][1]+P[1][1]*val[1][0]*val[1][1]+P[2][1]*val[2][0]*val[1][1]+P[3][1]*val[3][0]*val[1][1]+
                              P[0][2]*val[0][0]*val[2][1]+P[1][2]*val[1][0]*val[2][1]+P[2][2]*val[2][0]*val[2][1]+P[3][2]*val[3][0]*val[2][1]+
                              P[0][3]*val[0][0]*val[3][1]+P[1][3]*val[1][0]*val[3][1]+P[2][3]*val[2][0]*val[3][1]+P[3][3]*val[3][0]*val[3][1]; else
                return P[0][0]*val[0][0]*val[0][1]+P[1][0]*val[1][0]*val[0][1]+P[2][0]*val[2][0]*val[0][1]+P[3][0]*val[3][0]*val[0][1]+
                       P[0][1]*val[0][0]*val[1][1]+P[1][1]*val[1][0]*val[1][1]+P[2][1]*val[2][0]*val[1][1]+P[3][1]*val[3][0]*val[1][1]+
                       P[0][2]*val[0][0]*val[2][1]+P[1][2]*val[1][0]*val[2][1]+P[2][2]*val[2][0]*val[2][1]+P[3][2]*val[3][0]*val[2][1]+
                       P[0][3]*val[0][0]*val[3][1]+P[1][3]*val[1][0]*val[3][1]+P[2][3]*val[2][0]*val[3][1]+P[3][3]*val[3][0]*val[3][1]; 
  }




  inline poinT bicubicbeziersurfacE::dQv( valuE u, valuE v, poinT *dAv ) {
      valuE val[4][2];

      val[0][0] = B( 0, u );  val[1][0] = B( 1, u );  val[2][0] = B( 2, u );  val[3][0] = B( 3, u );
      val[0][1] = dB( 0, v );  val[1][1] = dB( 1, v );  val[2][1] = dB( 2, v );  val[3][1] = dB( 3, v );

      if( dAv ) return *dAv = P[0][0]*val[0][0]*val[0][1]+P[1][0]*val[1][0]*val[0][1]+P[2][0]*val[2][0]*val[0][1]+P[3][0]*val[3][0]*val[0][1]+
                              P[0][1]*val[0][0]*val[1][1]+P[1][1]*val[1][0]*val[1][1]+P[2][1]*val[2][0]*val[1][1]+P[3][1]*val[3][0]*val[1][1]+
                              P[0][2]*val[0][0]*val[2][1]+P[1][2]*val[1][0]*val[2][1]+P[2][2]*val[2][0]*val[2][1]+P[3][2]*val[3][0]*val[2][1]+
                              P[0][3]*val[0][0]*val[3][1]+P[1][3]*val[1][0]*val[3][1]+P[2][3]*val[2][0]*val[3][1]+P[3][3]*val[3][0]*val[3][1]; else
                return P[0][0]*val[0][0]*val[0][1]+P[1][0]*val[1][0]*val[0][1]+P[2][0]*val[2][0]*val[0][1]+P[3][0]*val[3][0]*val[0][1]+
                       P[0][1]*val[0][0]*val[1][1]+P[1][1]*val[1][0]*val[1][1]+P[2][1]*val[2][0]*val[1][1]+P[3][1]*val[3][0]*val[1][1]+
                       P[0][2]*val[0][0]*val[2][1]+P[1][2]*val[1][0]*val[2][1]+P[2][2]*val[2][0]*val[2][1]+P[3][2]*val[3][0]*val[2][1]+
                       P[0][3]*val[0][0]*val[3][1]+P[1][3]*val[1][0]*val[3][1]+P[2][3]*val[2][0]*val[3][1]+P[3][3]*val[3][0]*val[3][1];
  }




  inline poinT bicubicbeziersurfacE::ddQu( valuE u, valuE v, poinT *ddAu ) {
      valuE val[4][2];

      val[0][0] = ddB( 0, u );  val[1][0] = ddB( 1, u );  val[2][0] = ddB( 2, u );  val[3][0] = ddB( 3, u );
      val[0][1] = B( 0, v );  val[1][1] = B( 1, v );  val[2][1] = B( 2, v );  val[3][1] = B( 3, v );

      if( ddAu ) return *ddAu = P[0][0]*val[0][0]*val[0][1]+P[1][0]*val[1][0]*val[0][1]+P[2][0]*val[2][0]*val[0][1]+P[3][0]*val[3][0]*val[0][1]+
                                P[0][1]*val[0][0]*val[1][1]+P[1][1]*val[1][0]*val[1][1]+P[2][1]*val[2][0]*val[1][1]+P[3][1]*val[3][0]*val[1][1]+
                                P[0][2]*val[0][0]*val[2][1]+P[1][2]*val[1][0]*val[2][1]+P[2][2]*val[2][0]*val[2][1]+P[3][2]*val[3][0]*val[2][1]+
                                P[0][3]*val[0][0]*val[3][1]+P[1][3]*val[1][0]*val[3][1]+P[2][3]*val[2][0]*val[3][1]+P[3][3]*val[3][0]*val[3][1]; else
                 return P[0][0]*val[0][0]*val[0][1]+P[1][0]*val[1][0]*val[0][1]+P[2][0]*val[2][0]*val[0][1]+P[3][0]*val[3][0]*val[0][1]+
                        P[0][1]*val[0][0]*val[1][1]+P[1][1]*val[1][0]*val[1][1]+P[2][1]*val[2][0]*val[1][1]+P[3][1]*val[3][0]*val[1][1]+
                        P[0][2]*val[0][0]*val[2][1]+P[1][2]*val[1][0]*val[2][1]+P[2][2]*val[2][0]*val[2][1]+P[3][2]*val[3][0]*val[2][1]+
                        P[0][3]*val[0][0]*val[3][1]+P[1][3]*val[1][0]*val[3][1]+P[2][3]*val[2][0]*val[3][1]+P[3][3]*val[3][0]*val[3][1]; 
  }




  inline poinT bicubicbeziersurfacE::ddQv( valuE u, valuE v, poinT *ddAv ) {
      valuE val[4][2];

      val[0][0] = B( 0, u );  val[1][0] = B( 1, u );  val[2][0] = B( 2, u );  val[3][0] = B( 3, u );
      val[0][1] = ddB( 0, v );  val[1][1] = ddB( 1, v );  val[2][1] = ddB( 2, v );  val[3][1] = ddB( 3, v );

      if( ddAv ) return *ddAv = P[0][0]*val[0][0]*val[0][1]+P[1][0]*val[1][0]*val[0][1]+P[2][0]*val[2][0]*val[0][1]+P[3][0]*val[3][0]*val[0][1]+
                                P[0][1]*val[0][0]*val[1][1]+P[1][1]*val[1][0]*val[1][1]+P[2][1]*val[2][0]*val[1][1]+P[3][1]*val[3][0]*val[1][1]+
                                P[0][2]*val[0][0]*val[2][1]+P[1][2]*val[1][0]*val[2][1]+P[2][2]*val[2][0]*val[2][1]+P[3][2]*val[3][0]*val[2][1]+
                                P[0][3]*val[0][0]*val[3][1]+P[1][3]*val[1][0]*val[3][1]+P[2][3]*val[2][0]*val[3][1]+P[3][3]*val[3][0]*val[3][1]; else
                 return P[0][0]*val[0][0]*val[0][1]+P[1][0]*val[1][0]*val[0][1]+P[2][0]*val[2][0]*val[0][1]+P[3][0]*val[3][0]*val[0][1]+
                        P[0][1]*val[0][0]*val[1][1]+P[1][1]*val[1][0]*val[1][1]+P[2][1]*val[2][0]*val[1][1]+P[3][1]*val[3][0]*val[1][1]+
                        P[0][2]*val[0][0]*val[2][1]+P[1][2]*val[1][0]*val[2][1]+P[2][2]*val[2][0]*val[2][1]+P[3][2]*val[3][0]*val[2][1]+
                        P[0][3]*val[0][0]*val[3][1]+P[1][3]*val[1][0]*val[3][1]+P[2][3]*val[2][0]*val[3][1]+P[3][3]*val[3][0]*val[3][1]; 
  }




  inline poinT bicubicbeziersurfacE::dddQu( valuE u, valuE v, poinT *dddAu ) {
      valuE val[4][2];

      val[0][0] = dddB( 0, u );  val[1][0] = dddB( 1, u );  val[2][0] = dddB( 2, u );  val[3][0] = dddB( 3, u );
      val[0][1] = B( 0, v );  val[1][1] = B( 1, v );  val[2][1] = B( 2, v );  val[3][1] = B( 3, v );

      if( dddAu ) return *dddAu = P[0][0]*val[0][0]*val[0][1]+P[1][0]*val[1][0]*val[0][1]+P[2][0]*val[2][0]*val[0][1]+P[3][0]*val[3][0]*val[0][1]+
                                  P[0][1]*val[0][0]*val[1][1]+P[1][1]*val[1][0]*val[1][1]+P[2][1]*val[2][0]*val[1][1]+P[3][1]*val[3][0]*val[1][1]+
                                  P[0][2]*val[0][0]*val[2][1]+P[1][2]*val[1][0]*val[2][1]+P[2][2]*val[2][0]*val[2][1]+P[3][2]*val[3][0]*val[2][1]+
                                  P[0][3]*val[0][0]*val[3][1]+P[1][3]*val[1][0]*val[3][1]+P[2][3]*val[2][0]*val[3][1]+P[3][3]*val[3][0]*val[3][1]; else
                  return P[0][0]*val[0][0]*val[0][1]+P[1][0]*val[1][0]*val[0][1]+P[2][0]*val[2][0]*val[0][1]+P[3][0]*val[3][0]*val[0][1]+
                         P[0][1]*val[0][0]*val[1][1]+P[1][1]*val[1][0]*val[1][1]+P[2][1]*val[2][0]*val[1][1]+P[3][1]*val[3][0]*val[1][1]+
                         P[0][2]*val[0][0]*val[2][1]+P[1][2]*val[1][0]*val[2][1]+P[2][2]*val[2][0]*val[2][1]+P[3][2]*val[3][0]*val[2][1]+
                         P[0][3]*val[0][0]*val[3][1]+P[1][3]*val[1][0]*val[3][1]+P[2][3]*val[2][0]*val[3][1]+P[3][3]*val[3][0]*val[3][1]; 
  }




  inline poinT bicubicbeziersurfacE::dddQv( valuE u, valuE v, poinT *dddAv ) {
      valuE val[4][2];

      val[0][0] = B( 0, u );  val[1][0] = B( 1, u );  val[2][0] = B( 2, u );  val[3][0] = B( 3, u );
      val[0][1] = dddB( 0, v );  val[1][1] = dddB( 1, v );  val[2][1] = dddB( 2, v );  val[3][1] = dddB( 3, v );

      if( dddAv ) return *dddAv = P[0][0]*val[0][0]*val[0][1]+P[1][0]*val[1][0]*val[0][1]+P[2][0]*val[2][0]*val[0][1]+P[3][0]*val[3][0]*val[0][1]+
                                  P[0][1]*val[0][0]*val[1][1]+P[1][1]*val[1][0]*val[1][1]+P[2][1]*val[2][0]*val[1][1]+P[3][1]*val[3][0]*val[1][1]+
                                  P[0][2]*val[0][0]*val[2][1]+P[1][2]*val[1][0]*val[2][1]+P[2][2]*val[2][0]*val[2][1]+P[3][2]*val[3][0]*val[2][1]+
                                  P[0][3]*val[0][0]*val[3][1]+P[1][3]*val[1][0]*val[3][1]+P[2][3]*val[2][0]*val[3][1]+P[3][3]*val[3][0]*val[3][1]; else
                  return P[0][0]*val[0][0]*val[0][1]+P[1][0]*val[1][0]*val[0][1]+P[2][0]*val[2][0]*val[0][1]+P[3][0]*val[3][0]*val[0][1]+
                         P[0][1]*val[0][0]*val[1][1]+P[1][1]*val[1][0]*val[1][1]+P[2][1]*val[2][0]*val[1][1]+P[3][1]*val[3][0]*val[1][1]+
                         P[0][2]*val[0][0]*val[2][1]+P[1][2]*val[1][0]*val[2][1]+P[2][2]*val[2][0]*val[2][1]+P[3][2]*val[3][0]*val[2][1]+
                         P[0][3]*val[0][0]*val[3][1]+P[1][3]*val[1][0]*val[3][1]+P[2][3]*val[2][0]*val[3][1]+P[3][3]*val[3][0]*val[3][1];
  }




  inline poinT bicubicbeziersurfacE::decasteljaU( valuE u, valuE v, poinT *A ) {
      poinT W, left[4][4], right[4][4], top[4], bottom[4];


      left[0][0] = P[0][0];
      left[1][0] = P[0][0]+u*( P[1][0]-P[0][0] );
      W = P[1][0]+u*( P[2][0]-P[1][0] );
      left[2][0] = left[1][0]+u*( W-left[1][0] ); 
      right[3][0] = P[3][0];
      right[2][0] = P[2][0]+u*( P[3][0]-P[2][0] );
      right[1][0] = W+u*( right[2][0]-W );
      left[3][0] = right[0][0] = left[2][0]+u*( right[1][0]-left[2][0] );

      left[0][1] = P[0][1];
      left[1][1] = P[0][1]+u*( P[1][1]-P[0][1] );
      W = P[1][1]+u*( P[2][1]-P[1][1] );
      left[2][1] = left[1][1]+u*( W-left[1][1] ); 
      right[3][1] = P[3][1];
      right[2][1] = P[2][1]+u*( P[3][1]-P[2][1] );
      right[1][1] = W+u*( right[2][1]-W );
      left[3][1] = right[0][1] = left[2][1]+u*( right[1][1]-left[2][1] );

      left[0][2] = P[0][2];
      left[1][2] = P[0][2]+u*( P[1][2]-P[0][2] );
      W = P[1][2]+u*( P[2][2]-P[1][2] );
      left[2][2] = left[1][2]+u*( W-left[1][2] ); 
      right[3][2] = P[3][2];
      right[2][2] = P[2][2]+u*( P[3][2]-P[2][2] );
      right[1][2] = W+u*( right[2][2]-W );
      left[3][2] = right[0][2] = left[2][2]+u*( right[1][2]-left[2][2] );

      left[0][3] = P[0][3];
      left[1][3] = P[0][3]+u*( P[1][3]-P[0][3] );
      W = P[1][3]+u*( P[2][3]-P[1][3] );
      left[2][3] = left[1][3]+u*( W-left[1][3] ); 
      right[3][3] = P[3][3];
      right[2][3] = P[2][3]+u*( P[3][3]-P[2][3] );
      right[1][3] = W+u*( right[2][3]-W );
      left[3][3] = right[0][3] = left[2][3]+u*( right[1][3]-left[2][3] );


      top[0] = left[3][0];
      top[1] = left[3][0]+v*( left[3][1]-left[3][0] );
      W = left[3][1]+v*( left[3][2]-left[3][1] );
      top[2] = top[1]+v*( W-top[1] ); 
      bottom[3] = left[3][3];
      bottom[2] = left[3][2]+v*( left[3][3]-left[3][2] );
      bottom[1] = W+v*( bottom[2]-W );

      if( A ) return *A = top[3] = bottom[0] = top[2]+v*( bottom[1]-top[2] ); else
              return top[3] = bottom[0] = top[2]+v*( bottom[1]-top[2] ); 
  }




  inline void bicubicbeziersurfacE::splitU( valuE u, bicubicbeziersurfacE *bbs_left, bicubicbeziersurfacE *bbs_right ) {
      poinT W;


      bbs_left->deletealL();
      bbs_right->deletealL();

      bbs_left->P[0][0] = P[0][0];
      bbs_left->P[1][0] = P[0][0]+u*( P[1][0]-P[0][0] );
      W = P[1][0]+u*( P[2][0]-P[1][0] );
      bbs_left->P[2][0] = bbs_left->P[1][0]+u*( W-bbs_left->P[1][0] ); 
      bbs_right->P[3][0] = P[3][0];
      bbs_right->P[2][0] = P[2][0]+u*( P[3][0]-P[2][0] );
      bbs_right->P[1][0] = W+u*( bbs_right->P[2][0]-W );
      bbs_left->P[3][0] = bbs_right->P[0][0] = bbs_left->P[2][0]+u*( bbs_right->P[1][0]-bbs_left->P[2][0] );

      bbs_left->P[0][1] = P[0][1];
      bbs_left->P[1][1] = P[0][1]+u*( P[1][1]-P[0][1] );
      W = P[1][1]+u*( P[2][1]-P[1][1] );
      bbs_left->P[2][1] = bbs_left->P[1][1]+u*( W-bbs_left->P[1][1] ); 
      bbs_right->P[3][1] = P[3][1];
      bbs_right->P[2][1] = P[2][1]+u*( P[3][1]-P[2][1] );
      bbs_right->P[1][1] = W+u*( bbs_right->P[2][1]-W );
      bbs_left->P[3][1] = bbs_right->P[0][1] = bbs_left->P[2][1]+u*( bbs_right->P[1][1]-bbs_left->P[2][1] );

      bbs_left->P[0][2] = P[0][2];
      bbs_left->P[1][2] = P[0][2]+u*( P[1][2]-P[0][2] );
      W = P[1][2]+u*( P[2][2]-P[1][2] );
      bbs_left->P[2][2] = bbs_left->P[1][2]+u*( W-bbs_left->P[1][2] ); 
      bbs_right->P[3][2] = P[3][2];
      bbs_right->P[2][2] = P[2][2]+u*( P[3][2]-P[2][2] );
      bbs_right->P[1][2] = W+u*( bbs_right->P[2][2]-W );
      bbs_left->P[3][2] = bbs_right->P[0][2] = bbs_left->P[2][2]+u*( bbs_right->P[1][2]-bbs_left->P[2][2] );

      bbs_left->P[0][3] = P[0][3];
      bbs_left->P[1][3] = P[0][3]+u*( P[1][3]-P[0][3] );
      W = P[1][3]+u*( P[2][3]-P[1][3] );
      bbs_left->P[2][3] = bbs_left->P[1][3]+u*( W-bbs_left->P[1][3] ); 
      bbs_right->P[3][3] = P[3][3];
      bbs_right->P[2][3] = P[2][3]+u*( P[3][3]-P[2][3] );
      bbs_right->P[1][3] = W+u*( bbs_right->P[2][3]-W );
      bbs_left->P[3][3] = bbs_right->P[0][3] = bbs_left->P[2][3]+u*( bbs_right->P[1][3]-bbs_left->P[2][3] );
  }




  inline void bicubicbeziersurfacE::splitV( valuE v, bicubicbeziersurfacE *bbs_top, bicubicbeziersurfacE *bbs_bottom ) {
      poinT W;


      bbs_top->deletealL();
      bbs_bottom->deletealL();

      bbs_top->P[0][0] = P[0][0];
      bbs_top->P[0][1] = P[0][0]+v*( P[0][1]-P[0][0] );
      W = P[0][1]+v*( P[0][2]-P[0][1] );
      bbs_top->P[0][2] = bbs_top->P[0][1]+v*( W-bbs_top->P[0][1] ); 
      bbs_bottom->P[0][3] = P[0][3];
      bbs_bottom->P[0][2] = P[0][2]+v*( P[0][3]-P[0][2] );
      bbs_bottom->P[0][1] = W+v*( bbs_bottom->P[0][2]-W );
      bbs_top->P[0][3] = bbs_bottom->P[0][0] = bbs_top->P[0][2]+v*( bbs_bottom->P[0][1]-bbs_top->P[0][2] );

      bbs_top->P[1][0] = P[1][0];
      bbs_top->P[1][1] = P[1][0]+v*( P[1][1]-P[1][0] );
      W = P[1][1]+v*( P[1][2]-P[1][1] );
      bbs_top->P[1][2] = bbs_top->P[1][1]+v*( W-bbs_top->P[1][1] ); 
      bbs_bottom->P[1][3] = P[1][3];
      bbs_bottom->P[1][2] = P[1][2]+v*( P[1][3]-P[1][2] );
      bbs_bottom->P[1][1] = W+v*( bbs_bottom->P[1][2]-W );
      bbs_top->P[1][3] = bbs_bottom->P[1][0] = bbs_top->P[1][2]+v*( bbs_bottom->P[1][1]-bbs_top->P[1][2] );

      bbs_top->P[2][0] = P[2][0];
      bbs_top->P[2][1] = P[2][0]+v*( P[2][1]-P[2][0] );
      W = P[2][1]+v*( P[2][2]-P[2][1] );
      bbs_top->P[2][2] = bbs_top->P[2][1]+v*( W-bbs_top->P[2][1] ); 
      bbs_bottom->P[2][3] = P[2][3];
      bbs_bottom->P[2][2] = P[2][2]+v*( P[2][3]-P[2][2] );
      bbs_bottom->P[2][1] = W+v*( bbs_bottom->P[2][2]-W );
      bbs_top->P[2][3] = bbs_bottom->P[2][0] = bbs_top->P[2][2]+v*( bbs_bottom->P[2][1]-bbs_top->P[2][2] );

      bbs_top->P[3][0] = P[3][0];
      bbs_top->P[3][1] = P[3][0]+v*( P[3][1]-P[3][0] );
      W = P[3][1]+v*( P[3][2]-P[3][1] );
      bbs_top->P[3][2] = bbs_top->P[3][1]+v*( W-bbs_top->P[3][1] ); 
      bbs_bottom->P[3][3] = P[3][3];
      bbs_bottom->P[3][2] = P[3][2]+v*( P[3][3]-P[3][2] );
      bbs_bottom->P[3][1] = W+v*( bbs_bottom->P[3][2]-W );
      bbs_top->P[3][3] = bbs_bottom->P[3][0] = bbs_top->P[3][2]+v*( bbs_bottom->P[3][1]-bbs_top->P[3][2] );
  }








  // BICUBICBEZIERSURFACEARRAY
  class bicubicbeziersurfacearraY: public arraY_<bicubicbeziersurfacE> {};


  // LPBICUBICBEZIERSURFACE
  typedef bicubicbeziersurfacE* lpbicubicbeziersurfacE;


  // LPBICUBICBEZIERSURFACEARRAY
  class lpbicubicbeziersurfacearraY: public arraY__<lpbicubicbeziersurfacE> {};
















  // RATIONALBICUBICBEZIERSURFACE
  class rationalbicubicbeziersurfacE {
      private:


      public:
  		  poinT P[4][4];
  		  valuE w[4][4];


          rationalbicubicbeziersurfacE( void ) { reseT(); };
          ~rationalbicubicbeziersurfacE( void ) { deletealL(); };

          void reseT( void );
		  void deletealL( void );
		  void copY( rationalbicubicbeziersurfacE *rbbs );

          valuE B( DWORD i, valuE t );
		  valuE dB( DWORD i, valuE t );
		  poinT Q( valuE u, valuE v, poinT *A = NULL );
		  poinT dQu( valuE u, valuE v, poinT *dAu = NULL ); // je spravene ale blbo treba prerobit, aj NURBS
		  poinT dQv( valuE u, valuE v, poinT *dAv = NULL ); // je spravene ale blbo treba prerobit, aj NURBS
		  poinT decasteljaU( valuE u, valuE v, poinT *A = NULL );
          void splitU( valuE u, rationalbicubicbeziersurfacE *rbbs_left, rationalbicubicbeziersurfacE *rbbs_right );
          void splitV( valuE v, rationalbicubicbeziersurfacE *rbbs_top, rationalbicubicbeziersurfacE *rbbs_bottom );
  };                   






  inline void rationalbicubicbeziersurfacE::reseT( void ) {
      P[0][0] = P[1][0] = P[2][0] = P[3][0] = 
      P[0][1] = P[1][1] = P[2][1] = P[3][1] = 
      P[0][2] = P[1][2] = P[2][2] = P[3][2] = 
      P[0][3] = P[1][3] = P[2][3] = P[3][3] = poinT();
      w[0][0] = w[1][0] = w[2][0] = w[3][0] = 
      w[0][1] = w[1][1] = w[2][1] = w[3][1] = 
      w[0][2] = w[1][2] = w[2][2] = w[3][2] = 
      w[0][3] = w[1][3] = w[2][3] = w[3][3] = 0.0;
  }

  


  inline void rationalbicubicbeziersurfacE::deletealL( void ) {

	  reseT();
  }




  inline void rationalbicubicbeziersurfacE::copY( rationalbicubicbeziersurfacE *rbbs ) {
      rbbs->deletealL();

      rbbs->P[0][0] = P[0][0];  rbbs->P[1][0] = P[1][0];  rbbs->P[2][0] = P[2][0];  rbbs->P[3][0] = P[3][0];
      rbbs->P[0][1] = P[0][1];  rbbs->P[1][1] = P[1][1];  rbbs->P[2][1] = P[2][1];  rbbs->P[3][1] = P[3][1];
      rbbs->P[0][2] = P[0][2];  rbbs->P[1][2] = P[1][2];  rbbs->P[2][2] = P[2][2];  rbbs->P[3][2] = P[3][2];
      rbbs->P[0][3] = P[0][3];  rbbs->P[1][3] = P[1][3];  rbbs->P[2][3] = P[2][3];  rbbs->P[3][3] = P[3][3];
      rbbs->w[0][0] = w[0][0];  rbbs->w[1][0] = w[1][0];  rbbs->w[2][0] = w[2][0];  rbbs->w[3][0] = w[3][0];
      rbbs->w[0][1] = w[0][1];  rbbs->w[1][1] = w[1][1];  rbbs->w[2][1] = w[2][1];  rbbs->w[3][1] = w[3][1];
      rbbs->w[0][2] = w[0][2];  rbbs->w[1][2] = w[1][2];  rbbs->w[2][2] = w[2][2];  rbbs->w[3][2] = w[3][2];
      rbbs->w[0][3] = w[0][3];  rbbs->w[1][3] = w[1][3];  rbbs->w[2][3] = w[2][3];  rbbs->w[3][3] = w[3][3];
  }




  inline valuE rationalbicubicbeziersurfacE::B( DWORD i, valuE t ) {
      if( i == 0 ) {
          return -t*t*t+3.0*t*t-3.0*t+1.0;
      } else 
      if( i == 1 ) {
          return 3.0*t*t*t-6.0*t*t+3.0*t;
      } else 
      if( i == 2 ) {
          return -3.0*t*t*t+3.0*t*t;
      } else 
      if( i == 3 ) {
          return t*t*t;
      }
  }




  inline valuE rationalbicubicbeziersurfacE::dB( DWORD i, valuE t ) {
      if( i == 0 ) {
          return -3.0*t*t+6.0*t-3.0;
      } else 
      if( i == 1 ) {
          return 9.0*t*t-12.0*t+3.0;
      } else 
      if( i == 2 ) {
          return -9.0*t*t+6.0*t;
      } else 
      if( i == 3 ) {
          return 3.0*t*t;
      }
  }




  inline poinT rationalbicubicbeziersurfacE::Q( valuE u, valuE v, poinT *A ) {
      register DWORD i, j;
      valuE a, b, c;
      poinT Q;


      b = 0.0;
      Q = poinT( 0.0, 0.0, 0.0 );
      for( i = 0;  i < 4;  i++ ) {
          c = B( i, u );
          for( j = 0;  j < 4;  j++ ) {
      	      a = w[i][j]*c*B( j, v );
	    	  Q+=P[i][j]*a;
              b+=a;
          }
      }

	  if( A ) return *A = Q/b; else return Q/b;
   }




  inline poinT rationalbicubicbeziersurfacE::dQu( valuE u, valuE v, poinT *dAu ) {
      vectoR w;

      w = normalizE( Q( u+EPSILON, v )-Q( u, v ) );

      if( dAu ) return *dAu = poinT( w.x, w.y, w.z ); else return poinT( w.x, w.y, w.z );
  }




  inline poinT rationalbicubicbeziersurfacE::dQv( valuE u, valuE v, poinT *dAv ) {
      vectoR w;

      w = normalizE( Q( u, v+EPSILON )-Q( u, v ) );

      if( dAv ) return *dAv = poinT( w.x, w.y, w.z ); else return poinT( w.x, w.y, w.z );
  }




  inline poinT rationalbicubicbeziersurfacE::decasteljaU( valuE u, valuE v, poinT *A ) {
      valuE val, left_w[4][4], right_w[4][4], top_w[4], bottom_w[4];
      poinT W, PP[4][4], left_P[4][4], right_P[4][4], top_P[4], bottom_P[4];


      PP[0][0] = P[0][0]*w[0][0];  PP[1][0] = P[1][0]*w[1][0];  PP[2][0] = P[2][0]*w[2][0];  PP[3][0] = P[3][0]*w[3][0];
      PP[0][1] = P[0][1]*w[0][1];  PP[1][1] = P[1][1]*w[1][1];  PP[2][1] = P[2][1]*w[2][1];  PP[3][1] = P[3][1]*w[3][1];
      PP[0][2] = P[0][2]*w[0][2];  PP[1][2] = P[1][2]*w[1][2];  PP[2][2] = P[2][2]*w[2][2];  PP[3][2] = P[3][2]*w[3][2];
      PP[0][3] = P[0][3]*w[0][3];  PP[1][3] = P[1][3]*w[1][3];  PP[2][3] = P[2][3]*w[2][3];  PP[3][3] = P[3][3]*w[3][3];

      left_P[0][0] = PP[0][0];
      left_P[1][0] = PP[0][0]+u*( PP[1][0]-PP[0][0] );
      W = PP[1][0]+u*( PP[2][0]-PP[1][0] );
      left_P[2][0] = left_P[1][0]+u*( W-left_P[1][0] ); 
      right_P[3][0] = PP[3][0];
      right_P[2][0] = PP[2][0]+u*( PP[3][0]-PP[2][0] );
      right_P[1][0] = W+u*( right_P[2][0]-W );
      left_P[3][0] = right_P[0][0] = left_P[2][0]+u*( right_P[1][0]-left_P[2][0] );
      left_w[0][0] = w[0][0];
      left_w[1][0] = w[0][0]+u*( w[1][0]-w[0][0] );
      val = w[1][0]+u*( w[2][0]-w[1][0] );
      left_w[2][0] = left_w[1][0]+u*( val-left_w[1][0] ); 
      right_w[3][0] = w[3][0];
      right_w[2][0] = w[2][0]+u*( w[3][0]-w[2][0] );
      right_w[1][0] = val+u*( right_w[2][0]-val );
      left_w[3][0] = right_w[0][0] = left_w[2][0]+u*( right_w[1][0]-left_w[2][0] );

      left_P[0][1] = PP[0][1];
      left_P[1][1] = PP[0][1]+u*( PP[1][1]-PP[0][1] );
      W = PP[1][1]+u*( PP[2][1]-PP[1][1] );
      left_P[2][1] = left_P[1][1]+u*( W-left_P[1][1] ); 
      right_P[3][1] = PP[3][1];
      right_P[2][1] = PP[2][1]+u*( PP[3][1]-PP[2][1] );
      right_P[1][1] = W+u*( right_P[2][1]-W );
      left_P[3][1] = right_P[0][1] = left_P[2][1]+u*( right_P[1][1]-left_P[2][1] );
      left_w[0][1] = w[0][1];
      left_w[1][1] = w[0][1]+u*( w[1][1]-w[0][1] );
      val = w[1][1]+u*( w[2][1]-w[1][1] );
      left_w[2][1] = left_w[1][1]+u*( val-left_w[1][1] ); 
      right_w[3][1] = w[3][1];
      right_w[2][1] = w[2][1]+u*( w[3][1]-w[2][1] );
      right_w[1][1] = val+u*( right_w[2][1]-val );
      left_w[3][1] = right_w[0][1] = left_w[2][1]+u*( right_w[1][1]-left_w[2][1] );

      left_P[0][2] = PP[0][2];
      left_P[1][2] = PP[0][2]+u*( PP[1][2]-PP[0][2] );
      W = PP[1][2]+u*( PP[2][2]-PP[1][2] );
      left_P[2][2] = left_P[1][2]+u*( W-left_P[1][2] ); 
      right_P[3][2] = PP[3][2];
      right_P[2][2] = PP[2][2]+u*( PP[3][2]-PP[2][2] );
      right_P[1][2] = W+u*( right_P[2][2]-W );
      left_P[3][2] = right_P[0][2] = left_P[2][2]+u*( right_P[1][2]-left_P[2][2] );
      left_w[0][2] = w[0][2];
      left_w[1][2] = w[0][2]+u*( w[1][2]-w[0][2] );
      val = w[1][2]+u*( w[2][2]-w[1][2] );
      left_w[2][2] = left_w[1][2]+u*( val-left_w[1][2] ); 
      right_w[3][2] = w[3][2];
      right_w[2][2] = w[2][2]+u*( w[3][2]-w[2][2] );
      right_w[1][2] = val+u*( right_w[2][2]-val );
      left_w[3][2] = right_w[0][2] = left_w[2][2]+u*( right_w[1][2]-left_w[2][2] );

      left_P[0][3] = PP[0][3];
      left_P[1][3] = PP[0][3]+u*( PP[1][3]-PP[0][3] );
      W = PP[1][3]+u*( PP[2][3]-PP[1][3] );
      left_P[2][3] = left_P[1][3]+u*( W-left_P[1][3] ); 
      right_P[3][3] = PP[3][3];
      right_P[2][3] = PP[2][3]+u*( PP[3][3]-PP[2][3] );
      right_P[1][3] = W+u*( right_P[2][3]-W );
      left_P[3][3] = right_P[0][3] = left_P[2][3]+u*( right_P[1][3]-left_P[2][3] );
      left_w[0][3] = w[0][3];
      left_w[1][3] = w[0][3]+u*( w[1][3]-w[0][3] );
      val = w[1][3]+u*( w[2][3]-w[1][3] );
      left_w[2][3] = left_w[1][3]+u*( val-left_w[1][3] ); 
      right_w[3][3] = w[3][3];
      right_w[2][3] = w[2][3]+u*( w[3][3]-w[2][3] );
      right_w[1][3] = val+u*( right_w[2][3]-val );
      left_w[3][3] = right_w[0][3] = left_w[2][3]+u*( right_w[1][3]-left_w[2][3] );


      top_P[0] = left_P[3][0];
      top_P[1] = left_P[3][0]+v*( left_P[3][1]-left_P[3][0] );
      W = left_P[3][1]+v*( left_P[3][2]-left_P[3][1] );
      top_P[2] = top_P[1]+v*( W-top_P[1] ); 
      bottom_P[3] = left_P[3][3];
      bottom_P[2] = left_P[3][2]+v*( left_P[3][3]-left_P[3][2] );
      bottom_P[1] = W+v*( bottom_P[2]-W );
      top_P[3] = bottom_P[0] = top_P[2]+v*( bottom_P[1]-top_P[2] );
      top_w[0] = left_w[3][0];
      top_w[1] = left_w[3][0]+v*( left_w[3][1]-left_w[3][0] );
      val = left_w[3][1]+v*( left_w[3][2]-left_w[3][1] );
      top_w[2] = top_w[1]+v*( val-top_w[1] ); 
      bottom_w[3] = left_w[3][3];
      bottom_w[2] = left_w[3][2]+v*( left_w[3][3]-left_w[3][2] );
      bottom_w[1] = val+v*( bottom_w[2]-val );
      top_w[3] = bottom_w[0] = top_w[2]+v*( bottom_w[1]-top_w[2] );

      if( A ) return *A = top_P[3]/top_w[3]; else return top_P[3]/top_w[3];
  }




  inline void rationalbicubicbeziersurfacE::splitU( valuE u, rationalbicubicbeziersurfacE *rbbs_left, rationalbicubicbeziersurfacE *rbbs_right ) {
      valuE val;
      poinT W, PP[4][4];


      rbbs_left->deletealL();
      rbbs_right->deletealL();

      PP[0][0] = P[0][0]*w[0][0];  PP[1][0] = P[1][0]*w[1][0];  PP[2][0] = P[2][0]*w[2][0];  PP[3][0] = P[3][0]*w[3][0];
      PP[0][1] = P[0][1]*w[0][1];  PP[1][1] = P[1][1]*w[1][1];  PP[2][1] = P[2][1]*w[2][1];  PP[3][1] = P[3][1]*w[3][1];
      PP[0][2] = P[0][2]*w[0][2];  PP[1][2] = P[1][2]*w[1][2];  PP[2][2] = P[2][2]*w[2][2];  PP[3][2] = P[3][2]*w[3][2];
      PP[0][3] = P[0][3]*w[0][3];  PP[1][3] = P[1][3]*w[1][3];  PP[2][3] = P[2][3]*w[2][3];  PP[3][3] = P[3][3]*w[3][3];

      rbbs_left->P[0][0] = PP[0][0];
      rbbs_left->P[1][0] = PP[0][0]+u*( PP[1][0]-PP[0][0] );
      W = PP[1][0]+u*( PP[2][0]-PP[1][0] );
      rbbs_left->P[2][0] = rbbs_left->P[1][0]+u*( W-rbbs_left->P[1][0] ); 
      rbbs_right->P[3][0] = PP[3][0];
      rbbs_right->P[2][0] = PP[2][0]+u*( PP[3][0]-PP[2][0] );
      rbbs_right->P[1][0] = W+u*( rbbs_right->P[2][0]-W );
      rbbs_left->P[3][0] = rbbs_right->P[0][0] = rbbs_left->P[2][0]+u*( rbbs_right->P[1][0]-rbbs_left->P[2][0] );
      rbbs_left->w[0][0] = w[0][0];
      rbbs_left->w[1][0] = w[0][0]+u*( w[1][0]-w[0][0] );
      val = w[1][0]+u*( w[2][0]-w[1][0] );
      rbbs_left->w[2][0] = rbbs_left->w[1][0]+u*( val-rbbs_left->w[1][0] ); 
      rbbs_right->w[3][0] = w[3][0];
      rbbs_right->w[2][0] = w[2][0]+u*( w[3][0]-w[2][0] );
      rbbs_right->w[1][0] = val+u*( rbbs_right->w[2][0]-val );
      rbbs_left->w[3][0] = rbbs_right->w[0][0] = rbbs_left->w[2][0]+u*( rbbs_right->w[1][0]-rbbs_left->w[2][0] );

      rbbs_left->P[0][1] = PP[0][1];
      rbbs_left->P[1][1] = PP[0][1]+u*( PP[1][1]-PP[0][1] );
      W = PP[1][1]+u*( PP[2][1]-PP[1][1] );
      rbbs_left->P[2][1] = rbbs_left->P[1][1]+u*( W-rbbs_left->P[1][1] ); 
      rbbs_right->P[3][1] = PP[3][1];
      rbbs_right->P[2][1] = PP[2][1]+u*( PP[3][1]-PP[2][1] );
      rbbs_right->P[1][1] = W+u*( rbbs_right->P[2][1]-W );
      rbbs_left->P[3][1] = rbbs_right->P[0][1] = rbbs_left->P[2][1]+u*( rbbs_right->P[1][1]-rbbs_left->P[2][1] );
      rbbs_left->w[0][1] = w[0][1];
      rbbs_left->w[1][1] = w[0][1]+u*( w[1][1]-w[0][1] );
      val = w[1][1]+u*( w[2][1]-w[1][1] );
      rbbs_left->w[2][1] = rbbs_left->w[1][1]+u*( val-rbbs_left->w[1][1] ); 
      rbbs_right->w[3][1] = w[3][1];
      rbbs_right->w[2][1] = w[2][1]+u*( w[3][1]-w[2][1] );
      rbbs_right->w[1][1] = val+u*( rbbs_right->w[2][1]-val );
      rbbs_left->w[3][1] = rbbs_right->w[0][1] = rbbs_left->w[2][1]+u*( rbbs_right->w[1][1]-rbbs_left->w[2][1] );

      rbbs_left->P[0][2] = PP[0][2];
      rbbs_left->P[1][2] = PP[0][2]+u*( PP[1][2]-PP[0][2] );
      W = PP[1][2]+u*( PP[2][2]-PP[1][2] );
      rbbs_left->P[2][2] = rbbs_left->P[1][2]+u*( W-rbbs_left->P[1][2] ); 
      rbbs_right->P[3][2] = PP[3][2];
      rbbs_right->P[2][2] = PP[2][2]+u*( PP[3][2]-PP[2][2] );
      rbbs_right->P[1][2] = W+u*( rbbs_right->P[2][2]-W );
      rbbs_left->P[3][2] = rbbs_right->P[0][2] = rbbs_left->P[2][2]+u*( rbbs_right->P[1][2]-rbbs_left->P[2][2] );
      rbbs_left->w[0][2] = w[0][2];
      rbbs_left->w[1][2] = w[0][2]+u*( w[1][2]-w[0][2] );
      val = w[1][2]+u*( w[2][2]-w[1][2] );
      rbbs_left->w[2][2] = rbbs_left->w[1][2]+u*( val-rbbs_left->w[1][2] ); 
      rbbs_right->w[3][2] = w[3][2];
      rbbs_right->w[2][2] = w[2][2]+u*( w[3][2]-w[2][2] );
      rbbs_right->w[1][2] = val+u*( rbbs_right->w[2][2]-val );
      rbbs_left->w[3][2] = rbbs_right->w[0][2] = rbbs_left->w[2][2]+u*( rbbs_right->w[1][2]-rbbs_left->w[2][2] );

      rbbs_left->P[0][3] = PP[0][3];
      rbbs_left->P[1][3] = PP[0][3]+u*( PP[1][3]-PP[0][3] );
      W = PP[1][3]+u*( PP[2][3]-PP[1][3] );
      rbbs_left->P[2][3] = rbbs_left->P[1][3]+u*( W-rbbs_left->P[1][3] ); 
      rbbs_right->P[3][3] = PP[3][3];
      rbbs_right->P[2][3] = PP[2][3]+u*( PP[3][3]-PP[2][3] );
      rbbs_right->P[1][3] = W+u*( rbbs_right->P[2][3]-W );
      rbbs_left->P[3][3] = rbbs_right->P[0][3] = rbbs_left->P[2][3]+u*( rbbs_right->P[1][3]-rbbs_left->P[2][3] );
      rbbs_left->w[0][3] = w[0][3];
      rbbs_left->w[1][3] = w[0][3]+u*( w[1][3]-w[0][3] );
      val = w[1][3]+u*( w[2][3]-w[1][3] );
      rbbs_left->w[2][3] = rbbs_left->w[1][3]+u*( val-rbbs_left->w[1][3] ); 
      rbbs_right->w[3][3] = w[3][3];
      rbbs_right->w[2][3] = w[2][3]+u*( w[3][3]-w[2][3] );
      rbbs_right->w[1][3] = val+u*( rbbs_right->w[2][3]-val );
      rbbs_left->w[3][3] = rbbs_right->w[0][3] = rbbs_left->w[2][3]+u*( rbbs_right->w[1][3]-rbbs_left->w[2][3] );

      rbbs_left->P[0][0]/=rbbs_left->w[0][0];  rbbs_left->P[1][0]/=rbbs_left->w[1][0];  rbbs_left->P[2][0]/=rbbs_left->w[2][0];  rbbs_left->P[3][0]/=rbbs_left->w[3][0];
      rbbs_left->P[0][1]/=rbbs_left->w[0][1];  rbbs_left->P[1][1]/=rbbs_left->w[1][1];  rbbs_left->P[2][1]/=rbbs_left->w[2][2];  rbbs_left->P[3][1]/=rbbs_left->w[3][1];
      rbbs_left->P[0][2]/=rbbs_left->w[0][2];  rbbs_left->P[1][2]/=rbbs_left->w[1][2];  rbbs_left->P[2][2]/=rbbs_left->w[2][2];  rbbs_left->P[3][2]/=rbbs_left->w[3][2];
      rbbs_left->P[0][3]/=rbbs_left->w[0][3];  rbbs_left->P[1][3]/=rbbs_left->w[1][3];  rbbs_left->P[2][3]/=rbbs_left->w[2][3];  rbbs_left->P[3][3]/=rbbs_left->w[3][3];
      rbbs_right->P[0][0]/=rbbs_right->w[0][0];  rbbs_right->P[1][0]/=rbbs_right->w[1][0];  rbbs_right->P[2][0]/=rbbs_right->w[2][0];  rbbs_right->P[3][0]/=rbbs_right->w[3][0];
      rbbs_right->P[0][1]/=rbbs_right->w[0][1];  rbbs_right->P[1][1]/=rbbs_right->w[1][1];  rbbs_right->P[2][1]/=rbbs_right->w[2][2];  rbbs_right->P[3][1]/=rbbs_right->w[3][1];
      rbbs_right->P[0][2]/=rbbs_right->w[0][2];  rbbs_right->P[1][2]/=rbbs_right->w[1][2];  rbbs_right->P[2][2]/=rbbs_right->w[2][2];  rbbs_right->P[3][2]/=rbbs_right->w[3][2];
      rbbs_right->P[0][3]/=rbbs_right->w[0][3];  rbbs_right->P[1][3]/=rbbs_right->w[1][3];  rbbs_right->P[2][3]/=rbbs_right->w[2][3];  rbbs_right->P[3][3]/=rbbs_right->w[3][3];
  }




  inline void rationalbicubicbeziersurfacE::splitV( valuE v, rationalbicubicbeziersurfacE *rbbs_top, rationalbicubicbeziersurfacE *rbbs_bottom ) {
      valuE val;
      poinT W, PP[4][4];


      rbbs_top->deletealL();
      rbbs_bottom->deletealL();

      PP[0][0] = P[0][0]*w[0][0];  PP[1][0] = P[1][0]*w[1][0];  PP[2][0] = P[2][0]*w[2][0];  PP[3][0] = P[3][0]*w[3][0];
      PP[0][1] = P[0][1]*w[0][1];  PP[1][1] = P[1][1]*w[1][1];  PP[2][1] = P[2][1]*w[2][1];  PP[3][1] = P[3][1]*w[3][1];
      PP[0][2] = P[0][2]*w[0][2];  PP[1][2] = P[1][2]*w[1][2];  PP[2][2] = P[2][2]*w[2][2];  PP[3][2] = P[3][2]*w[3][2];
      PP[0][3] = P[0][3]*w[0][3];  PP[1][3] = P[1][3]*w[1][3];  PP[2][3] = P[2][3]*w[2][3];  PP[3][3] = P[3][3]*w[3][3];

      rbbs_top->P[0][0] = PP[0][0];
      rbbs_top->P[0][1] = PP[0][0]+v*( PP[0][1]-PP[0][0] );
      W = PP[0][1]+v*( PP[0][2]-PP[0][1] );
      rbbs_top->P[0][2] = rbbs_top->P[0][1]+v*( W-rbbs_top->P[0][1] ); 
      rbbs_bottom->P[0][3] = PP[0][3];
      rbbs_bottom->P[0][2] = PP[0][2]+v*( PP[0][3]-PP[0][2] );
      rbbs_bottom->P[0][1] = W+v*( rbbs_bottom->P[0][2]-W );
      rbbs_top->P[0][3] = rbbs_bottom->P[0][0] = rbbs_top->P[0][2]+v*( rbbs_bottom->P[0][1]-rbbs_top->P[0][2] );
      rbbs_top->w[0][0] = w[0][0];
      rbbs_top->w[0][1] = w[0][0]+v*( w[0][1]-w[0][0] );
      val = w[0][1]+v*( w[0][2]-w[0][1] );
      rbbs_top->w[0][2] = rbbs_top->w[0][1]+v*( val-rbbs_top->w[0][1] ); 
      rbbs_bottom->w[0][3] = w[0][3];
      rbbs_bottom->w[0][2] = w[0][2]+v*( w[0][3]-w[0][2] );
      rbbs_bottom->w[0][1] = val+v*( rbbs_bottom->w[0][2]-val );
      rbbs_top->w[0][3] = rbbs_bottom->w[0][0] = rbbs_top->w[0][2]+v*( rbbs_bottom->w[0][1]-rbbs_top->w[0][2] );

      rbbs_top->P[1][0] = PP[1][0];
      rbbs_top->P[1][1] = PP[1][0]+v*( PP[1][1]-PP[1][0] );
      W = PP[1][1]+v*( PP[1][2]-PP[1][1] );
      rbbs_top->P[1][2] = rbbs_top->P[1][1]+v*( W-rbbs_top->P[1][1] ); 
      rbbs_bottom->P[1][3] = PP[1][3];
      rbbs_bottom->P[1][2] = PP[1][2]+v*( PP[1][3]-PP[1][2] );
      rbbs_bottom->P[1][1] = W+v*( rbbs_bottom->P[1][2]-W );
      rbbs_top->P[1][3] = rbbs_bottom->P[1][0] = rbbs_top->P[1][2]+v*( rbbs_bottom->P[1][1]-rbbs_top->P[1][2] );
      rbbs_top->w[1][0] = w[1][0];
      rbbs_top->w[1][1] = w[1][0]+v*( w[1][1]-w[1][0] );
      val = w[1][1]+v*( w[1][2]-w[1][1] );
      rbbs_top->w[1][2] = rbbs_top->w[1][1]+v*( val-rbbs_top->w[1][1] ); 
      rbbs_bottom->w[1][3] = w[1][3];
      rbbs_bottom->w[1][2] = w[1][2]+v*( w[1][3]-w[1][2] );
      rbbs_bottom->w[1][1] = val+v*( rbbs_bottom->w[1][2]-val );
      rbbs_top->w[1][3] = rbbs_bottom->w[1][0] = rbbs_top->w[1][2]+v*( rbbs_bottom->w[1][1]-rbbs_top->w[1][2] );

      rbbs_top->P[2][0] = PP[2][0];
      rbbs_top->P[2][1] = PP[2][0]+v*( PP[2][1]-PP[2][0] );
      W = PP[2][1]+v*( PP[2][2]-PP[2][1] );
      rbbs_top->P[2][2] = rbbs_top->P[2][1]+v*( W-rbbs_top->P[2][1] ); 
      rbbs_bottom->P[2][3] = PP[2][3];
      rbbs_bottom->P[2][2] = PP[2][2]+v*( PP[2][3]-PP[2][2] );
      rbbs_bottom->P[2][1] = W+v*( rbbs_bottom->P[2][2]-W );
      rbbs_top->P[2][3] = rbbs_bottom->P[2][0] = rbbs_top->P[2][2]+v*( rbbs_bottom->P[2][1]-rbbs_top->P[2][2] );
      rbbs_top->w[2][0] = w[2][0];
      rbbs_top->w[2][1] = w[2][0]+v*( w[2][1]-w[2][0] );
      val = w[2][1]+v*( w[2][2]-w[2][1] );
      rbbs_top->w[2][2] = rbbs_top->w[2][1]+v*( val-rbbs_top->w[2][1] ); 
      rbbs_bottom->w[2][3] = w[2][3];
      rbbs_bottom->w[2][2] = w[2][2]+v*( w[2][3]-w[2][2] );
      rbbs_bottom->w[2][1] = val+v*( rbbs_bottom->w[2][2]-val );
      rbbs_top->w[2][3] = rbbs_bottom->w[2][0] = rbbs_top->w[2][2]+v*( rbbs_bottom->w[2][1]-rbbs_top->w[2][2] );

      rbbs_top->P[3][0] = PP[3][0];
      rbbs_top->P[3][1] = PP[3][0]+v*( PP[3][1]-PP[3][0] );
      W = PP[3][1]+v*( PP[3][2]-PP[3][1] );
      rbbs_top->P[3][2] = rbbs_top->P[3][1]+v*( W-rbbs_top->P[3][1] ); 
      rbbs_bottom->P[3][3] = PP[3][3];
      rbbs_bottom->P[3][2] = PP[3][2]+v*( PP[3][3]-PP[3][2] );
      rbbs_bottom->P[3][1] = W+v*( rbbs_bottom->P[3][2]-W );
      rbbs_top->P[3][3] = rbbs_bottom->P[3][0] = rbbs_top->P[3][2]+v*( rbbs_bottom->P[3][1]-rbbs_top->P[3][2] );
      rbbs_top->w[3][0] = w[3][0];
      rbbs_top->w[3][1] = w[3][0]+v*( w[3][1]-w[3][0] );
      val = w[3][1]+v*( w[3][2]-w[3][1] );
      rbbs_top->w[3][2] = rbbs_top->w[3][1]+v*( val-rbbs_top->w[3][1] ); 
      rbbs_bottom->w[3][3] = w[3][3];
      rbbs_bottom->w[3][2] = w[3][2]+v*( w[3][3]-w[3][2] );
      rbbs_bottom->w[3][1] = val+v*( rbbs_bottom->w[3][2]-val );
      rbbs_top->w[3][3] = rbbs_bottom->w[3][0] = rbbs_top->w[3][2]+v*( rbbs_bottom->w[3][1]-rbbs_top->w[3][2] );

      rbbs_top->P[0][0]/=rbbs_top->w[0][0];  rbbs_top->P[1][0]/=rbbs_top->w[1][0];  rbbs_top->P[2][0]/=rbbs_top->w[2][0];  rbbs_top->P[3][0]/=rbbs_top->w[3][0];
      rbbs_top->P[0][1]/=rbbs_top->w[0][1];  rbbs_top->P[1][1]/=rbbs_top->w[1][1];  rbbs_top->P[2][1]/=rbbs_top->w[2][2];  rbbs_top->P[3][1]/=rbbs_top->w[3][1];
      rbbs_top->P[0][2]/=rbbs_top->w[0][2];  rbbs_top->P[1][2]/=rbbs_top->w[1][2];  rbbs_top->P[2][2]/=rbbs_top->w[2][2];  rbbs_top->P[3][2]/=rbbs_top->w[3][2];
      rbbs_top->P[0][3]/=rbbs_top->w[0][3];  rbbs_top->P[1][3]/=rbbs_top->w[1][3];  rbbs_top->P[2][3]/=rbbs_top->w[2][3];  rbbs_top->P[3][3]/=rbbs_top->w[3][3];
      rbbs_bottom->P[0][0]/=rbbs_bottom->w[0][0];  rbbs_bottom->P[1][0]/=rbbs_bottom->w[1][0];  rbbs_bottom->P[2][0]/=rbbs_bottom->w[2][0];  rbbs_bottom->P[3][0]/=rbbs_bottom->w[3][0];
      rbbs_bottom->P[0][1]/=rbbs_bottom->w[0][1];  rbbs_bottom->P[1][1]/=rbbs_bottom->w[1][1];  rbbs_bottom->P[2][1]/=rbbs_bottom->w[2][2];  rbbs_bottom->P[3][1]/=rbbs_bottom->w[3][1];
      rbbs_bottom->P[0][2]/=rbbs_bottom->w[0][2];  rbbs_bottom->P[1][2]/=rbbs_bottom->w[1][2];  rbbs_bottom->P[2][2]/=rbbs_bottom->w[2][2];  rbbs_bottom->P[3][2]/=rbbs_bottom->w[3][2];
      rbbs_bottom->P[0][3]/=rbbs_bottom->w[0][3];  rbbs_bottom->P[1][3]/=rbbs_bottom->w[1][3];  rbbs_bottom->P[2][3]/=rbbs_bottom->w[2][3];  rbbs_bottom->P[3][3]/=rbbs_bottom->w[3][3];
  }








  // RATIONALBICUBICBEZIERSURFACEARRAY
  class rationalbicubicbeziersurfacearraY: public arraY_<rationalbicubicbeziersurfacE> {};
        

  // LPRATIONALBICUBICBEZIERSURFACE
  typedef rationalbicubicbeziersurfacE* lprationalbicubicbeziersurfacE;


  // LPRATIONALBICUBICBEZIERSURFACEARRAY
  class lprationalbicubicbeziersurfacearraY: public arraY__<lprationalbicubicbeziersurfacE> {};
















  // BEZIERSURFACE
  class beziersurfacE : public objecT {
      private:
          void createbsptreE( beziersurfacE *bs, bsptreenodE *bsptn_, DWORD depth );
		  void releasebsptreE( bsptreenodE *bsptn_ );


      public:
          DWORD n, m;
  		  pointarraY P;
          bsptreenodE bsptroot;
          lpbsptreenodearraY lpbsptna;


          beziersurfacE( void ) { reseT(); };
          ~beziersurfacE( void ) { deletealL(); };

          void reseT( void );
		  void deletealL( void );
		  void copY( beziersurfacE *bs );

		  poinT calculatecenterofmasS( void );
		  aabboX findaabboX( void );
		  oobboX findoobboX( void ) { return oobboX(); };
		  bspherE findbspherE( void );
		  void findconvexhulL( void );
		  void findprojectedconvexhulL( camerA *C );
		  void resetxforM( void );

          void createbsptreE( DWORD maxdepth = 6 );
          void releasebsptreE( void );

		  poinT decasteljaU( valuE u, valuE v, poinT *A = NULL, vectoR *dA = NULL );
          void splitU( valuE u, beziersurfacE *bs_left, beziersurfacE *bs_right ); 
          void splitV( valuE v, beziersurfacE *bs_bottom, beziersurfacE *bs_top ); 
  };                   


  BOOL beziersurfaceraY_( beziersurfacE *bs, const raY& r, valuE *t, verteX *V );
  BOOL beziersurfaceraY( beziersurfacE *bs, const raY& r, valuE *t, verteX *V );






  void beziersurfacE::reseT( void ) {
      n = m = 0;
      P.reseT();
	  aabb = aabboX();
	  oobb = oobboX();
	  bsph = bspherE();
	  mata.reseT();
	  mtrla.reseT();
      bsptroot.reseT();
      lpbsptna.reseT();
      convexhull.reseT();
	  projected_ch.reseT();
  }

  


  void beziersurfacE::deletealL( void ) {
      P.deletealL();
	  mata.deletealL();
	  mtrla.deletealL();
      releasebsptreE();
      lpbsptna.deletealL();
      convexhull.deletealL();
      projected_ch.deletealL();

	  reseT();
  }




  void beziersurfacE::copY( beziersurfacE *bs ) {
      bs->deletealL();

      bs->n = n;
      bs->m = m;
      P.copY( &bs->P );
      bs->aabb = aabb; 
      bs->oobb = oobb; 
      bs->bsph = bsph; 
      mata.copY( &bs->mata );
      mtrla.copY( &bs->mtrla );
      convexhull.copY( &bs->convexhull );
      projected_ch.copY( &bs->projected_ch );
  }




  void beziersurfacE::createbsptreE( beziersurfacE *bs, bsptreenodE *bsptn_, DWORD depth ) {
      if( depth > 0 ) {
		  beziersurfacE bs_left, bs_right;


	      bsptn_->left_node = new bsptreenodE;
          bsptn_->right_node = new bsptreenodE;

		  bsptn_->left_node->reseT();
		  bsptn_->right_node->reseT();

		  bsptn_->left_node->pl = bsptn_->right_node->pl = bsptn_->pl;

		  if( ( depth % 2 ) == 0 ) {  // subdivide u
			  bs->splitU( 0.5, &bs_left, &bs_right );
			  bsptn_->left_node->pl.n.z = bsptn_->right_node->pl.n.x = ( bsptn_->pl.n.x+bsptn_->pl.n.z )*0.5;
		  } else {  // subdivide v
			  bs->splitV( 0.5, &bs_left, &bs_right );
			  bsptn_->left_node->pl.d = bsptn_->right_node->pl.n.y = ( bsptn_->pl.n.y+bsptn_->pl.d )*0.5;
		  }

		  bsptn_->left_node->aabb = bs_left.findaabboX();
		  bsptn_->right_node->aabb = bs_right.findaabboX();

		  depth--;
	      createbsptreE( &bs_left, bsptn_->left_node, depth );
          createbsptreE( &bs_right, bsptn_->right_node, depth );
	  } 
  }




  void beziersurfacE::releasebsptreE( bsptreenodE *bsptn_ ) {
	  if( bsptn_->left_node ) {
		  releasebsptreE( bsptn_->left_node );  
		  delete bsptn_->left_node;  
	  } 
	  if( bsptn_->right_node ) {
		  releasebsptreE( bsptn_->right_node );  
		  delete bsptn_->right_node;  
	  } 
	  bsptn_->deletealL();
  }




  void beziersurfacE::createbsptreE( DWORD maxdepth ) {
  	  releasebsptreE();

	  bsptroot.aabb = aabb;
	  bsptroot.pl.n.x = bsptroot.pl.n.y = 0.0;  bsptroot.pl.n.z = bsptroot.pl.d = 1.0;  // v plane su postupne u0, v0, u1, v1
      createbsptreE( this, &bsptroot, maxdepth );
  }




  void beziersurfacE::releasebsptreE( void ) {
      releasebsptreE( &bsptroot );  

      bsptroot.reseT();
  }




  poinT beziersurfacE::decasteljaU( valuE u, valuE v, poinT *A, vectoR *dA ) {
	  register long i, j, k;
      valuE val;
	  vectoR du, dv;
	  poinT pt;
	  pointarraY pta, pta2;


	  pta.inserT( -1, poinT(), max( n, m )*max( n, m ) );
      pta2.inserT( -1, poinT(), max( n, m ) );


      // DeCasteljau u
      val = 1.0-u;

      for( k = 0;  k < m;  k++ ) {
    	  for( i = 0;  i < n;  i++ ) pta.elem[i+0*n] = P.elem[i+k*n];

	      for( j = 1;  j < n;  j++ )
		      for( i = j;  i < n;  i++ ) 
			      pta.elem[i+j*n] = val*pta.elem[i-1+( j-1 )*n]+u*pta.elem[i+( j-1 )*n];

          pta2.elem[k] = pta.elem[n-1+( n-1 )*n];
      }

      // DeCasteljau v
      val = 1.0-v;

   	  for( i = 0;  i < m;  i++ ) pta.elem[i+0*m] = pta2.elem[i];

      for( j = 1;  j < m;  j++ )
	      for( i = j;  i < m;  i++ ) 
		      pta.elem[i+j*m] = val*pta.elem[i-1+( j-1 )*m]+v*pta.elem[i+( j-1 )*m];

	  pt = pta.elem[m-1+( m-1 )*m];
	  dv = ( m-1 )*( pta.elem[m-1+( m-2 )*m]-pta.elem[m-1+( m-1 )*m] );


	  if( dA ) {
	      // DeCasteljau v
		  val = 1.0-v;

	      for( k = 0;  k < n;  k++ ) {
    		  for( i = 0;  i < m;  i++ ) pta.elem[i+0*m] = P.elem[k+i*n];

		      for( j = 1;  j < m;  j++ )
			      for( i = j;  i < m;  i++ ) 
				      pta.elem[i+j*m] = val*pta.elem[i-1+( j-1 )*m]+v*pta.elem[i+( j-1 )*m];

		      pta2.elem[k] = pta.elem[m-1+( m-1 )*m];
	      }

		  // DeCasteljau u
	      val = 1.0-u;

   		  for( i = 0;  i < n;  i++ ) pta.elem[i+0*n] = pta2.elem[i];

	      for( j = 1;  j < n;  j++ )
		      for( i = j;  i < n;  i++ ) 
			      pta.elem[i+j*n] = val*pta.elem[i-1+( j-1 )*n]+u*pta.elem[i+( j-1 )*n];

		  du = ( n-1 )*( pta.elem[n-1+( n-2 )*n]-pta.elem[n-1+( n-1 )*n] );


		  *dA = normalizE( crosS( du, dv ) );
	  }
      if( A ) return *A = pt; else return pt;
  }




  void beziersurfacE::splitU( valuE u, beziersurfacE *bs_left, beziersurfacE *bs_right ) {
	  register long i, j, k;
      valuE val;
	  pointarraY pta;


	  if( bs_left != NULL ) {
	      bs_left->deletealL();
	      bs_left->n = n;
		  bs_left->m = m;
		  bs_left->P.inserT( -1, poinT(), n*m );
	  } 
	  if( bs_right != NULL ) {
		  bs_right->deletealL();
	      bs_right->n = n;
		  bs_right->m = m;
	      bs_right->P.inserT( -1, poinT(), n*m );
	  } 


      pta.inserT( -1, poinT(), n*n );


      // DeCasteljau u
      val = 1.0-u;

      for( k = 0;  k < m;  k++ ) {
    	  for( i = 0;  i < n;  i++ ) pta.elem[i+0*n] = P.elem[i+k*n];

	      for( j = 1;  j < n;  j++ )
		      for( i = j;  i < n;  i++ ) 
			      pta.elem[i+j*n] = val*pta.elem[i-1+( j-1 )*n]+u*pta.elem[i+( j-1 )*n];

		  if( bs_left != NULL )
	          for( i = 0;  i < n;  i++ ) bs_left->P.elem[i+k*n] = pta.elem[i+i*n];
		  if( bs_right != NULL )
	          for( i = 0;  i < n;  i++ ) bs_right->P.elem[i+k*n] = pta.elem[n-1+( n-1-i )*n];
      }
  }




  void beziersurfacE::splitV( valuE v, beziersurfacE *bs_bottom, beziersurfacE *bs_top ) {
	  register long i, j, k;
      valuE val;
	  pointarraY pta;


	  if( bs_bottom != NULL ) {
	      bs_bottom->deletealL();
	      bs_bottom->n = n;
		  bs_bottom->m = m;
	      bs_bottom->P.inserT( -1, poinT(), n*m );
	  }
	  if( bs_top != NULL ) {
	      bs_top->deletealL();
	      bs_top->n = n;
		  bs_top->m = m;
	      bs_top->P.inserT( -1, poinT(), n*m );
	  }


      pta.inserT( -1, poinT(), m*m );


      // DeCasteljau v
      val = 1.0-v;

      for( k = 0;  k < n;  k++ ) {
    	  for( i = 0;  i < m;  i++ ) pta.elem[i+0*m] = P.elem[k+i*n];

	      for( j = 1;  j < m;  j++ )
		      for( i = j;  i < m;  i++ ) 
			      pta.elem[i+j*m] = val*pta.elem[i-1+( j-1 )*m]+v*pta.elem[i+( j-1 )*m];

		  if( bs_bottom != NULL )
	          for( i = 0;  i < m;  i++ ) bs_bottom->P.elem[k+i*n] = pta.elem[i+i*m];
		  if( bs_top != NULL )
	          for( i = 0;  i < m;  i++ ) bs_top->P.elem[k+i*n] = pta.elem[m-1+( m-1-i )*m];
      }
  }




  poinT beziersurfacE::calculatecenterofmasS( void ) {
      com = poinT( 0.0, 0.0, 0.0 );

      for( register DWORD i = 0;  i < n*m;  i++ ) com += P.elem[i];
	  if (n*m > 0) com /= (valuE) (n*m);

      return com;
  }




  aabboX beziersurfacE::findaabboX( void ) {
      aabb.min = poinT( INFINITY, INFINITY, INFINITY );
      aabb.max = poinT( -INFINITY, -INFINITY, -INFINITY );

      for( register DWORD i = 0;  i < n*m;  i++ ) {
          if( P.elem[i].x < aabb.min.x ) aabb.min.x = P.elem[i].x;
          if( P.elem[i].x > aabb.max.x ) aabb.max.x = P.elem[i].x; 	  
          if( P.elem[i].y < aabb.min.y ) aabb.min.y = P.elem[i].y; 
   	      if( P.elem[i].y > aabb.max.y ) aabb.max.y = P.elem[i].y; 	  
          if( P.elem[i].z < aabb.min.z ) aabb.min.z = P.elem[i].z; 
          if( P.elem[i].z > aabb.max.z ) aabb.max.z = P.elem[i].z; 	  
      }

      return aabb;
  }




  bspherE beziersurfacE::findbspherE( void ) {
      register DWORD i;
      valuE a;
      vectoR v;
      poinT pt;


      bsph.C = poinT( 0.0, 0.0, 0.0 );
      for( i = 0;  i < n*m;  i++ ) bsph.C += P.elem[i];
      bsph.C /= n*m;

      bsph.r = -INFINITY;
      for( i = 0;  i < n*m;  i++ ) {
          v = P.elem[i]-bsph.C;
          a = doT( v, v );
          if( a > bsph.r ) {
              bsph.r = a;
              pt = P.elem[i];
          }
      }
      bsph.r = lengtH( pt-bsph.C );

      return bsph;
  }




  void beziersurfacE::findconvexhulL( void ) {
      pointarraY pta;

      pta.inserT( -1, poinT(), n*m );
      for( register DWORD i = 0;  i < n*m;  i++ ) pta.elem[i] = P.elem[i];

      quickhull3D( &pta, &convexhull );
  }




  void beziersurfacE::findprojectedconvexhulL( camerA *C ) {
      pointarraY pta;

      pta.inserT( -1, poinT(), n*m );
      for( register DWORD i = 0;  i < n*m;  i++ ) pta.elem[i] = projecT( C, P.elem[i] );

      quickhull2D( &pta, &projected_ch );
  }




  void beziersurfacE::resetxforM( void ) {
      if( mata.num > 0 ) {
    	  for( register DWORD i = 0;  i < P.num;  i++ ) 
	          P.elem[i] = multiplY( P.elem[i], mata.elem[0] );

    	  mata.elem[0] = identitY();
      }
  }








  // BEZIERSURFACEARRAY
  class beziersurfacearraY: public arraY_<beziersurfacE> {};


  // LPBEZIERSURFACE
  typedef beziersurfacE* lpbeziersurfacE;


  // LPBEZIERSURFACEARRAY
  class lpbeziersurfacearraY: public arraY__<lpbeziersurfacE> {};








  BOOL beziersurfaceraY_( beziersurfacE *bs, const raY& r, valuE *t, verteX *V ) {
	  BOOL b_, xpos, xneg, ypos, yneg, zpos;
	  register long i, j;
	  long l;
	  valuE val, a, b, x, u0, u1, v0, v1, u0_, u1_, v0_, v1_, thres = 0.01;
	  vectoR v;
	  poinT pt;
	  planE plx, ply, plz;
	  valuearraY vala, vala_;
	  vectorarraY va;
	  pointarraY pta, d, d_, ch;
	  beziersurfacE bs_, bs_left, bs_right, bs_top, bs_bottom;
	  lpbeziersurfacearraY lpbsa;


	  if( abs( r.q.x ) <= abs( r.q.y ) ) {
		  if( abs( r.q.x ) <= abs( r.q.z ) ) { // min abs( r.q.x )
			  v = crosS( E0, r.q );
		  } else { // min abs( r.q.z )
			  v = crosS( E2, r.q );
		  }
	  } else {
		  if( abs( r.q.y ) <= abs( r.q.z ) ) { // min abs( r.q.y )
			  v = crosS( E1, r.q );
		  } else { // min abs( r.q.z )
			  v = crosS( E2, r.q );
		  }
	  }
	  plx = planE( normalizE( v ), r.A );
	  plz = planE( normalizE( r.q ), r.A );
	  ply = planE( crosS( plx.n, plz.n ), r.A ); // crosS( v, r.q )


	  d.inserT( -1, poinT(), bs->n*bs->m );
	  d_.inserT( -1, poinT(), bs->n*bs->m );


	  u0_ = v0_ = 0.0;
	  u1_ = v1_ = 1.0; 
	  bs->copY( &bs_ );
	  b_ = FALSE;
	  do {
		  // pop
		  if( b_ ) { // ak plati b, tak popujeme
			  v1_ = vala_.elem[vala_.num-1];
			  vala_.deletE( -1 );
			  v0_ = vala_.elem[vala_.num-1];
			  vala_.deletE( -1 );
			  u1_ = vala_.elem[vala_.num-1];
			  vala_.deletE( -1 );
			  u0_ = vala_.elem[vala_.num-1];
			  vala_.deletE( -1 );

			  lpbsa.elem[lpbsa.num-1]->copY( &bs_ );
			  lpbsa.releasE( -1 );
		  } else b_ = TRUE;


		  // premietneme plochu
		  xpos = xneg = ypos = yneg = zpos = FALSE;
		  val = -INFINITY;
		  for( i = 0;  i < bs_.n;  i++ ) 
			  for( j = 0;  j < bs_.m;  j++ ) {
				  l = i+j*bs_.n;
				  d.elem[l].x = planepoinT( plx, bs_.P.elem[l] );
				  d.elem[l].y = planepoinT( ply, bs_.P.elem[l] );
				  d.elem[l].z = planepoinT( plz, bs_.P.elem[l] );

				  if( d.elem[l].x > -EPSILON ) xpos = TRUE;
				  if( d.elem[l].x < EPSILON ) xneg = TRUE;
				  if( d.elem[l].y > -EPSILON ) ypos = TRUE;
				  if( d.elem[l].y < EPSILON ) yneg = TRUE;
				  if( d.elem[l].z >= 0.0 ) zpos = TRUE;

				  a = sqR( d.elem[l].x )+sqR( d.elem[l].y );
				  if( a > val ) val = a;
			  }

		  if( zpos ) {
			  if( val < thres || ( u1_-u0_ < EPSILON && v1_-v0_ < EPSILON ) ) { // intersection, vsetky premietnute body plochy lezia blizko k bodu 0,0 takze mame priesecnik, alebo je jednoducho interval uz prilis maly
				  if( doT( r.q, bs_.P.elem[0]-r.A ) >= 0.0 ) {
					  pta.inserT( -1, poinT() ); 
					  va.inserT( -1, vectoR() ); 
					  vala.inserT( -1, u0_, 2 );
					  vala.elem[vala.num-1] = v0_;
					  pta.elem[pta.num-1] = bs_.P.elem[0];
				  }
			  } else 
			  if( xpos && xneg && ypos && yneg ) { // moze existovat priesecnik
				  if( u1_-u0_ >= v1_-v0_ ) { // delime podla u
					  l = ( bs_.m-1 )*bs_.n;
					  a = d.elem[l].y-d.elem[0].y + d.elem[bs_.n-1+l].y-d.elem[bs_.n-1].y;  
					  b = -( d.elem[l].x-d.elem[0].x + d.elem[bs_.n-1+l].x-d.elem[bs_.n-1].x );
					  val = a*a+b*b;
	
					  if( val < EPSILON ) { // degenerovana plocha, splitneme na polky
						  // push
						  if( lpbsa.num < 1024 ) {
							  vala_.inserT( -1, 0.0, 4 );
							  vala_.elem[vala_.num-4] = ( u0_+u1_ )*0.5;
							  vala_.elem[vala_.num-3] = u1_;
							  vala_.elem[vala_.num-2] = v0_;
							  vala_.elem[vala_.num-1] = v1_;

							  u1_ = vala_.elem[vala_.num-4];

							  lpbsa.inserT( -1, new beziersurfacE() );
							  bs_.splitU( 0.5, &bs_left, lpbsa.elem[lpbsa.num-1] );	
							  bs_left.copY( &bs_ );

							  b_ = FALSE;
						  }
					  } else {
						  val = 1.0/sqrT( val );
						  a *= val;  b *= val;

						  val = diV( 1.0, bs_.n-1, 0.0 );
						  ypos = yneg = FALSE;
						  for( i = 0;  i < bs_.n;  i++ ) 
							  for( j = 0;  j < bs_.m;  j++ ) {
								  l = i+j*bs_.n;
								  d_.elem[l].x = i*val;
								  d_.elem[l].y = a*d.elem[l].x+b*d.elem[l].y;
	
								  if( d_.elem[l].y >= 0.0 ) ypos = TRUE;
								  if( d_.elem[l].y <= 0.0 ) yneg = TRUE;
							  }

						  if( ypos && yneg ) {
							  // najdeme konvexnu obalku
							  quickhull2D( &d_, &ch );
		
							  // priesecniky konvexnej obalky s x-osou
							  u0 = INFINITY;  u1 = -INFINITY;
							  for( i = 0;  i < ch.num;  i+=2 ) 
								  if( ch.elem[i].y*ch.elem[i+1].y <= 0.0 ) {
									  if( ch.elem[i].y == 0.0 && ch.elem[i+1].y == 0.0 ) {
										  x = ch.elem[i].x;
										  if( x < u0 ) u0 = x;
										  if( x > u1 ) u1 = x;
										  x = ch.elem[i+1].x;
										  if( x < u0 ) u0 = x;
										  if( x > u1 ) u1 = x;
									  } else {
									      val = diV( -ch.elem[i].y, ch.elem[i+1].y-ch.elem[i].y, 0.0 );    		      	
										  x = ch.elem[i].x+val*( ch.elem[i+1].x-ch.elem[i].x );
										  if( x < u0 ) u0 = x;
										  if( x > u1 ) u1 = x;
									  }
								  }
	
                              u0 = clamP( u0-EPSILON, 0.0, 1.0 );
                              u1 = clamP( u1+EPSILON, 0.0, 1.0 );

							  // vyrezeme pas z bezierovej plochy urcenu u0 a u1	
							  if( u0 < 0.5 ) {
								  bs_.splitU( u0, NULL, &bs_right );
								  bs_right.splitU( diV( u1-u0, 1.0-u0, 1.0 ), &bs_, NULL );
							  } else {
								  bs_.splitU( u1, &bs_left, NULL );
								  bs_left.splitU( u0/u1, NULL, &bs_ );
							  }

							  if( u1-u0 > 0.8 ) { // pravdepodobne existuje viecero priesecnikov, splitneme na polky
								  // push
								  if( lpbsa.num < 1024 ) {
									  vala_.inserT( -1, 0.0, 4 );
									  vala_.elem[vala_.num-2] = v0_;
									  vala_.elem[vala_.num-1] = v1_;
									  val = u1_-u0_;
									  vala_.elem[vala_.num-4] = u0_+( u0+u1 )*0.5*val;
									  vala_.elem[vala_.num-3] = u0_+u1*val;

									  u0_ = u0_+u0*val;
									  u1_ = vala_.elem[vala_.num-4];
	
									  lpbsa.inserT( -1, new beziersurfacE() );
									  bs_.splitU( 0.5, &bs_left, lpbsa.elem[lpbsa.num-1] );	
									  bs_left.copY( &bs_ );

									  b_ = FALSE;
								  }
							  } else {
								  // push
								  val = u1_-u0_;
								  u1_ = u0_+u1*val;
								  u0_ = u0_+u0*val;

								  b_ = FALSE;
							  }
						  }
				      }
				  } else { // delime podla v
					  l = ( bs_.m-1 )*bs_.n;
					  a = d.elem[bs_.n-1].y-d.elem[0].y + d.elem[bs_.n-1+l].y-d.elem[l].y;  
					  b = -( d.elem[bs_.n-1].x-d.elem[0].x + d.elem[bs_.n-1+l].x-d.elem[l].x );
					  val = a*a+b*b;
		
					  if( val < EPSILON ) { // degenerovana plocha, splitneme na polky
						  // push
						  if( lpbsa.num < 1024 ) {
							  vala_.inserT( -1, 0.0, 4 );
							  vala_.elem[vala_.num-4] = u0_;
							  vala_.elem[vala_.num-3] = u1_;
							  vala_.elem[vala_.num-2] = ( v0_+v1_ )*0.5;
							  vala_.elem[vala_.num-1] = v1_;

							  v1_ = vala_.elem[vala_.num-2];

							  lpbsa.inserT( -1, new beziersurfacE() );
							  bs_.splitV( 0.5, &bs_bottom, lpbsa.elem[lpbsa.num-1] );	
							  bs_bottom.copY( &bs_ );
	
							  b_ = FALSE;
						  }
					  } else {
						  val = 1.0/sqrT( val );
						  a *= val;  b *= val;

						  val = diV( 1.0, bs_.m-1, 0.0 );
						  ypos = yneg = FALSE;
						  for( i = 0;  i < bs_.n;  i++ ) 
							  for( j = 0;  j < bs_.m;  j++ ) {
								  l = i+j*bs_.n;
								  d_.elem[l].x = j*val;
								  d_.elem[l].y = a*d.elem[l].x+b*d.elem[l].y;
	
								  if( d_.elem[l].y >= 0.0 ) ypos = TRUE;
								  if( d_.elem[l].y <= 0.0 ) yneg = TRUE;
							  }

						  if( ypos && yneg ) {
							  // najdeme konvexnu obalku
							  quickhull2D( &d_, &ch );

							  // priesecniky s x-osou
							  v0 = INFINITY;  v1 = -INFINITY;
							  for( i = 0;  i < ch.num;  i+=2 ) 
								  if( ch.elem[i].y*ch.elem[i+1].y <= 0.0 ) {
									  if( ch.elem[i].y == 0.0 && ch.elem[i+1].y == 0.0 ) {
										  x = ch.elem[i].x;
										  if( x < v0 ) v0 = x;
										  if( x > v1 ) v1 = x;
										  x = ch.elem[i+1].x;
										  if( x < v0 ) v0 = x;
										  if( x > v1 ) v1 = x;
									  } else {
									      val = diV( -ch.elem[i].y, ch.elem[i+1].y-ch.elem[i].y, 0.0 );    		      	
										  x = ch.elem[i].x+val*( ch.elem[i+1].x-ch.elem[i].x );
										  if( x < v0 ) v0 = x;
										  if( x > v1 ) v1 = x;
									  }
								  }

                              v0 = clamP( v0-EPSILON, 0.0, 1.0 );
                              v1 = clamP( v1+EPSILON, 0.0, 1.0 );

							  // vyrezeme pas z bezierovej plochy urcenu v0 a v1	
							  if( v0 < 0.5 ) {
								  bs_.splitV( v0, NULL, &bs_top );
								  bs_top.splitV( diV( v1-v0, 1.0-v0, 1.0 ), &bs_, NULL );
							  } else {
								  bs_.splitV( v1, &bs_bottom, NULL );
								  bs_bottom.splitV( v0/v1, NULL, &bs_ );
							  }

							  if( v1-v0 > 0.8 ) { // pravdepodobne existuje viecero priesecnikov, splitneme na polky
								  // push
								  if( lpbsa.num < 1024 ) {
									  vala_.inserT( -1, 0.0, 4 );
									  vala_.elem[vala_.num-4] = u0_;
									  vala_.elem[vala_.num-3] = u1_;
									  val = v1_-v0_;
									  vala_.elem[vala_.num-2] = v0_+( v0+v1 )*0.5*val;
									  vala_.elem[vala_.num-1] = v0_+v1*val;

									  v0_ = v0_+v0*val;
									  v1_ = vala_.elem[vala_.num-2];
	
									  lpbsa.inserT( -1, new beziersurfacE() );
									  bs_.splitV( 0.5, &bs_bottom, lpbsa.elem[lpbsa.num-1] );	
									  bs_bottom.copY( &bs_ );
	
									  b_ = FALSE;
								  }
							  } else {
								  // push
								  val = v1_-v0_;
								  v1_ = v0_+v1*val;
								  v0_ = v0_+v0*val;
	
								  b_ = FALSE;
							  }
						  } 
					  }
				  }
			  }
		  }
	  } while( lpbsa.num > 0 || b_ == FALSE );


	  if( pta.num > 0 ) {
		  // najdeme najblizsi priesecnik
		  val = INFINITY;
		  for( i = 0;  i < pta.num;  i++ ) {
			  a = squarelengtH( pta.elem[i]-r.A );
			  if( a < val ) {	
				  val = a;
				  j = i;	
			  }
		  }

		  if( abs( r.q.x ) >= abs( r.q.y ) ) {
			  if( abs( r.q.x ) >= abs( r.q.z ) ) { // max abs( r.q.x )
				  *t = ( pta.elem[j].x-r.A.x )/r.q.x;
			  } else { // max abs( r.q.z )
				  *t = ( pta.elem[j].z-r.A.z )/r.q.z;
			  }
		  } else {
			  if( abs( r.q.y ) >= abs( r.q.z ) ) { // max abs( r.q.y )
				  *t = ( pta.elem[j].y-r.A.y )/r.q.y;
			  } else { // max abs( r.q.z )
				  *t = ( pta.elem[j].z-r.A.z )/r.q.z;
			  }
		  }

		  V->t.x = vala.elem[2*j]; 
		  V->t.y = vala.elem[2*j+1];
		  V->t.z = 0.0;
		  bs->decasteljaU( V->t.x, V->t.y, &V->v, &V->n );	

		  return TRUE;
	  }


	  return FALSE;
  }




  BOOL beziersurfaceraY( beziersurfacE *bs, const raY& r, valuE *t, verteX *V ) {
      if( bs ) {
	      bsptreenodE *bsptn;
	      valuE tnear, tfar, ti;
	      raY r_;
	      matriX invmat = inversE( bs->mata.elem[0] );
		  verteX Vi;
		  beziersurfacE bs_, bs_temp;

		
	      r_.A = multiplY( r.A, invmat );  
	      r_.q = multiplY( r.A+r.q, invmat )-r_.A;

	      *t = INFINITY;
	      bs->lpbsptna.num = 1;
	      bs->lpbsptna.inserT( -1, &bs->bsptroot );
	      do {
              bsptn = bs->lpbsptna.elem[bs->lpbsptna.num-1];
              bs->lpbsptna.deletE( -1 );
			
 	          if( aabboxraY( aabboX( bsptn->aabb.min-vectoR( 0.25, 0.25, 0.25 ), bsptn->aabb.max+vectoR( 0.25, 0.25, 0.25 ) ), r_, &tnear, &tfar ) && *t > tnear ) {
			      if( bsptn->left_node == NULL ) {  // leaf
					  // vyrezeme pas z bezierovej plochy podla u	
					  if( bsptn->pl.n.x < 0.5 ) {
						  bs->splitU( bsptn->pl.n.x, NULL, &bs_temp );
						  bs_temp.splitU( diV( bsptn->pl.n.z-bsptn->pl.n.x, 1.0-bsptn->pl.n.x, 1.0 ), &bs_, NULL );
					  } else {
						  bs->splitU( bsptn->pl.n.z, &bs_temp, NULL );
						  bs_temp.splitU( bsptn->pl.n.x/bsptn->pl.n.z, NULL, &bs_ );
					  }
				
					  // vyrezeme pas z bezierovej plochy podla v
					  if( bsptn->pl.n.y < 0.5 ) {
						  bs_.splitV( bsptn->pl.n.y, NULL, &bs_temp );
						  bs_temp.splitV( diV( bsptn->pl.d-bsptn->pl.n.y, 1.0-bsptn->pl.n.y, 1.0 ), &bs_, NULL );
					  } else {
						  bs_.splitV( bsptn->pl.d, &bs_temp, NULL );
						  bs_temp.splitV( bsptn->pl.n.y/bsptn->pl.d, NULL, &bs_ );
					  }

					  if( beziersurfaceraY_( &bs_, r_, &ti, &Vi ) ) {
						  if( ti < *t ) {
					          *t = ti;
							  Vi.copY( V );
						  }
					  }
    			  } else {
					  bs->lpbsptna.inserT( -1, bsptn->left_node, 2 );
					  bs->lpbsptna.elem[bs->lpbsptna.num-1] = bsptn->right_node;
				  }
			  }
		  } while( bs->lpbsptna.num > 1 );

		  if( *t != INFINITY ) {
			  V->v = multiplY( V->v, bs->mata.elem[0] );
			  invmat = bs->mata.elem[0];
			  invmat._[3][0] = invmat._[3][1] = invmat._[3][2] = 0.0;
			  invmat = transposE( inversE( invmat ) );
			  V->n = normalizE( multiplY( V->n, invmat ) );		 

			  return TRUE;
		  }
	  }

	  return FALSE;
  }
