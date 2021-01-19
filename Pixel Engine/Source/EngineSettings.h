#pragma once

static struct Settings
{
	unsigned settings;
};


namespace PX {

	struct Settings
	{
		static unsigned physicsCalcPerFrame;
		static unsigned rendersPerFrame;
	};
}