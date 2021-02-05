#pragma once

#define OutOfRange "Error! Index is out of range!"

template<typename T>
class LinkedList {
private:
    struct List {
        T item = 0;
        List *next = nullptr;
    };

    List *head = nullptr;
    int size = 0;

public:

    LinkedList() : size(0) {}

    LinkedList(T *items, int size) : LinkedList() {
        if (size < 0) throw OutOfRange;

        List **elem = &(this->head);
        for (int i = 0; i < size; i++) {
            *elem = new List;
            (*elem)->item = items[i];
            elem = &((*elem)->next);
        }

        this->size = size;
    }


    LinkedList(int size) : LinkedList() {
        if (size < 0) throw OutOfRange;

        List **elem = &(this->head);
        for (int i = 0; i < size; i++) {
            *elem = new List;
            (*elem)->item = T();
            elem = &((*elem)->next);
        }

        this->size = size;
    }


    LinkedList(const LinkedList<T> &list) {
        List *elem = list.head;
        List **new_elem = &(this->head);

        for (int i = 0; i < list.size; i++, elem = elem->next) {
            *new_elem = new List;
            (*new_elem)->item = elem->item;
            new_elem = &((*new_elem)->next);
        }

        this->size = list.size;
    }

    virtual ~LinkedList() {
        List *elem = this->head;
        List *next;
        while (elem != nullptr) {
            next = elem->next;
            delete elem;
            elem = next;
        }

        this->size = 0;
    }


    T GetFirst() const {
        if (this->size == 0) throw OutOfRange;

        return this->head->item;
    }

    T GetLast() const {
        if (this->size == 0) throw OutOfRange;

        List *elem = this->head;
        while (elem->next != nullptr) elem = elem->next;

        return elem->item;
    }

    T Get(int index) const {
        if (index < 0 || index >= this->size) throw OutOfRange;

        List *elem = this->head;
        for (int i = 0; i < index; i++) elem = elem->next;

        return elem->item;
    }

    void Set(const T &item, int index) {
        if (index < 0 || index >= this->size) throw OutOfRange;

        List *elem = this->head;
        for (int i = 0; i < index; i++) elem = elem->next;
        elem->item = item;
    }

    LinkedList<T> *GetSubList(int start, int end) const {
        if (start < 0 || start >= this->size || end < 0 || end > this->size) throw OutOfRange;

        LinkedList<T> *new_list = new LinkedList<T>();

        List *elem = this->head;
        List **new_elem = &new_list->head;

        for (int i = 0; i < end; i++, elem = elem->next)
            if (i >= start) {
                *new_elem = new List;
                (*new_elem)->item = elem->item;
                new_elem = &((*new_elem)->next);
            }

        new_list->size = end - start;

        return new_list;
    }

    int GetSize() const {
        return this->size;
    }

    void Append(const T &item) {
        List **elem = &(this->head);

        while (*elem != nullptr) elem = &((*elem)->next);
        (*elem) = new List;
        (*elem)->item = item;

        this->size++;
    }

    void Prepend(const T &item) {
        List *elem = new List{item, this->head};
        this->head = elem;

        this->size++;
    }

    void InsertAt(const T &item, int index) {
        if (index < 0 || index > this->size) throw OutOfRange;

        List temp;
        temp.next = this->head;
        List *elem = &temp;

        for (int i = 0; i < index; i++)
            elem = elem->next;

        elem->next = new List{item, elem->next};
        this->head = temp.next;

        this->size++;
    }

//    LinkedList<T> *Concat(const LinkedList<T> &list) const {
//        List *first = this->head;
//        List *second = list.head;
//
//        LinkedList<T> *newList = new LinkedList<T>();
//        List **elem = &(newList->head);
//        while (first != nullptr) {
//            *elem = new List;
//            (*elem)->item = first->item;
//            (*elem)->next = first->next;
//            first = first->next;
//            elem = &((*elem)->next);
//        }
//        while (second != nullptr) {
//            *elem = new List;
//            (*elem)->item = second->item;
//            (*elem)->next = second->next;
//            second = second->next;
//            elem = &((*elem)->next);
//        }
//
//        newList->size = this->size + list.size;
//        return newList;
//    }

    bool operator==(const LinkedList<T> &array) const {
        if (this->size != array.size) return false;

        for (int i = 0; i < this->size; i++)
            if (this->Get(i) != array.Get(i)) return false;

        return true;
    }
};