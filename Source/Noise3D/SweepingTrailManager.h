
/***********************************************************************

								h£ºSweepingTrailManager


		Desc: Sweeping Trail is an special effect that uses
		a sequence of triangle strip to simulate/visualize a
		path that a line segment sweep through 3D spaces.

		picture ref:https://blog.csdn.net/cbbbc/article/details/70863580
************************************************************************/

#pragma once

namespace Noise3D
{
	class /*_declspec(dllexport)*/ SweepingTrailManager :
		public IFactory<SweepingTrail>
	{
	public:

		SweepingTrail*	CreateSweepingTrail(SceneNode* pAttachedNode, N_UID objName, uint32_t maxVertexCount);

	private:

		friend  class SceneManager;

		friend IFactory<SweepingTrailManager>;

		SweepingTrailManager();

		~SweepingTrailManager();
	};
}