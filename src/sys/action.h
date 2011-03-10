/*
/ Class for action constructs
/ Author: Victor Rådmark
/ File created: 2011-03-10
/ File updated: 2010-03-10
/ License: GPLv3
*/
#ifndef ACTION_H_INCLUDED
#define ACTION_H_INCLUDED

#include <string>

#include <SFML/Window.hpp>

namespace sbe
{
	class Action
	{
		public:
            Action() { funcObject = NULL; }
			Action(void* callObject,
                   void (*callFunction) (void* object),
                   const sf::Key::Code& key);
			Action(void* callObject,
                   void (*callFunction) (void* object),
                   void (*otherFunction) (void* object),
                   const sf::Key::Code& key);
			~Action() {}

			void setKey(const sf::Key::Code& k)
			{
                key = k;
			}

			sf::Key::Code getKey()
			{
			    return key;
			}

			void act(bool sec = 0)
			{
			    if(!sec)
                    actionFunc(funcObject);
                else
                    if(elseFunc != NULL) elseFunc(funcObject);
			}
		private:
			sf::Key::Code key;
			void* funcObject;
			void (*actionFunc) (void* object);
			void (*elseFunc) (void *object);
	};
}

#endif
