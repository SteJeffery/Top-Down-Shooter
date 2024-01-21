#pragma once
#include "../../Engine/Input/InputDevice.h"


class KeyboardAndMouseInputDevice : public InputDevice
{
public:
	KeyboardAndMouseInputDevice();
	virtual ~KeyboardAndMouseInputDevice();

	virtual void ProcessInputs();




};

