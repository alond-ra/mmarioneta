//
// The puppet
// Gráficas por computadora
// Alondra Galván Patlán
// 04/10/23
//


#include "necessary_headers.h"


int main()
{
	//std::cout << "print check 4" << std::endl;
	// initialize glfw and create window/context
	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW." << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// window ; opengl context
	GLFWwindow* window = glfwCreateWindow(1250, 720, "Puppet - Computer Graphics", NULL, NULL);
	if (!window){
		std::cout << "Failed to open GLFW window." << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	
	/* window icon */ // https://youtu.be/So7J1dJhmZw
	int width, height, channels;
	unsigned char* pixels = stbi_load("stb/icon.png", &width, &height, &channels, 4);
	GLFWimage img[1];
	img[0].height = height; img[0].width = width; img[0].pixels = pixels;
	glfwSetWindowIcon(window, 1, img);
	/* */
	
	// GLEW initialize
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}		
	else 
		std::cout << "GL VERSION " << glGetString(GL_VERSION) << std::endl << std::endl;
	//


	// settings for transparency, depth testing, line smoothing, and alpha handling.
	GLCall(
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_DEPTH_CLAMP);
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_SAMPLE_ALPHA_TO_ONE);
	);

	// ImGui setup
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui::StyleColorsDark();
	
	ImGui_ImplOpenGL3_Init("#version 460");
	//
	
	// Sphere mesh with sector count
	int sectorCount = 80;              // Number of sectors in the sphere
	float* positions;                       // Vertex positions
	unsigned int* indices;           // Vertex indices

	int idx_size = buildVertices(1.f, sectorCount, positions, indices);		 // Build sphere vertices and indices
	int nv = (1 + sectorCount / 2) * (sectorCount + 1);											 // Total number of vertices
	VertexArray va;

	// Create vertex and index buffers for the sphere
	VertexBuffer vb(positions, nv * 3 * sizeof(float));
	VertexBufferLayout layout;
	layout.AddFloat(3);  // xyz
	IndexBuffer ib(indices, idx_size);

	va.AddBuffer(vb, layout);
	//


	// Puppet model with a specified color
	Model model = puppetmodel(glm::vec4(0.74f, 0.85f, 0.85f, 1.0f));

	// yaw and pitch angles for the camera
	float yaw = 0.0f;             // horizontal rotation
	float pitch = -90.0f;      // vertical rotation

	// initial position of the camera
	glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 30.0f);

	Camera camera(yaw, pitch, cameraPosition);
	Shader shader("basic.shader");


	/* camera stuff: https://learnopengl.com/Getting-Started/Camera */ 

	// Camera's front direction based on yaw and pitch angles
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	glm::vec3 cameraFront = glm::normalize(direction);																											// camera's front vector

	glm::mat4 View = glm::lookAt(cameraPosition, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));		// view matrix using the camera's position, target, and up vector
	glm::mat4 Projection = glm::perspective(glm::radians(450.0f), 700.0f / 700.0f, 0.1f, 100.0f);						// perspective projection matrix

	// set the view and projection matrices as uniforms in the shader
	shader.SetUniformMat4f("f_View", View);
	shader.SetUniformMat4f("f_Projection", Projection);

	// light properties: color and position
	glm::vec4 lightColor(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPosition(0.f, 0.f, 50.f);

	// Set light color and position as uniforms in the shader
	shader.SetUniform4f("u_LightColor", lightColor);
	shader.SetUniform3f("lightPos", lightPosition);

	va.Unbind();
	vb.Unbind();
	ib.Unbind();

	glBindVertexArray(0);
	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	while (!glfwWindowShouldClose(window)){

		// ImGui setup for new frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		interfaz(model);
		//buttons(model);		

		// Main menu bar for undo, redo, reset, close			//  implementados aquí por la facilidad del disable/enable
		if (ImGui::BeginMainMenuBar()){

			// menu items
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(7, 0));
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20, 0));
			//ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0,0));

			// UNDO 
			if (model.undostack.size() <= 1)
				ImGui::BeginMenu("undo", 0);
			else
				if (ImGui::MenuItem("undo"))
					modelUndo(model);

			// REDO
			if (model.redostack.size() == 0)
				ImGui::BeginMenu("redo", 0);
			else
				if (ImGui::MenuItem("redo")) 
					modelRedo(model);
			
			// RESET
			if (model.undostack.size() == 1 && model.redostack.size() == 0)
				ImGui::BeginMenu("reset", 0);
			else
				if (ImGui::MenuItem("reset"))
					modelReset(model);
			
			// CLOSE
			if (ImGui::BeginMenu("close")){
				std::cout << "------------------------------------------" << std::endl;
				std::cout << "------------------------------------------" << std::endl;
				std::cout << "         La ventana se ha cerrado." << std::endl;
				std::cout << "------------------------------------------" << std::endl;
				std::cout << "------------------------------------------" << std::endl;
				//glfwWindowShouldClose(window) = true; ????
				return 0;
			}

			ImGui::PopStyleVar(2);
			ImGui::EndMainMenuBar();
		}

		// rendeering
		Renderer render;
		model.build(render, va, ib, shader);
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


		// 
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// clean up
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();

	return 0;
}