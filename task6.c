#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>

void recursive_func(int depth){
	char stack_array[1024];
	printf("Depth of recursion: %d\n", depth);
	recursive_func(depth+1);
}

int main(){
	struct rlimit limit;

	getrlimit(RLIMIT_STACK, &limit);
	printf("Limit if stack now: %ld bytes(soft), %ld bytes(hard)\n", limit.rlim_cur, limit.rlim_max);

	recursive_func(1);

	return 0;

}
