
  #undef PI
  #undef INV_PI
  #undef PI_TIMES2
  #undef INV_PI_TIMES2
  #undef PI_OVER2
  #undef INV_PI_OVER2
  #undef DEG_RAD
  #undef RAD_DEG
  #undef SQRT2
  #undef INV_SQRT2
  #undef SQRT3
  #undef INV_SQRT3
  #undef LOG2
  #undef INV_LOG2
  #undef LN2
  #undef INV_LN2
  #undef INFINITY
  #undef INF
  #undef EPSILON
  #undef EPS
  #undef EULER_NUMBER
  #undef INV_255

  #define PI 3.141592653589793238462643383279502884197169399375105820975
  #define INV_PI ( 1.0/PI )
  #define PI_TIMES2 ( 2.0*PI )
  #define INV_PI_TIMES2 ( 1.0/( 2.0*PI ) )
  #define PI_OVER2 ( 0.5*PI )
  #define INV_PI_OVER2 ( 1.0/( 0.5*PI ) )
  #define DEG_RAD ( PI/180.0 )
  #define RAD_DEG ( 180.0/PI )
  #define SQRT2 pow( 2.0, 0.5 )
  #define INV_SQRT2 ( 1.0/SQRT2 )
  #define SQRT3 pow( 3.0, 0.5 )
  #define INV_SQRT3 ( 1.0/SQRT3 )
  #define LOG2 log10( 2.0 )
  #define INV_LOG2 ( 1.0/LOG2 )
  #define LN2 log( 2.0 )
  #define INV_LN2 ( 1.0/LN2 )
  #define INFINITY 10000000.0
  #define INF INFINITY
  #define EPSILON 0.0001
  #define EPS EPSILON
  #define EULER_NUMBER 2.7182818284590452353602874713527  
  #define INV_255 ( 1.0/255.0 )