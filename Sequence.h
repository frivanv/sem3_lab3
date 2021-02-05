#pragma once

#include "LinkedList.h"
#include "DynamicArray.h"

template<typename T>
class Sequence {
protected:
    int size = 0;
public:

    virtual T GetFirst() const = 0;

    virtual T GetLast() const = 0;

    virtual T Get(int index) const = 0;

    virtual int GetSize() const {
        return this->size;
    }

    virtual Sequence<T> *GetSubSequence(int start_index, int end_index) const = 0;

    virtual void Set(const T &item, int index) = 0;

    virtual void Append(const T &item) = 0;

    virtual void Prepend(const T &item) = 0;

    virtual void InsertAt(const T &item, int index) = 0;

    virtual Sequence<T> *Concat(const Sequence<T> &Sequence) const = 0;

    virtual bool operator==(const Sequence<T> &seq) {
        if (this->size != seq.size) return false;

        for (int i = 0; i < this->size; i++) {
            if (this->Get(i) != seq.Get(i)) return false;
        }
        return true;
    }
};


template<typename T>
class ArraySequence : public Sequence<T> {
private:
    DynamicArray<T> *array;

public:
    ArraySequence() {
        this->array = new DynamicArray<T>();
        this->size = 0;
    }

    ArraySequence(const ArraySequence<T> &Sequence) {
        this->array = new DynamicArray<T>(*Sequence.array);
        this->size = Sequence.size;
    }

    ArraySequence(DynamicArray<T> *items) {
        this->array = items;
        this->size = items->GetSize();
    }

    ArraySequence(T *items, int size) {
        this->array = new DynamicArray<T>(items, size);
        this->size = size;
    }

    ArraySequence(int size) {
        this->array = new DynamicArray<T>(size);
        this->size = size;
    }

    virtual ~ArraySequence() {
        delete this->array;
        this->size = 0;
    }

    virtual T GetFirst() const override {
        return this->array->Get(0);
    }

    virtual T GetLast() const override {
        return this->array->Get(this->size - 1);
    }

    virtual T Get(int index) const override {
        return this->array->Get(index);
    }

    virtual void Set(const T &item, int index) override {
        if (index < 0 || index >= this->size) throw OutOfRange;

        this->array->Set(item, index);
    }


    virtual ArraySequence<T> *GetSubSequence(int start, int end) const override {
        if (start < 0 || start >= this->size || end < 0 || end > this->size) throw OutOfRange;

        DynamicArray<T> *sub_array = new DynamicArray<T>(end - start);
        for (int i = 0; i < end - start; i++) sub_array->Set(this->array->Get(i + start), i);

        ArraySequence<T> *sub_sequence = new ArraySequence<T>(sub_array);

        return sub_sequence;
    }

    virtual void Append(const T &item) override {
        this->array->Resize(this->size + 1);
        this->array->Set(item, this->size);
        this->size++;
    }

    virtual void Prepend(const T &item) override {
        this->array->Resize(this->size + 1);
        T a = this->array->Get(0);
        T b;
        for (int i = 0; i < this->size; i++) {
            b = a;
            a = this->array->Get(i + 1);
            this->array->Set(b, i + 1);
        }
        this->array->Set(item, 0);

        this->size++;
    }

    virtual void InsertAt(const T &item, int index) override {
        if (index < 0 || index > this->size) throw OutOfRange;

        this->array->Resize(this->size + 1);
        T a = this->array->Get(index);
        T b;
        for (int i = index; i < this->size; i++) {
            b = a;
            a = this->array->Get(i + 1);
            this->array->Set(b, i + 1);
        }
        this->array->Set(item, index);

        this->size++;
    }

    virtual ArraySequence<T> *Concat(const Sequence<T> &Sequence) const override {
        DynamicArray<T> *arr = new DynamicArray<T>(this->size + Sequence.GetSize());
        ArraySequence<T> *new_sequence = new ArraySequence<T>(arr);

        for (int i = 0; i < this->size; i++)
            new_sequence->Set(this->Get(i), i);

        for (int i = 0; i < Sequence.GetSize(); i++)
            new_sequence->Set(Sequence.Get(i), i + this->size);

        return new_sequence;
    }
};


template<typename T>
class ListSequence : public Sequence<T> {
protected:
    LinkedList<T> *list;
public:
    ListSequence() {
        this->list = new LinkedList<T>();
        this->size = 0;
    }

    ListSequence(const ListSequence<T> &Sequence) {
        this->list = new LinkedList<T>(*Sequence.list);
        this->size = Sequence.size;
    }

    ListSequence(LinkedList<T> *list) {
        this->list = list;
        this->size = list->GetSize();
    }

    ListSequence(T *items, int size) {
        this->list = new LinkedList<T>(items, size);
        this->size = size;
    }

    explicit ListSequence(int size) {
        this->list = new LinkedList<T>(size);
        this->size = size;
    }

    virtual ~ListSequence() {
        delete this->list;
        this->size = 0;
    }

    T GetFirst() const override {
        return this->list->GetFirst();
    }

    T GetLast() const override {
        return this->list->GetLast();
    }

    T Get(int index) const override {
        return this->list->Get(index);
    }

    ListSequence<T> *GetSubSequence(int start, int end) const override {
        LinkedList<T> *sub_list = this->list->GetSubList(start, end);
        auto *Sequence = new ListSequence<T>(sub_list);
        return Sequence;
    }

    void Set(const T &item, int index) override {
        this->list->Set(item, index);
    }

    void Append(const T &item) override {
        this->list->Append(item);
        this->size++;
    }

    void Prepend(const T &item) override {
        this->list->Prepend(item);
        this->size++;
    }

    void InsertAt(const T &item, int index) override {
        this->list->InsertAt(item, index);
        this->size++;
    }

    ListSequence<T> *Concat(const Sequence<T> &Sequence) const override {
        auto *new_sequence = new ListSequence<T>();

        for (int i = 0; i < this->size; i++) new_sequence->Append(this->Get(i));

        for (int i = 0; i < Sequence.GetSize(); i++) new_sequence->Append(Sequence.Get(i));

        return new_sequence;
    }
};