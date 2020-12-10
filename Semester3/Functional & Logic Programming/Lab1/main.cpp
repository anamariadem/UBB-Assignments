#include <iostream>

using namespace std;

struct LinkedListNode{
    int info;
    LinkedListNode* next;
};

LinkedListNode* creare_rec(){
    int x;
    cout<<"x=";
    cin>>x;
    if (x==0)
        return nullptr;
    else{
        LinkedListNode* p=new LinkedListNode();
        p->info=x;
        p->next=creare_rec();
        return p;
    }
}

void tipar_rec(LinkedListNode* p){
    if (p!=nullptr){
        cout<<p->info<<" ";
        tipar_rec(p->next);
    }
}
/*
 * getLastElement(l1l2..ln) = {
 *      0, l1...ln empty (n=0)
 *      l1, l2...ln empty
 *      getLastElement(l2...ln), otherwise
 * }
 */
int getLastElement(LinkedListNode* head){
    if(head == nullptr)
        return 0;
    else if (head->next == nullptr)
        return head->info;
    else
        return getLastElement(head->next);
}

/*
 * deleteElements(l1...ln, index, givenNumber) {
 *      [], if l1...ln empty
 *      delete(l2..ln, index+1, givenNumber), index mod n = 0
 *      l1 U delete(l2..ln, index + 1, givenNumber), otherwise
 * }
 */
LinkedListNode* deleteElements(LinkedListNode* head, int index, int givenNumber){
    if(head == nullptr)
        return nullptr;
    if(index % givenNumber == 0){
        return deleteElements(head->next, index + 1, givenNumber);
    } else{
        LinkedListNode* node = deleteElements(head->next, index+1, givenNumber);
        head->next = node;
        return head;
    }
}

/*
 * copyList(l1...ln) = {
 *      [], l1...ln empty
        l1 U copyList(l2..ln), otherwise
 * }
 */
LinkedListNode* copyList(LinkedListNode* head){
    if (head == nullptr)
        return nullptr;
    else{
        LinkedListNode* p=new LinkedListNode();
        p->info=head->info;
        p->next=copyList(head->next);
        return p;
    }
}

LinkedListNode* deleteElementsWrapper(LinkedListNode* head, int index, int givenNumber){
    LinkedListNode* copiedList = copyList(head);
    return deleteElements(copiedList, index, givenNumber);
}

void distrug_rec(LinkedListNode* p){
    if (p!= nullptr){
        distrug_rec(p->next);
        delete p;
    }
}


int main() {
    LinkedListNode* head = creare_rec();
    //tipar_rec(head);
    cout<<"The last element of the list is: "<<getLastElement(head)<<'\n';

    LinkedListNode* newHead = deleteElementsWrapper(head, 1, 2);
    tipar_rec(newHead);
    tipar_rec(head);
    distrug_rec(head);
    return 0;
}
