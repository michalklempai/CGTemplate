 
  // RAY
  class raY {
      public:
          poinT A;
          vectoR q; 


          raY( void );
          raY( const poinT& A, const vectoR& q );
          raY( const raY& r );

          raY operator+( void ) const;
          raY operator-( void ) const;
          
          BOOL operator==( const raY& r ) const;
          BOOL operator!=( const raY& r ) const;
  };
    







  inline raY::raY( void ) {
      A = poinT();
      q = vectoR();
  }




  inline raY::raY( const poinT& A, const vectoR& q ) {
      this->A = A;  this->q = q;
  }




  inline raY::raY( const raY& r ) {
      A = r.A;  q = r.q;
  }




  inline raY raY::operator+( void ) const {
      return *this;
  }
  
  
  
  
  inline raY raY::operator-( void ) const {
      return raY( A, -q );
  }



    
  inline BOOL raY::operator==( const raY& r ) const {
      return A == r.A && q == r.q;
  }




  inline BOOL raY::operator!=( const raY& r ) const {
      return A != r.A || q != r.q;
  }








  // RAYARRAY
  class rayarraY: public arraY<raY> {};
 