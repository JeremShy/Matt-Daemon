#include <maths.hpp>
#include <Tintin_reporter.hpp>
#include <Matt_Exception.hpp>
#include <get_next_line.hpp>

int g_nb_client = 0;
int g_must_quit = 0;
int	g_pid = 0;

int	initialise_socket(char *porc)
{
	struct addrinfo hints;
	struct addrinfo *res;
	int	sock;

	bzero(&hints, sizeof(hints));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_family = AF_INET;

	if (getaddrinfo(NULL, porc, &hints, &res) != 0)
	{
		perror("oups");
		return (-1);
	}
	if ((sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1)
	{
		perror("oups");
		printf("ai_family : %d, ai_socktype : %d, protocol : %d\n", res->ai_family, res->ai_socktype, res->ai_protocol);
		return (-1);
	}
	if (bind(sock, res->ai_addr, res->ai_addrlen) == -1)
	{
		perror("oups");
		return (-1);
	}
	return (sock);
}

void	handle_sigchld(int p)
{
	p = 0;
	g_nb_client--;
	wait4(-1, NULL, WNOHANG, NULL);
	if (g_must_quit)
		exit(0);
}

void	daemonize()
{
	int	pid;
	int len;
	int	i;

	pid = fork();
	if (pid < 0)
	{
		std::cerr << "Can't fork !" << std::endl;
		exit(1);
	}
	if (pid > 0)
	{
		exit(0);
	}
	if (setsid() == -1)
	{
		std::cerr << "Can't setsid !" << std::endl;
		exit(2);
	}
	if (chdir("/") == -1)
	{
		std::cerr << "Can't chdir to / !" << std::endl;
		exit(3);
	}
	i = 0;
	while (i < 3)
	{
		close(i);
		i++;
	}
	i = 0;
	len = open("/dev/null", O_RDWR, 0);
	while (i < 3)
	{
		dup2(len, i);
		i++;
	}
	if (len > 2)
		close(len);
	umask(027);
}

void fork_accept(int client, Tintin_reporter *logger)
{
	int	pid;
	char	*s = NULL;

	if (g_nb_client > 2)
	{
		logger->log(ERROR_LOG, "too much clients connected.");
		shutdown(client, SHUT_RDWR);
		close(client);
		return ;
	}
	logger->log(GREEN_LOG, "new client connected.");
	pid = fork();
	if (pid == 0)
	{
		while (get_next_line(client, &s) > 0)
		{
			logger->log(INFO_LOG, std::string("received : ") + std::string(s));
			if (std::string(s) == std::string("quit"))
			{
				logger->log(INFO_LOG, "quitting because of user input.");
				g_must_quit = 1;
				kill(g_pid, SIGSEGV);
				break;
			}
		}
		std::stringstream ss;
		ss << g_pid;
		logger->log(DISCO_LOG, std::string("Client disconnected.") + std::string(ss.str()));
		shutdown(client, SHUT_RDWR);
		close(client);
		exit(0);
	}
	if (pid > 0)
	{
		g_nb_client++;
		return ;
	}
}

int main(int ac, char **av)
{
	int						suck;
	int						client;
	struct sockaddr_storage	other;
	int						fd_lock;
	socklen_t				other_len;
	Tintin_reporter			*logger;

	if (getuid() != 0)
	{
		std::cerr << "Error : You have to be root in order to use this program." << std::endl;
		return (2);
	}
	if (ac != 2)
	{
		std::cerr << "Error : please enter a port name (#BalanceTonPort)." << std::endl;
		return (1);
	}
	fd_lock = open("/var/lock/matt_daemon.lock", O_CREAT | O_RDWR);
	if (flock(fd_lock, LOCK_EX | LOCK_NB) == -1)
	{
		if (errno == EWOULDBLOCK)
			std::cerr << "Error: /var/lock/matt_daemon.lock is locked. Is an instance of Matt Daemon already running ?" << std::endl;
		return (3);
	}

	try {
		logger = new Tintin_reporter;
	} catch (Matt_Exception exception)
	{
		std::cout << "Error ! - " << exception.what() << std::endl;
		return (2);
	}

	daemonize();
	g_pid = getpid();
	signal(SIGCHLD, handle_sigchld);
	logger->log(GREEN_LOG, "daemon launched");

	suck = initialise_socket(av[1]);
	if (suck == -1)
	{
		logger->log(ERROR_LOG, "can not initialise socket.");
		return (suck);
	}

	listen(suck, 3);
	other_len = sizeof(other);
	while (1)
	{
		client = accept(suck, reinterpret_cast<struct sockaddr *>(&other), &other_len);
		fork_accept(client, logger);
	}
	flock(fd_lock, LOCK_UN);
	close(fd_lock);
	unlink("/var/lock/matt_daemon.lock");
	return (0);
}
