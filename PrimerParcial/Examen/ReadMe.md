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