//
//  CommonUtil.cpp
//  Menu
//
//  Created by 成田 輝久 on 2013/11/03.
//
//

#include "CommonUtil.h"

// 文字列の長さを全角文字数で数える
int utf8len(const string &s)
{
    size_t i = 0;
    size_t len = 0;
    size_t s_size = s.size();
    unsigned char c;
    while(i < s_size){
        c = s[i];
        if(c == 0x00) i += 0;
        else if(c < 0x80) i += 1;
        else if(c < 0xC2) throw logic_error("error");
        else if(c < 0xE0) i += 2;
        else if(c < 0xF0) i += 3;
        else if(c < 0xF8) i += 4;
        else if(c < 0xFC) i += 5;
        else if(c < 0xFE) i += 6;
        else i += 1;
        len++;
    }
    return len;
}

// 文字列の長さを半角文字数で数える
int utf8HWlen(const string &s)
{
    size_t i = 0;
    size_t len = 0;
    size_t s_size = s.size();
    unsigned char c;
    while(i < s_size){
        c = s[i];
        if(c == 0x00) i += 0;
        else if(c < 0x80) {
            i += 1;
            len ++;
            continue;
        }
        else if(c < 0xC2) throw logic_error("error");
        else if(c < 0xE0) i += 2;
        else if(c < 0xF0) i += 3;
        else if(c < 0xF8) i += 4;
        else if(c < 0xFC) i += 5;
        else if(c < 0xFE) i += 6;
        else i += 1;
        len+=2;
    }
    return len;
}

// n番目の全角文字のインデックスを返す
int utf8index(const string &s, int widx) {
    if(widx == 0)return 0;
    
    size_t i = 0;
    size_t len = 0;
    size_t s_size = s.size();
    unsigned char c;
    while(i < s_size){
        c = s[i];
        if(c == 0x00) i += 0;
        else if(c < 0x80) i += 1;
        else if(c < 0xC2) throw logic_error("error");
        else if(c < 0xE0) i += 2;
        else if(c < 0xF0) i += 3;
        else if(c < 0xF8) i += 4;
        else if(c < 0xFC) i += 5;
        else if(c < 0xFE) i += 6;
        else i += 1;
        len++;
        if(len == widx) return i;
    }
    return -1;
}

// stringのbegin番目の全角文字からbegin+length-1番目の全角文字までのsubstringを返す
std::string utf8substr(const string &s, int begin, int length) {
    int beginIndex = utf8index(s, begin);
    int endIndex   = utf8index(s, begin+length);
    return s.substr(beginIndex, endIndex-beginIndex);
}

// メッシュに法線ベクトルを自動追加する（TRIANGLESを想定）
void setNormals(ofMesh &mesh) {
    int nV = mesh.getNumVertices();
    int nT = mesh.getNumIndices() / 3;
    vector<ofPoint> norm(nV);
    
    for(int t=0;t<nT;t++) {
        int i1 = mesh.getIndex(3 * t );
        int i2 = mesh.getIndex(3 * t + 1);
        int i3 = mesh.getIndex(3 * t + 2);
        
        const ofPoint &v1 = mesh.getVertex(i1);
        const ofPoint &v2 = mesh.getVertex(i2);
        const ofPoint &v3 = mesh.getVertex(i3);
        
        ofPoint dir = ((v2 - v1)).crossed(v3 - v1).normalized();
        
        norm[i1] += dir;
        norm[i2] += dir;
        norm[i3] += dir;
    }
    
    for(int i=0;i<nV;i++) {
        norm[i].normalize();
    }
    mesh.clearNormals();
    mesh.addNormals(norm);
}