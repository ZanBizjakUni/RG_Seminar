#include "Door.h"



Door::Door(){
}


Door::~Door(){
}

void Door::init(GLint pID){
	m_modelLoc = glGetUniformLocation(pID, "model");
	m_projectionLoc = glGetUniformLocation(pID, "projection");
	m_viewLoc = glGetUniformLocation(pID, "view");
}
