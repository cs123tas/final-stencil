#version 330 core

uniform sampler2D pos;
uniform sampler2D vel;
uniform int numParticles;

uniform mat4 p;
uniform mat4 v;
uniform mat4 m;

out vec2 uv;
out vec3 color;

// Offsets and UVs for the triangle around the particle
const int NUM_VERTICES_PER_PARTICLE = 3;
const vec4 TRI_VERTS[NUM_VERTICES_PER_PARTICLE] = vec4[NUM_VERTICES_PER_PARTICLE](
    // TODO [Task 18] Calculate the triangle point offsets (see diagram in handout)
    // vec4(p1.x, p1.y, 0, 0),
    // vec4(p2.x, p2.y, 0, 0),
    // vec4(p3.x, p3.y, 0, 0)
    vec4(0, 4, 0, 0), vec4(0, 0, 0, 0), vec4(4, 0, 0, 0)
);

vec3 pickRainbowColor(float lifetime, float age) {
//    return HSLtoRGB(24.0 / 360.0, max(0.0, (1 - y)), 0.5);
    if (age / lifetime <= 0.2) {
        return vec3(1.0, 1.0, 1.0); //white
    } else if (age / lifetime < 1.2) {
        return vec3(0.941, 0.316, 0.234); //red
    } else if (age / lifetime < 2.6) {
        return vec3(.976, .585, .179); //orange
    } else if (age < 3.0) {
        return vec3(1.0, .903, .179); //yellow
    } else {
        return vec3(.5, .5, .5); //grey
    }
}

void main() {
    // TODO [Task 18] Which particle and triangle vertex are we dealing with?
    int particleID = int(floor(gl_VertexID / 3));
    int triID = int(gl_VertexID % 3);

    // Pass the tex coords to the fragment shader
    uv = TRI_VERTS[triID].xy;

    // TODO [Task 18] sample pos and vel textures
    vec4 posTime = texelFetch(pos, ivec2(particleID, 0), 0);
    vec4 velAge = texelFetch(vel, ivec2(particleID, 0), 0);

    // Calculate diameter based on age and lifetime
    float diameter = 0.02;
    diameter *= min(min(1.0, velAge.w / (0.1 * posTime.w)),
                    min(1.0, abs(posTime.w - velAge.w) / (0.1 * posTime.w)));

    // Calculate color based on particleID
    color = pickRainbowColor(posTime.w, velAge.w);

    // the offset to the points of the triangle
    vec4 triPos = diameter * TRI_VERTS[triID];

    // anchor point in world space
    vec4 anchorPoint = vec4(posTime.xyz, 1.0);

    // Center the particle around anchorPoint
    gl_Position = p * v * m * (anchorPoint + triPos);
}
