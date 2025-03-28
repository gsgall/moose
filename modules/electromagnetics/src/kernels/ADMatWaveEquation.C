//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ADMatWaveEquation.h"
#include "ElectromagneticEnums.h"
#include "ElectromagneticConstants.h"
#include "Function.h"
#include <complex>

registerMooseObject("ElectromagneticsApp", ADMatWaveEquation);

InputParameters
ADMatWaveEquation::validParams()
{
  InputParameters params = ADVectorKernel::validParams();
  params.addClassDescription(
      "Kernel to calculate the current source term in the Helmholtz wave equation.");
  // params.addParam<FunctionName>("function_coefficient",
  //                               1.0,
  //                               "Function coefficient multiplier for current source (normally "
  //                               "$\\omega$ or $\\omega \\cdot \\mu$).");
  // params.addRequiredParam<FunctionName>("source_real", "Current Source vector, real component");
  // params.addRequiredParam<FunctionName>("source_imag",
  //                                      "Current Source vector, imaginary component");
  params.addRequiredCoupledVar("E_real", "The real component of the E-field.");
  params.addRequiredCoupledVar("E_imag", "The imaginary component of the E-field.");

  params.addParam<MaterialPropertyName>(
      "wave_coef_real",
      1.0,
      "The real component of the coefficient for the Helmholtz wave equation.");
  params.addParam<MaterialPropertyName>(
      "wave_coef_imag",
      0.0,
      "The imaginary component of the coefficient for the Helmholtz wave equation.");

  MooseEnum component("real imaginary");
  params.addParam<MooseEnum>("component", component, "Component of field (real or imaginary).");
  return params;
}

ADMatWaveEquation::ADMatWaveEquation(const InputParameters & parameters)
  : ADVectorKernel(parameters),
    //_func(getFunction("function_coefficient")),
    //_source_real(getFunction("source_real")),
    //_source_imag(getFunction("source_imag")),

    _E_real(adCoupledVectorValue("E_real")),
    _E_imag(adCoupledVectorValue("E_imag")),

    _coef_real(getADMaterialProperty<Real>("wave_coef_real")),
    _coef_imag(getADMaterialProperty<Real>("wave_coef_imag")),

    _component(getParam<MooseEnum>("component"))
{
}

ADReal
ADMatWaveEquation::computeQpResidual()
{
  // std::complex<double> source_0(_source_real.vectorValue(_t, _q_point[_qp])(0),
  //                               _source_imag.vectorValue(_t, _q_point[_qp])(0));
  // std::complex<double> source_1(_source_real.vectorValue(_t, _q_point[_qp])(1),
  //                               _source_imag.vectorValue(_t, _q_point[_qp])(1));
  // std::complex<double> source_2(_source_real.vectorValue(_t, _q_point[_qp])(2),
  //                               _source_imag.vectorValue(_t, _q_point[_qp])(2));
  // VectorValue<std::complex<double>> source(source_0, source_1, source_2);

  // std::complex<double> source_0(_E_real[_qp](0), _E_imag[_qp](0));
  // std::complex<double> source_1(_E_real[_qp](1), _E_imag[_qp](1));
  // std::complex<double> source_2(_E_real[_qp](2), _E_imag[_qp](2));
  // ADRealVectorValue<std::complex<double>> source(source_0, source_1, source_2);

  // std::complex<double> res = EM::j * _func.value(_t, _q_point[_qp]) * source * _test[_i][_qp];

  // if (_component == EM::REAL)
  //   return res.real();
  // else
  //   return res.imag();

  if (_component == EM::REAL)
    return -_test[_i][_qp] * (_coef_real[_qp] * _E_real[_qp] - _coef_imag[_qp] * _E_imag[_qp]);
  else
    return -_test[_i][_qp] * (_coef_imag[_qp] * _E_real[_qp] + _coef_imag[_qp] * _E_real[_qp]);
}

// Real
// ADMatWaveEquation::computeQpJacobian()
//{
//   return 0.0;
// }
