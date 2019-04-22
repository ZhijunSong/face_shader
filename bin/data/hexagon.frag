//hexagon.frag
#version 120
#extension GL_ARB_texture_rectangle : enable

uniform float len;
uniform sampler2DRect colorTex0;
void main (void){
    float TR = 0.866025f;
    float x = gl_TexCoord[0].x;
    float y = gl_TexCoord[0].y;
    int wx = int(x/1.5f/len);
    int wy = int(y/TR/len);
    vec2 v1, v2, vn;
    if(wx/2 * 2 == wx) {
        if(wy/2 * 2 == wy) {
            v1 = vec2(len*1.5f*wx, len*TR*wy);
            v2 = vec2(len*1.5f*(wx+1), len*TR*(wy+1));
        } else {
            v1 = vec2(len*1.5f*wx, len*TR*(wy+1));
            v2 = vec2(len*1.5f*(wx+1), len*TR*wy);
        }
    } else {
        if(wy/2 * 2 == wy) {
            v1 = vec2(len*1.5f*wx, len*TR*(wy+1));
            v2 = vec2(len*1.5f*(wx+1), len*TR*wy);
        } else {
            v1 = vec2(len*1.5f*wx, len*TR*wy);
            v2 = vec2(len*1.5f*(wx+1), len*TR*(wy+1));
        }
    }
    float s1 = sqrt( pow(v1.x-x, 2) + pow(v1.y-y, 2) );
    float s2 = sqrt( pow(v2.x-x, 2) + pow(v2.y-y, 2) );
    if(s1 < s2)
        vn = v1;
    else
        vn = v2;
    vec4  color = texture2DRect(colorTex0, vn);
    gl_FragColor = color;
}

