//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

/*
#include "MagneticTimeDerivVector.h"

registerMooseObject("MooseApp", MagneticTimeDerivVector);

InputParameters
MagneticTimeDerivVector::validParams()
{
  InputParameters params = VectorAuxKernel::validParams();
  params.addClassDescription(
      "");
  params.addRequiredCoupledVar("Efield", "The efield to find the magnetic time derivative.");
  return params;
}

MagneticTimeDerivVector::MagneticTimeDerivVector(const InputParameters & parameters)
  : AuxKernel(parameters),
    //_efield_cul(coupledCurl("Efield"))
    _variable_value(coupledVectorValue("Efield"))
{
}

Real
MagneticTimeDerivVector::computeValue()
{
  //return -_efield_cul[_qp](0);
  return _variable_value[_qp](0);
}
*/

#include "MagneticTimeDerivVector.h"

registerMooseObject("MooseApp", MagneticTimeDerivVector);

InputParameters
MagneticTimeDerivVector::validParams()
{
  InputParameters params = AuxKernel::validParams();
  params.addClassDescription("Creates a field consisting of the magnitude of a "
                             "coupled vector variable.");
  params.addRequiredCoupledVar("vector_variable",
                               "The variable from which to compute the component");
  return params;
}

MagneticTimeDerivVector::MagneticTimeDerivVector(const InputParameters & parameters)
  : AuxKernel(parameters),
    //_variable_value(coupledVectorValue("vector_variable"))
    _variable_curl(coupledCurl("vector_variable"))
{
}

Real
MagneticTimeDerivVector::computeValue()
{
  // return _variable_value[_qp](0);
  return -_variable_curl[_qp](2);
}
