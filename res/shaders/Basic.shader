#shader vertex
#version 460 core
    
layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in float textureSlot;
        
out vec2 v_texCoord;
out vec4 v_color;
out float v_textureSlot;

uniform mat4 u_mvp;

void main()
{
    gl_Position = u_mvp * vec4(position, 1.0);
    v_texCoord = texCoord;
    v_color = color;
    v_textureSlot = textureSlot;
}

#shader fragment
#version 460 core
    
layout(location = 0) out vec4 color;

uniform sampler2D u_textures[2];
        
in vec2 v_texCoord;
in vec4 v_color;
in float v_textureSlot;

void main()
{
    int textureSlot = int(v_textureSlot);
    color = texture(u_textures[textureSlot], v_texCoord) * vec4(v_texCoord, v_textureSlot, 1.0);
}