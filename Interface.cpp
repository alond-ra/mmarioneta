#include "Interface.h"
#include "Model.h"

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

void resetStateStack(std::stack<State>& stck, int n)
{
	while (stck.size() > n)
		stck.pop();
}
void modelUndo(Model& model)
{
	model.redostack.push(model.undostack.top());
	model.undostack.pop();
	model.setModelState(model.undostack.top());
}
void modelRedo(Model& model)
{
	model.setModelState(model.redostack.top());
	model.redostack.pop();
}
void modelReset(Model& marioneta)
{
	if (marioneta.undostack.size() > 1)
	{
		State zero;
		marioneta.current_st = zero;
		marioneta.setModelState(marioneta.current_st);
	}
	resetStateStack(marioneta.undostack, 1);
	resetStateStack(marioneta.redostack, 0);
}

void interfaz(Model& marioneta)
{
	ImGui::Begin("Control de movimientos", NULL);
	ImGui::SetWindowSize(ImVec2(200, 720));
	//marioneta.current_std::cout << marioneta.current_st.HeadOrientation.x << marioneta.current_st.HeadOrientation.y << marioneta.current_st.HeadOrientation.z << marioneta.current_std::endl;

	/// muestra los slider para cada parte movible de la marioneta
	/// se utiliza este tipo de control para poder limitar los angulos del movimiento
	/// angulos más o menos basado en 
	/// Panero J., Zelnik M. Human Dimension and Interior Space: A Source Book of Design Reference Standards Watson-Guptill (2014)
	/// 8.9 Antrhopomorpric tables: Joint motion (p297)

	// 1
	if (ImGui::TreeNode("Shoulder"))
	{
		ImGui::Text("Pitch [x]");
		ImGui::SliderFloat("##Shoulder.pitch", &marioneta.current_st.ShoulderOrientation.x, -30.0f, 70.0f);
		ImGui::Text("Yaw [y]");
		ImGui::SliderFloat("##Shoulder.yaw", &marioneta.current_st.ShoulderOrientation.y, -35.0f, 35.0f);
		ImGui::Text("Roll [z]");
		ImGui::SliderFloat("##Shoulder.roll", &marioneta.current_st.ShoulderOrientation.z, -40.0f, 40.0f);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Pelvis"))
	{
		ImGui::Text("Pitch [x]");
		ImGui::SliderFloat("##Pelvis.pitch", &marioneta.current_st.PelvisOrientation.x, -80.0f, 10.0f);
		ImGui::Text("Yaw [y]");
		ImGui::SliderFloat("##Pelvis.yaw", &marioneta.current_st.PelvisOrientation.y, -35.0f, 35.0f);
		ImGui::Text("Roll [z]");
		ImGui::SliderFloat("##Pelvis.roll", &marioneta.current_st.PelvisOrientation.z, -40.0f, 40.0f);
		ImGui::TreePop();
	} //
	ImGui::Separator();
	// 2
	if (ImGui::TreeNode("Right Arm"))
	{
		ImGui::Text("Pitch [x]");
		ImGui::SliderFloat("##RArm.pitch", &marioneta.current_st.RArmOrientation.x, -180.0f, 45.0f);
		ImGui::TextDisabled("Yaw [y]");
		ImGui::SliderFloat("##RArm.yaw", &marioneta.current_st.RArmOrientation.y, -180.0f, 45.0f);
		ImGui::Text("Roll [z]");
		ImGui::SliderFloat("##RArm.roll", &marioneta.current_st.RArmOrientation.z, -130.0f, 40.0f);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Left Arm"))
	{
		ImGui::Text("Pitch [x]");
		ImGui::SliderFloat("##LArm.pitch", &marioneta.current_st.LArmOrientation.x, 45.0f, -180.0f);
		ImGui::TextDisabled("Yaw [y]");
		ImGui::SliderFloat("##LArm.yaw", &marioneta.current_st.LArmOrientation.y, 45.0f, -180.0f);
		ImGui::Text("Roll [z]");
		ImGui::SliderFloat("##LArm.roll", &marioneta.current_st.LArmOrientation.z, -40.0f, 130.0f);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Neck"))
	{
		ImGui::Text("Pitch [x]");
		ImGui::SliderFloat("##Neck.pitch", &marioneta.current_st.NeckOrientation.x, -50.0f, 60.0f);
		ImGui::Text("Yaw [y]");
		ImGui::SliderFloat("##Neck.yaw", &marioneta.current_st.NeckOrientation.y, -55.0f, 55.0f);
		ImGui::Text("Roll [z]");
		ImGui::SliderFloat("##Neck.roll", &marioneta.current_st.NeckOrientation.z, -40.0f, 40.0f);
		ImGui::TreePop();
	} // 
	if (ImGui::TreeNode("Right Thigh"))
	{
		ImGui::Text("Pitch [x]");
		ImGui::SliderFloat("##RThigh.pitch", &marioneta.current_st.RThighOrientation.x, -90.0f, 45.0f);
		ImGui::Text("Yaw [y]");
		ImGui::SliderFloat("##RThigh.yaw", &marioneta.current_st.RThighOrientation.y, -25.0f, 25.0f);
		ImGui::Text("Roll [z]");
		ImGui::SliderFloat("##RThigh.roll", &marioneta.current_st.RThighOrientation.z, -50.0f, 25.0f);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Left Thigh"))
	{
		ImGui::Text("Pitch [x]");
		ImGui::SliderFloat("##LThigh.pitch", &marioneta.current_st.LThighOrientation.x, -90.0f, 45.0f);
		ImGui::Text("Yaw [y]");
		ImGui::SliderFloat("##LThigh.yaw", &marioneta.current_st.LThighOrientation.y, -25.0f, 25.0f);
		ImGui::Text("Roll [z]");
		ImGui::SliderFloat("##LThigh.roll", &marioneta.current_st.LThighOrientation.z, -25.0f, 50.0f);
		ImGui::TreePop();
	}

	ImGui::Separator();
	// 3
	if (ImGui::TreeNode("Right Forearm"))
	{
		ImGui::Text("Pitch [x]");
		ImGui::SliderFloat("##RForearm.pitch", &marioneta.current_st.RForearmOrientation.x, -145.0f, 0.0f);
		ImGui::Text("Yaw [y]");
		ImGui::SliderFloat("##RForearm.yaw", &marioneta.current_st.RForearmOrientation.y, -40.0f, 70.0f);
		ImGui::TextDisabled("Roll [z]");
		ImGui::SliderFloat("##RForearm.roll", &marioneta.current_st.RForearmOrientation.z, -90.0f, 90.0f);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Left Forearm"))
	{
		ImGui::Text("Pitch [x]");
		ImGui::SliderFloat("##LForearm.pitch", &marioneta.current_st.LForearmOrientation.x, -145.0f, 0.0f);
		ImGui::Text("Yaw [y]");
		ImGui::SliderFloat("##LForearm.yaw", &marioneta.current_st.LForearmOrientation.y, -70.0f, 40.0f);
		ImGui::TextDisabled("Roll [z]");
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Right Calf"))
	{
		ImGui::Text("Pitch [x]");
		ImGui::SliderFloat("##RCalf.pitch", &marioneta.current_st.RCalfOrientation.x, 0.0f, 145.0f);
		ImGui::TextDisabled("Yaw [y]");
		ImGui::TextDisabled("Roll [z]");
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Left Calf"))
	{

		ImGui::Text("Pitch [x]");
		ImGui::SliderFloat("##LCalf.pitch", &marioneta.current_st.LCalfOrientation.x, 0.0f, 145.0f);
		ImGui::TextDisabled("Yaw [y]");
		ImGui::TextDisabled("Roll [z]");
		ImGui::TreePop();
	}

	ImGui::Separator();
	// 4
	if (ImGui::TreeNode("Right Hand"))
	{
		ImGui::Text("Pitch [x]");
		ImGui::SliderFloat("##RHand.pitch", &marioneta.current_st.RHandOrientation.x, -60.0f, 70.0f);
		ImGui::TextDisabled("Yaw [y]");
		//ImGui::SliderFloat("##RHand.yaw", &marioneta.current_st.RHandOrientation.y, -15.0f, 30.0f);
		ImGui::Text("Roll [z]");
		ImGui::SliderFloat("##RHand.roll", &marioneta.current_st.RHandOrientation.z, -30.0f, 15.0f);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Left Hand"))
	{
		ImGui::Text("Pitch [x]");
		ImGui::SliderFloat("##LHand.pitch", &marioneta.current_st.LHandOrientation.x, -65.0f, 70.0f);
		ImGui::TextDisabled("Yaw [y]");
		//ImGui::SliderFloat("##LHand.yaw", &marioneta.current_st.LHandOrientation.y, -90.0f, 90.0f);
		ImGui::Text("Roll [z]");
		ImGui::SliderFloat("##LHand.roll", &marioneta.current_st.LHandOrientation.z, -15.0f, 30.0f);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Right Foot"))
	{
		ImGui::Text("Pitch [x]");
		ImGui::SliderFloat("##RFoot.pitch", &marioneta.current_st.RFootOrientation.x, -20.0f, 35.0f);
		ImGui::TextDisabled("Yaw [y]");
		//ImGui::SliderFloat("##RFoot.yaw", &marioneta.current_st.RFootOrientation.y, -25.0f, 35.0f);
		ImGui::Text("Roll [z]");
		ImGui::SliderFloat("##RFoot.roll", &marioneta.current_st.RFootOrientation.z, -25.0f, 35.0f);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Left Foot"))
	{
		ImGui::Text("Pitch [x]");
		ImGui::SliderFloat("##LFoot.pitch", &marioneta.current_st.LFootOrientation.x, -20.0f, 35.0f);
		ImGui::TextDisabled("Yaw [y]");
		//ImGui::SliderFloat("##RFoot.yaw", &marioneta.current_st.RFootOrientation.y, -25.0f, 35.0f);
		ImGui::Text("Roll [z]");
		ImGui::SliderFloat("##RFoot.roll", &marioneta.current_st.RFootOrientation.z, -35.0f, 25.0f);
		ImGui::TreePop();
	}

	ImGui::Separator();
	ImGui::Separator();


	// 0: movimiento de la marioneta entera:
	if (ImGui::TreeNode("Puppet"))
	{
		ImGui::Text("Desplazamiento horizontal");
		ImGui::SliderFloat("##Torso.x", &marioneta.current_st.TorsoPosition.x, -27.6f, 27.6f);
		ImGui::Text("Desplazamiento vertical");
		ImGui::SliderFloat("##Torso.y", &marioneta.current_st.TorsoPosition.y, -18.4f, 23.3f);
		ImGui::Text("Acercamiento");
		ImGui::SliderFloat("##Torso.z", &marioneta.current_st.TorsoPosition.z, -70.0f, 18.5f);
		ImGui::Text("Pitch");
		ImGui::SliderFloat("##Torso.pitch", &marioneta.current_st.TorsoOrientation.x, -90.0f, 90.0f);
		ImGui::Text("Yaw");
		ImGui::SliderFloat("##Torso.yaw", &marioneta.current_st.TorsoOrientation.y, -90.0f, 90.0f);
		ImGui::Text("Roll [z]");
		ImGui::SliderFloat("##Torso.roll", &marioneta.current_st.TorsoOrientation.z, -90.0f, 90.0f);
		ImGui::TreePop();
	}
	ImGui::Separator();
	ImGui::Separator();

	// si el estado actual y el ultimo guardado en la pila de acciones son iguales
	if (!equalState(marioneta.undostack.top(), marioneta.current_st)) {
		//std::cout << "if" << std::endl;
		marioneta.undostack.push(marioneta.current_st); // si no son iguales, almacena uno nuevo
		marioneta.setModelState(marioneta.current_st); // y actualiza el movimiento de la marioneta
	} // 	
	
	ImGui::End();
}