
// @Deprecated.
// Currently Discarded.
// There is need at a higher level to transform sprites specifically.
// The entities would be the one which are going to transform the sprite.
// A similar structure for entities will be made.


#pragma once
#if 0
#include<vector>
#include<map>

#include"Matrix.h"
#include"Renderable.h"


namespace Pixel {
	namespace graphics {

		class Sprite;
		class Text;

		class Group : public Renderable
		{
			Math::mat4 transform;
			float angle;
			std::vector<Sprite*> renderables;
			
			std::vector<Group*> sub_groups;
			Group* master_group;


		public:
			Group(const Math::Vector3& origin, Group* master = nullptr);
		   ~Group();

		   void SubmitSprite(Sprite* s);
		   void Submit(Renderer* renderer, Math::mat4 transform = Math::mat4::identity()) override;
		   void InsertRenderable(Group* group) override {}

		   void SetPosition(const Math::Vector3& pos);
		   void SetRotation(const float& angle);
		   void Subgroup(Group* group);
		};

	}

}

#endif
