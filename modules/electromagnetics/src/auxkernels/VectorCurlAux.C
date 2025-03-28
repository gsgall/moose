//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "VectorCurlAux.h"

registerMooseObject("MooseApp", VectorCurlAux);

InputParameters
VectorCurlAux::validParams()
{
  InputParameters params = VectorAuxKernel::validParams();
  params.addClassDescription("");
  params.addRequiredCoupledVar("vector_variable",
                               "The variable from which to compute the component");
  return params;
}

VectorCurlAux::VectorCurlAux(const InputParameters & parameters)
  : VectorAuxKernel(parameters), _variable_curl(coupledCurl("vector_variable"))
{
}

RealVectorValue
VectorCurlAux::computeValue()
{
  return _variable_curl[_qp];
}
