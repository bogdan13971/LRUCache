#pragma once

#include <string>
#include <vector>

struct Entity
{
	int id;
	std::string name;
	float prec;
	int arr[10];
	std::vector<int> vec;

	Entity() = default;

	Entity(int id)
	{
		this->id = id;
		name = std::to_string(id);
		prec = id * 0.31224f;
		for (int i = 0; i < 10; i++) arr[i] = id;
		vec.resize(id % 3, id);
	}

	Entity(const Entity& other)
	{
		id = other.id;
		name = other.name;
		prec = other.prec;
		std::copy(other.arr, other.arr + 10, arr);
		vec = other.vec;
	}

	Entity& operator=(const Entity& other)
	{
		id = other.id;
		name = other.name;
		prec = other.prec;
		std::copy(other.arr, other.arr + 10, arr);
		vec = other.vec;

		return *this;
	}

	Entity(Entity&& other) noexcept
	{
		id = std::move(other.id);
		name = std::move(other.name);
		prec = std::move(other.prec);
		std::move(other.arr, other.arr + 10, arr);
		vec = std::move(other.vec);
	}

	Entity& operator=(Entity&& other) noexcept
	{
		id = std::move(other.id);
		name = std::move(other.name);
		prec = std::move(other.prec);
		std::move(other.arr, other.arr + 10, arr);
		vec = std::move(other.vec);

		return *this;
	}

	bool operator==(const Entity& other)
	{
		return id == other.id && name == other.name && prec == other.prec &&
			std::equal(arr, arr + 10, other.arr, other.arr + 10) &&
			vec == other.vec;
	}
};
