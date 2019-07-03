// -----------------------------------------------------------------------------
//
// Copyright (C) The BioDynaMo Project.
// All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
//
// See the LICENSE file distributed with this work for details.
// See the NOTICE file distributed with this work for additional information
// regarding copyright ownership.
//
// -----------------------------------------------------------------------------
#ifndef BIOLOGY_MODULES_H_
#define BIOLOGY_MODULES_H_

#include "core/biology_module/biology_module.h"
#include "core/resource_manager.h"
#include "my-neurite.h"

namespace bdm {

enum Substances { kSubstanceApical };

struct NeuriteElongationBM : public BaseBiologyModule {
  NeuriteElongationBM() : BaseBiologyModule(gAllEventIds) {}

  //NeuriteElongationBM() : BaseBiologyModule(gAllEventIds) {}
  /// Default event constructor
  template <typename TEvent, typename TBm>
  NeuriteElongationBM(const TEvent& event, TBm* other, uint64_t new_oid = 0)
      : BaseBiologyModule(event, other, new_oid) {}

  // TODO: don't copy BM when split (elongate)

  template <typename T, typename TSimulation = Simulation<>>
  void Run(T* dendrite) {
    auto* sim = TSimulation::GetActive();
    auto* random = sim->GetRandom();
   
    if (dendrite->IsTerminal() && dendrite->GetDiameter() > 0.75) {
     
      double randomness_weight = 0.3;
      double old_direction_weight = 3;

      auto random_axis = random->template UniformArray<3>(-1, 1);

      auto old_direction =
          Math::ScalarMult(old_direction_weight, dendrite->GetSpringAxis());
      
      auto random_direction = Math::ScalarMult(randomness_weight, random_axis);

      auto new_step_direction = Math::Add(old_direction, random_direction);

      dendrite->ElongateTerminalEnd(25, new_step_direction);
      dendrite->SetDiameter(dendrite->GetDiameter() - 0.001);

        if (random->Uniform() < 0.008) {
        dendrite->SetDiameter(dendrite->GetDiameter() - 0.001);
        dendrite->Bifurcate();
       } // bifurcating codition
      

      }// if daimeter

    } // run 
  private:
  
  ClassDefNV(NeuriteElongationBM, 1);  // end if diameter
  };  // end run
  

}  // namespace bdm

#endif  // BIOLOGY_MODULES_H_

