#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

struct nodeInt {
    int n;
    struct nodeInt* next;
    struct nodeInt* prev;
};

struct list {
    struct nodeInt* headI;
    struct nodeInt* tailI;
};

struct list* newList() {
    struct list* e = (struct list*)malloc(sizeof(struct list));
    e->headI = NULL;
    e->tailI = NULL;
}

void addNodeInt(struct list* l, int i) {
    struct nodeInt* e = (struct nodeInt*)malloc(sizeof(struct nodeInt));
    e->n = i;
    e->next = NULL;
    if (l->headI == NULL) {
        l->headI = e;
        l->tailI = e;
        e->prev = NULL;
    } else {
        l->tailI->next = e;
        e->prev = l->tailI;
        l->tailI = e;
    }
}

void printList(struct list* l, bool valid) {
    struct nodeInt* tmp = l->headI;
    while (tmp != NULL)
    {
        printf("%d ", tmp->n);
        tmp = tmp->next;
    }
    
    if (valid) 
        printf("TRUE\n");
    else 
        printf("FALSE\n");
}

void removeNodeInt(struct list* l, struct nodeInt* n) {
    if (n == NULL) {
        printf("null entry\n");
        return;
    }

    if (n == l->headI) {
        if (n == l->tailI) {
            l->headI = NULL;
            l->tailI = NULL;
        } else {
            l->headI = n->next;
            l->headI->prev = NULL;
        }
    } else if (n == l->tailI) {
        l->tailI = n->prev;
        l->tailI->next = NULL;
    } else {
        n->prev->next = n->next;
        n->next->prev = n->prev;
    }

    free(n);
}

void emptyListInt(struct list* l) {
    if (l->headI == NULL) {
        return;
    }

    struct nodeInt* tmp = l->headI;
    struct nodeInt* tmp2 = NULL;
    while (tmp != NULL)
    {
        tmp2 = tmp;
        tmp = tmp->next;
        free(tmp2);
    }

    l->headI = NULL;
    l->tailI  = NULL;
}

bool isDifValid(int n1, int n2) {
    int dif = n1 - n2;
    if (dif > 3 || dif < -3 || dif == 0) 
        return false;

    return true;
}

// copies l2 to l1
void copyListWithRemove(struct list* l1, struct list* l2, struct nodeInt* rm) {
    struct nodeInt* tmp = l2->headI;
    while (tmp != NULL)
    {
        if (tmp != rm) 
            addNodeInt(l1, tmp->n);
        tmp = tmp->next;
    }

}

bool isCopySafe(struct list* l) {
    if (l->headI == NULL) 
        return false;
    
    struct nodeInt* tmp = l->headI;
    bool set = false;
    bool isIncreasing = true;
    while (tmp->next != NULL) {
        if (!isDifValid(tmp->next->n, tmp->n)) {
            return false;
        }

        if (tmp->next->n > tmp->n) {
            if (set && !isIncreasing) {
                return false;
            } else {
                set = true;
            }
        } else {
            if (set && isIncreasing) {
                return false;
            } else {
                set = true;
                isIncreasing = false;
            }
        }

        tmp = tmp->next;
    }
    
    return true;
}

// create a copy of the list and check if removing one node from list is valid or other node
bool solveUnsafe(struct list* l, struct nodeInt* n) {
    struct list* cp = newList();
    copyListWithRemove(cp, l, n);
    bool safe = isCopySafe(cp);
    emptyListInt(cp);
    if (safe) {
        free(cp);
        return true;
    }

    copyListWithRemove(cp, l, n->next);
    safe = isCopySafe(cp);
    emptyListInt(cp);
    if (safe) {
        free(cp);
        return true;
    }
    
    // check all nodes now 
    struct nodeInt* tmp = l->headI;
    while (tmp != NULL)
    {
        copyListWithRemove(cp, l, tmp);
        safe = isCopySafe(cp);
        emptyListInt(cp);
        if (safe) {
            free(cp);
            return true;
        }
        
        tmp = tmp->next;
    }
    
    free(cp);
    return false;
}

// TODO: reset isIncreasing after removal
bool isSafe(struct list* l) {
    bool removed = false;
    if (l->headI == NULL) 
        return false;
    
    struct nodeInt* tmp = l->headI;
    bool set = false;
    bool isIncreasing = true;
    while (tmp->next != NULL) {
        // printf("check\n");
        if (!isDifValid(tmp->next->n, tmp->n)) {
            if (solveUnsafe(l, tmp)) {
                return true;
            } else {
                printList(l, false);
                return false;
            }
        } else if (tmp->next->n > tmp->n) {
            // printf("check3\n");
            if (set && !isIncreasing) {
                if (solveUnsafe(l, tmp)) {
                    return true;
                } else {
                    printList(l, false);
                    return false;
                }
            } else {
                set = true;
            }
        } else {
            // printf("check4\n");
            if (set && isIncreasing) {
                if (solveUnsafe(l, tmp)) {
                    return true;
                } else {
                    printList(l, false);
                    return false;
                }
            } else {
                set = true;
                isIncreasing = false;
            }
        }

        tmp = tmp->next;
    }
    
    // printList(l, true);
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
        struct list *l = newList();
        char *token = strtok(line, " \t\n");
        while (token != NULL) {
            addNodeInt(l, atoi(token)); 
            token = strtok(NULL, " \t\n"); // Get the next token
        }

        if (isSafe(l)) 
            counter++;

        emptyListInt(l);
    }

    printf("%d\n", counter);
    
    fclose(ifp);
}