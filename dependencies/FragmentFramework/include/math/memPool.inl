/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

///=============================================================================
template <class T> ffw::memPool<T>::memPool(size_t Increment, size_t Aligment){
    buffer = NULL;
    bufferSize = 0;
    increment = Increment;
    aligment = Aligment;
}

///=============================================================================
template <class T> ffw::memPool<T>::~memPool(){
    if(buffer != NULL)delete[] buffer;
}

///=============================================================================
template <class T> size_t ffw::memPool<T>::allocate(size_t Size){
    size_t newPos = 0;
    size_t i = 0;
    size_t newSize = getAligned(Size);

    for(; i < blocks.size(); i++){
        size_t test = blocks[i].pos - newPos;

        if(test >= newSize)break;
        else newPos = blocks[i].pos + blocks[i].size;
    }

    if(newPos + newSize >= bufferSize)increaseSize(newPos + newSize);

    for(size_t i = newPos+Size; i < newPos+newSize; i++)buffer[i] = 0;

    memBlock<T> block;
    block.pos = newPos;
    block.size = newSize;
    //std::cout << "adding at: " << block.pos << " size: " << block.size << std::endl;
    blocks.insert(blocks.begin()+i, block);
    return newPos;
}

///=============================================================================
template <class T> bool ffw::memPool<T>::release(size_t Ptr){
    bool result = false;
    for(size_t i = 0; i < blocks.size(); i++){
        if(Ptr == blocks[i].pos){
            //std::cout << "erasing at: " << blocks[i].pos << " size: " << blocks[i].size << std::endl;
            for(size_t p = blocks[i].pos; p < blocks[i].pos + blocks[i].size; p++){
                buffer[p] = 0;
            }
            blocks.erase(blocks.begin()+i);
            result = true;
        }
    }
    if(!result)return false;
    if(blocks.size() > 0)
        decreaseSize(blocks[blocks.size()-1].pos + blocks[blocks.size()-1].size);
    return true;
}

///=============================================================================
template <class T> T* ffw::memPool<T>::begin(){
    return &buffer[0];
}

///=============================================================================
template <class T> T* ffw::memPool<T>::end(){
    return (&buffer[bufferSize-1]) +1;
}

///=============================================================================
template <class T> size_t ffw::memPool<T>::getAligned(size_t Value){
    if(Value % aligment > 0)
        return (Value/aligment)*aligment +aligment;
    return Value;
}

///=============================================================================
template <class T> void ffw::memPool<T>::increaseSize(size_t Min){
    size_t inc = 0;
    while(inc < Min-bufferSize)inc += increment;

    T* temp = new T[bufferSize+inc];
    if(buffer != NULL){
        std::copy(buffer, buffer + bufferSize, temp);
        delete[] buffer;
    }
    buffer = temp;
    bufferSize = bufferSize+inc;
}

///=============================================================================
template <class T> void ffw::memPool<T>::decreaseSize(size_t Max){
    if(buffer == NULL)return;

    size_t dec = bufferSize;
    while(dec >= Max+increment)dec -= increment;
    dec = bufferSize - dec;

    if(dec == 0)return;

    if(buffer-dec > 0){
        T* temp = new T[bufferSize-dec];
        std::copy(buffer, buffer + bufferSize - dec, temp);
        delete[] buffer;
        buffer = temp;

    } else {
        delete[] buffer;
        buffer = NULL;
    }
}
