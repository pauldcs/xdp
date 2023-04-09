#include "file.h"
#include "xleaks.h"
#include "log.h"
#include <string.h>
#include <sys/stat.h>

t_file *file_init(ct8 *path)
{
	t_file *file = __xmalloc__(sizeof(t_file));
	struct stat st;

	if (file == NULL)
		return (NULL);

	bzero(file, sizeof(t_file));

	/* 
	 * if no filename was provided it 
	 * means stdin
	 */
	if (!path)
		path = "/dev/stdin";
	
	if (access(path, F_OK) != 0
		|| stat(path, &st) < 0) {
		__log__(error, "%s: %s", path, ERROR_MSG);
		goto failure;
	}

	if (S_ISREG(st.st_mode))  
		file->type = FILE_TYPE_REGULAR;  
        
    else if (S_ISDIR(st.st_mode))  
		file->type = FILE_TYPE_DIRECTORY;        

    //else if (S_ISLNK(st.st_mode))
	//	file->type = FILE_TYPE_SYMBOLIC_LINK;    
	/*
	 *     maybe it would be good to ask if the 
	 *     link should be followed or not, and
	 *     dump the actual symlink if not
	 */

    else if (S_ISSOCK(st.st_mode)) 
		file->type = FILE_TYPE_SOCKET;      
     
	else if (S_ISFIFO(st.st_mode)) 
		file->type = FILE_TYPE_PIPE;     
        
    else if (S_ISBLK(st.st_mode))  
		file->type = FILE_TYPE_BLOCK_DEVICE;  
   
    else if (S_ISCHR(st.st_mode))  
		file->type = FILE_TYPE_CHARACTER_DEVICE; 

    else {
		__log__(error,
			"%s: Foreign tongue:\n "
			"this file speaks a language we cannot understand,\n "
			"and thus remains silent to us...", path);
		goto failure;
	}
	
	file->path = path;
	file->st = st;
	file->size = st.st_size;
	return (file);

failure:
	__xfree__(file);
	return (NULL);
}