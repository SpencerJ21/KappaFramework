#pragma once

#include "kappa/output/abstractOutput.hpp"
#include <initializer_list>
#include <array>
#include <memory>


namespace kappa {

template<typename T, std::size_t N>
class ArrayDistributor : public AbstractOutput<std::array<T,N>> {
public:

  /**
   * Splits an array of control signals to be handled individually
   *
   * @param ioutput outputs for data
   */
  ArrayDistributor(std::initializer_list<std::shared_ptr<AbstractOutput<T>>> ioutput) {
    if (ioutput.size() != N) throw std::invalid_argument("Invalid number of args in kappa::ArrayDistributor");

    std::copy(ioutput.begin(), ioutput.end(), output.begin());
  }

  /**
   * Sets each element within itarget to its respective output
   *
   * @param itarget targets
   */
  virtual void set(const std::array<T,N> &itarget) override {
    for(std::size_t i = 0; i < N; i++) {
      output[i]->set(itarget[i]);
    }
  }

  /**
   * Send a stop command to each output
   * eg. idle the motor, as opposed to trying to hold vel = 0
   */
  virtual void stop() override {
    for(std::size_t i = 0; i < N; i++) {
      output[i]->stop();
    }
  }

  /**
   * Gets outputs
   *
   * @return outputs
   */
  std::array<std::shared_ptr<AbstractOutput<T>>,N> getOutput() const {
    return output;
  };

protected:
  std::array<std::shared_ptr<AbstractOutput<T>>,N> output;
};

extern template class ArrayDistributor<double, 2>;
extern template class ArrayDistributor<double, 4>;

}
