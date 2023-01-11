#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#define BUF_SIZE 2056
int main(void) {
	char *buf = (char*)calloc(BUF_SIZE, sizeof(char));
	char *tok;
	char *pathname;
	char **argv;
	int argc = 0;
	int status;
	while(true) {
		printf("# ");
		fgets(buf, BUF_SIZE-1, stdin);
		// remove trailling NL
		buf[strcspn(buf, "\n")] = 0;
		tok = strtok(buf, " ");
		pathname = tok;
		while(tok != NULL) {
			argc++;
			argv = (char**)realloc(argv, (argc+1) * sizeof(char*));
			for(int i = 0; i < argc; i++) {
				argv[i] = (char*)malloc(strlen(tok) * sizeof(char));
				strcpy(argv[i], tok);
			}
			tok = strtok(NULL, " ");
		}
		argv[argc+1] = 0;
		if(fork() != 0) {
			waitpid(-1, &status, 0);
		} else {
			if(execve(pathname, argv, 0))
				perror("execve");
			free(argv);
		}
	}
}
