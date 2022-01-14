// OBJ_Loader.h - A Single Header OBJ Model Loader

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iterator>

// Print progress to console while loading (large models)
//#define OBJL_CONSOLE_OUTPUT

// Namespace: OBJL
//
// Description: The namespace that holds eveyrthing that
// is needed and used for the OBJ Model Loader
namespace objl
{
	// Structure: Vector2
	//
	// Description: A 2D Vector that Holds Positional Data

#if defined(_WIN32)
#pragma pack(push)
#pragma pack(1)
#endif

	struct Vector2
	{
		// Positional Variables
		float X;
		float Y;
	};
#if defined(_WIN32)
#pragma pack(pop)
#endif

			// Bool Equals Operator Overload
	inline bool operator==(const Vector2& lhs,const Vector2& rhs)
	{
		return (lhs.X == rhs.X && lhs.Y == rhs.Y);
	}
	// Bool Not Equals Operator Overload
	inline bool operator!=(const Vector2& lhs,const Vector2& rhs)
	{
		return !(lhs == rhs);
	}
	// Addition Operator Overload
	inline Vector2 operator+(const Vector2& lhs,const Vector2& rhs)
	{
		return Vector2{lhs.X + rhs.X, lhs.Y + rhs.Y};
	}
	// Subtraction Operator Overload
	inline Vector2 operator-(const Vector2& lhs,const Vector2& rhs)
	{
		return Vector2{lhs.X - rhs.X, lhs.Y - rhs.Y};
	}
	// Float Multiplication Operator Overload
	inline Vector2 operator*(const Vector2& lhs,const float& rhs)
	{
		return Vector2{lhs.X * rhs, lhs.Y * rhs};
	}

	// Structure: Vector3
	//
	// Description: A 3D Vector that Holds Positional Data
	#if defined(_WIN32)
	#pragma pack(push)
	#pragma pack(1)
	#endif
	struct Vector3
	{
		// Positional Variables
		float X;
		float Y;
		float Z;
	};
	#if defined(_WIN32)
	#pragma pack(pop)
	#endif

	// Bool Equals Operator Overload
	inline bool operator==(const Vector3& lhs,const Vector3& rhs)
	{
		return (lhs.X == rhs.X && lhs.Y == rhs.Y && lhs.Z == rhs.Z);
	}

	// Bool Not Equals Operator Overload
	inline bool operator!=(const Vector3& lhs,const Vector3& rhs)
	{
		return !(lhs == rhs);
	}

	// Addition Operator Overload
	inline Vector3 operator+(const Vector3& lhs,const Vector3& rhs)
	{
		return Vector3{lhs.X + rhs.X, lhs.Y + rhs.Y, lhs.Z + rhs.Z};
	}
	// Subtraction Operator Overload
	inline Vector3 operator-(const Vector3& lhs,const Vector3& rhs)
	{
		return Vector3{lhs.X - rhs.X, lhs.Y - rhs.Y, lhs.Z - rhs.Z};
	}
	// Float Multiplication Operator Overload
	inline Vector3 operator*(const Vector3& lhs,const float& rhs)
	{
		return Vector3{lhs.X * rhs, lhs.Y * rhs, lhs.Z * rhs};
	}
	// Float Division Operator Overload
	inline Vector3 operator/(const Vector3& lhs,const float& rhs)
	{
		return Vector3{lhs.X / rhs, lhs.Y / rhs, lhs.Z / rhs};
	}


	// Structure: Vertex
	//
	// Description: Model Vertex object that holds
	//	a Position, Normal, and Texture Coordinate
	struct Vertex
	{
		// Position Vector
		Vector3 Position{0.0f,0.0f,0.0f};

		// Normal Vector
		Vector3 Normal{0.0f,0.0f,0.0f};

		// Texture Coordinate Vector
		Vector2 TextureCoordinate{0.0f,0.0f};
	};

	struct Material
	{
		// Material Name
		std::string name;
		// Ambient Color
		Vector3 Ka{0.0f,0.0f,0.0f};
		// Diffuse Color
		Vector3 Kd{0.0f,0.0f,0.0f};
		// Specular Color
		Vector3 Ks{0.0f,0.0f,0.0f};
		// Specular Exponent
		float Ns = 0.0f;
		// Optical Density
		float Ni = 0.0f;
		// Dissolve
		float d = 0.0f;
		// Illumination
		int illum = 0;
		// Ambient Texture Map
		std::string map_Ka;
		// Diffuse Texture Map
		std::string map_Kd;
		// Specular Texture Map
		std::string map_Ks;
		// Specular Hightlight Map
		std::string map_Ns;
		// Alpha Texture Map
		std::string map_d;
		// Bump Map
		std::string map_bump;
	};

	// Structure: Mesh
	//
	// Description: A Simple Mesh Object that holds
	//	a name, a vertex list, and an index list
	struct Mesh
	{
		// Default Constructor
		Mesh()= default;
		// Variable Set Constructor
		Mesh(const std::vector<Vertex>& _Vertices, const std::vector<unsigned int>& _Indices)
		{
			Vertices = _Vertices;
			Indices = _Indices;
		}
		// Mesh Name
		std::string MeshName;
		// Vertex List
		std::vector<Vertex> Vertices;
		// Index List
		std::vector<unsigned int> Indices;

		// Material
		Material MeshMaterial;
	};

	// Namespace: Math
	//
	// Description: The namespace that holds all of the math
	//	functions need for OBJL
	namespace math
	{
		// Vector3 Cross Product
		inline Vector3 CrossV3(const Vector3 a, const Vector3 b)
		{
			return Vector3{a.Y * b.Z - a.Z * b.Y,
				a.Z * b.X - a.X * b.Z,
				a.X * b.Y - a.Y * b.X};
		}

		// Vector3 Magnitude Calculation
		inline float MagnitudeV3(const Vector3 in)
		{
			return (sqrtf(powf(in.X, 2) + powf(in.Y, 2) + powf(in.Z, 2)));
		}

		// Vector3 DotProduct
		inline float DotV3(const Vector3 a, const Vector3 b)
		{
			return (a.X * b.X) + (a.Y * b.Y) + (a.Z * b.Z);
		}

		// Angle between 2 Vector3 Objects
		inline float AngleBetweenV3(const Vector3 a, const Vector3 b)
		{
			float angle = DotV3(a, b);
			angle /= (MagnitudeV3(a) * MagnitudeV3(b));
			return angle = acosf(angle);
		}

		// Projection Calculation of a onto b
		inline Vector3 ProjV3(const Vector3 a, const Vector3 b)
		{
			Vector3 bn = b / MagnitudeV3(b);
			return bn * DotV3(a, bn);
		}
	}

	// Namespace: Algorithm
	//
	// Description: The namespace that holds all of the
	// Algorithms needed for OBJL
	namespace algorithm
	{
		// Vector3 Multiplication Opertor Overload
		inline Vector3 operator*(const float& left, const Vector3& right)
		{
			return Vector3{right.X * left, right.Y * left, right.Z * left};
		}

		// A test to see if P1 is on the same side as P2 of a line segment ab
		inline bool SameSide(Vector3 p1, Vector3 p2, Vector3 a, Vector3 b)
		{
			const Vector3 cp1 = math::CrossV3(b - a, p1 - a);
			const Vector3 cp2 = math::CrossV3(b - a, p2 - a);

			return math::DotV3(cp1, cp2) >= 0;
		}

		// Generate a cross produect normal for a triangle
		inline Vector3 GenTriNormal(Vector3 t1, Vector3 t2, Vector3 t3)
		{
			const Vector3 u = t2 - t1;
			const Vector3 v = t3 - t1;

			const Vector3 normal = math::CrossV3(u,v);

			return normal;
		}

		// Check to see if a Vector3 Point is within a 3 Vector3 Triangle
		inline bool inTriangle(Vector3 point, Vector3 tri1, Vector3 tri2, Vector3 tri3)
		{
			// Test to see if it is within an infinite prism that the triangle outlines.
			const bool within_tri_prisim = SameSide(point, tri1, tri2, tri3) && SameSide(point, tri2, tri1, tri3)
				&& SameSide(point, tri3, tri1, tri2);

			// If it isn't it will never be on the triangle
			if (!within_tri_prisim)
				return false;

			// Calulate Triangle's Normal
			const Vector3 n = GenTriNormal(tri1, tri2, tri3);

			// Project the point onto this normal
			const Vector3 proj = math::ProjV3(point, n);

			// If the distance from the triangle to the point is 0
			//	it lies on the triangle
			return math::MagnitudeV3(proj) == 0;
		}

		// Split a String into a string array at a given token
		inline void split(const std::string &in,
			std::vector<std::string> &out,
		                  const std::string& token)
		{
			out.clear();

			std::string temp;

			for (int i = 0; i < int(in.size()); i++)
			{
				const std::string test = in.substr(i, token.size());

				if (test == token)
				{
					if (!temp.empty())
					{
						out.push_back(temp);
						temp.clear();
						i += static_cast<int>(token.size()) - 1;
					}
					else
					{
						out.emplace_back("");
					}
				}
				else if (i + token.size() >= in.size())
				{
					temp += in.substr(i, token.size());
					out.push_back(temp);
					break;
				}
				else
				{
					temp += in[i];
				}
			}
		}

		// Get tail of string after first token and possibly following spaces
		inline std::string tail(const std::string &in)
		{
			const size_t token_start = in.find_first_not_of(" \t");
			const size_t space_start = in.find_first_of(" \t", token_start);
			const size_t tail_start = in.find_first_not_of(" \t", space_start);
			const size_t tail_end = in.find_last_not_of(" \t");
			if (tail_start != std::string::npos && tail_end != std::string::npos)
			{
				return in.substr(tail_start, tail_end - tail_start + 1);
			}
			else if (tail_start != std::string::npos)
			{
				return in.substr(tail_start);
			}
			return "";
		}

		// Get first token of string
		inline std::string firstToken(const std::string &in)
		{
			if (!in.empty())
			{
				const size_t token_start = in.find_first_not_of(" \t");
				const size_t token_end = in.find_first_of(" \t", token_start);
				if (token_start != std::string::npos && token_end != std::string::npos)
				{
					return in.substr(token_start, token_end - token_start);
				}
				else if (token_start != std::string::npos)
				{
					return in.substr(token_start);
				}
			}
			return "";
		}

		// Get element at given index position
		template <class T>
		const T & getElement(const std::vector<T> &elements, std::string &index)
		{
			int idx = std::stoi(index);
			if (idx < 0)
				idx = int(elements.size()) + idx;
			else
				idx--;
			return elements[idx];
		}
	}

	// Class: Loader
	//
	// Description: The OBJ Model Loader
	class Loader
	{
	public:
		// Default Constructor
		Loader() = default;

		Loader(const std::string&& filePath)
		{
			load(filePath);
		}

		Loader(const std::string& filePath)
		{
			load(filePath);
		}

		~Loader()
		{
			LoadedMeshes.clear();
		}

		// Load a file into the loader
		//
		// If file is loaded return true
		//
		// If the file is unable to be found
		// or unable to be loaded return false
		bool load(const std::string& filePath)
		{
			// If the file is not an .obj file return false

			std::ifstream stream(reinterpret_cast<const char*>(filePath.data()));

			LoadedMeshes.clear();
			LoadedVertices.clear();
			LoadedIndices.clear();

			std::vector<Vector3> positions;
			std::vector<Vector2> t_coords;
			std::vector<Vector3> normals;

			std::vector<Vertex> vertices;
			std::vector<unsigned int> indices;

			std::vector<std::string> mesh_mat_names;

			bool listening = false;
			std::string meshname;

			Mesh temp_mesh;

			#ifdef OBJL_CONSOLE_OUTPUT
			const unsigned int outputEveryNth = 1000;
			unsigned int outputIndicator = outputEveryNth;
			#endif

			std::string curline;
			while (std::getline(stream, curline))
			{
				#ifdef OBJL_CONSOLE_OUTPUT
				if ((outputIndicator = ((outputIndicator + 1) % outputEveryNth)) == 1)
				{
					if (!meshname.empty())
					{
						std::cout
							<< "\r- " << meshname
							<< "\t| vertices > " << positions.size()
							<< "\t| texcoords > " << t_coords.size()
							<< "\t| normals > " << normals.size()
							<< "\t| triangles > " << (vertices.size() / 3)
							<< (!mesh_mat_names.empty() ? "\t| material: " + mesh_mat_names.back() : "");
					}
				}
				#endif

				// Generate a Mesh Object or Prepare for an object to be created
				if (algorithm::firstToken(curline) == "o" || algorithm::firstToken(curline) == "g" || curline[0] == 'g')
				{
					if (!listening)
					{
						listening = true;

						if (algorithm::firstToken(curline) == "o" || algorithm::firstToken(curline) == "g")
						{
							meshname = algorithm::tail(curline);
						}
						else
						{
							meshname = "unnamed";
						}
					}
					else
					{
						// Generate the mesh to put into the array

						if (!indices.empty() && !vertices.empty())
						{
							// Create Mesh
							temp_mesh = Mesh(vertices, indices);
							temp_mesh.MeshName = meshname;

							// Insert Mesh
							LoadedMeshes.push_back(temp_mesh);

							// Cleanup
							vertices.clear();
							indices.clear();
							meshname.clear();

							meshname = algorithm::tail(curline);
						}
						else
						{
							if (algorithm::firstToken(curline) == "o" || algorithm::firstToken(curline) == "g")
							{
								meshname = algorithm::tail(curline);
							}
							else
							{
								meshname = "unnamed";
							}
						}
					}
					#ifdef OBJL_CONSOLE_OUTPUT
					std::cout << std::endl;
					outputIndicator = 0;
					#endif
				}
				// Generate a Vertex Position
				if (algorithm::firstToken(curline) == "v")
				{
					std::vector<std::string> spos;
					Vector3 vpos{};
					algorithm::split(algorithm::tail(curline), spos, " ");

					vpos.X = std::stof(spos[0]);
					vpos.Y = std::stof(spos[1]);
					vpos.Z = std::stof(spos[2]);

					positions.push_back(vpos);
				}
				// Generate a Vertex Texture Coordinate
				if (algorithm::firstToken(curline) == "vt")
				{
					std::vector<std::string> stex;
					Vector2 vtex;
					algorithm::split(algorithm::tail(curline), stex, " ");

					vtex.X = std::stof(stex[0]);
					vtex.Y = std::stof(stex[1]);

					t_coords.push_back(vtex);
				}
				// Generate a Vertex Normal;
				if (algorithm::firstToken(curline) == "vn")
				{
					std::vector<std::string> snor;
					Vector3 vnor{};
					algorithm::split(algorithm::tail(curline), snor, " ");

					vnor.X = std::stof(snor[0]);
					vnor.Y = std::stof(snor[1]);
					vnor.Z = std::stof(snor[2]);

					normals.push_back(vnor);
				}
				// Generate a Face (vertices & indices)
				if (algorithm::firstToken(curline) == "f")
				{
					// Generate the vertices
					std::vector<Vertex> v_verts;
					GenVerticesFromRawOBJ(v_verts, positions, t_coords, normals, curline);

					// Add Vertices
					for (const auto& v_vert : v_verts)
					{
						vertices.push_back(v_vert);

						LoadedVertices.push_back(v_vert);
					}

					std::vector<unsigned int> i_indices;

					VertexTriangluation(i_indices, v_verts);

					// Add Indices
					for (unsigned int i_index : i_indices)
					{
						unsigned int indnum = static_cast<unsigned int>((vertices.size()) - v_verts.size()) + i_index;
						indices.push_back(indnum);

						indnum = static_cast<unsigned int>((LoadedVertices.size()) - v_verts.size()) + i_index;
						LoadedIndices.push_back(indnum);

					}
				}
				// Get Mesh Material Name
				if (algorithm::firstToken(curline) == "usemtl")
				{
					mesh_mat_names.push_back(algorithm::tail(curline));

					// Create new Mesh, if Material changes within a group
					if (!indices.empty() && !vertices.empty())
					{
						// Create Mesh
						temp_mesh = Mesh(vertices, indices);
						temp_mesh.MeshName = meshname;
						const int i = 2;
						while(true) {
							temp_mesh.MeshName = meshname + "_" + std::to_string(i);

							for (auto &m : LoadedMeshes)
								if (m.MeshName == temp_mesh.MeshName)
									continue;
							break;
						}

						// Insert Mesh
						LoadedMeshes.push_back(temp_mesh);

						// Cleanup
						vertices.clear();
						indices.clear();
					}

					#ifdef OBJL_CONSOLE_OUTPUT
					outputIndicator = 0;
					#endif
				}
				// Load Materials
				if (algorithm::firstToken(curline) == "mtllib")
				{
					// Generate LoadedMaterial

					// Generate a path to the material file
					const std::string pathtomat = algorithm::tail(curline);

					#ifdef OBJL_CONSOLE_OUTPUT
					std::cout << std::endl << "- find materials in: " << pathtomat << std::endl;
					#endif

					//open the file
					std::ifstream file(pathtomat, std::ios::binary);
					std::vector<uint8_t> material_data;
					//disable eating newlines
					file.unsetf(std::ios::skipws);

					if(file.good()){

						file.seekg(0, std::ios::end);
						const std::streampos file_size = file.tellg();
						file.seekg(0, std::ios::beg);

						//reserve capacity
						material_data.reserve(file_size);

						//read data
						material_data.insert(material_data.begin(),
							std::istream_iterator<uint8_t>(file),
							std::istream_iterator<uint8_t>());
					}

					// Load Materials
					LoadMaterials(material_data);
				}
			}

			#ifdef OBJL_CONSOLE_OUTPUT
			std::cout << std::endl;
			#endif

			// Deal with last mesh

			if (!indices.empty() && !vertices.empty())
			{
				// Create Mesh
				temp_mesh = Mesh(vertices, indices);
				temp_mesh.MeshName = meshname;

				// Insert Mesh
				LoadedMeshes.push_back(temp_mesh);
			}


			// Set Materials for each Mesh
			for (size_t i = 0; i < mesh_mat_names.size(); i++)
			{
				const std::string matname = mesh_mat_names[i];

				// Find corresponding material name in loaded materials
				// when found copy material variables into mesh material
				for (auto& LoadedMaterial : LoadedMaterials)
				{
					if (LoadedMaterial.name == matname)
					{
						LoadedMeshes[i].MeshMaterial = LoadedMaterial;
						break;
					}
				}
			}

			return !(LoadedMeshes.empty() && LoadedVertices.empty() && LoadedIndices.empty());
		}

		// Loaded Mesh Objects
		std::vector<Mesh> LoadedMeshes;
		// Loaded Vertex Objects
		std::vector<Vertex> LoadedVertices;
		// Loaded Index Positions
		std::vector<unsigned int> LoadedIndices;
		// Loaded Material Objects
		std::vector<Material> LoadedMaterials;

	private:
		// Generate vertices from a list of positions,
		//	tcoords, normals and a face line
		static void GenVerticesFromRawOBJ(std::vector<Vertex>& o_verts,
										  const std::vector<Vector3>& i_positions,
										  const std::vector<Vector2>& i_t_coords,
										  const std::vector<Vector3>& i_normals,
		                                  const std::string& icurline)
		{
			std::vector<std::string> sface, svert;
			Vertex vVert;
			algorithm::split(algorithm::tail(icurline), sface, " ");

			bool noNormal = false;

			// For every given vertex do this
			for (const auto& face : sface)
			{
				// See What type the vertex is.
				int vtype = 0;

				algorithm::split(face, svert, "/");

				// Check for just position - v1
				if (svert.size() == 1)
				{
					// Only position
					vtype = 1;
				}

				// Check for position & texture - v1/vt1
				if (svert.size() == 2)
				{
					// Position & Texture
					vtype = 2;
				}

				// Check for Position, Texture and Normal - v1/vt1/vn1
				// or if Position and Normal - v1//vn1
				if (svert.size() == 3)
				{
					if (svert[1] != "")
					{
						// Position, Texture, and Normal
						vtype = 4;
					}
					else
					{
						// Position & Normal
						vtype = 3;
					}
				}

				// Calculate and store the vertex
				switch (vtype)
				{
				case 1: // P
				{
					vVert.Position = algorithm::getElement(i_positions, svert[0]);
					vVert.TextureCoordinate = Vector2{0.0f,0.0f};
					noNormal = true;
					o_verts.push_back(vVert);
					break;
				}
				case 2: // P/T
				{
					vVert.Position = algorithm::getElement(i_positions, svert[0]);
					vVert.TextureCoordinate = algorithm::getElement(i_t_coords, svert[1]);
					noNormal = true;
					o_verts.push_back(vVert);
					break;
				}
				case 3: // P//N
				{
					vVert.Position = algorithm::getElement(i_positions, svert[0]);
					vVert.TextureCoordinate = Vector2{0.0f,0.0f};
					vVert.Normal = algorithm::getElement(i_normals, svert[2]);
					o_verts.push_back(vVert);
					break;
				}
				case 4: // P/T/N
				{
					vVert.Position = algorithm::getElement(i_positions, svert[0]);
					vVert.TextureCoordinate = algorithm::getElement(i_t_coords, svert[1]);
					vVert.Normal = algorithm::getElement(i_normals, svert[2]);
					o_verts.push_back(vVert);
					break;
				}
				default:
				{
					break;
				}
				}
			}

			// take care of missing normals
			// these may not be truly acurate but it is the
			// best they get for not compiling a mesh with normals
			if (noNormal)
			{
				const Vector3 A = o_verts[0].Position - o_verts[1].Position;
				const Vector3 B = o_verts[2].Position - o_verts[1].Position;

				const Vector3 normal = math::CrossV3(A, B);

				for (auto& o_vert : o_verts)
				{
					o_vert.Normal = normal;
				}
			}
		}

		// Triangulate a list of vertices into a face by printing
		//	inducies corresponding with triangles within it
		static void VertexTriangluation(std::vector<unsigned int>& o_indices,
										const std::vector<Vertex>& i_verts)
		{
			// If there are 2 or less verts,
			// no triangle can be created,
			// so exit
			if (i_verts.size() < 3)
			{
				return;
			}
			// If it is a triangle no need to calculate it
			if (i_verts.size() == 3)
			{
				o_indices.push_back(0);
				o_indices.push_back(1);
				o_indices.push_back(2);
				return;
			}

			// Create a list of vertices
			auto t_verts = i_verts;

			while (true)
			{
				// For every vertex
				for (size_t i = 0; i < t_verts.size(); i++)
				{
					// pPrev = the previous vertex in the list
					Vertex pPrev;
					if (i == 0)
					{
						pPrev = t_verts[t_verts.size() - 1];
					}
					else
					{
						pPrev = t_verts[i - 1];
					}

					// pCur = the current vertex;
					const Vertex pCur = t_verts[i];

					// pNext = the next vertex in the list
					Vertex p_next;
					if (t_verts.size() - 1 == i)
					{
						p_next = t_verts[0];
					}
					else
					{
						p_next = t_verts[i + 1];
					}

					// Check to see if there are only 3 verts left
					// if so this is the last triangle
					if (t_verts.size() == 3)
					{
						// Create a triangle from pCur, pPrev, pNext
						for (int j = 0; j < int(t_verts.size()); j++)
						{
							if (i_verts[j].Position == pCur.Position)
								o_indices.push_back(j);
							if (i_verts[j].Position == pPrev.Position)
								o_indices.push_back(j);
							if (i_verts[j].Position == p_next.Position)
								o_indices.push_back(j);
						}

						t_verts.clear();
						break;
					}
					if (t_verts.size() == 4)
					{
						// Create a triangle from pCur, pPrev, pNext
						for (int j = 0; j < int(i_verts.size()); j++)
						{
							if (i_verts[j].Position == pCur.Position)
								o_indices.push_back(j);
							if (i_verts[j].Position == pPrev.Position)
								o_indices.push_back(j);
							if (i_verts[j].Position == p_next.Position)
								o_indices.push_back(j);
						}

						Vector3 temp_vec{};
						for (auto& t_vert : t_verts)
						{
							if (t_vert.Position != pCur.Position
								&& t_vert.Position != pPrev.Position
								&& t_vert.Position != p_next.Position)
							{
								temp_vec = t_vert.Position;
								break;
							}
						}

						// Create a triangle from pCur, pPrev, pNext
						for (int j = 0; j < int(i_verts.size()); j++)
						{
							if (i_verts[j].Position == pPrev.Position)
								o_indices.push_back(j);
							if (i_verts[j].Position == p_next.Position)
								o_indices.push_back(j);
							if (i_verts[j].Position == temp_vec)
								o_indices.push_back(j);
						}

						t_verts.clear();
						break;
					}

					// If Vertex is not an interior vertex
					const float angle = math::AngleBetweenV3(pPrev.Position - pCur.Position, p_next.Position - pCur.Position) * (180.0f / 3.14159265359f);
					if (angle <= 0 && angle >= 180)
						continue;

					// If any vertices are within this triangle
					bool in_tri = false;
					for (const auto& i_vert : i_verts)
					{
						if (algorithm::inTriangle(i_vert.Position, pPrev.Position, pCur.Position, p_next.Position)
							&& i_vert.Position != pPrev.Position
							&& i_vert.Position != pCur.Position
							&& i_vert.Position != p_next.Position)
						{
							in_tri = true;
							break;
						}
					}
					if (in_tri)
						continue;

					// Create a triangle from pCur, pPrev, pNext
					for (int j = 0; j < int(i_verts.size()); j++)
					{
						if (i_verts[j].Position == pCur.Position)
							o_indices.push_back(j);
						if (i_verts[j].Position == pPrev.Position)
							o_indices.push_back(j);
						if (i_verts[j].Position == p_next.Position)
							o_indices.push_back(j);
					}

					// Delete pCur from the list
					for (int j = 0; j < int(t_verts.size()); j++)
					{
						if (t_verts[j].Position == pCur.Position)
						{
							t_verts.erase(t_verts.begin() + j);
							break;
						}
					}

					// reset i to the start
					// -1 since loop will add 1 to it
					i = -1;
				}

				// if no triangles were created
				if (o_indices.empty())
					break;

				// if no more vertices
				if (t_verts.empty())
					break;
			}
		}

		// Load Materials from .mtl file
		bool LoadMaterials(std::vector<uint8_t> data)
		{
			if(data.empty()) return false;
			std::stringstream stream(reinterpret_cast<const char*>(data.data()));

			Material tempMaterial;

			bool listening = false;

			// Go through each line looking for material variables
			std::string curline;
			while (std::getline(stream, curline))
			{
				// new material and material name
				if (algorithm::firstToken(curline) == "newmtl")
				{
					if (!listening)
					{
						listening = true;

						if (curline.size() > 7)
						{
							tempMaterial.name = algorithm::tail(curline);
						}
						else
						{
							tempMaterial.name = "none";
						}
					}
					else
					{
						// Generate the material

						// Push Back loaded Material
						LoadedMaterials.push_back(tempMaterial);

						// Clear Loaded Material
						tempMaterial = Material();

						if (curline.size() > 7)
						{
							tempMaterial.name = algorithm::tail(curline);
						}
						else
						{
							tempMaterial.name = "none";
						}
					}
				}
				// Ambient Color
				if (algorithm::firstToken(curline) == "Ka")
				{
					std::vector<std::string> temp;
					algorithm::split(algorithm::tail(curline), temp, " ");

					if (temp.size() != 3)
						continue;

					tempMaterial.Ka.X = std::stof(temp[0]);
					tempMaterial.Ka.Y = std::stof(temp[1]);
					tempMaterial.Ka.Z = std::stof(temp[2]);
				}
				// Diffuse Color
				if (algorithm::firstToken(curline) == "Kd")
				{
					std::vector<std::string> temp;
					algorithm::split(algorithm::tail(curline), temp, " ");

					if (temp.size() != 3)
						continue;

					tempMaterial.Kd.X = std::stof(temp[0]);
					tempMaterial.Kd.Y = std::stof(temp[1]);
					tempMaterial.Kd.Z = std::stof(temp[2]);
				}
				// Specular Color
				if (algorithm::firstToken(curline) == "Ks")
				{
					std::vector<std::string> temp;
					algorithm::split(algorithm::tail(curline), temp, " ");

					if (temp.size() != 3)
						continue;

					tempMaterial.Ks.X = std::stof(temp[0]);
					tempMaterial.Ks.Y = std::stof(temp[1]);
					tempMaterial.Ks.Z = std::stof(temp[2]);
				}
				// Specular Exponent
				if (algorithm::firstToken(curline) == "Ns")
				{
					tempMaterial.Ns = std::stof(algorithm::tail(curline));
				}
				// Optical Density
				if (algorithm::firstToken(curline) == "Ni")
				{
					tempMaterial.Ni = std::stof(algorithm::tail(curline));
				}
				// Dissolve
				if (algorithm::firstToken(curline) == "d")
				{
					tempMaterial.d = std::stof(algorithm::tail(curline));
				}
				// Illumination
				if (algorithm::firstToken(curline) == "illum")
				{
					tempMaterial.illum = std::stoi(algorithm::tail(curline));
				}
				// Ambient Texture Map
				if (algorithm::firstToken(curline) == "map_Ka")
				{
					tempMaterial.map_Ka = algorithm::tail(curline);
				}
				// Diffuse Texture Map
				if (algorithm::firstToken(curline) == "map_Kd")
				{
					tempMaterial.map_Kd = algorithm::tail(curline);
				}
				// Specular Texture Map
				if (algorithm::firstToken(curline) == "map_Ks")
				{
					tempMaterial.map_Ks = algorithm::tail(curline);
				}
				// Specular Hightlight Map
				if (algorithm::firstToken(curline) == "map_Ns")
				{
					tempMaterial.map_Ns = algorithm::tail(curline);
				}
				// Alpha Texture Map
				if (algorithm::firstToken(curline) == "map_d")
				{
					tempMaterial.map_d = algorithm::tail(curline);
				}
				// Bump Map
				if (algorithm::firstToken(curline) == "map_Bump" || algorithm::firstToken(curline) == "map_bump" || algorithm::firstToken(curline) == "bump")
				{
					tempMaterial.map_bump = algorithm::tail(curline);
				}
			}

			// Deal with last material

			// Push Back loaded Material
			LoadedMaterials.push_back(tempMaterial);

			// Test to see if anything was loaded
			// If not return false
			return ! LoadedMaterials.empty();
		}
	};
}
