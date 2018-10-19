#include <iostream>
#include <ctime>
#include <conio.h>

#include "source/Tree.h"
using namespace std;
int main() {
    int n = 0;
    Tree Tr('a', 'z', 8);
    srand(time(nullptr));
    setlocale(LC_ALL, "Russian");
    Tr.MakeTree( );
    if(Tr.exist( )) {
        Tr.OutTree( );
        cout << '\n' << "Обход в глубину: ";
        n = Tr.DFS( );
        cout << " Пройдено узлов = " << n;
        cout << '\n' << "Обход в ширину: ";
        n = Tr.BFS( );
        cout << " Пройдено узлов = " << n;
    }
    else cout << "Дерево пусто!";
    cout << '\n' << "=== Конец ===";

}
