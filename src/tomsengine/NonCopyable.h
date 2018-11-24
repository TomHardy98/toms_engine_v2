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

		NonCopyable(const NonCopyable&);   /// Object isnt allow to copy it self

		NonCopyable& operator=(const NonCopyable&);   /// Object cant equal it self
	};
}

#endif