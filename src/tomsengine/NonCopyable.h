#ifndef NONCOPYABLE_H
#define NONCOPYABLE_H

namespace tomsengine
{
	class NonCopyable
	{
	protected:

		NonCopyable() { }

		~NonCopyable() { }

	private:

		NonCopyable(const NonCopyable&);

		NonCopyable& operator=(const NonCopyable&);
	};
}

#endif