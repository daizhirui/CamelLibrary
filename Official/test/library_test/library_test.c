#include "stdio.h"
#define TEST_VERSION "1.0"
// This is the interrupt function for user
void user_interrupt() {

}

// This is the main function
void main() {
	// set some varibles here, like:
	int a = 1;
	printf("Library Test, version %s\n", TEST_VERSION);
	puts("Author: Zhirui Dai\n");
	while(a<1000) {
		printf("%d\t%x\n",a,a++);
	}
}
