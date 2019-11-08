#include "Scene.h"

#include "ShaderEyelight.h"
#include "ShaderEyelightTextured.h"
#include "ShaderPhong.h"
#include "PrimTriangle.h"
#include "PrimTriangleSmooth.h"
#include "PrimTriangleSmoothTextured.h"

#include <fstream> 

void CScene::ParseOBJ(const std::string& fileName)
{
	std::ifstream file(fileName);

	if (file.is_open()) {
		std::cout << "Parsing OBJFile : " << fileName << std::endl;

		// std::shared_ptr<IShader> pShader = std::make_shared<CShaderEyelight>(RGB(1, 0.5f, 0));

		// 4.3
		// std::shared_ptr<IShader> pShader = std::make_shared<CShaderEyelightTextured>(RGB(1, 1, 1), "../data/barney.bmp");

		// 4.4
		std::shared_ptr<IShader> pShader = std::make_shared<CShaderEyelightTextured>(RGB(1, 1, 1), "../data/cb.bmp");

		std::vector<Vec3f> vVertexes;
		std::vector<Vec3f> vVertexNormals;
		std::vector<Vec2f> vTextureCoordinates;

		std::string line;

		for (;;) {
			if (!getline(file, line)) break;
			std::stringstream ss(line);
			getline(ss, line, ' ');
			if (line == "v") {
				Vec3f v;
				for (int i = 0; i < 3; i++) ss >> v.val[i];
				// std::cout << "Vertex: " << v << std::endl;
				vVertexes.emplace_back(v);
			}
			else if (line == "f") {
				Vec3i f, vn, vt;

				for (int i = 0; i < 3; i++) {
					getline(ss, line, '/');
					f.val[i] 	= std::stoi(line);
					getline(ss, line, '/');
					vt.val[i]	= std::stoi(line);
					getline(ss, line, ' ');
					vn.val[i] 	= std::stoi(line);
				}

				// std::cout << "Face: " << f << std::endl;
				// Add(std::make_shared<CPrimTriangle>(
				// 	vVertexes[f.val[0] - 1], 
				// 	vVertexes[f.val[1] - 1], 
				// 	vVertexes[f.val[2] - 1], pShader));

				// 4.1

				// Add(std::make_shared<CPrimTriangleSmooth>(
				// 	vVertexes[f.val[0] - 1], 
				// 	vVertexes[f.val[1] - 1], 
				// 	vVertexes[f.val[2] - 1],
				// 	vVertexNormals[vn.val[0] - 1],
				// 	vVertexNormals[vn.val[1] - 1], 
				// 	vVertexNormals[vn.val[2] - 1],
				// 	 pShader));

				Add(std::make_shared<CPrimTriangleSmoothTextured>(
					vVertexes[f.val[0] - 1], 
					vVertexes[f.val[1] - 1], 
					vVertexes[f.val[2] - 1],
					vVertexNormals[vn.val[0] - 1],
					vVertexNormals[vn.val[1] - 1], 
					vVertexNormals[vn.val[2] - 1],
					vTextureCoordinates[vt.val[0] - 1],
					vTextureCoordinates[vt.val[1] - 1],
					vTextureCoordinates[vt.val[2] - 1],
					 pShader));
			}
			else if (line == "vn"){
				Vec3f v;
				for (int i = 0; i < 3; i++) ss >> v.val[i];
				// std::cout << "Vertex normal: " << v << std::endl;
				vVertexNormals.emplace_back(v);
			}
			else if(line == "vt"){
				Vec2f v;
				for (int i = 0; i < 2; i++) ss >> v.val[i];
				// std::cout << "Texture coordinate: " << v << std::endl;
				vTextureCoordinates.emplace_back(v);
			}
			else {
				std::cout << "Unknown key [" << line << "] met in the OBJ file" << std::endl;
			}
		}

		file.close();
		std::cout << "Finished Parsing" << std::endl;
	} else
		std::cout << "ERROR: Can't open OBJFile" << std::endl;
}
