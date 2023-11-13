#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>

#define BOOKSHOP_SIZE 5

typedef struct{
    int bookID;
    char title[40];
    char author[40];
    double price;
    int quantity;
} Book;

int findLast(Book arr[], int size);
void swap(Book *, Book *);
void sortOrder(Book arr[], int size);
void toLowerCase(char str[]);
void trimWhitespace(char str[]);

void listBook(Book arr[], int size);
void addBook(Book arr[], int size);
void removeBook(Book arr[], int size);
void findBook(Book arr[], int size);
void updateBook(Book arr[], int size);

int findLast(Book arr[], int size){
    int last = 1;
    for (int i = 1; i < BOOKSHOP_SIZE; i++){
        if(arr[i].bookID != 0)
            last ++;
    }
    return last;
}

void swap(Book *a, Book *b){
    Book temp = *a;
    *a = *b;
    *b = temp;
}
void sortOrder(Book arr[], int size){
    for (int i = 1; i < size; i++) {
        for (int j = 0; j < size - i; j++) {
            if (arr[j].bookID == 0 && arr[j + 1].bookID != 0) {
                swap(&arr[j], &arr[j + 1]);
            } else if (arr[j].bookID > arr[j + 1].bookID && arr[j + 1].bookID != 0) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void toLowerCase(char str[]){
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower(str[i]);
    }
}
void trimWhitespace(char str[]){
    int start = 0, end = strlen(str) - 1;
    while (isspace(str[start])) {
        start++;
    }
    while (end > start && isspace(str[end])) {
        end--;
    }
    for (int i = 0; i <= end - start; i++) {
        str[i] = str[start + i];
    }

    str[end - start + 1] = '\0';
}

void listBook(Book arr[], int size){
    printf("listBooks(): \n");
    if (arr[0].bookID == 0) {
        printf("The bookshop is empty\n");
    }
    else{
        sortOrder(arr, size);
        int lastBookID = findLast(arr, size);

        for (int i = 0; i < lastBookID; i++) {
            if (arr[i].bookID != 0){
                printf("BookID: %d \n", arr[i].bookID);
                printf("Book title: %s \n", arr[i].title);
                printf("Author name: %s \n", arr[i].author);
                printf("Book price: %.2f \n", arr[i].price);
                printf("Quantity: %d \n", arr[i].quantity);
            }
        }
    }
}

void addBook(Book arr[], int size){
    int id, quantity;
    double price;
    char title[40];
    char author[40];
    char *p1, *p2;

    printf("addBook(): \n");
    
    printf("Enter bookID: \n");
    scanf("%d", &id);
    fflush(stdin);
    
    printf("Enter book title: \n");
    fgets(title, sizeof(title), stdin);
    if ((p1=strchr(title,'\n')) != NULL)
        *p1 = '\0';
    
    printf("Enter author name: \n");
    fgets(author, sizeof(author), stdin);
    if ((p2=strchr(author,'\n')) != NULL)
        *p2 = '\0';
    
    printf("Enter price: \n");
    scanf("%lf", &price);

    printf("Enter quantity: \n");
    scanf("%d", &quantity);
    
    if(arr[4].bookID != 0)
        printf("The bookshop is full! Unable to addBook()\n");
    else{
        for(int i = 0; i<BOOKSHOP_SIZE; i++){
            if(arr[i].bookID==id){
                printf("The bookID has already existed! Unable to addBook()\n");
                break;
            }
            if(arr[i].bookID==0){
                arr[i].bookID = id;
                strcpy(arr[i].title, title);
                strcpy(arr[i].author, author);
                arr[i].price = price;
                arr[i].quantity = quantity;
                printf("The book has been added successfully\n");
                break;
            } 
        }
    }
    sortOrder(arr, size);
}

void removeBook(Book arr[], int size){
    char target_title[40], lower_title[40];
    char target_author[40], lower_author[40];
    char *p3, *p4;
    int find = 0;

    printf("removeBook(): \n");

    printf("Enter the target book title: \n");
    fflush(stdin);
    fgets(target_title, 40, stdin);
    if ((p3 = strchr(target_title, '\n')) != NULL)
        *p3 = '\0';
    trimWhitespace(target_title);
    strcpy(lower_title, target_title);
    toLowerCase(lower_title);

    printf("Enter the target author name: \n");
    fgets(target_author, 40, stdin);
    if ((p4 = strchr(target_author, '\n')) != NULL)
        *p4 = '\0';
    trimWhitespace(target_author);
    strcpy(lower_author, target_author);
    toLowerCase(lower_author);

    if(arr[0].bookID==0)
        printf("The bookshop is empty \n");
    else{
        for (int i = 0; i < BOOKSHOP_SIZE; i++) {
            char middle_title[40];
            char middle_author[40];
            strcpy(middle_title, arr[i].title);
            strcpy(middle_author, arr[i].author);
            toLowerCase(middle_title);
            toLowerCase(middle_author);

            int comp_title = strcmp(middle_title, lower_title);
            int comp_author = strcmp(middle_author, lower_author);
            if (comp_author == 0 && comp_title == 0) {
                find = 1;
                printf("The target book is removed \n");
                printf("BookID: %d \n", arr[i].bookID);
                printf("Book title: %s \n", arr[i].title);
                printf("Author name: %s \n", arr[i].author);
                printf("Book price: %.2f \n", arr[i].price);
                printf("Quantity: %d \n", arr[i].quantity);
                arr[i].bookID = 0;
                arr[i].title[0] = '\0';
                arr[i].author[0] = '\0';
                arr[i].price = 0;
                arr[i].quantity = 0;
                break;
            }
        }

        if (!find)
            printf("The target book is not in the bookshop\n");
    }
    
}

void findBook(Book arr[], int size){
    char found_title[40], lowerTitle[40];
    char found_author[40], lowerAuthor[40];
    char *p5, *p6;
    int find = 0;

    printf("findBook(): \n");

    printf("Enter the target book title: \n");
    fgets(found_title, 40, stdin);
    if ((p5 = strchr(found_title, '\n')) != NULL)
        *p5 = '\0';
    trimWhitespace(found_title);
    strcpy(lowerTitle, found_title);
    toLowerCase(lowerTitle);

    printf("Enter the target author name: \n");
    fgets(found_author, 40, stdin);
    if ((p6 = strchr(found_author, '\n')) != NULL)
        *p6 = '\0';
    trimWhitespace(found_author);
    strcpy(lowerAuthor, found_author);
    toLowerCase(lowerAuthor);

    for (int i = 0; i < BOOKSHOP_SIZE; i++) {
        char middle_title[40];
        char middle_author[40];
        strcpy(middle_title, arr[i].title);
        strcpy(middle_author, arr[i].author);

        toLowerCase(middle_title);
        toLowerCase(middle_author);
        int comp_title = strcmp(middle_title, lowerTitle);
        int comp_author = strcmp(middle_author, lowerAuthor);
        if (comp_author == 0 && comp_title == 0) {
            find = 1;
            printf("The target book is found \n");
            printf("BookID: %d \n", arr[i].bookID);
            printf("Book title: %s \n", arr[i].title);
            printf("Author name: %s \n", arr[i].author);
            printf("Book price: %.2f \n", arr[i].price);
            printf("Quantity: %d \n", arr[i].quantity);
            break;
        }
    }
    if (!find)
        printf("The target book is not found\n");
}

void updateBook(Book arr[], int size){
    char update_title[40], Lower_title[40];
    char update_author[40], Lower_author[40];
    char *p7, *p8;
    int find = 0;

    printf("updateBook(): \n");

    printf("Enter the target book title: \n");
    fgets(update_title, 40, stdin);
    if ((p7 = strchr(update_title, '\n')) != NULL)
        *p7 = '\0';
    trimWhitespace(update_title);
    strcpy(Lower_title, update_title);
    toLowerCase(Lower_title);

    printf("Enter the target author name: \n");
    fgets(update_author, 40, stdin);
    if ((p8 = strchr(update_author, '\n')) != NULL)
        *p8 = '\0';
    trimWhitespace(update_author);
    strcpy(Lower_author, update_author);
    toLowerCase(Lower_author);

    for (int i = 0; i < BOOKSHOP_SIZE; i++) {
        char middle_title[40];
        char middle_author[40];
        strcpy(middle_title, arr[i].title);
        strcpy(middle_author, arr[i].author);

        toLowerCase(middle_title);
        toLowerCase(middle_author);
        int comp_title = strcmp(middle_title, Lower_title);
        int comp_author = strcmp(middle_author, Lower_author);
        if (comp_author == 0 && comp_title == 0) {
            find = 1;
            double updatePrice;
            int updateQuantity;
            printf("Enter updated book price: \n");
            scanf("%lf", &updatePrice);
            printf("Enter updated quantity: \n");
            scanf("%d", &updateQuantity);

            arr[i].price = updatePrice;
            arr[i].quantity = updateQuantity;
            printf("The target book is updated\n");
            printf("BookID: %d \n", arr[i].bookID);
            printf("Book title: %s \n", arr[i].title);
            printf("Author name: %s \n", arr[i].author);
            printf("Book price: %.2f \n", arr[i].price);
            printf("Quantity: %d \n", arr[i].quantity);
            break;
        }

    }
    if (!find)
        printf("The target book is not in the bookshop\n");
}

int main(){
    int choice;
    Book Lib[BOOKSHOP_SIZE] = {
    };

    printf("NTU BOOKSHOP MANAGEMENT PROGRAM: \n");
    printf("1: listBooks() \n");
    printf("2: addBook() \n");
    printf("3: removeBook() \n");
    printf("4: findBook() \n");
    printf("5: updateBook() \n");
    printf("6: quit \n");

    do{
        printf("Enter your choice: \n");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                listBook(Lib, BOOKSHOP_SIZE);
                break;
            case 2:
                addBook(Lib, BOOKSHOP_SIZE);
                break;
            case 3:
                removeBook(Lib, BOOKSHOP_SIZE);
                break;
            case 4:
                fflush(stdin);
                findBook(Lib, BOOKSHOP_SIZE);
                break;
            case 5:
                fflush(stdin);
                updateBook(Lib, BOOKSHOP_SIZE);
                break;
            case 6:
                choice = 7;
                break;
        }
    } while(choice<7);

    return 0;
}

