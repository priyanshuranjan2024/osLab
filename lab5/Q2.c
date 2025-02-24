#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
struct X{ 
	int a ;
};
int calc(int x){
    return x+5 ;
}
int main() {
    int p[2];
    pipe(p);
    if ( fork()){
        close(p[0]);
        struct X d = {5}; 
        write(p[1], &d, sizeof(d));
        close(p[1]);
    } else { 
        close(p[1]);
        struct X r;
        read(p[0], &r, sizeof(r));
        printf("%d\n", calc(r.a));
        close(p[0]);
    }
    return 0;
}
