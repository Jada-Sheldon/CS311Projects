// MSArray.h
// Jada Sheldon
// 12 September 2020
// CS311 Chappell
// Project 2 MSArray

// Header for template class MSArray
// MSArray, an array of client chosen type that knows its size. Can also be compared to same type MSArrays

#ifndef MSARRAY_H
#define MSARRAY_H

#include <cstddef> // std::size_t
#include <utility> // std::swap
#include <algorithm> // std::lexicographical_order


// Class Invariants:
//		_size >= 0



template <typename T>
class MSArray {
public:
	// **********************
	// **** Member types ****
	// **********************
	using size_type = std::size_t;
	using value_type = T;






public:
	// **********************
	// **** Constructors ****
	// **********************

	// default constructor with size 8
	MSArray() : _arrayptr(new value_type[8]), _size(8) {}


	// explicit one parameter constructor
	explicit MSArray(const size_type& size) : _arrayptr(new value_type[size]), _size(size) {}


	// two parameter constructor
	MSArray (const size_type& size, const value_type& value) : _arrayptr(new value_type[size]), _size(size) {
		// changing to same value for all indexes of array
		for (int i = 0; i < _size; i++) {
			_arrayptr[i] = value;
		}
	}






	// ******************
	// **** Big Five ****
	// ******************
	//copy ctor: Creates new vector and copys over values from original
	MSArray(const MSArray& original) : _arrayptr(new value_type[original.size()]), _size(original.size()) {

		std::copy(original.begin(), original.end(), _arrayptr);
	}


	//move ctor
	MSArray(MSArray&& other) noexcept : _arrayptr(other._arrayptr), _size(other.size()) {

		// move data from other to new array
		other._arrayptr = nullptr;
		other._size = 0;
		// set other array to a valid value so the destructor still works
	}


	//copy assignment
	MSArray& operator=(const MSArray& rhs) {

		MSArray copy_of_rhs(rhs);
		mswap(copy_of_rhs);
		return *this;
	}


	//move assignment
	MSArray& operator=(MSArray&& rhs) noexcept {

		mswap(rhs);
		return *this;
	}

	// destructor dealicates memory
	~MSArray() {

		delete[] _arrayptr;
	}






	// ************************************
	// **** Non Const Member Functions ****
	// ************************************
	value_type& operator[] (size_type index) {
		return _arrayptr[index];
	}


	value_type* begin() {
		return _arrayptr;
	}


	value_type* end() {
		return (_arrayptr + _size);
	}






	// ********************************
	// **** Const Member Functions ****
	// ********************************
	// size of array
	const size_type size() const {
		return _size;
	}

	
	// Bracket operator for const MSArrays
	const value_type& operator[] (size_type index) const {
		return _arrayptr[index];
	}

	
	const value_type* begin() const {
		return _arrayptr;
	}


	const value_type* end() const {
		return (_arrayptr + _size);
	}







private:

	value_type* _arrayptr; // Allocated array
	size_type _size; // Keeps track of size of array


	// mswap for Copy assignment and Move assignment
	void mswap(MSArray& other) noexcept {

		std::swap(_arrayptr, other._arrayptr);
		std::swap(_size, other._size);
	}
};






// ********************************
// ******* Global operators *******
// ********************************

// Invariant:
//		Type has to be the same
template<typename T>
bool operator==(const MSArray<T>& lhs, const MSArray<T>& rhs) {
	if (lhs.size() == rhs.size()) {
		for (int i = 0; i < lhs.size(); ++i) {
			if (lhs[i] != rhs[i]) {
				return false;
			}
		}
		return true;
	}
	return false;
}


// Invariant:
//		Type has to be the same
template<typename T>
bool operator!=(const MSArray<T>& lhs, const MSArray<T>& rhs) {
	return !(lhs == rhs);
}


// Invariant:
//		Type has to be the same
template<typename T>
bool operator<(const MSArray<T>& lhs, const MSArray<T>& rhs) {
	return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}


// Invariant:
//		Type has to be the same
template<typename T>
bool operator>= (const MSArray<T>& lhs, const MSArray<T>& rhs) {
	return !(lhs < rhs);
}


// Invariant:
//		Type has to be the same
template<typename T>
bool operator> (const MSArray<T>& lhs, const MSArray<T>& rhs) {
	return rhs < lhs;
}


// Invariant:
//		Type has to be the same
template<typename T>
bool operator<= (const MSArray<T>& lhs, const MSArray<T>& rhs) {
	return !(lhs > rhs);
}

#endif