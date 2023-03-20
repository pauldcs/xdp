#include "hdump.h"
#include "reader.h"

#include <stdbool.h>

bool start_stdin_reader(t_dump_params *params)
{
	t_reader        r;
	int             ret;

	r.fd = 0;
	r.save.buf = NULL;
	r.save.size = 0;
	r.range_size = params->file.range_size;
	ret = reader((uint8_t **)&params->data.data, &r, "");
	
	if (ret == -1)
		return (false);
	params->file.file_size = ret;
	reader_destroy(&r);
	return (true);
}