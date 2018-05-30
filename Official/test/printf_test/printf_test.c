#include "mcu.h"
#include "stdio.h"
#define TEST_VERSION "1.0"
// This is the interrupt function for user
void user_interrupt() {

}

// This is the main function
int main() {
	// set some varibles here, like:
	int a = 0;
	while (1) {
		printf("Library Test, version %s\n", TEST_VERSION);
		puts("Author: Zhirui Dai\n");
		a=0;
		while(a<1000) {
			printf("%d\t%x\n",a,a);
			a++;
		}
		puts("Repeat?");
		switch (getchar()) {
			case 'y':continue;break;
			case 'n':JumpTo(0x10000000);break;
		}
	}
}
