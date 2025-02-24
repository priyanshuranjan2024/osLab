#include <stdio.h>
#include <unistd.h>

int main() {
    int p1[2], p2[2];  
    pipe(p1);  
    pipe(p2);  
    if (fork()) {  
        close(p1[0]); 
        close(p2[1]);  

        int num = 5;  
        write(p1[1], &num, sizeof(num));  

        read(p2[0], &num, sizeof(num));  
        printf("Updated Value: %d\n", num);

        close(p1[1]);  
        close(p2[0]);  
    } else {  
        close(p1[1]);  
        close(p2[0]);  

        int num;
        read(p1[0], &num, sizeof(num));  

        num += 5;  

        write(p2[1], &num, sizeof(num));  
        close(p1[0]);  
        close(p2[1]);  
    }

    return 0;
}
