//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "AuxKernel.h"

/**
 * Function auxiliary value
 */
class MagneticTimeDerivTheta : public AuxKernel
{
public:
  static InputParameters validParams();

  /**
   * Factory constructor, takes parameters so that all derived classes can be built using the same
   * constructor.
   */
  MagneticTimeDerivTheta(const InputParameters & parameters);

protected:
  virtual Real computeValue() override;

  //const VectorVariableGradient & _grad_efield;

  const VariableGradient & _efield_x_grad;
  const VariableGradient & _efield_y_grad;
};
