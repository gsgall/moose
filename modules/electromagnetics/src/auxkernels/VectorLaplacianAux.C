//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "VectorLaplacianAux.h"

registerMooseObject("MooseApp", VectorLaplacianAux);

InputParameters
VectorLaplacianAux::validParams()
{
  InputParameters params = VectorAuxKernel::validParams();
  params.addClassDescription("");
  params.addRequiredCoupledVar("u", "x-component");
  params.addCoupledVar("v", 0, "y-component"); // only required in 2D and 3D
  params.addCoupledVar("w", 0, "z-component"); // only required in 3D
  return params;
}

VectorLaplacianAux::VectorLaplacianAux(const InputParameters & parameters)
  : VectorAuxKernel(parameters),
    _second_u_vel(coupledSecond("u")),
    _second_v_vel(coupledSecond("v")),
    _second_w_vel(coupledSecond("w"))
{
}

RealVectorValue
VectorLaplacianAux::computeValue()
{
  return RealVectorValue(_second_u_vel[_qp].tr(), _second_v_vel[_qp].tr(), _second_w_vel[_qp].tr());
}
