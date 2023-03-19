/*
+-----------------------------------------------------+
| Assignment 3 of Object oriented programming in C++  |
| Zhiyu Liu, University of Mancheseter, 2023.3.3      |
+-----------------------------------------------------+
This program demonstrates how to use constructors to initialize an object.
The example object is a galaxy implemented in "Galaxy.hpp".
The output format uses "Table.hpp" to print a table of galaxy information.
==============================================================================
The first part of this program demonstrates: 
1. The use of parameterized constructor. An author-defined Milky_Way object is implemented.
2. A method that changes the hubble type of the object.
3. A method that adds satellites to the galaxy object.
The seocnd part of this program demonstrates:
- A constructor that takes arguments from user input.
==============================================================================
*/
#include "Table.hpp"
#include "Galaxy.hpp"

int main()
{
    // Set true to demonstrate the first part of the program.
    bool DEMONSTRATE_DEFAULT = true;

    if (DEMONSTRATE_DEFAULT) {
        std::cout << "\nWelcome to the program!" << std::endl;

        std::cout << "\nDemonstration of using parameterized constructor:" << std::endl;

        Galaxy Milky_Way("Milky Way", "Sc", 0, 1.5e12, 0.03);
        Milky_Way.display_info();

        std::cout << "\nDemonstration of a method to change the galaxy's type:" << std::endl;
        Milky_Way.change_type("SBc");
        Milky_Way.display_info();

        std::cout << "\nDemonstration of calculating stallar mass: " << std::endl;
        std::cout << "Stellar mass of " << Milky_Way.get_name() << ": ";
        std::cout << Milky_Way.get_stellar_mass() << std::endl;

        // Initialize two satellites and add them to Milky_Way.
        std::cout << "\nDemonstration of adding satellites" << std::endl;
        Galaxy LMC("Large Magellanic Cloud", "Irr", 0, 1.2e11, 0.03);
        Galaxy SMC("Small Magellanic Cloud", "Irr", 0.000527, 7e9, 0.02);

        Milky_Way.add_satellite(&LMC);
        Milky_Way.add_satellite(&SMC);

        Milky_Way.display_info();
    }

    // Set true to demonstrate the second part of the program.
    bool DEMONSTRATE_INPUT = false;

    if (DEMONSTRATE_INPUT) {
        // Construct the object from user input.
        Galaxy new_galaxy(std::cin);
        std::cout << "\nInformation about your galaxy:" << std::endl;
        new_galaxy.display_info();
    }

    return 0;
}