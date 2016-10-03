#pragma once
#include "Object.h"
#include "ObjectListIterator.h"

const int MAX_OBJECTS = 5000;

namespace df {

	class ObjectListIterator;

	class ObjectList
	{

	private:
		int count;
		Object *p_obj[MAX_OBJECTS];

	public:
		friend class ObjectListIterator;
		ObjectList();
		int insert(Object *p_o);
		int remove(Object *p_o);
		void clear();
		int getCount() const;
		bool isEmpty() const;
		bool isFull() const;
	};
}

