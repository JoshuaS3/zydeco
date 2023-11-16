R""(

#version 460 core


in vec3 vertexColor;
uniform uint time;

out vec4 fragColor;


vec3 hueShift(vec3 color, float hue) {
    const vec3 k = vec3(0.57735, 0.57735, 0.57735);
    float cosAngle = cos(hue);
    return vec3(color * cosAngle + cross(k, color) * sin(hue) + k * dot(k, color) * (1.0 - cosAngle));
}


void main()
{
    fragColor = vec4(hueShift(vertexColor, time/1000.), 1.0f);
}

)""
