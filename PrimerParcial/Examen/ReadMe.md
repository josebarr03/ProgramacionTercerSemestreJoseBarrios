## Parte 1. Preguntas.
- ¿Qué es un Rvalor y un Lvalor?
Un rvalue es una expresión que identifica un objeto temporal o un valor asociado con un objeto, y un lvalue es una expresión que identifica un objeto atemporal. Los rvalues se ubican en la derecha y los lvalues se ubican en la izquierda.

- ¿Porqué es necesario que una clase tenga constructores y operadores por copia y por referencia?
Porque estos operadores se aplican cuando un "=" se asigna a dos objetos que han sido previamente construidos.  El constructor de copia acepta de entrada una referencia a otro objeto de la misma clase, podiendo guardar un valor.

- ¿Qué función desarrollan los : : en la implementación de la clase?
Los dos dos puntos sirve para indicar que la función definida pertenece a la clase empleado. Por ejemplo en el std : : swap se puede convertir cualquier lvalue (o rvalue) en un rvalue o el std : : move logra que un valor esté sujeto a ser movido.

- ¿Cómo se le denomina a cuando una clase posee un operador puede tener múltiples implementaciones dependiendo de los argumentos que este reciba?
Overload y las funciones que especifica son llamadas de sobrecarga. 

- ¿Cuál es la función del archivo .h ?
El header es un archivo que funciona similar a una librería, ya que en él se pueden crear clases o estructuras que pueden ser llamadas en un archivo main para su uso.

## Parte 2. Complejidad Temporal.
Calcular la complejidad temporal en Big(O) Notation del siguiente algoritmo:
```c++
#include <iostream>
int algoritmo1(int n) {
int resultado = 0;

for (int i = 0; i < n; i++) {
resultado += i; // Operación simple O(1)
}

for (int i = 0; i < n; i++) {
for (int j = 0; j < n; j++) {
resultado += i * j; // Operación simple O(1)
}
}

return resultado;
}

int main() {
int n;
std::cout << "Ingrese el valor de n: ";
std::cin >> n;
int resultado = algoritmo1(n);
std::cout << "Resultado: " << resultado << std::endl;

return 0;
}
```

O(log^2) - logarítmica cuadrática

## Documentación código examen
### .h
```c++
#ifndef DOUBLE_CELL_H  
#define DOUBLE_CELL_H  
  
class DoubleCell {  
public:  
    // Default constructor  
    explicit DoubleCell(); //  
  
    // Constructor with value    
    explicit DoubleCell(double value);  
  
    // Copy constructor  
    DoubleCell(const DoubleCell &other);  
  
    //Reference constructor  
    DoubleCell(DoubleCell &&other) noexcept; //  
  
    // Destructor    
    ~DoubleCell() = default;  
  
    // Assignment operator by copy  
    DoubleCell &operator = (const DoubleCell &other); //  
  
    // Assignment operator by reference    
    DoubleCell &operator = (DoubleCell &&other) noexcept;  
  
    // Assignment operator for double  
    DoubleCell &operator=(double other);  
  
    // Arithmetic operators  
    DoubleCell operator +(const DoubleCell &other) const;  
    DoubleCell operator +(const double other) const;  
    DoubleCell operator -(const DoubleCell &other) const;  
    DoubleCell operator -(const double other) const;  
    DoubleCell operator *(const DoubleCell &other) const;  
    DoubleCell operator *(const double other) const;  
    DoubleCell operator /(const DoubleCell &other) const;  
    DoubleCell operator /(const double other) const;  
  
    // Setters  
    void setValue (double newValue);  
    // Getters  
    double GetValue() const;  
  
  
private:  
    double Storedvalue;  
};  
  
#endif  // DOUBLE_CELL_H
```
Este es el archivo header para las celdas de double, primero hacemos un constructor implícito que almacenará un valor por default si después no se asigna uno. Después tenemos un constructor con valor que almacenará el double. Con los constructores de copia y referencia se podrán asignar valores y con el destructor se puede destruir el "DoubleCell" para que no ocupe espacio. Después a los siguientes operadores (referencia, copia y double) se les dice que el valor será un double, luego tenemos los operadores aritméticos que los primeros dos son suma, el tercero y cuarto resta, el quinto y sexto multiplicación y los últimos dos división.  Al final tenemos las funciones de Set y Get, con el set se puede ver el valor y con el get se puede asignar el valor.

