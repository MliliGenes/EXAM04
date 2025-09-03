#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int	ft_popen(const char *file, char *const argv[], char type)
{
	if (!file || !argv || (type != 'r' && type != 'w'))
		return -1;



	int fd[2];
	pipe(fd);


	pid_t pid;
	if (type == 'r')
	{
		pid = fork();
		if (pid == -1) return -1;
		if (pid  == 0)
		{
			dup2(fd[1], 1);
			close(fd[0]);
			close(fd[1]);
			execvp(file, argv);
			exit (-1);
		}
		close(fd[1]);
		if (waitpid(pid, 0, 0) == -1) return -1;
		return (fd[0]);
	}
	if (type == 'w')
	{
		pid = fork();
		if (pid == -1) return -1;
		if (pid== 0)
		{
			dup2(fd[0], 0);
			close(fd[0]);
			close(fd[1]);
			execvp(file, argv);
			exit (-1);
		}
		close(fd[0]);
		if (waitpid(pid, 0, 0) == -1) return -1;
		return (fd[1]);
	}
	
	return -1;
}

int main() 
{
    printf("fd : %d\n", ft_popen("ls", (char *const[]){"ls", NULL}, 'r'));
    printf("fd : %d\n", ft_popen("ls", (char *const[]){"ls", NULL}, 'w'));
    // while(1){}
}