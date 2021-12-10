#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define READ 0
#define WRITE 1

int main() {
	mkfifo("send2child", 0777);
	mkfifo("send2parent", 0777);
	int send2child = open("send2child", O_WRONLY, 0777);
	int send2parent = open("send2parent", O_RDONLY, 0777);
	while (1) {
		printf("Enter input: ");
		char line[1000];
		for (int i = 0; i < 1000; i++) line[i] = 0;
		fgets(line, 1000, stdin);
		write(send2child, line, strlen(line));
		printf("Output: ");
		for (int i = 0; i < 1000; i++) line[i] = 0;
		read(send2parent, line, sizeof(line));
		printf("%s\n", line);
	}
	close(send2child);
	close(send2parent);
	return 0;
}
