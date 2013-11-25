//
//  Plane.cpp
//  study_texture
//
//  Created by 成田 輝久 on 2013/11/24.
//
//

#include "TexturePlane.h"

void TexturePlane::setTexturePointer(ofTexture *texture) {
    if(texture == NULL)return;
    this->texture = texture;
    resizeToTexture(*texture);
}

void TexturePlane::draw() {
    if(texture != NULL) texture->bind();
    ofPlanePrimitive::draw();
    if(texture != NULL) texture->unbind();
}