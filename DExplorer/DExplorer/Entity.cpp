#include "Entity.h"



Entity::Entity() {}

Entity::Entity(float verts[]) {
	const int n = sizeof(verts) / sizeof(float);
	for (int i = 0; i < n; i++) {
		m_verts.push_back(verts[i]);
	}
	

}


Entity::~Entity() {}
