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
#ifndef MULTIPLE_NEURON_H_
#define MULTIPLE_NEURON_H_

#include "biodynamo.h"
#include "biology-modules.h"
#include "core/substance_initializers.h"
#include "my-neurite.h"
#include "neuroscience/neuroscience.h"
#include "Mor_ex_soma.h"
#include "morphology_exportor.h"
//#include "neurite_element_morphologies.h"
#include "record_morphology_recursive.h"

namespace bdm {

// Define compile time parameter
BDM_CTPARAM(experimental::neuroscience) {
  BDM_CTPARAM_HEADER(experimental::neuroscience);

  using NeuriteElement = MyNeurite;

  using SimObjectTypes =
      CTList<experimental::neuroscience::NeuronSoma, bdm::MyNeurite>;

  BDM_CTPARAM_FOR(bdm, MyNeurite) {
    using BiologyModules = CTList<NeuriteElongationBM>;
  };
};

//Building the neuron
struct NeuronBuilder {
  void operator()(const std::array<double, 3>& position) {
    auto* rm = Simulation<>::GetActive()->GetResourceManager();

    experimental::neuroscience::NeuronSoma soma(position);
    soma.SetDiameter(10);
    auto soma_soptr = soma.GetSoPtr();
    rm->push_back(soma);

    auto&& dendrite_apical = soma_soptr->ExtendNewNeurite({0, 0, 1});
    dendrite_apical->AddBiologyModule(NeuriteElongationBM());

    auto&& dendrite_apical1 = soma_soptr->ExtendNewNeurite({1, 1, 1});
    dendrite_apical1->AddBiologyModule(NeuriteElongationBM());
    
/* 
    auto&& dendrite_apical1 = soma_soptr->ExtendNewNeurite({0, 1, 1});
    dendrite_apical1->AddBiologyModule(NeuriteElongationBM());
    dendrite_apical1->SetCanBranch(true);

    auto&& dendrite_apical2 = soma_soptr->ExtendNewNeurite({1, 1, 1});
    dendrite_apical2->AddBiologyModule(NeuriteElongationBM());
    dendrite_apical2->SetCanBranch(true);
  */
  }
};

inline int Simulate(int argc, const char** argv) {
  Simulation<> simulation(argc, argv);

#pragma omp parallel
  simulation.GetRandom()->SetSeed(8794);
  simulation.GetExecutionContext()->DisableNeighborGuard();

  NeuronBuilder builder;
  builder({0, 0, 0});
  

  //simulate, write the soma and beuron morphologies
  
  simulation.GetScheduler()->Simulate(500);
  //WriteSoma("SOMA_NM_TEST_12-06-2019");
  //WriteMorphology("NEURITE_TEST_12-06-2019");
  //WriteNeuriteElementMorphology("Test_neeurite_element_file");
  WriteNeuriteElementMorphologyRecursive();

  std::cout << "Simulation completed successfully!" << std::endl;
  return 0;
}

}  // namespace bdm

#endif  // MULTIPLE_NEURON_H_
