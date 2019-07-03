

#ifndef NEURITE_ELEMENT_RECURSIVE_H_
#define NEURITE_ELEMENT_RECURSIVE_H_

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

    //  Function to record the dimension of a neurite exteneded from the soma, 
    //It keeps on recording the dimesnion until it reaches the terminal end of the neurite

    template <typename T>
    void record_morphology(const T& neurite_element){

             ofstream Neurite_Element_Morphology;
            Neurite_Element_Morphology.open("Neurite_Morphology.csv",ios::out | ios::app);
       
       
        if (neurite_element->GetDaughterRight() != nullptr)
        {   
        
            auto&& daughter_dia = neurite_element->GetDiameter();
            auto&& daughter_pos = neurite_element->GetPosition();
            auto&& daughter_so_ptr = neurite_element->GetSoPtr();
            cout<<"Diameter:"<<"\t"<<daughter_dia<<"\t"<<"Position:"<<"\t"<<daughter_pos[0]<<"\t"<<daughter_pos[1]<<"\t"<<daughter_pos[2]<<"\t"<<"SO Ptr:"<<"\t"<<daughter_so_ptr<<"\t"<<"Right"<<endl;
            Neurite_Element_Morphology <<"Diameter:"<<"\t"<<daughter_dia<<"\t"<<"Position:"<<"\t"<<daughter_pos[0]<<"\t"<<daughter_pos[1]<<"\t"<<daughter_pos[2]<<"\t"<<"SO Ptr:"<<"\t"<<daughter_so_ptr<<"\t"<<"Right"<<endl;
            
           /*  if(neurite_element->GetDaughterRight() != nullptr) {
                return (record_morphology((neurite_element->GetDaughterRight())));
            } // return right daughter
            else if (neurite_element->GetDaughterLeft() != nullptr){
                return (record_morphology((neurite_element->GetDaughterLeft())));
            }  // return left daughter
            */

            record_morphology(neurite_element->GetDaughterRight()) ;

        } // if right daughter != null ptr
        
        if (neurite_element->GetDaughterLeft() != nullptr)
        {   
        
            auto&& daughter_dia = neurite_element->GetDiameter();
            auto&& daughter_pos = neurite_element->GetPosition();
            auto&& daughter_so_ptr = neurite_element->GetSoPtr();
            cout<<"Diameter:"<<"\t"<<daughter_dia<<"\t"<<"Position:"<<"\t"<<daughter_pos[0]<<"\t"<<daughter_pos[1]<<"\t"<<daughter_pos[2]<<"\t"<<"SO Ptr:"<<"\t"<<daughter_so_ptr<<"\t"<<"Left"<<endl;
            Neurite_Element_Morphology <<"Diameter:"<<"\t"<<daughter_dia<<"\t"<<"Position:"<<"\t"<<daughter_pos[0]<<"\t"<<daughter_pos[1]<<"\t"<<daughter_pos[2]<<"\t"<<"SO Ptr:"<<"\t"<<daughter_so_ptr<<"\t"<<"Left"<<endl;
            
           /*  if(neurite_element->GetDaughterRight() != nullptr){
                return (record_morphology((neurite_element->GetDaughterRight())));
            } // return right daughter
            else if (neurite_element->GetDaughterLeft() != nullptr){
                return (record_morphology((neurite_element->GetDaughterLeft())));
            } // return left daughter
            */

            record_morphology(neurite_element->GetDaughterLeft());

        } // if left daughter != nullptr 

        if (neurite_element->GetDaughterLeft() == nullptr && neurite_element->GetDaughterRight() == nullptr)
        {    
            cout<<"TERMINAL END !!"<< endl;
            Neurite_Element_Morphology <<"New Neurite"<<endl;
        } // if nullptrs 

    } // record morpology template function

    // Function to record the morphology of soma
    //argument :  name of the file to be created
    //void WriteNeuriteElementMorphologyRecursive(std::string file_name ) {
    template <typename TSimulation = Simulation<>>
    void WriteNeuriteElementMorphologyRecursive() {
    auto* sim = TSimulation::GetActive();
    auto* rm = sim->GetResourceManager();
    auto soma = rm->template Get<experimental::neuroscience::NeuronSoma>();

    int n = rm->GetNumSimObjects();
    std::cout<< "Number of Simulation object :"<< n<< std::endl;


    //ofstream Neurite_Element_Morphology;
   // Neurite_Element_Morphology.open(file_name,ios::out | ios::app);

            // recording the diameter, position and simulation objct pointer
                    auto diameter = soma->GetDiameter();
                    auto position = soma->GetPosition();
                    auto so_ptr = soma->GetSoPtr();
                    cout<< "SOMA"<< endl;
                    cout<<"Diameter     "<<diameter<<"      Position:        "<<position[0]<<"      "<<position[1]<<"       "<<position[2]<<"       "<<"        SO PTR:     "<<so_ptr<<endl;

           //Get the extended neurite elements on soma 
           // An array of all the neurites elements 
            auto&& extended_neurite_elements = soma->GetDaughters();


            // Number of neurite elements extended from the soma
            int number_of_extended_neurites = extended_neurite_elements.size();
             cout<<"Number of neurites :"<< number_of_extended_neurites<<endl;


                // 
                for (int i = 0; i < number_of_extended_neurites; i++)
                {
                    auto&& current_neurite_element = extended_neurite_elements[i];

                    auto&& daughter = current_neurite_element->GetDaughterLeft();
                    cout<<"Diameter: "<< daughter->GetDiameter()<<endl;
                    record_morphology(current_neurite_element);
                    
                    
                    
                }// FOR LOOP


}

} //namespace bdm 

#endif  // NEURITE_ELEMENT_RECURSIVE_H_


