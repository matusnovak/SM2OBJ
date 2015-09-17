template <class T>
inline ffw::ringBuffer<T>::ringBuffer(){
	size = 0;
	tail.store(0);
	head.store(0);
}

template <class T>
inline ffw::ringBuffer<T>::ringBuffer(size_t Size){
	tail.store(0);
	head.store(0);
	elements.resize(Size+1);
	size = Size;
}

template <class T>
inline ffw::ringBuffer<T>::~ringBuffer(){
}

template <class T>
inline void ffw::ringBuffer<T>::create(size_t Size){
	reset();
	elements.resize(Size+1);
	size = Size;
}

template <class T>
inline T* ffw::ringBuffer<T>::back(){
	size_t current = head.load();
	if(current == tail.load())return NULL;

	return &elements[current];
}

template <class T>
inline bool ffw::ringBuffer<T>::push(const T& Item){
	size_t current = tail.load();
	size_t next = (current + 1) % (size + 1);
	if(next == head.load() || size == 0)return false;

	elements[current] = Item;
	tail.store(next);
	return true;
}

template <class T>
inline bool ffw::ringBuffer<T>::pop(T* Item){
	size_t current = head.load();
	if(current == tail.load())return false;

	*Item = elements[current];
	head.store((current + 1) % (size + 1));
	return true;
}

template <class T>
inline size_t ffw::ringBuffer<T>::getRange() const {
	return size;
}

template <class T>
inline size_t ffw::ringBuffer<T>::getTail() const {
	return tail.load();
}

template <class T>
inline size_t ffw::ringBuffer<T>::getHead() const {
	return head.load();
}

template <class T>
inline size_t ffw::ringBuffer<T>::getSize() const {
	size_t currentTail = tail.load();
	size_t currentHead = head.load();
	if(currentTail == currentHead)return 0;

	//std::cout << "ret size head: " << currentHead << " tail: " << currentTail << std::endl;

	if(currentTail > currentHead){
        return currentTail - currentHead;
	}

	//if(tail_ > head_){
        return size - currentHead + currentTail +1;
	//}

    //return 0;
}

template <class T>
inline bool ffw::ringBuffer<T>::isFull() const {
	size_t next = (tail.load() + 1) % (size + 1);
	return (next == head.load());
}

template <class T>
inline bool ffw::ringBuffer<T>::isEmpty() const {
	return (tail.load() == head.load());
}

template <class T>
inline void ffw::ringBuffer<T>::clear(){
	elements.clear();
	tail.store(0);
	head.store(0);
}

template <class T>
inline void ffw::ringBuffer<T>::reset(){
	tail.store(0);
	head.store(0);
}
