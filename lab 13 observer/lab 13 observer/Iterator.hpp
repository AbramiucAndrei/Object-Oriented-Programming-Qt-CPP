//
// Created by Mihai Adomnitei on 13.04.2024.
//

#pragma once

#include <cstddef>
#include <algorithm>
#include "Vector.hpp"

/*
 * ITERATOR HPP
 */

template<typename TElem>
class Iterator {
private:
    const Vector<TElem> &list; // Reference to the list being iterated
    size_t index; // Current index of the iterator within the list
public:
    /**
     * Constructor with list reference parameter
     * @param list a reference to the list that is being iterated
     */
    [[maybe_unused]] explicit Iterator(Vector<TElem> &list);

    /**
     * Constructor with list reference and starting index parameters
     * @param list a reference to the list that is being iterated
     * @param index a position in the list
     */
    [[maybe_unused]] Iterator(Vector<TElem> &list, size_t index);

    /**
     * Checks if the iterator is still within the bounds of the list.
     * @return true if the iterator is valid, false otherwise.
     */
    [[nodiscard]] bool valid() const;

    /**
     * Dereferences the iterator to retrieve the element at the current position.
     * @return Reference to the element at the current iterator position.
     */
    TElem &operator*();

    /**
     * Prefix increment operator to move the iterator to the next position.
     * @return Reference to the iterator after increment.
     */
    Iterator &operator++();

    /**
     * Equality comparison operator.
     * @param other Another iterator to compare with.
     * @return true if the iterators are equal, false otherwise.
     */
    bool operator==(const Iterator &other);

    /**
     * Inequality comparison operator.
     * @param other Another iterator to compare with.
     * @return true if the iterators are not equal, false otherwise.
     */
    bool operator!=(const Iterator &other);
    Iterator(const Iterator& other) :list{other.list}, index{other.index} {}
    Iterator& operator=(const Iterator& other) {
        if (this != &other) { // protect against invalid self-assignment
            index = other.index;
        }
        return *this;
    }

};

/*
 * ITERATOR CPP
 */

template<typename TElem>
[[maybe_unused]] Iterator<TElem>::Iterator(Vector<TElem> &list) : list{list}, index{0} {}

template<typename TElem>
[[maybe_unused]] Iterator<TElem>::Iterator(Vector<TElem> &list, size_t index) : list{list}, index{index} {}

template<typename TElem>
bool Iterator<TElem>::valid() const {
    return index < list.len;
}

template<typename TElem>
TElem &Iterator<TElem>::operator*() {
    return list.items[index];
}

template<typename TElem>
Iterator<TElem> &Iterator<TElem>::operator++() {
    index++;
    return *this;
}

template<typename TElem>
bool Iterator<TElem>::operator==(const Iterator<TElem> &other) {
    return index == other.index;
}

template<typename TElem>
bool Iterator<TElem>::operator!=(const Iterator<TElem> &other) {
    return !(*this == other);
}
