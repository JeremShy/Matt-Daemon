#include <maths.hpp>

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

int main(int ac, char **av)
{
	int		suck;
	int		client;
	struct sockaddr_storage other;
	socklen_t	other_len;

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
	suck = initialise_socket(av[1]);
	if (suck == -1)
		return (suck);

	std::ifstream file("/var/lock/matt_daemon.lock");
	if (!file)
	{
		std::ofstream file("/var/lock/matt_daemon.lock");
		file.close();
	}
	else
	{
		std::cerr << "Error: /var/lock/matt_daemon.lock exists. Is an instance of Matt Daemon already running ?" << std::endl;
		return (3);
	}

	listen(suck, 3);
	other_len = sizeof(other);
	client = accept(suck, reinterpret_cast<struct sockaddr *>(&other), &other_len);

	remove("/var/lock/matt_daemon.lock");
	return (0);
}
