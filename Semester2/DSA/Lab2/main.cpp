#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"

#include "SortedIndexedList.h"

bool relation(TComp e1, TComp e2) {
    if (e1 <= e2) {
        return true;
    }
    else {
        return false;
    }
}

int main(){
    testAll();
    testAllExtended();
    //std::cout<<"Finished IL Tests!"<<std::endl;
    //system("pause");

    /*SortedIndexedList list = SortedIndexedList(relation);
    list.add(10);
    list.add(7);
    list.add(4);
    list.add(6);

    int elem1 = list.getElement(0);
    int elem2 = list.getElement(1);
    int elem3 = list.getElement(2);
    int elem4 = list.getElement(3);
    std::cout<<elem1<<"\n";
    std::cout<<elem2<<"\n";
    std::cout<<elem3<<"\n";
    std::cout<<elem4<<"\n";

    int position1 = list.search(4);
    int position2 = list.search(6);
    int position3 = list.search(7);
    int position4 = list.search(10);

    std::cout<<position1<<"\n";
    std::cout<<position2<<"\n";
    std::cout<<position3<<"\n";
    std::cout<<position4<<"\n";

    list.remove(2);
    int elem1 = list.getElement(0);
    int elem2 = list.getElement(1);
    int elem3 = list.getElement(2);
    std::cout<<elem1<<"\n";
    std::cout<<elem2<<"\n";
    std::cout<<elem3<<"\n";*/
    return 0;
}