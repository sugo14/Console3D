#include "scripts.hpp"

#include <algorithm>

int colorLerp(int c1, int c2, float u) {
    u = std::clamp(u, 0.0f, 1.0f);
    int r = (int)((1 - u) * ((c1 >> 16) & 0xFF) + u * ((c2 >> 16) & 0xFF));
    int g = (int)((1 - u) * ((c1 >> 8) & 0xFF) + u * ((c2 >> 8) & 0xFF));
    int b = (int)((1 - u) * (c1 & 0xFF) + u * (c2 & 0xFF));
    return (r << 16) | (g << 8) | b;
}

int rgb(int r, int g, int b) {
    r = std::clamp(r, 0, 255);
    g = std::clamp(g, 0, 255);
    b = std::clamp(b, 0, 255);
    return (r << 16) | (g << 8) | b;
}

void CrystalScript::start(GameEngine* engine, GameObject* gameObject) {
    debug("CrystalScript started");
    gameObject->transform.scale = {4, 4, 4};

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-2.0f, 2.0f);
    std::uniform_real_distribution<float> dist2(-3.0f, 3.0f);
    std::uniform_real_distribution<float> dist3(-80.0f, -3.0f);
    std::uniform_real_distribution<float> dist4(2.0f, 8.0f);

    rotationSpeed = {-0.5, -1, -2};
    // gameObject->transform.position = {dist2(gen), dist2(gen), dist3(gen)};
    gameObject->transform.position = {0, 0, -30};
    gameObject->transform.rotation = {dist2(gen), dist2(gen), dist2(gen)};
    positionSpeed = {dist2(gen) / 20.0f, dist2(gen) / 20.0f, dist4(gen)};

    Vector3 min = gameObject->mesh.vertices[0], max = gameObject->mesh.vertices[0];
    int high = 0x0062cc, low = 0x910951;
    for (const Vector3& v : gameObject->mesh.vertices) {
        if (v.x > max.x) { max.x = v.x; }
        if (v.y > max.y) { max.y = v.y; }
        if (v.z > max.z) { max.z = v.z; }
        if (v.x < min.x) { min.x = v.x; }
        if (v.y < min.y) { min.y = v.y; }
        if (v.z < min.z) { min.z = v.z; }
    }

    std::uniform_real_distribution<float> colorDist(0.0f, 50.0f);
    std::uniform_real_distribution<float> jitterDist(-0.02f, 0.02f);
    for (int i = 0; i < gameObject->mesh.vertices.size(); i++) {
        float val = (gameObject->mesh.vertices[i].y - min.y) / (max.y - min.y);
        int color = colorLerp(
            low + rgb(colorDist(gen), colorDist(gen), colorDist(gen)),
            high + rgb(colorDist(gen), colorDist(gen), colorDist(gen)),
            val + jitterDist(gen)
        );
        gameObject->mesh.vertexColors.push_back(color);
    }
    gameObject->mesh.lightingMode = LightingMode::Crystal;
}

void CrystalScript::update(int deltaTime, GameEngine* engine, GameObject* gameObject) {
    float seconds = deltaTime / 1000.0f;
    gameObject->transform.rotation = gameObject->transform.rotation + rotationSpeed * seconds;
    gameObject->transform.position = gameObject->transform.position + positionSpeed * seconds;

    if (gameObject->transform.position.z > -3.0f) {
        gameObject->transform.position.z = -80.0f; // reset position
    }
}
