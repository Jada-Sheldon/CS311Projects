#ifndef MSARRAY_H
#define MSARRAY_H

#include <cstddef>
#include <utility>
#include <algorithm>

template <typename T>
class MSArray {
public:
	using size_type = std::size_t;
	using value_type = T;

public:
	// default constructor with size 8
	MSArray() : _arrayptr(new value_type[8]), _size(8) {
	}

	// explicit one parameter constructor
	explicit MSArray(size_type size) : _arrayptr(new value_type[size]), _size(size) { // was reference to const
	}

	// two parameter constructor
	// TODO figure out how to set the whole array to the same value
	// I think done
	MSArray( size_type size, value_type value) : _arrayptr(new value_type[size]), _size(size) { // size_type was reference to const
		// changing to same value for all indexes of array
		for (int i = 0; i < _size; i++) {
			_arrayptr[i] = value;
		}
	}
	//copy ctor
	MSArray(const MSArray& original) noexcept : _arrayptr(new value_type[original.size()]), _size(original.size())
	{
		std::copy(original.begin(), original.end(), _arrayptr);
	}

	//move ctor
	MSArray(MSArray&& other) noexcept : _arrayptr(other._arrayptr), _size(other.size())
	{
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
	MSArray& operator=(MSArray&& rhs) noexcept
	{
		mswap(rhs);
		return *this;
	}

	// destructor dealicates memory
	~MSArray() {
		delete[] _arrayptr;
	}



	// bracet operator for both const and non const
	value_type& operator[] (size_type index) {
		return _arrayptr[index];
	}

	//TODO: Make member funtion begin
	value_type* begin() {
		return _arrayptr;
	}
	//TODO: Make member funtion end
	value_type* end() {
		return (_arrayptr + _size);
	}

	


	
	// size of array
	const size_type size() const {
		return _size;
	}


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

	value_type* _arrayptr;
	size_type _size;

	void mswap(MSArray& other) noexcept {
		std::swap(_arrayptr, other._arrayptr);
		std::swap(_size, other._size);
	}
};




//TODO: Operator ==
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


// TODO: Operator !=
template<typename T>
bool operator!=(const MSArray<T>& lhs, const MSArray<T>& rhs) {
	return !(lhs == rhs);
}


template<typename T>
//TODO: Operators < <= > >=
bool operator<(const MSArray<T>& lhs, const MSArray<T>& rhs) {
	return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<typename T>
bool operator>= (const MSArray<T>& lhs, const MSArray<T>& rhs) {
	return !(lhs < rhs);
}

template<typename T>
bool operator> (const MSArray<T>& lhs, const MSArray<T>& rhs) {
	return rhs < lhs;
}

template<typename T>
bool operator<= (const MSArray<T>& lhs, const MSArray<T>& rhs) {
	return !(lhs > rhs);
}


#endif
