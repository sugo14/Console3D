#include "camera.hpp"
#include "tui.hpp"
#include "debug.hpp"
#include "gameengine.hpp"
#include "scripts.hpp"
#include "image.hpp"

#include <iostream>
#include <unistd.h>

void end() {
    return;
    std::cout << "Game over! You died due to an asteroid collision." << std::endl;
    std::cout << "Final score: " << PlayerBodyScript::score << std::endl;
}

int main() {
    GameEngine engine = GameEngine();
    
    int cockpitColor = 0x323542; // 0x6b4e2e
    int barrelColor = 0x8d93b5; // 0xfcb86d

    // for (int i = 0; i < 2; i++) {
    //     GameObject obj;
    //     obj.mesh = Mesh::loadObjFile("sharp-crystal-m");
    //     obj.name = "Crystal" + std::to_string(i);
    //     obj.tags = {"crystal"};
    //     obj.scripts.push_back(std::make_unique<SphereCollider>(3));
    //     obj.scripts.push_back(std::make_unique<CrystalScript>());
    //     engine.addObject(std::move(obj));

    //     GameObject obj2;
    //     obj2.mesh = Mesh::loadObjFile("rock_1");
    //     obj2.name = "Asteroid" + std::to_string(i);
    //     obj2.tags = {"asteroid"};
    //     obj2.scripts.push_back(std::make_unique<SphereCollider>(3));
    //     obj2.scripts.push_back(std::make_unique<AsteroidScript>());
    //     engine.addObject(std::move(obj2));
    // }

    GameObject moveHandler;
    moveHandler.name = "MoveHandler";
    moveHandler.scripts.push_back(std::make_unique<MoveHandlerScript>());
    engine.addObject(std::move(moveHandler));

    GameObject bulletHandler;
    bulletHandler.name = "BulletHandler";
    bulletHandler.scripts.push_back(std::make_unique<BulletHandlerScript>());
    engine.addObject(std::move(bulletHandler));

    GameObject cockpit;
    cockpit.mesh = Mesh::loadObjFile("cockpit");
    cockpit.name = "Cockpit";
    cockpit.scripts.push_back(std::make_unique<CockpitScript>(Vector3{0, 0, 0}, cockpitColor, LightingMode::Crystal));
    cockpit.transform.scale = {0.775f, 0.775f, 0.775f};
    engine.addObject(std::move(cockpit));

    GameObject computer;
    computer.name = "Computer";
    computer.mesh = Mesh::loadObjFile("comp");
    computer.scripts.push_back(std::make_unique<CockpitScript>(Vector3{0, -0.27, 0.01}, 0x00c0c0, LightingMode::Regular, Vector3{-0.9, 0, 0}));
    computer.transform.scale = {0.5, 0.5, 4};
    engine.addObject(std::move(computer));

    GameObject barrel1;
    barrel1.name = "Barrel1";
    barrel1.mesh = Mesh::loadObjFile("cylinderW");
    barrel1.scripts.push_back(std::make_unique<CockpitScript>(Vector3{0.225, -0.23, -0.22}, barrelColor, LightingMode::Regular, Vector3{1.57, 0, 0}));
    barrel1.transform.scale = {0.11, 0.4, 0.11};
    engine.addObject(std::move(barrel1));

    GameObject barrel2;
    barrel2.name = "Barrel2";
    barrel2.mesh = Mesh::loadObjFile("cylinderW");
    barrel2.scripts.push_back(std::make_unique<CockpitScript>(Vector3{-0.225, -0.23, -0.22}, barrelColor, LightingMode::Regular, Vector3{1.57, 0, 0}));
    barrel2.transform.scale = {0.11, 0.4, 0.11};
    engine.addObject(std::move(barrel2));

    GameObject arrow;
    arrow.name = "Arrow";
    arrow.mesh = Mesh::loadObjFile("arrow");
    arrow.scripts.push_back(std::make_unique<ArrowScript>(Vector3{0, -0.13, 0.05}, 0xaa2222, LightingMode::Regular, Vector3{0, 0, 0}));
    arrow.transform.scale = Vector3{0.05f, 0.15f, 0.05f} * 2.0f;
    arrow.transform.position = {0, 0, -1.5f};
    engine.addObject(std::move(arrow));

    // for (int i = 0; i < 100; i++) {
    //     GameObject cube;
    //     cube.mesh = Mesh::loadObjFile("sphere8");
    //     for (int j = 0; j < cube.mesh.vertices.size(); j++) {
    //         cube.mesh.vertexColors.push_back(0xFFFFFF); // white color
    //     }
    //     cube.name = "Cube" + std::to_string(i);
    //     cube.tags = {"asteroid"};
    //     cube.transform.position = {static_cast<float>(rand() % 20 - 10), static_cast<float>(rand() % 20 - 10), static_cast<float>(rand() % 20 - 10)};
    //     cube.transform.scale = {1, 1, 1};
    //     cube.scripts.push_back(std::make_unique<SphereCollider>(1));
    //     engine.addObject(std::move(cube));
    // }

    GameObject asteroidManager;
    asteroidManager.name = "AsteroidManager";
    asteroidManager.scripts.push_back(std::make_unique<AsteroidManager>());
    engine.addObject(std::move(asteroidManager));

    GameObject playerBody;
    playerBody.name = "PlayerBody";
    playerBody.scripts.push_back(std::make_unique<SphereCollider>(0.1f));
    playerBody.scripts.push_back(std::make_unique<PlayerBodyScript>());
    engine.addObject(std::move(playerBody));

    // GameObject levelCylinder;
    // levelCylinder.mesh = Mesh::loadObjFile("cylinder");
    // levelCylinder.scripts.push_back(std::make_unique<CylinderScript>());
    // levelCylinder.name = "LevelCylinder";
    // levelCylinder.tags = {};
    // engine.addObject(std::move(levelCylinder));

    GameObject crosshair;
    crosshair.name = "Crosshair";
    crosshair.scripts.push_back(std::make_unique<CrosshairScript>());
    engine.addObject(std::move(crosshair));

    GameObject topTitle;
    topTitle.name = "TopTitle";
    topTitle.scripts.push_back(std::make_unique<TitleScript>("terminal2", true));
    engine.addObject(std::move(topTitle));

    GameObject bottomTitle;
    bottomTitle.name = "BottomTitle";
    bottomTitle.scripts.push_back(std::make_unique<TitleScript>("velocity2", false));
    engine.addObject(std::move(bottomTitle));

    GameObject scoreText;
    scoreText.name = "ScoreText";
    scoreText.scripts.push_back(std::make_unique<ScoreText>());
    engine.addObject(std::move(scoreText));

    GameObject gameOverText;
    gameOverText.name = "GameOverText";
    gameOverText.scripts.push_back(std::make_unique<GameOverTextScript>());
    engine.addObject(std::move(gameOverText));

    engine.run(&end);
}
