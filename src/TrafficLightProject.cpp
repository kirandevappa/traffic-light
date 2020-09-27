#include<iostream>
#include<cstdlib>
#include<numeric>
#include<string>
#include"SignalController.h"

/***
 * Show usage: utility to help display the usage of this program 
 * Parameters: String 
 */
static void show_usage(std::string name)
{
    std::cerr << "Usage: " << name << "-f=40 -a=2 -r=2" <<std::endl
              << "Options:\n" <<std::endl
			  << " -d,--default \t\t -f=40 -a=2 -r=2\n"<<std::endl
			  << " -f,--fullcycle\t\tGreen to Green cycle time in seconds"<<std::endl
			  << " -a,--amber\t\tAmber time in seconds before red"<<std::endl
			  << " -r,--redfull\t\tRed time in seconds for all signals"<<std::endl
              << "-h,--help\t\tShow this help message"<<std::endl
              << std::endl;
}

/**
 * @brief Get the Cmd Option object
 * 
 * @param argc 
 * @param argv 
 * @param option 
 * @return std::string 
 */

std::string getCmdOption(int argc, char* argv[], const std::string& option)
{
    std::string cmd;
     for( int i = 0; i < argc; ++i)
     {
          std::string arg = argv[i];
          if(0 == arg.find(option))
          {
               std::size_t found = arg.find_last_of(option);
               cmd =arg.substr(found + 1);
               return cmd;
          }
     }
     return cmd;
}

/**
 * @brief Check if an option is present in the command line argument
 * 
 * @param argc 
 * @param argv 
 * @param option 
 * @return true 
 * @return false 
 */

bool isOptionPresent(int argc, char* argv[], const std::string& option)
{
    std::string cmd;
     for( int i = 0; i < argc; ++i)
     {
          std::string arg = argv[i];
          if(0 == arg.find(option))
          {
               return true;
          }
     }
     return false;
}

/**
 * @brief Entry point to the program
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */

int main(int argc, char* argv[])
{
	uint fullCycle = 40;
	uint amberTime = 2;
	uint redTime = 2;

	//Parameterize
	if ( (argc < 2) || (true==isOptionPresent(argc, argv, "-h"))) {
        show_usage(argv[0]);
        return 1;
    }
	else if (true==isOptionPresent(argc, argv, "-d"))
	{
		std::cout<<"Using Defaults: "<<fullCycle<<" "<<amberTime<<" "<<redTime<<std::endl;
	}
	else
	{
		if(isOptionPresent(argc, argv, "-f=")){ fullCycle = stoi(getCmdOption(argc, argv, "-f=")); }
		if(isOptionPresent(argc, argv, "-a=")){ amberTime = stoi(getCmdOption(argc, argv, "-a=")); }
		if(isOptionPresent(argc, argv, "-r=")){ redTime = stoi(getCmdOption(argc, argv, "-r=")); }
	}
	

	SignalController *publisher = new SignalController();

	for(uint i=1; i<=4; i++)
	{
		publisher->attach(new TrafficSignal(i));
	}

	publisher->startComputing(fullCycle, amberTime, redTime);

	return 0;
}

