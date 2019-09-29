#ifndef GENSCATTERHIERARCHY_H
#define GENSCATTERHIERARCHY_H

#include "typelist.h"

namespace TL {

  template <typename TList, template<typename> class Unit>
  struct GenScatterHierarchy;

  template <typename head, typename tail, template<typename> class Unit>
  struct GenScatterHierarchy<typelist<head, tail>, Unit> :
    public GenScatterHierarchy<head, Unit>,
    public GenScatterHierarchy<tail, Unit> {
    using LeftBase = GenScatterHierarchy<head, Unit>;
    using RightBase = GenScatterHierarchy<tail, Unit>;
    template <typename T>
    struct Rebind {
      using Result = Unit<T>;
      };
  };

  template <typename atomicType, template<typename> class Unit>
  struct GenScatterHierarchy : public Unit<atomicType> {
    using LeftBase = Unit<atomicType>;
    template <typename T>
    struct Rebind {
      using Result = Unit<T>;
    };
  };

  template <template<typename> class Unit>
  struct GenScatterHierarchy<NullType, Unit> {};

  template <typename T>
  struct ObjectHolder {
    T value;
  };

  /*
    This implementation has bug with duplicates entries of type.
   */
  template <typename T, typename H>
  typename H::template Rebind<T>::Result&
  Field(H& obj)
  {
    return obj;
  }
}

#endif /* GENSCATTERHIERARCHY_H */
