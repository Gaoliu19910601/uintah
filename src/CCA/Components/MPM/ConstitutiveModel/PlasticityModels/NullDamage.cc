/*
 * The MIT License
 *
 * Copyright (c) 1997-2016 The University of Utah
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */


#include "NullDamage.h"

using namespace Uintah;
static DebugStream dbg("DamageModel", false);

NullDamage::NullDamage()
{
} 
//______________________________________________________________________
//         
NullDamage::NullDamage(ProblemSpecP& )
{
  Algorithm = DamageAlgo::none;
} 
         
NullDamage::NullDamage(const NullDamage* )
{
} 
//______________________________________________________________________
//         
NullDamage::~NullDamage()
{
}
//______________________________________________________________________
//
void NullDamage::outputProblemSpec(ProblemSpecP& ps)
{
  ProblemSpecP damage_ps = ps->appendChild("damage_model");
  damage_ps->setAttribute("type","null");
}

//______________________________________________________________________
//         
inline double 
NullDamage::initialize()
{
  return 0.0;
}
//______________________________________________________________________
//
inline bool
NullDamage:: hasFailed(double )
{
  return false;
}
//______________________________________________________________________
//    
double 
NullDamage::computeScalarDamage(const double& ,
                                const Matrix3& ,
                                const double& ,
                                const double& ,
                                const MPMMaterial*,
                                const double& ,
                                const double& )
{
  return 0.0;
}
 
//______________________________________________________________________
//
void
NullDamage::addComputesAndRequires(Task* task,
                                   const MPMMaterial* matl)
{
  printTask( dbg, "    NullDamage::addComputesAndRequires" );
  Ghost::GhostType  gnone = Ghost::None;
  const MaterialSubset* matls = matl->thisMaterial();

  task->requires( Task::OldDW, d_lb->pLocalizedMPMLabel,  matls, gnone);
  task->computes( d_lb->pLocalizedMPMLabel_preReloc,      matls);
}
//______________________________________________________________________
//
void
NullDamage::computeSomething( ParticleSubset  * pset,
                              const int       & ,
                              const Patch     * patch,
                              DataWarehouse   * old_dw,
                              DataWarehouse   * new_dw )
{
  printTask( patch, dbg, "    NullDamage::computeSomething" );

  constParticleVariable<int>     pLocalized;
  ParticleVariable<int>          pLocalized_new;
  
  old_dw->get(pLocalized, d_lb->pLocalizedMPMLabel,         pset);
 
  new_dw->allocateAndPut(pLocalized_new,
                         d_lb->pLocalizedMPMLabel_preReloc, pset);
    // Copy to new dw
  pLocalized_new.copyData( pLocalized );
}
