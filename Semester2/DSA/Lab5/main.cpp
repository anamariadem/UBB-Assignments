#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"
#include "SortedMultiMap.h"
#include "SMMIterator.h"

bool rel(int e1, int e2){
    return e1<=e2;
}


int main(){
    testExtraOp();
    std::cout<<"Extra Op Done\n";
    testAll();
    testAllExtended();

    std::cout<<"Finished SMM Tests!"<<std::endl;
    /*{
        auto smm = SortedMultiMap{rel};
        smm.add(7,1);
        smm.add(7, 35);
        smm.add(21, 34);
        smm.add(28,0);
        smm.add(1, 10);
        //smm.add(14, 19);
        smm.add(1, 100);
        smm.add(16, 6);
        smm.add(35, 78);
        smm.myPrint();
        SMMIterator it = smm.iterator();
        it.first();
        while (it.valid()){
            TElem e = it.getCurrent();
            cout<<e.first <<" " <<e.second<<'\n';
            it.next();
        }
    }*/
    return 0;
}
