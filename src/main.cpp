#include "GameEngine/GameEngine.h"
#include "GLUTConfig.h"

using namespace std;
using namespace GLUTConfig;

// The name of the animation engin.
char const * g_Name = "Animation\0";
	
// The engin of the whole syste
GameEngine g_Engine;

int main(int argc, char** argv)
{
	GLUTConfig::g_InitializeEngine(&argc, argv, 960, 540, 150, 100);
	GLUTConfig::g_Run();
	return 0;
}
