/*
This file defines the Galaxy class, which represents a galaxy and its information
such as names, redshift value, total mass and stellar fraction.
The file starts with a new typename representing the hubble types and 
several functions that help to validate the constructor attributes.
------------------------------------------------------------
Author: Zhiyu Liu, University of Manchester, 2023.3.3
*/

#ifndef GALAXY_HPP
#define GALAXY_HPP

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <sstream>
#include "Table.hpp"

// A template function to convert numbers to strings and keep the initial format.
template <typename T>
std::string to_string_format(const T num)
{
    std::ostringstream oss;
    oss << num;
    return oss.str();
}

// Create an alias for the std::string that represents the hubble types
typedef std::string HubbleType;

// All valid hubble types stored in a vector of strings.
const std::vector<HubbleType> HubbleTypes
{"E0", "E1", "E2", "E3", "E4", "E5", "E6", "E7",
 "S0", "Sa", "Sb", "Sc", "SBa", "SBb", "SBc", "Irr"};

// A series of validation functions
bool is_valid_hubble_type(const std::string& str) {
  return std::find(HubbleTypes.begin(), HubbleTypes.end(), str) != HubbleTypes.end();
}

bool is_valid_redshift(const double redshift) {
    return (redshift >=0 && redshift <= 10);
}

bool is_valid_mass_tot(const double mass_tot) {
    return (mass_tot >= 1e6 && mass_tot <= 1e13);
}

bool is_valid_stellar_frac(const double stellar_frac)
{
    return (stellar_frac >= 0 && stellar_frac <= 0.05);
}

/*
Class name: Galaxy
--------------------
Description: The Galaxy class contains information of a single galaxy.
User can initialize a galaxy object by a parameterized constructor or through a input stream.
Both constructors validate the attributes.
----------------------------------------
Attibutes:
- name: (string type) name of the galaxy.
- hubble_type: (HubbleType type) Hubble type of the galaxy.
- redshift: (double type) redshift of the galaxy in the range [0, 10].
- mass_tot: double tpye total mass of the galaxy in the range 1e6-1e13 solar masses.
    (the provided range 1e7-1e12 has been modified)
- stellar_frac: (double type) steallar mass fraction in the range [0, 0.05].
- satellites: (vector of Galaxy*) satellites of the galaxy. 
    satellites are initialized as Galaxy objects and have the same attributes.
    A satellite is not supposed to have satellites
----------------------------------------
Methods:
- Galaxy()
    Default constructor.
- Galaxy(std::string name_in, HubbleType hubble_type_in, double redshift_in, 
           double mass_tot_in, double stellar_frac_in, Galaxy* satellite_in)
    Parameterized constructor. Detailed description can be found in the implementation.
- Galaxy(std::istream&)
    Constructor that takes arguments from the input.
- ~Galaxy()
    Destructor
- get_name(), get_hubble_type(), get_redshift(), get_mass_tot(), get_stellar_frac()
    Getters
- get_stellar_mass()
    Get the stellar mass using formulat M = stellar fraction * total mass
- display_info()
    Display the galaxy information in a tabular form using "Table.hpp"
- change_type()
    Change the hubble type of the galaxy.
- add_satellite()
    Add satellites to the galaxy object by passing their addresses.
*/

class Galaxy
{
friend std::istream& read_input(std::istream& input_stream, Galaxy& galaxy_in);
private:
    std::string name;
    HubbleType hubble_type;
    double redshift;
    double mass_tot;
    double stellar_frac;
    std::vector<Galaxy*> satellites;
public:
    // Consturctors and a destructor
    Galaxy() = default;
    Galaxy(std::string name_in, HubbleType hubble_type_in, double redshift_in, 
           double mass_tot_in, double stellar_frac_in, Galaxy* satellite_in);
    Galaxy(std::istream&); 
    
    ~Galaxy() {}

    // Getters
    std::string get_name() const {return name;}
    HubbleType get_hubble_type() const {return hubble_type;}
    double get_redshift() const {return redshift;}
    double get_mass_tot() const {return mass_tot;}
    double get_stellar_frac() const {return stellar_frac;}
    double get_stellar_mass() const;

    // Member functions
    void display_info() const;
    void change_type(HubbleType new_type);
    void add_satellite(Galaxy* satellite_in);
};

/*
Parameterized constructor for the galaxy object.
The satellites have defualt values nullptr. All attributes except name are validated.
*/
Galaxy::Galaxy(std::string name_in, HubbleType hubble_type_in, double redshift_in, 
               double mass_tot_in, double stellar_frac_in, Galaxy* satellite_in=nullptr) : 
        name(name_in), 
        hubble_type(hubble_type_in), 
        redshift(redshift_in), 
        mass_tot(mass_tot_in), 
        stellar_frac(stellar_frac_in)
{
    if (!is_valid_hubble_type(hubble_type_in)) {
        std::cout << "Invalide Hubble type." << std::endl;
        throw std::invalid_argument("Invalid input");
    }

    if (!is_valid_redshift(redshift_in)) {
        std::cout << "Invalid redshift." << std::endl;
        throw std::invalid_argument("Invalid input");
    }

    if (!is_valid_mass_tot(mass_tot_in)) {
        std::cout << "Invalid total mass." << std::endl;
        throw std::invalid_argument("Invalid input");
    }

    if (!is_valid_stellar_frac(stellar_frac_in)) {
        std::cout << "Invalid stellar fraction" << std::endl;
        throw std::invalid_argument("Invalid input");
    }
}

// friend of the Galaxy class that initializes the object passed by the constructor.
std::istream& read_input(std::istream& input_stream, Galaxy& galaxy_in)
{
    std::cout << "Please enter the name of the galaxy: ";
    std::getline(input_stream, galaxy_in.name);

    std::cout << "Please enter the type of the galaxy: ";
    while (!(input_stream >> galaxy_in.hubble_type) || !is_valid_hubble_type(galaxy_in.hubble_type)) {
        std::cout << "Invalid hubble type, please enter again: ";
        input_stream.clear();
        input_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Please enter the redshift: ";
    while (!(input_stream >> galaxy_in.redshift) || galaxy_in.redshift < 0 || galaxy_in.redshift > 10) {
        std::cout << "Invalid redshift, please enter again: ";
        input_stream.clear();
        input_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Please enter the total mass: ";
    while (!(input_stream >> galaxy_in.mass_tot) || galaxy_in.mass_tot < 1e7 || galaxy_in.mass_tot > 1e12) {
        std::cout << "Invalid total mass, please enter again: ";
        input_stream.clear();
        input_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Please enter the stellar mass fraction: ";
    while (!(input_stream >> galaxy_in.stellar_frac) || galaxy_in.stellar_frac < 0 || galaxy_in.stellar_frac > 0.05) {
        std::cout << "Invalid stellar mass fraction, please enter again: ";
        input_stream.clear();
        input_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return input_stream;
}

Galaxy::Galaxy(std::istream& input_stream)
{
    read_input(input_stream, *this);
}

void Galaxy::display_info() const
{
    std::vector<std::string> headers{"Name", "Type", "Redshift", "Total mass", "Stellar fraction"};
    std::vector<std::vector<std::string>> rows;
    std::vector<std::string> row{name, hubble_type, 
                            to_string_format(redshift),
                            to_string_format(mass_tot), 
                            to_string_format(stellar_frac)};

    if (!satellites.size()) {
        rows.push_back(row);
        Table Galaxy_info(headers, rows);
        Galaxy_info.display_table();
    } 
    else {
        headers.push_back("Satellites");
        row.push_back(to_string_format(satellites.size()));
        rows.push_back(row);

        std::stringstream oss_satellite;
        oss_satellite << "of " << name;

        for (auto it = satellites.begin(); it != satellites.end(); ++it) {
            std::vector<std::string> more_row{(*it)->name, (*it)->hubble_type, 
                                            to_string_format((*it)->redshift),
                                            to_string_format((*it)->mass_tot),
                                            to_string_format((*it)->stellar_frac),
                                            oss_satellite.str()};
            rows.push_back(more_row);
        }
        Table Galaxy_info(headers, rows);
        Galaxy_info.display_table();
    }
}

void Galaxy::change_type(HubbleType new_type)
{
    this->hubble_type = new_type;
}

inline double Galaxy::get_stellar_mass() const
{
    return this->stellar_frac * this->mass_tot;
}

void Galaxy::add_satellite(Galaxy* satellite_in)
{
    satellites.push_back(satellite_in);
}

#endif