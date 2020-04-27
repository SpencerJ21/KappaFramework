#pragma once

#include "abstractInput.hpp"

namespace kappa {

template <typename T>
class AbstractComputationalInput : public AbstractInput<T> {
public:
  virtual T step() = 0;
};

}
