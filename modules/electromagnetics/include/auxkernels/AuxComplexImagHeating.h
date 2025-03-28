//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

/*
#pragma once

#include "AuxKernel.h"

class AuxComplexImagHeating : public AuxKernel
{
public:
  static InputParameters validParams();

  AuxComplexImagHeating(const InputParameters & parameters);

protected:
  virtual Real computeValue() override;

  //const VectorVariableCurl & _efield_cul;
  const VectorVariableValue & _variable_value;
};
*/

#pragma once

#include "AuxKernel.h"

class AuxComplexImagHeating : public AuxKernel
{
public:
  static InputParameters validParams();

  AuxComplexImagHeating(const InputParameters & parameters);

protected:
  virtual Real computeValue() override;

private:
  const VectorVariableValue & _E_real;
  const VectorVariableValue & _E_imag;
  const MaterialProperty<Real> & _cond;
};
