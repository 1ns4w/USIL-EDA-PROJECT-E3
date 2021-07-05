#ifndef __LIST_H__
#define __LIST_H__
using std::cout;
using std::endl;
template <typename T>
class List
{
    struct Node
    {
        T data;
        Node *next=nullptr;
        Node(T _data, Node *_next=nullptr):data(_data),next(_next) {}
        T getData()
        {
            return data;
        }
        void setData(T &_data)
        {
            data = _data;
        }
        Node *getNext()
        {
            return next;
        }
        void setNext(Node *_next)
        {
            next = _next;
        }
    };
    class Iterator
    {
    private:
        Node* currentNode = nullptr;
    public:
        Iterator(Node* initialNode = nullptr):currentNode(initialNode) {}
        ~Iterator()
        {
            currentNode = nullptr;
            delete(currentNode);
        }

        void setCurrentNode(Node* node)
        {
            currentNode = node;
        }
        bool hasNext()
        {
            return currentNode;
        }
        T next()
        {
            if(currentNode)
            {
                T _data = currentNode->getData();
                currentNode = currentNode->getNext();
                return _data;
            }
            else
            {
                throw "There is not next element.";
            }
        }
    };

protected:
    Node *head = nullptr;
    Node *tail = nullptr;
public:
    ~List()
    {
        clearAll();
        head = nullptr;
        tail = nullptr;
        delete(head);
        delete(tail);
    }
    void pushFront(T data);
    void pushBack(T data);
    T popFront();
    T popBack();
    bool isEmpty();
    Iterator getIterator();
    void print();
    void clearAll();
};

template <typename T>
bool List<T>::isEmpty()
{
    return !head;
}

template <typename T>
void List<T>::pushFront(T data)
{
    Node *newNode = new Node(data, head);
    if(isEmpty())
    {
        tail = newNode;
    }
    head = newNode;
}

template <typename T>
void List<T>::pushBack(T data)
{
    Node *newNode = new Node(data);
    if(isEmpty())
    {
        head = newNode;
    }
    else
    {
        tail->setNext(newNode);
    }
    tail = newNode;
}

template <typename T>
T List<T>::popFront()
{
    T data;
    if(isEmpty())
    {
        throw "The List is empty.";
    }
    else if(head == tail)
    {
        data = head->getData();
        delete(head);
        head = nullptr;
        tail = nullptr;
    }
    else
    {
        Node *temp = head;
        data = head->getData();
        head = head->getNext();
        delete(temp);
    }
    return data;
}

template <typename T>
T List<T>::popBack()
{
    T data;
    if(isEmpty())
    {
        throw "The List is empty.";
    }
    else if(head == tail)
    {
        data = head->getData();
        delete(head);
        head = nullptr;
        tail = nullptr;
    }
    else
    {
        Node *temp = head;
        while(temp && temp->getNext() != tail)
        {
            temp  = temp->getNext();
        }
        temp->setNext(nullptr);
        data = tail->getData();
        delete(tail);
        tail = temp;
    }
    return data;
}

template <typename T>
typename List<T>::Iterator List<T>::getIterator()
{
    return Iterator(head);
}

template <typename T>
void List<T>::print()
{
    Node *temp = head;
    while(temp)
    {
        cout<<temp->getData()<<" ";
        temp = temp->getNext();
    }
    cout<<endl;
}

template <typename T>
void List<T>::clearAll()
{
    while(!isEmpty())
    {
        popBack();
    }
}



#endif // __LIST_H__
