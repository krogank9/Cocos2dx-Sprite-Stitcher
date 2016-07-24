#ifdef GL_ES
precision lowp float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform sampler2D u_texture1;

void main(void)
{
    vec3 tex = texture2D(CC_Texture0, v_texCoord).rgb; //CC_Texture0 is rgb texture of the sprite
    float alpha = texture2D(u_texture1, v_texCoord).r;
    gl_FragColor = vec4(tex, alpha);
    //gl_FragColor =  texture2D(CC_Texture0, v_texCoord);
}
