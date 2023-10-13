## Header (.h)
```c++
#ifndef DLLIST_DLLIST_H  
#define DLLIST_DLLIST_H  
  
#include <iostream>  
#include <utility>  
  
template <typename Object>  
class DLList {  
private: // Se inician los valores privados  
    struct Node  {  
        Object data;  
        Node *next;  
        Node *prev;  
  
        Node(const Object &d = Object{}, Node *n = nullptr) // Constructor copia  
                : data{d}, next{n}, prev{n} {}  
  
        Node(Object &&d, Node *n = nullptr) // Constructor referencia  
                : data{std::move(d)}, next{n}, prev{n} {}  
    };  
  
public: // Inicializan valores públicos  
    class iterator {  
    public:  
        iterator() : current{nullptr} {} // Constructor, declara nulo para que no apunte algo random  
  
        Object &operator*() { // Se comprueba el contenido del puntero, si el igual a nulo da error lógico  
            if(current == nullptr)  
                throw std::logic_error("Trying to dereference a null pointer.");  
            return current->data;  
        }  
  
        iterator &operator++() { // Sirve para ir avanzando, pero si la posición es un extremo da error lógico  
            if(current)  
                current = current->next;  
            else  
                throw std::logic_error("Trying to increment past the end.");  
            return *this;  
        }  
  
        iterator operator++(int) { // Se determina el momento en que se usa el "++"" por su posición  
            iterator old = *this;  
            ++(*this);  
            return old;  
        }  
  
        iterator &operator--() { // Sirve para ir avanzando, pero si la posición es un extremo da error lógico  
            if(current)  
                current = current->prev;  
            else  
                throw std::logic_error("Trying to decrease past the beginning.");  
            return *this;  
        }  
  
        iterator operator--(int) { // Se determina el momento en que se usa el "++"" por su posición  
            iterator old = *this;  
            --(*this);  
            return old;  
        }  
  
        bool operator==(const iterator &rhs) const { // Si "operator" es igual a "(const iterator &rhs) const" regresa verdadero  
            return current == rhs.current;  
        }  
  
        bool operator!=(const iterator &rhs) const { // Si "operator" es diferente a "(const iterator &rhs) const" regresa verdadero  
            return !(*this == rhs);  
        }  
  
    private: // Se vuelve a declarar miembros privados, el primero es un puntero, el segundo un constructor y el último un amigo de la lista  
        Node *current;  
        iterator(Node *p) : current{p} {}  
        friend class DLList<Object>;  
    };  
  
public: // De forma pública se declara el constructor implícito de la lista  
    DLList() : head(new Node()), tail(new Node()), theSize(0) {  
        head->next = tail;  
    }  
  
    ~DLList() { // Se declara el destructor que elimina el inicio y la cola  
        clear();  
        delete head;  
        delete tail;  
    }  
  
    iterator begin() { return {head->next}; } // Se obtiene el inicio y final de la lista  
    iterator end() { return {tail}; }  
  
    int size() const { return theSize; } // En el primero se obtiene el tamaño y en el segundo y regresa verdadero si está vacío  
    bool empty() const { return size() == 0; }  
  
    void clear() { while (!empty()) pop_front(); } // Se usa mientras hay elementos en la lista  
  
    Object &front() { // Si no hay objetos da error lógico  
        if(empty())  
            throw std::logic_error("List is empty.");  
        return *begin();  
    }  
  
    void push_front(const Object &x) { insert(begin(), x); } // Pone objetos al inicio, el primero con copia y el segundo con referencia  
    void push_front(Object &&x) { insert(begin(), std::move(x)); }  
  
    void push_back(const Object &x) { insert(begin(), x); }  
    void push_back(Object &&x) { insert(begin(), std::move(x)); }  
  
    void pop_front() { // Borra el dato inicial  
        if(empty())  
            throw std::logic_error("List is empty.");  
        erase(begin());  
    }  
  
    iterator insert(iterator itr, const Object &x) { // Se inserta el dato hacia donde apunta el iterador  
        Node *p = itr.current;  
        head->next = new Node{x, head->next};  
        theSize++;  
        return iterator(head->next);  
    }  
  
    iterator insert(iterator itr, Object &&x) { // Se mueve un dato a donde apunta el iterador.  
        Node *p = itr.current;  
        head->next = new Node{std::move(x), head->next};  
        theSize++;  
        return iterator(head->next);  
    }  
  
    void insert(int pos, const Object &x) {  
        insert(get_iterator(pos), x);  
    }  
  
    iterator get_iterator(int a)  
    {  
        iterator it = begin();  
        for(int i = 0; i != a; ++i) {  
            ++it;  
        }  
        return it;  
    }  
  
    iterator erase(iterator itr) { // Se usa el "erase" para borrar hacia donde apunta el iterador  
        if (itr == end())  
            throw std::logic_error("Cannot erase at end iterator");  
        Node *p = head;  
        while (p->next != itr.current) p = p->next;  
        p->next = itr.current->next;  
        delete itr.current;  
        theSize--;  
        return iterator(p->next);  
    }  
  
    void erase(int pos)  
    {  
        erase(get_iterator(pos));  
    }  
  
    void printList() { // De forma cíclica se imprime el primer término mientras avanza hasta el final  
        iterator itr = begin();  
        while (itr != end()) {  
            std::cout << *itr << " ";  
            ++itr;  
        }  
        std::cout << std::endl;  
    }  
  
private: // Se inicializa de forma privada el nodo de inicio y de cola, así mismo el tamaño  
    Node *head;  
    Node *tail;  
    int theSize;  
    void init() {  
        theSize = 0;  
        head->next = tail;  
    }  
};  
  
#endif
```

## Main
```c++
#include <iostream>  
#include "DLList.h"  
  
int main() {  
    // Test integer list  
    DLList<int> integerList;  
    integerList.push_back(10);  
    integerList.push_front(20);  
    integerList.insert(1, 30);  
    std::cout << "Integer list: ";  
    integerList.printList();  
    integerList.erase(1);  
    std::cout << "Integer list after erase: ";  
    integerList.printList();  
    integerList.clear();  
    std::cout << "Integer list after clear: ";  
    integerList.printList();  
  
    // Test double list  
    DLList<double> doubleList;  
    doubleList.push_back(1.5);  
    doubleList.push_front(2.5);  
    doubleList.insert(1, 3.5);  
    std::cout << "\nDouble list: ";  
    doubleList.printList();  
    doubleList.erase(1);  
    std::cout << "Double list after erase: ";  
    doubleList.printList();  
    doubleList.clear();  
    std::cout << "Double list after clear: ";  
    doubleList.printList();  
  
    // Test char list  
    DLList<char> charList;  
    charList.push_back('a');  
    charList.push_front('b');  
    charList.insert(1, 'c');  
    std::cout << "\nChar list: ";  
    charList.printList();  
    charList.erase(1);  
    std::cout << "Char list after erase: ";  
    charList.printList();  
    charList.clear();  
    std::cout << "Char list after clear: ";  
    charList.printList();  
  
    return 0;  
}
```