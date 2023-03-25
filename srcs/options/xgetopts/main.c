#include "xgetopts.h"
#include <stdio.h>

int main(int ac, char *av[])
{
	char c;
	t_xgetopts o;

	xgetopts_init(&o, ac, (cut8 **)av, "s:hfg:");
	while ((c = xgetopts_next(&o)) != -1) {
		switch (c) {
		case 'h':
			printf ("arg '%c' called arg: %s\n", c, (char *)o.arg);
			break; 
		case 's':
			printf ("arg '%c' called arg: %s\n", c, (char *)o.arg);
			break;
		case 'g':
			printf ("arg '%c' called arg: %s\n", c, (char *)o.arg);
			break;
		case '*': 
			printf ("Unknown arg %s\n", (char *)o.arg);
			break ;
		}
	}

	return (0);
}