## Header (.h)
```c++
#ifndef FLOATCELL_H  
#define FLOATCELL_H  
  
class FloatCell {  
public:  
    explicit FloatCell(float newValue = 0);  
    FloatCell(const FloatCell &rhs);  
    FloatCell(FloatCell &&rhs) noexcept;  
    ~FloatCell() = default;  
  
    FloatCell &operator=(const FloatCell &rhs);  
    FloatCell &operator=(FloatCell &&rhs) noexcept;  
  
    // Overloaded assignment operator to accept primitive int  
    FloatCell &operator=(float rhs);  
  
    float getValue() const;  
    void setValue(float newValue);  
  
private:  
    float storedValue;  
};  
  
#endif  // FLOATCELL_H
```
### Explicación
Línea 1 - Se ejecuta la instrucción #ifndef con el nombre del header, esta instrucción sirve para habilitar algunas funciones específicas del header y evitar importaciones.

Línea 2 - Se declara #define con el nombre del header para que funcione como constante.

Línea 4 - Se declara una clase con el nombre de "FloatCell".

Línea 5 - Se van a comenzar a declarar las variables públicas.

Línea 6 - Aquí con el "explicit FloatCell" se crea el constructor implícito. Con este podemos asignar un valor predeterminado si posteriormente no le damos uno. En este caso es 0.

Línea 7 - En esta línea como se puede ver un ejemplo en la página 32 del libro, tenemos un constructor de copia, que sirve para que le podamos dar un valor.

Línea 8 - En esta línea como se puede ver un ejemplo en la página 32 del libro, tenemos un constructor de referencia, que sirve para que le podamos dar un valor.

Línea 9 - Al igualar el "FloatCell" con el "default" se crea un destructor que sirve para destruir la variable cuando ya no se ocupe.

Líneas 11 y 12 - Aquí los rvalues que se se asignen tendrán un valor entero.

Línea 15 - Con esta línea el operador podrá aceptar enteros y no solo datos de su mismo tipo.

Líneas 17 y 18 - Con el "getValue" se podrá asignar un valor a una variable y con el "setValue" se podrá ver el valor.

Línea 20 - Se van a comenzar a declarar las variables privadas.

Línea 21 - Se inicializa una variable FloatCell con la cual se va a almacenar el valor entero.

Línea 24 - Se cierra la instrucción de la línea 1 con el "#endif".

## .Cpp
```c++
#include "FloatCell.h"  
  
// Default constructor  
FloatCell::FloatCell(float newValue) : storedValue(newValue) {}  
  
// Copy constructor  
FloatCell::FloatCell(const FloatCell &rhs) : storedValue(rhs.storedValue) {}  
  
// Move constructor  
FloatCell::FloatCell(FloatCell &&rhs) noexcept : storedValue(rhs.storedValue) 
{  
    rhs.storedValue = 0;  
}  
// Copy assignment operator  
FloatCell &FloatCell::operator=(const FloatCell &rhs) 
{  
    if (this != &rhs) 
    {  
        storedValue = rhs.storedValue;  
    }  
    return *this;  
}  
  
// Remove Move assignment operator  
FloatCell &FloatCell::operator=(FloatCell &&rhs) noexcept 
{  
    if (this != &rhs) 
    {  
        storedValue = rhs.storedValue;  
        rhs.storedValue = 0;  
    }  
    return *this;  
}  
  
// Removed overloaded assignment operator to accept any data  
  
// Overloaded assignment operator to accept only integer data  
FloatCell &FloatCell::operator=(float rhs) 
{  
    storedValue = rhs;  
    return *this;  
}
```
### Explicación

Línea 1 - Se llama al header con la clase anteriormente creada.

Línea 4 - Se tiene el constructor implícito que contiene el "storedValue", que como se mencionó tiene almacenado el valor entero.

Línea 7 - Aquí se tiene un constructor de copia con el que se hace una copia en el "storedValue" el valor asignado en una variable.

Línea 10 - En esta línea hay un constructor de referencia que tiene la misma función que el constructor de la línea 7 pero éste en la línea 11 iguala a 0.

Línea 14 - Aquí cuando hay una asignación de copia entre dos variables (una "FloatCell" y otra de otro tipo), con el if se van a tomar los rvalues.

Línea 22 - Igual que la asignación de la línea 14 pero aquí los rvalues se van a igualar en 0.

Línea 33 - Aquí se podrá acceder al valor de "storedValue".