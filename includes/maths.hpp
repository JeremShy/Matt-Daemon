#ifndef MATHS_HPP
# define MATHS_HPP

# include <iostream>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <sys/uio.h>
# include <unistd.h>
# include <strings.h>
# include <stdio.h>
# include <fstream>
# include <exception>
# include <cstdio>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <sys/file.h>
# include <errno.h>
# include <cstdlib>
# include <sstream>
# include <signal.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/wait.h>
# include <Tintin_reporter.hpp>

struct glob
{
	int g_nb_client;
	int g_must_quit;
	int	g_pid;
	int	g_socket;
	int g_fd_lock;
	Tintin_reporter *g_logger;
} ;
# endif
