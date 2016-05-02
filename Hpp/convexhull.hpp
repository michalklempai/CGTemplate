
  void quickhull2D_( pointarraY *pta, pointarraY *convexhull, DWORD chi_A, DWORD chi_B );
  long quickhull2D( pointarraY *pta, pointarraY *convexhull );
  void findhorizont3D( const poinT& eye, pointarraY *convexhull, arraY_<pointarraY> *ptaa, pointarraY *horizontedg, pointarraY *pta );
  valuE tetrahedronvolumE( const poinT& pt0, const poinT& pt1, const poinT& pt2, const poinT& pt3 );
  long quickhull3D( pointarraY *pta, pointarraY *convexhull );






  void quickhull2D_( pointarraY *pta, pointarraY *convexhull, DWORD chi_A, DWORD chi_B ) {
	  register long i;
	  DWORD j;
	  valuE val, val2, a1, b1, c1, a2, b2, c2;
	  pointarraY pta_1, pta_2;


	  // najdeme trojuholnik s max. obsahom
	  val = -INFINITY;
	  for( i = 0;  i < pta->num;  i++ ) {
		  val2 = triangleareA( convexhull->elem[chi_A], convexhull->elem[chi_B], pta->elem[i] ); 
		  if( val2 > val ) {
			  val = val2;
			  j = i;
		  }
	  }

	
	  if( val > 0.0 ) { // ak mame max. trojuholnik s obsahom 0.0, tak vlastne vsetky ostatne body musisa lezat v nom  
		  a1 = pta->elem[j].y-convexhull->elem[chi_A].y;
		  b1 = convexhull->elem[chi_A].x-pta->elem[j].x;
		  val = diV( 1.0, sqrT( a1*a1+b1*b1 ), 0.0 );
		  a1*=val;  b1*=val;
		  c1 = -( a1*pta->elem[j].x + b1*pta->elem[j].y );

		  a2 = convexhull->elem[chi_B].y-pta->elem[j].y;
		  b2 = pta->elem[j].x-convexhull->elem[chi_B].x;
		  val = diV( 1.0, sqrT( a2*a2+b2*b2 ), 0.0 );
		  a2*=val;  b2*=val;
		  c2 = -( a2*pta->elem[j].x + b2*pta->elem[j].y );

		  for( i = 0;  i < pta->num;  i++ ) 
			  if( i != j ) { // bod, ktory tvori trojuholnik s max. obsahom uz urcite nepatri do vonkajsich oblasti
				  if( a1*pta->elem[i].x + b1*pta->elem[i].y + c1 < -EPSILON ) pta_1.inserT( -1, pta->elem[i] ); 
				  if( a2*pta->elem[i].x + b2*pta->elem[i].y + c2 < -EPSILON ) pta_2.inserT( -1, pta->elem[i] ); 
			  }

		  // pridame usecky najdeneho trojuholnika a zmazeme usecku chi_A, chi_B pretoze je nahradena najdenymi zvysnymi dvoma useckami max. trojuholnika
		  convexhull->inserT( -1, pta->elem[j] );
		  convexhull->inserT( -1, convexhull->elem[chi_B] );
		  convexhull->elem[chi_B] = pta->elem[j];

		  j = convexhull->num;
		  if( pta_1.num > 0 ) quickhull2D_( &pta_1, convexhull, chi_A, chi_B );
		  if( pta_2.num > 0 ) quickhull2D_( &pta_2, convexhull, j-2, j-1 );
	  }
  }




  long quickhull2D( pointarraY *pta, pointarraY *convexhull ) {
	  if( pta->num > 0 ) {
		  register long i, j;
		  DWORD min_x, max_x, min_y, max_y, dw[2];
		  valuE val, a, b, c;
		  poinT pt;
		  pointarraY pta_, pta_left, pta_right;


		  convexhull->deletealL();

		  // vyhodime body s rovnakou poziciou
		  pta->copY( &pta_ );
	      for( i = 0;  i < pta_.num;  i++ )
			  for( j = pta_.num-1;  j > i;  j-- ) 
				  if( pta_.elem[i] == pta_.elem[j] ) pta_.deletE( j );

		  // najdeme body s minimalnou a maximalnou suradnicou
		  min_x = max_x = min_y = max_y = 0;
		  for( i = 1;  i < pta_.num;  i++ ) {
			  if( pta_.elem[i].x < pta_.elem[min_x].x ) min_x = i; 
			  if( pta_.elem[i].x > pta_.elem[max_x].x ) max_x = i; 
			  if( pta_.elem[i].y < pta_.elem[min_y].y ) min_y = i; 
			  if( pta_.elem[i].y > pta_.elem[max_y].y ) max_y = i; 
		  }

		  if( pta_.elem[max_x].x-pta_.elem[min_x].x < EPSILON ) {
			  if( pta_.elem[max_y].y-pta_.elem[min_y].y < EPSILON ) { // 0d riesenie - bod
				  convexhull->inserT( -1, pta_.elem[min_x] );

				  return 0;
			  } else { // 1d riesenie - usecka
				  convexhull->inserT( -1, pta_.elem[min_y] );
				  convexhull->inserT( -1, pta_.elem[max_y] );
				  convexhull->inserT( -1, pta_.elem[max_y] ); 
				  convexhull->inserT( -1, pta_.elem[min_y] );

				  return 1;
			  }
		  } else {
			  if( pta_.elem[max_y].y-pta_.elem[min_y].y < EPSILON ) { // 1d riesenie - usecka
				  convexhull->inserT( -1, pta_.elem[min_x] );
				  convexhull->inserT( -1, pta_.elem[max_x] );
				  convexhull->inserT( -1, pta_.elem[max_x] ); 
				  convexhull->inserT( -1, pta_.elem[min_x] );

				  return 1;
			  } else { // 2d riesenie - mnohouholnik
				  // pociatocna usecka
				  dw[0] = min_x;  dw[1] = max_x;
				  planE_( pta_.elem[dw[0]], pta_.elem[dw[1]], &a, &b, &c );

				  // rozdelenie bodov podla deliacej usecky
				  for( i = 0;  i < pta_.num;  i++ ) {
					  val = planepoinT( a, b, c, pta_.elem[i] );
					  if( val < -EPSILON ) pta_left.inserT( -1, pta_.elem[i] ); else
					  if( val > EPSILON ) pta_right.inserT( -1, pta_.elem[i] ); 
				  }

				  // pridame usecky do konvexneho obalu
				  convexhull->inserT( -1, pta_.elem[dw[0]] );
				  convexhull->inserT( -1, pta_.elem[dw[1]] );
				  convexhull->inserT( -1, pta_.elem[dw[1]] ); 
				  convexhull->inserT( -1, pta_.elem[dw[0]] );

				  // rekurzivne zavolame vytvorenie konvexneho obalu pre lavu a pravu polovicu
				  j = convexhull->num;
				  if( pta_left.num > 0 ) quickhull2D_( &pta_left, convexhull, 0, 1 ); 
				  if( pta_right.num > 0 ) quickhull2D_( &pta_right, convexhull, j-2, j-1 );

				  // utriedime najdene usecky konvexneho obalu
				  if( convexhull->num > 1 )
					  for( i = 0;  i < convexhull->num-2;  i+=2 ) {
						  j = i+2;
						  while( j < convexhull->num && convexhull->elem[i+1] != convexhull->elem[j] ) j+=2;
						
						  if( j != convexhull->num ) {
							  pt = convexhull->elem[i+2]; 	
							  convexhull->elem[i+2] = convexhull->elem[j];
							  convexhull->elem[j] = pt;

							  pt = convexhull->elem[i+3]; 	
							  convexhull->elem[i+3] = convexhull->elem[j+1];
							  convexhull->elem[j+1] = pt;
						  } // else error;
					  }

				  return 2;
			  }
		  }
	  } else return -1;
  }




  void findhorizont3D( const poinT& eye, pointarraY *convexhull, arraY_<pointarraY> *ptaa, pointarraY *horizontedg, pointarraY *pta ) {
	  register long i, j;
	  long k;
      BOOL b;
      boolarraY ba;
      planE pl;
      pointarraY edg;
      arraY_<dwordarraY> edgneighb;


      horizontedg->deletealL();


      ba.inserT( -1, FALSE, convexhull->num/3 );
      for( i = 0;  i < convexhull->num;  i+=3 ) {  // pre vsetky steny zatial vytvoreneho konvexneho obalu 
          // rozdelujeme na privratene a odvratene steny 
		  pl = planE( convexhull->elem[i], convexhull->elem[i+1], convexhull->elem[i+2] );
          if( planepoinT( pl, eye ) <= 0.0 ) ba.elem[i/3] = TRUE;

		  // teraz budeme vytvarat hrany steny(ak samozrejme uz neexistuju) a sucasne si pametame, ze tato stena je susedna s pridavanou hranou
          // i, i+1
          b = FALSE;
          for( j = 0;  j < edg.num;  j+=2 )  // pre vsetky zatial pridane hrany  
              if( ( convexhull->elem[i] == edg.elem[j] && convexhull->elem[i+1] == edg.elem[j+1] ) || 
                  ( convexhull->elem[i] == edg.elem[j+1] && convexhull->elem[i+1] == edg.elem[j] ) ) {
                  b = TRUE;
                  k = j;
                  j = edg.num;
              }

          if( b ) {  // hrana uz existuje v zozname hran
              edgneighb.elem[k/2].inserT( -1, i/3 );
          } else {  // neexistuje a treba ju pridat do zoznamu hran
			  if( ba.elem[i/3] ) { // orientacia je rovnaka ako privratenej steny
		          edg.inserT( -1, convexhull->elem[i] );
	              edg.inserT( -1, convexhull->elem[i+1] );
			  } else { // orientacia je opacna ako maju privratene steny, preto zmenime orientaciu hrany
	              edg.inserT( -1, convexhull->elem[i+1] );
		          edg.inserT( -1, convexhull->elem[i] );
			  }
              edgneighb.inserT( -1, NULL );
              edgneighb.elem[edgneighb.num-1].inserT( -1, i/3 );
          }
          //

          // i+1, i+2
          b = FALSE;
          for( j = 0;  j < edg.num;  j+=2 )  // pre vsetky zatial pridane hrany  
              if( ( convexhull->elem[i+1] == edg.elem[j] && convexhull->elem[i+2] == edg.elem[j+1] ) || 
                  ( convexhull->elem[i+1] == edg.elem[j+1] && convexhull->elem[i+2] == edg.elem[j] ) ) {
                  b = TRUE;
                  k = j;
                  j = edg.num;
              }

          if( b ) {  // hrana uz existuje v zozname hran
              edgneighb.elem[k/2].inserT( -1, i/3 );
          } else {  // neexistuje a treba ju pridat do zoznamu hran
			  if( ba.elem[i/3] ) { // orientacia je rovnaka ako privratenej steny
		          edg.inserT( -1, convexhull->elem[i+1] );
	              edg.inserT( -1, convexhull->elem[i+2] );
			  } else { // orientacia je opacna ako maju privratene steny, preto zmenime orientaciu hrany
	              edg.inserT( -1, convexhull->elem[i+2] );
		          edg.inserT( -1, convexhull->elem[i+1] );
			  }
              edgneighb.inserT( -1, NULL );
              edgneighb.elem[edgneighb.num-1].inserT( -1, i/3 );
          }
          //

          // i+2, i
          b = FALSE;
          for( j = 0;  j < edg.num;  j+=2 )  // pre vsetky zatial pridane hrany  
              if( ( convexhull->elem[i+2] == edg.elem[j] && convexhull->elem[i] == edg.elem[j+1] ) || 
                  ( convexhull->elem[i+2] == edg.elem[j+1] && convexhull->elem[i] == edg.elem[j] ) ) {
                  b = TRUE;
                  k = j;
                  j = edg.num;
              }

          if( b ) {  // hrana uz existuje v zozname hran
              edgneighb.elem[k/2].inserT( -1, i/3 );
          } else {  // neexistuje a treba ju pridat do zoznamu hran
			  if( ba.elem[i/3] ) { // orientacia je rovnaka ako privratenej steny
		          edg.inserT( -1, convexhull->elem[i+2] );
	              edg.inserT( -1, convexhull->elem[i] );
			  } else { // orientacia je opacna ako maju privratene steny, preto zmenime orientaciu hrany
	              edg.inserT( -1, convexhull->elem[i] );
		          edg.inserT( -1, convexhull->elem[i+2] );
			  }
              edgneighb.inserT( -1, NULL );
              edgneighb.elem[edgneighb.num-1].inserT( -1, i/3 );
          }
          //
      }

      // vytvorime mnozinu hran(horizontedg) tvoriacu horizont z pohladu bodu eye
      for( i = 0;  i < edg.num/2;  i++ ) 
          if( ba.elem[edgneighb.elem[i].elem[0]] != ba.elem[edgneighb.elem[i].elem[1]] ) {
              horizontedg->inserT( -1, edg.elem[2*i] );
              horizontedg->inserT( -1, edg.elem[2*i+1] );
          }

      // vymazeme privratene steny
	  pta->deletealL();
      for( i = convexhull->num/3-1;  i >= 0;  i-- )
          if( ba.elem[i] ) {
			  k = 3*i;
              convexhull->deletE( k );
              convexhull->deletE( k );
              convexhull->deletE( k );

			  // spojime body vymazanych stien do jedneho pola bodov, ktore neskor rozdelime medzi novovzniknute steny
			  pta->inserT( -1, poinT(), ptaa->elem[i].num );
			  for( j = 0;  j < ptaa->elem[i].num;  j++ ) pta->elem[pta->num+j-ptaa->elem[i].num] = ptaa->elem[i].elem[j];
			  ptaa->deletE( i );
          }
  }




  inline valuE tetrahedronvolumE( const poinT& pt0, const poinT& pt1, const poinT& pt2, const poinT& pt3 ) {
	  return ( ( pt0.x-pt1.x )*( pt0.y-pt2.y )*( pt0.z-pt3.z ) + ( pt0.y-pt1.y )*( pt0.z-pt2.z )*( pt0.x-pt3.x ) + ( pt0.z-pt1.z )*( pt0.x-pt2.x )*( pt0.y-pt3.y ) -
		       ( pt0.z-pt1.z )*( pt0.y-pt2.y )*( pt0.x-pt3.x ) - ( pt0.x-pt1.x )*( pt0.z-pt2.z )*( pt0.y-pt3.y ) - ( pt0.y-pt1.y )*( pt0.x-pt2.x )*( pt0.z-pt3.z ) )/6.0;
  }




  long quickhull3D( pointarraY *pta, pointarraY *convexhull ) {
	  if( pta->num > 0 ) {
		  register long i, j;
		  long k;
		  BOOL b[5][6];
		  DWORD min_x, max_x, min_y, max_y, min_z, max_z, dw[3];
		  valuE val, val2;
		  vectoR u;
		  poinT pt;
		  planE pl;
		  pointarraY pta_, pta2, horizontedg;
		  arraY_<pointarraY> ptaa;


		  convexhull->deletealL();

		  // vyhodime body s rovnakou poziciou
		  pta->copY( &pta_ );
	      for( i = 0;  i < pta_.num;  i++ )
			  for( j = pta_.num-1;  j > i;  j-- ) 
				  if( pta_.elem[i] == pta_.elem[j] ) pta_.deletE( j );

		  // najdeme body s minimalnou a maximalnou suradnicou
		  min_x = max_x = min_y = max_y = min_z = max_z = 0;
		  for( i = 1;  i < pta_.num;  i++ ) {
			  if( pta_.elem[i].x < pta_.elem[min_x].x ) min_x = i;
			  if( pta_.elem[i].x > pta_.elem[max_x].x ) max_x = i; 
			  if( pta_.elem[i].y < pta_.elem[min_y].y ) min_y = i;
			  if( pta_.elem[i].y > pta_.elem[max_y].y ) max_y = i; 
			  if( pta_.elem[i].z < pta_.elem[min_z].z ) min_z = i;
			  if( pta_.elem[i].z > pta_.elem[max_z].z ) max_z = i; 
		  }

		  if( pta_.elem[max_x].x-pta_.elem[min_x].x < EPSILON ) {
			  if( pta_.elem[max_y].y-pta_.elem[min_y].y < EPSILON ) {
				  if( pta_.elem[max_z].z-pta_.elem[min_z].z < EPSILON ) { // 0d riesenie - bod
					  convexhull->inserT( -1, pta_.elem[min_x] );

					  return 0;
				  } else { // 1d riesenie - usecka
					  convexhull->inserT( -1, pta_.elem[min_z] );
					  convexhull->inserT( -1, pta_.elem[max_z] );
					  convexhull->inserT( -1, pta_.elem[max_z] ); 
					  convexhull->inserT( -1, pta_.elem[min_z] );

					  return 1;
				  }
			  } else {
				  if( pta_.elem[max_z].z-pta_.elem[min_z].z < EPSILON ) { // 1d riesenie - usecka
					  convexhull->inserT( -1, pta_.elem[min_y] );
					  convexhull->inserT( -1, pta_.elem[max_y] );
					  convexhull->inserT( -1, pta_.elem[max_y] ); 
					  convexhull->inserT( -1, pta_.elem[min_y] );

					  return 1;
				  } else { // 2d riesenie - mnohouholnik
					  for( i = 0;  i < pta_.num;  i++ ) {
						  pta_.elem[i].x = pta_.elem[i].y;
						  pta_.elem[i].y = pta_.elem[i].z;
						  pta_.elem[i].z = 0.0;
					  }

					  quickhull2D( pta, convexhull );

					  return 2;
				  }
			  }
		  } else {
			  if( pta_.elem[max_y].y-pta_.elem[min_y].y < EPSILON ) {
				  if( pta_.elem[max_z].z-pta_.elem[min_z].z < EPSILON ) { // 1d riesenie - usecka
					  convexhull->inserT( -1, pta_.elem[min_x] );
					  convexhull->inserT( -1, pta_.elem[max_x] );
					  convexhull->inserT( -1, pta_.elem[max_x] ); 
					  convexhull->inserT( -1, pta_.elem[min_x] );

					  return 1;
				  } else { // 2d riesenie - mnohouholnik
					  for( i = 0;  i < pta_.num;  i++ ) {
						  pta_.elem[i].y = pta_.elem[i].z;
						  pta_.elem[i].z = 0.0;
					  }

					  quickhull2D( pta, convexhull );

					  return 2;
				  }
			  } else {
				  if( pta_.elem[max_z].z-pta_.elem[min_z].z < EPSILON ) { // 2d riesenie - mnohouholnik
					  for( i = 0;  i < pta_.num;  i++ ) pta_.elem[i].z = 0.0;

					  quickhull2D( pta, convexhull );

					  return 2;
				  } else { // 3d riesenie - mnohosten
					  // zaciatocny trojuholnik
					  b[0][1] = pta_.elem[min_x] != pta_.elem[max_x];
					  b[0][2] = pta_.elem[min_x] != pta_.elem[min_y];
					  b[0][3] = pta_.elem[min_x] != pta_.elem[max_y];
					  b[0][4] = pta_.elem[min_x] != pta_.elem[min_z];
					  b[0][5] = pta_.elem[min_x] != pta_.elem[max_z];
					  b[1][2] = pta_.elem[max_x] != pta_.elem[min_y];
					  b[1][3] = pta_.elem[max_x] != pta_.elem[max_y];
					  b[1][4] = pta_.elem[max_x] != pta_.elem[min_z];
					  b[1][5] = pta_.elem[max_x] != pta_.elem[max_z];
					  b[2][3] = pta_.elem[min_y] != pta_.elem[max_y];
					  b[2][4] = pta_.elem[min_y] != pta_.elem[min_z];
					  b[2][5] = pta_.elem[min_y] != pta_.elem[max_z];
					  b[3][4] = pta_.elem[max_y] != pta_.elem[min_z];
					  b[3][5] = pta_.elem[max_y] != pta_.elem[max_z];
					  b[4][5] = pta_.elem[min_z] != pta_.elem[max_z];

					  if( b[0][1] & b[0][2] & b[1][2] ) {
						  dw[0] = min_x;  
						  dw[1] = max_x;  
						  dw[2] = min_y;
					  } else
					  if( b[0][1] & b[0][3] & b[1][3] ) {
						  dw[0] = min_x;  
						  dw[1] = max_x;  
						  dw[2] = max_y;
					  } else
					  if( b[0][1] & b[0][4] & b[1][4] ) {
						  dw[0] = min_x;  
						  dw[1] = max_x;  
						  dw[2] = min_z;
					  } else
					  if( b[0][1] & b[0][5] & b[1][5] ) {
						  dw[0] = min_x;  
						  dw[1] = max_x;  
						  dw[2] = max_z;
					  } else
					  if( b[0][2] & b[0][3] & b[2][3] ) {
						  dw[0] = min_x;  
						  dw[1] = min_y;  
						  dw[2] = max_y;
					  } else
					  if( b[0][2] & b[0][4] & b[2][4] ) {
						  dw[0] = min_x;  
						  dw[1] = min_y;  
						  dw[2] = min_z;
					  } else
					  if( b[0][2] & b[0][5] & b[2][5] ) {
						  dw[0] = min_x;  
						  dw[1] = min_y;  
						  dw[2] = max_z;
					  } else
					  if( b[0][3] & b[0][4] & b[3][4] ) {
						  dw[0] = min_x;  
						  dw[1] = max_y;  
						  dw[2] = min_z;
					  } else
					  if( b[0][3] & b[0][5] & b[3][5] ) {
						  dw[0] = min_x;  
						  dw[1] = max_y;  
						  dw[2] = max_z;
					  } else
					  if( b[0][4] & b[0][5] & b[4][5] ) {
						  dw[0] = min_x;  
						  dw[1] = min_z;  
						  dw[2] = max_z;
					  } else
					  if( b[1][2] & b[1][3] & b[2][3] ) {
						  dw[0] = max_x;  
						  dw[1] = min_y;  
						  dw[2] = max_y;
					  } else
					  if( b[1][2] & b[1][4] & b[2][4] ) {
						  dw[0] = max_x;  
						  dw[1] = min_y;  
						  dw[2] = min_z;
					  } else
					  if( b[1][2] & b[1][5] & b[2][5] ) {
						  dw[0] = max_x;  
						  dw[1] = min_y;  
						  dw[2] = max_z;
					  } else
					  if( b[1][3] & b[1][4] & b[3][4] ) {
						  dw[0] = max_x;  
						  dw[1] = max_y;  
						  dw[2] = min_z;
					  } else
					  if( b[1][3] & b[1][5] & b[3][5] ) {
						  dw[0] = max_x;  
						  dw[1] = max_y;  
						  dw[2] = max_z;
					  } else
					  if( b[1][4] & b[1][5] & b[4][5] ) {
						  dw[0] = max_x;  
						  dw[1] = min_z;  
						  dw[2] = max_z;
					  } else
					  if( b[2][3] & b[2][4] & b[3][4] ) {
						  dw[0] = min_y;  
						  dw[1] = max_y;  
						  dw[2] = min_z;
					  } else
					  if( b[2][3] & b[2][5] & b[3][5] ) {
						  dw[0] = min_y;  
						  dw[1] = max_y;  
						  dw[2] = max_z;
					  } else
					  if( b[2][4] & b[2][5] & b[4][5] ) {
						  dw[0] = min_y;  
						  dw[1] = min_z;  
						  dw[2] = max_z;
					  } else
					  if( b[3][4] & b[3][5] & b[4][5] ) {
						  dw[0] = max_y;  
						  dw[1] = min_z;  
						  dw[2] = max_z;
					  }	else { // neexistuju tri rozne body

						  return -1; // nedokoncene
					  }


					  // pridame trojuholniky do konvexneho obalu
					  convexhull->inserT( -1, pta_.elem[dw[0]] );
					  convexhull->inserT( -1, pta_.elem[dw[1]] );
					  convexhull->inserT( -1, pta_.elem[dw[2]] );
					  convexhull->inserT( -1, pta_.elem[dw[0]] ); 
					  convexhull->inserT( -1, pta_.elem[dw[2]] ); 
					  convexhull->inserT( -1, pta_.elem[dw[1]] );


					  // rozdelime body podla najdenej zaciatocnej roviny
					  ptaa.inserT( -1, NULL, 2 );
				      pl = planE( pta_.elem[dw[0]], pta_.elem[dw[1]], pta_.elem[dw[2]] );
					  for( i = 0;  i < pta_.num;  i++ ) 
						  if( i != dw[0] && i != dw[1] && i != dw[2] ) { 
							  if( planepoinT( pl, pta_.elem[i] ) <= 0.0 ) ptaa.elem[0].inserT( -1, pta_.elem[i] ); else ptaa.elem[1].inserT( -1, pta_.elem[i] ); 
						  }


					  do { // pokial existuje stena s nenulovym poctom bodov na jej 'lavej' strane
						  // najdeme stenu s nenulovym poctom bodov na 'lavej' strane
						  b[0][0] = FALSE;
						  for( i = 0;  i < ptaa.num;  i++ ) 
							  if( ptaa.elem[i].num > 0 ) { // stena najdena
								  b[0][0] = TRUE;  
								  k = i;
								  i = ptaa.num;
							  }

						  if( b[0][0] ) { // existuje stena s nenulovym poctom bodov na svojej 'lavej' strane
							  // najdeme stvorsten s max. objemom
							  val = -INFINITY;
							  for( i = 0;  i < ptaa.elem[k].num;  i++ ) {
								  val2 = -tetrahedronvolumE( ptaa.elem[k].elem[i], convexhull->elem[3*k], convexhull->elem[3*k+1], convexhull->elem[3*k+2] ); 
								  if( val2 > val ) {
									  val = val2;
									  pt = ptaa.elem[k].elem[i];
								  }
							  }

							  // najdeme horizont z bodu s max. objemom, (findhorizont3D sucasne zmazava privratene steny)
							  findhorizont3D( pt, convexhull, &ptaa, &horizontedg, &pta2 );

							  ptaa.inserT( -1, NULL, horizontedg.num/2 );
							  convexhull->inserT( -1, poinT(), 3*horizontedg.num/2 );

							  // rozdelime body podla toho v ktorej polrovine lezia
							  for( i = 0;  i < horizontedg.num/2;  i++ ) {
								  pl = planE( horizontedg.elem[2*i], horizontedg.elem[2*i+1], pt );

								  // pridame trojuholniky do konvexneho obalu
								  convexhull->elem[convexhull->num-3*( horizontedg.num/2-i )] = horizontedg.elem[2*i];
								  convexhull->elem[convexhull->num-3*( horizontedg.num/2-i )+1] = horizontedg.elem[2*i+1];
								  convexhull->elem[convexhull->num-3*( horizontedg.num/2-i )+2] = pt;

								  for( k = pta2.num-1;  k >= 0;  k-- ) 
									  if( pta2.elem[k] != horizontedg.elem[2*i] && pta2.elem[k] != horizontedg.elem[2*i+1] && pta2.elem[k] != pt )  
										  if( planepoinT( pl, pta2.elem[k] ) <= 0.0 ) {
											  ptaa.elem[ptaa.num-horizontedg.num/2+i].inserT( -1, pta2.elem[k] ); 
											  pta2.deletE( k );
										  }
							  }
						  }
					  } while( b[0][0] );


					  return 3;
				  }
			  }
		  }
	  } else return -1;
  }
