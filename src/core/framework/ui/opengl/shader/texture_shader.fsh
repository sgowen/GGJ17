#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D u_TextureUnit;

varying vec4 v_Color;
varying vec2 v_TextureCoordinates;

void main()
{
    gl_FragColor = texture2D(u_TextureUnit, v_TextureCoordinates);
    
    if (gl_FragColor.a > 0.0
        && v_Color.g < 1.0)
    {
        float redness = v_Color.r * 2.0;
        redness = clamp(v_Color.r, 0.0, 1.0);
        float rDelta = 1.0 - gl_FragColor.r;
        gl_FragColor.r += rDelta * redness;
        gl_FragColor.r = clamp(gl_FragColor.r, 0.0, 1.0);
        
        if (v_Color.r > 0.5)
        {
            float additive = (v_Color.r - 0.5) * 2.0;
            
            float gDelta = 1.0 - gl_FragColor.g;
            float bDelta = 1.0 - gl_FragColor.b;
            
            gl_FragColor.g += gDelta * additive;
            gl_FragColor.g = clamp(gl_FragColor.g, 0.0, 1.0);
            
            gl_FragColor.b += bDelta * additive;
            gl_FragColor.b = clamp(gl_FragColor.b, 0.0, 1.0);
        }
    }
}
