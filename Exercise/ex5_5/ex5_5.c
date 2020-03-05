#include <stdio.h>
#include <unistd.h>

int main(){
	printf("===== System call execl testing ====\n");
	//execl("/bin/date", "/bin/date", NULL);
	//execl("date", "date", NULL);
	execlp("date", "date", NULL);
	printf("exec error\n");
}
