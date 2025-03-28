//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "AuxVectorCoupleGrad.h"

registerMooseObject("MooseApp", AuxVectorCoupleGrad);

InputParameters
AuxVectorCoupleGrad::validParams()
{
  InputParameters params = VectorAuxKernel::validParams();
  params.addClassDescription("");
  params.addCoupledVar("coupled_scalar", "The coupled scalar variable.");
  return params;
}

AuxVectorCoupleGrad::AuxVectorCoupleGrad(const InputParameters & parameters)
  : VectorAuxKernel(parameters), _grad_coupled(coupledGradient("coupled_scalar"))
{
}

RealVectorValue
AuxVectorCoupleGrad::computeValue()
{
  return _grad_coupled[_qp];
}
