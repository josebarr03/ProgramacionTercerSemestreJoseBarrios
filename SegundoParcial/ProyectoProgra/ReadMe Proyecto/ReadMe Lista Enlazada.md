## Header (.h)
``` c++
#ifndef SLLLIST_H  
#define SLLLIST_H  
  
#include <iostream> // Llama las librerías que se van a utilizar en éste header  
#include <utility>  
  
template <typename Object> // Se declara una plantilla en la que los objetos van a ser reemplazados por la lista que se va a definir  
class SLList { // Se inicia la clase  
private: // Se inician los valores privados  
    //Cada Cuadrito    struct Node  { //Aquí está un a clase nodo con un "stored item", un puntero al nodo siguiente y dos constructores, uno de copia y uno de referencia  
        Object data;  
        Node *next;//Anya  
  
        Node(const Object &d = Object{}, Node *n = nullptr)  
                : data{d}, next{n} {}  
  
        Node(Object &&d, Node *n = nullptr)  
                : data{std::move(d)}, next{n} {}  
    };  
  
public:  
    class iterator { // Se establece la clase de iterador  
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
  
        bool operator==(const iterator &rhs) const { // Si "operator" es igual a "(const iterator &rhs) const" regresa verdadero  
            return current == rhs.current;  
        }  
  
        bool operator!=(const iterator &rhs) const { // Si "operator" es diferente a "(const iterator &rhs) const" regresa verdadero  
            return !(*this == rhs);  
        }  
  
    private: // Se vuelve a declarar miembros privados, el primero es un puntero, el segundo un constructor y el último un amigo de la lista  
        Node *current;  
        iterator(Node *p) : current{p} {}  
        friend class SLList<Object>;  
    };  
  
public: // De forma pública se declara el constructor implícito de la lista  
    SLList() : head(new Node()), tail(new Node()), theSize(0) {  
        head->next = tail;  
    }  
  
    ~SLList() { // Se declara el destructor de elimina el inicio y la cola  
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
  
    void print() { // De forma cíclica se imprime el primer término mientras avanza hasta el final  
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