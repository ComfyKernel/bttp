#ifndef BTTP_TYPE2D_HPP
#define BTTP_TYPE2D_HPP

#include "types.hpp"

template<typename T>
class type2d {
public:
  T a, b;

  type2d() { }
  type2d(T A,T B) : a(A), b(B) { }
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

template<typename T>
std::ostream& operator<<(std::ostream& o, const type2d<T>& t) {
  o<<"("<<t.a<<","<<t.b<<")";
  return o;
}
#endif
