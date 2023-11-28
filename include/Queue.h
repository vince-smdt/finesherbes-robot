#ifndef QUEUE_H__
#define QUEUE_H__

template <class T>
class Queue {
private:
    struct Node {
        T data;
        Node* next = nullptr;
    };
    Node* first = nullptr;
    Node* last = nullptr;

    void do_unchecked_pop();

public:
    Queue() = default;                                                        // empty constructor
    Queue(Queue const& value);                                                // copy constructor
                                          // move constuctor
    Queue& operator=(Queue&& move) noexcept;                                  // move assignment operator
    ~Queue();                                                                 // destructor

    Queue& operator=(Queue const& rhs);
    
    bool empty() const {return first == nullptr;}
    int size() const;
    T& front() const;
    T& back() const;
    void push(const T& theData);
    void push(T&& theData);
    void pop();
    void swap(Queue& other) noexcept;


};

template <class T>
Queue<T>::Queue(Queue<T> const& value)  {
    try {
        for(auto loop = value.first; loop != nullptr; loop = loop->next)
            push(loop->data);
    }
    catch (...) {
        while(first != nullptr)
            do_unchecked_pop();
        throw;
    }
}

template <class T>
Queue<T>& Queue<T>::operator=(Queue<T> &&move) noexcept {
    move.swap(*this);
    return *this;
}

template <class T>
Queue<T>::~Queue() {
    while(first != nullptr) {
        do_unchecked_pop();
    }
}

template <class T>
int Queue<T>::size() const {
    int size = 0;
    for (auto current = first; current != nullptr; current = current->next)
        size++;
    return size;
}

template <class T>
T& Queue<T>::front() const {
    return first->data;
}

template <class T>
T& Queue<T>::back() const {
    return last->data;
}

template <class T>
void Queue<T>::push(const T& theData) {
    Node* newNode = new Node;
    newNode->data = theData;
    newNode->next = nullptr;

    if(first == nullptr) {
        first = last = newNode;
    }

    else {
        last->next = newNode;
        last = newNode;
    }
}

template <class T>
void Queue<T>::pop() {
    do_unchecked_pop();
}

template <class T>
void Queue<T>::do_unchecked_pop() {
    Node* tmp = first->next;
    delete tmp;
    first = tmp;
}


#endif