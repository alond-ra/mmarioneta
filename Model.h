#pragma once

#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include <string>
#include <stack>
#include "Sphere.h"
#include "Renderer.h"

//  Nodo class for nodes in the puppet hierarchy
class Nodo {
public:
	Nodo() {};
	Nodo(const std::string& Name, Sphere Bodypart);
	//~Nodo();
	std::string name;
	Sphere bodypart;
	std::vector<Nodo> children;
};

// State class for representing the state of the puppet
class State {
public:
	State();
	void setState(glm::vec3 TP, glm::vec3 TO,
		glm::vec3 SO, glm::vec3 NO, glm::vec3 PO,
		glm::vec3 RAO, glm::vec3 LAO, glm::vec3 RTO, glm::vec3 LTO,
		glm::vec3 RFO, glm::vec3 LFO, glm::vec3 HO, glm::vec3 RCO, glm::vec3 LCO,
		glm::vec3 RHO, glm::vec3 LHO, glm::vec3 RFoO, glm::vec3 LFoO);
	// 0 = root
	glm::vec3 TorsoPosition;
	glm::vec3 TorsoOrientation;
	// 1
	glm::vec3 ShoulderOrientation;
	glm::vec3 NeckOrientation;
	glm::vec3 PelvisOrientation;
	// 2
	glm::vec3 RArmOrientation;
	glm::vec3 LArmOrientation;
	glm::vec3 RThighOrientation;
	glm::vec3 LThighOrientation;
	// 3
	glm::vec3 RForearmOrientation;
	glm::vec3 LForearmOrientation;
	glm::vec3 HeadOrientation;
	glm::vec3 RCalfOrientation;
	glm::vec3 LCalfOrientation;
	// 4
	glm::vec3 RHandOrientation;
	glm::vec3 LHandOrientation;
	glm::vec3 RFootOrientation;
	glm::vec3 LFootOrientation;
};

Sphere modelNode(glm::vec3 frame_pos, glm::vec3 scale, glm::vec3 pos, glm::vec4 col);

// Model class representing the puppet
class Model {
public:
	Model(Sphere primitive);
	Model(const std::string& id, Sphere primitive);

	Nodo root;

	enum NodeOperation {
		Scale,
		Translate,
		Orientate,
		FScale,
		FTranslate,
		FOrientate
	};

	State current_st;  //current state (position of the puppet)
	std::stack<State> undostack;
	std::stack<State> redostack;

	void add(const std::string& after, Nodo node);
	void updateNode(const std::string& nodeId, NodeOperation op, glm::vec3 data);
	void setModelState(State new_st);
	void build(Renderer renderer, VertexArray& va, IndexBuffer& ib, Shader& shader);
};

Model puppetmodel(glm::vec4 puppetColor);

// for comparing two states
bool equalState(State st1, State st2);

#endif