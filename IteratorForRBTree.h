#ifndef ITERATOR_H
#define ITERATOR_H
#include <string>
#pragma once
template <class T>
class Iterator
{
public:
	virtual T next() = 0;

	virtual bool has_next() = 0;

	virtual ~Iterator() {};
};

#endif ITERATOR_H