#include "kappa/output/impl/twoAxisChassis.hpp"
#include <math.h>

namespace kappa {

TwoAxisChassis::TwoAxisChassis(std::shared_ptr<AbstractOutput<std::array<double,2>>> ichassis):
  chassis(ichassis), linearScalar(1), angularScalar(1){}

TwoAxisChassis::TwoAxisChassis(double iwheelDiameter, double ichassisWidth, std::shared_ptr<AbstractOutput<std::array<double,2>>> ichassis):
  chassis(ichassis), linearScalar((60.0 / M_PI) / iwheelDiameter), angularScalar((30.0 / M_PI) * (ichassisWidth / iwheelDiameter)) {}

void TwoAxisChassis::set(const std::tuple<double,double> &iTarget) {
  double linearTarget   = linearScalar  * std::get<0>(iTarget);
  double rotationTarget = angularScalar * std::get<1>(iTarget);

  chassis->set({linearTarget - rotationTarget,
                linearTarget + rotationTarget});
}

void TwoAxisChassis::stop(){
  chassis->stop();
}

std::shared_ptr<AbstractOutput<std::array<double,2>>> TwoAxisChassis::getOutput() const {
  return chassis;
}

}
