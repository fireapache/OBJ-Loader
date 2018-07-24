// Example 1: Load and Print
//
// Load the data from the .obj then print it into a file
//	called e1Out.txt

// Iostream - STD I/O Library
#include <iostream>

// fStream - STD File I/O Library
#include <fstream>

// OBJ_Loader - .obj Loader
#include "obj_parse.h"
#include <conio.h>

// Main function
int main(int argc, char* argv[])
{
	// Initialize Loader
	objl::Loader Loader;

		//open the file
	std::ifstream file("box_stack.obj", std::ios::binary);

	//disable eating newlines
	file.unsetf(std::ios::skipws);

	file.seekg(0, std::ios::end);
	const std::streampos file_size = file.tellg();
	file.seekg(0, std::ios::beg);

	//reserve capacity
	std::vector<uint8_t> vec;
	vec.reserve(file_size);

	//read data
	vec.insert(vec.begin(),
		std::istream_iterator<uint8_t>(file),
		std::istream_iterator<uint8_t>());

	// Load .obj File
	const bool loadout = Loader.load(vec);

	// Check to see if it loaded

	// If so continue
	if (loadout)
	{
		// Create/Open e1Out.txt
		std::ofstream log("e1Out.txt");

		// Go through each loaded mesh and out its contents
		for (size_t i = 0; i < Loader.LoadedMeshes.size(); i++)
		{
			// Copy one of the loaded meshes to be our current mesh
			objl::Mesh curMesh = Loader.LoadedMeshes[i];

			// Print Mesh Name
			log << "Mesh " << i << ": " << curMesh.MeshName << "\n";

			// Print Vertices
			log << "Vertices:\n";

			// Go through each vertex and print its number,
			//  position, normal, and texture coordinate
			for (size_t j = 0; j < curMesh.Vertices.size(); j++)
			{
				log << "V" << j << ": " <<
					"P(" << curMesh.Vertices[j].Position.X << ", " << curMesh.Vertices[j].Position.Y << ", " << curMesh.Vertices[j].Position.Z << ") " <<
					"N(" << curMesh.Vertices[j].Normal.X << ", " << curMesh.Vertices[j].Normal.Y << ", " << curMesh.Vertices[j].Normal.Z << ") " <<
					"TC(" << curMesh.Vertices[j].TextureCoordinate.X << ", " << curMesh.Vertices[j].TextureCoordinate.Y << ")\n";
			}

			// Print Indices
			log << "Indices:\n";

			// Go through every 3rd index and print the
			//	triangle that these indices represent
			for (size_t j = 0; j < curMesh.Indices.size(); j += 3)
			{
				log << "T" << j / 3 << ": " << curMesh.Indices[j] << ", " << curMesh.Indices[j + 1] << ", " << curMesh.Indices[j + 2] << "\n";
			}

			// Print Material
			log << "Material: " << curMesh.MeshMaterial.name << "\n";
			log << "Ambient Color: " << curMesh.MeshMaterial.Ka.X << ", " << curMesh.MeshMaterial.Ka.Y << ", " << curMesh.MeshMaterial.Ka.Z << "\n";
			log << "Diffuse Color: " << curMesh.MeshMaterial.Kd.X << ", " << curMesh.MeshMaterial.Kd.Y << ", " << curMesh.MeshMaterial.Kd.Z << "\n";
			log << "Specular Color: " << curMesh.MeshMaterial.Ks.X << ", " << curMesh.MeshMaterial.Ks.Y << ", " << curMesh.MeshMaterial.Ks.Z << "\n";
			log << "Specular Exponent: " << curMesh.MeshMaterial.Ns << "\n";
			log << "Optical Density: " << curMesh.MeshMaterial.Ni << "\n";
			log << "Dissolve: " << curMesh.MeshMaterial.d << "\n";
			log << "Illumination: " << curMesh.MeshMaterial.illum << "\n";
			log << "Ambient Texture Map: " << curMesh.MeshMaterial.map_Ka << "\n";
			log << "Diffuse Texture Map: " << curMesh.MeshMaterial.map_Kd << "\n";
			log << "Specular Texture Map: " << curMesh.MeshMaterial.map_Ks << "\n";
			log << "Alpha Texture Map: " << curMesh.MeshMaterial.map_d << "\n";
			log << "Bump Map: " << curMesh.MeshMaterial.map_bump << "\n";

			// Leave a space to separate from the next mesh
			log << "\n";
		}

		// Close File
		log.close();
	}
	// If not output an error
	else
	{
		// Create/Open e1Out.txt
		std::ofstream log("e1Out.txt");

		// Output Error
		log << "Failed to Load File. May have failed to find it or it was not an .obj file.\n";

		// Close File
		log.close();
	}

	_getch();

	// Exit the program
	return 0;
}