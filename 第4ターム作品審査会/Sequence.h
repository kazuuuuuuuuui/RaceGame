#pragma once

#include <assert.h>

template<class T> class Sequence 
{
public:
	typedef void (T::*Process)(float);

	Sequence() :
		_time(0),
		_prev(nullptr),
		_now(nullptr),
		_next(nullptr)
	{}
	~Sequence() {}

	inline void Run(T* obj, const float delta) 
	{
		if (!_now && !_next) return;
		if (_next) {
			_prev = _now;
			_now = _next;
			_next = nullptr;
			_time = 0.0f;
		}
		(obj->*_now)(delta);
		_time += delta;
	}

	inline void Change(const Process sequence = nullptr) 
	{
		if (!sequence && !_next) 
		{
			assert(0);
		}
		_next = sequence;
		_time = 0.0f;
	}

	inline float GetTime() const { return _time; }

private:
	float _time;
	Process _prev;
	Process _now;
	Process _next;

};



