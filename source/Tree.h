
#ifndef LESSON3_TREE_H
#define LESSON3_TREE_H

#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;
template <class Item> class STACK
{ Item * S; int t;
public:
    explicit STACK(int maxt) : S(new Item[ maxt ]), t(0) { }
    bool empty( ) const { return t==0; }
    int size( ) const { return t; }
    void push(Item item) { S[t++] = item; }
    Item top( ) const { return S[ t - 1 ]; }
    void pop( ) { if(t) --t; }
};

template <class Item> class QUEUE
{	Item * Q; int head, tail, n, N;
public:
    explicit QUEUE(int maxQ)
            : head(0), tail(0), n(0), N(maxQ), Q(new Item[maxQ + 1]) { }
    bool empty( ) const { return (head % N) == tail; }
    int size( ) const { return n; }
    void push(Item item) { Q[ tail++ ] = item; tail %= N; ++n; }
    Item front( ) const { return Q[ head % N ]; }
    void pop( ) { head++; head %= N; --n; }
};


class Node { char d;	 //тег узла
    Node * lft;	// левый сын
    //	Node  * mdl;	средний сын (если нужно)
    Node * rgt;	// правый сын
public:
    Node( ) : d('0'), lft(nullptr), rgt(nullptr) { } // конструктор узла
    ~Node( ){ if(rgt) delete rgt; // деструктор (уничтожает поддерево)
        if (lft) delete lft; }
    friend class Tree;	// дружественный класс «дерево»
} ;
// Класс «дерево в целом»
class Tree
{	Node * root;	// указатель на корень дерева
    char num, maxnum;		//счётчик тегов и максимальный тег
    int maxrow, offset;		//максимальная глубина, смещение корня
    char ** SCREEN;	// память для выдачи на экран
    void clrscr();	// очистка рабочей памяти
    Node* MakeNode(int depth);	// создание поддерева
    void OutNodes(Node * v, int r, int c); // выдача поддерева
    Tree (const Tree &);	// фиктивный конструктор копии
    Tree (Tree &&);		//копия с переносом (С++11)
    Tree operator = (const Tree &) const;	// фиктивное присваивание
    Tree operator = (Tree &&) const; //присваивание с переносом (С++11)
public:
    Tree(char num, char maxnum, int maxrow);
    ~Tree();
    void MakeTree() // ввод — генерация дерева
    { root = MakeNode(0); }
    bool exist( ) { return root != nullptr; } // проверка «дерево не пусто»
    int DFS( );	// обходы дерева
    int BFS( );
    void OutTree( );	// выдача на экран

};
// constructor
Tree ::	Tree(char nm, char mnm, int mxr):
        num(nm), maxnum(mnm), maxrow(mxr), offset(40), root(nullptr),
        SCREEN(new char * [maxrow])
{	for(int i = 0; i < maxrow; ++i) SCREEN[ i ] = new char[80]; }
//destructor
Tree :: ~Tree( ) { for(int i = 0; i < maxrow; ++i) delete [ ]SCREEN[i];
    delete [ ] SCREEN; delete root; }
Node * Tree :: MakeNode(int depth)
{ Node * v = nullptr;
    int Y = (depth < rand( )%6+1) && (num <= 'z');
//  Вариант: cout ≪ "Node (" ≪ num ≪ ',' ≪ depth ≪ ")1/0: "; cin ≫ Y;
    if (Y) {	// создание узла, если Y = 1
        v = new Node;
        v->d = num++;	 // разметка в прямом порядке (= «в глубину»)
        v->lft = MakeNode(depth+1);
//	 v->d = num++;          //вариант — во внутреннем
        v->rgt = MakeNode(depth+1);
//	 v->d = num++;		// вариант — в обратном
    }
    return v;
}
void Tree :: OutTree( )
{	clrscr( );
    OutNodes(root, 1, offset);
    for (int i = 0; i < maxrow; ++i)
    { SCREEN[ i ][ 79 ] = 0;
        cout << 'n' << SCREEN[ i ];
    }
    cout << '\n';
}

void Tree :: clrscr( )
{ for(int i = 0; i < maxrow; ++i)
        memset(SCREEN[ i ], '.', 80);
}
void Tree :: OutNodes(Node * v, int r, int c)
{ if (r && c && (c<80)) SCREEN[ r - 1 ][ c - 1 ] = v->d; // вывод метки
    if (r < maxrow) {
        if (v->lft) OutNodes(v->lft, r + 1, c - (offset >> r)); //левый сын
        // if (v->mdl) OutNode(v->mdl, r + 1, c);	— средний сын (если нужно)
        if (v->rgt) OutNodes(v->rgt, r + 1, c + (offset >> r)); //правый сын
    }
}int Tree :: DFS( )
{ const int MaxS = 20; // максимальный размер стека
    int count = 0;
    STACK <Node *> S(MaxS);  //создание стека указателей на узлы
    S.push(root); // QUEUE <- v
    while (!S.empty( )) //Пока стек не пуст…
    { Node * v = S.top( ); S.pop( ); // поднять узел из стека
        cout << v->d <<  '_'; ++count;       // выдать тег, счёт узлов
        if (v->rgt) S.push(v->rgt); // STACK <- (правый сын)
        if (v->lft) S.push(v->lft); // STACK <- (левый сын)
    }
    return count;
}

int Tree :: BFS( )
{ const int MaxQ = 20; //максимальный размер очереди
    int count = 0;
    QUEUE < Node * > Q(MaxQ);  //создание очереди указателей на узлы
    Q.push(root); // QUEUE <- root поместить в очередь корень дерева
    while (!Q.empty( )) //пока очередь не пуста
    { 	Node * v = Q.front( ); Q.pop( );// взять из очереди,
        //if(!(v->lft) && !(v->rgt)) cout << "List founded" << endl;
        cout << v->d << '_'; ++count; // выдать тег, счёт узлов
        if (v->lft) Q.push(v->lft); // QUEUE <- (левый сын) put -> push
        if (v->rgt) Q.push(v->rgt); // QUEUE <- (правый сын)
    }
    return count;
}
#endif //LESSON3_TREE_H
