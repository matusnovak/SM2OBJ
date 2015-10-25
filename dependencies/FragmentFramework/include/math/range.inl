/*** This file is part of FragmentFramework project ***/

///=============================================================================
template <class T>
ffw::rangeIterator<T>::rangeIterator(T Value){
    value = Value;
}

///=============================================================================
template <class T>
bool ffw::rangeIterator<T>::operator != (const ffw::rangeIterator<T>& Other) const{
    return value != Other.value;
}

///=============================================================================
template <class T>
const T& ffw::rangeIterator<T>::operator*() const {
    return value;
}

///=============================================================================
template <class T>
ffw::rangeIterator<T>& ffw::rangeIterator<T>::operator ++ (){
    value++;
    return *this;
}

///=============================================================================
template <class T>
ffw::range<T>::range(T Min, T Max){
    min = Min;
    max = Max;
}

///=============================================================================
template <class T>
ffw::range<T>::range(T Max){
    min = 0;
    max = Max;
}

///=============================================================================
template <class T>
ffw::rangeIterator<T> ffw::range<T>::begin(){
    return rangeIterator<T>(min);
}

///=============================================================================
template <class T>
ffw::rangeIterator<T> ffw::range<T>::end(){
    return rangeIterator<T>(max);
}
