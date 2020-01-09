#version 330 core

layout (location = 0) in vec3 position;

// MVM matrices.
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	// MVP = Model * View * Projection
	gl_Position = projection * view * model * vec4(position, 1.0);
}

