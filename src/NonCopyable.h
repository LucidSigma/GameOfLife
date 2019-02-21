#pragma once
#ifndef I_NONCOPYABLE_H
#define I_NONCOPYABLE_H

class INoncopyable
{
public:
	INoncopyable() = default;
	~INoncopyable() = default;

	INoncopyable(const INoncopyable&) = delete;
	INoncopyable& operator =(const INoncopyable&) = delete;
};

#endif