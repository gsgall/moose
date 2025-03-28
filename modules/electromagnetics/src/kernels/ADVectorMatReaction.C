//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ADVectorMatReaction.h"

registerMooseObject("ElectromagneticsApp", ADVectorMatReaction);

InputParameters
ADVectorMatReaction::validParams()
{
  InputParameters params = ADVectorKernel::validParams();
  params.addClassDescription("");
  // MooseEnum sign("positive=1 negative=-1", "positive");
  // params.addParam<MooseEnum>("sign", sign, "Sign of boundary term in weak form.");
  params.addParam<bool>("positive",
                        true,
                        "If the Sign of boundary term in weak form is positive, this is true, if "
                        "negative, it is false");
  params.addParam<MaterialPropertyName>(
      "mat_prop_coef",
      1.0,
      "User-supplied material property multiplier for the coupled force term.");
  return params;
}

ADVectorMatReaction::ADVectorMatReaction(const InputParameters & parameters)
  : ADVectorKernel(parameters),
    //_sign(getParam<MooseEnum>("sign")),
    _sign(getParam<bool>("positive") ? 1.0 : -1.0),
    _mat_prop(getADMaterialProperty<Real>("mat_prop_coef"))
{
}

ADReal
ADVectorMatReaction::computeQpResidual()
{
  return _sign * _mat_prop[_qp] * _u[_qp] * _test[_i][_qp];
}
