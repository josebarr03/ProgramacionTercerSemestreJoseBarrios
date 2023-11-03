```c++
#ifndef QUEUE_H  
#define QUEUE_H  
  
template<typename T> // Se crea un "template" con el nombre "T"  
class Queue : private DLList<T> // Crea la clase "Queue" que hereda desde DLList  
{  
private:  
  
public: // Se empieza declarando de forma pública  
    Queue()  
    {  
        DLList<T>::init(); // Inicializa "Queue" con un "init" definido en DLList  
    }  
  
    ~Queue() // Destructor  
    {  
        clear(); // Llama la función "clear"  
        delete DLList<T>::head; // Elimina el encabezado  
        delete DLList<T>::tail; // Elimina la cola  
    }  
  
    void enqueue(T &data) // Función que agrega "data" al inicio de la cola por copia  
    {  
        DLList<T>::push_back(data);  
    }  
  
    void enqueue(T &&data) // Función que agrega "data" al inicio de la cola por referencia  
    {  
        DLList<T>::push_back(data);  
    }  
  
    void dequeue() // Función que elimina la "data" al inicio de la cola  
    {  
        DLList<T>::pop_front();  
    }  
  
    void clear() // Función que limpia la cola  
    {  
        DLList<T>::clear();  
    }  
  
    void print() // Función que imprime la cola  
    {  
        DLList<T>::print();  
    }  
  
    T front() // Imprime únicamente el primer valor  
    {  
        return DLList<T>::head->next->data;  
    }  
};  
  
#endif //QUEUE_H
```