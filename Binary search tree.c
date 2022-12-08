/*
Author Srihari K G
CSE
210030035
Binary search tree
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct bstree
{
    struct bstree *left;
    struct bstree *right;
    int data;
} bstree;
int len = 0;
bstree *root = NULL;
FILE *ans;

void insert(int n)
{
    bstree *newnode = (bstree *)malloc(sizeof(bstree));
    newnode->left = NULL;
    newnode->data = n;
    newnode->right = NULL;

    if (root == NULL)
    {
        root = newnode;
        fprintf(ans, "%d inserted\n", root->data);
        len++;
    }

    else
    {
        bstree *current = root, *temp;
        while (current != NULL)
        {
            temp = current;
            if (current->data > newnode->data)
            {
                current = current->left;
            }

            else
            {
                current = current->right;
            }
        }
        if (temp->data > newnode->data)
        {
            temp->left = newnode;
            fprintf(ans, "%d inserted\n", newnode->data);
            len++;
        }

        else
        {
            temp->right = newnode;
            fprintf(ans, "%d inserted\n", newnode->data);
            len++;
        }
    }
}

void inorder(bstree *inptr)
{

    int i = 0;

    if (inptr != NULL)
    {
        inorder(inptr->left);
        fprintf(ans, "%d ", inptr->data);
        inorder(inptr->right);
    }
}
int GlobalIndex = 0;
int create_inorder_array(int a[], bstree *ptr, int i)
{
    if (ptr == NULL)
        return i;

    i = create_inorder_array(a, ptr->left, i);

    a[i++] = ptr->data;
    create_inorder_array(a, ptr->right, i);
}
void postorder(bstree *postptr)
{

    if (postptr != NULL)
    {
        postorder(postptr->left);
        postorder(postptr->right);
        fprintf(ans, "%d ", postptr->data);
    }
}

void preorder(bstree *preptr)
{

    if (preptr != NULL)
    {
        fprintf(ans, "%d ", preptr->data);
        preorder(preptr->left);
        preorder(preptr->right);
    }
}
void search(int n)
{
    bstree *srch = root;
    if (len == 0)
    {
        fprintf(ans, "%d not found\n", n);
        return;
    }
    while (srch != NULL)
    {
        if (n == srch->data)
        {

            fprintf(ans, "%d found\n", n);
            return;
        }
        else if (n < srch->data)
            srch = srch->left;

        else
            srch = srch->right;

        if (srch == NULL)
            fprintf(ans, "%d not found\n", n);
    }
}

void minimum(bstree *minm)
{
    if (len == 0)
    {
        fprintf(ans, "\n");
        return;
    }
    while (minm->left != NULL)
    {
        minm = minm->left;
    }
    fprintf(ans, "%d\n", minm->data);
}

void maximum(bstree *maxm)
{
    if (len == 0)
    {
        fprintf(ans, "\n");
        return;
    }
    while (maxm->right != NULL)
    {
        maxm = maxm->right;
    }
    fprintf(ans, "%d\n", maxm->data);
}

void pred(int n)
{
    if (len == 0)
    {
        fprintf(ans, "%d does not exist\n", n);
        return;
    }
   
  
    int i = 0;
    int a[len];
    for (i = 0; i < len; i++)
        a[i] = -123;

    create_inorder_array(a, root, 0);
 if(n==a[0])
   {
        fprintf(ans, "predecessor of %d does not exist\n", n);
        return;
    }
    int found = 0;
    bstree *srch = root;
    while (srch != NULL)
    {
        if (n == srch->data)
        {
            found = 1;
            break;
        }
        else if (n < srch->data)
            srch = srch->left;

        else
            srch = srch->right;

        if (srch == NULL)
            found = 0;
    }
    if (found == 1)
    {
        if (a[0] == n)
        {
            fprintf(ans, "%d does not exist\n", n);
        }

        else
        {
            int suc = -1;
            int k = 0;
            for (k = 0; k < len; k++)
            {
                if (a[k] == n)
                {
                    suc = a[k - 1];
                    break;
                }
            }

            fprintf(ans, "%d\n", suc);
        }
    }

    else
        fprintf(ans, "%d does not exist\n", n);
}

void succ(int n)
{

    if (len == 0)
    {
        fprintf(ans, "%d does not exist\n", n);
        return;
    }
    int i = 0;
    int a[len];
    for (i = 0; i < len; i++)
        a[i] = -123;

    create_inorder_array(a, root, 0);
 if(n==a[len-1])
   {
        fprintf(ans, "successor of %d does not exist\n", n);
        return;
    }
    int found = 0;
    bstree *srch = root;
    while (srch != NULL)
    {
        if (n == srch->data)
        {
            found = 1;
            break;
        }
        else if (n < srch->data)
            srch = srch->left;

        else
            srch = srch->right;

        if (srch == NULL)
            found = 0;
    }
    if (found == 1)
    {
        if (a[len - 1] == n)
        {
            fprintf(ans, "%d does not exist\n", n);
        }

        else
        {
            int suc = -1;
            int k = 0;
            for (k = 0; k < len; k++)
            {
                if (a[k] == n)
                {
                    suc = a[k + 1];
                    break;
                }
            }

            fprintf(ans, "%d\n", suc);
        }
    }

    else
        fprintf(ans, "%d does not exist\n", n);
}

int main(int argc, char *argv[])
{

    FILE *open;
    open = fopen(argv[1], "r");
    ans = fopen("bst.txt", "w");
    char ch[100];
    while (fscanf(open, "%s ", &ch) != EOF)
    {
        int num;

        if (strcmp(ch, "insert") == 0)
        {
            fscanf(open, "%d", &num);
            insert(num);
        }

        else if (strcmp(ch, "inorder") == 0)
        {
            fscanf(open, "%d", &num);
            if (root == NULL)
            {
                fprintf(ans, "\n");
            }
            else
            {
                inorder(root);
                fseek(ans, -1, SEEK_CUR);
                fprintf(ans, "\n");
            }
        }
        else if (strcmp(ch, "preorder") == 0)
        {
            if (root == NULL)
            {
                fprintf(ans, "\n");
            }
            else
            {
                preorder(root);
                fseek(ans, -1, SEEK_CUR);
                fprintf(ans, "\n");
            }
        }

        else if (strcmp(ch, "postorder") == 0)
        {
            if (root == NULL)
            {
                fprintf(ans, "\n");
            }
            else
            {
                postorder(root);
                fseek(ans, -1, SEEK_CUR);
                fprintf(ans, "\n");
            }
        }

        else if (strcmp(ch, "search") == 0)
        {
            fscanf(open, "%d", &num);
            search(num);
        }

        else if (strcmp(ch, "minimum") == 0)
        {
            fscanf(open, "%d", &num);
            minimum(root);
        }

        else if (strcmp(ch, "maximum") == 0)
        {
            fscanf(open, "%d", &num);
            maximum(root);
        }

        else if (strcmp(ch, "successor") == 0)
        {
            fscanf(open, "%d", &num);

            succ(num);
        }
        else if (strcmp(ch, "predecessor") == 0)
        {
            fscanf(open, "%d", &num);
            pred(num);
        }
    }
}
