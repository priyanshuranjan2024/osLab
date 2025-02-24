#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

struct X
{ 
	int a , b ;
	char c;
};


int calculate(int a, int b, char c)
{
	if(c == '+')
		return a + b;
	else if(c == '-')
		return a - b;
	else if(c == '*')
		return a * b;
	else if(c == '/')
		return a / b;
	return 0;
}
int main() {
    int t, n, k;
    printf("Enter n: ");
    scanf("%d", &n);
    
    int m[3][2],m_return[3][2];  
    for (int i = 0; i < 3; i++) {
        if (pipe(m[i]) == -1|| pipe(m_return[i])== -1) 
        {
            perror("Pipe failed");
            return 1;
        }
    }

    printf("Process: ID = %d \n", getpid());

    for (int i = 0; i < n; i++) {
        t = fork();

        if (t == 0) 
        {  
            struct X received;
            read(m[i][0], &received, sizeof(received));
            printf("Child %d (PID=%d) received: a=%d, b=%d, c=%c from Parent (PID=%d)\n",i,
            getpid(), received.a, received.b, received.c, getppid());
           int value  = calculate(received.a, received.b, received.c);
           write(m_return[i][1], &value, sizeof(value));
            exit(0);  
        } 
        else if (t > 0) {  
            int num1, num2, value; struct X d;
            printf("Enter the 1st number of %d number pipeline\n", i);
            scanf("%d", &d.a);
            printf("Enter the 2nd number of %d number pipeline\n", i);
            scanf("%d", &d.b);
            printf("Enter the operation of %d number pipeline\n", i);
            scanf(" %c", &d.c);
            //struct X d = {num1, num2, ch};
            write(m[i][1], &d, sizeof(d));
            sleep(1);
            read(m_return[i][0], &value, sizeof(value));
            printf("The calculated value after receiving is %d\n", value);  
        } 
        else {
            perror("Fork failed");
            return 1;
        }
    }

    // Step 3: Parent waits for all child processes
    while ((k = wait(NULL)) != -1 || errno == EINTR)
        printf("Child process %d terminated\n", k);

    return 0;
}