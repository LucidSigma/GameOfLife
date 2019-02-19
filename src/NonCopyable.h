#pragma once
#ifndef NON_COPYABLE_H
#define NON_COPYABLE_H

class NonCopyable
{
protected:
	NonCopyable() = default;

	NonCopyable(const NonCopyable&) = delete;
	NonCopyable& operator =(const NonCopyable&) = delete;
};

#endif
