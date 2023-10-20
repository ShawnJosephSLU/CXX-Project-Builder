// this program builds a CMake based CPP Project

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <string>
#include <filesystem>
#include <ctime>

// Define macros for text colors
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

std::string getCurrentDate() {
    // Get the current time point
    auto now = std::chrono::system_clock::now();

    // Convert the time point to a time_t object
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // Convert the time_t object to a struct tm
    std::tm* timeinfo = std::localtime(&currentTime);

    // Format the date as a string in day, month, year format
    char buffer[11];
    std::strftime(buffer, sizeof(buffer), "%d-%m-%Y", timeinfo);

    return buffer;
}

std::string getAuthor() {
    const char* username = getenv("USER");
    if (username) {
        return username;
    } else {
        return "Unknown"; // Failed to retrieve the username
    }
}


//Main path Directories 
const std::string HOME_DIR = getenv("HOME");
const std::string DOCUMENTS_DIR = HOME_DIR + "/" + "Documents";
const std::string CXX_PROJECTS_DIR = DOCUMENTS_DIR + "/" + "CXX PROJECTS" + "/";



// Global Varibles 
std::string PROJECT_NAME;
std::string ABSOLUTE_PROJECT_DIR_PATH;
std::string PROJECT_BUILD_DIR;
std::string PROJECT_SOURCE_DIR;
std::string PROJECT_HEADERS_DIR;

// create the project name 
void creatProjectName() {
    system("clear");
    std::cout << GREEN << "Create a name for your C++ Project : " << RESET;
    std::getline(std::cin, PROJECT_NAME);
}

// create the Directory with the Project name 
void createProjectDir() {
    system("clear");
    ABSOLUTE_PROJECT_DIR_PATH =  CXX_PROJECTS_DIR + PROJECT_NAME;
    std::cout << ABSOLUTE_PROJECT_DIR_PATH.c_str() << std::endl;
    
    //make the CXX Project Directory if not yet created 

    if(std::filesystem::exists(CXX_PROJECTS_DIR.c_str())  && std::filesystem::is_directory(CXX_PROJECTS_DIR)) {
        mkdir(ABSOLUTE_PROJECT_DIR_PATH.c_str(), 0777);
        std::cout << GREEN << ABSOLUTE_PROJECT_DIR_PATH  << RESET << " : Directory Created Successfully"<< std::endl;

    } else {
        mkdir(CXX_PROJECTS_DIR.c_str() , 0777);
        mkdir(ABSOLUTE_PROJECT_DIR_PATH.c_str(), 0777);
        std::cout << GREEN << CXX_PROJECTS_DIR << RESET << " : Directory Created Successfully"<< std::endl;
        std::cout << GREEN << ABSOLUTE_PROJECT_DIR_PATH  << RESET << " : Directory Created Successfully"<< std::endl;
        system("clear");
    }

    std::cout << GREEN << "Generating Project Files : " << std::endl;

    // create the build and scr dir
    PROJECT_BUILD_DIR = ABSOLUTE_PROJECT_DIR_PATH + "/build";
    PROJECT_SOURCE_DIR = ABSOLUTE_PROJECT_DIR_PATH + "/src";
    PROJECT_HEADERS_DIR = ABSOLUTE_PROJECT_DIR_PATH + "/header";


    mkdir(PROJECT_BUILD_DIR.c_str(),  0777);
    mkdir(PROJECT_SOURCE_DIR.c_str(), 0777);
    mkdir(PROJECT_HEADERS_DIR.c_str(), 0777);


    std::cout << YELLOW << "\t\tbuild dir created" << std::endl;
    std::cout << YELLOW << "\t\tsrc dir created" <<std::endl;
    std::cout << YELLOW << "\t\theader dir created" <<std::endl;

    // Create CMakeLists file
    std::ofstream cmake_file;
    cmake_file.open(ABSOLUTE_PROJECT_DIR_PATH + "/CMakeLists.txt", std::ios::out);
    if(cmake_file.is_open()) {

        std::string projectName = PROJECT_NAME;

       // removes spaces the String
       for(int i = 0; i < projectName.length(); i++) {

            switch(projectName[i]) {
                case 'a' : projectName[i] = 'A'; break; 
                case 'b' : projectName[i] = 'B'; break;
                case 'c' : projectName[i] = 'C'; break;
                case 'd' : projectName[i] = 'D'; break;
                case 'e' : projectName[i] = 'E'; break;
                case 'f' : projectName[i] = 'F'; break;
                case 'g' : projectName[i] = 'G'; break;
                case 'h' : projectName[i] = 'H'; break;
                case 'i' : projectName[i] = 'I'; break;
                case 'j' : projectName[i] = 'J'; break;
                case 'k' : projectName[i] = 'K'; break;
                case 'l' : projectName[i] = 'L'; break;
                case 'm' : projectName[i] = 'M'; break;
                case 'n' : projectName[i] = 'N'; break;
                case 'o' : projectName[i] = 'O'; break;
                case 'p' : projectName[i] = 'P'; break;
                case 'q' : projectName[i] = 'Q'; break;
                case 'r' : projectName[i] = 'R'; break;
                case 's' : projectName[i] = 'S'; break;
                case 't' : projectName[i] = 'T'; break;
                case 'u' : projectName[i] = 'U'; break;
                case 'v' : projectName[i] = 'V'; break;
                case 'w' : projectName[i] = 'W'; break;
                case 'x' : projectName[i] = 'X'; break;
                case 'y' : projectName[i] = 'Y'; break;
                case 'z' : projectName[i] = 'Z'; break;
                case ' ' : projectName[i] = '_'; break;
            }
       }


        cmake_file << "cmake_minimum_required(VERSION 3.10)" << std::endl;
        cmake_file << "project("  << projectName <<")" << std::endl << std::endl;

        cmake_file << "include_directories(headers)" << std::endl << std::endl;

        cmake_file << "set(CMAKE_CXX_STANDARD 17)" << std::endl << std::endl;
        cmake_file << "add_executable(\"" << projectName  << "\""<< std::endl;
        cmake_file << "\tsrc/Main.cpp" << std::endl;
        cmake_file << ")" << std::endl << std::endl;





        // do something 
        std::cout << YELLOW <<"\t\tCMakeList.txt Created Successfully." << RESET << std::endl;

        cmake_file.close();
    }
    else  {
       std::cout << RED <<"ERROR : Cannot Open  " << RESET << std::endl;
    }
}

// create git ignore file
void createGitIgnore() {
    std::ofstream gitIgnoreFile(ABSOLUTE_PROJECT_DIR_PATH + "/.gitignore", std::ios::out);
    gitIgnoreFile << "build/" << std::endl;
    gitIgnoreFile << "*.exec" << std::endl;
    gitIgnoreFile << ".DS_Store"<< std::endl;
    std::cout << YELLOW <<"\t\t.gitignore Created Successfully." << RESET << std::endl;

}

// initalise git
void gitInit() {
    system("clear");
    std::string command = "cd \"" + ABSOLUTE_PROJECT_DIR_PATH + "\" && git init && git add . && git commit -m \"Initial commit\"";
    system(command.c_str());
    system("clear");

}

// create main.cpp 
void createMainFile() {
    std::ofstream main_cpp_file(PROJECT_SOURCE_DIR + "/Main.cpp",std::ios::out);
    if(main_cpp_file.is_open()) {
        // create initial code 
        main_cpp_file << "/*" << std::endl;
        main_cpp_file << "\tAuthor: " << getAuthor() << std::endl;
        main_cpp_file << "\tDate: " << getCurrentDate() << std::endl;
        main_cpp_file << "*/" << std::endl;

        main_cpp_file << "#include <iostream>"  << std::endl << std::endl;
        main_cpp_file << "int main() {\n\n//Code goes here ...\n\tstd::cout << \"Hello World !\" << std::endl;\n\tEXIT_SUCCESS;\n\n}";

    }
    std::cout << YELLOW <<"\t\tMain.cpp Created Successfully." << RESET << std::endl;

    main_cpp_file.close();
}


void openProjectInVSCode() {
   
    // Open Visual Studio Code with the project directory
    std::string command = "open -a 'Visual Studio Code' \"" + ABSOLUTE_PROJECT_DIR_PATH + "\"";
    int result = std::system(command.c_str());

    if (result == 0) {
        // Visual Studio Code was successfully opened
        std::cout << "Visual Studio Code opened with the project." << std::endl;
    } else {
        // Handle any errors while opening Visual Studio Code
        std::cerr << "Error opening Visual Studio Code. Make sure the project path is correct." << std::endl;
    }
}


int main() {

    creatProjectName();
    createProjectDir();
    createMainFile();
    createGitIgnore();
    gitInit();
    openProjectInVSCode();

    EXIT_SUCCESS;
}