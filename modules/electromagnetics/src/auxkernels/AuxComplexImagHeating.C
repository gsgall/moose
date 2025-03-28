//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "AuxComplexImagHeating.h"

registerMooseObject("MooseApp", AuxComplexImagHeating);

InputParameters
AuxComplexImagHeating::validParams()
{
  InputParameters params = AuxKernel::validParams();
  params.addClassDescription("");
  params.addRequiredCoupledVar("E_real", "The real component of the E-field.");
  params.addRequiredCoupledVar("E_imag", "The imaginary component of the E-field.");
  params.addRequiredParam<std::string>("conductivity", "The name of the plasma conductivity.");
  return params;
}

AuxComplexImagHeating::AuxComplexImagHeating(const InputParameters & parameters)
  : AuxKernel(parameters),
    _E_real(coupledVectorValue("E_real")),
    _E_imag(coupledVectorValue("E_imag")),
    _cond(getMaterialProperty<Real>(getParam<std::string>("conductivity")))
{
}

Real
AuxComplexImagHeating::computeValue()
{
  return 0.5 * _cond[_qp] * (2.0 * _E_real[_qp] * _E_imag[_qp]);
}
