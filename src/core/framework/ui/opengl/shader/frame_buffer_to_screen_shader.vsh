attribute vec2 a_Position;

varying vec2 v_TextureCoordinates;

void main()
{
    gl_Position = vec4(a_Position, 0, 1);
    v_TextureCoordinates = (a_Position + 1.0) / 2.0;
}