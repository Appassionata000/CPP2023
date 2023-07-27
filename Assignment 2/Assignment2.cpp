/*
Assignment 2 of Object-oriente programming to C++ 2023.
Zhiyu Liu 2023.2.23 Physics Department, University of Manchester
This programme reads the file courselit.dat, stores course information in a list, 
prints the mean/standard deviation of the course grade, and formats the course title.
The programme also allows you to sort the course list in various ways.
The user can access various functions of this programme by typing the option in the menu.
*/
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <limits>
#include <algorithm>
#include <iomanip>

// *CamelCase style* is used for typedef/struct names to distinguish from *snake case* local variables
typedef unsigned int UserOption;

struct CourseInfo
{ 
    double grade;         // grade of this course, eg: 90.5
    unsigned int code;    // Course number, eg: 30014
    std::string title;    // Course title, eg: Mathematics 2
};

void display_menu(const std::string menu_option, const UserOption semester_option=0)
{
    if (menu_option == "main") {
        std::cout << "-----------------------------------" << std::endl;
        std::cout << "|            Main menu            |" << std::endl;
        std::cout << "-----------------------------------" << std::endl;
        std::cout << "1. Select a specific semester" << std::endl;
        std::cout << "2. Calculate the mean of grades" << std::endl;
        std::cout << "3. Calculate the standard deviation of the grades" << std::endl;
        std::cout << "4. Show course titles" << std::endl;
        std::cout << "5. Show course details" << std::endl;
    } else if (menu_option == "sem") {
        std::cout << "-------------------------------------" << std::endl;
        std::cout << "|  Main menu | current semester: " << semester_option << "  |" << std::endl;
        std::cout << "-------------------------------------" << std::endl;
        std::cout << "1. Select a specific semester" << std::endl;
        std::cout << "2. Calculate the mean of grades" << std::endl;
        std::cout << "3. Calculate the standard deviation of the grades" << std::endl;
        std::cout << "4. Show course titles" << std::endl;
        std::cout << "5. Show course details" << std::endl;
    }  else if (menu_option == "sort") {
        std::cout << "-----------------------------------"  << std::endl;
        std::cout << "Please select the sorting option:" << std::endl;
        std::cout << "1. Sort by course codes." << std::endl;
        std::cout << "2. Sort by course titles alphabetically" << std::endl;
        std::cout << "3. Sort by course grades (increasing)" << std::endl;
        std::cout << "4. Sort by course grades (decreasing)" << std::endl;
    }
}

UserOption get_valid_input(std::string prompt, UserOption lower_limit, UserOption upper_limit)
{
    UserOption input;
    std::cout << prompt;
    while(!(std::cin >> input) || input < lower_limit || input > upper_limit || std::cin.peek() != '\n'){
        std::cout << "Invalide input! " << prompt;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return input;
}

std::vector<CourseInfo> read_file(const std::string& filename)
{
    /*
    Function that read the file and store the data as the struct CourseInfo type
    */
    std::vector<CourseInfo> course_info_tot;
    double grade;
    unsigned int code;
    std::string title;

    std::fstream course_file(filename); 

    if (!course_file.good()){
        std::cerr << "Error: File couldn't open" << std::endl;
        exit(0);
    }

    // Read course grade/code and course title separately
    while (course_file >> grade >> code) {
        // Read and format the course title
        std::string title_line;                 // will hold unformated line *with leading whitespaces after the course code*
        getline(course_file, title_line);       // get unformated line
        std::string title_word;                 // will hold words in the unformated line
        std::stringstream ss_line{title_line};  // define a string stream to be read
        std::stringstream ss_title;             // string stream of the formated title
        while (ss_line >> title_word) {
            ss_title << title_word << " ";      // formatting
        }
        std::string title{ss_title.str()};      // store the formatted stream to string

        CourseInfo CourseInfoSingle = {grade, code, title};  // Create an object to hold this course's info
        // Append info to corresponding vectors
        course_info_tot.push_back(CourseInfoSingle);  // append this course info to total info vector
    }   

    std::cout << "File read successfully. Totally " << course_info_tot.size() << " courses read." << std::endl;

    return course_info_tot;
}

double get_sum(const std::vector<CourseInfo>& course_info)
{
    double sum = 0.0;
    for (auto it = course_info.begin(); it != course_info.end(); ++it){
        sum += it->grade;
    }
    return sum;
}

double get_mean(const std::vector<CourseInfo>& course_info)
{
    double sum = get_sum(course_info);
    auto num = course_info.size();
    double mean = sum / num;
    return mean;
}

std::vector<double> get_std_with_err(const std::vector<CourseInfo>& course_info)
{
    // Get the std and std error of the course grades in the CourseInfo struct
    double mean = get_mean(course_info);
    auto num = course_info.size();
    double diff_square_sum = 0.0;
    std::vector<double> std_with_err;
    // Calculate std
    for (auto it = course_info.begin(); it != course_info.end(); ++it){
        diff_square_sum += pow((it->grade - mean), 2);
    }
    double std = sqrt((1.0 / (num - 1)) * diff_square_sum);
    double std_err = std / sqrt(num);
    // Store std and error in the vector
    std_with_err.push_back(std);
    std_with_err.push_back(std_err);
    return std_with_err;
}

bool compare_criteria(const CourseInfo& a, const CourseInfo& b, UserOption sort_option)
{
    switch(sort_option){
        case 1:
            return a.code < b.code;
        case 2:
            return a.title < b.title;
        case 3: 
            return a.grade < b.grade;
        case 4:
            return a.grade > b.grade;
        default:
            return a.code < b.code;
    }
}

void sort_course(std::vector<CourseInfo>& course_info)
{
    display_menu("sort");
    UserOption sort_option = get_valid_input("Your sort option (1-4): ", 1, 4);
    std::sort(course_info.begin(), course_info.end(), 
              [sort_option](const CourseInfo& a, const CourseInfo& b){ return compare_criteria(a, b, sort_option); });
}

std::vector<std::string> combine_title(const std::vector<CourseInfo>& course_info)
{
    std::vector<std::string> full_titles;     // string vector to store all course titles
    for (auto it = course_info.begin(); it != course_info.end(); ++it) {
        std::ostringstream full_title_stream;   // ostringstream object will combine the string and number
        full_title_stream << "PHYS " << it->code << " " << it->title;
        std::string full_title{full_title_stream.str()};
        full_titles.push_back(full_title);
    }
    return full_titles;
}

void print_vec_str(const std::vector<std::string> str)
{
    std::cout << "-----------------------------------"  << std::endl;
    for (auto it = str.begin(); it != str.end(); ++it){
        std::cout << *it << std::endl;
    }
    std::cout << "-----------------------------------"  << std::endl;
}

void display_course_detail(const std::vector<CourseInfo>& course_info)
{
    std::cout << "-----------------------------------"  << std::endl;
    for (auto it = course_info.begin(); it != course_info.end(); ++it){
        std::cout << std::setprecision(1) << std::fixed << it->grade << " ";
        std::cout << it->code << " " << it->title << std::endl;
    }
    std::cout << "-----------------------------------"  << std::endl;
}

std::vector<CourseInfo> get_semester(const std::vector<CourseInfo>& course_info_tot, UserOption semester)
{
    std::vector<CourseInfo> course_info_sem;
    for (auto it = course_info_tot.begin(); it != course_info_tot.end(); ++it){
        if (floor((it->code) / 1e4) == semester){
            CourseInfo CourseInfoSingle = {it->grade, it->code, it->title};
            course_info_sem.push_back(CourseInfoSingle);
        }
    }
    return course_info_sem;
}

int main()
{
    std::cout << "Welcome to this program!" << std::endl;
    std::cout << "Start reading file...." << std::endl;
    const std::vector<CourseInfo> course_info_tot{read_file("courselist.dat")};
    std::vector<CourseInfo> course_info(course_info_tot); 

    // default 0 for total information, 1-4 for a specific semester
    UserOption semester_option = 0;

    std::string process {"y"};
    while (process == "y") {
        
        display_menu(semester_option == 0 ? "main" : "sem", semester_option);
        UserOption main_option = get_valid_input("Your choice (1-5): ", 1, 5);

        switch (main_option) 
        {
            case 1: {
                // option 1: Selecet a single semester or get back total information
                semester_option = semester_option == 0 ? 
                                  get_valid_input("Your semester option (1-4): ", 1, 4) :
                                  get_valid_input("Your semester option (1-4 or 0 to get back information for all semesters): ", 0, 4);
                if (semester_option == 0) {
                    std::cout << "Your have retrieved courses for all semesters" << std::endl; 
                    course_info = course_info_tot;
                } 
                else {
                    std::cout << "---------------------------------------------"  << std::endl;
                    std::cout << "Warning: you have selected semester: " << semester_option << std::endl;
                    std::cout << "Only the information of this semester will be considered in the following" << std::endl;
                    std::vector<CourseInfo> course_info_sem = get_semester(course_info_tot, semester_option);
                    course_info = course_info_sem;
                }
                break;
            }
            case 2: {
                // option 2: Get mean value of course grades    
                double grades_mean = get_mean(course_info);
                std::cout << "Mean value of course grades: " << std::setprecision(3) << std::fixed;
                std::cout << grades_mean << std::endl;
                break;
            }
            case 3: {
                // option 3:  Get std and std error of course grades
                std::vector<double> std_with_err = get_std_with_err(course_info);
                std::cout << "Standard deviation of grades: " << std::setprecision(3) << std::fixed;
                std::cout << std_with_err.at(0) << std::setprecision(3) << std::fixed;
                std::cout << " +/- " << std_with_err.at(1) << std::endl;
                break;
            }
            case 4: {   
                // option 4: Display course titles
                sort_course(course_info);
                std::vector<std::string> combined_title = combine_title(course_info);
                print_vec_str(combined_title);
                break;
            }
            case 5: {
                // option 5: Display course details
                sort_course(course_info);
                display_course_detail(course_info);
                break;
            }
        }
        if (main_option != 1){
            std::cout << "Do you want to continue? (y/n) ";
            while (!(std::cin >> process) || (process != "y" && process != "n") || std::cin.peek() != '\n') {
                std::cout << "Invalid input! Do you want to continue? (y/n) ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }
    
    std::cout << "Goodbye!" << std::endl;
    return 0;
}