
#ifndef NEURITE_ELEMENT_MORPHOLOGY_H_
#define NEURITE_ELEMENT_MORPHOLOGY_H_

#include "biodynamo.h"
#include "biology-modules.h"
#include "core/substance_initializers.h"
#include "my-neurite.h"
#include "neuroscience/neuroscience.h"
#include <iostream>
#include <fstream>
#include "neurite_element.h"
#include <iterator>


/*
This function take the soma from the simulation and measures it's diameter, position and simulation pointer.

And for each neurite, it measures its morphology unitl the neurite ends

I 
*/


namespace bdm {



    // Function to record the morphology of soma
    //argument :  name of the file to be created
    template <typename TSimulation = Simulation<>>
    void WriteNeuriteElementMorphology(std::string file_name ) {
    auto* sim = TSimulation::GetActive();
    auto* rm = sim->GetResourceManager();
    auto soma = rm->template Get<experimental::neuroscience::NeuronSoma>();

    int n = rm->GetNumSimObjects();
    std::cout<< "Number of Simulation object :"<< n<< std::endl;


    ofstream Neurite_Element_Morphology;
    Neurite_Element_Morphology.open(file_name,ios::out | ios::app);

            // recording the diameter, position and simulation objct pointer
           /*    auto diameter = soma->GetDiameter();
                 auto position = soma->GetPosition();
                 auto so_ptr = soma->GetSoPtr();
            */

           //Get the extended neurite elements on soma 
           // An array of all the neurites elements 
            auto&& extended_neurite_elements = soma->GetDaughters();


            // Number of neurite elements extended from the soma
            int number_of_extended_neurites = sizeof(extended_neurite_elements)/sizeof(extended_neurite_elements[0]);
            cout<<"Number of neurites :"<< number_of_extended_neurites<<endl;;


                // 
                for (int i = 0; i < number_of_extended_neurites; i++)
                {
                    auto&& current_neurite_element = extended_neurite_elements[i];

                    auto&& daughter = current_neurite_element->GetDaughterLeft();
                    cout<<"Diameter: "<< daughter->GetDiameter()<<endl;
                
                    while (current_neurite_element->GetDaughterLeft() != nullptr)
                    {
                         
                    
                        auto&& new_daughter = current_neurite_element->GetDaughterLeft();

                        auto&& daughter_dia = new_daughter->GetDiameter();
                        auto&& daughter_pos = new_daughter->GetPosition();
                        auto&& daughter_so_ptr = new_daughter->GetSoPtr();
                        Neurite_Element_Morphology <<"S.No.:     "<<"        Diameter:       "<<daughter_dia<<"      Position:       "<<daughter_pos[0]<<"   "<<daughter_pos[1]<<"   "<<daughter_pos[2]<<"       SO Ptr:     "<<daughter_so_ptr<<endl;

                        auto& current_neurite_element = new_daughter;
                       
                    } //while loop
                    
                    
                }// fro loop


}
 //templete
} //namespace bdm 

#endif  // NEURITE_ELEMENT_MORPHOLOGY_H_


