## Tipos de datos abstractos
Un ADT es un conjunto de objetos y de operaciones, son abstracciones matemáticas. Algunos objetos como las listas, conjuntos y grafos, junto sus operaciones, pueden verse como tipos de datos abstractos, así como los números enteros, reales y booleanos son tipos de datos. 
C++ permite implementación de ADTs, así que cualquier parte del programa que necesite de ellos los puede llamar con el método correcto. Si los detalles de la implementación requieren cambiarse, será fácil usando las rutinas de operaciones de los ADTs.

***Abstracción: Consiste en ignorar los detalles de la manera particular en
que está hecha una cosa quedándonos solamente con su visión general.
Algunas de las operaciones que se pueden aplicar son:
1.  Makenull(A). Inicializa el conjunto A al conjunto vacío.
2. Add elem(A,a). Agrega el elemento a al conjunto A.
3. Union(A,B,C). Toma dos sets A y B y asigna la uni´on de A y B al conjunto C.
4. Size(A). Toma un conjunto A y devuelve un entero cuyo valor es la cantidad de elementos de A.

***

## Listas de tipos de datos abstractos
Una lista general con forma A0, A1, A2, ..., A(N - 1). N se refiere al tamaño de la lista. Una lista especial es una lista de tamaño 0 es una lista vacía.
Para cualquier lista exceptuando la vacía, Ai sigue a Ai - 1 (i < N) y Ai - 1 precede a Ai (i > 0). El primer elemento de la lista es A0 y el último es A(N -1). La posición del elemento de una lista Ai es i.
"printList" y "makeEmpty" son operaciones populares, otra es "find" que regresa la posición de la primera aparición de un elemento, "insert" que inserta un elemento de una posición, "remove" que remueve un elemento de su posición, y "findKth" que devuelve un elemento en una posición.

***Para un ADT se distinguen tres niveles:
- Utilización: basada en la especificación, independiente de su implementación.
- Especificación: (interfaz público) especifica el concepto abstracto que representa, y la semántica y restricciones de las operaciones.
- Implementación: (privada) define las estructuras de datos internas y la implementación de las operaciones.***
### Implementación de matriz simple de listas
Las instrucciones anteriores se pueden agregar usando una matriz (creado con una capacidad fija), el vector clase almacena un arreglo que permite que pueda crecer duplicando su capacidad cuando se requiera. 
Cuando se implementa una matriz se permite que "printList" se lleve a cabo en tiempo lineal, mientras que "findKth" en tiempo constante. La inserción y eliminación son costosos dependiendo dónde se produzcan estos. 
Para cualquier operación es necesario mover la mitad de la lista, así que se requiere tiempo lineal. Mientras que si las operaciones se realizan en el extremo superior no es necesario mover ningún elemento, para después agregar y eliminar que toma de tiempo O(1).
Hay situaciones donde la lista está construida con inserciones en el extremo superior para que luego se produzcan accesos a la matriz, si eso pasa la implementación de la matriz es adecuada, pero si las eliminaciones e inserciones se producen al principio de la lista significa que la matriz no es una buena opción.
### Lista enlazada simple
Una lista enlazada consiste en una serie de nodos que no son necesariamente adyacentes en la memoria. Los nodos contienen un elemento y un enlace (el siguiente enlace de la última celda apunta a "nullptr") al nodo sucesor.

![[Captura de pantalla 2023-10-05 001639.png]]

Al ejecutar "printList()" o "find(x)" se comienza con el primer nodo y luego se recorre la lista con los siguientes enlaces. La operación "findKth" no es tan eficiente como una implementación de matriz pues "findKth (i)" toma O (i) de tiempo y funciona recorriendo la lista de manera obvia.
El método "remove" puede ser ejecutado en el siguiente cambio de puntero

![[Captura de pantalla 2023-10-05 001652.png]]

El método "insert" requiere obtener un nodo del sistema usando una llamado y después ejecutando dos maniobras del puntero siguiente.

![[Captura de pantalla 2023-10-05 001707.png]]

En una lista doblemente enlazada cada nodo mantiene un enlace con el nodo previo de la lista.

![[Captura de pantalla 2023-10-05 001720.png]]

## Vectores y listas en el STL
Los vectores y las listas son implementaciones populares de la lista de ADTs. 
- El vector provee una implementación de matriz, con la ventaja de que es indexeable en tiempo constante, y la desventaja de que la inserción de nuevos items y la eliminación de items existentes es costosa. 
- La lista provee una implementación de una lista doblemente enlazada, la ventaja es que la inserción y eliminación de items es barata, y la desventaja es que no es fácilmente indexable.

Ambos son ineficientes para búsquedas y ambos son plantillas instanciadas con elementos que almacenan. Sus primeros tres métodos en común son:
- **int size () const:** regresa el número de elementos en el contenedor.
- **void clear ():** remueve los elementos del contenedor.
- **bool empty () const:** regresa "true" si el contenedor no contiene elementos y "falso" si los tiene.

El vector y la lista permiten la adición y eliminación desde el final de la la lista en tiempo constante, también permiten el acceso al item frontal en tiempo constante. Las operaciones son:
- **void push_back (const Object & x):** agrega "x" al final de la lista.
- **void pop_back ():** remueve el objeto al final de la lista.
- **const Object & back () const:** regresa el objeto al final de la lista.
- **const Object & front () const:** regresa el objeto al inicio de la lista.

Una lista doblemente enlazada permite cambios eficientes al inicio, pero un vector no. Los siguientes dos métodos solo se pueden usar en una lista:
- **void push_front (const Object & x):** agrega "x" al inicio de la lista.
- **void pop_front ():** remueve el objeto al inicio de la lista.

Los siguientes métodos son parte del vector y no de la lista:
- **Object & operator[] (int idx):** permite una indexación eficiente. Regresa el objeto en el index "idx" en el vector sin verificación de límites.
- **Object & at (int idx):** permite una indexación eficiente. Regresa el objeto en el index "idx" en el vector con verificación de límites.
- **int capacity () const:** regresa la capacidad interna del vector.
- **void reserve (int newCapacity):** establece una nueva capacidad. Si la estimación es buena se puede usar para evitar la expansión del vector. 
### Iteradores
En el STL un iterador representa la posición de un tipo anidado. Para un "list< string >" la posición se representa con un "list< string >::iterator", y para un "vector< int >" la posición se representa con un "vector< int >::iterator". Tenemos algunos problemas principales para tratar:
1. **Obtener un iterador:** las listas STL define estos métodos:
- **iterator begin ():** regresa un iterador apropiado representando el primer item del contenedor.
- **iterator end ():** regresa un iterador apropiado representando el marcador final en el contenedor.
2. **Métodos de iterador:** los iteradores pueden ser comparados con "!=" o " == " y probablemente tener constructores por copia y "operator =" definidos. Las operaciones más comunes en iteradores son:
- **itr++ y ++itr:** avanza el iterador "itr" a la siguiente locación. El prefijo y el sufijo son permitidos.
- ***itr:*** regresa una referencia al objeto almacenado en el iterador de la locación del "itr". La referencia regresada puede o no ser modificable.
- **itr1 == itr2:** regresa "true" si los iteradores "itr1" e "itr2" hacen referencia a la misma locación, si no, regresa "false".
- **itr1 != itr2:** regresa "true" si los iteradores "itr1" e "itr2" hacen referencia a una diferente locación, si no, regresa "false".
3. **Operaciones del contenedor que requieren iterador:** los métodos más populares agregan o eliminan de la lista de una posición especificada:
- **iterator insert (iterator pos, const Object & x):** agrega "x" en la lista, priorizando la posición dada por el iterador "pos". Para las listas es una operación de tiempo constante pero para el vector no. El valor regresado es un iterador representando la posición del item insertado.
- **iterator erase (iterator pos):** remueve el objeto de la posición dada por el iterador.  Para las listas es una operación de tiempo constante pero para el vector no. El valor regresado es la posición del elemento seguido "pos" hacia la llamada. Esta operación invalida "pos".
- **iterator erase (iterator start, iterator end):** remueve todos los items empezando por la posición "start" pero sin incluir "end".

### Ejemplo: Usando "erase" en una lista
El método "erase" para las listas toma un tiempo constante pero para un vector toma un tiempo cuadrático, pues cada una de las llamadas a "erase" es ineficiente. El siguiente es un código de ejemplo:

```C++
template <typename Container>
void removeEveryOtherItem( Container & lst )
{
auto itr = lst.begin( ); // itr is a Container::iterator

while( itr != lst.end( ) )
{
itr = lst.erase( itr );
if( itr != lst.end( ) )
++itr;
}
}
```

### Const_iterators
El resultado de  * *itr* es el valor del item que el iterador está viendo pero también el mismo item. El siguiente ejemplo funciona para listas y vectores y este corre en tiempo lineal.

```c++
template <typename Container, typename Object>
void change( Container & c, const Object & newValue )
{
typename Container::iterator itr = c.begin( );
while( itr != c.end( ) )
*itr++ = newValue;
}
```

Si suponemos que el "Contenedor c" fue pasado a una rutina usando una llamada de referencia constante no habría cambios permitidos a "c" y el compilador se aseguraría de no permitir llamados a los mutadores de "c".
La principal diferencia entre un iterador y un "const_iterator" es que el "operator*" del "const_iterator" regresa una referencia constante mientras logrando que el * itr del "const_iterator" no pueda aparecer en el "left hand side" de la sentencia de asignación.
Existen dos versiones del "begin":
- iterator begin ()
- const_iterator begin () const
Existen dos versiones del "end":
- iterator end ()
- const_iterator end () const
Si "begin" es invocado en un contenedor no constante, el mutador que regresa el iterador es invocado, si "begin" es invocado en un contenedor constante se regresa un "const_iterator" y posiblemente el valor no se asigne al iterador. 
Escribir un código genérico usando "begin (c)" en lugar de "c.begin ()" permite que se pueda trabajar en contenedores que tengan "begin" o "end" como miembros aunque también si no se tienen esos miembros pueden ser argumentados con funciones no miembros apropiadas.

## Implementación de un vector
Un vector puede ser copiado y la memoria que este usa se puede reclamar de forma automática.
- El vector mantendrá una matriz primitiva, la capacidad de la matriz y el número de items en el vector.
- El vector va a implementar los "Big Five" (vistos en el primer capítulo) para proporcionar su semántica de copia profunda y el "operator=", así mismo va a proporcionar un destructor para reclamar la matriz primitiva.
- El vector va a proporcionar una rutina de cambio que va a cambiar la capacidad del vector.
- El vector proveerá una implementación de "operator[]".
- El vector va a proporcionar rutinas básicas como el "size", "empty", "clear", "back", "pop_back" y "push_back".
- El va a proporcionar soporte para los tipos anidados como "iterator" y "const_iterator", y los métodos "begin" y "end".

## Implementación de una lista
La clase lista será implementada como una lista doblemente enlazada que necesitan mantener punteros en ambos extremos de la lista, esto nos permite mantener constante el costo por operación. La posición puede ser al final o en una posición especificada por el iterador. Se va a necesitar proveer cuatro clases:
- La clase lista que contiene enlaces hacia ambos extremos, el tamaño de la lista y un anfitrión de métodos.
- La clase nodos que es una clase anidada privada. Un nodo contiene datos y punteros hacia los nodos previos y siguientes, junto los constructores apropiados.
- La clase "const_iterator" que abstrae la noción de una posición y es una clase anidada pública. El "const_iterator" almacena un puntero hacia el nodo actual y proporciona la implementación de las operaciones básicas del iterador.
- La clase iterador que abstrae la noción de una posición y es una clase pública anidada. Tiene la misma función que la clase anterior con la diferencia que el "operator*" devuelve una referencia al elemento que se está viendo, en lugar de una referencia constante al elemento.
Un "sentinel node" es un nodo extra creado para representar una marca final. Si se encuentra al frente  se le llama "header node" y si está al último es un "tail node". 
A continuación se muestra una lista doblemente enlazada con "header node" y "tail node".

![[Captura de pantalla 2023-10-05 062435.png]]

La siguiente muestra una lista vacía.

![[Captura de pantalla 2023-10-05 062446.png]]

La siguiente imagen muestra como un nodo nuevo que contiene "x" es empalmada entre un nodo que está siendo apuntado por "p" y "p.prev".

![[Captura de pantalla 2023-10-05 063258.png]]

La siguiente muestra la lógica detrás de remover un nodo.

![[Captura de pantalla 2023-10-05 063407.png]]

## Bibliografía
- Maldonado. (s.f.). _Tipos abstractos de datos_. EDA-teorico1. Recuperado de [https://www.fing.edu.uy/tecnoinf/maldonado/cursos/eda/material/teo/EDA-teorico1.pdf](https://www.fing.edu.uy/tecnoinf/maldonado/cursos/eda/material/teo/EDA-teorico1.pdf)
- Vicente. (s.f.). _TIPOS ABSTRACTOS DE DATOS_. Tema 2, Málaga, España. Recuperado de [http://www.lcc.uma.es/~vicente/docencia/docencia/mp_tema_2.la.pdf](http://www.lcc.uma.es/~vicente/docencia/docencia/mp_tema_2.la.pdf)
- Weiss, M. A. (2013). _Data Structures & Algorithm Analysis in C++_. Pearson.

## Opinión
Mi opinión fue que este capítulo a diferencia del anterior se me hizo más fácil de leer, yo pienso que ha sido porque después de leer el capítulo pasado me acostumbré más a ciertos términos en inglés que antes no ubicaba tanto. Igual que el capítulo anterior siento que comprenderlo es más sencillo que aplicarlo, y algo que no me gusta del libro es que hay veces que una explicación está en una página y el código en dos páginas más adelante y eso confunde.
