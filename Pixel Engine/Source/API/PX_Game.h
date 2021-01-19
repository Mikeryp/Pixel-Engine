#pragma once

namespace PX {
	

	class PX_Game 
	{
	protected:
		PX_Game() {}
		virtual ~PX_Game() {}

	public:

		virtual void Init() {}
		virtual void Update() = 0;
		virtual void Cleanup() {}
	};

}
