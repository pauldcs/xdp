#ifndef __OPTIONS_H__
# define __OPTIONS_H__

#include "hdump.h"
#include <stdbool.h>

bool parse_single_option(const char *argument, t_dump_params *params, int *ac, char ***av);
bool sanitize(t_dump_params *params);

#endif /* __OPTIONS_H__ */