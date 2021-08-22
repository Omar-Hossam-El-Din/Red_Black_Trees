#include<stdio.h>                                //Omar Hossam Eldin Ebraheem_6667
#include<stdlib.h>
#include <string.h>                              //Loay Hesham Mohamed_6439
#define RED   'R'
#define BLACK 'B'                                //Karim Mohamed El Baroudy_6424
typedef struct Node
{
    char* word;
    char color;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;
struct Node  T_Nil_Node;
Node* T_Nil = &T_Nil_Node;
Node* Root = NULL;
Node* newNode(char* word)
{
    Node* temp= (Node*) malloc(sizeof(Node));
    temp->word=malloc(strlen(word)+1);
    strcpy(temp->word,word);
    temp->color  = RED;
    temp->left   = NULL;
    temp->right  = NULL;
    temp->parent = NULL;
    return temp;
}
void rotateLeft( Node** T, Node* x)
{
    Node *y  = x->right;
    x->right = y->left;
    if (y->left != T_Nil)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == T_Nil)
        *T = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left   = x;
    x->parent = y;
}
void rotateRight(Node** T, Node* y)
{
    Node *x  = y->left;
    y->left  = x->right;
    if (x->right != T_Nil)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == T_Nil)
        *T = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left  = x;
    x->right  = y;
    y->parent = x;
}
void redBlackInsertFixup(Node** Root, Node* New)
{
    Node* temp;
    while (New->parent->color == RED)
    {
        if (New->parent == New->parent->parent->left)
        {
            temp = New->parent->parent->right;
            if (temp->color == RED)
            {
                New->parent->color = BLACK;
                temp->color = BLACK;
                New->parent->parent->color = RED;
                New = New->parent->parent;
            }
            else
            {
                if (New == New->parent->right)
                {
                    New = New->parent;
                    rotateLeft(Root, New);
                }
                New->parent->color = BLACK;
                New->parent->parent->color = RED;
                rotateRight(Root, New->parent->parent);
            }
        }
        else
        {
            temp = New->parent->parent->left;
            if (temp->color == RED)
            {
                New->parent->color = BLACK;
                temp->color = BLACK;
                New->parent->parent->color = RED;
                New = New->parent->parent;
            }
            else
            {
                if (New == New->parent->left)
                {
                    New = New->parent;
                    rotateRight(Root, New);
                }
                New->parent->color = BLACK;
                New->parent->parent->color = RED;
                rotateLeft(Root, New->parent->parent);
            }
        }
    }
    Root[0]->color = BLACK;
}
void redBlackInsert(Node** T,char* word)
{
    Node* z =  newNode(word);
    Node* y =  T_Nil;
    Node* x = *T;

    while (x != T_Nil)
    {
        y = x;
        if (strcasecmp(z->word,x->word)<0)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == T_Nil)
        *T = z;
    else if (strcasecmp(z->word,y->word)<0)
        y->left  = z;
    else
        y->right = z;

    z->left  = T_Nil;
    z->right = T_Nil;
    z->color = RED;

    redBlackInsertFixup(T, z);
}
int MAX(int a, int b)
{
    return a>b?a:b;
}
int height(Node* Root)
{
    int h = 0;

    if (Root != T_Nil)
    {
        if (Root == T_Nil)
            h = 1;
        else
        {
            int leftHeight  = height(Root->left);
            int rightHeight = height(Root->right);
            h = MAX(leftHeight, rightHeight) + 1;
        }
    }

    return h;
}
int getSize(struct Node* root)
{
    if ( root == T_Nil)
        return 0;
    else
        return 1 +getSize(root->left)+getSize(root->right);
}
void printTree(Node* root)
{
    if (root->left != T_Nil)
        printTree(root->left);
    printf("%s ", root->word);
    if (root->right != T_Nil)
        printTree(root->right);
}
struct Node* search(Node* root,char* word)
{
    if (root ==NULL ||strcasecmp(root->word,word)==0)

        return root;

    if (strcasecmp(root->word,word)<0)

        return search(root->right,word);

    return search(root->left,word);
}
int main()
{
    Node* Root = T_Nil;
    FILE* fp=fopen("EN-US-Dictionary.txt","r");
    if (fp == NULL)
    {
        printf("FILE DOES NOT EXIST \n");
        exit(1);
    }
    printf("Dictionary Loaded Successfully...!\n");
    char word[100];
    char str[100];
    while(!feof(fp))
    {
        fscanf(fp,"%s",word);
        redBlackInsert(&Root,word);
    }
    printf("-----------------------------------------\n");
    while(1)
    {
        printf("TREE HEIGHT = %d\n",height(Root));
        printf("TREE SIZE = %d\n",getSize(Root));
        printf("-----------------------------------------\n");
        printf("#1 SEARCH FOR A WORD IN THE DICTIONARY\n");
        printf("#2 INSERT A NEW WORD TO THE DICTIONARY\n");
        printf("#3 EXIT THE PROGRAM\n");
        int x;
        printf("-----------------------------------------\n");
        printf("ENTER YOUR OPTION: ");
        scanf("%d",&x);
        switch(x)
        {
        case 1:
            printf("ENTER A WORD TO SEARCH FOR: ");
            scanf("%s",str);
            if(search(Root,str)==NULL)
                printf("NOT FOUND \n");
            else
                printf("FOUND  \n");
            break;
        case 2:
            printf("ENTER A WORD TO INSERT: ");
            scanf("%s",str);
            if(search(Root,str)==NULL)
            {
                redBlackInsert(&Root,str);
                FILE* fp=fopen("EN-US-Dictionary.txt","a+");
                fprintf(fp,"\n");
                fprintf(fp,"%s",str);
                fclose(fp);
                printf("SUCCESFULLY INSERTED \n");
            }
            else
                printf("THE WORD %s ALREADY EXISTED\n",str);
            break;
        case 3:
            printf("----------------THANK YOU----------------\n");
            exit(0);
        }
        printf("-----------------------------------------\n");
    }
}
