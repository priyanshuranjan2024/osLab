/* Send a structure from process p1 to p2 having 3 parameters(int,int,char) and p2 performs operation based on the character*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
struct X{ 
	int a , b ;
	char c;
};
int calc(int x , char o , int y){
    if ( o == '+') return x + y;
    if ( o == '-') return x - y;
    if ( o == '*') return x * y;
    if ( o == '/' && y!=0 ) return x/y;
    return 0;
}
int main() {
    int p[2];
    pipe(p);
    if ( fork()){
        close(p[0]);
        struct X d = {4, 5, '+'}; 
        write(p[1], &d, sizeof(d));
        close(p[1]);
    } else { 
        close(p[1]);
        struct X r;
        read(p[0], &r, sizeof(r));
        printf("%d\n", calc(r.a, r.c, r.b));
        close(p[0]);
    }
    return 0;
}
