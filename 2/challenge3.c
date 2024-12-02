#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

struct nodeInt {
    int n;
    struct nodeInt* next;
};

struct nodeString {
    char* n;
    struct nodeString* next;
};

struct nodeString* headS = NULL;
struct nodeInt* headI = NULL;
struct nodeString* tailS = NULL;
struct nodeInt* tailI = NULL;

void addNodeInt(int i) {
    struct nodeInt* e = (struct nodeInt*)malloc(sizeof(struct nodeInt*));
    e->n = i;
    e->next = NULL;
    if (headI == NULL) {
        headI = e;
        tailI = e;
    } else {
        tailI->next = e;
        tailI = e;
    }
}

void emptyListInt() {
    if (headI == NULL) {
        return;
    }

    struct nodeInt* tmp = headI;
    struct nodeInt* tmp2 = NULL;
    while (tmp != NULL)
    {
        tmp2 = tmp;
        tmp = tmp->next;
        free(tmp2);
    }

    headI = NULL;
    tailI  = NULL;
}

bool isSafe() {
    if (headI == NULL) 
        return false;
    
    struct nodeInt* tmp = headI;
    bool set = false;
    bool isIncreasing = true;
    printf("%d ", tmp->n);
    while (tmp->next != NULL) {
        printf("%d ", tmp->next->n);
        int dif = tmp->next->n - tmp->n;
        if (dif > 3 || dif < -3 || dif == 0) {
            printf("FALSE\n");
            return false;
        }

        if (tmp->next->n > tmp->n) {
            if (set && !isIncreasing) {
                printf("FALSE\n");
                return false;
            } else {
                set = true;
            }
        } else {
            if (set && isIncreasing) {
                printf("FALSE\n");
                return false;
            } else {
                set = true;
                isIncreasing = false;
            }
        }

        tmp = tmp->next;
    }
    
    printf("TRUE\n");
    return true;
}

int main() {
    FILE *ifp = fopen("input2.txt", "r");
    char c;
    int counter = 0;
    bool safe = true;
    int track = 0;
    int num;
    char line[128];
    // check the first 2 if increasing or decreasing then all after should be the same
    while (fgets(line, sizeof(line), ifp)) {
        char *token = strtok(line, " \t\n");
        while (token != NULL) {
            addNodeInt(atoi(token)); 
            token = strtok(NULL, " \t\n"); // Get the next token
        }

        if (isSafe()) 
            counter++;

        emptyListInt();
    }

    printf("%d\n", counter);
    
    fclose(ifp);
}