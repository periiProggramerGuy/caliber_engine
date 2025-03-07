#pragma once
class CSV {
public:
	const char* Frame;
	const char* Default;
	const char* ShadowMap;
	const char* Outline;
	const char* Skybox;
	CSV() {
		Default =
			R"(
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTex;

out vec3 crntPos;
out vec3 Normal;
out vec3 color;
out vec2 texCoord;
out vec3 eyeLightDir;

uniform mat4 camMatrix;
uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;

uniform vec3 lightPos;

void main()
{
    vec3 worldPos = vec3(model * translation * rotation * scale * vec4(aPos, 1.0f));
    
    vec3 worldNormal = normalize(vec3(model * vec4(aNormal, 0.0f)));
    
    vec3 objectLightPos = vec3(model * vec4(lightPos, 1.0f));
    
    vec3 eyeLightPos = vec3(camMatrix * vec4(objectLightPos, 1.0f));
    
    eyeLightDir = normalize(eyeLightPos - worldPos);
    
    crntPos = worldPos;
    Normal = worldNormal;
    color = aColor;
    texCoord = mat2(0.0, -1.0, 1.0, 0.0) * aTex;
	
    gl_Position = camMatrix * vec4(worldPos, 1.0);
}

		)";


		Frame =
			R"(
#version 330 core

layout (location = 0) in vec2 inPos;
layout (location = 1) in vec2 inTexCoords;

out vec2 texCoords;

void main()
{
    gl_Position = vec4(inPos.x, inPos.y, 0.0, 1.0); 
    texCoords = inTexCoords;
}  

		)";


		Default =
			R"(
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTex;

out vec3 crntPos;
out vec3 Normal;
out vec3 color;
out vec2 texCoord;
out vec4 fragPosLight;

uniform mat4 camMatrix;
uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;
uniform mat4 lightProjection;

void main()
{
    crntPos = vec3(model * translation * rotation * scale * vec4(aPos, 1.0));
    Normal = normalize(mat3(transpose(inverse(model * rotation))) * aNormal);
    color = aColor;
    texCoord = mat2(0.0, -1.0, 1.0, 0.0) * aTex;
    fragPosLight = lightProjection * vec4(crntPos, 1.0);

    gl_Position = camMatrix * vec4(crntPos, 1.0);
}

		)";


		ShadowMap =
			R"(
#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 crntPos;

uniform mat4 lightProjection;
uniform mat4 model;

uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;

void main()
{
	crntPos = vec3(translation * rotation * scale * vec4(aPos, 1.0f));

    gl_Position = lightProjection * model * vec4(crntPos, 1.0);
}

		)";


		Outline =
			R"(
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;


uniform mat4 camMatrix;
uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;
uniform float outlining;

void main()
{
	

	vec3 crntPos = vec3(model * translation * rotation * scale * vec4(aPos + aNormal * outlining, 1.0f));
	gl_Position = camMatrix * vec4(crntPos, 1.0);

	
}

		)";

		Skybox =
			R"(
#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 texCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    vec4 pos = projection * view * vec4(aPos, 1.0f);
    gl_Position = vec4(pos.x, pos.y, pos.w, pos.w);
    texCoords = vec3(aPos.x, aPos.y, -aPos.z);
}    
		)";


	}


};