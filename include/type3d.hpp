#ifndef BTTP_TYPE3D_HPP
#define BTTP_TYPE3D_HPP

#include "type2d.hpp"

template<typename T>
class type3d {
public:
  T a, b, c;

  type3d() { }
  type3d(T A, T B, T C)
    : a(A), b(B), c(C) { }

  template<typename T2>
  type3d(const type2d<T2>& ab, T C)
    : a(ab.a), b(ab.b), c(C) { }

  template<typename T2>
  type3d(T A, const type2d<T2>& bc)
    : a(A), b(bc.a), c(bc.b) { }
  
  template<typename T2>
  type3d(const T2& t)
    : a(t.a), b(t.b), c(t.c) { }

  template<typename T2>
  type3d<T>& operator=(const type3d<T2>& t2) {
    a = t2.a;
    b = t2.b;
    c = t2.c;
    return *this;
  }
};

#define _BT_T3D_B_OPERATOR(opr)						       \
  template<typename T1, typename T2>					       \
  const type3d<T1> operator opr (const type3d<T1>& t1, const type3d<T2>& t2) { \
    return type3d<T1>(t1.a opr t2.a, t1.b opr t2.b, t1.c opr t2.c);	       \
  }

_BT_T3D_B_OPERATOR(+);
_BT_T3D_B_OPERATOR(-);
_BT_T3D_B_OPERATOR(*);
_BT_T3D_B_OPERATOR(/);
_BT_T3D_B_OPERATOR(%);

#undef _BT_T3D_B_OPERATOR

#define _BT_T3D_S_OPERATOR(opr)					       \
  template<typename T1, typename T2>				       \
  const type3d<T1> operator opr (const type3d<T1>& t1, const T2& t2) { \
    return type3d<T1>(t1.a opr t2, t1.b opr t2, t1.c opr t2);	       \
  }

_BT_T3D_S_OPERATOR(+);
_BT_T3D_S_OPERATOR(-);
_BT_T3D_S_OPERATOR(*);
_BT_T3D_S_OPERATOR(/);
_BT_T3D_S_OPERATOR(%);

#undef _BT_T3D_S_OPERATOR

#define _BT_T3D_A_OPERATOR(opr,epr)				    \
  template<typename T1, typename T2>				    \
  type3d<T1>& operator epr (type3d<T1>& t1, const type3d<T2>& t2) { \
    return t1 = (t1 opr t2);					    \
  }

_BT_T3D_A_OPERATOR(+,+=);
_BT_T3D_A_OPERATOR(-,-=);
_BT_T3D_A_OPERATOR(*,*=);
_BT_T3D_A_OPERATOR(/,/=);
_BT_T3D_A_OPERATOR(%,%=);

#undef _BT_T3D_A_OPERATOR

#define _BT_T3D_AS_OPERATOR(opr,epr)   			    \
  template<typename T1, typename T2>   			    \
  type3d<T1>& operator epr (type3d<T1>& t1, const T2& t2) { \
    return t1 = (t1 opr t2);		       		    \
  }

_BT_T3D_AS_OPERATOR(+,+=);
_BT_T3D_AS_OPERATOR(-,-=);
_BT_T3D_AS_OPERATOR(*,*=);
_BT_T3D_AS_OPERATOR(/,/=);
_BT_T3D_AS_OPERATOR(%,%=);

#undef _BT_T3D_AS_OPERATOR

template<typename T1, typename T2>
bool operator==(type3d<T1>& t1, const type3d<T2>& t2) {
  return (t1.a == t2.a && t1.b == t2.b && t1.c == t2.c);
}

template<typename T1, typename T2>
bool operator!=(type3d<T1>& t1, const type3d<T2> t2) {
  return !(t1 == t2);
}

template<typename T>
std::ostream& operator<<(std::ostream& o, const type3d<T>& t) {
  o<<"("<<t.a<<","<<t.b<<","<<t.c<<")";
  return o;
}

#endif
