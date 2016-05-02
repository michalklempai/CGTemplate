
  #include <typeinfo> 
  
  #pragma warning( disable : 4244 4018 4715 4305 4083 4309 ) 

  #include "opengl//opengl.hpp"
  #include "..//cpp//opengl//opengl.cpp" 

  #include "math.hpp"
  #include "..//cpp//math.cpp" 
  #include "array.hpp"
  #include "..//cpp//array.cpp" 
  #include "bool.hpp"
  #include "..//cpp//bool.cpp" 
  #include "dword.hpp"
  #include "..//cpp//dword.cpp" 
  #include "value.hpp" 
  #include "..//cpp//value.cpp" 
  #include "vector.hpp"
  #include "..//cpp//vector.cpp" 
  #include "point.hpp"
  #include "..//cpp//point.cpp" 
  #include "homogcoord.hpp"
  #include "..//cpp//homogcoord.cpp" 
  #include "complex.hpp"
  #include "..//cpp//complex.cpp" 
  #include "quaternion.hpp"
  #include "..//cpp//quaternion.cpp" 
  #include "ciexyz31.hpp"
  #include "..//cpp//ciexyz31.cpp" 
  #include "color.hpp"
  #include "..//cpp//color.cpp" 
  #include "complexior.hpp" 
  #include "..//cpp//complexior.cpp" 
  #include "ray.hpp"
  #include "..//cpp//ray.cpp" 
  #include "plane.hpp"
  #include "..//cpp//plane.cpp" 
  #include "convexhull.hpp" 
  #include "..//cpp//convexhull.cpp" 
  #include "matrix.hpp" 
  #include "..//cpp//matrix.cpp" 
  #include "aabbox.hpp"
  #include "..//cpp//aabbox.cpp" 
  #include "oobbox.hpp"
  #include "..//cpp//oobbox.cpp" 
  #include "bsphere.hpp"
  #include "..//cpp//bsphere.cpp" 
  #include "camera.hpp" 
  #include "..//cpp//camera.cpp" 
  #include "light.hpp" 
  #include "..//cpp//light.cpp" 
  #include "vertex.hpp"
  #include "..//cpp//vertex.cpp" 
  #include "edge.hpp" 
  #include "..//cpp//edge.cpp" 
  #include "face.hpp" 
  #include "..//cpp//face.cpp" 
  #include "texture.hpp" 
  #include "..//cpp//texture.cpp" 
  #include "map.hpp" 
  #include "..//cpp//map.cpp" 
  #include "hdrimage.hpp" 
  #include "..//cpp//hdrimage.cpp" 
  #include "material.hpp" 
  #include "..//cpp//material.cpp" 
  #include "object.hpp"
  #include "..//cpp//object.cpp" 
  #include "mesh.hpp" // dorob dakedy optimize v tom zmysle akoze opak ku meshexplode, a ten obbox
  #include "..//cpp//mesh.cpp" 
  #include "beziercurve.hpp" // dorob do vsetkych kriviek a surfejsov matice array a tuna dorob interpolaciu cez body podla ulohu c.3, preco nemas dorobenu racionalnu bezierovu krivku
  #include "..//cpp//beziercurve.cpp" 
  #include "beziersurface.hpp" // neni dorobene to roam... a racionalna bezierova plocha
  #include "..//cpp//beziersurface.cpp" 
  #include "nurbscurve.hpp" // dorob ze dQ, ddQ ... vid. beziersurf, bezcuv...
  #include "..//cpp//nurbscurve.cpp" 
  #include "nurbssurface.hpp"  // dorob ze dQu, dQv ... vid beziersurface..., treba cele prezriet
  #include "..//cpp//nurbssurface.cpp" 
  #include "primitive.hpp" 
  #include "..//cpp//primitive.cpp" 
  #include "scene.hpp" // este napr scenebspherE..., ale to nevadi zatial, dorob dakedy
  #include "..//cpp//scene.cpp" 
  #include "ase.hpp"
  #include "..//cpp//ase.cpp" 
  //////////////// treba dorobit texttovy vystup do suboru!!! mal by si dorobit linE objekt, normaL objekt 
  





  CHAR ch, str[1024], str2[1024];
  BOOL b;
  boolarraY ba;
  long i, j, k, l;
  DWORD dw;
  dwordarraY dwa;
  valuE val, s, t;
  valuearraY vala;
  vectoR u, v, w;
  vectorarraY va;
  poinT pt;
  pointarraY pta;
  homogcoorD hc;
  homogcoordarraY hca;
  compleX cx;
  complexarraY cxa;
  quaternioN q;
  quaternionarraY qa;
  coloR c;
  colorarraY ca;
  complexioR cior;
  complexiorarraY ciora;
  raY r;
  rayarraY ra;
  planE pl;
  planearraY pla;
  matriX mat;
  matrixarraY mata;
  aabboX aabb;
  aabboxarraY aabba;
  oobboX oobb;
  oobboxarraY oobba;
  bspherE bsph;
  bspherearraY bspha;
  camerA C;
  cameraarraY Ca;
  lpcamerA lpC;
  lpcameraarraY lpCa;
  lighT L;
  lightarraY La;
  lplighT lpL;
  lplightarraY lpLa;
  verteX V;
  vertexarraY Va;
  lpverteX lpV;
  lpvertexarraY lpVa;
  edgE E;
  edgearraY Ea;
  lpedgE lpE;
  lpedgearraY lpEa;
  facE F;
  facearraY Fa;
  lpfacE lpF;
  lpfacearraY lpFa;
  maP map;
  maparraY mapa;
  lpmaP lpmap;
  lpmaparraY lpmapa;
  hdrimagE hdri;
  hdrimagearraY hdria;
  lphdrimagE lphdrI;
  lphdrimagearraY lphdria;
  materiaL mtrl;
  materialarraY mtrla;
  lpmateriaL lpmtrl;
  lpmaterialarraY lpmtrla;
  mesH M;
  mesharraY Ma;
  lpmesH lpM;
  lpmesharraY lpMa;
  cubicbeziercurvE cbc;
  cubicbeziercurvearraY cbca;
  lpcubicbeziercurvE lpcbc;
  lpcubicbeziercurvearraY lpcbca;
  rationalcubicbeziercurvE rcbc;
  rationalcubicbeziercurvearraY rcbca;
  lprationalcubicbeziercurvE lprcbc;
  lprationalcubicbeziercurvearraY lprcbca;
  beziercurvE bc;
  beziercurvearraY bca;
  lpbeziercurvE lpbc;
  lpbeziercurvearraY lpbca;
  bicubicbeziersurfacE bbs;
  bicubicbeziersurfacearraY bbsa;
  lpbicubicbeziersurfacE lpbbs;
  lpbicubicbeziersurfacearraY lpbbsa;
  rationalbicubicbeziersurfacE rbbs;
  rationalbicubicbeziersurfacearraY rbbsa;
  lprationalbicubicbeziersurfacE lprbbs;
  lprationalbicubicbeziersurfacearraY lprbbsa;
  beziersurfacE bs;
  beziersurfacearraY bsa;
  lpbeziersurfacE lpbs;
  lpbeziersurfacearraY lpbsa;
  nurbscurvE nc;
  nurbscurvearraY nca;
  lpnurbscurvE lpnc;
  lpnurbscurvearraY lpnca;
  nurbssurfacE ns;
  nurbssurfacearraY nsa;
  lpnurbssurfacE lpns;
  lpnurbssurfacearraY lpnsa; 
  bsptreenodE bsptn;
  lpbsptreenodE lpbsptn;
  lpbsptreenodearraY lpbsptna;
  scenE S;
  scenearraY Sa;
  lpscenE lpS;
  lpscenearraY lpSa;
  
  opengL ogl;
  