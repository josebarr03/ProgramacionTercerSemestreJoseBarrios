## Header (.h)
### Código
```c++
1-  #ifndef SLLLIST_H
2-  #define SLLLIST_H
3-
4-  #include <iostream>
5-  #include <utility>
6-
7-  template <typename Object>
8-  class SLList {
9-  private:
10- //Cada Cuadrito
11- struct Node  {
12-     Object data;
13-     Node *next;//Anya
14-
15-     Node(const Object &d = Object{}, Node *n = nullptr)
16-        : data{d}, next{n} {}
17-
18-     Node(Object &&d, Node *n = nullptr)
19-         : data{std::move(d)}, next{n} {}
20- };
21-
22-  public:
23-     class iterator {
24-  public:
25-     iterator() : current{nullptr} {}
26-
27-     Object &operator*() {
28-         if(current == nullptr)
29-             throw std::logic_error("Trying to dereference a null pointer.");
30-         return current->data;
31-     }
32-
33-     iterator &operator++() {
34-         if(current)
35-             current = current->next;
36-         else
37-             throw std::logic_error("Trying to increment past the end.");
38-         return *this;
39-     }
40-
41-     iterator operator++(int) {
42-         iterator old = *this;
43-         ++(*this);
44-         return old;
45-     }
46-
47-     bool operator==(const iterator &rhs) const {
48-         return current == rhs.current;
49-     }
50-
51-     bool operator!=(const iterator &rhs) const {
52-         return !(*this == rhs);
53-     }
54-
55-  private:
56-     Node *current;
57-     iterator(Node *p) : current{p} {}
58-     friend class SLList<Object>;
59-  };
60-
61-  public:
62-    SLList() : head(new Node()), tail(new Node()), theSize(0) {
63-    head->next = tail;
64-  }
65-
66-  ~SLList() {
67-     clear();
68-     delete head;
69-     delete tail;
70-  }
71-
72-  iterator begin() { return {head->next}; }
73-  iterator end() { return {tail}; }
74-
75-  int size() const { return theSize; }
76-  bool empty() const { return size() == 0; }
77-
78-  void clear() { while (!empty()) pop_front(); }
79-
80-  Object &front() {
81-     if(empty())
82-         throw std::logic_error("List is empty.");
83-     return *begin();
84-  }
85-
86-  void push_front(const Object &x) { insert(begin(), x); }
87-  void push_front(Object &&x) { insert(begin(), std::move(x)); }
88-
89-  void pop_front() {
90-     if(empty())
91-         throw std::logic_error("List is empty.");
92-     erase(begin());
93-  }
94-
95-  iterator insert(iterator itr, const Object &x) {
96-     Node *p = itr.current;
97-     head->next = new Node{x, head->next};
98-     theSize++;
99-     return iterator(head->next);
100- }
101-
102- iterator insert(iterator itr, Object &&x) {
103-    Node *p = itr.current;
104-    head->next = new Node{std::move(x), head->next};
105-    theSize++;
106-    return iterator(head->next);
107- }
108-
109- iterator erase(iterator itr) {
110-    if (itr == end())
111-        throw std::logic_error("Cannot erase at end iterator");
112-    Node *p = head;
113-    while (p->next != itr.current) p = p->next;
114-    p->next = itr.current->next;
115-    delete itr.current;
116-    theSize--;
117-    return iterator(p->next);
118- }
119-
120- void printList() {
121-    iterator itr = begin();
122-    while (itr != end()) {
123-        std::cout << *itr << " ";
124-        ++itr;
125-    }
126-    std::cout << std::endl;
127- }
128-
129- private:
130-    Node *head;
131-    Node *tail;
132-    int theSize;
133-    void init() {
134-        theSize = 0;
135-        head->next = tail;
136-    }
137- };
138-
139- #endif
```

### Explicación
**Líneas 4 y 5 -** Llama las librerías que se van a utilizar en éste header.
**Línea 7 -** Se declara una plantilla en la que los objetos van a ser reemplazados por la lista que se va a definir.
**Línea 8 -** Se inicia la clase.
**Línea 9 -** Se inician los valores privados.
**Líneas 11 a 19 -** Aquí está un a clase nodo con un "stored item", un puntero al nodo siguiente y dos constructores, uno de copia y uno de referencia.
**Línea 23 -** Se establece la clase de iterador.
**Línea 25 -** Constructor, declara nulo para que no apunte algo random.
**Líneas 27 a 31 -** Se comprueba el contenido del puntero, si el igual a nulo da error lógico.
**Líneas 33 a 39 -** Sirve para ir avanzando, pero si la posición es un extremo da error lógico.
**Líneas 41 a 45 -** Se determina el momento en que se usa el "++"" por su posición.
**Líneas 47 a 49 -** Si "operator" es igual a "(const iterator &rhs) const" regresa verdadero.
**Líneas 51 a 53 -** Si "operator" es diferente a "(const iterator &rhs) const" regresa verdadero.
**Líneas 55 a 59 -** Se vuelve a declarar miembros privados, el primero es un puntero, el segundo un constructor y el último un amigo de la lista.
**Líneas 61 a 64 -** De forma pública se declara el constructor implícito de la lista.
**Líneas 66 a 70 -** Se declara el destructor de elimina el inicio y la cola.
**Líneas 72 y 73 -** Se obtiene el inicio y final de la lista.
**Líneas 75 y 76 -** En el primero se obtiene el tamaño y en el segundo y regresa verdadero si está vacío.
**Línea 78 -** Se usa mientras hay elementos en la lista.
**Líneas 80 a 84 -** Si no hay objetos da error lógico.
**Líneas 86 y 87 -** Pone objetos al inicio, el primero con copia y el segundo con referencia.
**Líneas 89 a 93 -** Borra el dato inicial.
**Líneas 95 a 100 -** Se inserta el dato hacia donde apunta el iterador.
**Líneas 102 a 107 -** Se mueve un dato a donde apunta el iterador.
**Líneas 109 a 118 -** Se usa el "erase" para borrar hacia donde apunta el iterador.
**Líneas 120 a 127 -** De forma cíclica se imprime el primer término mientras avanza hasta el final.
**Líneas 129 a 137 -** Se inicializa de forma privada el nodo de inicio y de cola, así mismo el tamaño.
