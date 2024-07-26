#include "Sphere.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#ifdef SPHERE1
void Sphere::init(glm::vec3 position) {
    m_sphereShader.create("Shaders/vstSphere.glsl", "Shaders/fstSphere.glsl");
    m_model = glm::mat4(1);
    m_model = glm::translate(m_model, position);
    std::vector<SphereVertex> vertices;
    std::vector<uint32_t> indices;
    int sectorCount = 36, stackCount = 18;
    float radius = 1.0f;
    const float PI = 3.14159265358979323846f;
    float x, y, z, xy;                           // позиция на сфере
    float nx, ny, nz, lengthInv = 1.0f / radius; // нормаль
    float s, t;                                  // текстурные координаты

    float sectorStep = 2.0f * PI / sectorCount;
    float stackStep = PI / stackCount;
    float sectorAngle, stackAngle;

    for (int i = 0; i <= stackCount; ++i) {
        stackAngle = PI / 2.0f - i * stackStep; // от pi/2 до -pi/2
        xy = radius * cosf(stackAngle);         // r * cos(u)
        z = radius * sinf(stackAngle);          // r * sin(u)

        for (int j = 0; j <= sectorCount; ++j) {
            sectorAngle = j * sectorStep; // от 0 до 2pi

            x = xy * cosf(sectorAngle); // r * cos(u) * cos(v)
            y = xy * sinf(sectorAngle); // r * cos(u) * sin(v)
            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;

            s = (float)j / sectorCount;
            t = (float)i / stackCount;

            vertices.emplace_back(x, y, z, s, t, nx, ny, nz);
        }
    }

    int k1, k2;
    for (int i = 0; i < stackCount; ++i) {
        k1 = i * (sectorCount + 1);
        k2 = k1 + sectorCount + 1;
        for (int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
            if (i != 0) {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }
            if (i != (stackCount - 1)) {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }
    LOG_INFO("Vertex size: {}, Index size: {}", vertices.size(), indices.size());
    VertexBufferLayout layout;
    layout.pushVec3F();
    layout.pushVec2F();
    layout.pushVec3F();
    m_mesh.create(
        layout,
        (float *)vertices.data(),
        vertices.size() * sizeof(SphereVertex),
        indices.data(),
        indices.size()
    );
    std::ostringstream message;
//    for (int i = 0; i < ; ++i) {
//
//    }
}
#else

void Sphere::init() {
    m_sphereShader.create("Shaders/vstSphere.glsl", "Shaders/fstSphere.glsl");
    m_model = glm::mat4(1);

    m_lats = 40;
    m_longs = 40;

    std::vector<SphereVertex> vertices;
    std::vector<uint32_t> indices;
    int indicator = 0;
    for (int i = 0; i <= m_lats; i++) {
        double lat0 = glm::pi<double>() * (-0.5 + (double)(i - 1) / m_lats);
        double z0 = sin(lat0);
        double zr0 = cos(lat0);

        double lat1 = glm::pi<double>() * (-0.5 + (double)i / m_lats);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);

        for (int j = 0; j <= m_longs; j++) {
            double lng = 2 * glm::pi<double>() * (double)(j - 1) / m_longs;
            double x = cos(lng);
            double y = sin(lng);

            vertices.emplace_back(x * zr0, y * zr0, z0);
            indices.push_back(indicator);
            indicator++;

            vertices.emplace_back(x * zr1, y * zr1, z1);
            indices.push_back(indicator);
            indicator++;
        }
    }
    VertexBufferLayout layout;
    layout.pushVec3F();
    m_mesh.create(
        layout,
        (float *)vertices.data(),
        vertices.size() * sizeof(SphereVertex),
        indices.data(),
        indices.size()
    );
}
#endif

void Sphere::draw() {
    auto camera = Application::getInstance()->getCamera();
    m_sphereShader.use();
    m_sphereShader.setFloat("iTime", Application::getInstance()->getWindow()->getTime());
    m_sphereShader.setVec2("iMouse", Events::getCursorPos());
    m_sphereShader.setVec2("iResolution", Application::getInstance()->getWindow()->getSize());
    m_sphereShader.setMat4("u_model", m_model);
    m_sphereShader.setMat4("u_view", camera->getViewMatrix());
    m_sphereShader.setMat4("u_projection", camera->getProjectionMatrix());
    m_sphereShader.setVec3("cameraPos", camera->getPosition());
    m_mesh.draw();
}