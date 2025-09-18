#include <stdio.h>

int main() {
    int age;
    char name[50];      // Array to store string input for name
    char hobby[50];     // Array to store string input for hobby
  //getting user info
    printf("Enter your age:\n");
    scanf("%d", &age);

    printf("Enter name:\n");
    scanf("%s", name);  
    printf("Enter your hobby:\n");
    scanf("%s", hobby);

    // Print the output with the collected data
    printf("Hey %s, you're %d years old and you like %s.\n", name, age, hobby);

    return 0;
}
