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
    ObjInfo_f4 objInfo;

    int objCount = -1;

    bool Load(const char* path)
    {
        ifstream file(path); // 파일을 읽기 모드로 엽니다.
        if (!file.is_open()) {
            std::cerr << "파일 열기 실패" << std::endl;
            return false;
        }

        string line;
        
        

        while (std::getline(file, line)) {
            vector<string> tokens;
            istringstream iss(line);
            string token;
            while (iss >> token) {
                tokens.push_back(token);
            }

            if (tokens.size() == 0) { continue; }

            if (tokens[0] == "o") {

                /*ObjInfo_f4 newObjInfo;

                newObjInfo.name = tokens[1];

                objInfo.push_back(newObjInfo);*/
                objCount++;
            }
            else if (tokens[0] == "v") {
                vec3 vertex;

                vertex.x = stof(tokens[1]);
                vertex.y = stof(tokens[2]);
                vertex.z = stof(tokens[3]);

                objInfo.vertices.push_back(vertex);
                
            }
            else if (tokens[0] == "vn") {
                vec3 normal;

                normal.x = stof(tokens[1]);
                normal.y = stof(tokens[2]);
                normal.z = stof(tokens[3]);

                objInfo.normals.push_back(normal);
            }
            else if (tokens[0] == "vt") {
                vec2 uv;

                uv.x = stof(tokens[1]);
                uv.y = stof(tokens[2]);

                objInfo.uvs.push_back(uv);
            }
            else if (tokens[0] == "f") {

                //each strings 
                istringstream ss1(tokens[1]);
                istringstream ss2(tokens[2]);
                istringstream ss3(tokens[3]);
                istringstream ss4(tokens[4]);

                //
                string buffer1;
                string buffer2;
                string buffer3;
                string buffer4;

                vector<int> values1;
                vector<int> values2;
                vector<int> values3;
                vector<int> values4;

                while (getline(ss1, buffer1, '/')) {
                    if (!buffer1.empty()) {
                        values1.push_back(stoi(buffer1));
                    }

                }

                while (getline(ss2, buffer2, '/')) {
                    if (!buffer2.empty()) {
                        values2.push_back(stoi(buffer2));
                    }

                }

                while (getline(ss3, buffer3, '/')) {
                    if (!buffer3.empty()) {
                        values3.push_back(stoi(buffer3));
                    }

                }

                while (getline(ss4, buffer4, '/')) {
                    if (!buffer4.empty()) {
                        values4.push_back(stoi(buffer4));
                    }

                }

                if (values1.size() == 2) {
                    objInfo.faces_vertices.push_back(ivec4( values1[0]-1, values2[0]-1, values3[0]-1, values4[0]-1));
                    objInfo.faces_normals.push_back(ivec4( values1[1]-1, values2[1]-1, values3[1]-1, values4[1]-1));
                }

                if (values1.size() == 3) {
                    objInfo.faces_vertices.push_back(ivec4(values1[0]-1, values2[0]-1, values3[0]-1, values4[0]-1));
                    objInfo.faces_uvs.push_back(ivec4(values1[1]-1, values2[1]-1, values3[1]-1, values4[1]-1));
                    objInfo.faces_normals.push_back(ivec4(values1[2]-1, values2[2]-1, values3[2]-1, values4[2]-1));
                    
                    //cout << " 노말 벡터 번호 : " << values1[2] - 1 << " " << values2[2] - 1 << " " << values3[2] - 1 << " " << values4[2] - 1 << " " << endl;
                }

            }



        }

        /*for (int i = 0; i < objInfo.faces_normals.size(); i++) {
            cout << " 노말 번호 : ";
            for (int j = 0; j < 4; j++) {
                cout << objInfo.faces_normals[i][j] << " ";
            }
            cout << endl;
        }*/

        file.close();
        return true;
    }

    void printInfo() {

        
            
        cout << "----- 객체 정보 ------\n" << endl;
        cout << " 이름 : " << objInfo.name << endl;
        cout << " 정점 개수 : " << objInfo.vertices.size() << endl;
        cout << " 노말 벡터 개수 : " << objInfo.normals.size() << endl;
        cout << " uv 개수 : " << objInfo.uvs.size() << endl;
        cout << " 면 정점 개수 : " << objInfo.faces_vertices.size() << endl;
        cout << " 면 uv 개수 : " << objInfo.faces_uvs.size() << endl;
        cout << " 면 노말 벡터 개수 : " << objInfo.faces_normals.size() << endl;
        cout << "\n----------------------" << endl;


            



    }
};

