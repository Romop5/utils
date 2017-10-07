#include "args.h"
#include <iostream>

void help()
{
	std::cout << "USAGE:\n";
	std::cout << "isabot HOSTNAME[:PORT] CHANNELS [-l] \n";
}
int main(int argc, char** argv)
{
	Arguments arg;
	// expected fixed arguments first in CMD
	arg.first(Arguments::FIXED);
	arg.addFixed("hostname","(\\S*)|(\\S*:\\S*)");
	arg.addFixed("channels","(\\S*,)*(\\S*)");
	arg.addOpt("keywords","l");
	arg.addOpt("keywords","s");
	arg.addLongOpt("help","help","h",Arguments::NO_PARAM);

	int result = arg.parse(argc,argv);
	if(result == Arguments::ARGUMENT_INVALID_FORMAT)
	{
		std::cerr << "Error: " << arg.getErrorMessage() << std::endl;
		std::cerr << "Print usage...\n";
		help();
		exit(1);
	}

	std::cout << arg["hostname"] << " for " << arg["channels"] << std::endl;

	auto map = arg.getMap();
	for(auto it = map.begin(); it != map.end(); it++)
	{
		std::cout << it->first << " - " << it->second << std::endl;
	}

}
