#include <assert.h>
#include

//#include <vector>

// #include "adr-test.h"

template<typename _ZE_T_>
class TRUSTArray
{
public:
  inline _ZE_T_& operator()(int i) { _ZE_T_ v_; return v_;};
  inline const _ZE_T_& operator()(int i) const {  _ZE_T_ v_; return v_; }
private:
 };

using ArrOfDouble = TRUSTArray<double>;

const ArrOfDouble& func()
{
  const ArrOfDouble a;
  return a;
}

void func_sub()
{

}

template<typename Type_Double>
void t_func()
{
  Type_Double source;
  source(45);
}

void toto()
{
  ArrOfDouble aaa;
  aaa(42);

  func()(64);

  t_func<ArrOfDouble>();

  assert(aaa(43) == func()(36));
}

