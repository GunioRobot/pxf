#include <Pxf/Pxf.h>
#include <Pxf/Util/String.h>
#include <Pxf/Input/OpenGL/InputGL2.h>
#include <Pxf/Base/Debug.h>

#include <GL/glfw.h>

#define LOCAL_MSG "InputGL2"

using namespace Pxf;
using namespace Pxf::Input;
using Util::String;

InputGL2::InputGL2()
{
	Message(LOCAL_MSG, "Input initiated.");

}

InputGL2::~InputGL2()
{
	// Clean up
}


void InputGL2::Update()
{
	// TODO: Update input device...
}