#include <Pxf/Graphics/Device.h>
#include <Pxf/Graphics/QuadBatch.h>

#include <Pxf/Extra/LuaGUI/GUIWidget.h>

using namespace Pxf;
using namespace Pxf::Math;
using namespace Pxf::Graphics;
using namespace Pxf::Extra::LuaGUI;

GUIWidget::GUIWidget(const char* _name, Math::Vec4i* _hitbox, Graphics::Device* _device)
{
	m_Name = _name;
	m_Device = _device;
	m_QuadBatch = m_Device->CreateQuadBatch(PXF_EXTRA_LUAGUI_MAXQUAD_PER_WIDGET);

	m_MouseOver = false;
	m_MousePushed = false;
	m_MouseClicked = false;
	m_MousePushedLast = false;

	m_Position.x = _hitbox->x;
	m_Position.y = _hitbox->y;
	m_Size.x = _hitbox->z;
	m_Size.y = _hitbox->w;
}

GUIWidget::~GUIWidget()
{
	if (m_QuadBatch)
		delete m_QuadBatch;
}

void GUIWidget::SetPosition(Math::Vec2f _pos)
{
	m_Position = Math::Vec3f(_pos.x, _pos.y, 0.0f);
}

void GUIWidget::Reset()
{
	m_QuadBatch->Reset();
}

void GUIWidget::AddState(const char* _stateid)
{
	m_States.push_front(Util::String(_stateid));
}

void GUIWidget::SetState(const char* _stateid)
{
	m_ActiveState = _stateid;
}

const char* GUIWidget::GetState()
{
	return m_ActiveState.c_str();
}

void GUIWidget::AddQuad(Math::Vec4i* _quad, Math::Vec4f* _texcoord)
{
	m_QuadBatch->SetTextureSubset(_texcoord->x, _texcoord->y, _texcoord->z, _texcoord->w);
	m_QuadBatch->AddTopLeft(_quad->x, _quad->y, _quad->z, _quad->w);
}

void GUIWidget::Draw()
{
	m_Device->Translate(m_Position);
	m_QuadBatch->Draw();
	m_Device->Translate(-m_Position);
}

void GUIWidget::Update(Math::Vec2f* _mouse, bool _mouse_down)
{
	m_MouseOver = false;
	m_MousePushed = false;
	m_MouseClicked = false;

	if (_mouse->x < m_Position.x)
	{
		m_MousePushedLast = false;
		return;
	}

	if (_mouse->x > m_Position.x + m_Size.x)
	{
		m_MousePushedLast = false;
		return;
	}

	if (_mouse->y < m_Position.y)
	{
		m_MousePushedLast = false;
		return;
	}

	if (_mouse->y > m_Position.y + m_Size.y)
	{
		m_MousePushedLast = false;
		return;
	}

	m_MouseHit = Math::Vec2f(_mouse->x - m_Position.x, _mouse->y - m_Position.y);
	//printf("_x: %f, _y: %f\n", m_MouseHit.x, m_MouseHit.y);

	m_MouseOver = true;
	m_MousePushed = _mouse_down;

	if (!m_MousePushed && m_MousePushedLast)
	{
		m_MouseClicked = true;
	}

	m_MousePushedLast = m_MousePushed;
}

Math::Vec2f GUIWidget::GetMouseHit()
{
	//printf("_x: %f, _y: %f\n", m_MouseHit.x, m_MouseHit.y);
	return m_MouseHit;
}

bool GUIWidget::IsMouseOver()
{
	return m_MouseOver;
}

bool GUIWidget::IsDown()
{
	return m_MousePushed;
}

bool GUIWidget::IsClicked()
{
	return m_MouseClicked;
}