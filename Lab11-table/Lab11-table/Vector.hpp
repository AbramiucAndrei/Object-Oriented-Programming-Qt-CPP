//
// Created by Alex Balta on 02.04.2024.
//

#pragma once

#include <cstddef>
#include <algorithm>

template<typename TElem>
class Iterator;

/*
 * VECTOR HPP
 */

template<typename TElem>
class Vector {
private:
    size_t len{0}; // Current length of the list
    size_t capacity{1}; // Current capacity of the list
    TElem *items; // Array to store list elements

    /**
     * Helper function to resize the list when needed.
     */
    void resizeList();

public:
    /**
     * Default constructor.
     */
    Vector();

    /**
     * Copy constructor.
     * @param other The list to be copied.
     */
    Vector(const Vector &other);

    /**
     * Move constructor.
     * @param other The list to be copied.
     */
    Vector(Vector &&other) noexcept;

    /**
     * Destructor.
     */
    ~Vector();

    /**
     * Copy Assignment operator.
     * @param other The list to be assigned.
     * @return Reference to the assigned list.
     */
    Vector &operator=(const Vector &other);

    /**
     * Move Assignment operator.
     * @param other The list to be assigned.
     * @return Reference to the assigned list.
     */
    Vector &operator=(Vector &&other) noexcept;

    /**
     * Adds an element to the end of the list.
     * @param element The element to be added.
     */
    void push_back(const TElem &element);

    /**
     * Removes the element at the position pointed by the iterator.
     * @param iterator The iterator pointing to the element to be removed.
     */
    void erase(Iterator<TElem> iterator);

    /**
    * Retrieves the element at the specified position.
    * @param position The position of the element to retrieve.
    * @return Reference to the element at the specified position.
    */
    TElem &operator[](size_t position);

    /**
     * Sets the element at the specified position given by the iterator.
     * @param iter An iterator pointing to the position at which to set the element.
     * @param element The element to set.
     */
    void set(Iterator<TElem> &iter, const TElem &element);

    /**
     * Returns the current size of the list.
     * @return The number of elements in the list.
     */
    [[nodiscard]] size_t size() const;

    friend class Iterator<TElem>;

    /**
    * Returns an iterator pointing to the beginning of the list.
    * @return An iterator pointing to the beginning of the list.
    */
    Iterator<TElem> begin();

    /**
     * Returns an iterator pointing to the end of the list.
     * @return An iterator pointing to the end of the list.
     */
    Iterator<TElem> end();
};

/*
 * VECTOR CPP
 */

template<typename TElem>
Vector<TElem>::Vector() : items{new TElem[1]} {}

template<typename TElem>
Vector<TElem>::Vector(const Vector<TElem> &other) : len{other.len},
                                                    capacity{other.capacity},
                                                    items{new TElem[other.capacity]} {
    std::copy(other.items, other.items + other.len, items);
}

template<typename TElem>
Vector<TElem>::Vector(Vector<TElem> &&other) noexcept : len{other.len},
                                                        capacity{other.capacity},
                                                        items{other.items} {
    other.items = nullptr;
    other.len = 0;
    other.capacity = 0;
}

template<typename TElem>
Vector<TElem> &Vector<TElem>::operator=(const Vector<TElem> &other) {
    if (this == &other) {
        return *this;
    }

    delete[] items;

    len = other.len;
    capacity = other.capacity;
    items = new TElem[capacity];

    std::copy(other.items, other.items + other.len, items);

    return *this;
}

template<typename TElem>
Vector<TElem> &Vector<TElem>::operator=(Vector<TElem> &&other) noexcept {
    if (this == &other) {
        return *this;
    }

    delete[] items;

    items = other.items;
    len = other.len;
    capacity = other.capacity;

    other.items = nullptr;
    other.len = 0;
    other.capacity = 0;

    return *this;
}

template<typename TElem>
Vector<TElem>::~Vector() {
    delete[] items;
}

template<typename TElem>
void Vector<TElem>::push_back(const TElem &element) {
    if (len == capacity) {
        resizeList();
    }

    items[len++] = element;
}

template<typename TElem>
void Vector<TElem>::erase(Iterator<TElem> iterator) {
    auto nextIt = iterator;
    ++nextIt;

    while (nextIt.valid()) {
        *iterator = *nextIt;
        ++iterator;
        ++nextIt;
    }

    len--;
}

template<typename TElem>
TElem &Vector<TElem>::operator[](size_t position) {
    return items[position];
}

template<typename TElem>
void Vector<TElem>::set(Iterator<TElem> &iter, const TElem &element) {
    *iter = element;
}

template<typename TElem>
size_t Vector<TElem>::size() const {
    return len;
}

template<typename TElem>
void Vector<TElem>::resizeList() {
    capacity *= 2;

    auto temp = new TElem[capacity];
    std::copy(items, items + len, temp);

    delete[] items;
    items = temp;
}

template<typename TElem>
Iterator<TElem> Vector<TElem>::begin() {
    return Iterator<TElem>(*this);
}

template<typename TElem>
Iterator<TElem> Vector<TElem>::end() {
    return Iterator<TElem>(*this, len);
}

