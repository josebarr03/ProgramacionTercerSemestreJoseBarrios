## Header (.h)
``` c++
#ifndef DLLIST_H  
#define DLLIST_H  
  
#include <iostream>  
#include <utility>  
  
template <typename Object>  
class DLList  
{  
private: // Se inician los valores privados  
    struct Node  
    {  
        Object data;  
        Node *next;  
        Node *prev;  
  
        Node(const Object &d = Object{}, Node *n = nullptr, Node *p = nullptr) // Constructor copia  
                : data{d}, next{n}, prev{p} {}  
  
        Node(Object &&d, Node *n = nullptr, Node *p = nullptr) // Constructor referencia  
                : data{std::move(d)}, next{n}, prev{p} {}  
    };  
  
public: // Inicializan valores públicos  
    class iterator  
    {  
    public:  
        iterator() : current{nullptr} {} // Constructor, declara nulo para que no apunte algo random  
  
        Object &operator*() // Se comprueba el contenido del puntero, si el igual a nulo da error lógico  
        {  
            if(current == nullptr)  
                throw std::logic_error("Trying to dereference a null pointer.");  
            return current->data;  
        }  
  
        iterator &operator++() // Sirve para ir avanzando, pero si la posición es un extremo da error lógico  
        {  
            if(current)  
                current = current->next;  
            else  
                throw std::logic_error("Trying to increment past the end.");  
            return *this;  
        }  
  
        iterator operator++(int) // Se determina el momento en que se usa el "++"" por su posición  
        {  
            iterator old = *this;  
            ++(*this);  
            return old;  
        }  
  
        iterator &operator--() // Sirve para ir avanzando, pero si la posición es un extremo da error lógico  
        {  
            if(current)  
                current = current->prev;  
            else  
                throw std::logic_error("Trying to decrease past the beginning.");  
            return *this;  
        }  
  
        iterator operator--(int) // Se determina el momento en que se usa el "++"" por su posición  
        {  
            iterator old = *this;  
            --(*this);  
            return old;  
        }  
  
        iterator &operator+(int addition)  
        {  
            for(int i = 0; i<addition;i++){  
                ++(*this);  
            }  
            return  *this;  
        }  
  
        bool operator==(const iterator &rhs) const // Si "operator" es igual a "(const iterator &rhs) const" regresa verdadero  
        {  
            return current == rhs.current;  
        }  
  
        bool operator!=(const iterator &rhs) const // Si "operator" es diferente a "(const iterator &rhs) const" regresa verdadero  
        {  
            return !(*this == rhs);  
        }  
  
    protected:  
        Node *current;  
        iterator(Node *p) : current{p} {}  
        friend class DLList<Object>;  
  
        Object & retrieve() const  
        {  
            return current->data;  
        }  
    };  
  
public:  
    DLList()  
    {  
        init();  
    }  
  
    ~DLList() // Se declara el destructor que elimina el inicio y la cola  
    {  
        clear();  
        delete head;  
        delete tail;  
    }  
  
    iterator begin() { return {head->next}; } // Se obtiene el inicio y final de la lista  
    iterator end() { return {tail}; }  
  
    int size() const { return theSize; } // En el primero se obtiene el tamaño y en el segundo y regresa verdadero si está vacío  
    bool empty() const { return size() == 0; }  
  
    void clear() { while (!empty()) pop_front(); } // Se usa mientras hay elementos en la lista  
  
    Object &front() // Si no hay objetos da error lógico  
    {  
        if(empty())  
            throw std::logic_error("List is empty.");  
        return *begin();  
    }  
  
    void push_front(const Object &x) // Pone objetos al inicio, el primero con copia y el segundo con referencia  
    {  
        insert(begin(), x);  
    }  
  
    void push_front(Object &&x)  
    {  
        insert(begin(), std::move(x));  
    }  
  
    void push_back(const Object &x)  
    {  
        insert(end(), x);  
    }  
  
    void push_back(Object &&x)  
    {  
        insert(end(), std::move(x));  
    }  
  
    void pop_front() // Borra el dato inicial  
    {  
        if(empty())  
            throw std::logic_error("List is empty.");  
        erase(begin());  
    }  
  
    iterator insert(iterator itr, const Object &x) // Se inserta el dato hacia donde apunta el iterador  
    {  
        Node *p = itr.current;  
        theSize++;  
        return {p->prev = p->prev->next = new Node{x, p, p->prev}};  
    }  
  
    iterator insert(iterator itr, Object &&x) // Se mueve un dato a donde apunta el iterador.  
    {  
        Node *p = itr.current;  
        theSize++;  
        return {p->prev = p->prev->next = new Node{std::move(x), p, p->prev}};  
    }  
  
    void insert(int pos, const Object &x)  
    {  
        insert(get_iterator(pos), x);  
    }  
  
    iterator get_iterator(int a)  
    {  
        iterator it = begin();  
        for(int i = 0; i != a; ++i)  
        {  
            ++it;  
        }  
        return it;  
    }  
  
    iterator erase(iterator itr) // Se usa el "erase" para borrar hacia donde apunta el iterador  
    {  
        if (itr == end())  
            throw std::logic_error("Cannot erase at end iterator");  
        Node *p = itr.current;  
        iterator returnValue(p->next);  
        p->prev->next = p->next;  
        p->next->prev = p->prev;  
        delete p;  
        theSize--;  
  
        return returnValue;  
    }  
  
    void erase(int pos)  
    {  
        erase(get_iterator(pos));  
    }  
  
    void print() // De forma cíclica se imprime el primer término mientras avanza hasta el final  
    {  
        iterator itr = begin();  
        while (itr != end())  
        {  
            std::cout << *itr << " ";  
            ++itr;  
        }  
        std::cout << std::endl;  
    }  
  
protected: // Se inicializa de forma privada el nodo de inicio y de cola, así mismo el tamaño  
    Node *head;  
    Node *tail;  
    int theSize;  
    void init()  
    {  
        head = new Node;  
        tail = new Node;  
        theSize = 0;  
  
        head->next = tail;  
        head->prev = nullptr;  
  
        tail->prev = head;  
        tail->next = nullptr;  
    }  
};  
#endif //DLLIST_H
```