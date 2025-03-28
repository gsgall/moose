//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ADVectorCoupledGrad.h"

registerMooseObject("ElectromagneticsApp", ADVectorCoupledGrad);

InputParameters
ADVectorCoupledGrad::validParams()
{
  InputParameters params = ADVectorKernel::validParams();
  params.addClassDescription("");
  // MooseEnum sign("positive=1 negative=-1", "positive");
  // params.addParam<MooseEnum>("sign", sign, "Sign of boundary term in weak form.");
  params.addCoupledVar("coupled_scalar", "The coupled scalar variable.");
  return params;
}

ADVectorCoupledGrad::ADVectorCoupledGrad(const InputParameters & parameters)
  : ADVectorKernel(parameters), _grad_coupled(adCoupledGradient("coupled_scalar"))
{
}

ADReal
ADVectorCoupledGrad::computeQpResidual()
{
  return _test[_i][_qp] * (_u[_qp] + _grad_coupled[_qp]);
}
