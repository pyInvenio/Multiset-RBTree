#include <iostream>
#include "Node.h"
#include "RB_Iterator.h"
using namespace std;

//template<class T>
//rbiterator<T>::rbiterator() {
//	iter = nullptr;
//}

template <class T>
rbiterator<T> rbiterator<T>::operator++() {
	if (this->iter != nullptr) {
		this->iter = successor(this->iter);
		
	}
	return *this;
}
template <class T>
const rbiterator<T> rbiterator<T>::operator++(int) {
	rbiterator temp = *this;
	++(*this);
	return temp;
}
template <typename T>
rbiterator<T> rbiterator<T>::operator--() {
    if (this->iter != nullptr) {
        this->iter = predecessor(this->iter);

        return *this;
    }
    else return *this;
}

template <typename T>
const rbiterator<T> rbiterator<T>::operator--(int) {
	rbiterator temp = *this;
    --(*this);

    return temp;
}
