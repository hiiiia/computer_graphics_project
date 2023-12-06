//#include <vector>
//#include <string>
//#include <fstream>
//#include <iostream>
//
//using namespace std;
//
////2차원 점 ( 텍스처 정보 )
//class CPoint2f {
//public:
//	vector <float> d{ 0,0 };
//
//};
//
////3차원 실수 점
//class CPoint3f {
//public:
//	vector <float> d{ 0,0,0 };
//
//};
//
////3차원 정수 점
//class CPoint3i {
//public:
//	vector <int> d{ 0,0,0 };
//
//};
//
////면
//class CFace {
//public:
//	vector <CPoint3i> v_pairs;
//
//};
//
//// 오브젝트 정보
//class CObj {
//public:
//	string name;
//	vector <CPoint3f> v;
//	vector <CPoint2f> vt;
//	vector <CPoint3f> vn;
//	vector <CFace> f;
//};
//	
////모델 정보
//class CModel {
//public:
//	vector <CObj> objs;
//
//	//string을 특정 문자(delimeter)를 기준으로 나누는 것 
//	vector<float> my_strtok_f(char* str, char* delimeter) {
//
//		vector <float> v;
//		char* context;
//		char* tok = strtok_s(str, delimeter, &context);
//
//		while (tok != NULL) {
//			v.push_back(atof(tok));
//			tok = strtok_s(context, delimeter, &context);
//		}
//
//		return v;
//	}
//
//	vector<string> my_strtok_s(char* str, char* delimeter) {
//
//		vector <string> v;
//		char* context;
//		char* tok = strtok_s(str, delimeter, &context);
//
//		while (tok != NULL) {
//			cout << tok;
//			v.push_back(tok);
//			tok = strtok_s(context, delimeter, &context);
//		}
//
//		return v;
//	}
//
//	vector<int> my_strtok_i(char* str, char* delimeter) {
//		vector <int> v;
//		char* context;
//		char* tok = strtok_s(str, delimeter, &context);
//
//		while (tok != NULL) {
//			v.push_back(atoi(tok));
//			tok = strtok_s(context, delimeter, &context);
//		}
//		return v;
//	}
//
//	void loadObj(ifstream& fin) {
//		// 파일 한줄 읽기
//		string line;
//		// 오브젝트 하나를 불러서 임시로 저장용
//		CObj obj_tmp;
//
//		// 몇개의 오브젝트를 불러왔는지 확인
//		int cnt = 0;
//
//		while (getline(fin, line)) {
//			int len = line.length();
//			vector<float> vf;
//			vector<string> s;
//			vector<int> vi;
//			CPoint3f p3;
//			CPoint2f p2;
//			CPoint3i p3i;
//
//			cout << line << "\n";
//
//			//파일에서 v,vt 등등 구별
//			if (line[0] == 'o' && line[1] == ' ') {
//				obj_tmp.name = line.substr(2, len - 2);
//				objs.push_back(obj_tmp);
//				cnt += 1;
//			}
//
//			if(cnt < 1){
//				//cout << "카운트 안오름";
//				continue;
//			}
//
//			if (line[0] == 'v' && line[1] == ' ') {
//				vf = my_strtok_f
//				((char*)line.substr(2,len - 2).c_str(),(char*)" ");
//				p3.d = { vf[0],vf[1],vf[2] };
//				objs[cnt - 1].v.push_back(p3);
//			}
//			else if (line[0] == 'v' && line[1] == 't') {
//				vf = my_strtok_f
//				((char*)line.substr(3, len - 2).c_str(), (char*)" ");
//				p2.d = { vf[0], vf[1] };
//				objs[cnt - 1].vt.push_back(p2);
//			}
//			else if (line[0] == 'v' && line[1] == 'n') {
//				vf = my_strtok_f
//				((char*)line.substr(3, len - 2).c_str(), (char*)" ");
//				p3.d = { vf[0], vf[1], vf[2] };
//				objs[cnt - 1].vn.push_back(p3);
//			}
//			else if (line[0] == 'f' && line[1] == ' ') {
//				s = my_strtok_s
//				((char*)line.substr(3, len - 2).c_str(), (char*)" ");
//				int nVertexes = s.size();
//				
//				CFace face_tmp;
//
//				for (int i = 0; i < nVertexes; i++) {
//					vi = my_strtok_i((char*)s[i].c_str(), (char*)"/");
//					p3i.d = { vi[0], vi[1], vi[2] };
//					face_tmp.v_pairs.push_back(p3i);
//				}
//				objs[cnt - 1].f.push_back(face_tmp);
//			}
//
//
//		}
//	}
//
//	void readline(ifstream& fin) {
//		string line;
//
//	}
//
//};
//
//CModel m;
//
//int main(int argc, char** argv) {
//
//	string filepath = "C:/Users/user/Desktop/computer_graphics_project/3D_Models/Wooden Barrel/test.txt";
//	ifstream fin(filepath);
//
//	//m.readline(fin);
//
//	//m.loadObj(fin);
//
//	fin.close();
//	cout << "helo";
//
//
//    return 0;
//}
