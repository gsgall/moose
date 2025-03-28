//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "ADVectorKernel.h"
#include "Function.h"

/**
 *  Kernel representing the contribution of the PDE term $fu$, where $f$ is a function
 *  coefficient and $u$ is a vector variable.
 */
class ADVectorMatReaction : public ADVectorKernel
{
public:
  static InputParameters validParams();

  ADVectorMatReaction(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

private:
  // MooseEnum signifying sign of weak form contribution
  // const MooseEnum _sign;
  const Real _sign;

  // AD Material Property
  const ADMaterialProperty<Real> & _mat_prop;
};
