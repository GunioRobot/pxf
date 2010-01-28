#ifndef _PXF_GRAPHICS_DEVICE_H_
#define _PXF_GRAPHICS_DEVICE_H_

#include <Pxf/Math/Math.h>
#include <Pxf/Math/Vector.h>
#include <Pxf/Math/Matrix.h>
#include <Pxf/Graphics/DeviceType.h>

namespace Pxf
{
	namespace Graphics
	{
		class Window;
		class WindowSpecifications;
		class InterleavedVertexBuffer;
		class NonInterleavedVertexBuffer;

		class Texture;

		class QuadBatch;

		struct Vertex
		{
			Math::Vec3f pos;
			Math::Vec2f tex;
			Math::Vec4f color;
		};

		/**
		 * VertexBuffer location types
		 * VB_LOCATION_SYS is stored in system memory
		 * VB_LOCATION_GPU is stored in GPU memory
		 */
		enum VertexBufferLocation
		{
			VB_LOCATION_SYS,
			VB_LOCATION_GPU
		};

		/**
		 * VertexBuffer type
		 * VB_TYPE_INTERLEAVED: stores data interleaved in one continuous chunk
		 * VB_TYPE_NONINTERLEAVED: stores data in independent chunks
		 */
		enum VertexBufferType
		{
			VB_TYPE_INTERLEAVED,
			VB_TYPE_NONINTERLEAVED
		};

		/**
		 * VertexBuffer attributes
		 */
		enum VertexBufferAttribute
		{
			VB_VERTEX_DATA = 1,
			VB_NORMAL_DATA = 2,
			VB_TEXCOORD_DATA = 4,
			VB_COLOR_DATA = 8,
			VB_INDEX_DATA = 16,
			VB_EDGEFLAG_DATA = 32,
		};

		/**
		 * Vertex buffer usage flags (used for GPU located memory)
		 */

		enum VertexBufferUsageFlag
		{
			VB_USAGE_STATIC_DRAW = 1,
			VB_USAGE_STATIC_READ = 2,
			VB_USAGE_STATIC_COPY = 4,
			VB_USAGE_DYNAMIC_DRAW = 8,
			VB_USAGE_DYNAMIC_READ = 16,
			VB_USAGE_DYNAMIC_COPY = 32,
			VB_USAGE_STREAM_DRAW = 64,
			VB_USAGE_STREAM_READ = 128,
			VB_USAGE_STREAM_COPY = 256
		};

		/**
		 * Vertex buffer access flags, specifies what type of access when
		 * mapping gpu memory data.
		 */
		enum VertexBufferAccessFlag
		{
			VB_ACCESS_READ_ONLY = 1,
			VB_ACCESS_WRITE_ONLY = 2,
			VB_ACCESS_READ_WRITE = 4
		};

		enum VertexBufferPrimitiveType { 
			VB_PRIMITIVE_NONE   = 0,
			VB_PRIMITIVE_POINTS = 1, 
			VB_PRIMITIVE_LINES,
			VB_PRIMITIVE_LINE_LOOP,
			VB_PRIMITIVE_LINE_STRIP,
			VB_PRIMITIVE_TRIANGLES,
			VB_PRIMITIVE_TRIANGLE_STRIP,
			VB_PRIMITIVE_TRIANGLE_FAN,
			VB_PRIMITIVE_QUADS,
			VB_PRIMITIVE_QUAD_STRIP
		};
		
		//! Abstract video device
		class Device
		{
		public:

			// Windowing
			virtual Window* OpenWindow(WindowSpecifications* _pWindowSpecs) = 0;
			virtual void CloseWindow() = 0;

			// Device
			virtual DeviceType GetDeviceType() = 0;

			// Graphics
			virtual void SetViewport(int _x, int _y, int _w, int _h) = 0;
			virtual void SetProjection(Math::Mat4 *_matrix) = 0;
			virtual void Translate(Math::Vec3f _translate) = 0;
			virtual void SwapBuffers() = 0;

			// Texture
			virtual Texture* CreateTexture(const char* _filepath) = 0;
			virtual void BindTexture(Texture* _texture) = 0;
			virtual void BindTexture(Texture* _texture, unsigned int _texture_unit) = 0; // Multi-texturing

			// PrimitiveBatch
			virtual QuadBatch* CreateQuadBatch(int _maxSize) = 0;
			
			virtual NonInterleavedVertexBuffer* CreateNonInterleavedVertexBuffer(VertexBufferLocation _VertexBufferLocation) = 0;
			virtual InterleavedVertexBuffer* CreateInterleavedVertexBuffer(VertexBufferLocation _VertexBufferLocation) = 0;
			virtual void DestroyVertexBuffer(NonInterleavedVertexBuffer* _pVertexBuffer) = 0;
			virtual void DestroyVertexBuffer(InterleavedVertexBuffer* _pVertexBuffer) = 0;
			virtual void DrawBuffer(InterleavedVertexBuffer* _pVertexBuffer) = 0;


			// Need the name VertexBuffer for draw calls...?
			// Or should *VertexArray inherit from Drawable?

			// QuadBatch : public PrimitiveBatch public : Drawable
			// 

		};
	} // Graphics
} // Pxf

#endif // _PXF_GRAPHICS_DEVICE_H_