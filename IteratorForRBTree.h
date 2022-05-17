#ifndef ITERATORFORRBTREE

#pragma once


template <class typeKey>
class Iterator {
public:
	virtual typeKey next() = 0;
	virtual bool has_next() = 0;
	virtual ~Iterator() {};
};
#endif // !ITERATORFORRBTREE
