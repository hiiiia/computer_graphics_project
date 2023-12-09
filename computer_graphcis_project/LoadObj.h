#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;

class ObjInfo_f4 {
public:

    string name;
    vector < vec3 > vertices;
    vector < ivec4 > faces_vertices;
    vector < ivec4 > faces_uvs;
    vector < ivec4 > faces_normals;
    vector < vec2 > uvs;
    vector < vec3 > normals;
};

class LoadObj4 {
public:
    vector < ObjInfo_f4 > objInfo;

    int objCount_f4 = -1;

    bool Load(const char* path)
    {
        ifstream file(path); // 파일을 읽기 모드로 엽니다.
        if (!file.is_open()) {
            std::cerr << "파일 열기 실패" << std::endl;
            return false;
        }

        string line;
        
        bool isFace = false;
        vector<string> faces;
        vector<int> faces_vertexIndexs;
        vector<int> faces_uvIndexs;
        vector<int> faces_normalIndexs;

        while (std::getline(file, line)) {
            vector<string> tokens;
            istringstream iss(line);
            string token;
            while (iss >> token) {
                tokens.push_back(token);
            }

            if (tokens.size() == 0) { continue; }

            if (tokens[0] == "o") {

                ObjInfo_f4 newObjInfo;

                newObjInfo.name = tokens[1];

                objInfo.push_back(newObjInfo);
                objCount_f4++;



                if (faces.size() == 0) continue;
                else
                {
                    /*cout << " 면 개수 : " << faces.size() << endl;
                    for (int i = 0; i < faces.size(); i+=4) {
                        cout << " 면 정보 : " << faces[i] << " " << faces[i + 1] << " " << faces[i+2] << " " << faces[i + 3] << " " << endl;
                    }*/

                    for (int i = 0; i < faces.size(); i++) {

                        istringstream ss1(faces[i]);

                        string buffer;

                        vector<int> values;

                        while (getline(ss1, buffer, '/')) {
                            if (!buffer.empty()) { 
                                values.push_back(stoi(buffer));
                            }
                            
                        }

                        if (values.size() == 2) {
                            faces_vertexIndexs.push_back(values[0]);
                            faces_normalIndexs.push_back(values[1]);
                        }

                        if (values.size() == 3) {
                            faces_vertexIndexs.push_back(values[0]);
                            faces_uvIndexs.push_back(values[1]);
                            faces_normalIndexs.push_back(values[2]);
                        }
                    }
                    
                    /*for (int i = 0; i < faces_vertexIndexs.size(); i += 4) {
                        objInfo_f4[i].faces_vertices.push_back(ivec4(faces_vertexIndexs[i], faces_vertexIndexs[i + 1], faces_vertexIndexs[i + 2], faces_vertexIndexs[i + 3]));
                    }

                    for (int i = 0; i < faces_uvIndexs.size(); i += 4) {
                        objInfo_f4[i].faces_uvs.push_back(ivec4(faces_uvIndexs[i], faces_uvIndexs[i + 1] , faces_uvIndexs[i + 2], faces_uvIndexs[i + 3]));
                    }

                    for (int i = 0; i < faces_normalIndexs.size(); i += 4) {
                        objInfo_f4[i].faces_normals.push_back(ivec4(faces_normalIndexs[i], faces_normalIndexs[i + 1], faces_normalIndexs[i + 2], faces_normalIndexs[i + 3]));
                    }*/

                    faces.clear();
                    faces_vertexIndexs.clear();
                    faces_uvIndexs.clear();
                    faces_normalIndexs.clear();
                    isFace = false;
                    
                }
                
            }
            else if (tokens[0] == "v") {
                vec3 vertex;

                vertex.x = stof(tokens[1]);
                vertex.y = stof(tokens[2]);
                vertex.z = stof(tokens[3]);

                objInfo[objCount_f4].vertices.push_back(vertex);
                
            }
            else if (tokens[0] == "vn") {
                vec3 normal;

                normal.x = stof(tokens[1]);
                normal.y = stof(tokens[2]);
                normal.z = stof(tokens[3]);

                objInfo[objCount_f4].normals.push_back(normal);
            }
            else if (tokens[0] == "vt") {
                vec2 uv;

                uv.x = stof(tokens[1]);
                uv.y = stof(tokens[2]);

                objInfo[objCount_f4].uvs.push_back(uv);
            }
            else if (tokens[0] == "f") {
                isFace = true;
            }

            if (isFace) {



                for (int i = 0; i < tokens.size(); i++) 
                {
                    if (tokens[i] == "f") { continue; }
                    else 
                    {
                        faces.push_back(tokens[i]);
                    }

                }

            }

        }

        if (faces.size() == 0) {}
        else
        {
            cout << " 면 개수 : " << faces.size() << endl;
            for (int i = 0; i < faces.size(); i += 4) {
                cout << " 면 정보 : " << faces[i] << " " << faces[i + 1] << " " << faces[i + 2] << " " << faces[i + 3] << " " << endl;
            }

            faces.clear();
            faces_vertexIndexs.clear();
            faces_uvIndexs.clear();
            faces_normalIndexs.clear();
            isFace = false;

        }

        file.close();

        //FILE* file = fopen(path, "r");
        //if (file == NULL) {
        //    printf("Impossible to open the file !\n");
        //    return false;
        //}
        //
        //

        //while (1) {
        //    char lineHeader[128];
        //    // read the first word of the line
        //    int res = fscanf(file, "%s", lineHeader);
        //    if (res == -1)
        //        break;

        //    //cout << lineHeader << endl;

        //    if (strcmp(lineHeader, "o") == 0) {
        //        // make ObjInfo
        //        ObjInfo newObjInfo;

        //        //insert name
        //        char _name[128];
        //        int mat = fscanf(file, "%s\n", &_name);
        //        /*cout << "오브젝트 이름 매칭 수 " << mat << endl;
        //        cout <<"오브젝트 이름 : " << _name << endl;*/
        //        newObjInfo.name = _name; 

        //        //push_back newObjInfo
        //        objInfo.push_back(newObjInfo);
        //        objCount++;
        //    }
        //    else if (strcmp(lineHeader, "v") == 0) {
        //        vec3 vertex;
        //        fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
        //        objInfo[objCount].vertices.push_back(vertex);
        //    }
        //    else if (strcmp(lineHeader, "vt") == 0) {
        //        vec2 uv;
        //        fscanf(file, "%f %f\n", &uv.x, &uv.y);
        //        objInfo[objCount].uvs.push_back(uv);
        //    }
        //    else if (strcmp(lineHeader, "vn") == 0) {
        //        vec3 normal;
        //        fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
        //        objInfo[objCount].normals.push_back(normal);
        //    }
        //    else if (strcmp(lineHeader, "f") == 0) {
        //        unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
        //        
        //        int matches = fscanf(file, "%d//%d %d//%d %d//%d",
        //            &vertexIndex[0],  &normalIndex[0],
        //            &vertexIndex[1],  &normalIndex[1],
        //            &vertexIndex[2],  &normalIndex[2]);
        //        if (matches == 6) {
        //            objInfo[objCount].faces_vertices.push_back(ivec3(vertexIndex[0] - 1, vertexIndex[1] - 1, vertexIndex[2] - 1));
        //            objInfo[objCount].faces_normals.push_back(ivec3(normalIndex[0] - 1, normalIndex[1] - 1, normalIndex[2] - 1));
        //            continue;
        //        }
        //        else {
        //            int matches2 = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d",
        //                &vertexIndex[0], &uvIndex[0], &normalIndex[0],
        //                &vertexIndex[1], &uvIndex[1], &normalIndex[1],
        //                &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
        //            objInfo[objCount].faces_vertices.push_back(ivec3(vertexIndex[0] - 1, vertexIndex[1] - 1, vertexIndex[2] - 1));
        //            objInfo[objCount].faces_uvs.push_back(ivec3(uvIndex[0] - 1, uvIndex[1] - 1, uvIndex[2] - 1));
        //            objInfo[objCount].faces_normals.push_back(ivec3(normalIndex[0] - 1, normalIndex[1] - 1, normalIndex[2] - 1));

        //        }
        //        
        //        
        //        
        //        
        //    }
        //}

        //fclose(file);
        return true;
    }

    void printInfo() {

        if (objInfo.size() == 0) {
            cout << " 저장된 객체 정보 없음 " << endl;
            return;
        }

        cout << "----- 객체 정보 ------\n" << endl;

        for (int i = 0; i < objInfo.size(); i++) {
            cout << " 번호 : " << i << endl;
            cout << " 이름 : " << objInfo[i].name << endl;
            cout << " 정점 개수 : " << objInfo[i].vertices.size() << endl;
            cout << " 노말 벡터 개수 : " << objInfo[i].normals.size() << endl;
            cout << " uv 개수 : " << objInfo[i].uvs.size() << endl;
            cout << " 면 정점 개수 : " << objInfo[i].faces_vertices.size() << endl;
            cout << " 면 uv 개수 : " << objInfo[i].faces_uvs.size() << endl;
            cout << " 면 노말 벡터 개수 : " << objInfo[i].faces_normals.size() << endl;
            cout << "\n----------------------" << endl;
        }


    }
};

