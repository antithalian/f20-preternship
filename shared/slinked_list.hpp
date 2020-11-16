// slinked_list.h
// implements a templated singly linked list
// based on Professor Morrison's singly linked list from class

#ifndef SLINKED_H
#define SLINKED_H

#include <cstddef>

template<class T>
class slinked_list
{
  private:
    // list node data and pointer to next node
    // plus constructors and operators
    struct node
    {
        // data and next
        T data;
        node* next;

        // default constructor
        // up to user not to use this when they shouldn't
        node()
          : data()
          , next(NULL)
        {}

        // data input constructor
        node(T indata)
          : data(indata)
          , next(NULL)
        {}

        // copy constructor
        node(const node& copy)
        {
            data = copy.data;
            next = copy.next;
        }

        // node destructor
        // recursively deletes nodes down the list
        ~node()
        {
            delete next;
        }

        // operators
        // reference operator=
        node& operator=(const node& assign)
        {
            // if this and assign aren't the same, copy over the values
            if (this != &assign)
            {
                this->data = assign.data;
                this->next = assign.next;
            }

            return *this;
        }

        // pointer operator=
        node* operator=(const node* assign)
        {
            // if this and assign aren't the same, copy values
            if (this != (void*)&assign)
            {
                this->data = assign->data;
                this->next = assign->next;
            }

            return *this;
        }

        // pointer operator!=
        bool operator!=(const node* right)
        {
            return this != (void*)&right;
        }
    };

    // also need a head pointer for the whole list
    node* head;

  public:
    // linked list default constructor
    slinked_list()
      : head(NULL)
    {}

    // linked list copy constructor
    slinked_list(const slinked_list<T>& copy)
      : head(NULL)
    {
        // get head
        node* curr = copy.head;

        // iterate through and assign data and pointers
        while (NULL != curr)
        {
            insert(curr->data);
            curr = curr->next;
        }
    }

    // linked list destructor
    ~slinked_list()
    {
        delete head;  // recursive node deletion
    }

    // assignment operator
    slinked_list<T>& operator=(const slinked_list<T>& assign)
    {
        // is this me check
        if (this != &assign)
        {
            node* prev = NULL;
            node* curr = NULL;

            // iterate through, inserting
            while (NULL != curr)
            {
                this->insert(curr->data);

                // update pointers
                prev = curr;
                curr = curr->next;
            }
        }

        return *this;
    }

    // helper and other functions

    // insert item at end of list
    void insert(T value)
    {
        node* temp = new node(value);

        if (is_empty())
        {
            head = temp;
        }
        else
        {
            node* prev = NULL;
            node* curr = head;

            // find end of list
            while (NULL != curr)
            {
                prev = curr;
                curr = curr->next;
            }

            // insert node
            prev->next = temp;
        }
    }

    // push item onto front of list
    void push_front(T value)
    {
        node* temp = new node(value);

        // set up pointers
        temp->next = head;
        head = temp;
    }

    // delete target data (first instance, specifically - do a contains check afterwards if you want all)
    bool del(T target)
    {
        node* temp = new node();
        node* prev = new node();
        node* curr = new node();

        if (is_empty())
        {
            return false;
        }
        // handle first in list
        else if (target == head->data)
        {
            temp = head;
            head = head->next;
            delete (temp);
            return true;
        }
        // handle other options by traversing
        else
        {
            prev = head;
            curr = head->next;

            // traversal
            while ((NULL != curr) && (curr->data != target))
            {
                prev = curr;
                curr = curr->next;
            }

            if (NULL != curr)
            {
                // delete node with target value
                temp = curr;
                prev->next = curr->next;
                delete (temp);
                return true;
            }
            else
            {
                // not in list, so false
                return false;
            }
        }
    }

    // pop front element from list
    bool pop_front()
    {
        // check if empty
        if (is_empty())
        {
            return false;
        }
        // otherwise pop
        else
        {
            // node* temp = head;
            head = head->next;
            // delete(temp);
            return true;
        }
    }

    // get what's in front
    T front() const
    {
        return head->data;
    }

    // check if empty
    bool is_empty() const
    {
        return NULL == head;
    }

    // check if element is contained in list
    bool contains(const T& target) const
    {
        // emptiness check
        if (is_empty())
        {
            return false;
        }
        else
        {
            node* prev = NULL;
            node* curr = head;

            // traverse
            while ((NULL != curr) && (curr->data != target))
            {
                prev = curr;
                curr = curr->next;
            }

            return NULL != curr;
        }
    }
};

#endif