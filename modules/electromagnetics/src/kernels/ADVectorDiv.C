//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ADVectorDiv.h"
#include "Assembly.h"
#include "ElectromagneticEnums.h"
#include "ElectromagneticConstants.h"
#include "Function.h"
#include <complex>

registerMooseObject("MooseApp", ADVectorDiv);

InputParameters
ADVectorDiv::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addClassDescription("");
  params.addRequiredCoupledVar("vector_variable",
                               "The variable from which to compute the component");
  return params;
}

ADVectorDiv::ADVectorDiv(const InputParameters & parameters)
  : ADKernel(parameters), _coupled_grad_vec(adCoupledVectorGradient("vector_variable"))
{
}

ADReal
ADVectorDiv::computeQpResidual()
{
  return _test[_i][_qp] * -_coupled_grad_vec[_qp].tr();
}
