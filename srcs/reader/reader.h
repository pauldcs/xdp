/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 00:09:56 by pducos            #+#    #+#             */
/*   Updated: 2022/10/28 21:52:35 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READER_H
# define READER_H

# include <stdbool.h>
# include <sys/types.h>
# include <stdint.h>
# include <stddef.h>

# define BUFF_SIZE 64
# define R_ERROR  -1

typedef struct s_reader
{
	int		fd;
	size_t	cap;
	size_t	checked;
	struct	s_save {
		uint8_t	*buf;
		size_t	size;
	}	save;
}	t_reader;

/**
 * @brief Reads chuncks of 'sep' separated strings from a file descriptor.
 * 
 * @param buf - The buffer which will hold the output
 * @param r - The reader structure assiociated with the file 
 * @param sep - A string containing the characters that will be 
 * interpretated as separators.
 * @return the size of what was stored in 'buf'.
 * The content of buf will always be null terminated, so this can be ignored.
 */
ssize_t		reader(uint8_t **buf, t_reader *r, char *sep);

/**
 * @brief Initializes a new reader structure.
 * 
 * @param file - Path to the file 
 * @return a pointer to the static reader structure 
 */
t_reader	*reader_init(const char *file);

/**
 * @brief Destroys the content of the reader structure
 * 
 * @param reader - A pointer to the structure to destroy
 */
void		reader_destroy(t_reader *reader);
bool		r_alloc(uint8_t **ptr, size_t size);
bool		r_realloc(uint8_t **buf, size_t *cap, size_t len, size_t new_cap);
void		*r_memcpy(uint8_t *dst, const uint8_t *src, size_t n);

#endif
