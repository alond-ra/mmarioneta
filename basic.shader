#shader vertex
#version 460 core //360 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 textCoord;
layout(location = 0) in vec3 vnormal;

out vec2 v_TexCoord;
out vec3 v_FragPos;
out vec3 v_Normal;

//uniform mat4 u_MVP;
uniform mat4 f_Projection;
uniform mat4 f_View;
uniform mat4 f_Model;

void main()
{
	//gl_Position = u_MVP * position;
	gl_Position = (f_Projection * f_View * f_Model) * position;
	//v_TexCoord = texCoord;
	v_FragPos = vec3(f_Model * position);
	v_Normal = mat3(transpose(inverse(f_Model))) * vnormal;
}

#shader fragment
#version 460 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec3 v_FragPos;
in vec3 v_Normal;
out vec4 color;

uniform vec4 u_LightColor;
uniform vec4 u_ObjectColor;
uniform vec3 lightPos;

void main()
{
	
	float ambientStrenght = 0.1;
	float diffuseStrenght = 1.0;
	vec4 ambient = ambientStrenght * u_LightColor;

	vec3 norm = normalize(v_Normal);
	vec3 lightDir = normalize(lightPos - v_FragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec4 diffuse = diffuseStrenght * diff * u_LightColor;

	color = (ambient + diffuse) * u_ObjectColor;
}