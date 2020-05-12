//
// Created by Ana Maria on 27/03/2020.
//

#ifndef ASSIGNMENT6_DYNAMICVECTOR_H
#define ASSIGNMENT6_DYNAMICVECTOR_H




template <typename T=int>
class DynamicVector{
private:
    int capacity{}, size{};
    T* elements;

    void resizeDynamicVector(int factor =2);

public:
    //constructor
    explicit DynamicVector(int capacity = 2);

    // copy constructor for a Dynamic Vector
    DynamicVector(const DynamicVector& dynamicVectorToCopy);

    // overload of the assignment operator
    DynamicVector& operator=(const DynamicVector& dynamicVector);

    T& operator[](int position);

    T& getElement(int position);

    // adds a new element to the dynamic vector
    void addToDynamicVector(T element);

    int getPositionOfElement(T element);

    // deletes an element from the dynamic vector
    void deleteFromDynamicVector(int& positionInArray);

    // updates an element from the dynamic vector
    void updateElementInDynamicArray(int& positionInArray, T& newElement);

    int getSizeOfVector() const;

    ~DynamicVector();

public:
    class iterator{
    private:
        T* pointer;

    public:
        iterator()= default;
        iterator(T* constructorPointer): pointer{constructorPointer } {}
        T& operator*();
        bool operator!=(const iterator& iterator);
        bool operator==(const iterator& iterator);
        iterator operator++();
        iterator operator++(int);
    };

    iterator begin();

    iterator end();
};

template <typename T>
inline DynamicVector<T>::DynamicVector(int capacity){
    this->capacity = capacity;
    this->size = 0;
    this->elements = new T[this->capacity];
}

template <typename T>
inline DynamicVector<T>::~DynamicVector(){
    delete[] this->elements;
}

template <typename T>
inline int DynamicVector<T>::getSizeOfVector() const {
    return this->size;
}

template <typename T>
inline void DynamicVector<T>::resizeDynamicVector(int factor) {
    this->capacity *= factor;
    T* newDynamicArray = new T[this->capacity];

    for(int i=0; i<this->size;i++)
        newDynamicArray[i] = this->elements[i];

    delete [] this->elements;
    this->elements = newDynamicArray;
}

template <typename T>
inline int DynamicVector<T>::getPositionOfElement(T element) {
    for(int i=0; i<this->size;i++)
        if(this->elements[i] == element)
            return i;
    return -1;
}

template <typename T>
inline void DynamicVector<T>::addToDynamicVector(T element) {
    if(this->size == this->capacity)
        this->resizeDynamicVector();

    this->elements[this->size++] = element;
}

template <typename T>
inline void DynamicVector<T>::deleteFromDynamicVector(int& positionInArray) {
    for(int i=positionInArray; i< this->size ;i++)
        this->elements[i] = this->elements[i+1];
    this->size--;
}

template <typename T>
inline void DynamicVector<T>::updateElementInDynamicArray(int & positionInArray, T& newElement) {
    this->elements[positionInArray] = newElement;
}

template <typename T>
inline T& DynamicVector<T>::operator[](int position) {
    return this->elements[position];
}

template <typename T>
inline T& DynamicVector<T>::getElement(int position) {
    return this->elements[position];
}

template <typename T>
inline DynamicVector<T>::DynamicVector(const DynamicVector &dynamicVectorToCopy) {
    this->capacity = dynamicVectorToCopy.capacity;
    this->size = dynamicVectorToCopy.size;

    this->elements = new T[this->capacity];
    for(int i=0; i<this->size;i++)
        this->elements[i] = dynamicVectorToCopy.elements[i];
}

template <typename T>
inline DynamicVector<T>& DynamicVector<T>::operator=(const DynamicVector& dynamicVector) {
    if(this == &dynamicVector)
        return *this;

    this->capacity = dynamicVector.capacity;
    this->size = dynamicVector.size;
    delete [] this->elements;

    this->elements = new T[this->capacity];
    for(int i=0; i<this->size;i++)
        this->elements[i] = dynamicVector.elements[i];

    return *this;
}

template <typename T>
inline typename DynamicVector<T>::iterator DynamicVector<T>::begin() {
    return iterator{this->elements};
}

template <typename T>
inline typename DynamicVector<T>::iterator DynamicVector<T>::end() {
    return iterator{this->elements + this->size};
}

template <typename T>
inline T& DynamicVector<T>::iterator::operator*() {
    return *this->pointer;
}

template <typename T>
inline bool DynamicVector<T>::iterator::operator!=(const class DynamicVector::iterator & iterator) {
    return this->pointer != iterator.pointer;
}

template <typename T>
inline bool DynamicVector<T>::iterator::operator==(const class DynamicVector::iterator & iterator) {
    return this->pointer == iterator.pointer;
}

template <typename T>
inline typename DynamicVector<T>::iterator DynamicVector<T>::iterator::operator++() {
    this->pointer++;
    return *this;
}

template <typename T>
inline typename DynamicVector<T>::iterator DynamicVector<T>::iterator::operator++(int ) {
    iterator auxiliar = *this;
    this->pointer++;
    return auxiliar;
}
#endif //ASSIGNMENT6_DYNAMICVECTOR_H
