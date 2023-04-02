#include "xleaks.h"
#include <unistd.h>
#include <sys/ioctl.h>

__attribute__((destructor))
void xleaks_destroy(void)
{
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);


	for (size_t i = w.ws_col; i-- ;) 
		write(1,"=",1);
	write(1,"\n", 1);

	xleaks_state();
	xleaks_summary();
	
	for (size_t i = w.ws_col; i-- ;) 
		write(1,"=",1);
	write(1,"\n", 1);

	active_rss_clear();
	return ;
}