//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "DivVector.h"

registerMooseObject("MooseApp", DivVector);

InputParameters
DivVector::validParams()
{
  InputParameters params = AuxKernel::validParams();
  params.addClassDescription("");
  params.addRequiredCoupledVar("vector_variable",
                               "The variable from which to compute the component");
  return params;
}

DivVector::DivVector(const InputParameters & parameters)
  : AuxKernel(parameters), _grad_vec(coupledVectorGradient("vector_variable"))
{
}

Real
DivVector::computeValue()
{
  return _grad_vec[_qp].tr();
}
