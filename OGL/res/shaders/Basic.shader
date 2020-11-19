#shader vertex
#version 460 core
    
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
        
out vec2 v_texCoord;

uniform mat4 u_mvp;

void main()
{
    gl_Position = u_mvp * position;
    v_texCoord = texCoord;
}

#shader fragment
#version 460 core
    
layout(location = 0) out vec4 color;

uniform vec4 u_color;
uniform sampler2D u_texture;
        
in vec2 v_texCoord;

void main()
{
    color = texture(u_texture, v_texCoord) * u_color;
}