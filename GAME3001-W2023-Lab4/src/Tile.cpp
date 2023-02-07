#include "Tile.h"
#include "Config.h"
#include  "Util.h"
#include <sstream>
#include <iomanip>

Tile::Tile() : m_cost(0.0f)
{
	SetWidth(Config::TILE_SIZE);
	SetHeight(Config::TILE_COST);
}

Tile::~Tile()
= default;

void Tile::Draw()
{
	switch (m_status)
	{
	case START:
		Util::DrawFilledRect(GetTransform()->position, GetWidth(), GetHeight(), glm::vec4(0.5f, 1.0f, 0.5f, 1.0f));
		break;
	case GOAL:
		Util::DrawFilledRect(GetTransform()->position, GetWidth(), GetHeight(), glm::vec4(1.5f, 0.5f, 0.5f, 1.0f));
		break;
	default:
		Util::DrawRect(GetTransform()->position, GetWidth(), GetHeight());
			break;
	}
}

void Tile::Update()
{
}

void Tile::Clean()
{
}

Tile* Tile::GetNeighbourTile(const NeighbourTile position) const
{
	return m_neighbours[position];
}

void Tile::SetNeighbourTile(const NeighbourTile position, Tile* tile)
{
	m_neighbours[position] = tile;
}

float Tile::GetTileCost() const
{
	return m_cost;
}

void Tile::SetTileCost(const float cost)
{
	m_cost = cost;

	//update the cost label - convert from float with lots of precision to single precision
	std::stringstream stream;
	stream << std::fixed << std::setprecision(1) << m_cost;
	const std::string cost_string = stream.str();

	m_costLable->SetText(cost_string);
}

TileStatus Tile::GetTileStatus() const
{
	return m_status;
}

void Tile::SetTileStatus(const TileStatus status)
{
	m_status = status;

	switch (m_status)
	{
	case UNVISITED:
		m_statuslable->SetText("-");
		break;
	case OPEN:
		m_statuslable->SetText("O");
		break;
	case CLOSED:
		m_statuslable->SetText("C");
		break;
	case IMPASSABLE:
		m_statuslable->SetText("I");
		break;
	case GOAL:
		m_statuslable->SetText("G");
		break;
	case START:
		m_statuslable->SetText("S");
			break;
	}
}

void Tile::AddLabels()
{
	auto offset = glm::vec2(Config::TILE_SIZE * 0.5f, Config::TILE_SIZE * 0.5f);


	// add cost label
	m_costLable = new Label("99.9", "consolas", 12);
	m_costLable->GetTransform()->position = GetTransform()->position + offset + glm::vec2(0.0f, -6.0f);
	GetParent()->AddChild(m_costLable);
	m_costLable->SetEnabled(false);

	// add status label
	m_statuslable = new Label("-", "consolas", 12);
	m_statuslable->GetTransform()->position = GetTransform()->position + offset + glm::vec2(0.0f, 6.0f);
	GetParent()->AddChild(m_statuslable);
	m_statuslable->SetEnabled(false);
}

void Tile::SetlabelsEnabled(bool state) const
{
	m_costLable->SetEnabled(state);
	m_statuslable->SetEnabled(state);
}
