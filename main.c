
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

struct student{
    char /* firstName[60]*/ *firstName;
    char/*lastName[50]*/ *lastName;
    unsigned int matrikelNummer;
    char/*Adresse[60] */ *Adresse;
    unsigned int n;
    struct student* next;
    struct student* prev;
};

struct student* studentAlloc(){
    struct student* a= (struct student*) malloc(sizeof(struct student));
    if (a==NULL) printf("\n*******ERROR at studentAlloc*******\n");
    return a;
};

void studentInit(struct student* a, char* fname, char* lname, size_t mnum, char* ad, size_t n ){
    (a->firstName=fname);
    //strcpy(a->firstName,fname);
    (a->lastName=lname);
    //strcpy(a->lastName,lname);
    a->matrikelNummer = mnum;
    (a->Adresse=ad);
    //strcpy(a->Adresse,ad);
    a->n = n;
}

void printStudent(struct student* a){
    printf("{ %10s , %15s, %8u, %40s, %3u }\n",a->firstName,a->lastName,a->matrikelNummer,a->Adresse,a->n);
}

void printList(struct student *a){
    while(a!=NULL){
        printStudent(a);
        a=a->next;
    }
}

void add(struct student *begin, struct student *a){
    while(begin->next!=NULL){
        begin = begin->next;
    }
    begin->next=a;
    a->prev = begin;
    a->next = NULL;
}

struct student* getToFront(struct student *a){
    while((a->prev)!=NULL){
        a=a->prev;
    }
    return a;
}

struct student* delete(struct student* begin, struct student* a){
    if(a->prev == NULL){
             begin=begin->next;
             a->next->prev= a->prev;
    }else if(a->next==NULL){
            (a->prev)->next = NULL;
    }else{
        a->next->prev = a->prev;
        a->prev->next = a->next;
    }

    free(a);
    return begin;

}

struct student* reverse(struct student* begin){

    struct student* next = NULL;
    struct student* prev = NULL;

    while (begin != NULL){
            next = begin -> next;
            begin -> next = prev;
            prev = begin ;
            begin = begin->next;

    }
    return prev;
}

struct student* swap(struct student *a,struct student *b){
    struct student* temp;

    if(a->prev != NULL) a->prev->next = b;
    if (b->next != NULL) b->next->prev =a;
    if (a->next != b){
        a->next->prev = b;
        b->prev->next = a;
        temp = a->prev;
        a->prev = b->prev;
        b->prev = temp;
        temp = a->next;
        a->next = b->next;
        b->next = temp;
    }
   if(a->next == b){
        temp = b->next;
        b->next = a;
        a->next = temp;
        temp = a->prev;
        b->prev = a->prev;
        a->prev = b;
   }
return a;
}

int main()
{
    struct student *a = studentAlloc();
    studentInit(a,"Anna","Musterfrau",22222,"Am Schwarzenberg-Campus 3",4);
    a->prev = NULL;
    //a->next = studentAlloc();
    //(a->next)->prev = a;
    //a=a->next;
    a->next = NULL; //

    struct student* hans = studentAlloc();
    studentInit(hans,"Hans","Peter",44444,"Kasernenstrasse 12",2);
    add(a,hans);

    struct student* lisa = studentAlloc();
    studentInit(lisa,"Lisa","Lustig",66666,"Denickestrasse 15",8);
    add(a,lisa);

    /*
    studentInit(a,"Hans","Peter",44444,"Kasernenstrasse 12",2);
    a->next = studentAlloc();
    (a->next)->prev = a;
    a=a->next;

    studentInit(a,"Lisa","Lustig",66666,"Denickestrasse 15",8);
    a->next = NULL;
*/
    struct student* begin = getToFront(a);
    printList(begin);

    printf("\n\n********SWAPPING 1ST AND 3RD OBJS***************\n\n"),
    begin = getToFront(swap(begin,begin->next->next));
    printList(begin);

    printf("\n\n***********ADDING TWO MORE OBJS*****************\n\n");
    struct student* sushan = studentAlloc();
    studentInit(sushan,"Sushan","Gurung",88888,"Hamburg 23",15);
    add(a,sushan);


    struct student* sudip = studentAlloc();
    studentInit(sudip,"Sudip","Gurung",777777,"Hamburg 22763",0);
    add(a,sudip);
    printList(begin);

    /*
    printf("\n\n********SWAPPING 2ND AND 3RD OBJS***************\n\n"),
    begin = getToFront(swap(begin->next,begin->next->next));
    printList(begin);*/

    //delete 3.rd
    begin=delete(begin,begin->next->next);
    printf("\n\n*****************DELETING 3RD OBJ***************\n\n");
    printList(begin);

    printf("\n\n*********************REVERSE********************\n\n");
    begin = reverse(begin);
    printList(begin);


    free(a);
    free(hans);
    free(lisa);
    free(sushan);
    free(sudip);
    return 0;
}
