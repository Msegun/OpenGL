#version 330

// Dane przekazane z poprzednich etapow
in vec4 mojKolor;
out vec4 outColor;

uniform float width;
uniform float height;

void main()
{
    // To do set resolution
    vec4 workColor;
    vec2 pos = gl_FragCoord.xy / vec2(width, height);
    float center_distance = distance(pos, vec2(0.5));

    //    if (center_distance < 0.1){
    //        workColor = mix(vec4(0,0,1,1), mojKolor, 0.3 + center_distance);
    //    }
    //    else
    //        workColor = mix(mojKolor, vec4(0, 0, 1, 1), 0.7 - center_distance);
    //
    //    // outColor = workColor;
    //    outColor = mix(workColor,  vec4(1, 1, 1, 0), 0.3 + center_distance);

    workColor = mojKolor + center_distance;
    outColor = mix(workColor, vec4(1,1,1,0.5), center_distance);
}
