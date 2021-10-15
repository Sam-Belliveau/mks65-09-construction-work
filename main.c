#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PERSON_NAME_SIZE 32

struct person 
{
    char name[PERSON_NAME_SIZE];
    struct person* parent;
    struct person* child;
};

struct person* create_person(const char* name)
{
    struct person* p = malloc(sizeof(struct person));

    strncpy(p->name, name, PERSON_NAME_SIZE);
    p->parent = NULL;
    p->child = NULL;

    printf("Created Person %s @ %p\n", p->name, p);

    return p;
}

struct person* create_child(struct person* parent, const char* name)
{
    struct person* child = create_person(name);

    child->parent = parent;
    parent->child = child;

    return child;
}

int count_ancestors(struct person* person)
{
    if(person) return 1 + count_ancestors(person->parent);
    return -1;
}

int count_children(struct person* person)
{
    if(person) return 1 + count_children(person->child);
    return -1;
}

void print_person(struct person* person)
{
    int ancestors = count_ancestors(person);
    int children = count_ancestors(person);
    
    printf("This is %s! They have %d ancestors and %d children.", person->name, ancestors, children);

    printf("\n");
}

void erase_ancestors(struct person* person) 
{
    if(person)
    {
        printf(" - %s has been erased from the history books!\n", person->name);
        erase_ancestors(person->parent);

        if(person->child) person->child->parent = NULL;

        free(person);
    }
}

int main(void)
{
    struct person* adam = create_person("Adam");
    struct person* steve = create_child(adam, "Steve");
    struct person* john = create_child(steve, "John");
    struct person* jesus = create_child(john, "Jesus");
    struct person* paul = create_child(jesus, "Paul");
    struct person* kevin = create_child(paul, "Kevin");

    print_person(adam);
    print_person(john);
    print_person(jesus);
    print_person(kevin);

    erase_ancestors(john);
    
    print_person(jesus);
    print_person(kevin);
}