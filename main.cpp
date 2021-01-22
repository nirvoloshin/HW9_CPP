/* Includes */
#include <iostream>
#include <cstring>
#include "ip.h"
#include "port.h"
#include "input.h"


int main(int argc, char** argv)
{
	if (check_args(argc,argv)){
		return 1;
	}
	String rule = String(argv[1]);
	String *subrule = NULL;
	size_t size = 0;
	/* spliting the rule into rule type and rule data */
	rule.split("=",&subrule,&size);
	/* handeling Port related rules */
	if ((subrule[0].trim().equals("src-port")) ||
		(subrule[0].trim().equals("dst-port"))) {
		Port port_rule = Port (subrule[0].trim());
		port_rule.set_value(subrule[1].trim());
		parse_input (port_rule);

	}
	/* handeling Ip related rules */
	if ((subrule[0].trim().equals("src-ip")) ||
		(subrule[0].trim().equals("dst-ip"))) {
		Ip ip_rule = Ip (subrule[0].trim());
		ip_rule.set_value(subrule[1].trim());
		parse_input (ip_rule);

	}
	delete[] subrule;
	return 0;


}