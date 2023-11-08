## Header (.h)
``` c++
1-   #ifndef AVL_TREE_H
2-   #define AVL_TREE_H
3-   
4-   #include<iostream>
5-   #include<iomanip>
6-   #include<algorithm>
7-   #include<memory>
8-   
9-   template <typename T>
10-  class Node {
11-  public:
12-      T data;
13-      int height;
14-      std::shared_ptr<Node<T>> left;
15-      std::shared_ptr<Node<T>> right;
16-  
17-      Node(T data) : data(data), height(1), left(nullptr), right(nullptr) {}
18-  };
19-  
20-  template <typename T>
21-  class AVLTree {
22-  public:
23-      std::shared_ptr<Node<T>> root;
24-  
25-      AVLTree(): root(nullptr) {}
26-  
27-      void add(T data) {
28-          root = insert(root, data);
29-      }
30-  
31-      void remove(T data)  {
32-          root = deleteNode(root, data);
33-      }
34-  
35-      void print() {
36-          if (root != nullptr) {
37-              print(root, 0);
38-          } else {
39-              std::cout << "The tree is empty." << std::endl;
40-          }
41-      }
42-  
43-  private:
44-      void print(std::shared_ptr<Node<T>> node, int indent) {
45-          if(node) {
46-              if(node->right) {
47-                  print(node->right, indent + 8);
48-              }
49-              if (indent) {
50-                  std::cout << std::setw(indent) << ' ';
51-              }
52-              if (node->right) {
53-                  std::cout << " / (Right of " << node->data << ")\n" << 
54-                  std::setw(indent) << ' ';
55-              }
56-              std::cout << node->data << "\n" ;
57-              if (node->left) {
58-                  std::cout << std::setw(indent) << ' ' << " \\ (Left of " 
59-                  << node->data << ")\n";
60-                  print(node->left, indent + 8);
61-              }
62-          }
63-      }
64-  
65-      std::shared_ptr<Node<T>> newNode(T data) {
66-          return std::make_shared<Node<T>>(data);
67-      }
68-  
69-      std::shared_ptr<Node<T>> rightRotate(std::shared_ptr<Node<T>> y) {
70-          std::shared_ptr<Node<T>> x = y->left;
71-          std::shared_ptr<Node<T>> T2 = x->right;
72-
73-          x->right = y;
74-          y->left = T2;
75-  
76-          y->height = max(height(y->left), height(y->right))+1;
77-          x->height = max(height(x->left), height(x->right))+1;
78-  
79-          return x;
80-      }
81-  
82-      std::shared_ptr<Node<T>> leftRotate(std::shared_ptr<Node<T>> x) {
83-          std::shared_ptr<Node<T>> y = x->right;
84-          std::shared_ptr<Node<T>> T2 = y->left;
85-  
86-          y->left = x;
87-          x->right = T2;
88-  
89-          x->height = max(height(x->left),height(x->right))+1;
90-          y->height = max(height(y->left),height(y->right))+1;
91-  
92-          return y;
93-      }
94-  
95-      int getBalance(std::shared_ptr<Node<T>> N) {
96-          if (N == nullptr)
97-              return 0;
98-          return height(N->left) - height(N->right);
99-      }
100- 
101-     std::shared_ptr<Node<T>> insert(std::shared_ptr<Node<T>> node, T
102-	 data) {
103-         if (node == nullptr)
104-             return (newNode(data));
105- 
106-         if (data < node->data)
107-             node->left = insert(node->left, data);
108-         else if (data > node->data)
109-             node->right = insert(node->right, data);
110-         else
111-             return node;
112- 
113-         node->height = 1 + max(height(node->left), height(node->right));
114- 
115-         int balance = getBalance(node);
116- 
117-         if (balance > 1 && data < node->left->data)
118-             return rightRotate(node);
119- 
120-         if (balance < -1 && data > node->right->data)
121-             return leftRotate(node);
122- 
123-         if (balance > 1 && data > node->left->data) {
124-             node->left = leftRotate(node->left);
125-             return rightRotate(node);
126-         }
127- 
128-         if (balance < -1 && data < node->right->data) {
129-             node->right = rightRotate(node->right);
130-             return leftRotate(node);
131-         }
132- 
133-         return node;
134-     }
135- 
136-     std::shared_ptr<Node<T>> minValueNode(std::shared_ptr<Node<T>> node) {
137-         std::shared_ptr<Node<T>> current = node;
138- 
139-         while (current->left != nullptr)
140-             current = current->left;
141- 
142-         return current;
143-     }
144- 
145-     std::shared_ptr<Node<T>> deleteNode(std::shared_ptr<Node<T>> root, T 
146-     data) {
147-         if (!root)
148-             return root;
149- 
150-         if (data < root->data) {
151-             root->left = deleteNode(root->left, data);
152-         }
153-         else if(data > root->data) {
154-             root->right = deleteNode(root->right, data);
155-         }
156-         else {
157-             if(!root->left || !root->right) {
158-                 root = (root->left) ? root->left : root->right;
159-             }
160-             else {
161-                 std::shared_ptr<Node<T>> temp = minValueNode(root->right);
162-                 root->data = temp->data;
163-                 root->right = deleteNode(root->right, temp->data);
164-                 temp.reset();
165-             }
166-         }
167- 
168-         if(!root)
169-             return root;
170- 
171-         root->height = 1 + max(height(root->left), height(root->right));
172- 
173-         int balance = getBalance(root);
174- 
175-         if (balance > 1 && getBalance(root->left) >= 0)
176-             return rightRotate(root);
177- 
178-         if (balance < -1 && getBalance(root->right) <= 0)
179-             return leftRotate(root);
180- 
181-         if (balance > 1 && getBalance(root->left) < 0) {
182-             root->left = leftRotate(root->left);
183-             return rightRotate(root);
184-         }
185- 
186-         if (balance < -1 && getBalance(root->right) > 0) {
187-             root->right = rightRotate(root->right);
188-             return leftRotate(root);
189-         }
190- 
191-         return root;
192-     }
193- 
194-     int height(std::shared_ptr<Node<T>> N) {
195-         if (N == nullptr)
196-             return 0;
197-         return N->height;
198-     }
199- 
200-     int max(int a, int b) {
201-         return (a > b)? a : b;
202-     }
203- };
204- 
205- #endif /* AVL_TREE_H */
```
### Explicación
- ***Líneas 4 a 7:*** Inclusión de librerías con distintas funciones. "iostream" para acepta datos de entrada y muestra salida de resultados. "iomanip" para definir varios manipuladores que toman cada uno de ellos un solo argumento. "algorithm"  para comprobar si hay un elemento en un intervalo que sea igual a un valor especificado por un predicado binario. "memory" para definir una clase, un operador y varias plantillas que sirven de ayuda para asignar y liberar objetos.
- ***Línea 9:*** Creación de un "template" para poder trabajar con cualquier valor.
- ***Línea 10:*** Creación de la clase "Node".
- ***Línea 11:*** Declaración de variables públicas.
- ***Línea 12:*** Creación de la data "T".
- ***Línea 13:*** Inicialización de una variable entera que guarda la altura.
- ***Línea 14:*** Creación del puntero "shared_ptr" que comparte puntero para apuntar a la izquierda.
- ***Línea 15:*** Creación el puntero "shared_ptr" que comparte puntero para apuntar a la derecha.
- ***Línea 17:*** Definición del nodo.
- ***Línea 20:*** Creación de un "template" para el árbol AVL.
- ***Línea 21:*** Creación de la clase "AVLTree".
- ***Línea 22:*** Declaración de variables públicas.
- ***Línea 23:*** Creación de un puntero con los valores del nodo < T > para la raíz.
-  ***Línea 25:*** Árbol AVL hereda de la raíz.
-  ***Línea 28:*** Se agrega la "data" actual a la raíz.
-  ***Línea 32:*** Se quita la "data" de la raíz.
-  ***Línea 36:*** Imprime "(root,0)" si la raíz no está vacía.
-  ***Línea 39:*** Si está vacía imprime que el árbol está vacío.
-  ***Líneas 46 y 47:*** Si el nodo actual tiene algún nodo a la derecha y movimientos hacia él, imprime el nodo hijo de la derecha con un "indent" de + 8.
-  ***Línea 49:*** Si "indent" guarda un valor, establece el valor como el ancho.
-  ***Líneas 52 y 53:*** Si el nodo actual tiene algún nodo a la derecha y movimientos hacia él, imprime el lado derecho de la "data".
-  ***Línea 56:*** Impresión de la "data".
- ***Líneas 57 a 60:*** Si el nodo actual tiene algún nodo a la izquierda y movimientos hacia él, imprime el nodo hijo de la izquierda con un "indent" de + 8.
-  ***Línea 65:*** Creación de un nuevo nodo.
- ***Línea 69:*** Realización de rotaciones del nodo en sentido de las manecillas para el reequilibrio.
-  ***Líneas 70 y 71:*** La primera línea asigna el valor "x" de "y" a la izquierda y la segunda asigna el valor "T2" de "x" a la derecha.
-  ***Líneas 73 y 74:*** La primera línea asigna "y" al hijo de la derecha de "x" y la segunda asigna "T2" al hijo de la izquierda de "y".
-  ***Líneas 76 y 77:*** La primera línea recalcula la altura de "y" y la segunda recalcula la altura de "x".
- ***Línea 82:*** Realización de rotaciones del nodo en sentido contrario de las manecillas para el reequilibrio.
-  ***Líneas 83 y 84:*** La primera línea asigna el valor "y" de "x" a la derecha y la segunda asigna el valor "T2" de "y" a la izquierda.
-  ***Líneas 86 y 87:*** La primera línea asigna "x" al hijo de la izquierda de "y" y la segunda asigna "T2" al hijo de la derecha de "x".
-  ***Líneas 89 y 90:*** La primera línea recalcula la altura de "x" y la segunda recalcula la altura de "y"
-  ***Líneas 96 a 98:*** Si el nodo es nulo regresa 0 como balance pero si no es nulo resta la altura del lado izquierdo - derecho.
-  ***Líneas 103 y 104:*** Si el nodo es nulo, crea un nuevo nodo con una "data" asignada.
-  ***Líneas 106 y 107:*** Se comprueba si los datos son menores que los del nodo, si son menores, al hijo izquierdo del nodo se le asigna un nuevo nodo con la "data" dicha.
-  ***Líneas 108 y 109:*** Si los datos son más que los del nodo al hijo derecho del nodo se le asigna un nuevo nodo con la "data" dicha.
-  ***Línea 111:*** Si lo anterior no se cumple regresa el nodo.
- ***Línea 113:*** Re calculación de la altura después de la inserción.
- ***Línea 115:*** Creación de una variable entera para revisar el balance usando la substracción definida.
-  ***Líneas 117 y 118:*** Si el balance es más que 1 y la "data" es menor que la "data" del nodo del hijo de la izquierda rota en dirección de las manecillas.
-  ***Líneas 120 y 121:*** Si el balance es menor que 1 y la "data" es mayor que la "data" del nodo del hijo de la derecha rota en dirección contraria de las manecillas.
-  ***Líneas 123 a 125:*** Si el balance es más que 1 y la "data" es más que la "data" del nodo del hijo de la izquierda rota en dirección contrario de las manecillas en el nodo hijo de la izquierda y asigna un valor nuevo de la rotación al nodo, y regresa la rotación en sentido de la manecillas en el nodo con rotación a la izquierda.
-  ***Líneas 128 a 130:*** Si el balance es más que -1 y la "data" es menor que la "data" del nodo del hijo de la derecha rota en dirección de las manecillas en el nodo hijo de la derecha y asigna un valor nuevo de la rotación al nodo, y regresa la rotación en sentido contrario de la manecillas en el nodo con rotación a la derecha.
-  ***Línea 133:*** Regresa nodo con la rotación.
-  ***Línea 136:*** Declaración un nuevo nodo llamado "current" con el valor del "current node".
-  ***Líneas 139 y 140:*** Mientras el hijo de la izquierda del "current node" no sea nulo se declara a "current node" como su hijo de la izquierda.
-  ***Línea 142:*** Regresa el "current node".
-  ***Líneas 147 y 148:*** Si la raíz está vacía, regresa la raíz (nullptr).
-  ***Líneas 150 y 151:*** Si la "data" es menor que la "data" de la raíz, en el hijo izquierdo del nodo se elimina el nodo izquierdo.
-  ***Líneas 153 y 154:*** Si la "data" es más que la "data" de la raíz, en el hijo derecho del nodo se elimina el nodo derecho.
-  ***Líneas 157 y 158:*** Si el hijo izquierdo o derecho de la raíz está vacío asigna el hijo izquierdo o derecho a la raíz dependiendo cuál exista.
-  ***Línea 161:*** Asigna al "temp node" el valor mínimo del lado derecho de la raíz.
-  ***Línea 162:*** Asigna a la "data" de la raíz los datos del "temp".
-  ***Línea 163:*** Elimina en el lado derecho del nodo la "data" del "temp".
-  ***Línea 164:*** Resetea el "temp"
-  ***Líneas 168 y 169:*** Verifica si la raíz existe para después regresar la raíz(nullptr).
-  ***Línea 171:*** Re calculación de la altura después de la eliminación.
-  ***Línea 173:*** Creación de una variable entera para balancear desde la raíz.
-  ***Líneas 175 y 176:*** Si el balance es más que 1 y el balance del hijo izquierdo de la raíz es mayor o igual a 0 va a rotar en dirección de las manecillas.
-  ***Líneas 178 y 179:*** Si el balance es menor que -1 y el balance del hijo derecho de la raíz es menor o igual a 0 va a rotar en dirección contraria de las manecillas.
-  ***Líneas 181 a 183:*** Si el balance es más que 1 y el balance del hijo izquierdo de la raíz es menor a 0 el hijo va a rotar en dirección contraria de las manecillas, la raíz va a rotar en sentido de las manecillas.
-  ***Líneas 186 a 188:*** Si el balance es menor que -1 y el balance del hijo derecho de la raíz es mayor a 0 el hijo va a rotar en dirección de las manecillas, la raíz va a rotar en sentido contrario de las manecillas.
-  ***Línea 191:*** Regresa la raíz después de la rotación.
- ***Línea 195:*** Si "N" es nulo regresa 0.
- ***Línea 197:*** Si no regresa la altura de "N".
- ***Línea 200:*** Verifica si "a" es mayor que "b".
- ***Línea 201:*** Si "a" es mayor regresa "a" y si "b" es mayor regresa "b".
### Investigación
Un árbol AVL es un árbol binario de búsqueda que cumple con la condición de que la diferencia entre las alturas de los subárboles de cada uno de sus nodos es, como mucho 1.
Su propiedad de equilibrio asegura que la profundidad del árbol sea O(log(n)), por lo que las operaciones sobre estas estructuras no deberán recorrer mucho para hallar el elemento deseado.
Entre sus operaciones se encuentra la inserción que consiste cuando se inserta un nuevo nodo en el árbol hay que tener en cuenta que cada nodo no puede tener más de dos hijos, por esta razón si un nodo ya tiene 2 hijos, el nuevo nodo nunca se podrá insertar como su hijo, después del proceso hay que comprobar que se sigue manteniendo la condición de equilibrio. En la operación de borrado si el nodo no tiene hijos únicamente habrá que borrar el elemento y ya habremos concluido la operación, si tiene un sólo hijo para borrar el nodo deseado el padre del nodo a borrar pasa a apuntar al hijo del nodo borrado, y si el nodo a borrar tiene dos hijos se sustituye el nodo a borrar por mayor de los nodos menores del nodo borrado, o por el menor de los nodos mayores de dicho nodo y una vez realizada esta sustitución se borra el nodo que sustituyó al nodo eliminado. En este proceso se puede realizar más de una rotación.

## Bibliografía
- TLDP-ES: Página Principal. Accedido el 8 de noviembre de 2023. [En línea]. Disponible: http://es.tldp.org/Tutoriales/doc-programacion-arboles-avl/avl-trees.pdf
- “DSTool: Herramienta para la programación con estructuras de datos”. HCI-RG: welcome - home. Accedido el 8 de noviembre de 2023. [En línea]. Disponible: http://www.hci.uniovi.es/Products/DSTool/avl/avl-operaciones.html
