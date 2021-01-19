#pragma once
#include<map>

#include"Renderer.h"
#include"../Buffers/Texture.h"

#include"../Buffers/VertexBuffer.h"
#include"../Buffers/IndexBuffer.h"

#include"Matrix.h"

#define SPRITE_COUNT 10000
#define INDEX_BUFFER_SIZE (SPRITE_COUNT * 6)
#define VERTEX_BUFFER_SIZE (SPRITE_COUNT * sizeof(Vertex) * 4)

#define VERTEX_POS_INDEX 0
#define VERTEX_COLOR_INDEX 1
#define VERTEX_UV_INDEX 2
#define VERTEX_TID_INDEX 3

#define VERTEX_ROT_CENTER 1

#define TEXTURE_BATCH_SIZE 16



namespace PX {
	namespace graphics {
		

		struct BatchRendererSettings
		{
			unsigned short sprite_count;
			int Texture_Batch_Size;

			 BatchRendererSettings(const unsigned short& sprite_count);
		};

		class BatchRenderer : public Renderer
		{		


			struct RenderBatch
			{
				// @Note :
				// The reference in mat4 might optimize the memory usage.
				std::map<const Sprite*, Math::mat4> sprites;
				std::map<const Texture*, unsigned int> texture_map;
				unsigned int indicies_count;

				const BatchRendererSettings &settings;
				unsigned int available_sampler;

			public:
				RenderBatch(const BatchRendererSettings& settings) : settings(settings), available_sampler(0), indicies_count(0){}
				
				bool Insert(const Sprite* sprite, const Math::mat4& transform);
				void Clear();
			};





			VertexBuffer vbo;
			IndexBuffer ibo;
			Vertex* data;

			unsigned short indicies_count;
			unsigned int available_sampler;

			//std::map<const Texture*, unsigned int> texture_map;
			//std::vector<std::pair<const Sprite*, const Math::mat4&>> next_batch_buffer;
			unsigned int total_batches;
			std::vector<RenderBatch*> batches;
			BatchRendererSettings settings;

			struct FontString
			{
				std::string font_name;
				Math::Vector3 position;
				Math::Vector4 color;
				std::string string;
				float size;

				FontString(const std::string& font,const Math::Vector3& pos,const Math::Vector4& color,const std::string& string, const float& size)
					: font_name(font), position(pos), color(color), string(string), size(size)
				{}
			};

			std::vector<FontString> strings;
					    
		public:
			BatchRenderer();
			~BatchRenderer();

		   virtual void Begin() override;
		   virtual void End() override;

		   virtual void Submit(const Sprite* sprite,const Math::mat4& transform = Math::mat4::identity()) override;   

		   // Note:-
		   //  The coordinate for the position of the text is the bottom left
		   //  corner. So the dimensions are respective to that origin.
		   //virtual void DrawString(const std::string& string, const char* font_name, const float& size, const Math::Vector3 position = Math::Vector3(0,0,0), const Math::Vector2& dimensions = Math::Vector2(100,100),const Math::mat4& transform = Math::mat4::identity(), const Math::Vector4& color = Math::Vector4(1,0,1,1)) override;
		   virtual void Render() override; 

		private:
			void flush(RenderBatch* batch);
		
			void BufferSprite(const Sprite* sprite, const Math::mat4& transform, RenderBatch* batch);
			void BufferNoTextureData(const Sprite*, const Math::mat4& transform, RenderBatch* batch);
			void BufferTextureData(const Sprite* sprite, Math::mat4, RenderBatch* batch);
		};

	}
}
