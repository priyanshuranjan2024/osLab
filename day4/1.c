#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    // Demonstrating fprintf and fscanf
    FILE *file = fopen("test.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    fprintf(file, "Name: %s Age: %d\n", "Alice", 25);
    fclose(file);

    file = fopen("test.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    char name[20];
    int age;
    fscanf(file, "Name: %s Age: %d", name, &age);
    printf("Read using fscanf: Name = %s, Age = %d\n", name, age);
    fclose(file);

    // Demonstrating write and read
    int fd = open("test2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }
    char data[] = "Hello, World!";
    write(fd, data, strlen(data));
    close(fd);

    fd = open("test2.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }
    char buffer[50];
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    if (bytesRead >= 0) {
        buffer[bytesRead] = '\0';
        printf("Read using read(): %s\n", buffer);
    }
    close(fd);

    // Demonstrating sprintf
    char formattedStr[100];
    sprintf(formattedStr, "Hello %s, your score is %d!", "Bob", 90);
    printf("Formatted string using sprintf: %s\n", formattedStr);

    // Demonstrating system
    printf("Listing files using system command:\n");
    system("ls -l");  // Lists files in the directory

    // Demonstrating strtok
    char str[] = "apple,banana,grape,orange";
    char *token = strtok(str, ",");
    printf("Tokens using strtok:\n");
    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, ",");
    }

    return 0;
}
