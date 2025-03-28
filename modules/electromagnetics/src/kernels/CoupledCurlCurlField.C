//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "CoupledCurlCurlField.h"
#include "Assembly.h"

registerMooseObject("ElectromagneticsApp", CoupledCurlCurlField);

InputParameters
CoupledCurlCurlField::validParams()
{
  InputParameters params = VectorKernel::validParams();
  params.addClassDescription("Weak form term corresponding to $\\nabla \\times (a \\nabla \\times "
                             "\\vec{E})$.");
  params.addParam<Real>("coeff", 1.0, "Weak form coefficient (default = 1.0).");
  params.addRequiredCoupledVar("vector_variable",
                               "The variable from which to compute the component");
  return params;
}

CoupledCurlCurlField::CoupledCurlCurlField(const InputParameters & parameters)
  : VectorKernel(parameters),
    _curl_test(_var.curlPhi()),
    _curl_phi(_assembly.curlPhi(_var)),
    _variable_curl(coupledCurl("vector_variable")),
    _coeff(getParam<Real>("coeff"))
{
}

Real
CoupledCurlCurlField::computeQpResidual()
{
  return _coeff * _variable_curl[_qp] * _curl_test[_i][_qp];
}

// Real
// CoupledCurlCurlField::computeQpJacobian()
//{
//   return _coeff * _curl_phi[_j][_qp] * _curl_test[_i][_qp];
// }
