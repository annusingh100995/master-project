#ifndef MOR_EX_SOMA_H_
#define MOR_EX_SOMA_H_

#include "biodynamo.h"
#include "biology-modules.h"
#include "core/substance_initializers.h"
#include "my-neurite.h"
#include "neuroscience/neuroscience.h"
#include <iostream>
#include <fstream>
#include "neurite_element.h"


/*
This function take the soma from the simulation and measures it's diameter, position and simulation pointer.

I am currently trying to figure out how I can get the neurite that is extended from the soma
*/


namespace bdm {

    // Function to record the morphology of soma
    //argument :  name of the file to be created
    template <typename TSimulation = Simulation<>>
    void WriteSoma(std::string file_name ) {
    auto* sim = TSimulation::GetActive();
    auto* rm = sim->GetResourceManager();
    auto soma = rm->template Get<experimental::neuroscience::NeuronSoma>();

    int n = rm->GetNumSimObjects();
    std::cout<< "Number of Simulation object :"<< n<< std::endl;


    ofstream Neural_Network_Morphology;
    Neural_Network_Morphology.open(file_name,ios::out | ios::app);

            // recording the diameter, position and simulation objct pointer
            auto diameter = soma->GetDiameter();
            auto position = soma->GetPosition();
            auto so_ptr = soma->GetSoPtr();

           //GetDaughters on soma 
            auto& daughters = soma->GetDaughters();
            auto&& daughter_dia = daughters[0]->GetDiameter();
            auto&& daughter_pos = daughters[0]->GetPosition();
            auto&& daughter_so_ptr = daughters[0]->GetSoPtr();

                // second neuriite
        
            auto&& daughter_dia_1 = daughters[1]->GetDiameter();
            auto&& daughter_pos_1 = daughters[1]->GetPosition();
            auto&& daughter_so_ptr_1 = daughters[1]->GetSoPtr();

                // THIRD neuriite
            
            auto&& daughter_dia_2 = daughters[2]->GetDiameter();
            auto&& daughter_pos_2 = daughters[2]->GetPosition();
            auto&& daughter_so_ptr_2 = daughters[2]->GetSoPtr();

                // NEURITE-1 DAUGHTER TEST
            auto&& neurite_1_daughter_1 = daughters[0]->GetDaughterLeft();
            auto&& neurite_1_daughter_1_dia = neurite_1_daughter_1->GetDiameter();
            auto&& neurite_1_daughter_1_pos = neurite_1_daughter_1->GetPosition();
            auto&& neurite_1_daughter_1_so_ptr = neurite_1_daughter_1->GetSoPtr();

            cout<< "neurite_1_daughter_1" << "DIAMETER" << neurite_1_daughter_1_dia << "POSITION" << neurite_1_daughter_1_pos[0] << "SO PTR" << neurite_1_daughter_1_so_ptr <<endl;
            
                // NEURITE-1 DAUGHTER -2 TEST

            auto&& neurite_1_daughter_2 = neurite_1_daughter_1->GetDaughterLeft();
            auto&& neurite_1_daughter_2_dia = neurite_1_daughter_2->GetDiameter();
            auto&& neurite_1_daughter_2_pos = neurite_1_daughter_2->GetPosition();
            auto&& neurite_1_daughter_2_so_ptr = neurite_1_daughter_2->GetSoPtr();
            cout<< "neurite_1_daughter_2    " << "DIAMETER      " << neurite_1_daughter_2_dia << "POSITION      " << neurite_1_daughter_2_pos[0] << "SO PTR     " << neurite_1_daughter_2_so_ptr <<endl;


             // NERUTIRE-1 DAUGHTER -3 TEST
            auto&& neurite_1_daughter_3 = neurite_1_daughter_2->GetDaughterLeft();
            auto&& neurite_1_daughter_3_dia = neurite_1_daughter_3->GetDiameter();
            auto&& neurite_1_daughter_3_pos = neurite_1_daughter_3->GetPosition();
            auto&& neurite_1_daughter_3_so_ptr = neurite_1_daughter_3->GetSoPtr();
            cout<< "neurite_1_daughter_3    " << "DIAMETER      " << neurite_1_daughter_3_dia << "POSITION      " << neurite_1_daughter_3_pos[0] << "SO PTR     " << neurite_1_daughter_3_so_ptr <<endl;
           
            // NEURITE -2 
                // NEURITE-2 DAUGHTER TEST
            auto&& neurite_2_daughter_1 = daughters[1]->GetDaughterLeft();
            auto&& neurite_2_daughter_1_dia = neurite_2_daughter_1->GetDiameter();
            auto&& neurite_2_daughter_1_pos = neurite_2_daughter_1->GetPosition();
            auto&& neurite_2_daughter_1_so_ptr = neurite_2_daughter_1->GetSoPtr();

            cout<< "neurite_2_daughter_1" << "DIAMETER" << neurite_2_daughter_1_dia << "POSITION" << neurite_2_daughter_1_pos[0] << "SO PTR" << neurite_2_daughter_1_so_ptr <<endl;
            
                // NEURITE-2 DAUGHTER -2 TEST

            auto&& neurite_2_daughter_2 = neurite_2_daughter_1->GetDaughterLeft();
            auto&& neurite_2_daughter_2_dia = neurite_2_daughter_2->GetDiameter();
            auto&& neurite_2_daughter_2_pos = neurite_2_daughter_2->GetPosition();
            auto&& neurite_2_daughter_2_so_ptr = neurite_2_daughter_2->GetSoPtr();
            cout<< "neurite_2_daughter_2    " << "DIAMETER      " << neurite_2_daughter_2_dia << "POSITION      " << neurite_2_daughter_2_pos[0] << "SO PTR     " << neurite_2_daughter_2_so_ptr <<endl;


             // NERUTIRE-2 DAUGHTER -3 TEST
            auto&& neurite_2_daughter_3 = neurite_2_daughter_2->GetDaughterLeft();
            auto&& neurite_2_daughter_3_dia = neurite_2_daughter_3->GetDiameter();
            auto&& neurite_2_daughter_3_pos = neurite_2_daughter_3->GetPosition();
            auto&& neurite_2_daughter_3_so_ptr = neurite_2_daughter_3->GetSoPtr();
            cout<< "neurite_2_daughter_3    " << "DIAMETER      " << neurite_2_daughter_3_dia << "POSITION      " << neurite_2_daughter_3_pos[0] << "SO PTR     " << neurite_2_daughter_3_so_ptr <<endl;

            // writing to console and the file
            cout<<"S.No:  "<<"  Diameter  "<<diameter<<"  Position  "<<position[0]<<" "<<position[1]<<" "<<position[2]<<"  SO Ptr  "<< so_ptr  <<endl;
            Neural_Network_Morphology<<"S.No: "<<" "<<"  Diameter: "<<diameter<<"  Position: "<<position[0]<<" "<<position[1]<<" "<<position[2]<<endl;

            // daughter morphologies
            cout<<"** NEURITE - 1"<< "  daughter_dia   "<<daughter_dia <<"  daughter_pos  "<<daughter_pos[0]<<"  daughter_so_ptr  "<<daughter_so_ptr<<endl;
            cout<<"** NEURITE - 2"<< "  daughter_dia   "<<daughter_dia_1 <<"  daughter_pos  "<<daughter_pos_1[0]<<"  daughter_so_ptr  "<<daughter_so_ptr_1<<endl;
            cout<<"** NEURITE - 3"<< "  daughter_dia   "<<daughter_dia_2 <<"  daughter_pos  "<<daughter_pos_2[0]<<"  daughter_so_ptr  "<<daughter_so_ptr_2<<endl;    
       
}

} //namespace bdm 

#endif  // MOR_EX_SOAM_H_


