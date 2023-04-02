#include "file.h"
#include <stdio.h>

void file_db_print(t_file *file)
{
	fprintf(stdout, "t_file: {\n");
	fprintf(stdout, "t_file:     .path='%s'\n", file->path);
	fprintf(stdout, "t_file:     .size=%zu\n", file->size);
	fprintf(stdout, "t_file:     .blksize=%d\n", file->st.st_blksize);
	switch(file->type)
	{
		case FILE_TYPE_REGULAR:          fprintf(stdout, "t_file:     .type=REGULAR\n"); break;
		case FILE_TYPE_DIRECTORY:        fprintf(stdout, "t_file:     .type=DIRECTORY\n"); break; 
		case FILE_TYPE_SYMBOLIC_LINK:    fprintf(stdout, "t_file:     .type=SYMLINK\n"); break; 
		case FILE_TYPE_SOCKET:           fprintf(stdout, "t_file:     .type=SOCKET\n"); break; 
		case FILE_TYPE_PIPE:             fprintf(stdout, "t_file:     .type=PIPE\n"); break; 
		case FILE_TYPE_BLOCK_DEVICE:     fprintf(stdout, "t_file:     .type=BLOCK_DEVICE\n"); break; 
		case FILE_TYPE_CHARACTER_DEVICE: fprintf(stdout, "t_file:     .type=CHARACTER_DEVICE\n"); break;
		default: fprintf(stdout, ".type=UNKNOWN");
	}
	fprintf(stdout, "t_file: }\n");
}