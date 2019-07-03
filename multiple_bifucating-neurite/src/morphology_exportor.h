#ifndef MORPHOLOGY_EXPORTER_H_
#define MORPHOLOGY_EXPORTER_H_

#include "biodynamo.h"
#include "biology-modules.h"
#include "core/substance_initializers.h"
#include "my-neurite.h"
#include "neuroscience/neuroscience.h"
#include <iostream>
#include <fstream>
#include "neurite_element.h"


namespace bdm {

    // Function to write the morphology of neurite elements
    // Argument:  name of the file to be created
    template <typename TSimulation = Simulation<>>
    void WriteMorphology(std::string file_name ) {
    auto* sim = TSimulation::GetActive();
    auto* rm = sim->GetResourceManager();
  //  auto my_neurites = rm->template Get<MyNeurite>();
    
    int n = rm->GetNumSimObjects();
    
    //auto ptr = rm->GetSoPtr();
    
    std::cout<< "Number of Simulation object :"<< n<< std::endl;

    ofstream Neural_Network_Morphology_neurite;
   	Neural_Network_Morphology_neurite.open(file_name,ios::out | ios::app);

    //Get the position and diameter
    rm->ApplyOnAllElements([&](auto&& so, const SoHandle&) {
    auto& pos = so.GetPosition();
    auto type = so.GetDiameter();
    auto ne_soptr = so.GetSoPtr();

    //writing on the console and the file
    cout<<"Position:    "<<pos[0]<<"    "<<pos[1]<<"    "<<pos[2]<<"    Diameter:   "<<type<<"    "<<"    SO PTR:   "<< ne_soptr <<endl;
	Neural_Network_Morphology_neurite<<" "<<"  Diameter: "<<type<<"  Position: "<<pos[0]<<" "<<pos[1]<<" "<<pos[2]<<"  "<<"  SO PTR:   "<< ne_soptr <<endl;
    
  });
                  
}

} //namespace bdm 

#endif  // MORPHOLOGY_EXPORTER_H_


