R""(

#version 460 core


in ivec4 gl_FragCoord;
layout(binding=0, rgba32f) uniform image2D texture0;
uniform ivec2 screensize;
uniform int it_count;
uniform double zoom;
uniform float brightness;
uniform bool enable_interlacing;
uniform int interlace_layer;
uniform bool first_interlace;
out vec4 fragColor;

const float INTERLACE_COLOR_MULTIPLIERS[7] = {3., 3., 2., 2., 2., 1., 1.};

void main()
{
    ivec2 texcoord = gl_FragCoord.xy;
    bool point_contains_data = imageLoad(texture0, texcoord).r >= 0.9;
    if (enable_interlacing && first_interlace && !point_contains_data)
    {
        int nearest_x = 8;
        int nearest_y = 8;
        int offset_x = 0;
        int offset_y = 0;
        switch (interlace_layer)
        {
            case 1:
                nearest_x = 8;
                nearest_y = 8;
                int offset_x = 8;
                int offset_y = 8;
                break;
            case 2:
                nearest_x = 8;
                nearest_y = 8;
                offset_x = 4;
                break;
            case 3:
                nearest_x = 4;
                nearest_y = 8;
                offset_y = 4;
                break;
            case 4:
                nearest_x = 4;
                nearest_y = 4;
                offset_x = 2;
                break;
            case 5:
                nearest_x = 2;
                nearest_y = 4;
                offset_y = 2;
                break;
            case 6:
                nearest_x = 2;
                nearest_y = 2;
                offset_x = 1;
                break;
            case 7:
                nearest_x = 1;
                nearest_y = 2;
                offset_y = 1;
                break;
        }

        int xpos = (int(gl_FragCoord.x) - (int(gl_FragCoord.x) % nearest_x)) + offset_x;
        int ypos = (int(gl_FragCoord.y) - (int(gl_FragCoord.y) % nearest_y)) + offset_y;

        texcoord = ivec2(xpos, ypos).xy;
    }

    float iterations = imageLoad(texture0, texcoord).r;
    float col = iterations;
    if (enable_interlacing && first_interlace) { col *= INTERLACE_COLOR_MULTIPLIERS[interlace_layer - 1]; }

    if (iterations <= 0.6)
    {
        fragColor = vec4(0.0, 0.0, 0.0, 0.0);
    }
    else
    {
        col = clamp(col/it_count*brightness, 0.0, 1.0);
        fragColor = vec4(col*0.65, col*0.35, col*0.7, 0.0);
    }
}

)""
