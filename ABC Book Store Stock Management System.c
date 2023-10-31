#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    char bname[20];
    char genre[20];
    int quantity;
    int price;
    struct node *left,*right;
};
struct list{
    char genre[20];
    struct list *next;
};
struct lisrt *list_start=NULL;
struct node *start=NULL;
void insert(struct node *root, struct node *newData);
void removing(struct node *parent, struct node *root);
void update(struct node *parent,struct node*root);
void search(struct node *parent,struct node *root, char name[20],int removal);
void display_in(struct node *root);
void main(){
    int passcnt=0;
    char pass[]="2CS301";
    do{
        printf("\n\n\t******* Welcome to ABC Book Store Stock Management System *******\n\n");
        printf("Enter password to continue (Hint: course code) : ");
        char pword[7];
        scanf("%s",pword);
        int n=0;
        if(strcmpi(pass,pword)==0){
            printf("Password correct! Lets continue : ");
            passcnt=3;
            system("CLS");
            do{
                printf("\n\t******* Welcome to ABC Book Store Stock Management System *******\n");
                printf("\n\t\tEnter operation to be performed:\n");
                printf("\t\t1. To add stock");
                printf("\n\t\t2. To delete stock");
                printf("\n\t\t3. To update stock");
                printf("\n\t\t4. To search stock");
                printf("\n\t\t5. To display stock");
                printf("\n\t\t6. To display stock of specific category");
                printf("\n\t\t7. To Logout of system.\n");
                scanf("%d",&n);
                switch(n){
                case 1:
                    addition();
                    break;
                case 2:
                    removeBook();
                    break;
                case 3:
                    updateBook();
                    break;
                case 4:
                    searchBook();
                    break;
                case 5:
                    system("CLS");
                    display(start);
                    break;
                case 6:
                    category();
                    break;
                case 7:
                    system("CLS");
                    printf("\n\t***** Thank you for your operations! Logging out of system *****\n\n");
                    printf("\t\t\t\t\t\t               19BEC057\n");
                    break;
                default:
                    printf("\n\t\tEnter a correct option\n");
                }
            }while(n!=7);
        }
        if(n!=7){
            passcnt++;
            int x=3-passcnt;
            printf("Wrong password! Attempt left : %d",x);
            if(passcnt==3){
                printf("\n\tThis was your last attempt!");
            }
        }
    }while(passcnt!=3);
}

void addition(){
    system("CLS");
    int flag=1;
    do{
        insertion();
        flag=0;
        printf("\nStock added successfully.\n");
        printf("\n Do you want to add another stock? Enter 1 : ");
        scanf("%d",&flag);
    }while(flag==1);
}
void insertion(){
    char s[20],g[20];
    int n,p;
    printf("\nEnter Book Name : ");
    scanf("%s",s);
    printf("Enter Category : ");
    scanf("%s",g);
    printf("Enter quantity : ");
    scanf("%d",&n);
    printf("Enter price : ");
    scanf("%d",&p);
    struct node *newData;
    newData=(struct node*)malloc(sizeof(struct node));
    newData->right=NULL;
    newData->left=NULL;
    newData->price=p;
    newData->quantity=n;
    strcpy(newData->bname,s);
    strcpy(newData->genre,g);
    insert_list(g);
    insert(start,newData);

}
void insert(struct node *root,struct node *newData){

    if(start==NULL){
        start=newData;
    }
    else if(strcmpi(newData->bname,root->bname)==0)
    {
        root->quantity+=newData->quantity;
        root->price=newData->price;
    }
    else if(strcmpi(newData->bname,root->bname)<0 && root->left==NULL){
        root->left=newData;
    }

    else if(strcmpi(newData->bname,root->bname)<0 && root->left!=NULL){
        insert(root->left,newData);
    }

    else if(strcmpi(newData->bname,root->bname)>0 && root->right==NULL){
        root->right=newData;
    }

    else if(strcmpi(newData->bname,root->bname)>0 && root->right!=NULL){
        insert(root->right,newData);
    }
}
void insert_list(char cat[20]){
    struct list *newdata=(struct list*)malloc(sizeof(struct list));
    strcpy(newdata->genre,cat);
    newdata->next=NULL;
    if(list_start==NULL)
        list_start=newdata;
    else{
        int flag=0;
        struct list *temp=list_start;
        while(temp->next!=NULL){
            if(strcmpi(temp->genre,cat)==0) flag=1;
                temp=temp->next;
        }
        if(flag==0 && strcmpi(temp->genre,cat)!=0){
            temp->next=newdata;
        }
    }
}

void updateBook(){
    system("CLS");
    int flag=1;
    do{
        char bookName[20];
        printf("\nEnter book name for stock to be updated : ");
        scanf("%s",bookName);
        search(NULL,start,bookName,2);
        flag=0;
        printf("\n Do you want to update another stock? Enter 1 : ");
        scanf("%d",&flag);
    }while(flag==1);
}
void update(struct node *parent,struct node*root){
    if(root!=NULL){
        printf("\nCurrent book stock:\n");
        temp_display();
        display_out(root);
        int n;
        printf("\nDo you want to update book name? Enter 1 : ");
        scanf("%d",&n);
        if(n==1){
            char nname[20];
            printf("\nEnter new book name to update : ");
            scanf("%s",nname);
            strcpy(root->bname,nname);
            printf("\nBook name updated\n");
        }
        printf("\nDo you want to update category? Enter 1 : ");
        scanf("%d",&n);
        if(n==1){
            char nname[20];
            printf("\nEnter new category of book to update : ");
            scanf("%s",nname);
            strcpy(root->genre,nname);
            printf("\nBook genre updated\n");
        }
        printf("\nDo you want to update quantity of book? Enter 1 :");
        scanf("%d",&n);
        if(n==1){
            int flag,q;
            printf("\n Enter operation to perform : ");
            printf("\n1. Addition of quantity.");
            printf("\n2. Removal of quantity.");
            printf("\nEnter the choice : ");
            scanf("%d",&flag);
            switch(flag){
            case 1:
                printf("\nEnter more quantity to be added : ");
                scanf("%d",&q);
                root->quantity+=q;
                printf("\nQuantity of book updated.");
                break;
            case 2:
                printf("\nEnter quantity to be removed : ");
                scanf("%d",&q);
                if(root->quantity-q>0){
                    root->quantity-=q;
                    printf("\nQuantity of book updated.");
                }
                else if(root->quantity-q==0){
                    root->quantity=0;
                    printf("\nQuantity of book updated. As quantity is 0 stock is removed.");
                    search(parent,root,root->bname,1);
                    return;
                }
                else{
                    printf("\nQuantity cannot be updated as you do not have required stock!");
                }
            }
        }
        printf("\n\nDo you want to update price of book? Enter 1 :");
        scanf("%d",&n);
        if(n==1){
            int q;
            printf("\nEnter new price of book to update : ");
            scanf("%d",&q);
            root->price=q;
            printf("Book price updated\n");
        }
        printf("\n\n\t\t Updated Book Stock:\t\n\n");
        temp_display();
        display_out(root);
    }
}

void removeBook(){
    system("CLS");
    int flag=1;
    do{
        char bookName[20];
        printf("\nEnter book name for stock to be removed : ");
        scanf("%s",bookName);
        search(NULL,start,bookName,1);
        flag=0;
        printf("\n Do you want to remove another stock? Enter 1 : ");
        scanf("%d",&flag);
    }while(flag==1);
}
void removing(struct node *parent, struct node *root){
    strcpy(root->genre,"NULL");
    printf("\n Stock deletion completed\n");
}

void searchBook(){
    system("CLS");
    int flag=1;
    do{
        char bookName[20];
        printf("\nEnter book name for stock to be searched : ");
        scanf("%s",bookName);
        search(NULL,start,bookName,0);
        flag=0;
        printf("\n Do you want to search another stock? Enter 1 : ");
        scanf("%d",&flag);
    }while(flag==1);
}
void search(struct node *parent, struct node *root,char book[20],int removal){

    if(start==NULL){
        printf("\nNo book found!\n\n");
    }

    if(strcmpi(book,root->bname)==0){
            if(removal==1){
                removing(parent,root);
                return;
            }
            else if(removal==2){
                update(parent,root);
                return;
            }
            printf("\n");
        temp_display();
        display_out(root);
    }

    else if(strcmpi(book,root->bname)<0 && root->left==NULL){
        printf("\nNo book found!\n\n");
    }

    else if(strcmpi(book,root->bname)<0 && root->left!=NULL){
        search(root,root->left,book,removal);
    }

    else if(strcmpi(book,root->bname)>0 && root->right==NULL){
        printf("\nNo book found!\n\n");
    }

    else if(strcmpi(book,root->bname)>0 && root->right!=NULL){
        search(root,root->right,book,removal);
    }
}

void display(struct node *root){
    if(root==NULL){
        printf("\nNo book found\n");
        return;
    }
    temp_display();
    display_in(root);
}
void temp_display(){
    printf("Book Name:\tCategory:\tQuantity:\tPrice:\t\n");
}
void display_in(struct node *root){
    if(root==NULL){
        return;
    }
    display_in(root->left);
    if(strcmpi(root->genre,"NULL")!=0)
    display_out(root);
    display_in(root->right);
}
void display_out(struct node *root){
    printf("\n%-16s%-16s%-16d%-16d\t\t\n",root->bname,root->genre,root->quantity,root->price);
}

void category(){
    system("cls");
    int flag=1;
    do{
        printf("\n Category list \n");
        genreList();
        char cat[20];
        printf("\nEnter which category of books are to be displayed : ");
        scanf("%s",cat);
        printf("\nBooks of category %s \n\n",cat);
        temp_display();
        display_genre(start,cat);
        flag=0;
        printf("\nDo you want to display another category? Enter 1 : ");
        scanf("%d",&flag);
    }while(flag==1);
}
void genreList(){
    if(list_start==NULL){
        return;
    }
    struct list *temp=list_start;
    while(temp!=NULL){
        printf("%s\n",temp->genre);
        temp=temp->next;
    }
}
void display_genre(struct node *root,char genre[20]){
    if(root==NULL)
        return;
    display_genre(root->left,genre);
    if(strcmpi(root->genre,genre)==0)
        display_out(root);
    display_genre(root->right,genre);
}
