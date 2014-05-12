#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

class Keyboard
{

	public:

		// Singleton.
		static Keyboard & getInstance()
		{
			static Keyboard instance;
			return instance;
		}

		// Update function, called when some key pressed
		void updatePress(unsigned char const & key);

		// Update function, called when some key released
		void updateRelease(unsigned char const & key);

		// Return whether the test key is down
		bool isKeyDown(unsigned char const & key) const;

		// Return whether the test key is up
		bool isKeyUp(unsigned char const & key) const;

	private:

		// Constructor
		Keyboard();

		// Destructor
		~Keyboard();

		// Prevent any external implementaion
		Keyboard(Keyboard const &);
		void operator = (Keyboard const &);

		// Used to restore key state
		bool m_KeyState[256];
};

#endif
