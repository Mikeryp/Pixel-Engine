#if 0
#include"Group.h"
#include"Sprite.h"
#include"Text/Text.h"

#include"Vector.h"
#include"Renderers/Renderer.h"

namespace Pixel {
	namespace graphics {

		Group::Group(const Math::Vector3& origin, Group* master)
			:
			transform(1),
			angle(0),
			master_group(master)
		{
			this->transform.translate(origin); // The original transform
		}

		Group::~Group()
		{
			for (auto s : this->sub_groups)
			{
				s->master_group = nullptr;
			}
		}


		void Group::SubmitSprite(Sprite* s)
		{
			this->renderables.push_back(s); 
		}

		void Group::Submit(Renderer* renderer, Math::mat4 transform)
		{
			// Implementing the angle feature and completing group repairing
			Math::mat4 master_transform(1);

			// If this is a sub group
			if (this->master_group != nullptr)  
			{
				master_transform *= this->master_group->transform;
			}

			// Submiting the sprites.
			for (auto r : this->renderables) 
			{
				r->Submit(renderer, master_transform * this->transform * Math::mat4::rotation(0,0,1,-this->angle) * transform);
			}

		}

		void Group::SetPosition(const Math::Vector3& pos)
		{
			this->transform.translate(pos);
		}

		void Group::SetRotation(const float& angle)
		{
			this->angle = angle;
		}

		void Group::Subgroup(Group* group)
		{
			this->sub_groups.push_back(group); // Pushing in the sub groups array
			group->master_group = this; // marking the group as a sub group.
		}

	}
}

#endif