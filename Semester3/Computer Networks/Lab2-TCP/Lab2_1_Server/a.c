#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	int pid = fork();
	if(pid == 0){
		execlp( "/bin/sh", "/bin/sh", "-c", "ls -l  > redirected.txt", (char *)NULL );
	}	

	return 0;
}
