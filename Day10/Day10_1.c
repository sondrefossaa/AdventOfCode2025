#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUTTONS 100
#define MAX_JOLTAGE 100

typedef struct {
    char *switches;       
    char **buttons;       
    int *joltage;           
    int button_count;
    int joltage_count;
} machine;

int data_size = 0;
machine *machines[163];     
const char *file = "input.txt";

getFewestPresses(machine curr_machine){
    return;
}

int getAnswer(){
    int sum = 0;
    for(int i = 0; i < data_size; i++){
        sum += getFewestPresses(*machines[i]);
    }




    return sum;
}
int main(void) {
    FILE *input = fopen(file, "r");
    if (input == NULL) {
        printf("Error opening file %s\n", file);
        return 1;
    }
    
    char buffer[256];
    
    while (fgets(buffer, sizeof(buffer), input) != NULL) {
        // Remove newline character
        buffer[strcspn(buffer, "\n")] = '\0';
        
        // Initialize machine
        machines[data_size] = (machine*)malloc(sizeof(machine));
        if (machines[data_size] == NULL) {
            printf("Memory allocation failed\n");
            break;
        }
        
        machines[data_size]->buttons = (char**)malloc(sizeof(char*) * MAX_BUTTONS);
        machines[data_size]->joltage = (int*)malloc(sizeof(int) * MAX_JOLTAGE);
        machines[data_size]->button_count = 0;
        machines[data_size]->joltage_count = 0;
        
        // Tokenize by space
        char *token = strtok(buffer, " ");
        while (token != NULL) {
            // Check first character to determine type
            char first_char = token[0];
            
            switch (first_char) {
                case '[': {
                    int len = strlen(token);
                    if (len > 2 && token[len-1] == ']') {
                        // Allocate memory and copy without brackets
                        machines[data_size]->switches = malloc(len - 1);  // -2 for brackets, +1 for null term
                        strncpy(machines[data_size]->switches, token + 1, len - 2);
                        machines[data_size]->switches[len - 2] = '\0';
                    } 
                    break;
                }
                
                case '(': {
                    if (machines[data_size]->button_count < MAX_BUTTONS) {
                        machines[data_size]->buttons[machines[data_size]->button_count] = strdup(token);
                        machines[data_size]->button_count++;
                    }
                    break;
                }
                
                case '{': {
                    char *jolt_str = token + 1; // skip first
                    char *end_ptr;
                    
                    while (*jolt_str != '}' && *jolt_str != '\0') {
                        // Convert to integer
                        long value = strtol(jolt_str, &end_ptr, 10);
                        
                        if (machines[data_size]->joltage_count < MAX_JOLTAGE) {
                            machines[data_size]->joltage[machines[data_size]->joltage_count] = (int)value;
                            machines[data_size]->joltage_count++;
                        }
                        
                        // Move to next number (skip comma)
                        if (*end_ptr == ',') {
                            jolt_str = end_ptr + 1;
                        } else {
                            jolt_str = end_ptr;
                        }
                    }
                    break;
                }
            }
            
            token = strtok(NULL, " ");
        }
        
        data_size++;
    }
    
    fclose(input);
    
    // Print parsed data for verification
    printf("Parsed %d machines:\n", data_size);
    for (int i = 0; i < data_size; i++) {
        printf("Machine %d:\n", i);
        printf("  Switches: %s\n", machines[i]->switches);
        
        printf("  Buttons (%d): ", machines[i]->button_count);
        for (int j = 0; j < machines[i]->button_count; j++) {
            printf("%s ", machines[i]->buttons[j]);
        }
        printf("\n");
        
        printf("  Joltage (%d): ", machines[i]->joltage_count);
        for (int j = 0; j < machines[i]->joltage_count; j++) {
            printf("%d ", machines[i]->joltage[j]);
        }
        printf("\n\n");
    }
    printf("Answer is: %d", getAnswer());
    // Cleanup
    for (int i = 0; i < data_size; i++) {
        free(machines[i]->switches);
        
        for (int j = 0; j < machines[i]->button_count; j++) {
            free(machines[i]->buttons[j]);
        }
        free(machines[i]->buttons);
        free(machines[i]->joltage);
        free(machines[i]);
    }
    
    return 0;
}