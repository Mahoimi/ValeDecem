#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <Vertex.h>
#include <vector>
#include <string>
#include <GLTexture.h>

class aiScene;
class aiMesh;

class MeshRenderer {
private:
    struct Mesh {
        Mesh():m_numIndices(0){

        }

        ~Mesh();

        void init(const std::vector<Vertex>& Vertices,
                  const std::vector<unsigned int>& Indices);

        GLuint m_VB;
        GLuint m_IB;
        GLuint m_VAO;
        unsigned int m_numIndices;
        unsigned int m_materialIndex;
    };

    std::vector<Mesh> m_Entries;
    std::vector<GLTexture*> m_Textures;

    void initFromScene(const aiScene* pScene, const std::string& filename);
    void initMesh(unsigned int Index, const aiMesh* paiMesh);
    void initMaterials(const aiScene* pScene, const std::string& filename);

public:
    MeshRenderer(){}
    void load(const std::string& filepath);

    void render() const;
};

#endif // MESH_H
