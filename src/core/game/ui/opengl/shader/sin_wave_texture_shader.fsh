#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D u_TextureUnit;
uniform float u_Offset;

varying vec4 v_Color;
varying vec2 v_TextureCoordinates;

void main()
{
    vec2 texCoords = v_TextureCoordinates;
    texCoords.x += sin(texCoords.y * 4.0 * 2.0 * 3.14159 + u_Offset) / 100.0;
    gl_FragColor = v_Color * texture2D(u_TextureUnit, texCoords);
}
