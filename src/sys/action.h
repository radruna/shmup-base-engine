/*
/ Class for action constructs
/ Author: Victor Rådmark
/ File created: 2011-03-08
/ File updated: 2010-03-08
/ License: GPLv3
*/
#ifndef ACTION_H_INCLUDED
#define ACTION_H_INCLUDED

#include <string>

namespace sbe
{
	class Action
	{
		public:
			Action(void* callObject,
                   void (*callFunction) (void* object),
                   const std::string& key);
			~Action() {}

			void setKey(const std::string& k)
			{
                key = k;
			}

			void act()
			{
			    actionFunc(funcObject);
			}
		private:
			std::string key;
			void* funcObject;
			void (*actionFunc) (void* object);
	};
}

#endif
