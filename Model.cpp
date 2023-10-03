#include "Model.h"

//glm
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <iostream>

// estado (posicion) de la marioneta
State::State() { // original state (neutral position of the puppel!)
	// 0
	TorsoPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	TorsoOrientation = glm::vec3(0.0f);
	// 1
	ShoulderOrientation = glm::vec3(0.0f);
	NeckOrientation = glm::vec3(0.0f);
	PelvisOrientation = glm::vec3(0.0f);
	// 2
	RArmOrientation = glm::vec3(0.0f);
	LArmOrientation = glm::vec3(0.0f);
	RThighOrientation = glm::vec3(0.0f);
	LThighOrientation = glm::vec3(0.0f);
	// 3
	RForearmOrientation = glm::vec3(0.0f);
	LForearmOrientation = glm::vec3(0.0f);
	HeadOrientation = glm::vec3(0.0f);
	RCalfOrientation = glm::vec3(0.0f);
	LCalfOrientation = glm::vec3(0.0f);
	// 4
	RHandOrientation = glm::vec3(0.0f);
	LHandOrientation = glm::vec3(0.0f);
	RFootOrientation = glm::vec3(-90.0f, 0.0f, 0.0f);
	LFootOrientation = glm::vec3(-90.0f, 0.0f, 0.0f);
}

void State::setState(glm::vec3 TP, glm::vec3 TO,
	glm::vec3 SO, glm::vec3 NO, glm::vec3 PO,
	glm::vec3 RAO, glm::vec3 LAO, glm::vec3 RTO, glm::vec3 LTO,
	glm::vec3 RFO, glm::vec3 LFO, glm::vec3 HO, glm::vec3 RCO, glm::vec3 LCO,
	glm::vec3 RHO, glm::vec3 LHO, glm::vec3 RFoO, glm::vec3 LFoO) {
	// 0
	TorsoPosition = TP;
	TorsoOrientation = TO;
	// 1
	ShoulderOrientation = SO;
	NeckOrientation = NO;
	PelvisOrientation = PO;
	// 2
	RArmOrientation = RAO;
	LArmOrientation = LAO;
	RThighOrientation = RTO;
	LThighOrientation = LTO;
	// 3
	RForearmOrientation = RFO;
	LForearmOrientation = LFO;
	HeadOrientation = HO;
	RCalfOrientation = RCO;
	LCalfOrientation = LCO;
	// 4
	RHandOrientation = RHO;
	LHandOrientation = LHO;
	RFootOrientation = RFoO;
	LFootOrientation = LFoO;
}


Nodo::Nodo(const std::string& Name, Sphere Bodypart){
	name = Name;
	bodypart = Bodypart;
}

// p crear cada parte bodypart (torso, cuello, cabeza, extremidades) de la marioneta
Sphere modelNode(glm::vec3 frame_pos, glm::vec3 scale, glm::vec3 pos, glm::vec4 col){
	Sphere sp;
	sp.color = col;
	sp.FPosition = frame_pos;
	sp.Scale = scale;
	sp.Position = pos;
	return sp;
}

Model::Model(Sphere primitive){
	State current_st;
	undostack.push(current_st);
	Nodo OnlyNode("head", primitive);
	root = OnlyNode;
}

Model::Model(const std::string& id, Sphere primitive){
	undostack.push(current_st);
	Nodo headNode(id, primitive);
	root = headNode;
}

void Model::add(const std::string& after, Nodo node){
	std::stack<Nodo*> NodeStack;
	NodeStack.push(&(root));

	while (!NodeStack.empty()){
		Nodo* now = NodeStack.top();
		NodeStack.pop();

		if (now->name == after){
			now->children.push_back(node);
			return;
		}

		for (Nodo& child : now->children){
			NodeStack.push(&(child));
		}
	}
}

void Model::updateNode(const std::string& nodeId, NodeOperation op, glm::vec3 data){
	std::stack<Nodo*> NodeStack;
	NodeStack.push(&(root));

	while (!NodeStack.empty()){
		Nodo* now = NodeStack.top();
		NodeStack.pop();

		if (now->name == nodeId){
			switch (op){

			case NodeOperation::FOrientate:
				now->bodypart.FOrientation = data;
				break;

			case NodeOperation::FScale:
				now->bodypart.FScale = data;
				break;

			case NodeOperation::FTranslate:
				now->bodypart.FPosition = data;
				break;

			case NodeOperation::Orientate:
				now->bodypart.Orientation = data;
				break;

			case NodeOperation::Scale:
				now->bodypart.Scale = data;
				break;

			case NodeOperation::Translate:
				now->bodypart.Position = data;
				break;

			default:
				break;
			}
			return;
		}

		for (Nodo& child : now->children){
			NodeStack.push(&(child));
		}
	}
}


void Model::build(Renderer renderer, VertexArray& va, IndexBuffer& ib, Shader& shader){
	std::stack<Nodo> NodeStack;
	std::stack<glm::mat4> FStack;

	NodeStack.push(root);
	FStack.push(glm::mat4(1.0f));

	while (!NodeStack.empty()){
		Nodo nowNode = NodeStack.top();
		glm::mat4 parentF = FStack.top();
		NodeStack.pop();
		FStack.pop();

		glm::mat4 A = glm::mat4(1.0f);
		A *= glm::translate(nowNode.bodypart.FPosition);

		float yaw, pitch, roll;
		yaw = glm::radians(nowNode.bodypart.FOrientation.y);
		pitch = glm::radians(nowNode.bodypart.FOrientation.x);
		roll = glm::radians(nowNode.bodypart.FOrientation.z);

		A *= glm::eulerAngleYXZ(yaw, pitch, roll);
		A *= glm::scale(nowNode.bodypart.FScale);

		glm::mat4 objectF = parentF * A;

		glm::mat4 B = glm::mat4(1.0f);
		B *= glm::translate(nowNode.bodypart.Position);

		yaw = nowNode.bodypart.Orientation.y;
		pitch = nowNode.bodypart.Orientation.x;
		roll = nowNode.bodypart.Orientation.z;

		B *= glm::eulerAngleXYZ(yaw, pitch, roll);
		B *= glm::scale(nowNode.bodypart.Scale);

		glm::mat4 nowF = parentF * A;
		glm::mat4 modelMatrix = nowF * B;

		shader.Bind();
		shader.SetUniformMat4f("f_Model", modelMatrix);
		shader.SetUniform4f("u_ObjectColor", nowNode.bodypart.color);

		renderer.Draw(va, ib, shader);

		for (Nodo child : nowNode.children){
			NodeStack.push(child);
			FStack.push(nowF);
		}
	}
}

// cambia el estado actual de la marioneta a new_st
void Model::setModelState(State new_st) {
	current_st = new_st;
	updateNode("Torso", Model::NodeOperation::FTranslate, new_st.TorsoPosition);
	updateNode("Torso", Model::NodeOperation::FOrientate, new_st.TorsoOrientation);
	// 1
	updateNode("Shoulder", Model::NodeOperation::FOrientate, new_st.ShoulderOrientation);
	updateNode("Pelvis", Model::NodeOperation::FOrientate, new_st.PelvisOrientation);
	// 2
	updateNode("RArm", Model::NodeOperation::FOrientate, new_st.RArmOrientation);
	updateNode("LArm", Model::NodeOperation::FOrientate, new_st.LArmOrientation);
	updateNode("Neck", Model::NodeOperation::FOrientate, new_st.NeckOrientation);
	updateNode("RThigh", Model::NodeOperation::FOrientate, new_st.RThighOrientation);
	updateNode("LThigh", Model::NodeOperation::FOrientate, new_st.LThighOrientation);
	// 3
	updateNode("RForearm", Model::NodeOperation::FOrientate, new_st.RForearmOrientation);
	updateNode("LForearm", Model::NodeOperation::FOrientate, new_st.LForearmOrientation);
	//updateNode("Head", Model::NodeOperation::FOrientate, new_st.HeadOrientation);
	updateNode("RCalf", Model::NodeOperation::FOrientate, new_st.RCalfOrientation);
	updateNode("LCalf", Model::NodeOperation::FOrientate, new_st.LCalfOrientation);
	// 4
	updateNode("RHand", Model::NodeOperation::FOrientate, new_st.RHandOrientation);
	updateNode("LHand", Model::NodeOperation::FOrientate, new_st.LHandOrientation);
	updateNode("RFoot", Model::NodeOperation::FOrientate, new_st.RFootOrientation);
	updateNode("LFoot", Model::NodeOperation::FOrientate, new_st.LFootOrientation);
}

bool equalState(State st1, State st2) {
	if (st1.TorsoPosition == st2.TorsoPosition &&
		st1.TorsoOrientation == st2.TorsoOrientation &&
		st1.ShoulderOrientation == st2.ShoulderOrientation &&
		st1.NeckOrientation == st2.NeckOrientation &&
		st1.PelvisOrientation == st2.PelvisOrientation &&
		st1.RArmOrientation == st2.RArmOrientation &&
		st1.LArmOrientation == st2.LArmOrientation &&
		st1.RThighOrientation == st2.RThighOrientation &&
		st1.LThighOrientation == st2.LThighOrientation &&
		st1.RForearmOrientation == st2.RForearmOrientation &&
		st1.LForearmOrientation == st2.LForearmOrientation &&
		st1.HeadOrientation == st2.HeadOrientation &&
		st1.RCalfOrientation == st2.RCalfOrientation &&
		st1.LCalfOrientation == st2.LCalfOrientation &&
		st1.RHandOrientation == st2.RHandOrientation &&
		st1.LHandOrientation == st2.LHandOrientation &&
		st1.RFootOrientation == st2.RFootOrientation &&
		st1.LFootOrientation == st2.LFootOrientation
		)
		return true;
	return false;
}

Model puppetmodel(glm::vec4 puppetColor){
	// 0
	Sphere Torso = modelNode(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.2f, 2.5f, 0.9f), glm::vec3(0.0f, 0.0f, 0.0f), puppetColor);

	// 1
	Sphere Shoulder = modelNode(glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(1.65f, 0.75f, 0.75f), glm::vec3(0.0f, 0.5f, 0.0f), puppetColor);
	Sphere Pelvis = modelNode(glm::vec3(0.0f, -2.0f, 0.0f), glm::vec3(1.25f, 0.7f, 0.5f), glm::vec3(0.0f, -0.5f, 0.0f), puppetColor);
	// Pelvis = cadera
// 2 ----------------------------------------------------------------------------------------------------------------------------------------
	Sphere Neck = modelNode(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.25f, 0.5f, 0.25f), glm::vec3(0.0f, 0.5f, 0.0f), puppetColor);

	Sphere RArm = modelNode(glm::vec3(-1.65f, 0.5f, 0.0f), glm::vec3(0.4f, 1.5f, 0.4f), glm::vec3(0.0f, -1.5f, 0.0f), puppetColor);
	Sphere LArm = modelNode(glm::vec3(1.65f, 0.5f, 0.0f), glm::vec3(0.4f, 1.5f, 0.4f), glm::vec3(0.0f, -1.5f, 0.0f), puppetColor);

	Sphere RThigh = modelNode(glm::vec3(-0.75f, -0.5f, 0.0f), glm::vec3(0.45f, 2.25f, 0.5f), glm::vec3(0.0f, -2.25f, 0.0f), puppetColor);
	Sphere LThigh = modelNode(glm::vec3(0.75f, -0.5f, 0.0f), glm::vec3(0.45f, 2.25f, 0.5f), glm::vec3(0.0f, -2.25f, 0.0f), puppetColor);

	// 3 ----------------------------------------------------------------------------------------------------------------------------------------
	Sphere Head = modelNode(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.1f, 1.1f, 1.1f), glm::vec3(0.0f, 1.1f, 0.0f), puppetColor);
	Sphere REye = modelNode(glm::vec3(-0.45f, 1.3f, 0.95f), glm::vec3(0.15f, 0.14f, 0.15f), glm::vec3(0.0f, 0.0f, 0.0f), puppetColor);
	Sphere LEye = modelNode(glm::vec3(0.45f, 1.3f, 0.95f), glm::vec3(0.15f, 0.14f, 0.15f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), puppetColor);
	REye.color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	LEye.color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	Sphere RForearm = modelNode(glm::vec3(0.0f, -2.8f, 0.0f), glm::vec3(0.35f, 1.35f, 0.35f), glm::vec3(0.0f, -1.5f, 0.0f), puppetColor);
	//RForearm.color = glm::vec4(1.f, 1.f, 1.f, 1.0f);
	Sphere LForearm = modelNode(glm::vec3(0.0f, -2.8f, 0.0f), glm::vec3(0.35f, 1.35f, 0.35f), glm::vec3(0.0f, -1.5f, 0.0f), puppetColor);
	//LForearm.color = glm::vec4(1.f, 1.f, 1.f, 1.0f);

	Sphere RCalf = modelNode(glm::vec3(0.0f, -3.5f, 0.0f), glm::vec3(0.4f, 1.75f, 0.45f), glm::vec3(0.0f, -2.2f, 0.0f), puppetColor);
	Sphere LCalf = modelNode(glm::vec3(0.0f, -3.5f, 0.0f), glm::vec3(0.4f, 1.75f, 0.45f), glm::vec3(0.0f, -2.2f, 0.0f), puppetColor);

	// 4 ----------------------------------------------------------------------------------------------------------------------------------------
	Sphere RHand = modelNode(glm::vec3(0.0f, -2.4f, 0.0f), glm::vec3(0.25f, 0.7f, 0.25f), glm::vec3(0.0f, -0.9f, 0.0f), puppetColor);
	Sphere LHand = modelNode(glm::vec3(0.0f, -2.4f, 0.0f), glm::vec3(0.25f, 0.7f, 0.25f), glm::vec3(0.0f, -0.9f, 0.0f), puppetColor);

	Sphere RFoot = modelNode(glm::vec3(0.0f, -3.75f, 0.0f), glm::vec3(0.275f, 0.65f, 0.35f), glm::vec3(0.0f, -0.85f, 0.0f), puppetColor);
	Sphere LFoot = modelNode(glm::vec3(0.0f, -3.75f, 0.0f), glm::vec3(0.275f, 0.65f, 0.35f), glm::vec3(0.0f, -0.85f, 0.0f), puppetColor);
	RFoot.FOrientation = glm::vec3(-90.0f, 0.0f, 0.0f);
	LFoot.FOrientation = glm::vec3(-90.0f, 0.0f, 0.0f);

	//  ----------------------------------------------------------------------------------------------------------------------------------------
	Model puppt("Torso", Torso);
	//Model puppt;
	//Nodo headNode("Torso", Torso);
	//puppt.head = headNode;
	// Hijos del nodo torso
	puppt.add("Torso", Nodo("Shoulder", Shoulder));
	puppt.add("Torso", Nodo("Pelvis", Pelvis));

	// 2 
		// Hijos de Shoulder
	puppt.add("Shoulder", Nodo("RArm", RArm));
	puppt.add("Shoulder", Nodo("LArm", LArm));
	puppt.add("Shoulder", Nodo("Neck", Neck));
	// Hijos de Pelvis
	puppt.add("Pelvis", Nodo("RThigh", RThigh));
	puppt.add("Pelvis", Nodo("LThigh", LThigh));

	// 3
		// Hijos de RArm
	puppt.add("RArm", Nodo("RForearm", RForearm));
	// Hijos de LArm
	puppt.add("LArm", Nodo("LForearm", LForearm));
	// Hijos de Neck
	puppt.add("Neck", Nodo("Head", Head)); // leaf
		// Hijos de Rthigh
	puppt.add("RThigh", Nodo("RCalf", RCalf));
	// Hijos de Lthigh
	puppt.add("LThigh", Nodo("LCalf", LCalf));

	// 4 (Hojas!)
		// de RForearm
	puppt.add("RForearm", Nodo("RHand", RHand));
	// de LForearm
	puppt.add("LForearm", Nodo("LHand", LHand));
	// de Head // no funcionales
	puppt.add("Head", Nodo("REye", REye));
	puppt.add("Head", Nodo("LEye", LEye));
	// RCalf
	puppt.add("RCalf", Nodo("RFoot", RFoot));
	// LCalf
	puppt.add("LCalf", Nodo("LFoot", LFoot));
	return puppt;
}