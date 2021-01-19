 #include"BatchRenderer.h"
//#include"../Sprite.h"

#include<vector>

// Freetype gl sucks





namespace PX {
	namespace graphics {

		BatchRendererSettings::BatchRendererSettings(const unsigned short& sprite_count)
		{
			glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &this->Texture_Batch_Size);
			this->sprite_count = sprite_count;
		}


		bool BatchRenderer::RenderBatch::Insert(const Sprite* sprite, const Math::mat4& transform)
		{
			const Texture* tex = sprite->GetTexture();


			if (this->texture_map.find(tex) == this->texture_map.end())
			{
				//Not Found
				if (this->texture_map.size() >= this->settings.Texture_Batch_Size)
				{
					return false;
				}

				this->texture_map[tex] = this->available_sampler++;
			}

			this->sprites.insert(std::make_pair(sprite, transform));
			this->indicies_count += 6;
			return true;
		}

		void BatchRenderer::RenderBatch::Clear()
		{
			this->texture_map.clear();
			this->sprites.clear();
			this->available_sampler = 0;
			this->indicies_count = 0;
		}



















		BatchRenderer::BatchRenderer()
			:
			Renderer(),
			vbo(VERTEX_BUFFER_SIZE, GL_DYNAMIC_DRAW),
			ibo(),
			indicies_count(0),
			available_sampler(0),
			data(nullptr),
			settings(SPRITE_COUNT)
		{
			// The index buffer is filled in completely at the start.
			// This might be a waste of GPU memory, as not all the indicies are
			// used, but it would save us a lot of runtime, as this does not
			// have to be done again and again.
			unsigned short* index_buffer = new unsigned short[INDEX_BUFFER_SIZE];
			unsigned short *ref = index_buffer;

			for (unsigned int i = 0, count = 0; i < INDEX_BUFFER_SIZE; i += 6, count += 4)
			{
				ref = index_buffer + i;

				*ref = count;
				*(ref + 1) = count + 1;
				*(ref + 2) = count + 2;

				*(ref + 3) = count;
				*(ref + 4) = count + 2;
				*(ref + 5) = count + 3;
			}

			ibo.ResetBuffer(index_buffer, INDEX_BUFFER_SIZE);

			delete[] index_buffer;
		}

		BatchRenderer::~BatchRenderer()
		{}




		void BatchRenderer::Begin()
		{
			this->vbo.Bind();
			// Opening up the buffer.
			this->data = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		void BatchRenderer::End()
		{
			// Sealing the buffer.
			glUnmapBuffer(GL_ARRAY_BUFFER);
		}

		void BatchRenderer::Submit(const Sprite* sprite, const Math::mat4& transform)
		{
			//flag for insertion
			bool inserted = false;

			// Checking for any possibility of accomodation in the current batches
			for (auto i = this->batches.begin(); i != this->batches.end(); i++)
			{
				if (!((*i)->Insert(sprite, transform)))
					continue; // Unable to insert. Check the next batch.

				// Setting the flag
				inserted = true;
				break;
			}

			// If insertion was not completed, none of the current batches could 
			// accomodate the sprite. Creating a new batch.
			if (!inserted)
			{
				RenderBatch* new_batch = new RenderBatch(this->settings);
				new_batch->Insert(sprite, transform);
				this->batches.push_back(new_batch);
			}
		}

		void BatchRenderer::Render()
		{	
			this->vao.Bind();

			this->vbo.Bind();

			// Setting up the vertex buffer format
			glVertexAttribPointer(VERTEX_POS_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
			glVertexAttribPointer(VERTEX_COLOR_INDEX, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::color));
			glVertexAttribPointer(VERTEX_UV_INDEX, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::uv));
			glVertexAttribPointer(VERTEX_TID_INDEX, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::tex_id));

			// Enabling the vertex attributes
			glEnableVertexAttribArray(VERTEX_POS_INDEX);
			glEnableVertexAttribArray(VERTEX_COLOR_INDEX);
			glEnableVertexAttribArray(VERTEX_UV_INDEX);
			glEnableVertexAttribArray(VERTEX_TID_INDEX);

			this->ibo.Bind();
	

			// Rendering all the batches
			for (auto b = this->batches.begin(); b != this->batches.end(); b++)
			{
				RenderBatch* batch = *b;
				this->Begin();

				// Render all the sprites in the batch
				for (auto s = batch->sprites.begin(); s != batch->sprites.end(); s++)
				{
					this->BufferSprite(s->first, s->second, batch);
				}

				this->End();
				this->flush(batch);
				batch->Clear();
			}
		}





		void BatchRenderer::flush(RenderBatch* batch)
		{
			// Loading the textures
			for (auto i = batch->texture_map.begin(); i != batch->texture_map.end(); i++)
			{
				unsigned int a = i->second;
				glActiveTexture(GL_TEXTURE0 + a);
				i->first->Bind();
			}

			glDrawElements(GL_TRIANGLES, batch->indicies_count, GL_UNSIGNED_SHORT, 0);
		}



		void BatchRenderer::BufferSprite(const Sprite* sprite, const Math::mat4& transform, RenderBatch* batch)
		{
			const Texture* tex = sprite->GetTexture();
			
			if (!tex) this->BufferNoTextureData(sprite, transform, batch);
			else	  this->BufferTextureData(sprite, transform, batch);
		}


		void BatchRenderer::BufferNoTextureData(const Sprite* sprite, const Math::mat4& transform, RenderBatch* batch)
		{
			using namespace Math;
			const Vector2& dim = sprite->GetDimensions();
			const float angle = sprite->GetAngle();

			// Calculating spite rotated coordinates in local space, 
			// then transforming the pos to world space
			Vector4 v0 = ( ((VERTEX_ROT_CENTER) ? Vector4(-dim.x / 2, -dim.y / 2, sprite->GetPosition().z, 1) : Vector4(0, 0, 0, 1)) * mat4::rotation(0, 0, 1, -angle) + sprite->GetPosition()) * transform;
			Vector4 v1 = ( ((VERTEX_ROT_CENTER) ? Vector4(dim.x / 2, -dim.y, sprite->GetPosition().z, 1) : Vector4(dim.x, 0, 0, 1)) * mat4::rotation(0, 0, 1, -angle) + sprite->GetPosition()) * transform;
			Vector4 v2 = ( ((VERTEX_ROT_CENTER) ? Vector4(dim.x / 2, dim.y / 2, sprite->GetPosition().z, 1) : Vector4(dim.x, dim.y, 0, 1)) * mat4::rotation(0, 0, 1, -angle) + sprite->GetPosition()) * transform;
			Vector4 v3 = ( ((VERTEX_ROT_CENTER) ? Vector4(-dim.x / 2, dim.y / 2, sprite->GetPosition().z, 1) : Vector4(0, dim.y, 0, 1)) * mat4::rotation(0, 0, 1, -angle) + sprite->GetPosition()) * transform;

			//Getting Vector3 vertices
			Vector3 p0 = Vector3(v0.x, v0.y, v0.z);
			Vector3 p1 = Vector3(v1.x, v1.y, v1.z);
			Vector3 p2 = Vector3(v2.x, v2.y, v2.z);
			Vector3 p3 = Vector3(v3.x, v3.y, v3.z);

			// Top left
			this->data->vertex = p0;
			this->data->color = sprite->GetColor();
			this->data->tex_id = -1;
			this->data++;

			// Top right
			this->data->vertex = p1;
			this->data->color = sprite->GetColor();
			this->data->tex_id = -1;
			this->data++;

			// Bottom right
			this->data->vertex = p2;
			this->data->color = sprite->GetColor();
			this->data->tex_id = -1;
			this->data++;

			// Bottom left
			this->data->vertex = p3;
			this->data->color = sprite->GetColor();
			this->data->tex_id = -1;
			this->data++;
		}







		void BatchRenderer::BufferTextureData(const Sprite* sprite,Math::mat4 transform, RenderBatch* batch)
		{
			using namespace Math;

			const Texture* texture = sprite->GetTexture();
			float angle = sprite->GetAngle();
			const Vector2& dim = sprite->GetDimensions();

			// Calculating spite rotated coordinates in local space, 
			// then transforming the pos to world space
			Vector4 v0 = (((VERTEX_ROT_CENTER) ? Vector4(-dim.x / 2, -dim.y / 2, sprite->GetPosition().z, 1) : Vector4(0, 0, 0,1)) * mat4::rotation(0,0,1,-angle) + sprite->GetPosition()) * transform;
			Vector4 v1 = (((VERTEX_ROT_CENTER) ? Vector4(dim.x / 2, -dim.y / 2, sprite->GetPosition().z, 1) : Vector4(dim.x, 0, 0, 1)) * mat4::rotation(0, 0, 1, -angle) + sprite->GetPosition()) * transform;
			Vector4 v2 = (((VERTEX_ROT_CENTER) ? Vector4(dim.x / 2, dim.y / 2, sprite->GetPosition().z, 1) : Vector4(dim.x, dim.y, 0, 1)) * mat4::rotation(0, 0, 1, -angle) + sprite->GetPosition()) * transform;
			Vector4 v3 = (((VERTEX_ROT_CENTER) ? Vector4(-dim.x / 2, dim.y / 2, sprite->GetPosition().z, 1) : Vector4(0, dim.y, 0, 1)) * mat4::rotation(0, 0, 1, -angle) + sprite->GetPosition()) * transform;

			// Getting Vector3 vertices
			Vector3 p0 = Vector3(v0.x, v0.y, v0.z);
			Vector3 p1 = Vector3(v1.x, v1.y, v1.z);
			Vector3 p2 = Vector3(v2.x, v2.y, v2.z);
			Vector3 p3 = Vector3(v3.x, v3.y, v3.z);

			// Sprite texture coordinates
			const Vector2& uv_start = sprite->GetTextureUV();
			const Vector2& uv_dimensions = sprite->GetTextureDimensions();

			const unsigned short tex_width = texture->GetWidth();
			const unsigned short tex_height = texture->GetHeight();

			// Top left
			this->data->vertex = p0;
			this->data->color = sprite->GetColor();
			this->data->tex_id = batch->texture_map[texture];
			this->data->uv = Vector2(uv_start.x / tex_width, uv_start.y / tex_height);
			this->data++;

			// Top right
			this->data->vertex = p1;
			this->data->color = sprite->GetColor();
			this->data->tex_id = batch->texture_map[texture];
			this->data->uv = Vector2((uv_start.x + uv_dimensions.x) / tex_width, uv_start.y / tex_height);
			this->data++;

			// Bottom right
			this->data->vertex = p2;
			this->data->color = sprite->GetColor();
			this->data->tex_id = batch->texture_map[texture];
			this->data->uv = Vector2((uv_start.x + uv_dimensions.x) / tex_width, (uv_start.y + uv_dimensions.y) / tex_height);
			this->data++;

			// Bottom left
			this->data->vertex = p3;
			this->data->color = sprite->GetColor();
			this->data->tex_id = batch->texture_map[texture];
			this->data->uv = Vector2(uv_start.x / tex_width, (uv_start.y + uv_dimensions.y) / tex_height);
			this->data++;
		}

	}
}