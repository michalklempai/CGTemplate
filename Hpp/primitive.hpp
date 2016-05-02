
  void spherE( valuE radius, valuE zmin, valuE zmax, valuE thetamax, long slices, long stacks, mesH *M );
  void conE( valuE height, valuE radius, valuE thetamax, long slices, long stacks, mesH *M );
  void cylindeR( valuE radius, valuE zmin, valuE zmax, valuE thetamax, long slices, long stacks, mesH *M );
  void hyperboloiD( poinT pt1, poinT pt2, valuE thetamax, long slices, long stacks, mesH *M );
  void paraboloiD( valuE rmax, valuE zmin, valuE zmax, valuE thetamax, long slices, long stacks, mesH *M );
  void disK( valuE height, valuE radius, valuE thetamax, long slices, long stacks, mesH *M );
  void toruS( valuE majorradius, valuE minorradius, valuE phimin, valuE phimax, valuE thetamax, long slices, long stacks, mesH *M );






  void spherE( valuE radius, valuE zmin, valuE zmax, valuE thetamax, long slices, long stacks, mesH *M ) {
      if( M != NULL ) {
          register long i, j;
          valuE val, val2, phimin, phimax, phi, theta, u, v;

          if( zmin > -radius ) phimin = asin( zmin/radius ); else phimin = -90.0;
          if( zmax < radius ) phimax = asin( zmax/radius ); else phimax = 90.0;

          M->deletealL();

          M->Va.n = slices+1;
          M->Va.m = stacks+1;
          M->Va.inserT( -1, NULL, M->Va.n*M->Va.m );
          for( j = 0;  j < M->Va.m;  j++ ) {
              v = (valuE)j/stacks;

              phi = phimin+v*( phimax-phimin );

              val = radius*sin( phi*DEG_RAD );
              val2 = radius*cos( phi*DEG_RAD );

              for( i = 0;  i < M->Va.n;  i++ ) {
                  u = (valuE)i/slices;

                  theta = u*thetamax;

                  M->Va.elem[i+j*M->Va.n].v.x = cos( theta*DEG_RAD )*val2;
                  M->Va.elem[i+j*M->Va.n].v.y = sin( theta*DEG_RAD )*val2;
                  M->Va.elem[i+j*M->Va.n].v.z = val;
                  M->Va.elem[i+j*M->Va.n].t.x = u;
                  M->Va.elem[i+j*M->Va.n].t.y = v;
                  M->Va.elem[i+j*M->Va.n].t.z = 0.0;
                  M->Va.elem[i+j*M->Va.n].n = normalizE( vectoR( M->Va.elem[i+j*M->Va.n].v.x, M->Va.elem[i+j*M->Va.n].v.y, M->Va.elem[i+j*M->Va.n].v.z ) );
              }
          }

          M->Fa.inserT( -1, NULL, 2*slices*stacks );
          for( j = 0;  j < stacks;  j++ )
              for( i = 0;  i < slices;  i++ ) {
                  M->Fa.elem[2*( i+j*slices )].Via.inserT( -1, 0, 3 );
                  M->Fa.elem[2*( i+j*slices )].Via.elem[0] = i+j*M->Va.n;
                  M->Fa.elem[2*( i+j*slices )].Via.elem[1] = i+1+j*M->Va.n;
                  M->Fa.elem[2*( i+j*slices )].Via.elem[2] = i+( j+1 )*M->Va.n;

                  M->Fa.elem[2*( i+j*slices )+1].Via.inserT( -1, 0, 3 );
                  M->Fa.elem[2*( i+j*slices )+1].Via.elem[0] = i+1+j*M->Va.n;
                  M->Fa.elem[2*( i+j*slices )+1].Via.elem[1] = i+1+( j+1 )*M->Va.n;
                  M->Fa.elem[2*( i+j*slices )+1].Via.elem[2] = i+( j+1 )*M->Va.n;
              }
      }
  }




  void conE( valuE height, valuE radius, valuE thetamax, long slices, long stacks, mesH *M ) {
      if( M != NULL ) {
          register long i, j;
          valuE val, val2, theta, u, v;

          M->deletealL();

          M->Va.n = slices+1;
          M->Va.m = stacks+1;
          M->Va.inserT( -1, NULL, M->Va.n*M->Va.m );
          for( j = 0;  j < M->Va.m;  j++ ) {
              v = (valuE)j/stacks;

              val = radius*( 1.0-v );
              val2 = v*height;

              for( i = 0;  i < M->Va.n;  i++ ) {
                  u = (valuE)i/slices;

                  theta = u*thetamax;

                  M->Va.elem[i+j*M->Va.n].v.x = val*cos( theta*DEG_RAD );
                  M->Va.elem[i+j*M->Va.n].v.y = val*sin( theta*DEG_RAD );
                  M->Va.elem[i+j*M->Va.n].v.z = val2;
                  M->Va.elem[i+j*M->Va.n].t.x = u;
                  M->Va.elem[i+j*M->Va.n].t.y = v;
                  M->Va.elem[i+j*M->Va.n].t.z = 0.0;
                  M->Va.elem[i+j*M->Va.n].n = normalizE( crosS( vectoR( -M->Va.elem[i+j*M->Va.n].v.y*thetamax, M->Va.elem[i+j*M->Va.n].v.x*thetamax, 0.0 ),
                                                                vectoR( -radius*cos( theta*DEG_RAD ), -radius*sin( theta*DEG_RAD ), height ) ) );
              }
          }

          M->Fa.inserT( -1, NULL, 2*slices*stacks );
          for( j = 0;  j < stacks;  j++ )
              for( i = 0;  i < slices;  i++ ) {
                  M->Fa.elem[2*( i+j*slices )].Via.inserT( -1, 0, 3 );
                  M->Fa.elem[2*( i+j*slices )].Via.elem[0] = i+j*M->Va.n;
                  M->Fa.elem[2*( i+j*slices )].Via.elem[1] = i+1+j*M->Va.n;
                  M->Fa.elem[2*( i+j*slices )].Via.elem[2] = i+( j+1 )*M->Va.n;

                  M->Fa.elem[2*( i+j*slices )+1].Via.inserT( -1, 0, 3 );
                  M->Fa.elem[2*( i+j*slices )+1].Via.elem[0] = i+1+j*M->Va.n;
                  M->Fa.elem[2*( i+j*slices )+1].Via.elem[1] = i+1+( j+1 )*M->Va.n;
                  M->Fa.elem[2*( i+j*slices )+1].Via.elem[2] = i+( j+1 )*M->Va.n;
              }
      }
  }




  void cylindeR( valuE radius, valuE zmin, valuE zmax, valuE thetamax, long slices, long stacks, mesH *M ) {
      if( M != NULL ) {
          register long i, j;
          valuE val, theta, u, v;

          M->deletealL();

          M->Va.n = slices+1;
          M->Va.m = stacks+1;
          M->Va.inserT( -1, NULL, M->Va.n*M->Va.m );
          for( j = 0;  j < M->Va.m;  j++ ) {
              v = (valuE)j/stacks;

              val = zmin+v*( zmax-zmin );

              for( i = 0;  i < M->Va.n;  i++ ) {
                  u = (valuE)i/slices;

                  theta = u*thetamax;

                  M->Va.elem[i+j*M->Va.n].v.x = radius*cos( theta*DEG_RAD );
                  M->Va.elem[i+j*M->Va.n].v.y = radius*sin( theta*DEG_RAD );
                  M->Va.elem[i+j*M->Va.n].v.z = val;
                  M->Va.elem[i+j*M->Va.n].t.x = u;
                  M->Va.elem[i+j*M->Va.n].t.y = v;
                  M->Va.elem[i+j*M->Va.n].t.z = 0.0;
                  M->Va.elem[i+j*M->Va.n].n = normalizE( vectoR( M->Va.elem[i+j*M->Va.n].v.x, M->Va.elem[i+j*M->Va.n].v.y, 0.0 ) );
              }
          }

          M->Fa.inserT( -1, NULL, 2*slices*stacks );
          for( j = 0;  j < stacks;  j++ )
              for( i = 0;  i < slices;  i++ ) {
                  M->Fa.elem[2*( i+j*slices )].Via.inserT( -1, 0, 3 );
                  M->Fa.elem[2*( i+j*slices )].Via.elem[0] = i+j*M->Va.n;
                  M->Fa.elem[2*( i+j*slices )].Via.elem[1] = i+1+j*M->Va.n;
                  M->Fa.elem[2*( i+j*slices )].Via.elem[2] = i+( j+1 )*M->Va.n;

                  M->Fa.elem[2*( i+j*slices )+1].Via.inserT( -1, 0, 3 );
                  M->Fa.elem[2*( i+j*slices )+1].Via.elem[0] = i+1+j*M->Va.n;
                  M->Fa.elem[2*( i+j*slices )+1].Via.elem[1] = i+1+( j+1 )*M->Va.n;
                  M->Fa.elem[2*( i+j*slices )+1].Via.elem[2] = i+( j+1 )*M->Va.n;
              }
      }
  }




  void hyperboloiD( poinT pt1, poinT pt2, valuE thetamax, long slices, long stacks, mesH *M ) {
      if( M != NULL ) {
          register long i, j;
          valuE val, val2, theta, u, v;
          poinT ptr;

          M->deletealL();

          M->Va.n = slices+1;
          M->Va.m = stacks+1;
          M->Va.inserT( -1, NULL, M->Va.n*M->Va.m );
          for( j = 0;  j < M->Va.m;  j++ ) {
              v = (valuE)j/stacks;

              ptr.x = ( 1.0-v )*pt1.x+v*pt2.x;
              ptr.y = ( 1.0-v )*pt1.y+v*pt2.y;
              ptr.z = ( 1.0-v )*pt1.z+v*pt2.z;

              for( i = 0;  i < M->Va.n;  i++ ) {
                  u = (valuE)i/slices;

                  theta = u*thetamax;

                  val = sin( theta*DEG_RAD );  val2 = cos( theta*DEG_RAD );
                  M->Va.elem[i+j*M->Va.n].v.x = ptr.x*val2-ptr.y*val;
                  M->Va.elem[i+j*M->Va.n].v.y = ptr.x*val+ptr.y*val2;
                  M->Va.elem[i+j*M->Va.n].v.z = ptr.z;
                  M->Va.elem[i+j*M->Va.n].t.x = u;
                  M->Va.elem[i+j*M->Va.n].t.y = v;
                  M->Va.elem[i+j*M->Va.n].t.z = 0.0;
              }
          }

          M->Fa.inserT( -1, NULL, 2*slices*stacks );
          for( j = 0;  j < stacks;  j++ )
              for( i = 0;  i < slices;  i++ ) {
                  M->Fa.elem[2*( i+j*slices )].Via.inserT( -1, 0, 3 );
                  M->Fa.elem[2*( i+j*slices )].Via.elem[0] = i+j*M->Va.n;
                  M->Fa.elem[2*( i+j*slices )].Via.elem[1] = i+1+j*M->Va.n;
                  M->Fa.elem[2*( i+j*slices )].Via.elem[2] = i+( j+1 )*M->Va.n;

                  M->Fa.elem[2*( i+j*slices )+1].Via.inserT( -1, 0, 3 );
                  M->Fa.elem[2*( i+j*slices )+1].Via.elem[0] = i+1+j*M->Va.n;
                  M->Fa.elem[2*( i+j*slices )+1].Via.elem[1] = i+1+( j+1 )*M->Va.n;
                  M->Fa.elem[2*( i+j*slices )+1].Via.elem[2] = i+( j+1 )*M->Va.n;
              }
      }
  }




  void paraboloiD( valuE rmax, valuE zmin, valuE zmax, valuE thetamax, long slices, long stacks, mesH *M ) {
      if( M != NULL ) {
          register long i, j;
          valuE val, r, theta, u, v;

          M->deletealL();

          M->Va.n = slices+1;
          M->Va.m = stacks+1;
          M->Va.inserT( -1, NULL, M->Va.n*M->Va.m );
          for( j = 0;  j < M->Va.m;  j++ ) {
              v = (valuE)j/stacks;

              val = zmin+v*( zmax-zmin );

              r = rmax*sqrT( val/zmax );

              for( i = 0;  i < M->Va.n;  i++ ) {
                  u = (valuE)i/slices;

                  theta = u*thetamax;

                  M->Va.elem[i+j*M->Va.n].v.x = r*cos( theta*DEG_RAD );
                  M->Va.elem[i+j*M->Va.n].v.y = r*sin( theta*DEG_RAD );
                  M->Va.elem[i+j*M->Va.n].v.z = val;
                  M->Va.elem[i+j*M->Va.n].t.x = u;
                  M->Va.elem[i+j*M->Va.n].t.y = v;
                  M->Va.elem[i+j*M->Va.n].t.z = 0.0;
              }
          }

          M->Fa.inserT( -1, NULL, 2*slices*stacks );
          for( j = 0;  j < stacks;  j++ )
              for( i = 0;  i < slices;  i++ ) {
                  M->Fa.elem[2*( i+j*slices )].Via.inserT( -1, 0, 3 );
                  M->Fa.elem[2*( i+j*slices )].Via.elem[0] = i+j*M->Va.n;
                  M->Fa.elem[2*( i+j*slices )].Via.elem[1] = i+1+j*M->Va.n;
                  M->Fa.elem[2*( i+j*slices )].Via.elem[2] = i+( j+1 )*M->Va.n;

                  M->Fa.elem[2*( i+j*slices )+1].Via.inserT( -1, 0, 3 );
                  M->Fa.elem[2*( i+j*slices )+1].Via.elem[0] = i+1+j*M->Va.n;
                  M->Fa.elem[2*( i+j*slices )+1].Via.elem[1] = i+1+( j+1 )*M->Va.n;
                  M->Fa.elem[2*( i+j*slices )+1].Via.elem[2] = i+( j+1 )*M->Va.n;
              }
      }
  }




  void disK( valuE height, valuE radius, valuE thetamax, long slices, long stacks, mesH *M ) {
      if( M != NULL ) {
          register long i, j;
          valuE val, theta, u, v;

          M->deletealL();

          M->Va.n = slices+1;
          M->Va.m = stacks+1;
          M->Va.inserT( -1, NULL, M->Va.n*M->Va.m );
          for( j = 0;  j < M->Va.m;  j++ ) {
              v = (valuE)j/stacks;

              val = radius*( 1.0-v );

              for( i = 0;  i < M->Va.n;  i++ ) {
                  u = (valuE)i/slices;

                  theta = u*thetamax;

                  M->Va.elem[i+j*M->Va.n].v.x = val*cos( theta*DEG_RAD );
                  M->Va.elem[i+j*M->Va.n].v.y = val*sin( theta*DEG_RAD );
                  M->Va.elem[i+j*M->Va.n].v.z = height;
                  M->Va.elem[i+j*M->Va.n].t.x = u;
                  M->Va.elem[i+j*M->Va.n].t.y = v;
                  M->Va.elem[i+j*M->Va.n].t.z = 0.0;
                  M->Va.elem[i+j*M->Va.n].n = normalizE( crosS( vectoR( -M->Va.elem[i+j*M->Va.n].v.y*thetamax, M->Va.elem[i+j*M->Va.n].v.x*thetamax, 0.0 ),
                                                                vectoR( -radius*cos( theta*DEG_RAD ), -radius*sin( theta*DEG_RAD ), 0.0 ) ) );
              }
          }

          M->Fa.inserT( -1, NULL, 2*slices*stacks );
          for( j = 0;  j < stacks;  j++ )
              for( i = 0;  i < slices;  i++ ) {
                  M->Fa.elem[2*( i+j*slices )].Via.inserT( -1, 0, 3 );
                  M->Fa.elem[2*( i+j*slices )].Via.elem[0] = i+j*M->Va.n;
                  M->Fa.elem[2*( i+j*slices )].Via.elem[1] = i+1+j*M->Va.n;
                  M->Fa.elem[2*( i+j*slices )].Via.elem[2] = i+( j+1 )*M->Va.n;

                  M->Fa.elem[2*( i+j*slices )+1].Via.inserT( -1, 0, 3 );
                  M->Fa.elem[2*( i+j*slices )+1].Via.elem[0] = i+1+j*M->Va.n;
                  M->Fa.elem[2*( i+j*slices )+1].Via.elem[1] = i+1+( j+1 )*M->Va.n;
                  M->Fa.elem[2*( i+j*slices )+1].Via.elem[2] = i+( j+1 )*M->Va.n;
              }
      }
  }




  void toruS( valuE majorradius, valuE minorradius, valuE phimin, valuE phimax, valuE thetamax, long slices, long stacks, mesH *M ) {
      if( M != NULL ) {
          register long i, j;
          valuE val, val2, r, phi, theta, u, v;

          M->deletealL();

          M->Va.n = slices+1;
          M->Va.m = stacks+1;
          M->Va.inserT( -1, NULL, M->Va.n*M->Va.m );
          for( j = 0;  j < M->Va.m;  j++ ) {
              v = (valuE)j/stacks;

              phi = phimin+v*( phimax-phimin );
              r = minorradius*cos( phi*DEG_RAD );

              val = majorradius+r;
              val2 = minorradius*sin( phi*DEG_RAD );

              for( i = 0;  i < M->Va.n;  i++ ) {
                  u = (valuE)i/slices;

                  theta = u*thetamax;

                  M->Va.elem[i+j*M->Va.n].v.x = val*cos( theta*DEG_RAD );
                  M->Va.elem[i+j*M->Va.n].v.y = val*sin( theta*DEG_RAD );
                  M->Va.elem[i+j*M->Va.n].v.z = val2;
                  M->Va.elem[i+j*M->Va.n].t.x = u;
                  M->Va.elem[i+j*M->Va.n].t.y = v;
                  M->Va.elem[i+j*M->Va.n].t.z = 0.0;
                  M->Va.elem[i+j*M->Va.n].n = normalizE( M->Va.elem[i+j*M->Va.n].v-poinT( cos( theta*DEG_RAD )*majorradius, sin( theta*DEG_RAD )*majorradius, 0.0 ) );
              }
          }

          M->Fa.inserT( -1, NULL, 2*slices*stacks );
          for( j = 0;  j < stacks;  j++ )
              for( i = 0;  i < slices;  i++ ) {
                  M->Fa.elem[2*( i+j*slices )].Via.inserT( -1, 0, 3 );
                  M->Fa.elem[2*( i+j*slices )].Via.elem[0] = i+j*M->Va.n;
                  M->Fa.elem[2*( i+j*slices )].Via.elem[1] = i+1+j*M->Va.n;
                  M->Fa.elem[2*( i+j*slices )].Via.elem[2] = i+( j+1 )*M->Va.n;

                  M->Fa.elem[2*( i+j*slices )+1].Via.inserT( -1, 0, 3 );
                  M->Fa.elem[2*( i+j*slices )+1].Via.elem[0] = i+1+j*M->Va.n;
                  M->Fa.elem[2*( i+j*slices )+1].Via.elem[1] = i+1+( j+1 )*M->Va.n;
                  M->Fa.elem[2*( i+j*slices )+1].Via.elem[2] = i+( j+1 )*M->Va.n;
              }
      }
  }

