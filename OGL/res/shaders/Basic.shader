#shader vertex
#version 460 core
    
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec4 color;
        
out vec2 v_texCoord;
out vec4 v_color;

uniform mat4 u_mvp;

void main()
{
    gl_Position = u_mvp * position;
    v_texCoord = texCoord;
    v_color = color;
}

#shader fragment
#version 460 core
    
layout(location = 0) out vec4 color;

uniform vec4 u_color;
uniform sampler2D u_texture;
        
in vec2 v_texCoord;
in vec4 v_color;


void main()
{
    color = v_color;
}