#version 450 core

// location = 1 -> normals, location = 2 -> textureCoords
layout (location = 0) in vec3 position;
layout (location = 3) in vec3 color;

// MVM matrices.
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Send color to fragment shader.
out vec3 outColor;

void main()
{
	// MVP = Model * View * Projection
	gl_Position = projection * view * model * vec4(position, 1.0);
	outColor = color;
}

