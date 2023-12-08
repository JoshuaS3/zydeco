R""(

#version 460 core

layout (local_size_x = 32, local_size_y = 32, local_size_z = 1) in;


layout(rgba32f, binding = 0) uniform image2D texture0;
uniform ivec2 screensize;
uniform dvec2 offset;
uniform double zoom;
uniform float z;
uniform float discard_threshold;
uniform int current_iteration;
uniform int it_steps;
uniform bool enable_interlacing;
uniform int interlace_layer;


const int ADAM7_MATRIX[8][8] = {
    {1, 6, 4, 6, 2, 6, 4, 6},
    {7, 7, 7, 7, 7, 7, 7, 7},
    {5, 6, 5, 6, 5, 6, 5, 6},
    {7, 7, 7, 7, 7, 7, 7, 7},
    {3, 6, 4, 6, 3, 6, 4, 6},
    {7, 7, 7, 7, 7, 7, 7, 7},
    {5, 6, 5, 6, 5, 6, 5, 6},
    {7, 7, 7, 7, 7, 7, 7, 7},
};


dvec2 screenSpaceToGraphSpace(dvec2 coord)
{
    dvec2 dscreensize = dvec2(screensize);
    double aspectratio = dscreensize.x/dscreensize.y;
    return (((coord - dscreensize/2) / dscreensize * zoom) - (offset / dscreensize))*dvec2(aspectratio, 1.0);
}

void main()
{
    ivec2 texelCoord = ivec2(gl_GlobalInvocationID.xy);

    vec4 currentValue;

    dvec2 c = screenSpaceToGraphSpace(vec2(texelCoord));
    c.y = -c.y;
    if (current_iteration == 0 && interlace_layer == 1)
    {
        currentValue = vec4(0.5, c.x, c.y, 1.0);
    }
    else
    {
        currentValue = imageLoad(texture0, texelCoord);
    }


    bool do_compute = true;
    if (enable_interlacing)
    {
        do_compute = ADAM7_MATRIX[gl_LocalInvocationID.y % 8][gl_LocalInvocationID.x % 8] == interlace_layer;
    }
    if (do_compute)
    {
        if (abs(currentValue.x) < 0.6)
        {
            double x = c.x;//abs(c.x);
            double y = c.y;//abs(c.y);
            double x2 = x*x;
            double y2 = y*y;

            for (int i = 1; i < it_steps; i++)
            {
                y = 2.*x*y + c.y;
                //y = 2.*abs(x*y+z) + c.y - 2.*abs(z);
                x = x2 - y2 + c.x;
                x2 = x*x;
                y2 = y*y;
                if ((x2 + y2) > discard_threshold)
                {
                    currentValue.x = current_iteration + i;
                    break;
                }
            }
            currentValue.yz = vec2(float(x), float(y));
        }
    }

    imageStore(texture0, texelCoord, currentValue);
//    memoryBarrier();
}


)""
