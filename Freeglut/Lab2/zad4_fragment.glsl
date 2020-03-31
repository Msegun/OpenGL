#version 330

// Predefiniowane dane wejsciowe i wyjsciowe
in  vec4 gl_FragCoord;
//in  int  gl_PrimitiveID;

out vec4 outColor;

void main()
{
        vec4 black_t = vec4(0.0, 0.0, 0.0, 0.4);
        vec4 green = vec4(0.0 ,1.0, 0.0, 0.0);
        vec4 pink = vec4(1.0, 0.0, 1.0, 0.0);
        float alpha = gl_FragCoord.x/500;
        if (gl_PrimitiveID % 7 == 0)
                outColor = mix(black_t, green, alpha);
        if (gl_PrimitiveID % 7 == 1)
                outColor = mix(black_t, green, 1 - alpha);
        if (gl_PrimitiveID % 7  == 2)
                outColor = mix(black_t, green, alpha);
        if (gl_PrimitiveID % 7 == 3)
                outColor = mix(black_t, green, 1 - alpha);
        if (gl_PrimitiveID % 7  == 4)
                outColor = mix(black_t, pink, alpha);
        if (gl_PrimitiveID % 7 == 5)
                outColor = mix(black_t, pink, 1 - alpha);
        if (gl_PrimitiveID % 7  == 6)
                outColor = mix(black_t, pink, alpha);
}
