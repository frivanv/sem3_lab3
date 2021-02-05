#pragma once

#define OutOfRange "Error! Index is out of range!"

template<typename T>
class DynamicArray {
private:
    T *item = nullptr;
    int size = 0;
public:
    DynamicArray() : size(0) {}

    DynamicArray(int size) : size(size) {
        if (size < 0) throw OutOfRange;
        this->item = new T[size];
    }


    DynamicArray(T *items, int size) : DynamicArray(size) {
        for (int i = 0; i < size; i++) this->item[i] = items[i];
    }

    DynamicArray(const DynamicArray<T> &array, int size) : DynamicArray(size) {
        if (size > array.size) throw OutOfRange;

        for (int i = 0; i < size; i++) this->item[i] = array.item[i];
    }

    DynamicArray(const DynamicArray<T> &array) : DynamicArray(array.item, array.size) {}

    virtual ~DynamicArray() {
        this->size = 0;
        delete[] this->item;
    }


    T Get(int index) const {
        if (index < 0 || index >= this->size) throw OutOfRange;
        return this->item[index];
    }

    int GetSize() const {
        return this->size;
    }

    void Set(const T &elem, int index) {
        if (index < 0 || index >= this->size) throw OutOfRange;
        this->item[index] = elem;
    }

    void Resize(int val) {
        if (val < 0) throw OutOfRange;

        T *newArr = new T[val];
        if (val > this->size)
            for (int i = 0; i < this->size; i++) newArr[i] = item[i];
        else
            for (int i = 0; i < val; i++) newArr[i] = item[i];
        delete[] item;
        this->item = newArr;
        this->size = val;
    }

    bool operator==(const DynamicArray<T> &array) const {
        if (this->size != array.size) return false;

        for (int i = 0; i < this->size; i++)
            if (this->Get(i) != array.Get(i)) return false;

        return true;
    }
};