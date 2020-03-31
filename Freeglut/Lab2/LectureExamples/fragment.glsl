#version 330


// Predefiniowane dane wejsciowe i wyjsciowe
in  vec4 gl_FragCoord;
//in  int  gl_PrimitiveID;

out vec4 outColor;


float random (vec2 uv)
{
	return sin(dot(uv,vec2(12.9898,78.233)))*43758.5453123
	  - floor(sin(dot(uv,vec2(12.9898,78.233)))*43758.5453123);
}



void main()
{
    float ran1 = random(gl_FragCoord.xy);
    float ran2 = random(gl_FragCoord.yx);
    float ran3 = random(gl_FragCoord.xx);
    vec4 pod = vec4(0.0, 1.0, 0.0, 1.0);
    pod += vec4(ran1, ran2, ran3, 1.0)*2.0;
    if(gl_PrimitiveID % 2 == 0)
	    outColor = vec4(ran1, ran2, ran3, 1.0);
	else {
	    outColor = vec4(1, 0, 0, 1.0);
	}
}
