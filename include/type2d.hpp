#ifndef BTTP_TYPE2D_HPP
#define BTTP_TYPE2D_HPP

#include <ostream>

#include "types.hpp"

template<typename T>
class type2d {
public:
  T a, b;

  type2d() { }
  type2d(T A,T B)
    : a(A), b(B) { }

  template<typename T2>
  type2d(const T2& t)
    : a(t.a), b(t.b) { }

  template<typename T2>
  type2d<T>& operator=(const type2d<T2>& t2) {
    a = t2.a;
    b = t2.b;
    return *this;
  }
};

#define _BT_T2D_B_OPERATOR(opr)						       \
  template<typename T1, typename T2>					       \
  const type2d<T1> operator opr (const type2d<T1>& t1, const type2d<T2>& t2) { \
    return type2d<T1>(t1.a opr t2.a, t1.b opr t2.b);	 	 	       \
  }

_BT_T2D_B_OPERATOR(+);
_BT_T2D_B_OPERATOR(-);
_BT_T2D_B_OPERATOR(*);
_BT_T2D_B_OPERATOR(/);
_BT_T2D_B_OPERATOR(%);

#undef _BT_T2D_B_OPERATOR

#define _BT_T2D_S_OPERATOR(opr)						\
  template<typename T1, typename T2>					\
  const type2d<T1> operator opr (const type2d<T1>& t1, const T2& t2) {	\
    return type2d<T1>(t1.a opr t2, t1.b opr t2);			\
  }

_BT_T2D_S_OPERATOR(+);
_BT_T2D_S_OPERATOR(-);
_BT_T2D_S_OPERATOR(*);
_BT_T2D_S_OPERATOR(/);
_BT_T2D_S_OPERATOR(%);

#undef _BT_T2D_S_OPERATOR

#define _BT_T2D_A_OPERATOR(opr,epr)				    \
  template<typename T1, typename T2>				    \
  type2d<T1>& operator epr (type2d<T1>& t1, const type2d<T2>& t2) { \
    return t1 = (t1 opr t2);					    \
  }

_BT_T2D_A_OPERATOR(+,+=);
_BT_T2D_A_OPERATOR(-,-=);
_BT_T2D_A_OPERATOR(*,*=);
_BT_T2D_A_OPERATOR(/,/=);
_BT_T2D_A_OPERATOR(%,%=);

#undef _BT_T2D_A_OPERATOR

#define _BT_T2D_AS_OPERATOR(opr,epr)				    \
  template<typename T1, typename T2>				    \
  type2d<T1>& operator epr (type2d<T1>& t1, const T2& t2) {	    \
    return t1 = (t1 opr t2);					    \
  }

_BT_T2D_AS_OPERATOR(+,+=);
_BT_T2D_AS_OPERATOR(-,-=);
_BT_T2D_AS_OPERATOR(*,*=);
_BT_T2D_AS_OPERATOR(/,/=);
_BT_T2D_AS_OPERATOR(%,%=);

#undef _BT_T2D_AS_OPERATOR

template<typename T1, typename T2>
bool operator==(type2d<T1>& t1, const type2d<T2>& t2) {
  return (t1.a == t2.a && t1.b == t2.b);
}

template<typename T1, typename T2>
bool operator!=(type2d<T1>& t1, const type2d<T2>& t2) {
  return !(t1==t2);
}

template<typename T>
std::ostream& operator<<(std::ostream& o, const type2d<T>& t) {
  o<<"("<<t.a<<","<<t.b<<")";
  return o;
}

using uint32_2d = type2d<uint32>;
using uint16_2d = type2d<uint16>;
using byte2d    = type2d<byte>;

using int32_2d  = type2d<int32>;
using int16_2d  = type2d<int16>;
using sbyte2d   = type2d<sbyte>;

using int2d     = type2d<int>;
using uint2d    = type2d<unsigned int>;

using short2d   = type2d<short>;
using ushort2d  = type2d<unsigned short>;

using long2d    = type2d<long>;
using ulong2d   = type2d<unsigned long>;

using float2d   = type2d<float>;
using double2d  = type2d<double>;

using size = uint32_2d;

#endif
