#version 150 core
void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
