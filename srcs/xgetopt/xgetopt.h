#ifndef __XGETOPT_H__
# define __XGETOPT_H__

// t_xgetopt opt;
// xgetopt_init (&opt, argc, (const char **)argv, "hbc:d");
// while ((c = xgetopt_next (&opt)) != -1) {
// 		switch (c) {
// 		case 'h':
// 			ret = help (true);
// 			goto beach;
// 		case 'q':
// 			quiet = true;
// 			break;
// 		case 'F':
// 			free (fuzz_dir);
// 			fuzz_dir = strdup (opt.arg);
// 			break;
// 		default:
// 			ret = help (false);
// 			goto beach;
// 		}
// 	}

// beach:
// 	free();

typedef struct s_xgetopt {
	int err;
	int ind;
	int opt;
	int reset;
	const char *arg;
	int argc;
	const char **argv;
	const char *ostr;
} t_xgetopt;

void xgetopt_init(t_xgetopt *go, int argc, const char **argv, const char *ostr);
int	 xgetopt_next(t_xgetopt *opt);

#endif /* __XGETOPT_H__ */