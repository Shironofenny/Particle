#ifndef __MOUSE_H__
#define __MOUSE_H__

#include "../Utilities/Vector.h"
#include "../Utilities/Quaternion.h"
#include "../Utilities/ConstantHandler.h"

class Mouse
{
	public:
		
		// Singleton.
		static Mouse & getInstance()
		{
			static Mouse instance;
			return instance;
		}

		// Update function for active mouse reaction
		void updateActive(int _button, int _state, int _x, int _y);

		// Update function for passive mouse reaction
		void updatePassive(int _x, int _y);

		// Return if the mouse is on the boundary
		bool isOnBoundary();

		// Get current mouse x position
		int getPositionX() const;
		
		// Get current mouse y position
		int getPositionY() const;

		// Get the move on x
		int getDifferenceX();

		// Get the move on y
		int getDifferenceY();

		// Get the difference between now and center of the screen on X
		int getDeviationX() const;
		
		// Get the difference between now and center of the screen on Y
		int getDeviationY() const;

		// Refresh all mouse states
		void refresh();

		// Refresh only position info
		void refreshPositionInfo();

		// Return whether the left botton is pressed
		bool isMouseLeftDown();
		
		// Return whether the right botton is pressed
		bool isMouseRightDown();
	
	private:

		// Constructor
		Mouse();

		// Destructor
		~Mouse();

		// Prevent any external implementaion
		Mouse(Mouse const &);
		void operator = (Mouse const &);

		// The flags for restoring mouse states
		bool m_State[5];

		// Flag to prevent large deviation for first update
		bool m_IsFirstUpdate;

		// Position at the last time passive update is called
		int m_XLast, m_YLast;

		// Position at this passive update
		int m_XNow, m_YNow;
};

#endif
