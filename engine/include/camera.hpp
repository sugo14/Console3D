#pragma once

#include "mesh.hpp"
#include "screendata.hpp"

struct GameObject;

float degToRad(float deg);

int interpolateColor(int c1, int c2, float u);
int interpolateColor(int c1, int c2, int c3, float u, float v, float w);

struct Frustum {
    float fovY, aspect;
    float nearZ, farZ;
    Matrix44 projMatrix;

    Frustum();
    
    Frustum(float fovY, float aspect, float nearZ, float farZ);

    /// @brief Initializes the projection matrix based on the frustum parameters.
    void initProjMatrix();

    /// @brief Converts a point in world space to NDC space.
    /// X and Y values are in the range [-1, 1] and Z is in the range [0, 1].
    /// @param point The point in world space to convert.
    /// @return The point in NDC space.
    Vector3 ndcSpace(Vector3 point) const;
};

struct Camera {
    Frustum frustum;
    Transform transform;

    Camera();

    /// @brief Draws the current triangles to a screen using rasterization.
    /// @param screenData The screen to draw to.
    void draw(std::vector<GameObject>& gameObjects, ScreenData& screenData) const;

    /// @brief Draws the current triangles as wireframes to a screen.
    /// @param screenData The screen to draw to.
    void drawWireframe(std::vector<GameObject>& gameObjects, ScreenData& screenData) const;
};
