//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "MagneticTimeDerivTheta.h"

registerMooseObject("MooseApp", MagneticTimeDerivTheta);

InputParameters
MagneticTimeDerivTheta::validParams()
{
  InputParameters params = AuxKernel::validParams();
  params.addClassDescription(
      "");
  //params.addRequiredCoupledVar("Efield", "The efield to find the magnetic time derivative.");

  params.addRequiredCoupledVar("Efield_X", "The x-component of the E-field");
  params.addRequiredCoupledVar("Efield_Y", "The Y-component of the E-field");
  return params;
}

MagneticTimeDerivTheta::MagneticTimeDerivTheta(const InputParameters & parameters)
  : AuxKernel(parameters),
    //_grad_efield(coupledVectorGradient("Efield"))

    _efield_x_grad(coupledGradient("Efield_X")),
    _efield_y_grad(coupledGradient("Efield_Y"))
{
}

Real
MagneticTimeDerivTheta::computeValue()
{
  // Another note: libMesh implements grad(E) as dE_i/dr_j

  //return -(_grad_efield[_qp](0, 1) - _grad_efield[_qp](1, 0));
  return -(_efield_x_grad[_qp](1) - _efield_y_grad[_qp](0));
}
