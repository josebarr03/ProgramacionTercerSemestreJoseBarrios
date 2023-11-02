#ifndef AVL_TREE_H
#define AVL_TREE_H

#include<iostream> // Inclusión de librería que acepta datos de entrada y muestra salida de resultados
#include<iomanip> // Inclusión de librería definir varios manipuladores que toman cada uno de ellos un
                  // solo argumento.
#include<algorithm> // Inclusión de librería que comprueba si hay un elemento en un intervalo que sea
                    // igual a un valor especificado por un predicado binario
#include<memory> // Inclusión de librería que define una clase, un operador y varias plantillas que
                 // sirven de ayuda para asignar y liberar objetos.

template <typename T> // Se crea un "template" para poder trabajar con cualquier valor
class Node { // Se crea la clase "Node"
public: // Se declaran variables públicas
    T data; // Se crea la data "T"
    int height; // Se inicializa una variable entera que guarda la altura
    std::shared_ptr<Node<T>> left; // Se crea el puntero "shared_ptr" que comparte puntero para apuntar
                                   // a la izquierda
    std::shared_ptr<Node<T>> right; // Se crea el puntero "shared_ptr" que comparte puntero para apuntar
                                    // a la derecha

    Node(T data) : data(data), height(1), left(nullptr), right(nullptr) {} // Definición del nodo
};

template <typename T> // Se crea un "template" para el árbol AVL
class AVLTree { // Se crea la clase "AVLTree"
public: // Se declaran variables públicas
    std::shared_ptr<Node<T>> root; // Se crea un puntero con los valores del nodo<T> para la raíz

    AVLTree(): root(nullptr) {} // El árbol AVL hereda de la raíz

    void add(T data) {
        root = insert(root, data); // Se agrega la "data" actual a la raíz
    }

    void remove(T data)  {
        root = deleteNode(root, data); // Se quita la "data" de la raíz
    }

    void print() {
        if (root != nullptr) { // Si la raíz no está vacía, imprime "(root,0)"
            print(root, 0);
        } else {
            std::cout << "The tree is empty." << std::endl; // Si está vacía imprime que el árbol está vacío
        }
    }

private:
    void print(std::shared_ptr<Node<T>> node, int indent) {
        if(node) {
            if(node->right) { // Si el nodo actual tiene algún nodo a la derecha y movimientos hacia él
                print(node->right, indent + 8); // Imprime el nodo hijo de la derecha con un "indent" de + 8
            }
            if (indent) { // Si "indent" guarda un valor, establece el valor como el ancho
                std::cout << std::setw(indent) << ' ';
            }
            if (node->right) { // Si el nodo actual tiene algún nodo a la derecha y movimientos hacia él
                std::cout << " / (Right of " << node->data << ")\n" << std::setw(indent) << ' '; // Imprime
                                                                                                 // el lado derecho
                                                                                                 // de la "data"
            }
            std::cout << node->data << "\n" ; // Imprime la "data"
            if (node->left) { // Si el nodo actual tiene algún nodo a la izquierda y movimientos hacia él
                std::cout << std::setw(indent) << ' ' << " \\ (Left of " << node->data << ")\n";
                print(node->left, indent + 8); // Imprime el nodo hijo de la izquierda con un "indent" de + 8
            }
        }
    }

    std::shared_ptr<Node<T>> newNode(T data) { // Se crea un nuevo nodo
        return std::make_shared<Node<T>>(data);
    }

    std::shared_ptr<Node<T>> rightRotate(std::shared_ptr<Node<T>> y) { // Se realizan rotaciones del nodo en sentido
                                                                       // de las manecillas para el reequilibrio
        std::shared_ptr<Node<T>> x = y->left; // Asigna el valor "x" de "y" a la izquierda
        std::shared_ptr<Node<T>> T2 = x->right; // Asigna el valor "T2" de "x" a la derecha

        x->right = y; // Asigna "y" al hijo de la derecha de "x"
        y->left = T2; // Asigna "T2" al hijo de la izquierda de "y"

        y->height = max(height(y->left), height(y->right))+1; // Recalcula la altura de "y"
        x->height = max(height(x->left), height(x->right))+1; // Recalcula la altura de "x"

        return x;
    }

    std::shared_ptr<Node<T>> leftRotate(std::shared_ptr<Node<T>> x) { // Se realizan rotaciones del nodo en sentido
                                                                      // contrario de las manecillas para el
                                                                      // reequilibrio
        std::shared_ptr<Node<T>> y = x->right; // Asigna el valor "y" de "x" a la derecha
        std::shared_ptr<Node<T>> T2 = y->left; // Asigna el valor "T2" de "y" a la izquierda

        y->left = x; // Asigna "x" al hijo de la izquierda de "y"
        x->right = T2; // Asigna "T2" al hijo de la derecha de "x"

        x->height = max(height(x->left),height(x->right))+1; // Recalcula la altura de "x"
        y->height = max(height(y->left),height(y->right))+1; // Recalcula la altura de "y"

        return y;
    }

    int getBalance(std::shared_ptr<Node<T>> N) {
        if (N == nullptr) // Si el nodo es nulo regresa 0 como balance
            return 0;
        return height(N->left) - height(N->right); // Si no es nulo resta la altura del lado
                                                          // izquierdo - derecho
    }

    std::shared_ptr<Node<T>> insert(std::shared_ptr<Node<T>> node, T data) {
        if (node == nullptr) // Si el nodo es nulo, crea un nuevo nodo con una "data" asignada
            return (newNode(data));

        if (data < node->data) // Se comprueba si los datos son menores que los del nodo
            node->left = insert(node->left, data); // Si son menores, al hijo izquierdo del nodo se le
                                                         // asigna un nuevo nodo con la "data" dicha.
        else if (data > node->data) // Verifica si los datos son más que los del nodo
            node->right = insert(node->right, data); // Si son más, al hijo derecho del nodo se le
                                                           // asigna un nuevo nodo con la "data" dicha.
        else
            return node; // Si lo anterior no se cumple regresa el nodo

        node->height = 1 + max(height(node->left), height(node->right)); // Recalcula la altura
                                                                                      // después de la inserción

        int balance = getBalance(node); // Crea una variable entera para revisar el balance usando la
                                           // substracción definida

        if (balance > 1 && data < node->left->data) // Si el balance es más que 1 y la "data" es menor que la
                                                    // "data" del nodo del hijo de la izquierda rota en dirección
                                                   // de las manecillas
            return rightRotate(node);

        if (balance < -1 && data > node->right->data) // Si el balance es menor que 1 y la "data" es mayor que la
                                                      // "data" del nodo del hijo de la derecha rota en dirección
                                                      // contraria de las manecillas
            return leftRotate(node);

        if (balance > 1 && data > node->left->data) { // Si el balance es más que 1 y la "data" es más que la
                                                      // "data" del nodo del hijo de la izquierda rota en dirección
                                                      // contrario de las manecillas
            node->left = leftRotate(node->left);
            return rightRotate(node); //  Rota en sentido de las manecillas
        }

        if (balance < -1 && data < node->right->data) { // Si el balance es más que -1 y la "data" es menor que la
                                                        // "data" del nodo del hijo de la derecha rota en dirección
                                                        // de las manecillas
            node->right = rightRotate(node->right);
            return leftRotate(node); // Rota en sentido contrario de las manecillas
        }

        return node; // Regresa nodo con rotación
    }

    std::shared_ptr<Node<T>> minValueNode(std::shared_ptr<Node<T>> node) { // Declara un nuevo nodo llamado "current"
                                                                           // con el valor del "current node"
        std::shared_ptr<Node<T>> current = node;

        while (current->left != nullptr) // Mientras el hijo de la izquierda del "current node" no sea nulo
            current = current->left; // Declara "current node" como su hijo de la izquierda

        return current; // Regresa el "current node"
    }

    std::shared_ptr<Node<T>> deleteNode(std::shared_ptr<Node<T>> root, T data) {
        if (!root) // Si la raíz está vacía
            return root; // Regresa la raíz (nullptr)

        if (data < root->data) { // Si la "data" es menor que la "data" de la raíz
            root->left = deleteNode(root->left, data); // En el hijo izquierdo del nodo se elimina el
                                                            // nodo izquierdo
        }
        else if(data > root->data) { // Si la "data" es más que la "data" de la raíz
            root->right = deleteNode(root->right, data); // En el hijo derecho del nodo se elimina el
                                                              // nodo derecho
        }
        else {
            if(!root->left || !root->right) { // Si el hijo izquierdo o derecho de la raíz está vacío
                root = (root->left) ? root->left : root->right; // Asigna el hijo izquierdo o derecho a la raíz
                                                                // dependiendo cuál exista
            }
            else {
                std::shared_ptr<Node<T>> temp = minValueNode(root->right); // Asigna al "temp node" el valor
                                                                                // mínimo del lado derecho de la raíz
                root->data = temp->data; // Asigna a la "data" de la raíz los datos del "temp"
                root->right = deleteNode(root->right, temp->data); // Elimina en el lado derecho del
                                                                             // nodo la "data" del "temp".
                temp.reset(); // Resetea el "temp"
            }
        }

        if(!root) // Verifica si la raíz existe
            return root; // Regresa la raíz(nullptr)

        root->height = 1 + max(height(root->left), height(root->right)); // Recalcula la altura
                                                                                     // después de la eliminación

        int balance = getBalance(root); // Crea una variable entera para balancear desde la raíz

        if (balance > 1 && getBalance(root->left) >= 0) // Si el balance es más que 1 y el balance del
                                                           // hijo izquierdo de la raíz es mayor o igual a 0
                                                           // va a rotar en dirección de las manecillas
            return rightRotate(root);

        if (balance < -1 && getBalance(root->right) <= 0) // Si el balance es menor que -1 y el balance del
                                                             // hijo derecho de la raíz es menor o igual a 0
                                                             // va a rotar en dirección contraria de las manecillas
            return leftRotate(root);

        if (balance > 1 && getBalance(root->left) < 0) { // Si el balance es más que 1 y el balance del
                                                            // hijo izquierdo de la raíz es menor a 0 el hijo va a
                                                            // rotar en dirección contraria de las manecillas
            root->left = leftRotate(root->left);
            return rightRotate(root); // La raíz va a rotar en sentido de las manecillas
        }

        if (balance < -1 && getBalance(root->right) > 0) { // Si el balance es menor que -1 y el balance del
                                                              // hijo derecho de la raíz es mayor a 0 el hijo va a
                                                              // rotar en dirección de las manecillas
            root->right = rightRotate(root->right);
            return leftRotate(root); // La raíz va a rotar en sentido contrario de las manecillas
        }

        return root; // Regresa la raíz después de la rotación
    }

    int height(std::shared_ptr<Node<T>> N) {
        if (N == nullptr) // Si "N" es nulo regresa 0
            return 0;
        return N->height; // Si no regresa la altura de "N"
    }

    int max(int a, int b) { // Verifica si "a" es mayor que "b"
        return (a > b)? a : b; // Si "a" es mayor regresa "a" y si "b" es mayor regresa "b"
    }
};

#endif /* AVL_TREE_H */
