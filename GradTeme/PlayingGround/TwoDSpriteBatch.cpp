#include "TwoDSpriteBatch.h"
#include <algorithm>

namespace PlayingGround {


TwoDSpriteBatch::TwoDSpriteBatch():m_vbo(0), m_vao(0)
{
}


TwoDSpriteBatch::~TwoDSpriteBatch()
{
}

void TwoDSpriteBatch::init() {
	create_vertex_array();
}

void TwoDSpriteBatch::begin(GlyphSortType sortType /*= GlyphSortType::TEXTURE*/){
	m_sortType = sortType;
	m_renderBatches.clear();
	m_glyphs.clear();
}

void TwoDSpriteBatch::end(){
	m_glyphPointers.resize(m_glyphs.size());
	for (int i = 0; i < m_glyphs.size(); i++) {
		m_glyphPointers[i] = &m_glyphs[i];
	}
	sort_glyphs();
	create_render_batches();
}

void TwoDSpriteBatch::draw(const glm::vec4 & destRect, const glm::vec4 & uvRect, GLuint texture,float depth, const ColorRGBA8 & color){

	m_glyphs.emplace_back(destRect, uvRect, texture, depth, color);


}

void TwoDSpriteBatch::create_vertex_array(){
	if (m_vao == 0) {
		glGenVertexArrays(1, &m_vao);
	}
	glBindVertexArray(m_vao);
	if (m_vbo == 0) {
		glGenBuffers(1, &m_vbo);
	}
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);


	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position)); //attribute pointer za pozicijo
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));	//attribute pointer za barvo
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));  //attribute pointer za UV

	 (0);
}

void TwoDSpriteBatch::sort_glyphs(){
	switch (m_sortType) {
	case GlyphSortType::BACK_TO_FRONT:
		std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareBacktToFront);
			break;
	case GlyphSortType::FRONT_TO_BACK:
		std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareFrontToBack);
			break;
	case GlyphSortType::TEXTURE:
		std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareTexture);
			break;
	}
}

bool TwoDSpriteBatch::compareBacktToFront(Glyph* a, Glyph* b) {
	return (a->depth > b->depth);
}

bool TwoDSpriteBatch::compareFrontToBack(Glyph* a, Glyph* b) {
	return (a->depth < b->depth);
}

bool TwoDSpriteBatch::compareTexture(Glyph* a, Glyph* b) {
	return (a->texture < b->texture);
}
void TwoDSpriteBatch::create_render_batches(){
	std::vector<Vertex> vertices;  //shrani vse tocke ki jih naložimo

	vertices.resize(m_glyphs.size() * 6);  // nastavi velikost bufferja na pravsnjo


	if (m_glyphs.empty()) {
		return;
	}
	int offset = 0;  //current offset
	int cv = 0;  //current vertex
	m_renderBatches.emplace_back(offset, 6, m_glyphPointers[0]->texture);
	vertices[cv++] = m_glyphPointers[0]->topLeft;
	vertices[cv++] = m_glyphPointers[0]->bottomLeft;
	vertices[cv++] = m_glyphPointers[0]->bottomRight;
	vertices[cv++] = m_glyphPointers[0]->bottomRight;
	vertices[cv++] = m_glyphPointers[0]->topRight;
	vertices[cv++] = m_glyphPointers[0]->topLeft;
	offset += 6;

	for (int cg = 1; cg < m_glyphPointers.size(); cg++) { //current glyph
		if (m_glyphPointers[cg]->texture != m_glyphPointers[cg - 1]->texture) {
			m_renderBatches.emplace_back(offset, 6, m_glyphPointers[0]->texture);
		}
		else {
			m_renderBatches.back().numVertices += 6;
		}
		vertices[cv++] = m_glyphPointers[cg]->topLeft;
		vertices[cv++] = m_glyphPointers[cg]->bottomLeft;
		vertices[cv++] = m_glyphPointers[cg]->bottomRight;
		vertices[cv++] = m_glyphPointers[cg]->bottomRight;
		vertices[cv++] = m_glyphPointers[cg]->topRight;
		vertices[cv++] = m_glyphPointers[cg]->topLeft;
		offset += 6;
	}


	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW); //orphan the buffer

	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data()); //upoload data

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void TwoDSpriteBatch::render_Batch(){
	glBindVertexArray(m_vao);
	for (int i = 0; i < m_renderBatches.size(); i++) {
		glBindTexture(GL_TEXTURE_2D, m_renderBatches[i].texture);

		glDrawArrays(GL_TRIANGLES, m_renderBatches[i].offset, m_renderBatches[i].numVertices);
	}
	glBindVertexArray(0);

}







} //namespace

