#pragma once
class EntityId
{
public:
	EntityId(int slot_, int generation_);

	int slot; // Entity ID.
	int generation; // Vector (entities) position.
};

