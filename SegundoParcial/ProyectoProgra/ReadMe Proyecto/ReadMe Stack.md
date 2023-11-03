## Header (.h)
``` c++
#include <iostream>  
#include <cstdlib>  
#include <stack>  
#ifndef STACK_H  
#define STACK_H  
  
template <typename T> // Se crea un "template" con el nombre "T"  
class Stack : private DLList<T> // Se crea la clase "Stack" que hereda desde DLList  
{  
private:  
  
public: // Se empieza declarando de forma pública  
    Stack()  
    {  
        DLList<T>::init(); // Inicializa "Stack" con un "init" definido en DLList  
    }  
  
    ~Stack() // Destructor  
    {  
        clear(); // Llama la función "clear"  
        delete DLList<T>::head; // Elimina el encabezado  
        delete DLList<T>::tail; // Elimina la cola  
    }  
  
    void push(T &data) // Agrega "data" al inicio de la pila por copia  
    {  
        DLList<T>::push_front(data);  
    }  
  
    void push(T &&data) // Agrega "data" al inicio de la pila por referencia  
    {  
        DLList<T>::push_front(data);  
    }  
  
    void pop() // Elimina la "data" al inicio de la pila  
    {  
        DLList<T>::pop_front();  
    }  
  
    void clear() // Limpia la pila  
    {  
        DLList<T>::clear();  
    }  
  
    void print() // Imprime la pila  
    {  
        DLList<T>::print();  
    }  
  
    T top() // Imprime únicamente el primer valor  
    {  
        return DLList<T>::head->next->data;  
    }  
};  
  
#endif //STACK_H
```