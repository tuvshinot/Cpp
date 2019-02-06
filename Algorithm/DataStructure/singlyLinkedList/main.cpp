#include <iostream>

using namespace std;

struct node
{
    int data;
    node *next;
};

class linked_list
{
public:
    node *head,*tail;
    linked_list()
    {
        head = NULL;
        tail = NULL;
    }

    void add_node(int n)
    {
        node *tmp = new node;
        tmp->data = n;
        tmp->next = NULL;

        if(head == NULL)
        {
            head = tmp;
            tail = tmp;
        }
        else
        {
            tail->next = tmp;
            tail = tail->next;
        }
    }
    
    node get_node(int index)
    {
        node *tmp = new node;
        tmp->data = n;
        tmp->next = NULL;

        if(head == NULL)
        {
            head = tmp;
            tail = tmp;
        }
        else
        {
            tail->next = tmp;
            tail = tail->next;
        }
    }
};

int main()
{
    linked_list a;
    a.add_node(1);
    a.add_node(2);
    a.add_node(3);
    a.add_node(4);
    a.add_node(5);
    
    std::cout << a.head->data; << endl;
    
    
    
    return 0;
}